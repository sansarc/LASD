#ifndef STACKMYTEST
#define STACKMYTEST

#include "../../stack/vec/stackvec.hpp"
#include "../../stack/lst/stacklst.hpp"

/* ************************************************************************** */

#include <iostream>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

void testStackLst() {
  cout << "\n~*~#~*~ StackLst Operations ~*~#~*~";
  int choice = -1;
  StackLst<int> stackLst;
  int value;

  do {
    do {
      cout << "\n1) Push Element\n2) Pop Element\n3) Display Top\n4) Display Size\n5) Clear Stack\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());
    switch(choice) {
      case 1:
        cout << "Enter the value to push: ";
        cin >> value;
        stackLst.Push(value);
        cout << "Element pushed." << endl;
        break;
      case 2:
        try {
          stackLst.Pop();
          cout << "Element popped." << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 3:
        try {
          cout << "Top of the stack: " << stackLst.Top() << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 4:
        cout << "Size of the stack: " << stackLst.Size() << endl;
        break;
      case 5:
        stackLst.Clear();
        cout << "Stack cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while(choice != 0);
}

void testStackVec() {
  cout << "\n~*~#~*~ StackVec Operations ~*~#~*~";
  int choice = -1;
  StackVec<int> stackVec;
  int value;
  do {
    do {
      cout << "\n1) Push Element\n2) Pop Element\n3) Display Top\n4) Display Size\n5) Clear Stack\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch(choice) {
      case 1:
        cout << "Enter the value to push: ";
        cin >> value;
        stackVec.Push(value);
        cout << "Element pushed." << endl;
        break;
      case 2:
        try {
          stackVec.Pop();
          cout << "Element popped." << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 3:
        try {
          cout << "Top of the stack: " << stackVec.Top() << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 4:
        cout << "Size of the stack: " << stackVec.Size() << endl;
        break;
      case 5:
        stackVec.Clear();
        cout << "Stack cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while(choice != 0);
}

bool areParenthesesBalanced(const std::string& expression) {
  StackVec<char> stack;
  for (char c : expression) {
    if (c == '(' || c == '[' || c == '{') 
      stack.Push(c);
    else if (c == ')' || c == ']' || c == '}') {
      if (stack.Empty())
        return false;
      char top = stack.Top();
      if ((c == ')' && top == '(') || (c == ']' && top == '[') || (c == '}' && top == '{')) 
        stack.Pop();
      else 
        return false;
    }
  }

  return stack.Empty(); 
}

void checkParenthesesBalance() {
  std::string expression;
  std::cout << "\nEnter an expression with parentheses: ";
  std::cin >> expression;
  if (areParenthesesBalanced(expression)) {
    std::cout << "The parentheses are balanced!" << std::endl;
  } else {
    std::cout << "The parentheses are not balanced!" << std::endl;
  }
}

#endif