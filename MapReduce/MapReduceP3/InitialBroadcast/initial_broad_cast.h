#ifndef INITIAL_BROADCAST_H
#define INITIAL_BROADCAST_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp> // boost::lexical_cast<int>()

#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "../FileMgt/file_mgt.h"

static int finished_count_ = 0;

class InitalBroadCast
	:public std::enable_shared_from_this<InitalBroadCast> {
public:
	InitalBroadCast(boost::asio::ip::tcp::socket socket,
		boost::asio::io_service& io_service,
		boost::asio::io_service::strand& strand,
		const std::string& arguments,
		const int stub_index, const int stub_count)
		:strand_(strand), socket_(std::move(socket)), io_service_(io_service),
		arguments_(arguments + "<>" + std::to_string(stub_index)),
		stub_index_(stub_index), stub_count_(stub_count) {}
	void Start() {
		size_t request_length = arguments_.size();
		boost::asio::write(socket_,
			boost::asio::buffer(arguments_, request_length));
	};

private:
	int stub_index_;
	int stub_count_;
	std::string arguments_;
	std::string feed_back_;
	boost::asio::io_service& io_service_;
	boost::asio::io_service::strand& strand_;
	boost::asio::ip::tcp::socket socket_;
	enum { max_length = 1024 };
};

class StubConnection {
public:
	// constructor
	StubConnection(const std::vector<std::string>& ip_address_list,
		const std::vector<std::string>& port_list,
		boost::asio::io_service& io_service,
		boost::asio::io_service::strand strand,
		const std::string& arguments)
		:strand_(strand), socket_(io_service), resolver_(io_service),
		arguments_(arguments), stub_index_(0), io_service_(io_service),
		ip_list_(ip_address_list), port_list_(port_list),
		stub_count_(boost::lexical_cast<int>(FileMgt::ArgumentExtra(7, arguments))),
		query_(ip_address_list[0], port_list[0]) {
		Connect();
	}
	void Connect() {
		endpoint_iterator_ = resolver_.resolve(query_); //update endpoint
		boost::asio::connect(socket_, endpoint_iterator_);
		std::make_shared<InitalBroadCast>(std::move(socket_), io_service_, strand_,
			arguments_, stub_index_, stub_count_)->Start();
		stub_index_++;
		if (stub_index_ == stub_count_) { return; } // return when connect all stubs
		query_ = boost::asio::ip::tcp::resolver::query(
			ip_list_[stub_index_], port_list_[stub_index_]);
		Connect();
	}
private:
	int stub_index_;
	int stub_count_;
	std::string arguments_;
	std::vector<std::string> ip_list_;
	std::vector<std::string> port_list_;
	boost::asio::io_service& io_service_;
	boost::asio::io_service::strand& strand_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::resolver resolver_;
	boost::asio::ip::tcp::resolver::query query_;
	boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>
		endpoint_iterator_;
};

#endif
