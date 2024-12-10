#ifndef UTIL
#define UTIL

#include <iostream>
#include <limits>
using namespace std;

bool cinOK() {
  if (cin.fail()) {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    cout << "Invalid value entered." << endl << endl;
    return false;
  }
  return true;
}

bool cinOK_NoErr() {
  if (cin.fail()) {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return false;
  }
  return true;
}

#endif 