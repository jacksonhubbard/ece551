#include <cstdlib>
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
  vector<int> referencedPages;

  Page() :
      navigation_section(vector<string>()),
      text(vector<string>()),
      winLossIndicator(-1),
      referencedPages(vector<int>()){};

  Page parseFile(ifstream & file, bool print) {
    string line;
    bool navSectionDone = false;
    Page currentPage;
    int lineCount = 0;
    while (std::getline(file, line)) {
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
        if (print) {
          printf("%s\n", line.c_str());
        }
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
  void addPageNumber() {
    int choiceNumber = 1;
    for (vector<string>::iterator it = navigation_section.begin();
         it != navigation_section.end();
         ++it) {
      size_t indexColon = it->find(":");
      if (indexColon == std::string::npos) {
        // throw error
      }
      else {
        string s = it->substr(0, indexColon);
        stringstream substring(s);

        int currentPageNumber = stoi(it->substr(0, indexColon));
        referencedPages.push_back(currentPageNumber);
      }
      choiceNumber++;
    }
  }
};
