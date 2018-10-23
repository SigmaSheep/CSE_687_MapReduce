#include "stdafx.h"
#include "WorkFlow.h"

WorkFlow::WorkFlow(std::string inPath_p, std::string mediaPath_p, std::string outPath_p)
{
	FileMgt Works(inPath_p, mediaPath_p, outPath_p);
	Works.MapDist();

	std::vector<std::string> mediaFileList = Works.FileIter(mediaPath_p);
	
	//sortableToken contains strings like "word 1" for every word
	std::vector<std::string> sortableTokens = Works.ReadList(mediaFileList);


}
