#ifndef FILEMGT_H
#define FILEMGT_H

#include "boost/filesystem.hpp"
#include <boost/algorithm/string.hpp> // boost::split

#include <fstream>// std::ofstream, std::ifstream
#include <iostream> // std::cout
#include <string> // std::transform(), std::string
#include <utility> // std::pair
#include <vector> // std::vector

class FileMgt
{
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