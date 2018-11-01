#pragma once

#include <vector>
#include <string>

/////////////////////////////////////////////////////////////////////
//  Reduce.h -	   Reduce Mapped results to one file    		   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
//  Author:        Xin Liu, Tess Thoresen Syracuse University	   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module takes the intermediate files produced by Map and creates a 
sorted vector of the words in all the intermediate files

Public Interface:
=================
n/a

Required files
================
none

Maintenance History:
===============
10/28/2018 first release
*/
//
class SortClass
{
public:
	SortClass();
	~SortClass();
	std::vector<std::string> sortfunction(std::vector<std::string> inputString);

};

