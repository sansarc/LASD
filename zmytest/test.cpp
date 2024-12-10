#include "test.hpp"
#include "util.hpp"
#include "vector/vector.hpp"
#include "list/list.hpp"
#include "queue/queue.hpp"
#include "stack/stack.hpp"
#include "binarytree/binarytree.hpp"
#include "bst/bst.hpp"
#include "hashtable/hashtable.hpp"

/* ************************************************************************** */

#include <iostream>
using namespace std;

/* ************************************************************************** */

void menu1() {
  cout << "1) Vector Test\n2) List Test\n3) QueueVec Test\n4) QueueLst Test\n5) StackVec Test\n6) StackLst Test\n7) Guessing Game (using a Vector)\n8) TODO List (using a List)\n9) Maze Game (using a Queue)\n10) Balanced Parenthesis Checker (using a Stack)\n0) Exit" << endl;
  int choice;
  cout << "Enter your choice: ";
  cin >> choice;
  if (!cinOK()) 
    menu1();
  switch (choice) {
    case 1:
      testVector();
      break;
    case 2:
      testList();
      break;
    case 3:
      testQueueVec();
      break;
    case 4:
      testQueueLst();
      break;
    case 5:
      testStackVec();
      break;
    case 6:
      testStackLst();
      break;
    case 7:
      guessingGame();
      break;
    case 8:
      TODOlist();
      break;
    case 9:
      mazeGame();
      break;
    case 10:
      checkParenthesesBalance();
      break;
    case 0: break;
    default:
      cout << "Invalid choice." << endl << endl;
      menu1();
  }
  if (choice != 0) {
      char playAgain = 'n';
      cout << "\nDo you want to try something else? [y/n]: ";
      cin >> playAgain;
      if (playAgain == 'y')
        menu1();
  }
}

void menu2() {
  cout << "1) BinaryTreeLnk Test\n2) BinaryTreeVec Test\n3) BST Test\n0) Exit\n";
  int choice;
  cout << "Enter your choice: ";
  cin >> choice;
  if (!cinOK()) 
    menu2();
  switch (choice) {
    case 1:
      testBinaryTreeLnk();
      break;
    case 2:
      testBinaryTreeVec();
      break;
    case 3:
      testBST();
      break;
    case 0: break;
    default:
      cout << "Invalid choice." << endl << endl;
      menu2();
  }

  if (choice != 0) {
    char playAgain = 'n';
    cout << "\nDo you want to try something else? [y/n]: ";
    cin >> playAgain;
    if (playAgain == 'y')
      menu2();
  }
}

void menu3() {
  cout << "1) Hash Table with Chaining (Closed Addressing) Test\n2) Hash Table with Chaining (Open Addressing) Test\n0) Exit\n";
  int choice;
  cout << "Enter your choice: ";
  cin >> choice;
  if (!cinOK()) 
    menu3();
  switch (choice) {
    case 1:
      testHashTableClsAdr();
      break;
    case 2:
      testHashTableOpnAdr();
      break;
    case 0: break;
    default:
      cout << "Invalid choice." << endl << endl;
      menu3();
  }

  if (choice != 0) {
    char playAgain = 'n';
    cout << "\nDo you want to try something else? [y/n]: ";
    cin >> playAgain;
    if (playAgain == 'y')
      menu3();
  }
}

void menu() {
  int choice;
  do {
    cout << "Run tests from exercise [1] - [2] - [3] ([0] to exit): ";
    cin >> choice;
  } while (!cinOK());
  switch (choice) {
  case 1:
    menu1();
    break;
  case 2:
    menu2();
    break;
  case 3:
    menu3();
    break;
  case 0: break;
  default:
    cout << "Invalid choice." << endl << endl;
    menu();
  }
}

void mytest() {
  cout << "... or, you can run alternative tests: " << endl;
  menu();
  cout << endl << "Goodbye again!" << endl;
}
