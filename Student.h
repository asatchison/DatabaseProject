using namespace std;
#include <iostream>
#include <fstream>

class Student{

public:
  Student();
  Student(int id);
  Student(int id, string n, string g, string m, double gpa, int A);
  int ID;
  string name;
  string grade;
  string major;
  double GPA;
  int Advisor;

  void serialize(ofstream &ostream);
  void print();
};
