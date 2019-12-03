#include "table.hpp"
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#define BLOCK 512
#define DIRE 12
#define OUT 24
#define OFTEN 6
using std::array;
using std::cout;
using std::endl;
using std::ifstream;
using std::list;
using std::string;
list<file> directory;
int FAT[400];
string SName; // for search name so can cerror

/**
 * Function Outclusters
 *
 * Use outputs the cluster of each entry.
 *
 * Arguments: Entry: derectory entry
 *
 * returns: none
 */

void OutClusters(file Entry) {
  int next = FAT[Entry.Start];
  cout << "      clusters: ";
  cout << Entry.Start;
  for (int i = 1; i < Entry.Clusters; i++) {
    cout << next;
    next = FAT[next];
  }
  cout << endl;
}
/**
 * function outentry
 *
 * use Output the data of each directory entry
 *
 * Arguments None
 *
 * REturn none
 */
void OutEntry() {
  for (auto e : directory) {
    cout << e.Name << "  " << e.Size << "  " << e.Start << "  " << e.Clusters;
    OutClusters(e);
  }
}

/**
 * function firstAVA
 *
 * use finde first 0 in FAT
 *
 * arguments none
 *
 * return postion of first 0
 */
int firstAVA() {
  int i = 0;
  while (FAT[i] != 0) {
    i++;
  }
  return i;
}

/**
 * function nextAVA
 *
 * use finde second 0 in FAT
 *
 * arguments none
 *
 * return postion of second 0
 */
int nextAVA() {
  int f = firstAVA();
  f++;
  while (FAT[f] != 0) {
    f++;
  }
  return f;
}

/**
 * function Search
 *
 * use look for a file matintch a give name
 *
 * arguments name string
 *
 * return the file
 */
file Search(string N) {
  int spot = 0;
  SName = N;
  for (auto e : directory) {
    if (e.Name == N) {
      return e;
    }
    spot++;
  }
  return file();
}
/**
 * function Delete
 *
 * use Delete a given file from the directory list
 *
 * arguments the file object to be deleted
 *
 * return none
 */
void Delete(file e) {
  auto spot = directory.begin();
  for (auto &D : directory) {
    if (e.Name == D.Name) {
      directory.erase(spot);
      //  return;
      cout << "match";
      return;
    }
    spot++;
  }
}

/**
 * function RemFat
 *
 * use Set to zero all clusters used by file
 *
 * arguments the file object
 *
 * return none
 */
void RemFAT(file e) {
  if (e.Name == " ") {
    cout << endl << "File " << SName << " not found." << endl;
    return;
  }
  int next = e.Start;
  int cur = next;//postion of next thing to remove
  for (int i = 1; i <= e.Clusters; i++) {
    if (cur == -1) {
      cout << "off by one";
    }
    next = FAT[next];
    FAT[cur] = 0;
    cur = next;
  }
  Delete(e);
}
/**
 * function OutFat
 *
 * use Output a Defined first part of FAR
 *
 * arguments none
 *
 * return none
 */
void OutFAT() {
  cout << endl;
  for (int j = 0; j < OUT; j++) {
    // for (int i = 0; i < DIRE; i++
    cout << FAT[j] << "  ";
    if (((j + 1) % 12) == 0) {
      cout << endl;
    }
  }
  cout << endl;
}

/**
 * function AddFat
 *
 * use add a file with a given name and size to directory, and fill in FAT for it
 *
 * arguments 1) The name string
 * 		2) the size int
 *
 * return none
 */
void AddFAT(string N, int S) {
  file temp(N, S, firstAVA());
  if (temp.Start == 0) {
    directory.push_front(temp);
  } // replaces directory block
  else {
    directory.push_back(temp);
  }
  int F = temp.Start;
  int Sec = nextAVA();
  for (int i = 0; i < temp.Clusters; i++) {
    if (i == (temp.Clusters - 1)) {
      FAT[F] = -1;
    } else {
      FAT[F] = Sec;
      F = firstAVA();
      Sec = nextAVA();
    }
  }
}

/**
 * function CopyFat
 *
 * use add a new file to directory and FAT that is the same size as a given file but new name
 *
 * arguments N, the string name of the selected fiel
 * 		R, the string name for the new file
 *
 * return none
 */
void CopyFAT(string N, string R) {
  file e = Search(N);
  AddFAT(R, e.Size);
}

/**
 * function AddDB
 *
 * use See if the Database file needs a new block, and if change the database to use one more cluster
 *
 * arguments The database file object
 *
 * return none
 */
void AddDB(file d) {
  int a = directory.size() + 1;
  int b = DIRE * d.Clusters; // casting signed an unsigned to ints
  if (a > b) {
    string N = d.Name;
    int S = d.Size + BLOCK;
    RemFAT(Search(N));
    OutFAT();
    AddFAT(N, S);

    return;
  }
}

/**
 * function Name
 *
 * use Rename a file in directory
 *
 * arguments O, the name of the origianl
 * 		N, The new name
 *
 * return none
 */
void Name(string O, string N) {
  auto spot = directory.begin();
  for (auto &D : directory) {
    if (O == D.Name) {
      D.Name = N;
      return;
    }
    spot++;
  }
}

/**
 * function EditFAT
 *
 * use change the size of an existing file
 *
 * arguments the original file object
 * 		the new size int
 *
 * return none
 */
void EditFAT(file e, int s) {
  string n = e.Name;
  AddFAT("TEMP", s);
  RemFAT(e);
  Name("TEMP", n);
}

int main() {
  ifstream Infile;
  Infile.open("testdata");
  char Case;
  string Name, NewName;
  int Size;
  AddFAT(".", 512);
  AddFAT("..", 0);
  int time = 0;
  while (Infile >> Case)
    if (time % OFTEN == 0) {
      OutFAT();
      OutEntry();
    }
  switch (Case) {
  case 'N':
    AddDB(Search("."));
    Infile >> Name >> Size;
    AddFAT(Name, Size);

  case 'C':
    Infile >> Name >> NewName;
    AddDB(Search("."));
    CopyFAT(Name, NewName);
  case 'D':
    Infile >> Name;
    RemFAT(Search(Name));
  case 'M':
    Infile >> Name >> Size;
    EditFAT(Search(Name), Size);
  case 'R':
    Infile >> Name >> NewName;
    Name(Name, NewName);
  case '?':
    return 0;
  }
  time++;
}
