#ifndef MAPDLL_CPP
#define MAPDLL_CPP

#include "../MapInterface/MapInterface.h"
#include<boost/tokenizer.hpp> // boost::tokenizer<>
#include <algorithm> // std::transform()
#include <cctype> // std::ispunct()
#include <iostream> // std::cout
#include <string>  // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

#define Map_DLL __declspec(dllexport)

class Map_DLL MapClass : public MapInterface {
public:
	virtual void MapFunction(const std::string line, void(*exporting)(std::vector<std::pair<std::string, std::string>>, std::string), std::string median_file_name);
	std::vector<std::pair<std::string, std::string>> Tokenizer(std::string line);
};

extern "C" Map_DLL MapInterface* createMapIns() { return new MapClass(); }

void MapClass::MapFunction(const std::string line, void(*exporting)(std::vector<std::pair<std::string, std::string>>, std::string), std::string median_file_name)
{
	if (line.size() != 0)
	{
		std::vector<std::pair<std::string, std::string>> tokenized_vector = Tokenizer(line);
		exporting(tokenized_vector, median_file_name);
	}
}

std::vector<std::pair<std::string, std::string>> MapClass::Tokenizer(std::string line)
{
	std::transform(line.begin(), line.end(), line.begin(), ::tolower); //transfoer to lowercase
	std::vector<std::pair<std::string, std::string>> tokenized_vector;
	const char *str = line.c_str();
	int counter = 0;
	while (*str)
	{
		const char *begin = str;
		while (!std::ispunct(*str) && *str != ' ' && *str != '\t' &&*str)
		{
			str++;
			counter += 1;
		}
		if (begin != str) {
			tokenized_vector.push_back(std::make_pair(std::string(begin, str), "1"));
		}
		while ((std::ispunct(*str) || *str == ' ' || *str == '\t') && *str)
		{
			str++;
		}
	}
	return tokenized_vector;
}

#endif