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
//string N;
//int S;
//int start;
void OutEntry(){
	for(auto e : directory){
		cout << e.Name << "  " << e.Size << "  " << e.Start << "  " << e.Clusters << endl;
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

void AddFAT(string N, int S){
file temp(N, S, firstAVA());
directory.push_back(temp);
//FAT[temp.Start] = -1;
int F=temp.Start;
int Sec=nextAVA();
//cout << f << endl;
for(int i = 0; i <temp.Clusters; i++)
{ if (i == (temp.Clusters-1)){FAT[F]=-1; }
}
}
void OutFAT(){
	for (int j=0; j<OUT; j++){
//for (int i = 0; i < DIRE; i++
cout << FAT[j] << "  ";
if (((j+1)%12)==0) {cout << endl;}
	}
}
//void OutClusters(file Entry) {
//	int next = FAT[file.Start];
//	for (int i = 0; i>file.Clusters; i++) {
//	cout << next;
//	next = FAT[next];
//	}
//}
int main(){
OutFAT();
//cout << firstAVA();
AddFAT("..",0);
OutEntry();
OutFAT();
return 0;

}
