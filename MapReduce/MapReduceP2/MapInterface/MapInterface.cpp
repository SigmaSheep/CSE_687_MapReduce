#include "MapInterface.h"

class Map_API MapClass : public MapInterface {
public:
	virtual void MapFunction(const std::string line,
		void(*exporting)(std::vector<std::pair<std::string, std::string>>,
			std::string),
		std::string median_file_name);
};

extern "C" Map_API MapInterface* createMapIns() { return new MapClass(); }

void MapClass::MapFunction(const std::string line,
	void(*exporting)(std::vector<std::pair<std::string, std::string>>,
		std::string),
	std::string median_file_name)
{
	//this should be your dll function
}