#include "MapInterface.h"

/////////////////////////////////////////////////////////////////////////
/* virtual void MapFunction(const std::string line,
		void(*exporting)(
			std::vector<std::pair<std::string, std::string>>,std::string),
		std::string median_file_name) {};
This virtual function could be overload by child class
input: first argument is a single line of string read from input file
	   Second argument is a function pointer to exporting data. Don't change this
	   argument.
	   Thrid argument is out put file path.
How to use: Use the function passed by function pointer to exporting data
*/
/////////////////////////////////////////////////////////////////////////////
class Map_DLL MapClass : public MapInterface{
public:
	virtual void MapFunction(const std::string line,
		void(*exporting)(std::vector<std::pair<std::string, std::string>>,
			std::string),
		std::string median_file_name);
};

extern "C" Map_DLL MapInterface* createMapIns() { return new MapClass(); }

void MapClass::MapFunction(const std::string line,
	void(*exporting)(
		std::vector<std::pair<std::string, std::string>>,std::string),
	std::string median_file_name){
	//this should be the user dll function
}
