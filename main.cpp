#include <iostream>
#include "table.hpp"
#include <fstream>
#include <array>
#include <vector>
#define BLOCK 512
#define DIRE 12
#define OUT 36
using std::vector;
using std::cout;
using std::endl;
using std::array;
vector<file> directory;
int FAT[400];
string SName; // for search name so can cerror
//int S;
//int start;
void OutClusters(file Entry) {
	int next = FAT[Entry.Start];
	cout << endl << "cludters: ";
	cout << Entry.Start;
	for (int i = 1; i<Entry.Clusters; i++) {
	cout << next;
	next = FAT[next];
	}
	cout << endl;
}
void OutEntry(){
	for(auto e : directory){
		cout << e.Name << "  " << e.Size << "  " << e.Start << "  " << e.Clusters << endl;
OutClusters(e);
	}
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

		
void RemFAT(file e){
	if (e.Name == " ") {
		cout << endl << "File " << SName << " not found." <<endl;
		return;}
	int next=FAT[e.Start];
	if (next == -1) {
		FAT[e.Start] = 0;
		return;
	}
	int cur=next;
	for (int i = 0; i<e.Clusters; i++) {
//	cout << next;
if (cur == -1) {
	cout << "off by one";}
	next = FAT[next];
	FAT[cur] = 0;
	cur=next;
	}
	cout << endl;
}



void AddFAT(string N, int S){
file temp(N, S, firstAVA());
directory.push_back(temp);
//FAT[temp.Start] = -1;
int F=temp.Start;
int Sec=nextAVA();
//cout << f << endl;
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
	for (int j=0; j<OUT; j++){
//for (int i = 0; i < DIRE; i++
cout << FAT[j] << "  ";
if (((j+1)%12)==0) {cout << endl;}
	}
}
int main(){
OutFAT();
//cout << firstAVA();
AddFAT("..",0);
AddFAT("first", 512);
AddFAT("second", 500);
AddFAT("third", 2000);
OutEntry();
OutFAT();
 RemFAT(Search("second"));
OutFAT();
 AddFAT("Fourth", 1500);
//RemFAT(Search("four"));
OutFAT();
return 0;

}
