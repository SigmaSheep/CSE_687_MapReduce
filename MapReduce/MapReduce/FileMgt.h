#pragma once
#ifndef FILEMGT_H
#define FILEMGT_H


#include "boost/filesystem.hpp"
#include <string>
#include <vector>
#include "Map.h"

class FileMgt
{
public:
	FileMgt() {};
	~FileMgt() {};

	FileMgt(std::string inPath_p, std::string mediaPath_p, std::string outPath_p);

	void MapDist();
	std::vector<std::string> FileIter(std::string Path_p);

	std::vector<std::string> ReadList(std::vector<std::string> FileList);
private:


	std::string	inPath;
	std::string mediaPath;
	std::string outPath;

};


#endif