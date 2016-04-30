#include "DoublyLL.cpp"
#include <iostream>
#include <fstream>

using namespace std;

class Faculty{

public:
  Faculty();
  Faculty(int id, string n, string l, string d);
  int ID;
  string name;
  string level;
  string department;
  DoublyLL<int> students;

  void serialize(ofstream &ostream);
  void addAdvisee(int StudentID);
  void removeAdvisee(int StudentID);
  void print();
};
