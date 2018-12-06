//Dec 04 2018 first release
#include "../FileMgt/file_mgt.h"
#include "../MapInterface/map_interface.h"

#include <boost/lexical_cast.hpp> // boost::lexical_cast<int>()
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(log/error)
#include <iostream>
#include <windows.h>

// as a function pointer passed to map function to exporting data
void exportingMedianFile(
	const std::vector<std::pair<std::string, std::string>> tokenized,
	std::vector<std::string> median_file_list);

int main(int argc, char * argv[]) {
	// recieve parameters: mapper proc #id, dll_path, number of reducer,
	//					   median_file_path, input_file_paths(multiple)
	if (argc < 3) {
		BOOST_LOG_TRIVIAL(error) << 
			"Less arguments recieved in mapper process\n";
		std::exit(EXIT_FAILURE);
	}
	int mapper_process_id = boost::lexical_cast<int>(argv[0]);//cast to int
	BOOST_LOG_TRIVIAL(info) << "Mapper process #"
		<< mapper_process_id<<" is created\n";
	std::string map_dll_path = argv[1];
	int r_count = boost::lexical_cast<int>(argv[2]);//cast to int
	std::string median_path = argv[3];
	std::vector<std::string> input_file_list;
	for (int i = 4; i < argc; i++) {
		input_file_list.push_back(argv[i]);
	}
	//load dll
	typedef MapInterface*(CALLBACK* MapHolder)();
	HMODULE h_mod_map = LoadLibrary(map_dll_path.c_str());
	if (h_mod_map == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load map library failed\n";
		std::exit(EXIT_FAILURE);
	}
	MapHolder mCtor = (MapHolder)GetProcAddress(h_mod_map, 
		"createMapIns");
	if (mCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress map dll failed\n";
		std::exit(EXIT_FAILURE);
	}
	MapInterface* map_pointer = mCtor();

	FileMgt file_mgt_instance;
	// create median file name list
	std::vector<std::string> median_file_name_list =
		file_mgt_instance.createMedianFile(mapper_process_id,r_count,
			median_path);
	for (auto it = input_file_list.begin();//map each file in loop 
			it != input_file_list.end();++it) {
		std::string input_file = *it;
		int len = input_file.size();
		std::ifstream infile(*it); // open each input file
		std::string input_line; 
		if (infile.is_open()) { 
			BOOST_LOG_TRIVIAL(info) <<"Mapper #"<< mapper_process_id 
				<< " is mapping input file: \n" << std::string(52, ' ') 
				<< *it<<"\n";
			while (std::getline(infile, input_line)) {// read line
				map_pointer->MapFunction(input_line,
					&exportingMedianFile,
					median_file_name_list);//call MapFunction from Dll
			}
		} else {
			BOOST_LOG_TRIVIAL(error)
				<< "Open below input file failed\n"
				<< std::string(52, ' ')
				<< *it << "\n";
			std::exit(EXIT_FAILURE);
		}
		infile.close();
	}
	FreeLibrary(h_mod_map);
	BOOST_LOG_TRIVIAL(info) << "Mapper process #"
		<< mapper_process_id << " ended";
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
// void exportingMedianFile(
//		const std::vector<std::pair<std::string, std::string>> tokenized,
//		std::string median_file_name)
// input: tokenized- vector of pair contains value and key
//		  median_file_name- path to median file
// output: void writing tokenized vector into median file
/////////////////////////////////////////////////////////////////////////////////
void exportingMedianFile(
	const std::vector<std::pair<std::string, std::string>> tokenized,
	std::vector<std::string> median_file_list) {
	size_t r_count = median_file_list.size();
	std::ofstream *outfiles = new std::ofstream[r_count];//allocate heap
	for (int i = 0; i < (int)r_count; i++) { // open median files
		outfiles[i].open(median_file_list[i], std::ios::app);
	}
	// deliver pairs to different median files based on key's hash value
	std::hash<std::string> HashFunction;
	std::pair<std::string, std::string> tmp_pair;
	size_t hash_value;
	for (auto it = tokenized.begin(); it != tokenized.end(); ++it) {
		tmp_pair = *it;
		hash_value = HashFunction(tmp_pair.first) % r_count;
		if (outfiles[hash_value].is_open()) {//key and value seprate by " "
			outfiles[hash_value] << tmp_pair.first << " "
				<< tmp_pair.second << std::endl;
		} else {
			BOOST_LOG_TRIVIAL(error) << "Open median files failed\n";
			std::exit(EXIT_FAILURE);
		}
	}
	for (int i = 0; i < (int)r_count; i++) {//close all files
		outfiles[i].close();
	}
	delete[] outfiles;//delete in heap
};


