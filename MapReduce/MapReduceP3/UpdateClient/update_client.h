#ifndef UPDATE_CLIENT_H
#define UPDATE_CLIENT_H

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "../ChatMessage/chat_message.h"
typedef std::deque<ChatMessage> ChatMessageQueue;

class ChatClient{
public:
	ChatClient(boost::asio::io_context& io_context,
		const boost::asio::ip::tcp::resolver::results_type& endpoints,
		const bool reducer_flag)
		: io_context_(io_context),
		socket_(io_context), reducer_flag_(reducer_flag){
		do_connect(endpoints);
	}
	void write(const ChatMessage& msg){
		boost::asio::post(io_context_,
			[this, msg](){
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress){
				do_write();
			}
		});
	}
	void close(){
		boost::asio::post(io_context_, [this]() { socket_.close(); });
	}
private:
	void do_connect(
		const boost::asio::ip::tcp::resolver::results_type& endpoints){
		boost::asio::async_connect(socket_, endpoints,
			[this](boost::system::error_code ec, 
				boost::asio::ip::tcp::endpoint){
			if (!ec){
				do_read_header();
			}
		});
	}
	void do_read_header(){
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.GetMyData(), ChatMessage::header_length),
			[this](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec && read_msg_.DecodeHeader()){
				do_read_body();
			}else{
				socket_.close();
			}
		});
	}

	void do_read_body(){
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.GetMyBody(), read_msg_.GetBodyLength()),
			[this](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec){
				std::string msg(read_msg_.GetMyBody(), read_msg_.GetBodyLength());
				if (msg == "AllMappingFinished"&&reducer_flag_) {
					close();
				}
				do_read_header();
			}else{
				socket_.close();
			}
		});
	}
	void do_write(){
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().GetMyData(),
				write_msgs_.front().GetMyLength()),
			[this](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec){
				write_msgs_.pop_front();
				if (!write_msgs_.empty()){
					do_write();
				}
			}else{
				socket_.close();
			}
		});
	}
private:
	boost::asio::io_context& io_context_;
	boost::asio::ip::tcp::socket socket_;
	ChatMessage read_msg_;
	ChatMessageQueue write_msgs_;
	bool reducer_flag_;
};
#endif
