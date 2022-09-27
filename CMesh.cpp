#include "CMesh.h"
#include <fstream>
#include <math.h>
#include <iostream>
#include <algorithm>
//
//                                                        ?????? ?????????? ????? ?? ?????
//
CMesh::CMesh(string name)
{
	CFace tmp;
	ifstream fin(name);
	string buff;
	while (getline(fin, buff)) {
		if (buff == "$Nodes")
		{
			fin >> buff;
			fin >> buff;
			fin >> buff;
			fin >> buff;
			NN = stoi(buff);
			n.resize(NN + 1);
			int numb;
			for (int i = 0; i <= NN - 1; i++)
			{
				fin >> buff;
				fin >> buff;
				fin >> buff;
				fin >> buff;
				numb = stod(buff);
				for (int k = 1; k <= numb; k++) {
					fin >> buff;
					n[i + k].number = stod(buff);
				}
				for (int j = 1; j <= numb; j++) {
					fin >> buff;
					n[i + j].x = stod(buff);
					fin >> buff;
					n[i + j].y = stod(buff);
					fin >> buff;
					n[i + j].z = stod(buff);
				}
				i += numb - 1;
			}
		}

		if (buff == "$Elements") {
			fin >> buff;
			fin >> buff;
			fin >> buff;
			fin >> buff;
			NE = stoi(buff);
			e.resize(NE + 1);
			int type;
			int cr = 0;
			for (int i = 0; i <= NE - 1; i++)
			{
				fin >> buff;
				type = stoi(buff);
				fin >> buff;
				fin >> buff;
				fin >> buff;
				int numb = stoi(buff);

				for (int j = 0; j <= numb; j++) {
					e[i + j].type = type;
				}

				if (e[i].type == 0) {
					e[i].nn.resize(1);
					fin >> buff;
					e[i].number = stoi(buff);
					fin >> buff;
					e[i].nn[0] = stoi(buff);
				}

				if (e[i].type == 1) {
					for (int j = 1; j <= numb; j++) {
						e[i + j].nn.resize(2);
						fin >> buff;
						e[i + j].number = stoi(buff);
						fin >> buff;
						e[i + j].nn[0] = stoi(buff);
						fin >> buff;
						e[i + j].nn[1] = stoi(buff);
					}
					i += numb - 1;
				}
				if (e[i].type == 2) {
					int n = bf.size();
					bf.resize(n + numb + 1);
					for (int j = 1; j <= numb; j++) {
						e[i + j].nn.resize(3);
						fin >> buff;
						e[i + j].number = stoi(buff);
						bf[j + cr - 1].nf = j + cr;
						bf[j + cr].type = 0;
						fin >> buff;
						e[i + j].nn[0] = stoi(buff);
						
						fin >> buff;
						e[i + j].nn[1] = stoi(buff);
						
						fin >> buff;
						e[i + j].nn[2] = stoi(buff);

						sort(e[i + j].nn.begin(), e[i + j].nn.end());

						bf[j + cr - 1].nn[0] = e[i + j].nn[0];
						bf[j + cr - 1].nn[1] = e[i + j].nn[1];
						bf[j + cr - 1].nn[2] = e[i + j].nn[2];
					}
					cr += numb;
					i += numb - 1;
				}
				
				if (e[i].type == 3) {
					f.resize(1);
					for (int j = 1; j <= numb; j++) {

						//CFace tmp;
						e[i + j].nn.resize(4);

						fin >> buff;
						e[i + j].number = stoi(buff);
						fin >> buff;
						e[i + j].nn[0] = stoi(buff);
						fin >> buff;
						e[i + j].nn[1] = stoi(buff);
						fin >> buff;
						e[i + j].nn[2] = stoi(buff);
						fin >> buff;
						e[i + j].nn[3] = stoi(buff);
						sort(e[i + j].nn.begin(), e[i + j].nn.end());

						for (int k = 0; k <= 3; k++) {
							tmp.nn[0] = e[i + j].nn[(k - k % 3) / 3];
							tmp.nn[1] = e[i + j].nn[pow(2, (k - k % 2) / 2)];
							tmp.nn[2] = e[i + j].nn[(k + 8 - ((k + 8) % 3)) / 3];
							
							int counter = 0;
							for (int m = 0; m < f.size(); m++) {
								if (tmp.nn!= f[m].nn) {
									counter++;
								}
							}
							if (counter ==f.size())
								f.push_back(tmp);
						}
					}
					i += numb - 1;
				}
			}
		}
	}

	int counter = 0;
	for (int i = 1; i < f.size(); i++) {
		for (int j = 0; j < bf.size(); j++) {
			if (f[i].nn == bf[j].nn) {
				f[i].type = 1;
				counter++;
				break;
			}
			else
				f[i].type = 0;
		}
	}
}

