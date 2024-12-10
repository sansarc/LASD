#ifndef VECTORMYTEST
#define VECTORMYTEST

#include "../../vector/vector.hpp"
#include "../util.hpp"

/* ************************************************************************** */

#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <cassert>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

void testVector() {
  cout << "\n~*~#~*~ Vector Operations ~*~#~*~" << endl;
  int choice = -1;
  ulong size;
  cout << "Enter the size of the vector: ";
  cin >> size;
  Vector<int> vector(size);
  int value;

  for (ulong i = 0; i < vector.Size(); ++i) {
    cout << "Value at index " << "[" << i << "]: ";
    cin >> value;
    vector[i] = value;
  }

  do {
    do {
      cout << "\n1) Display Vector\n2) Resize Vector\n3) Access Element\n4) Modify Element\n5) Clear Vector\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch(choice) {
      case 1:
          cout << "Vector: ";
          for (ulong i = 0; i < vector.Size(); ++i) {
            if (vector[i] == -1094795586) 
              cout << "null" << " ";
            else
              cout << vector[i] << " ";
          } 
          cout << endl;
        break;
      case 2:
        ulong newSize;
        cout << "Enter the new size: ";
        cin >> newSize;
        vector.Resize(newSize);
        cout << "Vector resized." << endl;
        break;
      case 3:
        try {
          ulong index;
          cout << "Enter the index of the element to access: ";
          cin >> index;
          cout << "Element at index " << index << ": " << vector[index] << endl;
        } catch (out_of_range & oof) {
          cout << oof.what() << endl;
        }
        break;
      case 4:
        try {    
          ulong modifyIndex;
          int newValue;
          cout << "Enter the index of the element to modify: ";
          cin >> modifyIndex;
          cout << "Enter the new value: ";
          cin >> newValue;
          vector[modifyIndex] = newValue;
          cout << "Element modified." << endl;
        } catch (out_of_range & oof) {
          cout << oof.what() << endl;
        }
        break;
      case 5:
        vector.Clear();
        cout << "Vector cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while(choice != 0);
}

void guessingGame() {
  srand(time(nullptr));

  SortableVector<int> vec;
  for (ulong i = 0; i < 10; ++i) {
    vec.Resize(i + 1);
    vec[i] = rand() % 100 + 1;
  }
  vec.Sort();
  
  cout << "\n~*~#~*~ Let's play a guessing game! ~*~#~*~" << endl;
  cout << "Try to guess the random selected number in this vector of numbers from 1 to 100! (enter 0 to exit)" << endl;
  cout << "Sorted Vector: ";
  for (ulong i = 0; i < vec.Size(); ++i)
    cout << vec[i] << " ";
  cout << endl;

  int targetIndex = rand() % vec.Size(); 
  int targetValue = vec[targetIndex]; 
  int guess, attempts = 0;
  bool guessed;

  do {
    attempts++;
    cout << "Enter your guess: ";
    cin >> guess;
    if (cinOK()) {
      if (guess == 0)
        break; 
      guessed = guess == targetValue;
      if (guessed) 
        cout << "Congratulations! You guessed the number " << targetValue << " correctly in " << attempts << " attempts!" << endl;
      else if (guess < targetValue) 
        cout << "Too low! Try again." << endl;
      else
        cout << "Too high! Try again." << endl;
    }
  } while (!guessed);
}

#endif 