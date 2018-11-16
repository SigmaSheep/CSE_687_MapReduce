#ifndef REDUCEDLL_CPP
#define REDUCEDLL_CPP

#include "../ReduceInterface/ReduceInterface.h"

#include <string>  // std::string
#include <vector>  // std::vector

#define Reduce_Dll __declspec(dllexport)

class Reduce_Dll ReduceClass : public ReduceInterface {
public:
	virtual void ReduceFunction(
		const std::vector<std::vector<std::string>> input_vector,
		void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
		const std::string out_file_name);
	std::vector<std::vector<std::string>> sumValues(
		const std::vector<std::vector<std::string>> input_vector);

};

extern "C" Reduce_Dll ReduceInterface* createReduceIns()
	{ return new ReduceClass(); }

void ReduceClass::ReduceFunction(
	const std::vector<std::vector<std::string>> input_vector,
	void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
	const std::string out_file_name)
{
	std::vector<std::vector<std::string>> final_result = sumValues(input_vector);
	exporting(final_result, out_file_name);
}

std::vector<std::vector<std::string>> ReduceClass::sumValues(
	const std::vector<std::vector<std::string>> input_vector)
{
	std::vector<std::vector<std::string>> final_result;
	for (auto it = input_vector.begin(); it != input_vector.end(); ++it)
	{
		std::vector<std::string> tmp_vector = *it;
		std::vector<std::string> final_result_per_element;
		final_result_per_element.push_back(tmp_vector.front());
		int sum = 0;
		for (auto it = tmp_vector.begin() + 1; it != tmp_vector.end(); ++it)
		{
			sum += std::stoi(*it);
		}
		final_result_per_element.push_back(std::to_string(sum));
		final_result.push_back(final_result_per_element);
	}
	return final_result;
}
#endif