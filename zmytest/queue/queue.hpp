#ifndef QUEUEMYTEST
#define QUEUEMYTEST

#include "../util.hpp"
#include "../../queue/vec/queuevec.hpp"
#include "../../queue/lst/queuelst.hpp"

/* ************************************************************************** */

#include <iostream>
using namespace lasd;
using namespace std;

/* ************************************************************************** */

void testQueueLst() {
  cout << "\n~*~#~*~ QueueLst Operations ~*~#~*~";
  int choice = -1;
  QueueLst<int> queueLst;
  int value;

  do {
    do {
      cout << "\n1) Enqueue Element\n2) Dequeue Element\n3) Display Head\n4) Display Size\n5) Clear Queue\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch(choice) {
      case 1:
        cout << "Enter the value to enqueue: ";
        cin >> value;
        queueLst.Enqueue(value);
        cout << "Element enqueued." << endl;
        break;
      case 2:
        try {
          queueLst.Dequeue();
          cout << "Element dequeued." << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 3:
        try {
          cout << "Head of the queue: " << queueLst.Head() << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 4:
        cout << "Size of the queue: " << queueLst.Size() << endl;
        break;
      case 5:
        queueLst.Clear();
        cout << "Queue cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while(choice != 0);
}

void testQueueVec() {
  cout << "\n~*~#~*~ QueueVec Operations ~*~#~*~";
  int choice = -1;
  QueueVec<int> queueVec;
  int value;

  do {
    do {
      cout << "\n1) Enqueue Element\n2) Dequeue Element\n3) Display Head\n4) Display Size\n5) Clear Queue\n0) Exit\nEnter your choice: ";
      cin >> choice;
    } while (!cinOK());

    switch(choice) {
      case 1:
        cout << "Enter the value to enqueue: ";
        cin >> value;
        queueVec.Enqueue(value);
        cout << "Element enqueued." << endl;
        break;
      case 2:
        try {
          queueVec.Dequeue();
          cout << "Element dequeued." << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 3:
        try {
          cout << "Head of the queue: " << queueVec.Head() << endl;
        } catch (length_error & le) {
          cout << le.what() << endl;
        }
        break;
      case 4:
        cout << "Size of the queue: " << queueVec.Size() << endl;
        break;
      case 5:
        queueVec.Clear();
        cout << "Queue cleared." << endl;
        break;
      case 0: break;
      default: cout << "Invalid choice." << endl;
    }
  } while(choice != 0);
}

void display(const char maze[][5], int mazeSize, int playerX, int playerY) {
  for (int i = 0; i < mazeSize; ++i) {
    for (int j = 0; j < mazeSize; ++j) {
      if (i == playerY && j == playerX) {
        cout << "[@]"; 
      } else {
        cout << "[" << maze[i][j] << "]";
      }
    }
    cout << endl;
  }
  cout << "Exit point -> [X]" << endl;
  cout << "Use 'W' to move up, 'S' to move down, 'A' to move left, 'D' to move right" << endl;
}

void movePlayer(char direction, QueueVec<char> & movements) {
  movements.Enqueue(direction);
}

void mazeGame() {
  cout << "\n~*~#~*~ MAZE ~*~#~*~" << endl;
  QueueVec<char> movements;

  char playerPosition = ' ';
  char maze[5][5] = {
      {' ', ' ', ' ', ' ', 'X'},
      {' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' '}
  };

  int playerX = 0;
  int playerY = 0;

  char userInput;
  bool gameRunning = true;

  while (gameRunning) {
    display(maze, 5, playerX, playerY);
    maze[playerY][playerX] = playerPosition;

    maze[playerY][playerX] = ' ';

    cout << "Enter movement (W/S/A/D to move, Q to quit): ";
    cin >> userInput;

    switch (userInput) {
      case 'W':
      case 'w':
        movePlayer('U', movements);
        if (playerY > 0)
          playerY--;
        break;
      case 'S':
      case 's':
        movePlayer('D', movements);
        if (playerY < 4)
          playerY++;
        break;
      case 'A':
      case 'a':
        movePlayer('L', movements);
        if (playerX > 0)
          playerX--;
        break;
      case 'D':
      case 'd':
        movePlayer('R', movements);
        if (playerX < 4)
          playerX++;
        break;
      case 'Q':
      case 'q':
        gameRunning = false;
        break;
      default:
        cout << "Invalid input! Please try again." << endl;
        break;
    }

    if (playerX == 4 && playerY == 0) {
      cout << "Congratulations! You reached the exit!" << endl;
      gameRunning = false;
    }
  }
}

#endif