#include <string>
#include "../WorkFlow/WorkFlow.h"


int main()
{
	std::string input_path, media_path, out_path, map_dll_path, reduce_dll_path;
	/*
	std::cout << "type input directory\n";
	std::cin >> inPath;

	std::cout << "type intermediate directory\n";
	std::cin >> mediaPath;

	std::cout << "type output directory\n";
	std::cin >> outPath;
	*/

	input_path = "C:\\Users\\liuxi\\OneDrive\\Desktop\\test\\shakespeare";
	media_path = "C:\\Users\\liuxi\\OneDrive\\Desktop\\test\\median";
	out_path = "C:\\Users\\liuxi\\OneDrive\\Desktop\\test\\output";
	map_dll_path = "..\\debug\\MapDll.dll";
	reduce_dll_path = "..\\debug\\ReduceDll.dll";
	
	WorkFlow(input_path, media_path, out_path, map_dll_path, reduce_dll_path);

	return 0;
}
