#include "WorkFlow.h"

void exportingMedianFile(
	const std::vector<std::pair<std::string,std::string>> tokenized,
	std::string median_file_name);
void exportingOutputFile(
	const std::vector<std::vector<std::string>> input_vector,
	std::string out_file_name);

typedef MapInterface*(CALLBACK* MapHolder)();
typedef ReduceInterface*(CALLBACK* ReduceHolder)();

WorkFlow::WorkFlow(const std::string input_path, const std::string media_path,
	const std::string out_path, const std::string map_dll_path,
	const std::string reduce_dll_path)
{
	BOOST_LOG_TRIVIAL(info) << "Map-reduce work flow started\n";
	HMODULE h_mod_map = LoadLibrary(map_dll_path.c_str());
	if (h_mod_map == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load map library failed\n";
	}
	MapHolder mCtor = (MapHolder)GetProcAddress(h_mod_map, "createMapIns");
	if (mCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress map dll failed\n";
	}
	MapInterface* map_pointer = mCtor();

	HMODULE h_mod_reduce = LoadLibrary(reduce_dll_path.c_str());
	if (h_mod_reduce == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "Load reduce library failed\n";
	}
	ReduceHolder rCtor = (ReduceHolder)GetProcAddress(h_mod_reduce, 
		"createReduceIns");
	if (mCtor == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "GetProcAddress reduce dll failed\n";
	}
	ReduceInterface* reduce_pointer = rCtor();

	BOOST_LOG_TRIVIAL(info) << "Loading Dll sucussful\n";
	FileMgt file_mgt_instance;
	std::vector<std::string> input_file_list = 
		file_mgt_instance.fileIter(input_path);
	//-----check------//file_mgt_instance.printvector(inputFileList);
	std::string median_file_name = 
		file_mgt_instance.createMedianFile(media_path);
	int input_file_counter = 0;

	for (auto it= input_file_list.begin(); it != input_file_list.end(); ++it)
	{
		BOOST_LOG_TRIVIAL(info) << "Mapping input files number "
			<< input_file_counter<<"\n";
		input_file_counter++;

		std::ifstream infile(*it);
		std::string input_line;

		if (infile.is_open())
		{
			while (std::getline(infile, input_line))
			{
				map_pointer->MapFunction(input_line, &exportingMedianFile,
					median_file_name);
			}
		}
		else
		{
			BOOST_LOG_TRIVIAL(error) << "Open input files failed\n";
		}
		infile.close();
	}

	BOOST_LOG_TRIVIAL(info) << "Mapping finished\n";
	std::vector<std::string> median_file_list = 
		file_mgt_instance.fileIter(media_path);
	
	std::vector<std::pair<std::string, std::string>> sortable_tokens = 
		file_mgt_instance.readList(median_file_list);
	//-----check------//file_mgt_instance.printPairVector(sortable_tokens);

	BOOST_LOG_TRIVIAL(info) << "Sorting and grouping started\n";
	Sort sort_instance;
	std::vector<std::vector<std::string>> sorted_and_grouped_tokens = 
		sort_instance.sortAndGroup(sortable_tokens);
	//----check-----//file_mgt_instance.printVectorVector(sorted_and_grouped_tokens);
	std::string output_file_name = file_mgt_instance.createOutputFile(out_path);
	BOOST_LOG_TRIVIAL(info) << "Sorting and grouping finished\n";

	BOOST_LOG_TRIVIAL(info) << " Reducing started\n";
	reduce_pointer->ReduceFunction(sorted_and_grouped_tokens,
		exportingOutputFile, output_file_name);

	FreeLibrary(h_mod_map);
	FreeLibrary(h_mod_reduce);
}

void exportingMedianFile(const std::vector<std::pair<std::string, std::string>>
	tokenized, std::string median_file_name)
{
	std::ofstream outfile(median_file_name, std::ios::app);
	if (outfile.is_open())
	{
		for (auto it = tokenized.begin(); it != tokenized.end(); ++it)
		{
			std::pair<std::string, std::string> tmp_pair = *it;
			outfile << tmp_pair.first << " " << tmp_pair.second << std::endl;
		}
	}
	else {
		BOOST_LOG_TRIVIAL(error) << "Open median files failed\n";
	}
	outfile.close();
};

void exportingOutputFile(const std::vector<std::vector<std::string>> 
	input_vector, std::string out_file_name)
{
	std::ofstream outfile(out_file_name, std::ios::app);
	if (outfile.is_open())
	{
		for (auto it = input_vector.begin(); it != input_vector.end(); ++it)
		{
			std::vector<std::string> inside_vector = *it;
			for (auto it = inside_vector.begin(); it !=
				inside_vector.end(); ++it)
			{
				outfile << *it << " ";
			}
			outfile << std::endl;
		}
	}
	else {
		BOOST_LOG_TRIVIAL(error) << "Open output files failed\n";
	}
	outfile.close();
};

