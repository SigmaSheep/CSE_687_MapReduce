#ifndef MAPINTERFACE_H
#define MAPINTERFACE_H

#include <string>
#include <vector>
#define Map_API __declspec(dllexport)
class MapInterface
{
public:
	MapInterface() {};
	~MapInterface() {};
	virtual void MapFunction(const std::string line, void(*exporting)(std::vector<std::pair<std::string, std::string>>, std::string), std::string median_file_name) {};
};
#endif
