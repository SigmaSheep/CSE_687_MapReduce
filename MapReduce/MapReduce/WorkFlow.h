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


#include "FileMgt.h"
#include "Map.h"
#include "SortClass.h"
#include "Reduce.h"

#include <string> // std::string


class WorkFlow
{
public:
	WorkFlow() {};
	~WorkFlow() {};

	WorkFlow(std::string inPath_p, std::string mediaPath, std::string outPath);

};

#endif