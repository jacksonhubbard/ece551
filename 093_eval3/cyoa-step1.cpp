#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Page.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  if (argc != 2) {
    // need to report error
    return EXIT_FAILURE;
  }
  char * filename = argv[1];

  ifstream inputFile;
  inputFile.open(filename);
  if (inputFile.is_open()) {
    Page pageObject;

    //1. parse file and print line as we go
    pageObject.parseFile(inputFile, -1, true);
    pageObject.addPageNumber();
    //2.
    cout << "\n";
    if (pageObject.winLossIndicator == -1) {
      cout << "What would you like to do?\n\n";
      pageObject.printOptions();
    }
    else {
      switch (pageObject.winLossIndicator) {
        case 0:
          cout << "Sorry, you have lost. Better luck next time!\n";
          break;
        case 1:
          cout << "Congratulations! You have won. Hooray!\n";
          break;
      }
    }
    inputFile.close();
  }
  else {
    cerr << "Couldn't open file\n";
  }
  return EXIT_SUCCESS;
}
