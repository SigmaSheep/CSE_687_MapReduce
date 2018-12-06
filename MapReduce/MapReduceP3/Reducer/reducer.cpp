//12_04_2018 created
//12_06_2018 move sort and group here from work flow
#include "../FileMgt/file_mgt.h"
#include "../ReduceInterface/reduce_interface.h"
#include "../Sort/sort.h" // Sort sort_instance.sortAndGroup()

#include <boost/algorithm/string/classification.hpp> // boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // boost::split
#include <boost/lexical_cast.hpp> // boost::lexical_cast<int>()
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(log/error)
#include <iostream> // std::cout for debugging 
#include <windows.h> // HMODULE, GetProcAddress(), FreeLibrary()

// as a function pointer passed to reduce function to exporting data
void exportingOutputFile(
	const std::vector<std::vector<std::string>> input_vector,
	std::string out_file_name);

int main(int argc, char* argv[]) {
	// SECTION 1: recieve parameters:
	// process_id, reduce_dll_path,number of reducer, output_path, media_path 
	if (argc < 5) {
		BOOST_LOG_TRIVIAL(error) <<
			"Less arguments recieved in reducer process\n";
		std::exit(EXIT_FAILURE);
	}
	int reducer_process_id = boost::lexical_cast<int>(argv[0]);//cast to int
	BOOST_LOG_TRIVIAL(info) << "Reducer process #"
		<< reducer_process_id << " is created\n";
	std::string reduce_dll_path = argv[1];
	int r_count = boost::lexical_cast<int>(argv[2]);//cast to int
	std::string out_path = argv[3];
	std::string media_path = argv[4];

	// SECTION 2: sort and group data from median files 
	FileMgt file_mgt_instance;
	std::vector<std::string> reduceble_median_file_list =
		file_mgt_instance.CreateReducebleFiles(r_count, media_path);
	Sort sort_instance;
	std::vector<std::pair<std::string, std::string>> sortable_tokens;
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens;
	//read median files to sortable_tokens
	sortable_tokens = file_mgt_instance.ReadMediateFiles(
		reducer_process_id, r_count, media_path);
	//sort sortable_tokens based on key(pair.first)
	//group values with same key
	sorted_and_grouped_tokens =
		sort_instance.sortAndGroup(sortable_tokens);

	//  SECTION 3: load dll
	typedef ReduceInterface*(CALLBACK* ReduceHolder)();
	HMODULE h_mod_reduce = LoadLibrary(reduce_dll_path.c_str());
	if (h_mod_reduce == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load reduce library failed\n";
		std::exit(EXIT_FAILURE);
	}
	ReduceHolder rCtor = (ReduceHolder)GetProcAddress(h_mod_reduce,
		"createReduceIns");
	if (rCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress reduce dll failed\n";
		std::exit(EXIT_FAILURE);
	}
	ReduceInterface* reduce_pointer = rCtor();

	// SECTION 4: create final result file and call reducer function
	std::string result_file_name  =
		file_mgt_instance.createOutputFile(reducer_process_id,
			out_path);
	// call reduce function
	reduce_pointer->ReduceFunction(sorted_and_grouped_tokens,
		exportingOutputFile, result_file_name);//call MapFunction from Dll
	FreeLibrary(h_mod_reduce);
	BOOST_LOG_TRIVIAL(info) << "Reducer process #"
		<< reducer_process_id << " ended\n";
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////
//void exportingOutputFile(
//	const std::vector<std::vector<std::string>>	input_vector,
//	std::string out_file_name)
// input: input_vector- vector of vector contains key and values produced
//						by reduce function
//		  out_file_name- path to output file
// output: void writing vector of vector into output file
/////////////////////////////////////////////////////////////////////////////////
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
		BOOST_LOG_TRIVIAL(error) << "Open output files failed\n";
		std::exit(EXIT_FAILURE);
	}
	outfile.close();
};
