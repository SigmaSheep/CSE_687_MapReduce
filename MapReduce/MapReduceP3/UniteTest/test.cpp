#include "pch.h"

#include "../FileMgt/file_mgt.h"
#include "../MapInterface/map_interface.h"
#include "../ReduceInterface/reduce_interface.h"
#include "../Sort/sort.h"
#include <fstream>
#include <vector>
#include <string>
#include <tchar.h>
#include <Windows.h>


class testallclass : public ::testing::Test {
public:
	testallclass() {}
	~testallclass() {}

	void SetUp() {
		writeinput(input_file_name);
	};

	void TearDown() {
	};

	void writeinput(std::string inputfileName) {
		std::ofstream outfile(inputfileName);
		outfile << test;
	}

	std::string test = "A B, C A.\nA.";
	std::string input_path = "./input";
	std::string median_path = "./median";
	std::string median_path_mapper = "../UniteTest/median";
	std::string output_path = "./output";
	std::string input_file_name = "./input/ifls.txt";
	std::string input_file_mapper = "../UniteTest/input/ifls.txt";
	std::string median_file = "./median/intermediate.txt";
	std::string output_name = "./output/final_result.txt";
	std::string map_dll = "../Debug/MapDll.dll";
	std::string reduce_dll = "../Debug/ReduceDll.dll";
};
TEST_F(testallclass, testFileMgt_FileIter) {
	std::vector<std::string> file_list;
	FileMgt file_management_class_test;
	file_list = file_management_class_test.FileIter(input_path);
	auto len = file_list[0].length();
	EXPECT_EQ("ifls.txt", file_list[0].substr(len - 8, len));
}

TEST_F(testallclass, testFileMgt_CreateMedianFiles) {
	FileMgt file_management_class_test;
	file_management_class_test.ClearDirectory(median_path);
	std::vector<std::string> test_file_list =
		file_management_class_test.CreateMedianFiles(1,
			1, median_path);
	EXPECT_EQ("./median/intermediate1_0.txt", test_file_list[0]);
}
TEST_F(testallclass, testFileMgt_CreateOutputFile) {
	FileMgt file_management_class_test;
	file_management_class_test.ClearDirectory(output_path);
	std::string output_name = 
		file_management_class_test.CreateOutputFile(1,output_path);
	EXPECT_EQ("./output/final_result1.txt", output_name);
}

TEST_F(testallclass, testMapDll) {
	FileMgt file_management_class_test;
	typedef MapInterface*(CALLBACK* MapHolder_test)();
	HMODULE h_mod_map_test = LoadLibrary((LPCWSTR)map_dll.c_str());
	if (h_mod_map_test == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	MapHolder_test mCtor = (MapHolder_test)GetProcAddress(h_mod_map_test, "CreateMapIns");
	if (mCtor == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	MapInterface* map_pointer = mCtor();
	std::vector<std::pair<std::string, std::string>> result = 
		map_pointer->MapFunction("some_key", test);
	EXPECT_EQ("a", result[0].first);
	EXPECT_EQ("b", result[1].first);
	EXPECT_EQ("c", result[2].first);
	EXPECT_EQ("a", result[3].first);
}

TEST_F(testallclass, testSortClass_sortFunction) {
	std::vector<std::string> file_list;
	std::vector<std::pair<std::string, std::string>> sortable_tokens;
	std::pair<std::string, std::string> tmp_pair;
	tmp_pair.second = "1";
	tmp_pair.first = "c";
	sortable_tokens.push_back(tmp_pair);
	tmp_pair.first = "b";
	sortable_tokens.push_back(tmp_pair);
	tmp_pair.first = "a";
	sortable_tokens.push_back(tmp_pair);
	sortable_tokens.push_back(tmp_pair);

	Sort sort_instance;
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens =
		sort_instance.SortAndGroup(sortable_tokens);

	EXPECT_EQ("a", sorted_and_grouped_tokens[0][0]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[0][1]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[0][2]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[0][3]);
	EXPECT_EQ("b", sorted_and_grouped_tokens[1][0]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[1][1]);
	EXPECT_EQ("c", sorted_and_grouped_tokens[2][0]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[2][1]);
}

TEST_F(testallclass, testReduceDll) {
	FileMgt file_management_class_test;
	typedef ReduceInterface*(CALLBACK* ReduceHolder_test)();
	HMODULE h_mod_reduce_test = LoadLibrary((LPCWSTR)reduce_dll.c_str());
	if (h_mod_reduce_test == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	ReduceHolder_test mCtor = (ReduceHolder_test)GetProcAddress(h_mod_reduce_test, "CreateMapIns");
	if (mCtor == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	ReduceInterface* reduce_pointer = mCtor();

	std::vector<std::string> key_vector;
	std::vector<std::vector<std::string>> value_vector;
	key_vector.push_back("a");
	value_vector[0].push_back("1");
	value_vector[0].push_back("1");
	key_vector.push_back("b");
	value_vector[1].push_back("1");
	key_vector.push_back("c");
	value_vector[2].push_back("1");

	std::vector<std::vector<std::string>> result =
		reduce_pointer->ReduceFunction(key_vector, value_vector);
	EXPECT_EQ("a", result[0][0]);
	EXPECT_EQ("2", result[0][1]);
	EXPECT_EQ("b", result[1][0]);
	EXPECT_EQ("1", result[1][1]);
	EXPECT_EQ("c", result[2][0]);
	EXPECT_EQ("1", result[2][1]);
}

TEST_F(testallclass, testFileMgtPartitionFunction) {
	std::ofstream f1("./input2/f1.txt", std::ios::out);
	std::ofstream f2("./input2/f2.txt", std::ios::out);
	std::ofstream f3("./input2/f3.txt", std::ios::out);
	std::ofstream f4("./input2/f4.txt", std::ios::out);
	std::ofstream f5("./input2/f5.txt", std::ios::out);
	std::ofstream f6("./input2/f6.txt", std::ios::out);
	std::ofstream f7("./input2/f7.txt", std::ios::out);
	f1.close();
	f2.close();
	f3.close();
	f4.close();
	f5.close();
	f6.close();
	f7.close();
	FileMgt file_management_class_test;
	std::vector<std::string> file_list = 
		file_management_class_test.FileIter("./input2");
	std::vector<std::string> partioned_list =
		file_management_class_test.AllocateInputFiles(3,file_list);

	auto len = partioned_list[0].length();
	EXPECT_EQ("\"./input2\\f1.txt\" \"./input2\\f2.txt\" ", partioned_list[0]);
	EXPECT_EQ("\"./input2\\f3.txt\" \"./input2\\f4.txt\" ", partioned_list[1]);
	EXPECT_EQ("\"./input2\\f5.txt\" \"./input2\\f6.txt\" \"./input2\\f7.txt\" ",
		partioned_list[2]);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
