#include <iostream>

using namespace std;

template <class T>
class GenStack
{
  public:
    GenStack(int maxSize);
    GenStack();
    ~GenStack();

    void push(T data);
    T pop();
    T peek();

    int isFull();
    int isEmpty();

    int top;
    int maxSize;
    T *myArray;

};

template<class T>
GenStack<T>::GenStack()
{

}

template<class T>
GenStack<T>::GenStack(int max)
{
  myArray = new T[max];
  maxSize = max;
  top = -1;
}

template<class T>
GenStack<T>::~GenStack()
{
  delete myArray;
  cout << "object destroyed"<<endl;
}

template<class T>
void GenStack<T>::push(T data)
{
  if(isFull() == true)
  {
    for(int i = 0; i<maxSize-1; ++i)
    {
      myArray[i] = myArray[i+1];
    }
  }
  myArray[++top] = data;
}

template<class T>
T GenStack<T>::pop()
{
  return myArray[top--];
}

template<class T>
T GenStack<T>::peek()
{
  return myArray[top];
}

template<class T>
int GenStack<T>::isFull()
{
  return (top==maxSize-1);
}

template<class T>
int GenStack<T>::isEmpty()
{
  return (top == -1);
}
