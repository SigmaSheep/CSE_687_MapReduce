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
#include "ReduceInterface.h"
class Reduce_Dll ReduceClass : public ReduceInterface {
public:
	virtual void ReduceFunction(
		const std::vector<std::vector<std::string>>	input_vector,
		void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
		const std::string out_file_name);
};

extern "C" Reduce_Dll ReduceInterface* createReduceIns()
	{ return new ReduceClass(); }

void ReduceClass::ReduceFunction(
	const std::vector<std::vector<std::string>> input_vector,
	void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
	const std::string out_file_name) {
	//this should be your dll function
}
