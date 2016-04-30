#include <iostream>
#include <fstream>
#include "TreeNode.cpp"

using namespace std;

template <class T>
class BST
{
  public:
    BST();
    ~BST(); //why does it need to be virtual?

    void insert(T value);
    bool contains(T value);
    bool deleteNode(T value);
    bool isEmpty();
    T* getMin();
    T* getMax();
    TreeNode<T>* getSuccessor(TreeNode<T>* d);
    void recPrint(TreeNode<T>* node);
    void printTree();
    T* findNode(int key);
    void serialize(ofstream &ostream);
    void serializeHelper(ofstream &ostream, TreeNode<T>* node);

    int size;

  private:
    TreeNode<T>* root;

};

template<class T>
BST<T>::BST()
{
  root = NULL;
  size = 0;
}

template <class T>
BST<T>::~BST()
{
  //iterate and delete
}

template<class T>
void BST<T>::serialize(ofstream &ostream)
{
  serializeHelper(ostream, root);
}

template<class T>
void BST<T>::serializeHelper(ofstream &ostream, TreeNode<T>* node)
{
  if(node == NULL)
  {
    return;
  }
  serializeHelper(ostream, node->left);
  node->key.serialize(ostream);
  serializeHelper(ostream, node->right);
}

template <class T>
void BST<T>::printTree()
{
  recPrint(root);
}

template <class T>
void BST<T>::recPrint(TreeNode<T>* node)
{
  if(node == NULL)
  {
    return;
  }
  recPrint(node->left);
  node->key.print();
  recPrint(node->right);
}

template <class T>
T* BST<T>::getMax()
{
  TreeNode<T>* current = root;

  if(current == NULL)
  {
    return NULL;
  }

  while(current->right != NULL)
  {
    current = current->right;
  }

  return &(current->key);
}

template <class T>
bool BST<T>::isEmpty()
{
  return (size == 0);
}

template <class T>
void BST<T>::insert(T value)
{
  TreeNode<T>* node = new TreeNode<T>(value);
  size++;

  if(root == NULL)
  {
    root = node;
  }
  else
  {
    TreeNode<T>* current = root;
    TreeNode<T>* parent;
    while(true)
    {
      parent = current;

      if(value.ID < current->key.ID)//go left
      {
        current = current->left;
        if(current == NULL)//if null leaf insert here
        {
          parent->left = node;
          break;
        }
      }
      else
      {
        current = current->right;
        if(current == NULL)
        {
          parent->right = node;
          break;
        }
      }

    }
  }
}

template <class T>
bool BST<T>::contains(T value)
{
  if(root == NULL)
  {
    return false;
  }
  else
  {
    TreeNode<T>* current = root;

    while(current->key != value)//while we have not found the value keep iterating
    {
      if(value < current->key)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }

      if(current == NULL)
      {
        return false;
      }
    }
    return true;
  }
}

template <class T>
T* BST<T>::findNode(int key)
{
  if(root == NULL)
  {
    return NULL;
  }
  else
  {
    TreeNode<T>* current = root;

    while(current->key.ID != key)//while we have not found the value keep iterating
    {
      if(key < current->key.ID)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }

      if(current == NULL)
      {
        return NULL;
      }
    }
    return &(current->key);
  }
}

template <class T>
bool BST<T>::deleteNode(T k)
{
  if(root == NULL)
  {
    return false;
  }
  TreeNode<T>* current = root;
  TreeNode<T>* parent = root;
  bool isLeft = true;

  while(current->key.ID != k.ID)//search for node to be removed
  {
    parent = current;

    if(k.ID < current->key.ID)
    {
      isLeft = true;
      current = current->left;
    }
    else
    {
      isLeft = false;
      current = current->right;
    }

    if(current == NULL) //didnt find it
    {
      return false;
    }
  }

  //we found node with key value
  //if leaf node, no children
  if(current->left == NULL && current->right == NULL)
  {
    if(current == root) //delete root
    {
      root = NULL;
    }
    else if(isLeft)
    {
      parent->left = NULL;
    }
    else
    {
      parent->right = NULL;
    }
    size--;
    return true;
  }
  //has one child, left child, it has no right child
  else if(current->right == NULL)
  {
    if(current == root) //delete root
    {
      root = current->left;
    }
    else if(isLeft)
    {
      parent->left = current->left;
    }
    else
    {
      parent->right = current->left;
    }
    size--;
    return true;
  }
  else if(current->left == NULL)
  {
    if(current == root) //delete root
    {
      root = current->right;
    }
    else if(isLeft)
    {
      parent->left = current->right;
    }
    else
    {
      parent->right = current->right;
    }
    size--;
    return true;
  }
  else
  {
    TreeNode<T>* successor = getSuccessor(current);
    if(current == root)
    {
      root = successor;
    }
    //connect or link parent of current to successor
    //check is left
    else if(isLeft)
    {
      parent->left = successor;
    }
    //check is right
    else
    {
      parent->right = successor;
    }

    //link successor to current's left and right child
    successor->right = current->right;
    successor->left = current->left;
    size--;
    return true;


    //todo: delete successor from leaf placement on tree??

  }
  return false;
}

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d)//d is the node to be deleted
{
  TreeNode<T>* sp = d; //successors parent
  TreeNode<T>* successor = d; //should be one right and all the way to the left

  TreeNode<T>* current = d->right;

  while(current != NULL)
  {
    sp = successor;
    successor = current;
    current = current->left;
  }

  if(successor != d->right) //descendant of right child
  {
    sp->left = successor->right;
    successor->right = d->right;
  }

  return successor;
}
