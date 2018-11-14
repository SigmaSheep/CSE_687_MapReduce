#ifndef FILEMGT_H
#define FILEMGT_H
/////////////////////////////////////////////////////////////////////
//  FileMgt.h -	   file management class     					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module handles file operations including txt distribution to map function, file iteration in a directory,
read a list of files, write a vector of string to a txt file
Public Interface:
=================
MapDist(std::vector<std::string> inputFileList, std::string mediaPath_p, int MapBufSize);
Distribute a list of files to map function. MapDist will read each file in the inputFileList,and extract lines
and feed line by line to map function.
inputFileList is list of file paths, mediaPath_p is path to output median file,
MapBufSize is the buffer size used in map function
FileIter(std::string Path_p);
Iterate files in a directory. Return a vector of string contains paths of files in given directory
ReadList(std::vector<std::string> FileList);
Read a list of median files and return a vector contains tokens like "tmp1 1","tmp2 1","tmp3 1"
printvector(std::vector<std::string> inputVector);
Print out a vector of string for debug purples
writeTxt(std::vector<std::string> inputVector, std::string FileName);
Write given vector to a txt file. FileName is the path of the txt file.
Required files
================
Map.h
Map.cpp
Maintenance History:
===============
10/31/2018 first release
*/
//

#include "boost/filesystem.hpp"

#include "../map/map.h"
#include "../map/map.cpp"

#include <string> // std::transform(), std::string
#include <vector> // std::vector
#include <fstream>// std::ofstream, std::ifstream

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