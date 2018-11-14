#ifndef REDUCE_H
#define	REDUCE_H

#include <string>
#include <vector>
class Reduce
{
public:
	Reduce() {};
	~Reduce() {};
	void reduceFunction(const std::vector<std::vector<std::string>> input_vector, void(*exporting)(const std::vector<std::vector<std::string>>, std::string),const std::string out_file_name);
private:
	std::vector<std::vector<std::string>> sumValues(const std::vector<std::vector<std::string>> input_vector);
};
#endif // !REDUCE_H