#include <iostream>
#include "table.hpp"
#include <fstream>
#include <array>
#include <list>
#include <iterator>
#include <algorithm>
#define BLOCK 512
#define DIRE 12
#define OUT 12
using std::list;
using std::cout;
using std::endl;
using std::array;
list<file> directory;
int FAT[400];
string SName; // for search name so can cerror
//int S;
//int start;
void OutClusters(file Entry) {
	int next = FAT[Entry.Start];
	cout << "      clusters: ";
	cout << Entry.Start;
	for (int i = 1; i<Entry.Clusters; i++) {
	cout << next;
	next = FAT[next];
	}
	cout << endl;
}
void OutEntry(){
	for(auto e : directory){
		cout << e.Name << "  " << e.Size << "  " << e.Start << "  " << e.Clusters;
OutClusters(e);
	}
	cout << "here";
}

int firstAVA(){
	int i = 0;
	while (FAT[i] != 0){
		i++;}
	return i;
}

int nextAVA(){
	int f = firstAVA();
	f++;
	while(FAT[f] != 0) {f++;}
	return f;
}

file Search(string N){
	int spot = 0;
	SName = N;
	for(auto e : directory){
		if (e.Name == N){ return e;}
		spot++;
	}
return file();
}
void Delete(file e){
auto spot=directory.begin();
for (auto &D : directory){
	if( e.Name == D.Name){
		directory.erase(spot);
			return;
	cout << "match";
	}
	spot++;
}
}
void RemFAT(file e){
	if (e.Name == " ") {
		cout << endl << "File " << SName << " not found." <<endl;
		return;}
	int next=e.Start;
	if (next == -1) {
		FAT[e.Start] = 0;
		Delete(e);
	return;
	}
	int cur=next;
	cout << endl << cur << endl;
	for (int i = 0; i<e.Clusters; i++) {
if (cur == -1) {
	cout << "off by one";
}
	next = FAT[next];
	FAT[cur] = 0;
	cur=next;
	}
Delete(e);
}



void AddFAT(string N, int S){
file temp(N, S, firstAVA());
directory.push_back(temp);
int F=temp.Start;
int Sec=nextAVA();
for(int i = 0; i <temp.Clusters; i++)
{ if (i == (temp.Clusters-1)){FAT[F]=-1; }
	else {
		FAT[F]=Sec;
 F=firstAVA();
Sec=nextAVA();
	}
}
}


void OutFAT(){
	cout << endl;
	for (int j=0; j<OUT; j++){
//for (int i = 0; i < DIRE; i++
cout << FAT[j] << "  ";
if (((j+1)%12)==0) {cout << endl;}
	}
	cout << endl;
}
int main(){
//OutFAT();
//cout << firstAVA();
AddFAT("..",0);
AddFAT("first", 512);
AddFAT("second", 500);
AddFAT("third", 2000);
OutEntry();
OutFAT();
 RemFAT(Search("second"));
//OutFAT();
 AddFAT("Fourth", 1500);
//RemFAT(Search("four"));
OutFAT();
//OutEntry();
//cout << "here";
RemFAT(Search("third"));
OutFAT();
AddFAT("five", 5);
OutFAT();
OutEntry();
return 0;


}
