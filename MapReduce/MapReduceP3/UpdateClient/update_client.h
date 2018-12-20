#ifndef UPDATE_CLIENT_H
#define UPDATE_CLIENT_H

#include <boost/asio.hpp>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include "../ChatMessage/chat_message.h"
/*
Update client is implemented by ChatClient. Mapper forks thread
to run this ChatClient and connects to Controller(server). Mapper
mainly write finish message when mapper finished and reducer wait 
for service's ready boradcast. 
*/
typedef std::deque<ChatMessage> ChatMessageQueue;
class ChatClient{
public:
	ChatClient(boost::asio::io_context& io_context,
		const boost::asio::ip::tcp::resolver::results_type& endpoints,
		const bool reducer_flag)
		: io_context_(io_context),
		socket_(io_context), reducer_flag_(reducer_flag){
		DoConnect(endpoints);
	}
	void Write(const ChatMessage& msg){
		boost::asio::post(io_context_,
			[this, msg](){
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress){
				DoWrite();
			}
		});
	}
	void Close(){
		boost::asio::post(io_context_, [this]() { socket_.close(); });
	}
private:
	void DoConnect(
		const boost::asio::ip::tcp::resolver::results_type& endpoints){
		boost::asio::async_connect(socket_, endpoints,
			[this](boost::system::error_code ec, 
				boost::asio::ip::tcp::endpoint){
			if (!ec){
				DoReadHeader();
			}
		});
	}
	void DoReadHeader(){
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.GetMyData(), ChatMessage::header_length),
			[this](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec && read_msg_.DecodeHeader()){
				DoReadBody();
			}else{
				socket_.close();
			}
		});
	}
	void DoReadBody(){
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.GetMyBody(), read_msg_.GetBodyLength()),
			[this](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec){
				std::string msg(read_msg_.GetMyBody(), read_msg_.GetBodyLength());
				if (msg == "AllMappingFinished"&&reducer_flag_) {
					Close();
				}
				DoReadHeader();
			}else{
				socket_.close();
			}
		});
	}
	void DoWrite(){
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().GetMyData(),
				write_msgs_.front().GetMyLength()),
			[this](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec){
				write_msgs_.pop_front();
				if (!write_msgs_.empty()){
					DoWrite();
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
