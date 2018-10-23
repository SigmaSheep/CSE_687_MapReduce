#include "stdafx.h"
#include "FileMgt.h"
#include <sstream>


FileMgt::FileMgt(std::string inPath_p, std::string mediaPath_p, std::string outPath_p)
{
	inPath = inPath_p;
	mediaPath = mediaPath_p;
	outPath = outPath_p;
}

void FileMgt::MapDist()
{
	std::vector<std::string> FileList = FileIter(inPath);

	int FileCount = 0;
	std::string mediaFileName;
	std::stringstream sstm;

	for (std::vector<std::string>::iterator it = FileList.begin(); it != FileList.end(); ++it)
	{

		sstm << mediaPath << "\\" << FileCount << ".txt";
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
