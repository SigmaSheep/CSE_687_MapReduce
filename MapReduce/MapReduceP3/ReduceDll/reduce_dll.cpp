////////////////////////////////////////////////////////////////////////////////
// ReduceClass is a child class of ReduceInterface.
// Please follow this template to write dll.
// Map dll should keep all the following structures unchanged. User should add 
// their functions to ReduceFunction or add any other functions or attribute 
// used by ReduceFunction.
// ReduceFunction passes three arguments:input_vector,exporting,out_file_name
// input_vector contains sorted and grouped key and values. First element is 
// key. The reset elements are values.
// exportring function could be used to export data.
// exporting will export vector of vector to output path as final_result.txt.
// out_file_name is passed to ReduceFunction. out_file_name should be used
// as argument of exporting function.
///////////////////////////////////////////////////////////////////////////////

//required file: ReduceInterface.h

#include "../ReduceInterface/reduce_interface.h"

#include <iostream>
#include <string>  // std::string
#include <vector>  // std::vector

class __declspec(dllexport) ReduceClass : public ReduceInterface {
public:
	virtual std::vector<std::vector<std::string>> ReduceFunction(
		const std::vector<std::string>& key_vector,
		const std::vector<std::vector<std::string>>& value_vector);
	std::vector<std::vector<std::string>> sumValues(
        const std::vector<std::string>& key_vector,
		const std::vector<std::vector<std::string>>& input_vector);
};

extern "C" __declspec(dllexport) ReduceInterface* CreateReduceIns()
{
	return new ReduceClass();
}

//////////////////////////////////////////////////////////////////////////////////////
//std::vector<std::vector<std::string>> ReduceClass::ReduceFunction(
//		const std::string key,
//		const std::vector<std::vector<std::string>> value_vector)
// function: this function count word frequence in the input_vector, and 
//           return result back to framework
/////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<std::string>> ReduceClass::ReduceFunction(
	const std::vector<std::string>& key_vector,
	const std::vector<std::vector<std::string>>& value_vector) {
	std::vector<std::vector<std::string>> final_result = 
		sumValues(key_vector, std::ref(value_vector));
	return final_result;
}
//////////////////////////////////////////////////////////////////////////////////////
//std::vector<std::vector<std::string>> ReduceClass::sumValues(
//		const std::vector<std::vector<std::string>> input_vector){
// function: this function is called by ReduceFunction to sum all values in input_vector.
//           It first convert string to int, and after sum convert it back to string.
/////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<std::string>> ReduceClass::sumValues(
    const std::vector<std::string>& key_vector,
	const std::vector<std::vector<std::string>>& input_vector) {
	std::vector<std::vector<std::string>> final_result;
  auto key_iterator = key_vector.begin();
	for (auto it = input_vector.begin(); it != input_vector.end(); ++it) {
		std::vector<std::string> tmp_vector = *it;
		std::vector<std::string> final_result_per_element;
		final_result_per_element.push_back(*key_iterator);
		int sum = 0;
		for (auto it = tmp_vector.begin(); it != tmp_vector.end(); ++it) {
			sum += std::stoi(*it);
		}
		final_result_per_element.push_back(std::to_string(sum));
		final_result.push_back(final_result_per_element);
        ++key_iterator;
	}
	return final_result;
}
