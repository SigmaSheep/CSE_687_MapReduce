#include "stdafx.h"
#include "FileMgt.h"




void FileMgt::MapDist(std::vector<std::string> inputFileList, std::string mediaPath_p, int MapBufSize)
{
	std::vector<std::string> FileList = inputFileList;

	std::string mediaFileName = mediaPath_p.append("\\intermediate.txt");

	std::ofstream file(mediaFileName, std::ios::out);
 
	for (std::vector<std::string>::iterator it = FileList.begin(); it != FileList.end(); ++it)
	{

		// read and send to Map
		std::ifstream infile(*it);
		std::string line;

		// initial a map object
		Map mapStream;

		if (infile.is_open())  
		{
			while (std::getline(infile, line))
			{
				std::transform(line.begin(), line.end(), line.begin(), ::tolower); //transfoer to lowercase
				mapStream.MapperFunc(mediaFileName, line.c_str());
			}
		}
		else
		{
			std::cout << "file is not open" << std::endl;
		}

		infile.close();

	}
}


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
			//std::cout << *it << std::endl;
		}
	}
	else
	{
		std::cout << "file_error" << std::endl;
	}

	outfile.close();

}