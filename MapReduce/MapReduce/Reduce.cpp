#include "stdafx.h"
#include "Reduce.h"


Reduce::Reduce()
{
}


Reduce::~Reduce()
{
}

std::vector<std::string> Reduce::reduceFunction(std::vector<std::string> sortedTokens)
{
	__int64 count=0;
	std::vector<std::string> reduce_result;

	for (std::vector<std::string>::iterator it = sortedTokens.begin()+1; it != sortedTokens.end(); ++it)
	{
		std::string tmp = *it;
		std::string count_reuslt;


		count = boost::count(tmp, '1');

		tmp = tmp.substr(0, tmp.find(" "));
		count_reuslt.append(tmp);
		count_reuslt.append(" ");
		count_reuslt.append(std::to_string(count));


		count = 0;
		reduce_result.push_back(count_reuslt);
	}

	return reduce_result;

}
