#ifndef REDUCEINTERFACE_H
#define REDUCEINTERFACE_H
/////////////////////////////////////////////////////////////////////
//  ReduceInterface.h -	 Dll interface for reduce				   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module works as interface between framework and reduce dll
Public Interface:
=================
virtual void ReduceFunction(
		const std::vector<std::vector<std::string>> input_vector,
		void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
		const std::string out_file_name) {};
This virtual function could be overload by child class
input: input_vector contains sorted and grouped key and values. First element is
	   key. The reset elements are values.
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
12_06_2018 give exporting back to framework
*/
//
#include <string>
#include <vector>
class ReduceInterface {
public:
	ReduceInterface() {};
	~ReduceInterface() {};
	virtual  std::vector<std::vector<std::string>> ReduceFunction(
		const std::vector<std::string>& key_vector,
		const std::vector<std::vector<std::string>>& value_vector) {
		std::vector<std::vector<std::string>> result;
		return result;
	};
};
#endif
