#pragma once
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


#include "../file_management/file_management.h"
#include "../file_management/file_management.cpp"

#include "../map/map.h"
#include "../map/map.cpp"

#include "../sort/sort.h"
#include "../sort/sort.cpp"

#include "../reduce/reduce.h"
#include "../reduce/reduce.cpp"

#include <string> // std::string


class WorkFlow
{
public:
	WorkFlow() {};
	~WorkFlow() {};

	WorkFlow(std::string inPath_p, std::string mediaPath, std::string outPath);

};

#endif