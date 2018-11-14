#ifndef SORT_H
#define SORT_H

#include <algorithm> // std::sort
#include <iostream> //  std::cout (debug)
#include <string>  // std::string
#include <vector>  // std::vector; std::vector<std::string>::iterator

class Sort
{
public:
	Sort() {};
	~Sort() {};
	std::vector<std::vector<std::string>> sortAndGroup(const std::vector<std::pair<std::string, std::string>> sortableTokens);
};

#endif