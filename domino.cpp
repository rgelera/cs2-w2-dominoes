/* Define a struct that represents information about a single domino (Links to an external site.), keeping in mind that a single domino has two sets of 0 to 6 dots. You must decide what should be included and what the data types of the members will be.

In main(), declare an array of your domino structs that will store a double-six set of dominoes (Links to an external site.). (If you happen to know of more than one way to create arrays, make sure you are using a static array.) Write the necessary code using loop(s) needed to populate the array with all the dominoes in a set. The dominoes can be in any order.

Write code to sort the dominoes in a new order. You don’t need to write a function to do this, but may if you wish to.

Write code that prints the contents of the sorted dominoes array using asterisks (*) and any other characters needed, displaying them similar to how real dominoes would be laid out. When the program is run, it must be clear that your array has been sorted in a different order than it was created in. */

#include <iostream>

using namespace std;

struct domino {
  int top;
  int bottom;
};

void topRow(int num) {
  string dot;
  cout << "|";
  dot = (num >= 2) ? "*   " : "    ";
  cout << dot;
  dot = (num >= 4) ? "*" : " ";
  cout << dot << "|" << endl;
}

void midRow(int num) {
  string dot;
  cout << "|";
  dot = (num >= 6) ? "* " : "  ";
  cout << dot;
  dot = (num % 2 == 1) ? "* " : "  "; 
  cout << dot;
  dot = (num >= 6) ? "*" : " ";
  cout << dot << "|" << endl;
}

void botRow(int num) {
  string dot;
  cout << "|";
  dot = (num >= 4) ? "*   " : "    ";
  cout << dot;
  dot = (num >= 2) ? "*" : " ";
  cout << dot << "|" << endl;
}

void printDominoSection(int num) {
  topRow(num);
  midRow(num);
  botRow(num);
}

/* 
 +-----+ 
 |* * *|
 |* * *|
 |* * *|
 +-----+
 |* * *|
 |* * *|
 |* * *|
 +-----+
 */
void printDomino(domino domino) {
  const string horizontalLine = "+-----+";
  cout << horizontalLine << endl;
  printDominoSection(domino.top);
  cout << horizontalLine << endl;
  printDominoSection(domino.bottom);
  cout << horizontalLine << endl;
}

void printDominoes(domino dominoSet[], int SET_SIZE) {
  for (int i = 0; i < SET_SIZE; i++) {
    printDomino(dominoSet[i]);
  }
}

domino* generateDominoSet() {
  domino *dominoSet = new domino[49];
  int count = 0;

  for (int top = 0; top <= 6; top++) {
    for (int bottom = 0; bottom <= 6; bottom++) {
      domino domino;
      domino.top = top;
      domino.bottom = bottom;

      dominoSet[count] = domino;
      count++;
    }
  }

  return dominoSet;
}

// return true if a >= b, bottom of domino having more priority
bool compareDominos(domino a, domino b) {
  if (a.bottom > b.bottom) {
    return true;
  } else if (a.bottom == b.bottom) {
    return a.top >= b.top;
  } else {
    return false;
  }
}

/*
  Insertion sort by bottom domino lowest to highest, then top lowest to highest
  {0, 0}, {1, 0} {2, 0}... {0, 1}, {1, 1}, ...
 */
void sortDominoSet(domino *dominoSet, int SET_SIZE) {
  int i, j;
  domino curr;
  for (i = 1; i < SET_SIZE; i++) {
    curr = dominoSet[i];
    j = i - 1;
    
    while (j >= 0 && compareDominos(dominoSet[j], curr)) {
      dominoSet[j + 1] = dominoSet[j];
      j = j - 1;
    }
    dominoSet[j + 1] = curr;
  }
}

int main(int argc, char** argv) {
  const int SET_SIZE = 49;

  domino *dominoSet = generateDominoSet();

  // Top lowest to highest, bottom lowest to highest
  printDominoes(dominoSet, SET_SIZE);

  // Bottom lowest to highest, top lowest to highest
  sortDominoSet(dominoSet, SET_SIZE);
  printDominoes(dominoSet, SET_SIZE);

  return 0;
}