#include "algo.h"

using namespace std;

Algo::Algo(){
	for(int i = 0; i < 128; i++){
		placed[i] = false;
		name[i] = "";
	}
	nodes = 0;
	inputs = 0;
	names = 0;
}

short Algo::getnummer(string s){
	for(int i = 0; i <= names; i++){
		if(s.compare(name[i]) == 0){
			return i;
		}
	}
	name[names] = s;
	names++;
	return names - 1;
}

string Algo::getname(short a){
	return name[a];
}

void Algo::test(){
	short a = getnummer("blaba1");
	short b = getnummer("test 2");
	short c = getnummer("ding 3");

	cout << getname(a) << getname(b) << getname(c) << endl;
}

void Algo::reset(){
	for(int i = 0; i < 128; i++){
		placed[i] = false;
		x[i] = 0;
		y[i] = 0;
		name[i] = "";
	}
	for(int i = 0; i < 384; i++){
		input[i] = 0;
	} 
	nodes = 0;
	inputs = 0;	
	names = 0;
}

short Algo::aantalnodes(){
	return nodes;
}

void Algo::print(short a){
	for(int i = 0; i < a; i++){
		cout << i << "\t" << x[i] << "\t" << y[i] << endl;
	}
	cout << endl;
}

void Algo::calc(){
	//double size = input.length;
	double dx = 0;
	double dy = 0;
	double dr = 0;
	double r  = 0;

	for(int i = 0; i < inputs; i++){
		if(input[i * 3] > 2){
			dx = x[input[i * 3]] - x[input[i * 3 + 1]];
			dy = y[input[i * 3]] - y[input[i * 3 + 1]];
			r  = sqrt((dx * dx) + (dy * dy));
			dr = input[i * 3 + 2] / r;
			//dx = (x[input[i][1]] + (dx * dr));
			//dy = (y[input[i][1]] + (dy * dr));
			if(input[i * 3 + 2] > r){
				if(dx < 0){x[input[i * 3]]--;}
				if(dx > 0){x[input[i * 3]]++;}
				if(dy < 0){y[input[i * 3]]--;}
				if(dy > 0){y[input[i * 3]]++;}
			}

			if(input[i * 3 + 2] < r){
				if(dx < 0){x[input[i * 3]]++;}
				if(dx > 0){x[input[i * 3]]--;}
				if(dy < 0){y[input[i * 3]]++;}
				if(dy > 0){y[input[i * 3]]--;}
			}
		}

	}

}

void Algo::addinput(short a, short b, short c){
	input[inputs * 3] = a;
	input[inputs * 3 + 1] = b;
	input[inputs * 3 + 2] = c;
	inputs++;
}

void Algo::numberofnodes(short num){
	nodes = num;
}

void Algo::placenodes(){
	short templenght = 0;
	short templist[128];
	short tempstre[128];
	short sizepath;
	short lowest = 200;
	short lowest_radius;
	short resultx;
	short resulty;
	short minimal_devi = 1000;

	for(int n = 3; n < nodes; n++){
		//cout  << "node cyclus: " << n << "\t inputs: "<< inputs << endl;
		lowest = 200;
		//lijst maken met nodes die verbonden zijn met de node in onderzoek en die geplaatst zijn
		templenght = 0;
		for(int i = 0; i < inputs; i++){
			//cout << "inputplaats: " << i << "\tdata in plaats: " << input[i * 3 + 1] << "\tradius: " << input[i * 3 + 2] << endl;
			if(input[i * 3] == n){
				if(placed[input[i * 3 + 1]]){
					templist[templenght] = input[i * 3 + 1];
					tempstre[templenght] = input[i * 3 + 2];
					templenght++;
				}
			}
		}
		//zoeken naar laagste node in de lijst
		for(int i = 0; i < templenght; i++){
			if(templist[i] < lowest) {
				lowest = templist[i];
				lowest_radius = tempstre[i];
			}
		}
		//path maken
		//cout << "voor make path\n";
		sizepath = makepath(lowest, lowest_radius);
		//cout << "na make path\n";
		minimal_devi = 1000;
		for(int i = 0; i < sizepath; i++){
			short test = 0;
			
			for(int list = 0; list < templenght; list++){
				short xtrans = path[i * 2] - x[templist[list]];
				short ytrans = path[i * 2 + 1] - y[templist[list]];
				short afstand = sqrt(xtrans * xtrans + ytrans * ytrans);
				test += delta(tempstre[list], afstand); 
				//cout << templist[list] << "\t" << afstand << "\t" << delta(tempstre[list], afstand) << "\t" << tempstre[list] << endl;
			}
			if(test < minimal_devi){
				resultx = path[i * 2];
				resulty = path[i * 2 + 1];
				minimal_devi = test;
				//cout << test << endl;
			}
		}
		// klaar met path scannen
		x[n] = resultx;
		y[n] = resulty;
		placed[n] = true;
		//setnode(n, resultx, resultx);
		//print(4);
		//cout << "in placenodes n en nodes" << n << " " << nodes << endl;
	}
}

