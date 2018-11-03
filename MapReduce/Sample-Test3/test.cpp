#include "pch.h"


#include "gtest/gtest.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Map.cpp"
//#include "../MapReduce/FileMgt.h"
//#include "../MapReduce/FileMgt.cpp"
#include "../MapReduce/SortClass.h"
#include "../MapReduce/SortClass.cpp"
#include "../MapReduce/Reduce.h"
#include "../MapReduce/Reduce.cpp"
//#include "../MapReduce/WorkFlow.h"

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

	void TearDown()
	{
	};

	std::string inputfileName = ".\\ifls.txt";
	std::string sample = "A B,C A.";
	std::string medianFile = ".\\intermediate.txt";


};

TEST_F(testallclass, LetMapWrite)
{
	Map test;
	std::ofstream file(medianFile, std::ios::out);
	test.MapperFunc(medianFile, sample, 10);

}

TEST_F(testallclass, testMapResult)
{
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


TEST_F(testallclass, testSortFunction)
{
	std::string tmp = "a 1";
	std::vector<std::string> vectmp;
	vectmp.push_back(tmp);
	tmp = "b 1";
	vectmp.push_back(tmp);
	tmp = "c 1";
	vectmp.push_back(tmp);
	tmp = "a 1";
	vectmp.push_back(tmp);

	SortClass test;
	vectmp = test.sortfunction(vectmp);

	EXPECT_EQ("a 1 1", vectmp[1]);
	EXPECT_EQ("b 1", vectmp[2]);
	EXPECT_EQ("c 1", vectmp[3]);
}

TEST_F(testallclass, testReduceFunction)
{
	std::string tmp = "";
	std::vector<std::string> vectmp;
	vectmp.push_back(tmp);
	tmp = "b 1 1 1";
	vectmp.push_back(tmp);
	tmp = "c 1 1 1 1";
	vectmp.push_back(tmp);
	tmp = "d 1 1 1 1 1";
	vectmp.push_back(tmp);

	Reduce	test;
	vectmp = test.reduceFunction(vectmp);
	EXPECT_EQ("b 3", vectmp[0]);
	EXPECT_EQ("c 4", vectmp[1]);
	EXPECT_EQ("d 5", vectmp[2]);

}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}