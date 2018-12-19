
/////////////////////////////////////////////////////////////////////
//  Execute.cpp -	 executable program							   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module works as main function in project and handle cin of paths
Required files
================
WorkFlow.h
Maintenance History:
===============
11_16_2018 first release
12_02_2018 delete package config Chnage file name to lower case
*/
//

#include <iostream>
#include <string>
#include "../WorkFlow/work_flow.h"

int main() {
	int r_count, m_count;

	std::string input_path, media_path, out_path, map_dll_path,
		reduce_dll_path, map_dll_path_default, reduce_dll_path_default;
	/*
	std::cout << "type number of mapper processes\n";
	std::cin >> m_count;

	std::cout << "type number of reducer processes\n";
	std::cin >> r_count;

	std::cout << "type input directory\n";
	std::cin >> input_path;

	std::cout << "type intermediate directory\n";
	std::cin >> media_path;
	
	std::cout << "type output directory\n";
	std::cin >> out_path;

	map_dll_path_default = "../Debug/MapDll.dll";
	reduce_dll_path_default = "../Debug/ReduceDll.dll";

	std::cout << "enter d to use default path for map dll\n";
	std::cin >> map_dll_path;
	if (map_dll_path == "d") {
		map_dll_path = map_dll_path_default;
	}

	std::cout << "enter d to use default path for reduce dll\n";
	std::cin >> reduce_dll_path;
	if (reduce_dll_path == "d") {
		reduce_dll_path = reduce_dll_path_default;
	}
	*/
	input_path = "C:/Users/Xin/Desktop/test/shaktest";
	media_path = "C:/Users/Xin/Desktop/test/median";
	out_path = "C:/Users/Xin/Desktop/test/output";
	map_dll_path = "../Debug/MapDll.dll";
	reduce_dll_path = "../Debug/ReduceDll.dll";
	m_count = 4;
	r_count = 4;

	int stub_count = 2;
	std::vector<std::string> ip_list;
	std::vector<std::string> port_list;
	ip_list.push_back("localhost");
	ip_list.push_back("localhost");
	port_list.push_back("8080");
	port_list.push_back("6060");

	WorkFlow work_flow(input_path, media_path, out_path, map_dll_path,
		reduce_dll_path, m_count, r_count,
		stub_count, ip_list, port_list);

	std::cin.ignore();
	std::cin.get();
	return 0;
}
