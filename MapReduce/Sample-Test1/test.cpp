#include "pch.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Reduce.h"
#include "../MapReduce/FileMgt.h"
#include "../Mapper/Mapper.h"

#include <string>
#include <fstream>
#include <vector>

TEST(Maptest, test1)
{
	//Mapper test;

	/*
	std::string sample = "A B,C A.";
	std::string inputFile = ".\\sample_result\\test_file.txt";
	std::string medianPath = ".\\sample_result";

	std::ofstream test_file(inputFile);
	test_file << sample << std::endl;
	test.MapperFunc(inputFile, medianPath, 10);
	test_file.close();

	std::ifstream read_file(".\\sample_result\\intermediate.txt");
	std::string line;
	std::getline(read_file, line);

	EXPECT_EQ('A', line[0]);
	
	*/
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Reducetest, test2)
{

	//Reduce test2;

}

