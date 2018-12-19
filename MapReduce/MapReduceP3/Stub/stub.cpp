
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include "../StubWorkFlow/stub_work_flow.h"

int main() {
	int port;
	std::cin >> port;
	enum { max_length = 1024 };
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint);
	boost::asio::ip::tcp::socket socket(io_context);
	acceptor.accept(socket);

	std::string message;

	boost::system::error_code ignored_error;
	char buf[max_length];
	size_t len = socket.read_some(boost::asio::buffer(buf,max_length));
	//std::cout.write(buf, len);
	
	std::vector<std::string> arguments_vector;
	std::string arguments_string(buf, len);
	std::cout << arguments_string;
	boost::algorithm::split(arguments_vector, arguments_string,
		boost::is_any_of("<>"), boost::token_compress_on);
	/*
	for (auto it = arguments_vector.begin(); 
		it != arguments_vector.end(); ++it) {
		std::cout << *it << "\n";
	}
	*/

	auto it = arguments_vector.begin();
	std::string input_path = *it;
	++it;
	std::string media_path = *it;
	++it;
	std::string out_path = *it;
	++it;
	std::string map_dll_path = *it;
	++it;
	std::string reduce_dll_path = *it;
	++it;
	int m_count = std::stoi(*it);
	++it;
	int r_count = std::stoi(*it);
	++it;
	int stub_count = std::stoi(*it);
	++it;
	int stub_id = std::stoi(*it);

	StubWorkFlow stub_work_flow(input_path, media_path, out_path, map_dll_path,
		reduce_dll_path, m_count, r_count, stub_count, stub_id);

	stub_work_flow.InvokeMapperProcess();
	boost::asio::write(socket,boost::asio::buffer("F"));
	//len = socket.read_some(boost::asio::buffer(buf, max_length));
		
	//std::string feed_back(buf, len);
	//std::cout << feed_back << "\n";

	std::cin.get();
	return 0;
}

