#ifndef SORTCLASS_H
#define SORTCLASS_H
/////////////////////////////////////////////////////////////////////
//  SortClass.h -	   sort function	    					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module sort a token vector
Public Interface:
=================
sortfunction(std::vector<std::string> inputString);
sortfunction takes a inputString like "A 1","B 1","A 1" to a sorted
token vector like "A 1 1","B 1"
Required files
================
none
Maintenance History:
===============
10/31/2018 first release
*/
//

#include <vector>  // std::vector; std::vector<std::string>::iterator
#include <string>  // std::string
#include <algorithm> // std::sort
#include <iostream> //  std::cout (debug)


class SortClass
{
public:
	SortClass();
	~SortClass();
	std::vector<std::string> sortfunction(std::vector<std::string> inputString);

};

#endif