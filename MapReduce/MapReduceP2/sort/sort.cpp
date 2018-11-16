#include "Sort.h"

std::vector<std::vector<std::string>> Sort::sortAndGroup(
	const std::vector<std::pair<std::string, std::string>> sortableTokens)
{
	std::vector<std::pair<std::string, std::string>>
		copied_tokens = sortableTokens;
	std::sort(copied_tokens.begin(), copied_tokens.end(),
		[](const std::pair<std::string, std::string> &left,
		const std::pair<std::string, std::string> &right) 
		{return left.first < right.first; });

	std::string word;
	std::vector<std::string> grouped_element;
	std::vector<std::vector<std::string>> grouped_vector;
	
	for (auto it = copied_tokens.begin(); it != copied_tokens.end(); ++it)
	{
		std::pair<std::string, std::string> key_and_value = *it;
		if (word == key_and_value.first)
		{
			grouped_element.push_back(key_and_value.second);
		}
		else
		{
			grouped_vector.push_back(grouped_element);
			grouped_element.clear();
			grouped_element.push_back(key_and_value.first);
			grouped_element.push_back(key_and_value.second);
		}
		word = key_and_value.first;
	}
	grouped_vector.push_back(grouped_element);
	grouped_vector.erase(grouped_vector.begin(), grouped_vector.begin()+1);
	return grouped_vector;
}