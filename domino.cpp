/* Define a struct that represents information about a single domino (Links to an external site.), keeping in mind that a single domino has two sets of 0 to 6 dots. You must decide what should be included and what the data types of the members will be.

In main(), declare an array of your domino structs that will store a double-six set of dominoes (Links to an external site.). (If you happen to know of more than one way to create arrays, make sure you are using a static array.) Write the necessary code using loop(s) needed to populate the array with all the dominoes in a set. The dominoes can be in any order.

Write code to sort the dominoes in a new order. You don’t need to write a function to do this, but may if you wish to.

Write code that prints the contents of the sorted dominoes array using asterisks (*) and any other characters needed, displaying them similar to how real dominoes would be laid out. When the program is run, it must be clear that your array has been sorted in a different order than it was created in. */

#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>

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
  cout << dot << "|";
}

void midRow(int num) {
  string dot;
  cout << "|";
  dot = (num >= 6) ? "* " : "  ";
  cout << dot;
  dot = (num % 2 == 1) ? "* " : "  "; 
  cout << dot;
  dot = (num >= 6) ? "*" : " ";
  cout << dot << "|";
}

void botRow(int num) {
  string dot;
  cout << "|";
  dot = (num >= 4) ? "*   " : "    ";
  cout << dot;
  dot = (num >= 2) ? "*" : " ";
  cout << dot << "|";
}

void printDominoSection(int num) {
  topRow(num);
  cout << endl;
  midRow(num);
  cout << endl;
  botRow(num);
  cout << endl;
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

// print dominoes horizontally

void printHorizontalBarRow(int num) {
  const string horizontalLine = "+-----+";
  for (int i = 0; i < num; i++) {
    cout << horizontalLine << " ";
  }
  cout << endl;
}

void printDominoesHRow(domino dominoSet[], int start, int dominoesPerRow, int SET_SIZE) {
  int extraDominoes = dominoesPerRow - (SET_SIZE - start);
  if (extraDominoes < 0) extraDominoes = 0;

  printHorizontalBarRow(dominoesPerRow - extraDominoes);

  // start top section
  for (int t = start; t < start + dominoesPerRow - extraDominoes; t++) {
    topRow(dominoSet[t].top);
    cout << " ";
  }
  cout << endl;

  for (int m = start; m < start + dominoesPerRow - extraDominoes; m++) {
    midRow(dominoSet[m].top);
    cout << " ";
  }
  cout << endl;

  for (int b = start; b < start + dominoesPerRow - extraDominoes; b++) {
    botRow(dominoSet[b].top);
    cout << " ";
  }
  cout << endl;

  printHorizontalBarRow(dominoesPerRow - extraDominoes);

  // start bot section
  for (int t = start; t < start + dominoesPerRow - extraDominoes; t++) {
    topRow(dominoSet[t].bottom);
    cout << " ";
  }
  cout << endl;

  for (int m = start; m < start + dominoesPerRow - extraDominoes; m++) {
    midRow(dominoSet[m].bottom);
    cout << " ";
  }
  cout << endl;

  for (int b = start; b < start + dominoesPerRow - extraDominoes; b++) {
    botRow(dominoSet[b].bottom);
    cout << " ";
  }
  cout << endl;

  printHorizontalBarRow(dominoesPerRow - extraDominoes);
}

void printDominoesH(domino dominoSet[], int SET_SIZE, int dominoesPerRow) {
  for (int i = 0; i < SET_SIZE; i = i + dominoesPerRow) {
    printDominoesHRow(dominoSet, i, dominoesPerRow, SET_SIZE);
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
  // terminal width size
  struct winsize ws;
  ioctl(0, TIOCGWINSZ, &ws);

  // domino size is 7 in length plus a space after means 8 per domino
  // ws.ws_col / 8 will be how many dominos per print
  const int DOMINO_WIDTH = 7;
  int dominoesPerRow = ws.ws_col / (DOMINO_WIDTH + 1);
  
  const int SET_SIZE = 49;

  domino *dominoSet = generateDominoSet();

  /* // Top lowest to highest, bottom lowest to highest
  printDominoes(dominoSet, SET_SIZE);

  // Bottom lowest to highest, top lowest to highest
  sortDominoSet(dominoSet, SET_SIZE);
  printDominoes(dominoSet, SET_SIZE); */

  printDominoesH(dominoSet, SET_SIZE, dominoesPerRow);
  sortDominoSet(dominoSet, SET_SIZE);
  printDominoesH(dominoSet, SET_SIZE, dominoesPerRow);

  return 0;
}