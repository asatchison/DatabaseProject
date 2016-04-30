#include <iostream>
#include "Student.h"

using namespace std;

Student::Student()
{
  ID = 0;
  name = "";
  grade = "";
  major = "";
  GPA = 0.0;
  Advisor = 0;
}

Student::Student(int id)
{
  ID = id;
  name = "";
  grade = "";
  major = "";
  GPA = 0.0;
  Advisor = 0;
}

void Student::serialize(ofstream &ostream)
{
  ostream << ID << "\n";
  ostream << name << "\n";
  ostream << grade << "\n";
  ostream << major << "\n";
  ostream << GPA << "\n";
  ostream << Advisor << "\n";
}

Student::Student(int id, string n, string g, string m, double gpa, int A)
{
  ID = id;
  name = n;
  grade = g;
  major = m;
  GPA = gpa;
  Advisor = A;
}

void Student::print()
{
  cout<<"Name: "<<name<<endl;
  cout<<"ID: "<<ID<<endl;
  cout<<"Grade: "<<grade<<endl;
  cout<<"Major: "<<major<<endl;
  cout<<"GPA: "<<GPA<<endl;
  cout<<"Advisor ID: "<<Advisor<<endl;
}
