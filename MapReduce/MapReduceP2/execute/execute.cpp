#include <string>
#include "../WorkFlow/WorkFlow.h"


int main()
{
	std::string input_path, media_path, out_path;
	/*
	std::cout << "type input directory\n";
	std::cin >> inPath;

	std::cout << "type intermediate directory\n";
	std::cin >> mediaPath;

	std::cout << "type output directory\n";
	std::cin >> outPath;
	*/

	input_path = "C:\\Users\\liuxi\\OneDrive\\Desktop\\test\\input";
	media_path = "C:\\Users\\liuxi\\OneDrive\\Desktop\\test\\median";
	out_path = "C:\\Users\\liuxi\\OneDrive\\Desktop\\test\\output";
	
	WorkFlow(input_path, media_path, out_path);
	std::cout << "finished\n";
	std::cin.get();

	return 0;
}
