#include "pch.h"
#include "gtest/gtest.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Map.cpp"
#include "../MapReduce/FileMgt.h"
#include "../MapReduce/FileMgt.cpp"


class additonaltest : public  ::testing::test {
	TEST_F(Maptest, testMapperFunc)
	{

		Map test;

		std::string sample = "A B,C A.";
		std::string medianPath = ".\\intermediate.txt";;

		test.MapperFunc(medianPath, sample, 10);
		std::ifstream read_file(medianPath);
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

	TEST_F(FileMGTtest, testMapdist)
	{

	}
}