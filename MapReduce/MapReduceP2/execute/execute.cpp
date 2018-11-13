#include <iostream>
#include <string>
#include "..\workflow\workflow.h"
#include "..\workflow\workflow.cpp"

int main()
{

	std::string inPath, mediaPath, outPath;

	std::cout << "type input directory\n";
	std::cin >> inPath;

	std::cout << "type intermediate directory\n";
	std::cin >> mediaPath;

	std::cout << "type output directory\n";
	std::cin >> outPath;

	WorkFlow(inPath, mediaPath, outPath);

	return 0;
}
