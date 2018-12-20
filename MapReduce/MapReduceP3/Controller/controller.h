#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#include "../ChatMessage/chat_message.h"


//----------------------------------------------------------------------

typedef std::deque<ChatMessage> ChatMessageQueue;

//----------------------------------------------------------------------

class ChatParticipant {
public:
	virtual ~ChatParticipant() {}
	virtual void deliver(const ChatMessage& msg) = 0;
};

typedef std::shared_ptr<ChatParticipant> ChatParticipantPtr;
//----------------------------------------------------------------------
class ChatRoom{
public:
	void join(ChatParticipantPtr participant){
		participants_.insert(participant);
		for (auto msg : recent_msgs_)
			participant->deliver(msg);
	}
	void leave(ChatParticipantPtr participant){
		participants_.erase(participant);
	}
	void deliver(const ChatMessage& msg){
		recent_msgs_.push_back(msg);
		while (recent_msgs_.size() > max_recent_msgs)
			recent_msgs_.pop_front();
		for (auto participant : participants_)
			participant->deliver(msg);
	}
	void SetMapperNumber(const int num) {
		number_of_mapper_ = num;
	}
	void AddOneFinishedMapper() {
		finished_mapper_++;
		if (finished_mapper_ == number_of_mapper_) {
			ChatMessage msg;
			BOOST_LOG_TRIVIAL(info)<< "AllMappingFinished";
			char line[25] = "AllMappingFinished";
			msg.SetBodyLength(std::strlen(line));
			std::memcpy(msg.GetMyBody(), line, msg.GetBodyLength());
			msg.EncodeHeader();
			recent_msgs_.push_back(msg);
			for (auto participant : participants_)
				participant->deliver(msg);
		}
	}
private:
	std::set<ChatParticipantPtr> participants_;
	enum { max_recent_msgs = 100 };
	ChatMessageQueue recent_msgs_;
	int number_of_mapper_;
	int finished_mapper_ = 0;
};
//----------------------------------------------------------------------
class ChatSession
	: public ChatParticipant,
	public std::enable_shared_from_this<ChatSession>{
public:
	ChatSession(boost::asio::ip::tcp::socket socket, ChatRoom& room)
		: socket_(std::move(socket)),
		room_(room)	{}
	void start(){
		room_.join(shared_from_this());
		do_read_header();
	}
	void deliver(const ChatMessage& msg){
		bool write_in_progress = !write_msgs_.empty();
		write_msgs_.push_back(msg);
		if (!write_in_progress){
			do_write();
		}
	}
private:
	void do_read_header(){
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.GetMyData(), ChatMessage::header_length),
			[this, self](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec && read_msg_.DecodeHeader()){
				do_read_body();
			}else{
				room_.leave(shared_from_this());
			}
		});
	}
	void do_read_body(){
		auto self(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.GetMyBody(), read_msg_.GetBodyLength()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec){
				std::string s(read_msg_.GetMyBody(), read_msg_.GetBodyLength());
				room_.deliver(read_msg_);
				BOOST_LOG_TRIVIAL(info) << s;
				if (s == "map_process_done") {
					room_.AddOneFinishedMapper();
				}
				do_read_header();
			}else{
				room_.leave(shared_from_this());
			}
		});
	}

	void do_write(){
		auto self(shared_from_this());
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().GetMyData(),
				write_msgs_.front().GetMyLength()),
			[this, self](boost::system::error_code ec, std::size_t /*length*/){
			if (!ec){
				write_msgs_.pop_front();
				if (!write_msgs_.empty()){
					do_write();
				}
			}else{
				room_.leave(shared_from_this());
			}
		});
	}
	boost::asio::ip::tcp::socket socket_;
	ChatRoom& room_;
	ChatMessage read_msg_;
	ChatMessageQueue write_msgs_;
};

//----------------------------------------------------------------------

class ChatServer{
public:
	ChatServer(boost::asio::io_context& io_context,
		const boost::asio::ip::tcp::endpoint& endpoint,
		const int number_of_mapper)
		: acceptor_(io_context, endpoint){
		room_.SetMapperNumber(number_of_mapper);
		do_accept();
	}
private:
	void do_accept(){
		acceptor_.async_accept(
			[this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket){
			if (!ec){
				std::make_shared<ChatSession>(std::move(socket), room_)->start();
			}
			do_accept();
		});
	}
	boost::asio::ip::tcp::acceptor acceptor_;
	ChatRoom room_;
};
#endif
