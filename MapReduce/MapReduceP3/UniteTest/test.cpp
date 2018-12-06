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


void exportingMedianFile(
	const std::vector<std::pair<std::string, std::string>> tokenized,
	std::string median_file_name);

void exportingOutputFile(
	const std::vector<std::vector<std::string>> input_vector,
	std::string out_file_name);

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
	std::string input_path = ".\\input";
	std::string median_path = ".\\median";
	std::string output_path = ".\\output";
	std::string input_file_name = ".\\input\\ifls.txt";
	std::string median_file = ".\\median\\intermediate.txt";
	std::string output_name = ".\\output\\final_result.txt";
};

TEST_F(testallclass, testMapDll) {
	FileMgt file_management_class_test;
	file_management_class_test.createMedianFile(median_path);

	typedef MapInterface*(CALLBACK* MapHolder_test)();
	TCHAR map_dll_path_test[] = _T("./MapDll.dll");
	HMODULE h_mod_map_test = LoadLibrary(map_dll_path_test);
	if (h_mod_map_test == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	MapHolder_test mCtor = (MapHolder_test)GetProcAddress(h_mod_map_test, "createMapIns");
	if (mCtor == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	MapInterface* map_pointer = mCtor();
	map_pointer->MapFunction(test, &exportingMedianFile, median_file);
	std::ifstream read_file(median_file);
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

TEST_F(testallclass, testFileMgt_FileIter) {
	std::vector<std::string> file_list;
	FileMgt file_management_class_test;
	file_list = file_management_class_test.fileIter(input_path);
	auto len = file_list[0].length();
	EXPECT_EQ("ifls.txt", file_list[0].substr(len - 8, len));
}

TEST_F(testallclass, testFileMgt_ReadList) {
	std::vector<std::string> file_list;
	std::vector<std::pair<std::string, std::string>> sortable_tokens;
	FileMgt file_management_class;
	file_list = file_management_class.fileIter(median_path);
	sortable_tokens = file_management_class.readList(file_list);

	EXPECT_EQ("a", sortable_tokens[0].first);
	EXPECT_EQ("b", sortable_tokens[1].first);
	EXPECT_EQ("c", sortable_tokens[2].first);
	EXPECT_EQ("a", sortable_tokens[3].first);
}


TEST_F(testallclass, testSortClass_sortFunction) {
	std::vector<std::string> file_list;
	std::vector<std::pair<std::string, std::string>> sortable_tokens;
	FileMgt file_management_class;
	file_list = file_management_class.fileIter(median_path);
	sortable_tokens = file_management_class.readList(file_list);

	Sort sort_instance;
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens =
		sort_instance.sortAndGroup(sortable_tokens);

	EXPECT_EQ("a", sorted_and_grouped_tokens[0][0]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[0][1]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[0][2]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[0][3]);
	EXPECT_EQ("b", sorted_and_grouped_tokens[1][0]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[1][1]);
	EXPECT_EQ("c", sorted_and_grouped_tokens[2][0]);
	EXPECT_EQ("1", sorted_and_grouped_tokens[2][1]);
}

TEST_F(testallclass, testReduce_reduceFunction) {

	FileMgt file_management_class;
	file_management_class.createOutputFile(output_path);

	typedef ReduceInterface*(CALLBACK* ReduceHolder)();
	TCHAR re_dll_path[] = _T("./ReduceDll.dll");
	HMODULE h_mod_reduce = LoadLibrary(re_dll_path);
	if (h_mod_reduce == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	ReduceHolder rCtor = (ReduceHolder)GetProcAddress(h_mod_reduce, "createReduceIns");
	if (rCtor == nullptr) {
		std::exit(EXIT_FAILURE);
	}
	ReduceInterface* reduce_pointer = rCtor();

	std::vector<std::string> file_list;
	std::vector<std::pair<std::string, std::string>> sortable_tokens;
	file_list = file_management_class.fileIter(median_path);
	sortable_tokens = file_management_class.readList(file_list);
	Sort sort_instance;
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens =
		sort_instance.sortAndGroup(sortable_tokens);

	reduce_pointer->ReduceFunction(sorted_and_grouped_tokens, &exportingOutputFile, output_name);

	std::ifstream read_out_file(output_name);
	std::string out_line;
	if (read_out_file.is_open()) {
		std::getline(read_out_file, out_line);
		EXPECT_EQ("a 3 ", out_line);
		std::getline(read_out_file, out_line);
		EXPECT_EQ("b 1 ", out_line);
		std::getline(read_out_file, out_line);
		EXPECT_EQ("c 1 ", out_line);
	}
	read_out_file.close();
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
		file_management_class_test.fileIter("./input2");
	std::vector<std::string> partioned_list =
		file_management_class_test.AllocateInputFiles(3,file_list);

	auto len = partioned_list[0].length();
	EXPECT_EQ("./input2\\f1.txt ./input2\\f2.txt ", partioned_list[0]);
	EXPECT_EQ("./input2\\f3.txt ./input2\\f4.txt ", partioned_list[1]);
	EXPECT_EQ("./input2\\f5.txt ./input2\\f6.txt ./input2\\f7.txt ", partioned_list[2]);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

void exportingMedianFile(
	const std::vector<std::pair<std::string, std::string>> tokenized,
	std::string median_file_name) {

	std::ofstream outfile(median_file_name, std::ios::app);
	if (outfile.is_open()) {
		for (auto it = tokenized.begin(); it != tokenized.end(); ++it) {
			std::pair<std::string, std::string> tmp_pair = *it;
			outfile << tmp_pair.first << " " << tmp_pair.second << std::endl;
		}
	}
	else {
		std::exit(EXIT_FAILURE);
	}
	outfile.close();
};

void exportingOutputFile(
	const std::vector<std::vector<std::string>> input_vector,
	std::string out_file_name) {

	std::ofstream outfile(out_file_name, std::ios::app);
	if (outfile.is_open()) {
		for (auto it = input_vector.begin(); it != input_vector.end(); ++it) {
			std::vector<std::string> inside_vector = *it;
			for (auto it = inside_vector.begin(); it !=
				inside_vector.end(); ++it) {
				outfile << *it << " ";
			}
			outfile << std::endl;
		}
	}
	else {
		std::exit(EXIT_FAILURE);
	}
	outfile.close();
};