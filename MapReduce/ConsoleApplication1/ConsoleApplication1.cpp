// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../MapReduce/Map.h"
#include "../MapReduce/Map.cpp"


int main()
{
	Map test;

	std::string sample = "A B,C A.";
	std::string medianFile = ".\\intermediate.txt";

	test.MapperFunc(medianFile, sample, 1000);
	std::ifstream read_file(".\\intermediate.txt");
	std::string line;
	std::getline(read_file, line);
	read_file.close();

	std::cout << line;




    return 0;
}

