#ifndef MAPDLL_CPP
#define MAPDLL_CPP
/////////////////////////////////////////////////////////////////////
//  MapDll.h -	 user map function dll 						   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module works as user defined mapfunction
Required files
================
MapInterface.h
Maintenance History:
===============
11_16_2018 first release
12_06_2018 give exporting back to framework
*/
//
#include "../MapInterface/map_interface.h"

#include <algorithm> // std::transform()
#include <cctype> // std::ispunct()
#include <iostream> // std::cout
#include <string>  // std::string
#include <utility> // std::pair
#include <vector>  // std::vector

#define Map_DLL __declspec(dllexport)

class Map_DLL MapClass : public MapInterface {
public:
	virtual std::vector<std::pair<std::string, std::string>> MapFunction(
		const std::string key, const std::string& value);
private:
	std::string map_value = "1";
	std::vector<std::pair<std::string, std::string>> Tokenizer(
		std::string line, std::string map_value);
	bool ValidChar(const char c) { return (c < -1 || c>255) ? false : true; };
};

extern "C" Map_DLL MapInterface* CreateMapIns() { return new MapClass(); }

// tokenize the line of string into words, and call exporting function to export data.
std::vector<std::pair<std::string, std::string>> MapClass::MapFunction(
	const std::string key, const std::string& value) {
	std::vector<std::pair<std::string, std::string>> tokenized_vector;
	if (value.size() != 0) {
		tokenized_vector = Tokenizer(value, map_value);
	}
	return tokenized_vector;
}
// called by MapFunction as tokenizer
std::vector<std::pair<std::string, std::string>>
MapClass::Tokenizer(std::string line, std::string map_value) {
	//transfoer to lowercase
	std::transform(line.begin(), line.end(), line.begin(), ::tolower);
	std::vector<std::pair<std::string, std::string>> tokenized_vector;
	const char *str = line.c_str();
	int counter = 0;
	while (*str) {
		const char *begin = str;
		while (*str && ValidChar(*str) && !std::ispunct(*str)
			&& *str != ' ' && *str != '\t') {
			str++;
			counter += 1;
		}
		if (begin != str) {
			tokenized_vector.push_back(
				std::make_pair(std::string(begin, str), map_value));
		}
		while (*str && (!ValidChar(*str) || std::ispunct(*str)
			|| *str == ' ' || *str == '\t')) {
			str++;
		}
	}
	return tokenized_vector;
}
#endif