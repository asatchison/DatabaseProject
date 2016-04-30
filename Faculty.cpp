#include <iostream>
#include "Faculty.h"

using namespace std;

Faculty::Faculty()
{

}

Faculty::Faculty(int id, string n, string l, string d)
{
  ID = id;
  name = n;
  level = l;
  department = d;
}

void Faculty::serialize(ofstream &ostream)
{
    ostream << "*****" << "\n";
    ostream << ID << "\n";
		ostream << name << "\n";
		ostream << level << "\n";
		ostream << department << "\n";
    for(int i = 0; i<students.getSize(); i++)
    {
        ostream<<*(students.getAt(i))<<endl;
    }
		ostream << "*****" << "\n";
}

void Faculty::addAdvisee(int StudentID)
{
  students.insertFront(StudentID);
}

void Faculty::removeAdvisee(int StudentID)
{
  students.deleteNode(StudentID);
}

void Faculty::print()
{
  cout<<"Name: "<<name<<endl;
  cout<<"ID: "<<ID<<endl;
  cout<<"Level: "<<level<<endl;
  cout<<"Department: "<<department<<endl;
  cout<<students.getSize()<<" advisee(s)"<<endl;
  cout<<"Students: "<<endl;

  for(int i = 0; i<students.getSize(); i++)
  {
      cout<<*(students.getAt(i))<<endl;
  }
}
