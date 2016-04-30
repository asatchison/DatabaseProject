#include <iostream>

using namespace std;

template <class T>
class TreeNode
{
  public:
    TreeNode();
    TreeNode(T key);
    ~TreeNode();
    T key;
    TreeNode<T>* left;
    TreeNode<T>* right;
};

template <class T>
TreeNode<T>::TreeNode(T k) //overloaded constructor
{
  left = NULL;
  right = NULL;
  key = k;
}

template <class T>
TreeNode<T>::TreeNode()
{
  left = NULL;
  right = NULL;
}
