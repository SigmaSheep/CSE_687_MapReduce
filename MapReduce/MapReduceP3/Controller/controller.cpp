#include "controller.h"


/*

void Controller::Start() {
	try	{
		// first, send arguments to stubs
		boost::asio::io_service io_service;
		for (int i = 0; i < stub_count_; i++) {
			std::string arguments_tmp = arguments_ + "<>" + std::to_string(i);
			size_t request_length = arguments_tmp.length();
			StubConnection connect(ip_list_[i], port_list_[i], io_service);
			connection_list_.emplace_back(ip_list_[i], port_list_[i], io_service);
			endpoint_list_.push_back(connect.Connect());
			boost::asio::write(connect.socket_,
				boost::asio::buffer(arguments_tmp, request_length));
		}
		
		
		
		char reply[max_length];
		SingleConnection connect1(ip_list_[0], port_list_[0], io_service);

		size_t reply_length = connect1.socket_.read_some(boost::asio::buffer(reply));
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
		
		std::cin.get();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
*/