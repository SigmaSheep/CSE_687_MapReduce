#include "pch.h"

#include "gtest/gtest.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Map.cpp"
#include "../MapReduce/FileMgt.h"
#include "../MapReduce/FileMgt.cpp"
#include "../MapReduce/SortClass.h"
#include "../MapReduce/SortClass.cpp"
#include "../MapReduce/Reduce.h"
#include "../MapReduce/Reduce.cpp"
#include "../MapReduce/WorkFlow.h"
#include "../MapReduce/WorkFlow.cpp"

class testallclass : public ::testing::Test
{
public:
	testallclass() {}
	~testallclass() {}

	void SetUp()
	{
		std::ofstream writeinput(inputfileName);
		writeinput << sample;
		writeinput.close();
	};

	void TearDown()	{
		
	};

	std::string sample = "A B, C A.\nA.";
	std::string inputPath = ".\\input";
	std::string medianPath = ".\\median";
	std::string outputPath = ".\\output";
	std::string inputfileName = ".\\input\\ifls.txt";
	std::string medianFile = ".\\median\\intermediate.txt";
	std::string outputName = ".\\output\\finalresult.txt";
};

TEST_F(testallclass, testMap_MapperFunc)
{
	Map mapClass;
	std::ofstream file(medianFile, std::ios::out);
	mapClass.MapperFunc(medianFile, sample, 10);
	mapClass.~Map();

	std::ifstream read_file(medianFile);
	std::string line;
	if (read_file.is_open()) {
		std::getline(read_file, line);
		EXPECT_EQ("a 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("b 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("c 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("a 1", line);
	}
	read_file.close();

}


TEST_F(testallclass, testFileMgt_FileIter)
{
	std::vector<std::string> fileList;
	FileMgt filemgtClass;
	fileList = filemgtClass.FileIter(inputPath);
	int len = fileList[0].length();

	EXPECT_EQ("ifls.txt", fileList[0].substr(len - 8, len));
}

TEST_F(testallclass, testFileMgt_MapDist)
{
	std::vector<std::string> fileList;
	FileMgt filemgtClass;
	fileList = filemgtClass.FileIter(inputPath);

	filemgtClass.MapDist(fileList, medianPath, 10);

	std::ifstream read_file(medianFile);
	std::string line;
	if (read_file.is_open()) {
		std::getline(read_file, line);
		EXPECT_EQ("a 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("b 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("c 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("a 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("a 1", line);
	}
	read_file.close();
}


TEST_F(testallclass, testFileMgt_ReadList)
{
	std::vector<std::string> fileList, sortableTokens;
	FileMgt test;
	fileList = test.FileIter(medianPath);
	sortableTokens = test.ReadList(fileList);

	EXPECT_EQ("a 1", sortableTokens[0]);
	EXPECT_EQ("b 1", sortableTokens[1]);
	EXPECT_EQ("c 1", sortableTokens[2]);
	EXPECT_EQ("a 1", sortableTokens[3]);
	EXPECT_EQ("a 1", sortableTokens[4]);
}


TEST_F(testallclass, testSortClass_sortFunction)
{
	std::vector<std::string> fileList, sortableTokens, sortedTokens;
	FileMgt fclass;
	fileList = fclass.FileIter(medianPath);
	sortableTokens = fclass.ReadList(fileList);

	SortClass test;
	sortedTokens = test.sortfunction(sortableTokens);

	EXPECT_EQ("a 1 1 1", sortedTokens[1]);
	EXPECT_EQ("b 1", sortedTokens[2]);
	EXPECT_EQ("c 1", sortedTokens[3]);
}


TEST_F(testallclass, testReduce_reduceFunction)
{
	std::vector<std::string> fileList, sortableTokens, sortedTokens, result;
	FileMgt fclass;
	fileList = fclass.FileIter(medianPath);
	sortableTokens = fclass.ReadList(fileList);
	SortClass sortClass;
	sortedTokens = sortClass.sortfunction(sortableTokens);

	Reduce	test;
	result = test.reduceFunction(sortedTokens);
	EXPECT_EQ("a 3", result[0]);
	EXPECT_EQ("b 1", result[1]);
	EXPECT_EQ("c 1", result[2]);

}

TEST_F(testallclass, let_FIleMgt_writetxt_write)
{
	std::vector<std::string> fileList, sortableTokens, sortedTokens, result;
	FileMgt fclass;
	fileList = fclass.FileIter(medianPath);
	sortableTokens = fclass.ReadList(fileList);
	SortClass sortClass;
	sortedTokens = sortClass.sortfunction(sortableTokens);
	Reduce	reduceClass;
	result = reduceClass.reduceFunction(sortedTokens);

	std::ofstream file(outputName, std::ios::out);
	fclass.writeTxt(result,outputName);
	
	std::ifstream read_file(outputName);
	std::string line;
	if (read_file.is_open()) {
		std::getline(read_file, line);
		EXPECT_EQ("a 3", line);
		std::getline(read_file, line);
		EXPECT_EQ("b 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("c 1", line);
		std::getline(read_file, line);
	}
	read_file.close();
}


TEST_F(testallclass, testWorkFlow)
{
	WorkFlow workflowClass(inputPath, medianPath, outputPath);
	
	std::ifstream read_file(outputName);
	std::string line;
	if (read_file.is_open()) {
		std::getline(read_file, line);
		EXPECT_EQ("a 3", line);
		std::getline(read_file, line);
		EXPECT_EQ("b 1", line);
		std::getline(read_file, line);
		EXPECT_EQ("c 1", line);
		std::getline(read_file, line);
	}
	read_file.close();
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}