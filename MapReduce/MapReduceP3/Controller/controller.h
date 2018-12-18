
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <vector>
class SingleConnection // inheritent shared_ptr to keep instance alive
	:public std::enable_shared_from_this<SingleConnection>{ 
public:
	SingleConnection(std::string ip_address, std::string port,
		boost::asio::io_service& io_service)
		:socket_(io_service), resolver_(io_service),
		query_(ip_address, port) {
		endpoint_iterator_ = resolver_.resolve(query_);
	}
	boost::asio::ip::tcp::endpoint Connect(){
		return boost::asio::connect(socket_, endpoint_iterator_); // conect
	}

	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::resolver resolver_;
	boost::asio::ip::tcp::resolver::query query_;
	boost::asio::ip::basic_resolver_results<boost::asio::ip::tcp>
		endpoint_iterator_;
};

class Controller {
public:
	Controller() {}
	void Start();
	void BindArguments(const std::string& input_path, const std::string& media_path,
		const std::string& out_path, const std::string& map_dll_path,
		const std::string& reduce_dll_path, const int m_count, const int r_count
		, const int stub_count, const std::vector<std::string>& ip_list, 
		const std::vector<std::string>& port_list);
private:
	int stub_count_;
	std::string arguments_;
	std::list<SingleConnection> connection_list_;
	std::vector<boost::asio::ip::tcp::endpoint> endpoint_list_;
	std::vector<boost::asio::ip::tcp::socket> socket_list_;
	enum { max_length = 1024 };
	std::vector<std::string> ip_list_;
	std::vector<std::string> port_list_;
};

