#include <boost/algorithm/string.hpp> //split
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include "../StubWorkFlow/stub_work_flow.h"
/*
Stub is the first one to run. Type the port number 
and the stub would wait for controller's connection. Stub only recieves one 
message. Stub then invokes mappers and reducers according to controller's
allocation.
*/
int main() {
	std::cout << "type the port for this stub like 8080\n"
		<< "port 5050 is reserved for controller\n";
	int port;
	std::cin >> port;
	enum { max_length = 1024 };
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
	boost::asio::ip::tcp::acceptor acceptor(io_context, endpoint);
	boost::asio::ip::tcp::socket socket(io_context);
	acceptor.accept(socket);
	// ready for initial connection from controller
	std::string message;
	boost::system::error_code ignored_error;
	char buf[max_length];
	// read arguments as a long string
	size_t len = socket.read_some(boost::asio::buffer(buf,max_length));
	// split the long string into individual arguments
	std::vector<std::string> arguments_vector;
	std::string arguments_string(buf, len);
	boost::algorithm::split(arguments_vector, arguments_string,
		boost::is_any_of("<>"), boost::token_compress_on);

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

	// initial StubWorkFlow and ready for invoking mappers and reducers
	StubWorkFlow stub_work_flow(input_path, media_path, out_path, map_dll_path,
		reduce_dll_path, m_count, r_count, stub_count, stub_id);
	stub_work_flow.InvokeMapperProcess();
	stub_work_flow.InvokeReducerProcess();

	std::cin.get();
	return 0;
}

