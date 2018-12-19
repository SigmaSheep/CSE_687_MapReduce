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
           add clear directory
*/
//
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(info/error)
#include <boost/algorithm/string.hpp> // split
#include <fstream>// std::ofstream, std::ifstream
#include <iostream> // std::cout
#include <string> // std::transform(), std::string
#include <utility> // std::pair
#include <vector> // std::vector

class FileMgt {
public:
	FileMgt() {};
	~FileMgt() {};

	static void ClearDirectory(std::string path);
	std::vector<std::string> FileIter(const std::string path_p);
	static void PrintVector(const std::vector<std::string>& input_vector);
	static void PrintPairVector(const std::vector<std::pair<std::string,
		std::string>>& input_vector);
	static void PrintVectorVector(
		const std::vector<std::vector<std::string>>& input_vector);
    static std::vector<std::string> CreateMedianFiles(
        int proc_id, int r_count, const std::string media_path);
	static std::string CreateOutputFile(int reducer_id, const std::string out_path);
	static std::vector<std::pair<std::string, std::string>> ReadMediateFiles(
		int reducer_id, int r_count, const std::string media_path);
	static std::vector<std::string> AllocateInputFiles(
		int count, const std::vector<std::string>& input_file_list);
	// arguments are in following order: 1. input_path, 2. media_path, 3. out_path
	// 4.map_dll_path, 5. reduce_dll_path, 6.m_count, 7.r_count, 8.stub_count
	static std::string BindArguments(const std::string& input_path, 
		const std::string& media_path, const std::string& out_path, 
		const std::string& map_dll_path, const std::string& reduce_dll_path, 
		const int m_count, const int r_count, const int stub_count);
	static std::string ArgumentExtra(const int index, const std::string& arguments);
};
#endif