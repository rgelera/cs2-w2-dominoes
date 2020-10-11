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
  ----- 
 |* * *|
 |* * *|
 |* * *|
 |-----|
 |* * *|
 |* * *|
 |* * *|
  -----
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

int main(int argc, char** argv) {
  const int SET_SIZE = 5;
  domino dominoSet[SET_SIZE] = {
    {1, 5},
    {6, 2},
    {3, 5},
    {0, 1},
    {4, 6}
  };

  printDominoes(dominoSet, SET_SIZE);

  return 0;
}