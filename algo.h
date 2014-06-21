#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

struct van_nodes{
	string mac_source;
	string mac_destination;
	short power;
	void set(string a, string b, short c){
		mac_source = a;
		mac_destination = b;
		power = c;
	}
};

struct cor_gui{
	string mac;
	short x;
	short y;
	void set(string a, short b, short c){
		mac = a;
		x = b;
		y = c;
	}
};

struct naar_gui{
	short number_of_nodes;
	vector <cor_gui> xeny;
};

struct vaste_nodes{
	cor_gui a;
	cor_gui b;
	cor_gui c;
};

class Algo{
	bool placed[128];
	double x[128];
	double y[128];
	short nodes;
	short inputs;
	short input[384];
	short path[5096];
	short names;
	string name[128];


	void calc();
	void placenodes();
	short makepath(short, double);
	short delta(short, short);
	void reset();
	short getnummer(string);
	string getname(short);

public:

	short aantalnodes();
	void setnode(short,double,double);
	void addinput(short, short, short);
	void print(short);
	void numberofnodes(short);
	naar_gui bereken(vaste_nodes,vector<van_nodes>);
	void test(); // aleen voor data base
	Algo();


};
