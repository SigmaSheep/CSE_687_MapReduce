#ifndef FILEMGT_H
#define FILEMGT_H
/////////////////////////////////////////////////////////////////////
//  FileMgt.h -	 file management class						   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module works as handler for file operation for map reduce project
Required files
================
none
Maintenance History:
===============
11_16_2018 first release
*/
//

#include "boost/algorithm/string.hpp"
//#include "boost/algorithm/string.hpp" // boost::split
#include "boost/filesystem.hpp"

#include <fstream>// std::ofstream, std::ifstream
#include <iostream> // std::cout
#include <string> // std::transform(), std::string
#include <utility> // std::pair
#include <vector> // std::vector

class FileMgt {
public:
	FileMgt() {};
	~FileMgt() {};

	std::vector<std::string> fileIter(const std::string path_p);
	void printvector(const std::vector<std::string> input_vector);
	void printPairVector(const std::vector<std::pair<std::string,
		std::string>> input_vector);
	void printVectorVector(
		const std::vector<std::vector<std::string>> input_vector);
	std::string createMedianFile(const std::string media_path);
	std::string createOutputFile(const std::string out_path);
	std::vector<std::pair<std::string, std::string>> readList(
		const std::vector<std::string> meidan_file_list);
};
#endif