#ifndef REDUCEINTERFACE_H
#define REDUCEINTERFACE_H

#include <string>
#include <vector>
#define Reduce_API __declspec(dllexport)
class ReduceInterface
{
public:
	ReduceInterface() {};
	~ReduceInterface() {};
	virtual void ReduceFunction(
		const std::vector<std::vector<std::string>> input_vector,
		void(*exporting)(const std::vector<std::vector<std::string>>, std::string),
		const std::string out_file_name) {};
};
#endif
