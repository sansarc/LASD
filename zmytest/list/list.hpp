#ifndef LISTMYTEST
#define LISTMYTEST

#include "../../list/list.hpp"
#include "../util.hpp"

/* ************************************************************************** */

#include <iostream>
#include <string>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

void testList() {
  cout << "\n~*~#~*~ List Operations ~*~#~*~";
  int choice = -1;
  List<int> list;
  int value, index;

  do {
    do {
      cout << "\n1) Display List\n2) Insert Element at Back\n3) Insert Element at Front\n4) Remove Element at Front\n5) Access Element\n6) Modify Element\n7) Clear List\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch(choice) {
      case 1:
          cout << "List: ";
          for (ulong i = 0; i < list.Size(); ++i) {
            cout << list[i] << " ";
          } 
          cout << endl;
        break;
      case 2:
        cout << "Enter the value to insert at the back: ";
        cin >> value;
        list.InsertAtBack(value);
        cout << "Element inserted at the back." << endl;
        break;
      case 3:
        cout << "Enter the value to insert at the front: ";
        cin >> value;
        list.InsertAtFront(value);
        cout << "Element inserted at the front." << endl;
        break;
      case 4:
        try {
          list.RemoveFromFront();
          cout << "Element removed from the front." << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 5:
        try {
          cout << "Enter the index of the element to access: ";
          cin >> index;
          cout << "Element at index " << index << ": " << list[index] << endl;
        } catch (out_of_range & oor) {
          cout << oor.what() << endl;
        }
        break;
      case 6:
        try {
          cout << "Enter the index of the element to modify: ";
          cin >> index;
          cout << "Enter the new value: ";
          cin >> value;
          list[index] = value;
          cout << "Element modified." << endl;
        } catch (out_of_range & oor) {
          cout << oor.what() << endl;
        }
        break;
      case 7:
        list.Clear();
        cout << "List cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while(choice != 0);
}

void addTask(List<string> & list) {
  string task;
  cout << "Enter task: ";
  getline(cin, task);
  list.InsertAtBack(task);
  cout << "Task added successfully." << endl;
}

void removeTask(List<string> & list) {
  if (!list.Empty()) {
    cout << "Removing task: " << list.Front() << endl;
    list.RemoveFromFront();
    cout << "Task removed successfully." << endl;
  } else {
    cout << "No tasks to remove." << endl;
  }
}

void displayTasks(const List<string> & list) {
  if (!list.Empty()) {
    cout << "Current tasks:" << endl;
    for (size_t i = 0; i < list.Size(); ++i) {
      cout << "\t" << i + 1 << ". " << list[i] << endl;
    }
  } else {
    cout << "No tasks to display." << endl;
  }
}

void TODOlist() {
  List<string> todoList;
  cout << "\n~*~#~*~ To-Do List ~*~#~*~";

  int choice = -1;
  while (choice != 0) {
    cout << "\n1) Add Task\n2) Remove Task\n3) Display Tasks\n0) Exit" << endl;
    do {
      cout << "Enter your choice: ";
      cin >> choice;
    } while (!cinOK());
    cin.ignore();

    switch (choice) {
      case 1:
        addTask(todoList);
        break;
      case 2:
        removeTask(todoList);
        break;
      case 3:
        displayTasks(todoList);
        break;
      case 0:
        cout << "Exiting." << endl;
        break;
      default:
        cout << "Invalid choice! Please try again." << endl;
        break;
    }
  }
}

#endif