short Algo::delta(short a, short b){
	if(a == b) return 0;
	if(a < b) return b - a;
	else return a - b;
}

void Algo::setnode(short n, double xas, double yas){
	x[n] = xas;
	y[n] = yas;
	placed[n] = true;
}

short Algo::makepath(short node, double radius){
	bool live = true;
	short locx = 0;
	short locy = radius;
	short counter = 0;
	short tempcounter = 0;
	double temprad = radius * radius;

	//cout << "node: " << node << "\t radius: " << radius << endl;

	path[0] = 0;
	path[1] = radius;
	counter++;

	while(live){

		while(true){
			if(temprad >= (locx + 1) * (locx + 1) + locy * locy){
				locx++;
				path[counter * 2] = locx;
				path[counter * 2 + 1] = locy;
				break;
			}
			if(temprad >= (locx + 1) * (locx + 1) + (locy - 1) * (locy - 1)){
				locx++;
				locy--;
				path[counter * 2] = locx;
				path[counter * 2 + 1] = locy;
				break;
			}
			if(temprad >= locx * locx + (locy - 1) * (locy - 1)){
				locy--;
				path[counter * 2] = locx;
				path[counter * 2 + 1] = locy;
				break;
			}
		}
		counter++;
		if(locy <= 0) break;
	}
	tempcounter = counter;
	
	for(int c = 0; c < tempcounter; c++){
		path[counter * 2] = path[c * 2];
		path[counter * 2 + 1] = -path[c * 2 + 1];
		counter++;
	}
	for(int c = 0; c < tempcounter; c++){
		path[counter * 2] = -path[c * 2];
		path[counter * 2 + 1] = -path[c * 2 + 1];
		counter++;
	}
	for(int c = 0; c < tempcounter; c++){
		path[counter * 2] = -path[c * 2];
		path[counter * 2 + 1] = path[c * 2 + 1];
		counter++;
	}
	
	for(int c = 0; c < counter; c++){
		path[c* 2] += x[node];
		path[c * 2 + 1] += y[node];
	}
	return counter;
}

naar_gui Algo::bereken(vaste_nodes data_vast, vector<van_nodes> data_input){
	short size = data_input.size();
	reset();
	
	setnode(getnummer(data_vast.a.mac),data_vast.a.x, data_vast.a.y);
	setnode(getnummer(data_vast.b.mac),data_vast.b.x, data_vast.b.y);
	setnode(getnummer(data_vast.c.mac),data_vast.c.x, data_vast.c.y);

	for(int i = 0; i < size; i++){
		addinput(getnummer(data_input[i].mac_source),getnummer(data_input[i].mac_destination),data_input[i].power);
	}

	numberofnodes(size + 3);

	placenodes();

	for(int i = 0; i < 100; i++){
		calc();
	}
	naar_gui output;
	vector<cor_gui> voor_xeny(names); 
	// beeld uitwerken om met de gui samen te werken
	short maxx = -1000;
	short minx = 1000;
	short maxy = -1000;
	short miny = 1000;

	for(int i = 0; i < names; i++){
		if(maxx < x[i]) maxx = x[i];
		if(minx > x[i]) minx = x[i];
		if(maxy < y[i]) maxy = y[i];
		if(miny > y[i]) miny = y[i];
	}
	double difx = 200.0 / (maxx - minx);
	double dify = 200.0 / (maxy - miny);
	//cout << difx << "\t" << dify << endl;

	for(int i = 0; i < names; i++){
		voor_xeny[i].set(name[i], (x[i] - minx) * difx, (y[i] - miny) * dify);
	}
	
	output.number_of_nodes = names;
	output.xeny = voor_xeny;
	return output;
}
