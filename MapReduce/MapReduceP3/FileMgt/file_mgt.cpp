#include "file_mgt.h"

// iteration through a directory and return a vector contains file path
std::vector<std::string> FileMgt::fileIter(const std::string path_p) {
	std::vector<std::string> file_list;
	namespace fs = boost::filesystem;
	typedef boost::filesystem::recursive_directory_iterator iterator;
	fs::path p(path_p);
        if (!fs::exists(p)) {
			BOOST_LOG_TRIVIAL(error) << "this " << path_p << " does not exist\n";
			std::exit(EXIT_FAILURE);
		} else {
			fs::recursive_directory_iterator end =
              fs::recursive_directory_iterator();
			fs::recursive_directory_iterator begin =
              fs::recursive_directory_iterator(p);
			for (fs::recursive_directory_iterator it = begin; begin != end;
               it++) {
            file_list.push_back(it->path().string());
			}
			return file_list;
		}
}

// print out vector of string for debuging
void FileMgt::printvector(const std::vector<std::string> input_vector) {
	for (std::vector<std::string>::const_iterator it = input_vector.begin();
		it != input_vector.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

// create multiple median files and clear file if already exists
std::vector<std::string> FileMgt::createMedianFiles(int proc_id, int r_count,
	const std::string media_path) {
	std::vector<std::string > median_file_list;
	for (int i = 0; i < r_count; i++) {
		std::string media_file_name = media_path + 
			std::string("/intermediate") +std::to_string(proc_id)
			+"_" +std::to_string(i) +std::string(".txt");
		median_file_list.push_back(media_file_name);
		// create& clear a file
		std::ofstream file(media_file_name, std::ios::out);
	}
	return median_file_list;
};

// create output file and clear a file if already exists
std::string FileMgt::createOutputFile(int reducer_id, 
	const std::string out_path) {
	std::string output_file_name = out_path + std::string("/final_result")
		+ std::to_string(reducer_id) +std::string(".txt");
	std::ofstream file(output_file_name, std::ios::out); // create& clear a file
	return output_file_name;
};

// read a list of mediate files for a specific reducer
// return a vector contains pairs of key and value
std::vector<std::pair<std::string, std::string>> FileMgt::ReadMediateFiles(
	int reducer_id, int r_count, std::string media_path) {
	std::string reduceble_file_name_tmp;
	std::vector<std::string> reduceble_file_list;
	for (int j = 0; j < r_count; j++) {// j represents process id
		reduceble_file_name_tmp = media_path +
			std::string("/intermediate") + std::to_string(j)
			+ "_" + std::to_string(reducer_id) + std::string(".txt");
		reduceble_file_list.push_back(reduceble_file_name_tmp);
	}

	std::vector<std::pair<std::string, std::string>> sortable_token_list;
	for (auto it = reduceble_file_list.begin(); 
		it != reduceble_file_list.end(); ++it) {
		std::string delimiter = " ";
		std::ifstream infile(*it);
		std::string line;
		if (infile.is_open()) {
			while (std::getline(infile, line)) {
				size_t pos = line.find(delimiter);
				std::pair<std::string, std::string> key_and_value =
					std::make_pair(line.substr(0, pos),
						line.substr(pos + 1, line.size()));
				sortable_token_list.push_back(key_and_value);
			} 
		} else {
			std::cout << "file is not open" << std::endl;
		}
		infile.close();
	}
	return sortable_token_list;
}

// print out a vector of pairs for debuging
void FileMgt::printPairVector(const std::vector<std::pair<std::string,
	std::string>> input_vector) {
	std::pair<std::string, std::string> key_and_value;
	for (auto it = input_vector.begin(); it != input_vector.end(); ++it) {
		key_and_value = *it;
		std::cout << key_and_value.first << " " << key_and_value.second << std::endl;
	}
};

// print out a vector of vector for debuging
void FileMgt::printVectorVector(
	const std::vector<std::vector<std::string>> input_vector) {
	for (auto it = input_vector.begin(); it != input_vector.end(); ++it) {
		std::vector<std::string> inside_vector = *it;
		for (auto it = inside_vector.begin(); it != inside_vector.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << "\n";
	}
};

// divide input files to m parts according to how many map processes
// also make string ready for CreateProcess argument type like "path1 path2 ...pathn" 
std::vector<std::string> FileMgt::AllocateInputFiles(
	int count, const std::vector<std::string> input_file_list) {
	std::vector<std::string> divided_file_list;
	auto elements_per_part = input_file_list.size() / count;
	for (int i = 0; i < (count-1); i++) {
		auto start_position = input_file_list.begin() + (i * elements_per_part);
		auto end_position = input_file_list.begin() + ((i + 1) * elements_per_part);
		std::string path_for_one_mapper;
		for (auto it = start_position; it != end_position; ++it) {
			path_for_one_mapper.append("\""); // in case file name has space
			path_for_one_mapper.append(*it);
			path_for_one_mapper.append("\"");
			path_for_one_mapper.append(" ");
		}
		divided_file_list.push_back(path_for_one_mapper);
	}
	auto start_position = input_file_list.begin() + ((count - 1) * elements_per_part);
	std::string path_for_one_mapper;
	for (auto it = start_position; it != input_file_list.end(); ++it) {
		path_for_one_mapper.append("\""); // in case file name has space
		path_for_one_mapper.append(*it);
		path_for_one_mapper.append("\"");
		path_for_one_mapper.append(" ");
	}
	divided_file_list.push_back(path_for_one_mapper);
	return divided_file_list;
}
