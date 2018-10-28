// MapReduce.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Map.h"
#include "WorkFlow.h"

int main()
{
	
	std::string inPath, mediaPath, outPath;
	/*
	std::cout << "type input directory\n";
	std::cin >> inPath;

	std::cout << "type intermediate directory\n";
	std::cin >> mediaPath;

	std::cout << "type output directory\n";
	std::cin >> outPath;

	*/
	
	//for test only
	inPath = "C:\\Users\\Xin\\Desktop\\test\\shakespeare";
	mediaPath = "C:\\Users\\Xin\\Desktop\\test\\median";
	outPath = "C:\\Users\\Xin\\Desktop\\test\\output";

	WorkFlow(inPath, mediaPath, outPath);

    return 0;
}

