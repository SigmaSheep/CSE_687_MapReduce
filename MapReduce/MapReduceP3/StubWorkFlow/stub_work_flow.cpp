#include "stub_work_flow.h"

void StubWorkFlow::InvokeMapperProcess() {
	
	// put input files' paths into vector input_file_list
	FileMgt file_mgt_instance;
	std::vector<std::string> input_file_list =
		file_mgt_instance.FileIter(input_path_);
	if (input_file_list.size() < (int)m_count_) {
		BOOST_LOG_TRIVIAL(error) << "Too many mapper processes";
		std::exit(EXIT_FAILURE);
	}
	file_mgt_instance.FileIter(media_path_);//just check if exist
	file_mgt_instance.FileIter(out_path_);//just check if exist
	//file_mgt_instance.ClearDirectory(media_path_);//clear median_path
	//file_mgt_instance.ClearDirectory(out_path_); // clear out_path
	// divide input files based on the map count
	std::vector<std::string> divided_file_list =
		file_mgt_instance.AllocateInputFiles(m_count_,
			std::ref(input_file_list));
	// calculate how many processes are included in this stub
	int first_mapper_id_in_stub = stub_id_ * (m_count_/stub_count_);
	int last_mapper_id_in_stub;
	if (stub_id_ == stub_count_) {
		last_mapper_id_in_stub = m_count_ - 1;
	} else {
		last_mapper_id_in_stub = (stub_id_ + 1)*(m_count_ / stub_count_);
	}

	//combine arguments for mapper: stub_id, number of stubs
	//								process_id, map_dll_path,number of reducer,
	//	                            median_file_path, divided_file_list
	std::vector<std::string> argument_ready_mapper_input;
	for (int i = first_mapper_id_in_stub; i < last_mapper_id_in_stub; i++) {
		argument_ready_mapper_input.push_back(std::to_string(i) + " "
			+ map_dll_path_ + " " + std::to_string(r_count_) + " "
			+ media_path_ + " " + divided_file_list[i]);
	}
	// initialize windows.h process variables
	STARTUPINFO start_info; // establishes properties of child process
	GetStartupInfo(&start_info);
	LPSTARTUPINFO process_start_info = &start_info; // set process style
	LPCTSTR app_name = "../Mapper/Debug/Mapper.exe"; // program to run
	std::vector<PROCESS_INFORMATION> process_info_list; // process info list
	std::vector<bool> status_list; // hold creation fail
	// start the processes
	for (int i = 0; i < (last_mapper_id_in_stub- first_mapper_id_in_stub); i++) {
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
			BOOST_LOG_TRIVIAL(error) << "Map process " <<
				process_count << " failed to create\n";
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
};

void StubWorkFlow::InvokeReducerProcess() {
	std::cout << "start InvokeReducerProcess\n";
	// calculate how many processes are included in this stub
	int first_reducer_id_in_stub = stub_id_ * (r_count_ / stub_count_);
	int last_reducer_id_in_stub;
	if (stub_id_ == stub_count_) {
		last_reducer_id_in_stub = r_count_ - 1;
	} else {
		last_reducer_id_in_stub = (stub_id_ + 1)*(r_count_ / stub_count_);
	}

	// combine arguments for reducer: process_id, reduce_dll_path, 
	//                                number of reducer, output_path, media_path
	std::vector<std::string> argument_ready_reducer_input;
	for (int i = first_reducer_id_in_stub; i < last_reducer_id_in_stub; i++) {
		argument_ready_reducer_input.push_back(std::to_string(i) + " "
			+ reduce_dll_path_ + " " + std::to_string(r_count_) + " "
			+ out_path_ + " " + media_path_);
	}
	// initialize windows.h process variable
	STARTUPINFO start_info; // establishes properties of child process
	GetStartupInfo(&start_info);
	LPSTARTUPINFO process_start_info = &start_info; // set process style
	LPCTSTR app_name = "../Reducer/Debug/Reducer.exe"; // program to run
	std::vector<PROCESS_INFORMATION> process_info_list; // process info list
	std::vector<bool> status_list; // hold creation fail
	// start reducer processes
	for (int i = 0; 
		i < (first_reducer_id_in_stub - last_reducer_id_in_stub); i++) {
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
	int process_count = 0;
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
};
