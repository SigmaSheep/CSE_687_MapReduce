#include "ReduceInterface.h"

class Reduce_API ReduceClass : public ReduceInterface {
public:
	virtual void ReduceFunction(
		const std::vector<std::vector<std::string>>	input_vector,
		void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
		const std::string out_file_name);
};

extern "C" Reduce_API ReduceInterface* createReduceIns()
	{ return new ReduceClass(); }

void ReduceClass::ReduceFunction(
	const std::vector<std::vector<std::string>> input_vector,
	void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
	const std::string out_file_name)
{
	//this should be your dll function
}