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
Public Interface:
=================
virtual void MapFunction(const std::string line,
		void(*exporting)(
			std::vector<std::pair<std::string, std::string>>,std::string),
		std::string median_file_name) {};
This virtual function could be overload by child class
input: first argument is a single line of string read from input file
	   Second argument is a function pointer to exporting data. Don't change this
	   argument.
	   Thrid argument is out put file path.
How to use: Use the function passed by function pointer to exporting data
Required files
================
none
Maintenance History:
===============
11_16_2018 first release
*/
//
#include <string>
#include <vector>
#define Map_DLL __declspec(dllexport)
class MapInterface {
public:
	MapInterface() {};
	~MapInterface() {};
	virtual void MapFunction(const std::string line,
		void(*exporting)(
			std::vector<std::pair<std::string, std::string>>, std::string),
		std::string median_file_name) {};
};
#endif