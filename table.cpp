#include "table.hpp"
#define BLOCK 512
file::file(){
	Name = " ";
	Size = 0;
	Start = 0;
}
file::file(string N, int S, int start){
Name = N;
Size= S;
Start = start;
if (S==0){Clusters =1;} //think this only applies to the first entry (N = ..)
else if ((S%BLOCK)>0) {Clusters = (S/BLOCK) +1;}
else {Clusters = S/BLOCK;}
}
