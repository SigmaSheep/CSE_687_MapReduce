#pragma once
#ifndef WORKFLOW_H
#define WORKFLOW_H

#include <string>
#include "FileMgt.h"
#include "Map.h"

class WorkFlow
{
public:
	WorkFlow() {};
	~WorkFlow() {};

	WorkFlow(std::string inPath_p, std::string mediaPath, std::string outPath);

};

#endif