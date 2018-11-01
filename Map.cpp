//Map.cpp, creates vectors with tokens from input files 
#include "stdafx.h"
#include "Map.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>
#include <time.h>

#define MAX_DATE 12

/*
	std::string get_date(void)
	{
		time_t now;
		char the_date[MAX_DATE];

		the_date[0] = '\0';

		now = time(NULL);

		if (now != -1)
		{
			strftime(the_date, MAX_DATE, "%d_%m_%Y", gmtime(&now));
		}

	return std::string(the_date);
	}
*/
	void Map::MapperFunc(std::string mediaFileName, const char *str)
	{

	FileName = mediaFileName;
	BufCount = 0;

	//assign token
	std::vector<std::string>token = tokenizer(str);

	//export token
	exportToken(token);

	}

	//take a line of string, convert to vectors of words
	std::vector<std::string> Map::tokenizer(const char *str)
	{
		std::vector < std::string > result;

		while (*str)
		{
			const char *begin = str;

			while (!std::ispunct(*str) && *str != ' ' && *str)
			{
				str++;
			}
			//convert to lower case and add to results vector
			std::string item = std::string(begin, str);
			std::transform(item.begin(), item.end(), item.begin(), ::tolower);			
			result.push_back(std::string(item));

			while ((std::ispunct(*str) || *str == ' ') && *str)
			{
				str++;
			}
		};

		return result;
	}

	//write tokens as "word 1\n" to intermediate file
	void Map::exportToken(std::vector<std::string> token)
	{
		

		for (std::vector<std::string>::iterator it = token.begin(); it != token.end(); ++it)
		{
			Buffer << *it << " 1" << std::endl;
			BufCount++;
		}
		
		if (BufCount >= BufSize)
		{

			std::ofstream outfile(FileName, std::ios::app);

			if (outfile.is_open()) {

				outfile << Buffer.rdbuf();
			}

			BufCount = 0;
			outfile.close();
		}
		
	}


	Map::~Map()
	{

		std::ofstream outfile(FileName, std::ios::app);

		if (outfile.is_open()) {

			outfile << Buffer.rdbuf();
		}

		BufCount = 0;
		outfile.close();
	}