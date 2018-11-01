#include "stdafx.h"
#include "Map.h"


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

			while (!std::ispunct(*str) && *str != ' ' && *str !='\t' && *str)
			{
				str++;
			}

			if (begin != str) {
				result.push_back(std::string(begin, str));
			}

			while ((std::ispunct(*str) || *str == ' ' || *str =='\t') && *str)
			{
				str++;
			}
		};

		return result;
	}

	//write tokens as "word 1\n" to intermidiate file
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