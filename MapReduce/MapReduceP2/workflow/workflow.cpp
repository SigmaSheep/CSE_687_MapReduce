#include "WorkFlow.h"

WorkFlow::WorkFlow(std::string inPath_p, std::string mediaPath_p, std::string outPath_p)
{
	//Buffer size for Map to write
	int MapBufSize = 1000;

	FileMgt Works;

	std::vector<std::string> inputFileList = Works.FileIter(inPath_p);

	//Distribute lines of each input file to Map
	Works.MapDist(inputFileList, mediaPath_p, MapBufSize);

	std::vector<std::string> mediaFileList = Works.FileIter(mediaPath_p);

	//sortableToken contains strings like "word 1"
	std::vector<std::string> sortableTokens = Works.ReadList(mediaFileList);

	//sort media result file
	SortClass SortClass_ins;
	std::vector<std::string> sortedTokens = SortClass_ins.sortfunction(sortableTokens);

	//reduce to final result
	Reduce Reduce_ins;
	std::vector<std::string> final_result = Reduce_ins.reduceFunction(sortedTokens);

	//Works.printvector(final_result);
	std::string final_result_name = outPath_p.append("\\final_result.txt");
	std::ofstream file(final_result_name, std::ios::out);
	Works.writeTxt(final_result, final_result_name);

}