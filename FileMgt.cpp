//FileMgmt.cpp, manages the sstream and opening, reading, iterating, and writing to files
#include "stdafx.h"
#include "FileMgt.h"
#include <sstream>
#include <fstream>



void FileMgt::MapDist(std::vector<std::string> inputFileList, std::string mediaPath_p, int MapBufSize)
{
	std::vector<std::string> FileList = inputFileList;

	int FileCount = 0;
	std::string mediaFileName;
	std::stringstream sstm;

	for (std::vector<std::string>::iterator it = FileList.begin(); it != FileList.end(); ++it)
	{

		sstm << mediaPath_p << "\\" << FileCount << ".txt";
		mediaFileName = sstm.str();
		sstm.str(std::string());
		
		// read and send to Map
		std::ifstream infile(*it);
		std::string line;

		// initial a map object
		Map mapStream;

		if (infile.is_open())  
		{
			while (std::getline(infile, line))
			{
				mapStream.MapperFunc(mediaFileName, line.c_str());
			}
		}
		else
		{
			std::cout << "file is not open" << std::endl;
		}

		infile.close();

		FileCount++;
	}
}

//iterates through a file line by line
std::vector<std::string> FileMgt::FileIter(std::string Path_p)
{
	std::vector<std::string> FileList;

	namespace fs = boost::filesystem;

	typedef boost::filesystem::recursive_directory_iterator iterator;
	fs::path p(Path_p);
	fs::recursive_directory_iterator end = fs::recursive_directory_iterator();
	fs::recursive_directory_iterator begin = fs::recursive_directory_iterator(p);

	for (fs::recursive_directory_iterator it = begin;begin!=end;it++)
	{
		FileList.push_back(it->path().string());
	}

	return FileList;
}

//reads an input file
std::vector<std::string> FileMgt::ReadList(std::vector<std::string> FileList)
{	
	std::vector<std::string> Result;

	for (std::vector<std::string>::iterator it = FileList.begin(); it != FileList.end(); ++it)
	{
		// read and send to Map
		std::ifstream infile(*it);
		std::string line;

		if (infile.is_open())
		{
			while (std::getline(infile, line))
			{
				Result.push_back(line);
			}
		}
		else
		{
			std::cout << "file is not open" << std::endl;
		}

		infile.close();

	}

	return Result;
}

//iterates through a vector and prints it
void FileMgt::printvector(std::vector<std::string> inputVector)
{
	for (std::vector<std::string>::iterator it = inputVector.begin(); it != inputVector.end(); ++it)
	{
		std::cout << *it << std::endl;

	}

}


//write vectors to txt file
void FileMgt::writeTxt(std::vector<std::string> inputVector, std::string FileName)
{
	std::ofstream outfile(FileName, std::ios::app);

	if (outfile.is_open()) {
		for (std::vector<std::string>::iterator it = inputVector.begin(); it != inputVector.end(); ++it)
		{
			outfile << *it << std::endl;
			std::cout << *it << std::endl;
		}

	}
	else
	{
		std::cout << "file_error" << std::endl;
	}

	outfile.close();

}