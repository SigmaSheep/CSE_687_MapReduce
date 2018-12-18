#ifndef WORKFLOW_H
#define WORKFLOW_H
/////////////////////////////////////////////////////////////////////
//  WorkFlow.h -	   work flow operation    					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module manage the workflow operation
Public Interface:
=================
WorkFlow(const std::string input_path, const std::string media_path,
		const std::string out_path, const std::string map_dll_path,
		const std::string reduce_dll_path);
Manage the workflow operation
Required files
================
FileMgt.h
Sort.h
MapInterface.h
ReduceInterface.h
Maintenance History:
===============
11_16_2018 first release
12_06_2018 check if all paths exist
*/
//

#include "../MapInterface/map_interface.h"
#include "../Sort/sort.h"
#include "../ReduceInterface/reduce_interface.h"

#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(info)
#include <iostream> // std::cin
#include <string> // std::string
#include <tchar.h> // TCHAR _T
#include <vector> // std::vector
#include <Windows.h> // STARTUPINFO, GetStartupInfo(), LPSTARTUPINFO, 
//LPCTSTR, PROCESS_INFORMATION, LPPROCESS_INFORMATION, CreateProcess()
//CloseHandle(), WaitForSingleObject()

class WorkFlow {
public:
	WorkFlow() {};
	~WorkFlow() {};
	WorkFlow(const std::string input_path, const std::string media_path,
		const std::string out_path, const std::string map_dll_path,
		const std::string reduce_dll_path, int m_count, int r_count,
		const int stub_count, const int stub_id);
};
#endif
