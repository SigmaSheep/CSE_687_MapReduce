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

	void MapDist(std::vector<std::string> inputFileList, std::string mediaPath_p, int MapBufSize);

	std::vector<std::string> FileIter(std::string Path_p);

	std::vector<std::string> ReadList(std::vector<std::string> FileList);

	void printvector(std::vector<std::string> inputVector);

	void writeTxt(std::vector<std::string> inputVector, std::string FileName);

};


#endif