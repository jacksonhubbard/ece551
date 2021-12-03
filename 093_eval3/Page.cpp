#include "Page.hpp"
/*
Takes in a file, the index which represents the page number
and an indicaor variable specifying if it should print as it parses
Returns a Page object with data correctly parsed.
  */
Page Page::parseFile(ifstream & file, int index, bool print) {
  string line;
  bool navSectionDone = false;
  Page currentPage;
  int lineCount = 0;
  pageNumber = index;

  if (index < 0) {
    perror("page number must be positive");
    exit(EXIT_FAILURE);
  }
  while (std::getline(file, line)) {
    if (lineCount == 0 && line == "WIN") {
      winLossIndicator = 1;
    }
    else if (lineCount == 0 && line == "LOSE") {
      winLossIndicator = 0;
    }
    else if (!navSectionDone && line.find("#") == 0) {
      navSectionDone = true;
    }
    else if (!navSectionDone) {  // add line to navSection
      checkForValidNavSection(line);
      navigation_section.push_back(line);
    }
    else {  // add line to text
      text.push_back(line);
      if (print) {
        printf("%s\n", line.c_str());
      }
    }
    lineCount++;
  }
  return currentPage;
}
