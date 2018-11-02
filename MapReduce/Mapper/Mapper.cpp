#include "stdafx.h"
#include "Mapper.h"


void Mapper::MapperFunc(std::string mediaFileName, std::string line, int BufSize_p)
{

	BufSize = BufSize_p;

	FileName = mediaFileName;
	BufCount = 0;

	std::transform(line.begin(), line.end(), line.begin(), ::tolower); //transfoer to lowercase

	const char *str = line.c_str();

	//assign token
	std::vector<std::string>token = tokenizer(str);

	//export token
	exportToken(token);

}



//take a line of string, convert to vectors of words
std::vector<std::string> Mapper::tokenizer(const char *str)
{
	std::vector < std::string > result;

	while (*str)
	{
		const char *begin = str;

		while (!std::ispunct(*str) && *str != ' ' && *str != '\t' && *str)
		{
			str++;
		}

		if (begin != str) {
			result.push_back(std::string(begin, str));
		}

		while ((std::ispunct(*str) || *str == ' ' || *str == '\t') && *str)
		{
			str++;
		}
	};

	return result;
}

//write tokens as "word 1\n" to intermidiate file
void Mapper::exportToken(std::vector<std::string> token)
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


Mapper::~Mapper()
{

	std::ofstream outfile(FileName, std::ios::app);

	if (outfile.is_open()) {

		outfile << Buffer.rdbuf();
	}

	BufCount = 0;
	outfile.close();
}