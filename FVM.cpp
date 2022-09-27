#include <iostream>
#include <math.h>
#include "CMesh.h"
#include <ctime>

using namespace std;

int main()
{
	CMesh D("setka.txt");
	D.Adjacent();
	D.Geometry();
	//D.e;
	//cout << D.f.size() << endl;
	//cout << D.f[D.f.size()-1].nn[0] << " " << D.f[D.f.size()-1].nn[1] << " " << D.f[D.f.size()-1].nn[2] << " " << endl;
	
	/*for (int i = 0; i < D.f.size(); i++) {
		cout << i<<" " << D.f[i].nn[0] << " " << D.f[i].nn[1] << " " << D.bf[i].nn[2] << " "<<endl;
	}*/

	//cout << endl << endl<<endl<<endl<<endl;

	/*for (int i = 1; i < D.f.size(); i++) {
		cout << i << " ";
		for (int j=0; j< D.f[i].ne.size(); j++)
			cout <<" "<< D.f[i].ne[j] << " ";
		cout << endl;
	}*/

	//for (int i = 0; i < 540; i++)
		//cout <<D.f[i].nn[0] << " " << D.f[i].nn[1] << " " << " " << D.f[i].nn[2] << " " << endl;
	/*for (int i = 621; i <= 1745; i++) {
		cout << "Cell number:" << i << endl;;
		for (int j = 0; j <= 3; j++)
			cout << D.e[i].fn[j] << " ";
		cout << endl;
		cout << "NUmbers of Nodes" << endl;
		for (int k = 0; k <= 3; k++) {
			cout << D.e[i].nn[k] << " ";
		}
		cout << endl;


	}/*

	for (int i = 1106; i <=1109; i++) {
		cout << "Nodes of faces" << endl;
		for (int j=0; j<=2; j++)
			cout << D.f[i].nn[j] << " ";
		cout << endl;
	}
	for (int j = 0; j <= 2; j++)
		cout << D.f[1106].nn[j] << " ";
	cout << endl;

	*/
	//for (int i = 621; i <= 1745; i++)
		//cout << D.e[i].number<<" "<<D.e[i].nn[0] << " " << D.e[i].nn[1] << " " << D.e[i].nn[2] << " " << D.e[i].nn[3]  << endl;
	//cout << endl << endl << endl << endl << endl << endl << "_____________________________FACES__________________" << endl << endl << endl << endl << endl;
	/*for (int j = 0; j < D.f.size() - 1; j++) {
		cout << D.f[j].nf << " ";
		cout << D.f[j].ne << " ";
		cout << D.f[j].nn[0] << " ";
		cout << D.f[j].nn[1] << " ";
		cout << D.f[j].nn[2] << " "<<endl;
	}*/

	//cout << D.f[62].type << endl;


	//cout << sum << endl;
	for (int i = 621; i < D.e.size(); i++) {
		cout << i << " ";
		for (int j = 0; j < D.e[i].ad.size(); j++) {
			cout << D.e[i].ad[j] << " ";
		}
		cout << endl;
	}
	/*for (int i = 0; i < D.f.size(); i++) {
		cout << i << " ";
		for (int j = 0; j < D.f[i].ne.size(); j++) {
			cout << D.f[i].ne[j] << " ";
		}
		cout << endl;
	}*/
	cout<<" Time of program: " << clock() / 1000.0 <<" "<<"c."<< endl;
}

