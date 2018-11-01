#ifndef REDUCE_H
#define REDUCE_H
/////////////////////////////////////////////////////////////////////
//  Reduce.h -	   reduce function		    					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module reduce sorted token vector to reduced token vector

Public Interface:
=================
reduceFunction(std::vector<std::string> sortedTokens);
Take a sorted token vector like [A 1 1 1] [B 1 1] to a reduced
token vector like [A 3][B 2]

Required files
================
none

Maintenance History:
===============
*/
//

#include <vector> // std::vector
#include <string> // std::string
#include <iostream> // std::cout
#include <boost/range/algorithm/count.hpp> // boost::count

class Reduce
{
public:
	Reduce();
	~Reduce();

	std::vector<std::string> reduceFunction(std::vector<std::string> sortedTokens);
};

#endif