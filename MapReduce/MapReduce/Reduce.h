#pragma once
#include <vector>

class Reduce
{
public:
	Reduce();
	~Reduce();

	std::vector<std::string> reduceFunction(std::vector<std::string> sortedTokens);
};

