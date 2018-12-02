#include "work_flow.h"

// as a function pointer passed to map function to exporting data
void exportingMedianFile(
	const std::vector<std::pair<std::string, std::string>> tokenized,
	std::string median_file_name);

// as a function pointer passed to reduce function to exporting data
void exportingOutputFile(
	const std::vector<std::vector<std::string>> input_vector,
	std::string out_file_name);

// WorkFlow handles all working logics
WorkFlow::WorkFlow(const std::string input_path, const std::string media_path,
	const std::string out_path, const std::string map_dll_path,
	const std::string reduce_dll_path) {

	// MapHolder and ReduceHolder holding a map or reduce instance
	typedef MapInterface*(CALLBACK* MapHolder)();
	typedef ReduceInterface*(CALLBACK* ReduceHolder)();

	BOOST_LOG_TRIVIAL(info) << "Map-reduce work flow started\n";
	// loading Dlls
	HMODULE h_mod_map = LoadLibrary(map_dll_path.c_str());
	if (h_mod_map == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load map library failed\n";
		std::exit(EXIT_FAILURE);
	}
	MapHolder mCtor = (MapHolder)GetProcAddress(h_mod_map, "createMapIns");
	if (mCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress map dll failed\n";
		std::exit(EXIT_FAILURE);
	}
	MapInterface* map_pointer = mCtor();

	HMODULE h_mod_reduce = LoadLibrary(reduce_dll_path.c_str());
	if (h_mod_reduce == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load reduce library failed\n";
		std::exit(EXIT_FAILURE);
	}
	ReduceHolder rCtor = (ReduceHolder)GetProcAddress(h_mod_reduce,
		"createReduceIns");
	if (mCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress reduce dll failed\n";
		std::exit(EXIT_FAILURE);
	}
	ReduceInterface* reduce_pointer = rCtor();

	BOOST_LOG_TRIVIAL(info) << "Loading Dll sucussful\n";
	// put input files' paths into vector input_file_list
	FileMgt file_mgt_instance;
	std::vector<std::string> input_file_list =
		file_mgt_instance.fileIter(input_path);
	// median_file_name is median_path/intermedia.txt
	std::string median_file_name =
		file_mgt_instance.createMedianFile(media_path);
	// count current reading input file
	int input_file_counter = 0;
	for (auto it = input_file_list.begin(); it != input_file_list.end(); ++it) {
		BOOST_LOG_TRIVIAL(info) << "Mapping input files number "
			<< input_file_counter << "\n";
		input_file_counter++;

		std::ifstream infile(*it); // open input file
		std::string input_line; // read each line of input files to a string
		if (infile.is_open()) {
			while (std::getline(infile, input_line)) {
				//call MapFunction from Dll
				map_pointer->MapFunction(input_line, &exportingMedianFile,
					median_file_name);
			}
		}
		else {
			BOOST_LOG_TRIVIAL(error) << "Open input files failed\n";
			std::exit(EXIT_FAILURE);
		}
		infile.close();
	}

	BOOST_LOG_TRIVIAL(info) << "Mapping finished\n";
	//put median files' paths to a median_file_list
	std::vector<std::string> median_file_list =
		file_mgt_instance.fileIter(media_path);
	//read median files to sortable_tokens
	std::vector<std::pair<std::string, std::string>> sortable_tokens =
		file_mgt_instance.readList(median_file_list);

	BOOST_LOG_TRIVIAL(info) << "Sorting and grouping started\n";
	//sort sortable_tokens based on key(pair.first)
	//group values with same key
	Sort sort_instance;
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens =
		sort_instance.sortAndGroup(sortable_tokens);
	BOOST_LOG_TRIVIAL(info) << "Sorting and grouping finished\n";
	//output_file_name is out_path/final_result.txt
	std::string output_file_name = file_mgt_instance.createOutputFile(out_path);

	BOOST_LOG_TRIVIAL(info) << " Reducing started\n";
	//call ReduceFunction from Dll
	reduce_pointer->ReduceFunction(sorted_and_grouped_tokens,
		exportingOutputFile, output_file_name);

	FreeLibrary(h_mod_map);
	FreeLibrary(h_mod_reduce);
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
	std::string median_file_name) {

	std::ofstream outfile(median_file_name, std::ios::app);
	if (outfile.is_open()) {
		for (auto it = tokenized.begin(); it != tokenized.end(); ++it)
		{
			std::pair<std::string, std::string> tmp_pair = *it;
			outfile << tmp_pair.first << " " << tmp_pair.second << std::endl;
		}
	}
	else {
		BOOST_LOG_TRIVIAL(error) << "Open median files failed\n";
		std::exit(EXIT_FAILURE);
	}
	outfile.close();
};
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
