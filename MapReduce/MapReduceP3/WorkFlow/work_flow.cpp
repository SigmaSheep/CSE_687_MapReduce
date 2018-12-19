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
	
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 1234);
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);
	boost::asio::ip::tcp::socket socket(io_service);
	acceptor.accept(socket);
	std::string message;
	boost::system::error_code ignored_error;
	char buf[1024];
	size_t len = socket.read_some(boost::asio::buffer(buf, 1024));

	/*
	// SECTION 1: invok mapper processes
	// put input files' paths into vector input_file_list
	FileMgt file_mgt_instance;
	std::vector<std::string> input_file_list =
		file_mgt_instance.FileIter(input_path);
	if (input_file_list.size() < (int)m_count) {
		BOOST_LOG_TRIVIAL(error) << "Too many mapper processes";
		std::exit(EXIT_FAILURE);
	}
    file_mgt_instance.FileIter(media_path);//just check if exist
    file_mgt_instance.FileIter(out_path);//just check if exist
    file_mgt_instance.ClearDirectory(media_path);//clear median_path
    file_mgt_instance.ClearDirectory(out_path); // clear out_path
	// divide input files based on the map count
	std::vector<std::string> divided_file_list =
		file_mgt_instance.AllocateInputFiles(m_count*stub_count,
			std::ref(input_file_list));
	std::vector<std::string> input_file_list_for_this_stub(
		divided_file_list.begin()+stub_id*r_count,
		divided_file_list.begin()+(stub_id+1)*r_count);
	//combine arguments for mapper: stub_id, number of stubs
	//								process_id, map_dll_path,number of reducer,
	//	                            median_file_path, divided_file_list
	std::vector<std::string> argument_ready_mapper_input;
	for (int i = 0; i < m_count;i++) {
		argument_ready_mapper_input.push_back(std::to_string(stub_id)
			+ std::to_string(stub_count)+ " " + std::to_string(i)+ " "
			+ map_dll_path + " " + std::to_string(r_count) + " "
			+ media_path + " " + input_file_list_for_this_stub[i]);
	}
	// initialize windows.h process variables
	STARTUPINFO start_info; // establishes properties of child process
	GetStartupInfo(&start_info);
	LPSTARTUPINFO process_start_info = &start_info; // set process style
	LPCTSTR app_name = "../Mapper/Debug/Mapper.exe"; // program to run
	std::vector<PROCESS_INFORMATION> process_info_list; // process info list
	std::vector<bool> status_list; // hold creation fail
	// start the processes
	for (int i = 0; i < m_count; i++) {
		PROCESS_INFORMATION tmp_process_info;
		LPPROCESS_INFORMATION procee_retrive_infor = &tmp_process_info;
		LPTSTR  command_line = 
			(char *)argument_ready_mapper_input[i].c_str(); // main's args
		BOOL process_status =
			CreateProcess(app_name, command_line, NULL, NULL, FALSE,
			NULL, NULL, NULL, process_start_info, 
			procee_retrive_infor);
		CloseHandle(tmp_process_info.hThread);  // parent needs no access to child thread
		process_info_list.push_back(tmp_process_info);
		status_list.push_back(process_status);
	}
	// check all mappers' statuses
	int process_count = 0;
	for (auto it = status_list.begin(); it != status_list.end(); ++it) {
		if (!*it) {
			BOOST_LOG_TRIVIAL(error) << "Map process "<<
				process_count<<" failed to create\n";
            std::exit(EXIT_FAILURE);
		}
		process_count++;
	}
	// wait mappers' processes to finish
	for (auto it = process_info_list.begin(); it != process_info_list.end(); ++it) {
		PROCESS_INFORMATION tmp = *it;
		WaitForSingleObject(tmp.hProcess, INFINITE);
		CloseHandle(tmp.hProcess);
	}
	BOOST_LOG_TRIVIAL(info) << "Mapping finished\n";

	// SECTION 2: invoke reducer processes
	// combine arguments for reducer: process_id, reduce_dll_path, 
	//                                number of reducer, output_path, media_path
	std::vector<std::string> argument_ready_reducer_input;
	for (int i = 0; i < r_count;i++) {
		argument_ready_reducer_input.push_back(std::to_string(i) + " "
			+ reduce_dll_path + " " + std::to_string(r_count) + " "
			+ out_path + " " + media_path);
	}
	// initialize windows.h process variable
	app_name = "../Reducer/Debug/Reducer.exe"; // program to run
	process_info_list.clear(); // clear process info list
	status_list.clear(); // clear error vector
	// start reducer processes
	for (int i = 0; i < m_count; i++) {
		PROCESS_INFORMATION tmp_process_info;
		LPPROCESS_INFORMATION procee_retrive_infor = &tmp_process_info;
		LPTSTR  command_line =
			(char *)argument_ready_reducer_input[i].c_str(); // main's args
		BOOL process_status =
			CreateProcess(app_name, command_line, NULL, NULL, FALSE,
				NULL, NULL, NULL, process_start_info,
				procee_retrive_infor);
		CloseHandle(tmp_process_info.hThread);  // parent needs no access to child thread
		process_info_list.push_back(tmp_process_info);
		status_list.push_back(process_status);
	}
	// check all reducers' statuses
	process_count = 0;
	for (auto it = status_list.begin(); it != status_list.end(); ++it) {
		if (!*it) {
			BOOST_LOG_TRIVIAL(error) << "Reducer process " <<
				process_count << " failed to create\n";
            std::exit(EXIT_FAILURE);
		}
		process_count++;
	}
	// wait reducers' processes to finish
	for (auto it = process_info_list.begin(); it != process_info_list.end(); ++it) {
		PROCESS_INFORMATION tmp = *it;
		WaitForSingleObject(tmp.hProcess, INFINITE);
		CloseHandle(tmp.hProcess);
	}
	BOOST_LOG_TRIVIAL(info) << "Work finished\n";
	
	*/
}