//
//														  ?????????? ?????? ??????(?????????? ?????, ??????, ???????)
//
void CMesh::Adjacent() {
	CFace tmp;
	for (int i = 621; i < e.size(); i++) {
		for (int j = 1; j < f.size(); j++) {
			for (int k = 0; k <= 3; k++) {
				tmp = f[j];
				tmp.nn.push_back(e[i].nn[k]);
				sort(tmp.nn.begin(), tmp.nn.end());

				if (tmp.nn == e[i].nn) {
					e[i].fn.push_back(j);
					f[j].ne.push_back(i);
					tmp.nn.resize(3);
				}
			}
		}
	}

	for (int i = 621; i < e.size(); i++) {
		for (int j = 0; j < e[i].fn.size(); j++) {
			for (int k = 0; k < f[e[i].fn[j]].ne.size(); k++) {
				if (f[e[i].fn[j]].ne[k] != i) {
					e[i].ad.push_back(f[e[i].fn[j]].ne[k]);
				}
				
			}
		}
	}
}

void CMesh::Geometry() {
	for (int i = 621; i < e.size(); i++) {
		double** det;
		det = new double* [3];
		for (int j = 0; j < 3; j++)
			det[j] = new double[3];
		for (int k = 0; k < 3; k++) {
			det[k][0] = (n[e[i].nn[k + 1]].x - n[e[i].nn[0]].x);
			det[k][1] = (n[e[i].nn[k + 1]].y - n[e[i].nn[0]].y);
			det[k][2] = (n[e[i].nn[k + 1]].z - n[e[i].nn[0]].z);
		}
		e[i].volume = 1.0 / 6.0 * fabs((det[0][0] * (det[1][1] * det[2][2] - det[1][2] * det[2][1])) -
			(det[1][0] * (det[0][1] * det[2][2] - det[0][2] * det[2][1])) +
			(det[2][0] * (det[0][1] * det[1][2] - det[0][2] * det[1][1])));
		
		for (int k = 0; k < 4; k++) {
			e[i].Center.x += n[e[i].nn[k]].x/4;
			e[i].Center.y += n[e[i].nn[k]].y/4;
			e[i].Center.z += n[e[i].nn[k]].z/4;
		}

		for (int i = 0; i < 3; i++)
			delete[] det[i];
		delete[] det;
	}

	for (int i = 0; i < f.size(); i++) {
		double** det;
		det = new double* [3];
		for (int j = 0; j < 3; j++)
			det[j] = new double[2];
		for (int k = 0; k < 2; k++) {
			det[0][k] = (n[f[i].nn[k + 1]].x - n[f[i].nn[0]].x);
			det[1][k] = (n[f[i].nn[k + 1]].y - n[f[i].nn[0]].y);
			det[2][k] = (n[f[i].nn[k + 1]].z - n[f[i].nn[0]].z);
		}

		f[i].Normal.x = det[1][0] * det[2][1] - det[1][1] * det[2][0];
		f[i].Normal.y = det[0][0] * det[2][1] - det[2][0] * det[0][1];
		f[i].Normal.z = det[0][0] * det[1][1] - det[1][0] * det[0][1]; 
		f[i].Area =sqrt(pow(f[i].Normal.x, 2)+
						pow(f[i].Normal.y, 2)+
						pow(f[i].Normal.z, 2));

		f[i].Normal.x/= pow(f[i].Area, 0.5);
		f[i].Normal.y/= pow(f[i].Area, 0.5);
		f[i].Normal.z/= pow(f[i].Area, 0.5);

		for (int k = 0; k < 3; k++) {
			f[i].Center.x += n[f[i].nn[k]].x / 3;
			f[i].Center.y += n[f[i].nn[k]].y / 3;
			f[i].Center.z += n[f[i].nn[k]].z / 3;
		}
	}
}
