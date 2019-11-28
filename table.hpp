#include <vector>
#include <string>
#include <iostream>
#define BLOCK 512
using std::string;
class file{
	string Name;
	int Size;
	int Start;
int Clusters;
	file(); //default constructor
	file(string N, int S, int start);
};
	

