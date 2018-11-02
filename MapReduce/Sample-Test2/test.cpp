#include "pch.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Map.cpp"


TEST(TestCaseName, TestName) {
	Map test;

	std::string sample = "A B,C A.";
	std::string inputFile = ".\\test_file.txt";
	std::string medianPath = ".";

	std::ofstream test_file(inputFile);
	test_file << sample << std::endl;
	test_file.close();

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}