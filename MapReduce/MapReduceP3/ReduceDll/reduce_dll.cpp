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
{
	return new ReduceClass();
}

//////////////////////////////////////////////////////////////////////////////////////
//void ReduceClass::ReduceFunction(
//		const std::vector<std::vector<std::string>> input_vector,
//		void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
//		const std::string out_file_name)
// function: this function count word frequence in the input_vector, and call
//           exporting function to export the count to output file
/////////////////////////////////////////////////////////////////////////////////////
void ReduceClass::ReduceFunction(
	const std::vector<std::vector<std::string>> input_vector,
	void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
	const std::string out_file_name) {
	std::vector<std::vector<std::string>> final_result = sumValues(input_vector);
	exporting(final_result, out_file_name);
}
//////////////////////////////////////////////////////////////////////////////////////
//std::vector<std::vector<std::string>> ReduceClass::sumValues(
//		const std::vector<std::vector<std::string>> input_vector){
// function: this function is called by ReduceFunction to sum all values in input_vector.
//           It first convert string to int, and after sum convert it back to string.
/////////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<std::string>> ReduceClass::sumValues(
	const std::vector<std::vector<std::string>> input_vector) {
	std::vector<std::vector<std::string>> final_result;
	for (auto it = input_vector.begin(); it != input_vector.end(); ++it) {
		std::vector<std::string> tmp_vector = *it;
		std::vector<std::string> final_result_per_element;
		final_result_per_element.push_back(tmp_vector.front());
		int sum = 0;
		for (auto it = tmp_vector.begin() + 1; it != tmp_vector.end(); ++it) {
			sum += std::stoi(*it);
		}
		final_result_per_element.push_back(std::to_string(sum));
		final_result.push_back(final_result_per_element);
	}
	return final_result;
}