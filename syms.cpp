// map::lower_bound/upper_bound
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool fncomp (int lhs, int rhs) {return lhs>rhs;}

class Symbol
{
public:
	Symbol() : name(""), size(0),sourceline("") {}
	Symbol(string name, int size, string sourceline) : name(name), size(size), sourceline(sourceline) {}
	string name;
	int size;
	string sourceline;
};

int main (int argc, char** argv)
{
  if (argc != 3) {
	cout << "Usage: " << argv[0] << " symbol-file hex_address" << endl;
	return 1;
  }
  ifstream ifs(argv[1]);
  
  std::map<int,Symbol, bool(*)(int,int)> symmap(&fncomp);
  std::map<int, Symbol>::iterator itlow,itup;

  while (ifs)
  {
    string s;
  	int addr;
  	int size;
  	string name;
  	string line;
    if (!getline( ifs, s )) break;

    istringstream ss( s );
  	ss >> std::hex >> addr >> size;
  	ss >> name;
  	ss >> line;

	Symbol sym(name, size, line);
	symmap[addr] = sym;
  }
  ifs.close();
  
  for (std::map<int,Symbol>::iterator it=symmap.begin(); it!=symmap.end(); ++it)
    std::cout << std::hex << it->first << " => " << it->second.name << '\n';

  int addr;
  istringstream ss(argv[2]);
  ss >> std::hex >> addr;

  itup=symmap.lower_bound (addr);   // itup points to e (not d!)

  cout << std::hex << itup->first << " " << itup->second.name << endl;



  return 0;
}
