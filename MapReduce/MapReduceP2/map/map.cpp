#include "Map.h"

void Map::MapFunction(const std::string line, void(*exporting)(std::vector<std::pair<std::string, std::string>>, std::string), std::string median_file_name)
{
	if (line.size() != 0)
	{
		std::vector<std::pair<std::string, std::string>> tokenized_vector = Tokenizer(line);
		exporting(tokenized_vector, median_file_name);
	}
}

std::vector<std::pair<std::string,std::string>> Map::Tokenizer(std::string line)
{
	std::transform(line.begin(), line.end(), line.begin(), ::tolower); //transfoer to lowercase
	std::vector<std::pair<std::string, std::string>> tokenized_vector;
	/*
	int word_start;
	int i = 0;
	
	while(i!=line.size()-1)
	{
		word_start = i;
		while (!std::ispunct(line[i]) && line[i] != ' ' && line[i] != '\t' && i != line.size() - 1)
		{
			i++;
		}
		tokenized_vector.push_back(std::make_pair(line.substr(word_start,i), "1"));
		while ((std::ispunct(line[i]) || line[i] == ' ' || line[i] == '\t') && i!=line.size()-1)
		{
			i++;
		}
	}
	*/
	
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
		//if (*str < 0) {
			//*str = ' ';
		//}
		if (begin != str) {
			tokenized_vector.push_back(std::make_pair(std::string(begin, str),"1"));
		}
		while ((std::ispunct(*str) || *str == ' ' || *str == '\t') && *str)
		{
			str++;
		}
		//if (*str < 0) {
			//memmove(str, str + 1, strlen(str) - counter);
		//}
	}
	
	return tokenized_vector;
}