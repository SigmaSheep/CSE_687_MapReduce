#ifndef MAPPER_H
#define MAPPER_H


#include<boost/tokenizer.hpp> // boost::tokenizer<>

#include <algorithm> // std::transform()
#include <cctype> // std::ispunct()
#include <iostream> // std::cout
#include <string>  // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

class Map
{
public:
	Map() {};
	~Map() {};
	void MapFunction(const std::string line, void(*exporting)(std::vector<std::pair<std::string, std::string>>, std::string), std::string median_file_name);
	std::vector<std::pair<std::string, std::string>> Tokenizer(std::string line);
};

#endif