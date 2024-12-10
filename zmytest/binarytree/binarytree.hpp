#ifndef BINARYTREEMYTEST
#define BINARYTREEMYTEST

#include "../../binarytree/lnk/binarytreelnk.hpp"
#include "../../binarytree/vec/binarytreevec.hpp"
#include "../util.hpp"

/* ************************************************************************** */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

template <typename Data>
void PrintTree(typename BinaryTree<Data>::Node * node, const int level, const char side) {
if (node == nullptr)
  return;
if (node->HasRightChild())
  PrintTree<Data>(&node->RightChild(), level + 1, 'R');
for (int i = 0; i < level; ++i) 
  cout << "     ";
if(side != ' ')
  cout << side; 
cout <<" --- " << node->Element() << endl;
if (node->HasLeftChild())
  PrintTree<Data>(&node->LeftChild(), level + 1, 'L');
}

List<int> MakeList() {
  List<int> list; 
  int value;
  bool insertion = true;
  cout << "\nPress any key that is not a number to stop or press 0 to randomize a list." << endl;
  while (insertion) {
    cout << "Enter a value to insert into the Tree: ";
    cin >> value;
    if (cinOK_NoErr()) {
      if (value == 0) {
        srand((unsigned) time(0));
        for (ulong i = 0; i < 10; i++) 
          list.InsertAtBack(rand() % 101);
        cout << "Random Tree created." << endl;
        break;
      } else list.InsertAtBack(value);
    } else insertion = false;
  }
  return list;
}

void testBinaryTreeLnk() {
  cout << "\n~*~#~*~ BinaryTreeLnk Operations ~*~#~*~";
  List<int> list = MakeList();
  while (list.Empty()) {
    cout << "Tree cannot be Empty." << endl;
    list = MakeList();
  }
  BinaryTreeLnk<int> tree = BinaryTreeLnk<int>(list);
  BTPreOrderIterator<int> iterator = BTPreOrderIterator(tree);
  BTPreOrderMutableIterator<int> mutableIterator = BTPreOrderMutableIterator(tree);
  ulong i = 0;
  int value, oldValue, choice = -1;
  do {
    do {
      cout << "\n1) Print Tree\n2) Traverse \n3) PreOrder Traverse\n4) PostOrder Traverse\n5) InOrder Traverse\n6) Breadth Traverse\n7) Iterate through the tree\n8) Replace a value\n9) Clear Tree\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch (choice) {
      case 1:
        cout << endl;
        PrintTree<int>(&tree.Root(), 0, ' ');
        break;
      case 2:
      case 3:
        if (choice == 2) cout << "Traversal: ";
        if (choice == 3) cout << "PreOrder Traversal: ";
        tree.PreOrderTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 4:
        cout << "PostOrder Traversal: ";
        tree.PostOrderTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 5:
        cout << "InOrder Traversal: ";
        tree.InOrderTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 6:
        cout << "Breadth Traversal: ";
        tree.BreadthTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 7:
      case 8:
        while (!iterator.Terminated()) {
          cout << "element [" << i << "]: " << *iterator << endl;
          i++;
          ++iterator;
        }
        iterator.Reset();
        i = 0;
        if (choice == 8) {
          cout << "Enter the value to replace: ";
          cin >> oldValue;
          while (!mutableIterator.Terminated()) {
            if (*mutableIterator == oldValue) {
              cout << "Replace with: ";
              cin >> value;
              *mutableIterator = value;
              cout << "Value replaced." << endl;
              break;
            }
            ++mutableIterator;
          }
          if (mutableIterator.Terminated())
            cout << "Value not found." << endl;
          mutableIterator.Reset();
        }
        break;
      case 9:
        tree.Clear();
        cout << "Tree cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while (choice != 0);
}

void testBinaryTreeVec() {
  cout << "\n~*~#~*~ BinaryTreeVec Operations ~*~#~*~";
  List<int> list = MakeList();
  if (list.Empty()) {
    cout << "Tree cannot be Empty." << endl;
    list = MakeList();
  }
  BinaryTreeVec<int> tree = BinaryTreeVec<int>(list);
  BTPreOrderIterator<int> iterator = BTPreOrderIterator(tree);
  BTPreOrderMutableIterator<int> mutableIterator = BTPreOrderMutableIterator(tree);
  ulong i = 0;
  int value, oldValue, choice = -1;
  do {
    do {
      cout << "\n1) Print Tree\n2) Traverse \n3) PreOrder Traverse\n4) PostOrder Traverse\n5) InOrder Traverse\n6) Breadth Traverse\n7) Iterate through the tree\n8) Replace a value\n9) Clear Tree\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch (choice) {
      case 1:
        cout << endl;
        PrintTree<int>(&tree.Root(), 0, ' ');
        break;
      case 2:
      case 3:
        if (choice == 2) cout << "Traversal: ";
        if (choice == 3) cout << "PreOrder Traversal: ";
        tree.PreOrderTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 4:
        cout << "PostOrder Traversal: ";
        tree.PostOrderTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 5:
        cout << "InOrder Traversal: ";
        tree.InOrderTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 6:
        cout << "Breadth Traversal: ";
        tree.BreadthTraverse([](int value) { cout << value << " - "; });
        cout << endl;
        break;
      case 7:
      case 8:
        while (!iterator.Terminated()) {
          cout << "element [" << i << "]: " << *iterator << endl;
          i++;
          ++iterator;
        }
        iterator.Reset();
        i = 0;
        if (choice == 8) {
          cout << "Enter the value to replace: ";
          cin >> oldValue;
          while (!mutableIterator.Terminated()) {
            if (*mutableIterator == oldValue) {
              cout << "Replace with: ";
              cin >> value;
              *mutableIterator = value;
              cout << "Value replaced." << endl;
              break;
            }
            ++mutableIterator;
          }
          if (mutableIterator.Terminated())
            cout << "Value not found." << endl;
          mutableIterator.Reset();
        }
        break;
      case 9:
        tree.Clear();
        cout << "Tree cleared." << endl;
        break;
      case 0: break;
      default:
        cout << "Invalid choice." << endl;
    }
  } while (choice != 0);
}

/* ************************************************************************** */

#endif