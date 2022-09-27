#pragma once
#include "CNode.h"
#include <vector>
class CFace
{
public:
	int nf, type;
	double Area;
	CNode Center;
	std::vector <int> nn;
	std::vector <int> ne;
	CFace();
	CNode Normal;
};

