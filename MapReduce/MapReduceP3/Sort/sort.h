#ifndef SORT_H
#define SORT_H
/////////////////////////////////////////////////////////////////////
//  Sort.h -	   sort and group operation   					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module sort and group given keys and values produced by map
Public Interface:
=================
std::vector<std::vector<std::string>> sortAndGroup(
		const std::vector<std::pair<std::string, std::string>> sortableTokens);
input: sortableTokens- vector of pair read from median files
					   pair.first is key. pair.second is value.
return: a vector of vector of string. First element in inside vector is the
		key. Second to the last element are the values corresponding to first
		element key. Key is sorted by ascending order.
Required files
================
none
Maintenance History:
===============
11_16_2018 first release
*/
//
#include <algorithm> // std::sort
#include <iostream> //  std::cout (debug)
#include <string>  // std::string
#include <vector>  // std::vector; std::vector<std::string>::iterator

class Sort {
public:
	Sort() {};
	~Sort() {};
	std::vector<std::vector<std::string>> sortAndGroup(
		const std::vector<std::pair<std::string, std::string>> sortableTokens);
};
#endif