#include <iostream>
#include "table.hpp"
#include <fstream>
#include <array>
#include <vector>
#define BLOCK 512
#define DIRE 12
using std::vector;
using std::cout;
using std::endl;
using std::array;
vector<file> directory;
int FAT[400];
string N;
int S;
int start;
//int numClusters(int F) {
  //     if (F%BLOCK>0){ return (F/BLOCK)+1;}
//return F/BLOCK;
//}
int firstAVA(){
	int i = 0;
	while (FAT[i] != 0){
		i++;}
	return i;
}
void OutFAT(){
	for (int j=0; j<252; j++){
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
cout << firstAVA();
return 0;
}
