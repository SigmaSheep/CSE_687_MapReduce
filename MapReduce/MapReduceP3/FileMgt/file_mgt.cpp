#include "file_mgt.h"

// iteration through a directory and return a vector contains file path
std::vector<std::string> FileMgt::fileIter(const std::string path_p) {
	std::vector<std::string> file_list;
	namespace fs = boost::filesystem;

	typedef boost::filesystem::recursive_directory_iterator iterator;
	fs::path p(path_p);
	fs::recursive_directory_iterator end = fs::recursive_directory_iterator();
	fs::recursive_directory_iterator begin = fs::recursive_directory_iterator(p);

	for (fs::recursive_directory_iterator it = begin; begin != end; it++) {
		file_list.push_back(it->path().string());
	}
	return file_list;
}

// print out vector of string for debuging
void FileMgt::printvector(const std::vector<std::string> input_vector) {
	for (std::vector<std::string>::const_iterator it = input_vector.begin();
		it != input_vector.end(); ++it) {
		std::cout << *it << std::endl;
	}
}

// create median file and clear file if already exists
std::string FileMgt::createMedianFile(const std::string media_path) {
	std::string media_file_name = media_path + std::string("\\intermediate.txt");
	std::ofstream file(media_file_name, std::ios::out); // create& clear a file
	return media_file_name;
};

// create output file and clear a file if already exists
std::string FileMgt::createOutputFile(const std::string out_path) {
	std::string output_file_name = out_path + std::string("\\final_result.txt");
	std::ofstream file(output_file_name, std::ios::out); // create& clear a file
	return output_file_name;
};

// read a list of median files and return a vector of pairs contain key and value
std::vector<std::pair<std::string, std::string>> FileMgt::readList(
	const std::vector<std::string> meidan_file_list) {
	std::vector<std::pair<std::string, std::string>> sortable_token_list;

	for (auto it = meidan_file_list.begin(); it != meidan_file_list.end(); ++it) {
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
		}
		else {
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

// partition function to divide input files to R parts
std::vector<std::vector<std::string>> FileMgt::PartitionFunction(
	int count, const std::vector<std::string> input_file_list) {
	std::vector<std::vector<std::string>> partial_list;

	int elements_per_part = input_file_list.size() / count;
	for (int i = 0; i < (count-1); i++) {
		auto start_po = input_file_list.begin() + (i * elements_per_part);
		auto end_po = input_file_list.begin() + ((i + 1) * elements_per_part);
		std::vector<std::string> tmp(start_po,end_po);
		partial_list.push_back(tmp);
	}
	auto start_po = input_file_list.begin() + ((count - 1) * elements_per_part);
	std::vector<std::string> tmp(start_po, input_file_list.end());
	partial_list.push_back(tmp);
	return partial_list;
}