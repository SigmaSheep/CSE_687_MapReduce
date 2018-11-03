#include "pch.h"
#include "gtest/gtest.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Map.cpp"
//#include "boost/filesystem.hpp"
//#include "../MapReduce/FileMgt.h"
//#include "../MapReduce/FileMgt.cpp"
#include "../MapReduce/SortClass.h"
#include "../MapReduce/SortClass.cpp"

class testallclass : public ::testing::Test 
{
public:
	testallclass() {}
	~testallclass() {}

	void SetUp() 
	{
		std::string sample = "A, B.\n C, A.";
		std::string inputPath = ".\\input";
		std::string inputfileName = ".\\input\\ifls.txt";

		std::ofstream writeinput(inputfileName);
		writeinput << sample;
		writeinput.close();

		std::string medianFile = ".\\intermediate.txt";
		std::string outPath = ".\\out";

	};
		
	void TearDown()
	{

	};

	std::string sample = "A B,C A.";
	std::string inputfileName;
	std::string medianFile = ".\\intermediate.txt";


};

TEST_F(testallclass, testMapperFunc)
{
	SetUp();
	std::cout << medianFile;
	Map test;
	test.MapperFunc(medianFile, sample, 10);

	std::ifstream read_file(medianFile);
	std::string line;
	std::getline(read_file, line);
	EXPECT_EQ("a 1", line);
	std::getline(read_file, line);
	EXPECT_EQ("b 1", line);
	std::getline(read_file, line);
	EXPECT_EQ("c 1", line);
	std::getline(read_file, line);
	EXPECT_EQ("a 1", line);
	read_file.close();
}


TEST_F(testallclass, testSortFunction)
{
	SortClass test;
	

}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}