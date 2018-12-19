#include "work_flow.h"

// WorkFlow handles all working logics
WorkFlow::WorkFlow(const std::string input_path, const std::string media_path,
	const std::string out_path, const std::string map_dll_path,
	const std::string reduce_dll_path, int m_count, int r_count,
	const int stub_count, const std::vector<std::string>& ip_list,
	const std::vector<std::string> port_list) {
	
	std::string arguments = FileMgt::BindArguments(input_path, media_path,
		out_path, map_dll_path, reduce_dll_path, m_count, r_count, stub_count);
	
	boost::asio::io_service io_service;
	boost::asio::io_service::strand strand(io_service);
	//std::thread t([&io_service]() { io_service.run(); });
	StubConnection stub_connections(ip_list, port_list, 
		io_service, strand,arguments);
	BOOST_LOG_TRIVIAL(info) << "initial broadcast end \n";

	boost::asio::io_context io_context;
	boost::asio::ip::tcp::endpoint endpoint(
		boost::asio::ip::tcp::v4(), 5050); // hard coded listen port
	ChatServer servers(io_context, endpoint, m_count);
	BOOST_LOG_TRIVIAL(info) << "start server \n";
	io_context.run();
}
