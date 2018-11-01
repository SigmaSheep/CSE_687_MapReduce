#pragma once
#ifndef WORKFLOW_H
#define WORKFLOW_H

/////////////////////////////////////////////////////////////////////
//  Reduce.h -	   Reduce Mapped results to one file    		   //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2017                                 //
//  Application:   Prototype for CSE687 Pr1, Fa18                  //
//  Author:        Xin Liu, Tess Thoresen Syracuse University	   //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module controls the classes that are called and the input files 
to them

Public Interface:
=================
n/a

Required files
================
none

Maintenance History:
===============
10/28/2018 first relase

*/
//

#include <string>
#include "FileMgt.h"
#include "Map.h"
#include "SortClass.h"
#include "Reduce.h"
class WorkFlow
{
public:
	WorkFlow() {};
	~WorkFlow() {};

	WorkFlow(std::string inPath_p, std::string mediaPath, std::string outPath);

};

#endif