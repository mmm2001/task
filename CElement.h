#pragma once
#include <vector>
#include "CNode.h"
class CElement
{
public:
	int number, type;
	double volume;
	CNode Center;
	std::vector <int> ad;
	std::vector <int> nn;
	std::vector <int> fn;
	CElement();
};

