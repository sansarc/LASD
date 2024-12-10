#ifndef HTMYTEST
#define HTMYTEST

#include "../../hashtable/hashtable.hpp"
#include "../../hashtable/clsadr/htclsadr.hpp"
#include "../../hashtable/opnadr/htopnadr.hpp"
#include "../util.hpp"

/* ************************************************************************** */

#include <iostream>
#include <string>
#include <sstream>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

void testHashTableClsAdr() {
  cout << "\n~*~#~*~ Hash Table with Chaining (Closed Addressing) Operations ~*~#~*~";
  HashTableClsAdr<int> hashTable;
  bool insertion = true;
  int value, choice = -1;

  do {
    do {
      cout << "\n1) Print Hash Table\n2) Print Hash Table (compact view)\n3) Insert Elements\n4) Remove Element\n5) Search Element\n6) Resize Hash Table\n7) Clear Hash Table\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch (choice) {
      case 1:
        hashTable.Print();
        break;
      case 2:
        hashTable.PrintCompact();
        break;
      case 3:
        cout << "Press any key that is not a number to stop or press 0 to randomize the hash table." << endl;
        while (insertion) {
          cout << "Enter a value to insert into the hash table: ";
          cin >> value;
          if (cinOK_NoErr()) {
            if (value == 0) {
              srand((unsigned) time(0));
              for (ulong i = 0; i < 15; i++) 
                hashTable.Insert(rand() % 101);
              for (ulong i = 0; i < 15; i++) 
                hashTable.Insert(rand() % 1001);
              for (ulong i = 0; i < 15; i++) 
                hashTable.Insert(rand() % 10001);
              cout << "Random hash table created." << endl;
              break;
            } else hashTable.Insert(value);
          } else insertion = false;
        }
        insertion = true;
        if (hashTable.Empty())
          cout << "Hash table left empty." << endl;
        else if (!insertion)
          cout << "Elements inserted." << endl;
        break;
      case 4: 
        cout << "Enter the value to remove: ";
        cin >> value;
        if (hashTable.Remove(value))
          cout << "Element removed." << endl;
        else
          cout << "Element not found." << endl;
        break;
      case 5: 
        cout << "Enter the value to search: ";
        cin >> value;
        if (hashTable.Exists(value))
          cout << "Element found." << endl;
        else
          cout << "Element not found." << endl;
        break;
      case 6:
        ulong newSize;
        cout << "Enter the new size for the hash table: ";
        cin >> newSize;
        hashTable.Resize(newSize);
        cout << "Hash table appropriately resized." << endl;
        break;
      case 7: 
        hashTable.Clear();
        cout << "Hash table cleared." << endl;
        break; 
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while (choice != 0);
}

void testHashTableOpnAdr() {
  cout << "\n~*~#~*~ Hash Table with Chaining (Open Addressing) Operations ~*~#~*~";
  HashTableOpnAdr<int> hashTable;
  bool insertion = true;
  int value, choice = -1;

  do {
    do {
      cout << "\n1) Print Hash Table\n2) Print Hash Table (compact view)\n3) Insert Elements\n4) Remove Element\n5) Search Element\n6) Resize Hash Table\n7) Clear Hash Table\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch (choice) {
      case 1:
        hashTable.Print();
        break;
      case 2:
        hashTable.PrintCompact();
        break;
      case 3:
        cout << "Press any key that is not a number to stop or press 0 to randomize the hash table." << endl;
        while (insertion) {
          cout << "Enter a value to insert into the hash table: ";
          cin >> value;
          if (cinOK_NoErr()) {
            if (value == 0) {
              srand((unsigned) time(0));
              for (ulong i = 0; i < 15; i++) 
                hashTable.Insert(rand() % 101);
              for (ulong i = 0; i < 15; i++) 
                hashTable.Insert(rand() % 1001);
              for (ulong i = 0; i < 15; i++) 
                hashTable.Insert(rand() % 10001);
              cout << "Random hash table created." << endl;
              break;
            } else hashTable.Insert(value);
          } else insertion = false;
        }
        insertion = true;
        if (hashTable.Empty())
          cout << "Hash table left empty." << endl;
        else if (!insertion)
          cout << "Elements inserted." << endl;
        break;
      case 4: 
        cout << "Enter the value to remove: ";
        cin >> value;
        if (hashTable.Remove(value))
          cout << "Element removed." << endl;
        else
          cout << "Element not found." << endl;
        break;
      case 5: 
        cout << "Enter the value to search: ";
        cin >> value;
        if (hashTable.Exists(value))
          cout << "Element found." << endl;
        else
          cout << "Element not found." << endl;
        break;
      case 6:
        ulong newSize;
        cout << "Enter the new size for the hash table: ";
        cin >> newSize;
        hashTable.Resize(newSize);
        cout << "Hash table appropriately resized." << endl;
        break;
      case 7: 
        hashTable.Clear();
        cout << "Hash table cleared." << endl;
        break; 
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while (choice != 0);
}


/* ************************************************************************** */



#endif
