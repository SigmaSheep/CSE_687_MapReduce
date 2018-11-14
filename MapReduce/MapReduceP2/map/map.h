#ifndef MAPPER_H
#define MAPPER_H
/////////////////////////////////////////////////////////////////////
//  Map.h -	   Map function for input txt file					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18
//									//
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module maped a line of txt to word tokens as the form of "word 1"
A private method exportToken buff the output and write to the midiate files
Deault buffer size 1000 words per write is hard coded in constructor.
Destructor will clear the buffer and write to file.
Public Interface:
=================
MapperFunc(std::string mediaFileName, std::string line);
It takes mediaFileName as a compelete directory with file name.
Required files
================
none
Maintenance History:
===============
10/22/2018 first relase
*/
//

#include <iostream>  // std::cout (debug)
#include <string>  // std::string
#include <fstream> // std::ifstream, std::ofstream
#include <vector> // std::vector
#include <cctype> // std::ispunct()
#include <sstream> // std::stringstream
#include <algorithm> // std::transform()

class Map
{
public:
	//hard code bufsize
	Map() { BufSize = 1000; };
	~Map();
	void MapperFunc(std::string mediaFileName, std::string line, int BufSize_p);

private:
	std::vector<std::string> tokenizer(const char *str);
	void exportToken(std::vector<std::string> token);

	std::string	FileName;
	std::stringstream Buffer;
	int BufCount;
	int BufSize;
};

#endif


