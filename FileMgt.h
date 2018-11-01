#pragma once
#ifndef FILEMGT_H
#define FILEMGT_H
////////////////////////////////////////////////////////////////////
//  Reduce.h -	   Reduce Mapped results to one file    		   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
//  Author:        Xin Liu     Syracuse University	               //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module will managing opening, iterating through, reading, writing, and printing files.
It also will read and send an object to the Map class.

Public Interface:
=================
reduceFunction(std::vector<std::string> sortedTokens);
It takes vector containing strings
*str is the c-type string input.

Required files
================
none

Maintenance History:
===============
10/28/2018 first release

*/

#include "boost/filesystem.hpp"
#include <string>
#include <vector>
#include "Map.h"

class FileMgt
{
public:
	FileMgt() {};
	~FileMgt() {};

	void MapDist(std::vector<std::string> inputFileList, std::string mediaPath_p, int MapBufSize);

	std::vector<std::string> FileIter(std::string Path_p);

	std::vector<std::string> ReadList(std::vector<std::string> FileList);

	void printvector(std::vector<std::string> inputVector);

	void writeTxt(std::vector<std::string> inputVector, std::string FileName);

};


#endif