#ifndef BSTMYTEST
#define BSTMYTEST

#include "../../bst/bst.hpp"
#include "../util.hpp"

/* ************************************************************************** */

#include <iostream>
#include <string>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

void testBST() {
  cout << "\n~*~#~*~ Binary Search Tree Operations ~*~#~*~";
  BST<int> bst;
  BTPreOrderIterator<int> iterator = BTPreOrderIterator(bst);
  BTPreOrderMutableIterator<int> mutableIterator = BTPreOrderMutableIterator(bst);
  bool insertion = true;
  int value, oldValue, choice = -1;
  ulong i = 0;

  do {
    do {
      cout << "\n1) Insert Elements\n2) Remove Element\n3) Search Element\n4) Minimum Element\n5) Maximum Element\n6) Traverse\n7) PreOrder Traverse\n8) PostOrder Traverse\n9) InOrder Traverse\n10) Breadth Traverse\n11) Iterate through the BST\n12) Replace a value\n13) Clear BST\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch (choice) {
      case 1:
        cout << "Press any key that is not a number to stop or press 0 to randomize a BST." << endl;
        while (insertion) {
          cout << "Enter a value to insert into the BST: ";
          cin >> value;
          if (cinOK_NoErr()) {
            if (value == 0) {
              srand((unsigned) time(0));
              for (ulong i = 0; i < 10; i++) 
                bst.Insert(rand() % 101);
              cout << "Random BST created." << endl;
              break;
            } else bst.Insert(value);
          } else insertion = false;
        }
        insertion = true;
        if (bst.Empty())
          cout << "BST left Empty." << endl;
        else if (!insertion)
          cout << "Elements inserted." << endl;
        break;
      case 2: 
        cout << "Enter the value to remove: ";
        cin >> value;
        if (bst.Remove(value))
          cout << "Element removed successfully." << endl;
        else
          cout << "Element not found." << endl;
        break;
      case 3: 
        cout << "Enter the value to search: ";
        cin >> value;
        if (bst.Exists(value))
          cout << "Element found." << endl;
        else
          cout << "Element not found." << endl;
        break;
      case 4: 
        try {
          cout << "Minimum element: " << bst.Min() << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 5: 
        try {
          cout << "Maximum element: " << bst.Max() << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 6:
      case 7: 
        if (!bst.Empty()) {
          cout << "PreOrder Traversal: ";
          bst.PreOrderTraverse([](int value) { cout << value << " - "; });
        } else cout << "BST is Empty.";
        cout << endl;
        break;
      case 8:
        if (!bst.Empty()) {
          cout << "PostOrder Traversal: ";
          bst.PostOrderTraverse([](int value) { cout << value << " - "; });
        } else cout << "BST is Empty.";
        cout << endl;
        break;
      case 9:
        if (!bst.Empty()) {
          cout << "InOrder Traversal: ";
          bst.InOrderTraverse([](int value) { cout << value << " - "; });
        } else cout << "BST is Empty.";
        cout << endl;
        break;
      case 10:
        if (!bst.Empty()) {
          cout << "Breadth Traversal: ";
          bst.BreadthTraverse([](int value) { cout << value << " - "; });
        } else cout << "BST is Empty.";
        cout << endl;
        break;
      case 11:
      case 12:
        if (bst.Empty()) {
          cout << "BST is Empty.";
          break;
        }
        iterator = BTPreOrderIterator(bst);
        while (!iterator.Terminated()) {
          cout << "element [" << i << "]: " << *iterator << endl;
          i++;
          ++iterator;
        }
        iterator.Reset();
        i = 0;
        if (choice == 12) {
          mutableIterator = BTPreOrderMutableIterator(bst);
          cout << "Enter the value to replace: ";
          cin >> oldValue;
          if (bst.Exists(oldValue)) {
            while (!mutableIterator.Terminated()) { 
              if (*mutableIterator == oldValue) break;
              ++mutableIterator;
            }
            cout << "Replace with: ";
            cin >> value;
            *mutableIterator = value;
            cout << "Value replaced." << endl;
          }
          else 
            cout << "Value not found." << endl;
          mutableIterator.Reset();
        }
        break;
      case 13: {
        bst.Clear();
        cout << "BST cleared." << endl;
        break;
      }
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while (choice != 0);
}

#endif
