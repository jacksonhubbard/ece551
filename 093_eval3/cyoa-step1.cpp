#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Page {
 public:
  vector<string> navigation_section;
  vector<string> text;
  int winLossIndicator;  // 1 for win, 0 for loss, -1 for stillPlaying

  Page() :
      navigation_section(vector<string>()),
      text(vector<string>()),
      winLossIndicator(-1){};

  Page parseFile(ifstream & file) {
    string line;
    bool navSectionDone = false;
    Page currentPage;
    int lineCount = 0;
    while (std::getline(file, line)) {
      //      printf("%s\n", line.c_str());
      if (lineCount == 0 && line == "WIN") {
        winLossIndicator = 1;
      }
      else if (lineCount == 0 && line == "LOSE") {
        winLossIndicator = 0;
      }
      if (!navSectionDone && line.find("#") == 0) {
        navSectionDone = true;
      }
      else if (!navSectionDone) {
        navigation_section.push_back(line);
      }
      else {
        text.push_back(line);
        printf("%s\n", line.c_str());
      }
      lineCount++;
    }
    return currentPage;
  };

  void printOptions() {
    int choiceNumber = 1;
    for (vector<string>::iterator it = navigation_section.begin();
         it != navigation_section.end();
         ++it) {
      size_t indexColon = it->find(":");
      if (indexColon == std::string::npos) {
        // throw error
      }
      else {
        string currentChoice = it->substr(indexColon + 1);
        cout << " " << choiceNumber << ". " << currentChoice << "\n";
      }
      choiceNumber++;
    }
  }
};

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
    pageObject.parseFile(inputFile);

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