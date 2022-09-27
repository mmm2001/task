#pragma once
#include "cElement.h"
#include"cNode.h"
#include "CFace.h"
#include <vector>
#include <string>
using namespace std;

class CMesh
{
public:
	int NN, NE;
	CMesh(string name);
	void Geometry();
	void Adjacent();
	vector <CNode> n;
	vector <CElement> e;
	vector <CFace> f;
	vector <CFace> bf;
};