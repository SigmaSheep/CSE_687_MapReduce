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
	std::vector<std::string> FileList;
	FileList = FileIter(inPath);

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

using namespace boost::filesystem;
struct recursive_directory_range
{
	typedef recursive_directory_iterator iterator;
	recursive_directory_range(path p) : p_(p) {}

	iterator begin() { return recursive_directory_iterator(p_); }
	iterator end() { return recursive_directory_iterator(); }

	path p_;
};

std::vector<std::string> FileMgt::FileIter(std::string Path_p)
{
	std::vector<std::string> FileList;

	for (auto it : recursive_directory_range(inPath))
	{
		FileList.push_back(it.path().string());
	}
	return FileList;
}