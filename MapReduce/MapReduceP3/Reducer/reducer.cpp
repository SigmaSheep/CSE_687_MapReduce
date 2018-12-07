//12_04_2018 created
#include "../FileMgt/file_mgt.h"
#include "../ReduceInterface/reduce_interface.h"

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
	// recieve parameters: process_id, reduce_dll_path, 
	//  number of reducer, output_path, reduceble_file_list 
	if (argc < 3) {
		BOOST_LOG_TRIVIAL(error) <<
			"Less arguments recieved in mapper process\n";
		std::exit(EXIT_FAILURE);
	}
	int reducer_process_id = boost::lexical_cast<int>(argv[0]);//cast to int
	BOOST_LOG_TRIVIAL(info) << "Reducer process #"
		<< reducer_process_id << " is created\n";
	std::string reduce_dll_path = argv[1];
	int r_count = boost::lexical_cast<int>(argv[2]);//cast to int
	std::string out_path = argv[3];
	std::string reduceble_file = argv[4];

	//load dll
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
	FileMgt file_mgt_instance;
	// create final result file
	std::string result_file_name  =
		file_mgt_instance.createOutputFile(reducer_process_id,
			out_path);
	
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens;
	std::vector<std::string> single_key_and_values;
	std::ifstream infile(reduceble_file); // open reduceble file
	std::string input_line; 
	std::string delimiter = " ";
	if (infile.is_open()) { 
		BOOST_LOG_TRIVIAL(info) <<"Reducer #"<< reducer_process_id 
			<< " is reducing reduceble file: \n" << std::string(52, ' ') 
			<< reduceble_file <<"\n";
		while (std::getline(infile, input_line)) {// read line
			boost::split(single_key_and_values, input_line,
				boost::is_any_of(delimiter), boost::token_compress_on);
			single_key_and_values.pop_back();//last one is space
			sorted_and_grouped_tokens.push_back(single_key_and_values);
			single_key_and_values.clear();
		}
	} else {
	BOOST_LOG_TRIVIAL(error)
			<< "Open below input file failed\n"
			<< std::string(52, ' ')
			<< reduceble_file << "\n";
		std::exit(EXIT_FAILURE);
	}
	infile.close();
	
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
