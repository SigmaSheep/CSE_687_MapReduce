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
*/
//

#include <string>
#include "../WorkFlow/WorkFlow.h"

int main() {
	std::string input_path, media_path, out_path, map_dll_path, 
		reduce_dll_path, map_dll_path_default, reduce_dll_path_default;
	
	std::cout << "type input directory\n";
	std::cin >> input_path;

	std::cout << "type intermediate directory\n";
	std::cin >> media_path;

	std::cout << "type output directory\n";
	std::cin >> out_path;
	
	map_dll_path_default = ".\\MapDll.dll";
	reduce_dll_path_default = ".\\ReduceDll.dll";

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

	WorkFlow(input_path, media_path, out_path, map_dll_path, reduce_dll_path);

	return 0;
}
