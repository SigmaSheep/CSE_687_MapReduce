#include "controller.h"


void Controller::BindArguments(const std::string& input_path, const std::string& media_path,
	const std::string& out_path, const std::string& map_dll_path,
	const std::string& reduce_dll_path, const int m_count, const int r_count
	, const int stub_count, const std::vector<std::string>& ip_list,
	const std::vector<std::string>& port_list) {
	arguments_ = input_path + "<>" + media_path + "<>" + out_path
		+ "<>" + map_dll_path + "<>" + reduce_dll_path
		+ "<>" + std::to_string(m_count) + "<>" + std::to_string(r_count)
		+ "<>" + std::to_string(stub_count);
	stub_count_ = stub_count;
	ip_list_ = ip_list;
	port_list_ = port_list;
};

void Controller::Start() {
	try	{
		// first, send arguments to stubs
		boost::asio::io_service io_service;
		for (int i = 0; i < stub_count_; i++) {
			std::string arguments_tmp = arguments_ + "<>" + std::to_string(i);
			size_t request_length = arguments_tmp.length();
			SingleConnection connect(ip_list_[i], port_list_[i], io_service);
			connection_list_.emplace_back(ip_list_[i], port_list_[i], io_service);
			endpoint_list_.push_back(connect.Connect());
			boost::asio::write(connect.socket_,
				boost::asio::buffer(arguments_tmp, request_length));
		}
		
		
		/*
		char reply[max_length];
		SingleConnection connect1(ip_list_[0], port_list_[0], io_service);

		size_t reply_length = connect1.socket_.read_some(boost::asio::buffer(reply));
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
		*/
		std::cin.get();
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
}