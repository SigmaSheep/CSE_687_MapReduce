
#include "../FileMgt/file_mgt.h"
#include "../MapInterface/map_interface.h"
#include "../Sort/sort.h"
#include "../ReduceInterface/reduce_interface.h"

#include <boost/log/trivial.hpp>
#include <iostream> // std::cin
#include <string> // std::string
#include <tchar.h> // TCHAR _T
#include <vector> // std::vector
#include <Windows.h> // STARTUPINFO, GetStartupInfo(), LPSTARTUPINFO, 
//LPCTSTR, PROCESS_INFORMATION, LPPROCESS_INFORMATION, CreateProcess()
//CloseHandle(), WaitForSingleObject()

class StubWorkFlow {
public:
	StubWorkFlow(const std::string input_path, const std::string media_path,
		const std::string out_path, const std::string map_dll_path,
		const std::string reduce_dll_path, const int m_count, 
		const int r_count, const int stub_count, const int stub_id)
		:input_path_(input_path), media_path_(media_path),
		out_path_(out_path), map_dll_path_(map_dll_path),
		reduce_dll_path_(reduce_dll_path), m_count_(m_count),
		r_count_(r_count), stub_count_(stub_count), stub_id_(stub_id) {};
	~StubWorkFlow() {};
	void InvokeMapperProcess();
private:
	std::string input_path_;
	std::string media_path_;
	std::string out_path_;
	std::string map_dll_path_;
	std::string reduce_dll_path_;
	int r_count_;
	int m_count_;
	int stub_count_;
	int stub_id_;
};

