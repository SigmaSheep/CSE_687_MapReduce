#include "sort.h"


SortClass::SortClass()
{
}


SortClass::~SortClass()
{
}




std::vector<std::string> SortClass::sortfunction(std::vector<std::string> inputString)
{
	std::sort(inputString.begin(), inputString.end());
	std::string word;
	std::vector<std::string> result;
	std::string result_word;


	for (std::vector<std::string>::iterator it = inputString.begin(); it != inputString.end(); ++it)
	{

		if (word == *it)
		{
			result_word.append(" 1");
		}
		else
		{
			result.push_back(result_word);
			result_word.clear();
			std::string tmp = *it;
			tmp = tmp.substr(0, tmp.find(" "));
			result_word.append(tmp);
			result_word.append(" 1");
		}

		word = *it;
	}

	result.push_back(result_word);

	return result;

}