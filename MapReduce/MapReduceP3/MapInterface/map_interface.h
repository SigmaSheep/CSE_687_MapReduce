#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H
/////////////////////////////////////////////////////////////////////
//  MapInterface.h -	 Dll interface for map					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module works as interface between framework and map dll
Maintenance History:
===============
11_16_2018 first release
11_06_2018 give exporting back to framework
*/
//
#include <string>
#include <vector>
class MapInterface {
public:
	MapInterface() {};
	~MapInterface() {};
	// Map function
	virtual std::vector<std::pair<std::string, std::string>> MapFunction(
		const std::string key, const std::string& value) {
		std::vector<std::pair<std::string, std::string>> result;
		return result;
	};
};
#endif
