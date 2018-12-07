//12_04_2018 created
//12_06_2018 move sort and group here from work flow
//           add multi-threads
#include "../FileMgt/file_mgt.h"
#include "../ReduceInterface/reduce_interface.h"
#include "../Sort/sort.h" // Sort sort_instance.sortAndGroup()

#include <boost/algorithm/string/classification.hpp> // boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // boost::split
#include <boost/lexical_cast.hpp> // boost::lexical_cast<int>()
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL(log/error)
#include <iostream> // std::cout for debugging 
#include <mutex> // std::mutex
#include <thread>
#include <windows.h> // HMODULE, GetProcAddress(), FreeLibrary()

// as a globle function to export data
void ExportingOutputFile(
	const std::vector<std::vector<std::string>> input_vector,
	std::string out_file_name);

// thread function for multi-thread reducing
void ReduceThreadFunc(ReduceInterface* reduce_pointer,
	std::vector<std::vector<std::string>>::const_iterator begin_positon,
	std::vector<std::vector<std::string>>::const_iterator end_position,
	std::string result_file_name) {
	static std::mutex mtx;//lock
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens(
		begin_positon, end_position);
	std::vector<std::vector<std::string>> final_result = //call from Dll
		reduce_pointer->ReduceFunction(sorted_and_grouped_tokens);
	mtx.lock();
	ExportingOutputFile(final_result, result_file_name);
	mtx.unlock();
};

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
	//read median files to sortable_tokens
	 std::vector<std::pair<std::string, std::string>> sortable_tokens =
		 file_mgt_instance.ReadMediateFiles(reducer_process_id, r_count, media_path);
	 Sort sort_instance;
	//sort sortable_tokens based on key(pair.first)
	//group values with same key
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens 
		= sort_instance.SortAndGroup(sortable_tokens);

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

	// SECTION 4: create final result file and invoke threads
	//            to call reducer function
	std::string result_file_name  =
		file_mgt_instance.CreateOutputFile(reducer_process_id,
			out_path);

	// start 2 threads
	int reduceble_vector_size= sorted_and_grouped_tokens.size();
	std::vector<std::vector<std::string>>::const_iterator begin_position, end_position;
	begin_position = sorted_and_grouped_tokens.begin();
	end_position = begin_position + reduceble_vector_size / 2;
	std::thread t1(ReduceThreadFunc, reduce_pointer,
		begin_position, end_position, result_file_name);
	begin_position = end_position;
	end_position = sorted_and_grouped_tokens.end();
	std::thread t2(ReduceThreadFunc, reduce_pointer,
		begin_position, end_position, result_file_name);
	t1.join();
	t2.join();

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
void ExportingOutputFile(
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
	} else {
		BOOST_LOG_TRIVIAL(error) << "Open output files failed\n";
		std::exit(EXIT_FAILURE);
	}
	outfile.close();
};
