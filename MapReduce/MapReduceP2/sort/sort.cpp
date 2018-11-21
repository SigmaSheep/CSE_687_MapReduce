////////////////////////////////////////////////////////////////////////////
//std::vector<std::vector<std::string>> sortAndGroup(
//			const std::vector<std::pair<std::string, std::string>> sortableTokens);
//input: sortableTokens - vector of pair read from median files
//						  pair.first is key.pair.second is value.
//return: a vector of vector of string. First element in inside vector is the
//        key. Second to the last element are the values corresponding to first
//		  element key. Key is sorted by ascending order.
////////////////////////////////////////////////////////////////////////////
#include "Sort.h"

std::vector<std::vector<std::string>> Sort::sortAndGroup(
	const std::vector<std::pair<std::string, std::string>> sortableTokens) {

	std::vector<std::pair<std::string, std::string>> copied_tokens =
		sortableTokens;
	//use lambda to sort based on pair.first by ascending order
	std::sort(copied_tokens.begin(), copied_tokens.end(),
		[](const std::pair<std::string, std::string> &left,
		const std::pair<std::string, std::string> &right) 
		{return left.first < right.first; });

	std::string word; //store key
	std::vector<std::string> grouped_elements; // store a key and its values
	std::vector<std::vector<std::string>> grouped_vector;//store all results

	for (auto it = copied_tokens.begin(); it != copied_tokens.end(); ++it) {
		std::pair<std::string, std::string> key_and_value = *it;
		if (word == key_and_value.first) {//if key is same, add value
		
			grouped_elements.push_back(key_and_value.second);
		} else {//if different key, push grouped_elements to result
			    //and start a new grouped_elements
			grouped_vector.push_back(grouped_elements);
			grouped_elements.clear();
			grouped_elements.push_back(key_and_value.first);
			grouped_elements.push_back(key_and_value.second);
		}
		word = key_and_value.first;//update key
	}
	grouped_vector.push_back(grouped_elements);//push last to grouped_vector
	//clear the first empty spot in grouped_vector 
	grouped_vector.erase(grouped_vector.begin(), grouped_vector.begin()+1);
	return grouped_vector;
}
