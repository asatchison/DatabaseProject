#include <iostream>
#include "Student.h"
#include "Faculty.h"
#include "BST.cpp"
#include "GenStack.cpp"



using namespace std;

int menu();
void handleOne(BST<Student> students);
void handleTwo(BST<Faculty> faculty);
void handleThree(BST<Student> students);
void handleFour(BST<Faculty> fac, int ID);
void handleFive(BST<Student> students, BST<Faculty> fac);
void handleSix(BST<Faculty> faculty, BST<Student> students);
void handleSeven(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleEight(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleNine(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleTen(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleEleven(BST<Faculty> &faculty, BST<Student> &students, int StudID, int AdvID, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleTwelve(BST<Faculty> &faculty, BST<Student> &students, int StudID, int AdvID, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleThirteen(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem);
void handleFourteen(BST<Faculty> &faculty, BST<Student> &students);
void invalidInput();


int main(int argc, char** argv)
{
  BST<Student> masterStudent;
  BST<Faculty> masterFaculty;
  GenStack<BST<Student> > studMem(5);
  GenStack<BST<Faculty> > facMem(5);

  //todo::
//   When the program starts, it should check the current directory for the existence of 2 files
// “facultyTable” and “studentTable”. These files correspond to the BSTrees containing the
// faculty and student data. If neither of these files exist, then masterFaculty and
// masterStudent should be initialized as new, empty trees. If the files do exist, then they
// should be read into the appropriate variables.

  string line;
  string name;
  int id;
  string grade;
  string major;
  double gpa;
  int a_id;
  ifstream istream ("serialization.txt");
  if (istream.is_open())
  {
    getline(istream,line);
      int numStuds = atoi(line.c_str());
      for(int i = 0; i<numStuds; i++)
      {
        getline(istream,line);
        id = atoi(line.c_str());
        getline(istream,line);
        name = line;
        getline(istream,line);
        grade = line;
        getline(istream,line);
        major = line;
        getline(istream,line);
        gpa = atof(line.c_str());
        getline(istream,line);
        a_id = atoi(line.c_str());
        Student tempStud(id,name,grade,major,gpa,a_id);
        masterStudent.insert(tempStud);
      }

    while(getline(istream,line))
    {
      if(line == "*****")
      {
        continue;
      }
      else
      {
        id = atoi(line.c_str());
        getline(istream,line);
        name = line;
        getline(istream,line);
        grade = line;
        getline(istream,line);
        major = line;

        Faculty fac(id,name,grade,major);

        masterFaculty.insert(fac);
        Faculty* temp = masterFaculty.findNode(id);

        getline(istream,line);
        while(line != "*****")
        {
          temp->addAdvisee(atoi(line.c_str()));
          getline(istream,line);
        }
      }
    }

    istream.close();
  }

  else cout << "Unable to open file";

  while(true)
  {
    int userChoice = menu();
    switch(userChoice)
    {
      case 1:
        handleOne(masterStudent);
        break;
      case 2:
        handleTwo(masterFaculty);
        break;
      case 3:
        handleThree(masterStudent);
        break;
      case 4:
        handleFour(masterFaculty, 0);
        break;
      case 5:
        handleFive(masterStudent, masterFaculty);
        break;
      case 6:
        handleSix(masterFaculty, masterStudent);
        break;
      case 7:
        handleSeven(masterFaculty, masterStudent, studMem, facMem);
        break;
      case 8:
        handleEight(masterFaculty, masterStudent, studMem, facMem);
        break;
      case 9:
        handleNine(masterFaculty, masterStudent, studMem, facMem);
        break;
      case 10:
        handleTen(masterFaculty, masterStudent, studMem, facMem);
        break;
      case 11:
        handleEleven(masterFaculty, masterStudent, 0, 0, studMem, facMem);
        break;
      case 12:
        handleTwelve(masterFaculty, masterStudent, 0, 0, studMem, facMem);
        break;
      case 13:
        handleThirteen(masterFaculty, masterStudent, studMem, facMem);
        break;
      case 14:
        handleFourteen(masterFaculty,masterStudent);
        break;
      default:
        cout<<"Incorrect Input"<<endl;
        menu();
        break;
    }
    if(userChoice == 14)
    {
      break;
    }
  }


  cout<<"boom"<<endl;
  return 1;
}

int menu()
{
  cout<<"Choose the action you would like to take: "<<endl;
  cout<<"1. Print all students and their information (sorted by ascending id #)"<<endl;
  cout<<"2. Print all faculty and their information (sorted by ascending id #)"<<endl;
  cout<<"3. Find and display student information given the students id"<<endl;
  cout<<"4. Find and display faculty information given the faculty id"<<endl;
  cout<<"5. Given a student’s id, print the name and info of their faculty advisor"<<endl;
  cout<<"6. Given a faculty id, print ALL the names and info of his/her advisees."<<endl;
  cout<<"7. Add a new student"<<endl;
  cout<<"8. Delete a student given the id"<<endl;
  cout<<"9. Add a new faculty member"<<endl;
  cout<<"10. Delete a faculty member given the id."<<endl;
  cout<<"11. Change a student’s advisor given the student id and the new faculty id."<<endl;
  cout<<"12. Remove an advisee from a faculty member given the ids"<<endl;
  cout<<"13. Rollback"<<endl;
  cout<<"14. Exit"<<endl;
  int userIn = 0;
  cin>>userIn;
  return userIn;
}

//print students
void handleOne(BST<Student> students)
{
  if(students.isEmpty()== false)
  {
    students.printTree();
  }
  else
  {
    cout<<"Add Students"<<endl;
  }
}

//print faculty
void handleTwo(BST<Faculty> faculty)
{
  if(faculty.isEmpty()==false)
  {
    faculty.printTree();
    cout<<"Add Faculty"<<endl;
  }
}

//find and display sutdent information given the students id
void handleThree(BST<Student> students)
{
  if(students.isEmpty())
  {
    cout<<"Add Students"<<endl;
  }
  else
  {
    int ID = 0;
    cout<<"Input Student ID"<<endl;
    cin>>ID;
    Student* thisStud = students.findNode(ID);
    if(thisStud != NULL)
    {
      thisStud->print();
    }
    else
    {
      cout<<"Invalid ID"<<endl;
    }
  }
}

//find and display faculty information given the faculty id
void handleFour(BST<Faculty> fac, int ID)
{
  if(faculty.isEmpty())
  {
    cout<<"Add Faculty"<<endl;
  }
  else
  {
    if(ID == 0)
    {
      cout<<"Input Faculty ID"<<endl;
      cin>>ID;
    }

    Faculty* thisFac = fac.findNode(ID);
    if(thisFac != NULL)
    {
      thisFac->print();
    }
    else
    {
      cout<<"Invalid ID"<<endl;
    }
  }
}

//Given and students id print the name and info of their faculty advisor
void handleFive(BST<Student> students, BST<Faculty> fac)
{
  if(students.isEmpty())
  {
    cout<<"Add Students"<<endl;
  }
  else
  {
    int ID = 0;
    cout<<"Input Student ID"<<endl;
    cin>>ID;
    Student* thisStud = students.findNode(ID);
    if(thisStud != NULL)
    {
      handleFour(fac,thisStud->Advisor);
    }
    else
    {
      cout<<"Invalid ID"<<endl;
    }
  }

}

//Given a faculty id print all the names and info of thier advisees
void handleSix(BST<Faculty> faculty, BST<Student> students)
{
  if(faculty.isEmpty())
  {
    cout<<"Add faculty"<<endl;
  }
  else{
    int ID = 0;
    cout<<"Input Faculty ID"<<endl;
    cin>>ID;
    Faculty* thisFac = faculty.findNode(ID);
    if(thisFac != NULL)
    {
      DoublyLL<int> studs = thisFac->students;

      for(int i = 0; i<studs.getSize(); i++)
      {
          int* ID = studs.getAt(i);
          if(ID != NULL)
          {
            Student* temp = students.findNode(*ID);
            if(temp != NULL)
            {
              cout<<"Student "<<i+1<<endl;
              temp->print();
            }
          }

      }
    }
    else
    {
      cout<<"Invalid ID"<<endl;
    }
  }

}

//Add a new student
void handleSeven(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  if(faculty.isEmpty())
  {
    cout<<"Must add faculty to advise students"<<endl;
  }
  else{
    int ID;
    string name;
    string grade;
    string major;
    double GPA;
    int A_ID;

    cout<<"Input ID"<<endl;
    cin>>ID;
    if(cin.fail())//Id is a number
    {
      cout<<"ID must be a number"<<endl;
      cin.clear();
      cin.ignore(256,'\n');
    }
    else
    {
      if(students.findNode(ID) == NULL)//studnet ID is valid
      {
        cout<<"Input Name"<<endl;
        cin>>name;
        if(cin.fail()){invalidInput();}
        else
        {
          cout<<"Input Grade Level"<<endl;
          cin>>grade;
          if(cin.fail()){invalidInput();}
          else
          {
            cout<<"Input Major"<<endl;
            cin>>major;
            if(cin.fail()){invalidInput();}
            else
            {
              cout<<"Input GPA"<<endl;
              cin>>GPA;
              if(cin.fail()){invalidInput();}
              else
              {
                cout<<"Input Advisor ID"<<endl;
                cin>>A_ID;
                if(cin.fail()){invalidInput();}
                else
                {
                  if(faculty.findNode(A_ID) != NULL)//faculty exists
                  {
                    Student thisStud(ID,name,grade,major,GPA,A_ID);

                    if(students.isEmpty() == false)
                    {
                      studMem.push(students);
                    }
                    if(faculty.isEmpty()==false)
                    {
                      facMem.push(faculty);
                    }

                    students.insert(thisStud);
                    Faculty* temp = faculty.findNode(A_ID);
                    temp->students.insertFront(ID);
                  }
                }
              }
            }
          }
        }
      }
    }

  }

}

//Delete a student given the id
void handleEight(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  int ID;
  int AdvisorID;
  bool success = false;
  cout<<"Enter Student ID"<<endl;
  cin>>ID;
  Student* delStud = students.findNode(ID);
  if(delStud != NULL)
  {
    if(students.isEmpty() == false)
    {
      studMem.push(students);
    }
    if(faculty.isEmpty()==false)
    {
      facMem.push(faculty);
    }

    AdvisorID = delStud->Advisor;
    students.deleteNode(*delStud);

    Faculty* fac = faculty.findNode(AdvisorID);
    fac->removeAdvisee(ID);
  }
  else{
    cout<<"Student not found"<<endl;
  }
}

//Add a new faculty member
void handleNine(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  int ID;
  string name;
  string level;
  string department;

  cout<<"Input Faculty ID:"<<endl;
  cin>>ID;
  if(cin.fail()){invalidInput();}
  else
  {
    cout<<"Input Faculty Name:"<<endl;
    cin>>name;
    if(cin.fail()){invalidInput();}
    else
    {
      cout<<"Input Faculty Level:"<<endl;
      cin>>level;
      if(cin.fail()){invalidInput();}
      else
      {
        cout<<"Input Faculty Department:"<<endl;
        cin>>department;
        if(cin.fail()){invalidInput();}
        else
        {
          if(students.isEmpty() == false)
          {
            studMem.push(students);
          }
          if(faculty.isEmpty()==false)
          {
            facMem.push(faculty);
          }
          Faculty newFac(ID,name,level,department);
          faculty.insert(newFac);
        }
      }
    }
  }

}

// Delete a faculty member given the id
void handleTen(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  int ID;
  int A_ID;
  cout<<"Input ID of faculty to delete: "<<endl;
  cin>>ID;

  Faculty* temp = faculty.findNode(ID);
  if(temp != NULL)
  {
    if(students.isEmpty() == false)
    {
      studMem.push(students);
    }
    if(faculty.isEmpty()==false)
    {
      facMem.push(faculty);
    }

    if(temp->students.isEmpty() == false)
    {
      DoublyLL<int> studs = temp->students;

      for(int i = 0; i<studs.getSize(); i++)
      {
          int* ID = studs.getAt(i);
          if(ID != NULL)
          {
            Student* temp = students.findNode(*ID);
            if(temp != NULL)
            {
              cout<<"Must assign new advisor for student #"<<temp->ID<<endl;
              cout<<"Input ID of new Advisor"<<endl;
              cin>>A_ID;
              cout<<"do 11 for student #"<<temp->ID<<endl;
              handleEleven(faculty, students, *ID, A_ID, studMem, facMem);
              cout<<"did 11 for student #"<<temp->ID<<endl;
            }
          }

      }
    }
    faculty.deleteNode(*temp);
  }
  else{
    cout<<"Invalid input"<<endl;
  }
}
// Change a student’s advisor given the student id and the new faculty id.
void handleEleven(BST<Faculty> &faculty, BST<Student> &students, int StudID, int AdvID, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  if(students.isEmpty())
  {
    cout<<"Add students"<<endl;
  }
  else{
    bool outsideCall = false;
    if(StudID == 0 && AdvID == 0)
    {
      cout<<"Input Student ID"<<endl;
      cin>>StudID;
      cout<<"Input New Faculty ID"<<endl;
      cin>>AdvID;
      outsideCall = true;
    }

    Faculty* testFac = faculty.findNode(AdvID);
    if(testFac != NULL)
    {
      Student* thisStud = students.findNode(StudID);
      if(thisStud != NULL)
      {
        if(outsideCall == false)
        {
          if(students.isEmpty() == false)
          {
            studMem.push(students);
          }
          if(faculty.isEmpty()==false)
          {
            facMem.push(faculty);
          }
        }
        int removeAdv = thisStud->Advisor;
        Faculty* tempFac = faculty.findNode(removeAdv);
        thisStud->Advisor = AdvID;
        testFac->addAdvisee(StudID);
        tempFac->removeAdvisee(StudID);
      }
    }
  }

}
// Remove an advisee from a faculty member given the ids
void handleTwelve(BST<Faculty> &faculty, BST<Student> &students, int StudID, int AdvID, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  if(StudID == 0 && AdvID == 0)
  {
    cout<<"Input Student ID number:"<<endl;
    cin>>StudID;
    cout<<"Input Advisor ID number:"<<endl;
    cin>>AdvID;
  }
    Student* testStud = students.findNode(StudID);
    Faculty* fac = faculty.findNode(AdvID);
    if(fac != NULL && testStud != NULL)
    {
      if(students.isEmpty() == false)
      {
        studMem.push(students);
      }
      if(faculty.isEmpty()==false)
      {
        facMem.push(faculty);
      }
      fac->removeAdvisee(StudID);
      cout<<"Student #"<<StudID<<"needs a new Advisor"<<endl;
      cout<<"Input Advisor ID number:"<<endl;
      cin>>AdvID;
      fac = faculty.findNode(AdvID);
      if(cin.fail() || fac == NULL)
      {
        cout<<"Invalid Input"<<endl;
        cin.clear();
        cin.ignore(256,'\n');
      }
      else
      {
        handleEleven(faculty, students, StudID, AdvID, studMem, facMem);
      }
    }
    else
    {
      cout<<"Invalid input"<<endl;
    }
}
// Rollback
void handleThirteen(BST<Faculty> &faculty, BST<Student> &students, GenStack<BST<Student> > &studMem, GenStack<BST<Faculty> > &facMem)
{
  if(facMem.isEmpty() == false)
  {
    faculty = facMem.pop();
  }
  if(studMem.isEmpty() == false)
  {
    students = studMem.pop();
  }
}
// Exit
void handleFourteen(BST<Faculty> &faculty, BST<Student> &students)
{
  ofstream writer("serialization.txt");
	writer << students.size << endl;
	students.serialize(writer);
  faculty.serialize(writer);

	writer.close();
  exit(1);
}

void invalidInput()
{
  cout<<"Invalid Input"<<endl;
  cin.clear();
  cin.ignore(256,'\n');
}
