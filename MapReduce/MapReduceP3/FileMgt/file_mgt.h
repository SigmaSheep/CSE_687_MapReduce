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
11_06_2018 check if path exist in fileIter
*/
//

#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(info/error)
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
	std::vector<std::string> createMedianFiles(int proc_id,
		int r_count, const std::string media_path);
	std::string createOutputFile(int reducer_id, const std::string out_path);
	std::vector<std::pair<std::string, std::string>> ReadMediateFiles(
		int reducer_id, int r_count, std::string media_path);
	std::vector<std::string> AllocateInputFiles(
		int count, const std::vector<std::string> input_file_list);
};
#endif