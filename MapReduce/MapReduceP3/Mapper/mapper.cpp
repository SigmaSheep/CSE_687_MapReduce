//Dec 04 2018 first release
#include "../ChatMessage/chat_message.h"
#include "../FileMgt/file_mgt.h"
#include "../MapInterface/map_interface.h"
#include "../UpdateClient/update_client.h"
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp> // boost::lexical_cast<int>()
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(log/error)
#include <iostream> // std::cout for debugging 
#include <mutex>  // std::mutex
#include <thread> // std::thread
#include <windows.h> // HMODULE, GetProcAddress(), FreeLibrary()

// flag for heart beat thread
bool finish_flag = false;

// as a function pointer passed to map function to exporting data
void ExportingMedianFile(
	const std::vector<std::pair<std::string, std::string>>& tokenized,
	const std::vector<std::string>& median_file_list);

// as thread function
void MapThreadFunction(int thread_id, int mapper_process_id, 
	std::string map_dll_path, int r_count, std::string median_path,
	MapInterface* map_pointer,
	std::vector<std::string>::const_iterator start_median_file,
	std::vector<std::string>::const_iterator end_median_file);

void MapHeartBeatThreadFunc(const int id);

int main(int argc, char * argv[]) {
	

	// recieve parameters: mapper proc #id, dll_path, number of reducer,
	//					   median_file_path, input_file_paths(multiple)
	if (argc < 4) {
		BOOST_LOG_TRIVIAL(error) << 
			"Less arguments recieved in mapper process\n";
		std::exit(EXIT_FAILURE);
	}
	int mapper_process_id = boost::lexical_cast<int>(argv[0]);//cast to int
	// invoke heart beat thread
	std::thread map_hb_thread(MapHeartBeatThreadFunc, mapper_process_id);

	BOOST_LOG_TRIVIAL(info) << "Mapper process #"
		<< mapper_process_id<<" is created\n";
	std::string map_dll_path = argv[1];
	int r_count = boost::lexical_cast<int>(argv[2]);//cast to int
	std::string median_path = argv[3];
	std::vector<std::string> input_file_list;
	for (int i = 4; i < argc; i++) {
		input_file_list.push_back(argv[i]);
	}
	//load dll
	typedef MapInterface*(CALLBACK* MapHolder)();
	HMODULE h_mod_map = LoadLibrary(map_dll_path.c_str());
	if (h_mod_map == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load map library failed\n";
		std::exit(EXIT_FAILURE);
	}
	MapHolder mCtor = (MapHolder)GetProcAddress(h_mod_map, 
		"CreateMapIns");
	if (mCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress map dll failed\n";
		std::exit(EXIT_FAILURE);
	}
	MapInterface* map_pointer = mCtor();

	// divide median files based on thread number
	// now 2 threads
	int input_file_count = input_file_list.size();
	std::vector<std::string>::const_iterator start_input_file =
		input_file_list.begin();
	std::vector<std::string>::const_iterator end_input_file =
		start_input_file + input_file_count / 2;
	// start thread #1
	std::thread t1(MapThreadFunction, 0,mapper_process_id, map_dll_path,
		r_count, median_path, map_pointer, start_input_file,
		end_input_file);
	start_input_file = end_input_file;
	end_input_file = input_file_list.end();
	// start thread #2
	std::thread t2(MapThreadFunction, 1,mapper_process_id, map_dll_path,
		r_count, median_path, map_pointer, start_input_file,
		end_input_file);
	t1.join();
	t2.join();

	FreeLibrary(h_mod_map);
	BOOST_LOG_TRIVIAL(info) << "Mapper process #"
		<< mapper_process_id << " ended\n";
	
	finish_flag = true;
	map_hb_thread.join();
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// void exportingMedianFile(
//		const std::vector<std::pair<std::string, std::string>> tokenized,
//		std::string median_file_name)
// input: tokenized- vector of pair contains value and key
//		  median_file_name- path to median file
// output: void writing tokenized vector into median file
/////////////////////////////////////////////////////////////////////////////////
void ExportingMedianFile(
	const std::vector<std::pair<std::string, std::string>>& tokenized,
	const std::vector<std::string>& median_file_list) {
	size_t r_count = median_file_list.size();
	std::ofstream *outfiles = new std::ofstream[r_count];//allocate heap
	for (int i = 0; i < (int)r_count; i++) { // open median files
		outfiles[i].open(median_file_list[i], std::ios::app);
	}
	// deliver pairs to different median files based on key's hash value
	std::hash<std::string> HashFunction;
	std::pair<std::string, std::string> tmp_pair;
	size_t hash_value;
	for (auto it = tokenized.begin(); it != tokenized.end(); ++it) {
		tmp_pair = *it;
		hash_value = HashFunction(tmp_pair.first) % r_count;
		if (outfiles[hash_value].is_open()) {//key and value seprate by " "
			outfiles[hash_value] << tmp_pair.first << " "
				<< tmp_pair.second << std::endl;
		} else {
			BOOST_LOG_TRIVIAL(error) << "Open median files failed\n";
			std::exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < (int)r_count; i++) {//close all files
		outfiles[i].close();
	}
	delete[] outfiles;//delete in heap
};
//////////////////////////////////////////////////////////////////////////////////
//void MapThreadFunction(int thread_id, int mapper_process_id,
//		std::string map_dll_path,
//		int r_count, std::string median_path, MapInterface* map_pointer,
//		std::vector<std::string>::const_iterator start_input_file,
//		std::vector<std::string>::const_iterator end_input_file)
// run as map thread function
/////////////////////////////////////////////////////////////////////////////////
void MapThreadFunction(int thread_id, int mapper_process_id, 
	std::string map_dll_path,
	int r_count, std::string median_path, MapInterface* map_pointer,
	std::vector<std::string>::const_iterator start_input_file,
	std::vector<std::string>::const_iterator end_input_file) {
	static std::mutex mtx; // lock
	std::vector<std::string> input_file_list(
		start_input_file, end_input_file);
	FileMgt file_mgt_instance;
	// create median file name list
	std::vector<std::string> median_file_name_list =
		file_mgt_instance.CreateMedianFiles(mapper_process_id, r_count,
			median_path);
	for (auto it = input_file_list.begin();//map each file in loop 
		it != input_file_list.end(); ++it) {
		std::string input_file = *it;
		int len = input_file.size();
		std::ifstream infile(*it); // open each input file
		std::string input_line;
		if (infile.is_open()) {
			BOOST_LOG_TRIVIAL(info) << "Mapper #" << mapper_process_id
				<<" thread #"<< thread_id
				<< " is mapping input file: \n" << std::string(52, ' ')
				<< *it << "\n";
			while (std::getline(infile, input_line)) {// read line
				std::vector<std::pair<std::string, std::string>> key_values =
					map_pointer->MapFunction(input_file, 
						std::ref(input_line));//call MapFunction from Dll
				mtx.lock(); // lock before exporting
				ExportingMedianFile(std::ref(key_values),
					std::ref(median_file_name_list));
				mtx.unlock();
			}
		} else {
			BOOST_LOG_TRIVIAL(error)
				<< "Open below input file failed\n"
				<< std::string(52, ' ')
				<< *it << "\n";
			std::exit(EXIT_FAILURE);
		}
		infile.close();
	}
};

void MapHeartBeatThreadFunc(int id) {
	boost::asio::io_context io_context;

	boost::asio::ip::tcp::resolver resolver(io_context);
	boost::asio::ip::tcp::resolver::query query("localhost", "5050");
	auto endpoints = resolver.resolve(query);
	ChatClient c(io_context, endpoints,false);

	std::thread t([&io_context]() { io_context.run(); });
	char line1[ChatMessage::max_body_length + 1];
	while (finish_flag == false) {
		::Sleep(5000);
		ChatMessage msg;
		std::string str_message(("mapper#" + 
			std::to_string(id) + " is runing"));
		msg.SetBodyLength(std::strlen(str_message.c_str()));
		std::memcpy(msg.GetMyBody(), str_message.c_str(), msg.GetBodyLength());
		msg.EncodeHeader();
		c.write(msg);
	}
	ChatMessage msg;
	char line[25] = "map_process_done";
	msg.SetBodyLength(std::strlen(line));
	std::memcpy(msg.GetMyBody(), line, msg.GetBodyLength());
	msg.EncodeHeader();
	::Sleep(2500); // wait some time for connection
	c.write(msg); // writing routine ignore the last one
	::Sleep(2500);
	std::string str_message(("mapper#" +
		std::to_string(id) + " finished"));
	msg.SetBodyLength(std::strlen(str_message.c_str()));
	std::memcpy(msg.GetMyBody(), str_message.c_str(), msg.GetBodyLength());
	msg.EncodeHeader();
	c.write(msg);
	c.close();
	t.join();
};
