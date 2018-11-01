#pragma once
#include <vector>
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
This module will take intermediate files produced by the Sort class and
then create one output file that contains a count or each word contained
in the input files

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

class Reduce
{
public:
	Reduce();
	~Reduce();

	std::vector<std::string> reduceFunction(std::vector<std::string> sortedTokens);
};

