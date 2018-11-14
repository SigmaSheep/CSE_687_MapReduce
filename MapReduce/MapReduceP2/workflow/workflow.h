#ifndef WORKFLOW_H
#define WORKFLOW_H

/////////////////////////////////////////////////////////////////////
//  WorkFlow.h -	   work flow operation    					   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module manage the workflow operation
Public Interface:
=================
WorkFlow(std::string inPath_p, std::string mediaPath, std::string outPath);
Manage the workflow operation
Required files
================
FileMgt.h
FileMgt.cpp
Map.h
Map.cpp
SortClass.h
SortClass.cpp
Reduce.h
Reduce.cpp
Maintenance History:
===============
*/
//

#include "../FileMgt/FileMgt.h"
#include "../Map/Map.h"
#include "../Sort/Sort.h"
#include "../Reduce/Reduce.h"

#include <string> // std::string
#include <vector> // std::vector

class WorkFlow
{
public:
	WorkFlow() {};
	~WorkFlow() {};
	WorkFlow(const std::string input_path, const std::string media_path, const std::string out_path);
};
#endif