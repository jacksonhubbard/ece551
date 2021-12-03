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

/*
  Helper finction that takes in a line and exits the 
  program with an error message if it is not in the right format
  */
void Page::checkForValidNavSection(string line) {
  size_t indexColon = line.find(":");
  if (indexColon == std::string::npos) {
    perror("invalid page syntax, no colon");
    exit(EXIT_FAILURE);
  }
  else {
    string pageNumber = line.substr(0, indexColon);
    if (!(checkForValidNumber(pageNumber))) {
      perror("invalid page syntax, not a number");
      exit(EXIT_FAILURE);
    }
  }
}

/*
  Helper function that takes in a string and checks to see 
  if it is a valid number 
  */
bool Page::checkForValidNumber(const string & s) {
  if (s.empty()) {
    return false;
  }
  else {
    string::const_iterator it = s.begin();
    while (it != s.end()) {
      if (!(isdigit(*it))) {
        return false;
      }
      it++;
    }
    return true;
  }
}

/*
Displays the current page to the user and uses helper function
to take in user's input to allow for interaction
  */
void Page::displayPage() {
  // print the text
  for (vector<string>::iterator it = text.begin(); it != text.end(); it++) {
    cout << *it << "\n";
  }
  cout << "\n";
  if (winLossIndicator == -1) {
    cout << "What would you like to do?\n\n";
    printOptions();
  }
  else {
    switch (winLossIndicator) {
      case 0:
        cout << "Sorry, you have lost. Better luck next time!\n";
        break;
      case 1:
        cout << "Congratulations! You have won. Hooray!\n";
        break;
    }
  }
}

/*
Formats the navigation options and prints them out 
Adjusts page number and gets rid of colon formatting
  */
void Page::printOptions() {
  int choiceNumber = 1;
  for (vector<string>::iterator it = navigation_section.begin();
       it != navigation_section.end();
       ++it) {
    size_t indexColon = it->find(":");
    if (indexColon == std::string::npos) {
      perror("invalid page syntax");
      exit(EXIT_FAILURE);
    }
    else {
      string currentChoice = it->substr(indexColon + 1);
      cout << " " << choiceNumber << ". " << currentChoice << "\n";
    }
    choiceNumber++;
  }
}

/*
  Helper function to add Page numbers to the referencedPages field
  of a given page
  */
void Page::addPageNumber() {
  int choiceNumber = 1;
  for (vector<string>::iterator it = navigation_section.begin();
       it != navigation_section.end();
       ++it) {
    size_t indexColon = it->find(":");
    if (indexColon == std::string::npos) {
      // throw error
      //        perror("invalid page syntax\n");
      //        exit(EXIT_FAILURE);
    }
    else {
      // convert substring to int to add to referencedPages
      string s = it->substr(0, indexColon);
      stringstream substring(s);
      int currentPageNumber = -1;
      substring >> currentPageNumber;
      referencedPages.push_back(currentPageNumber);
    }
    choiceNumber++;
  }
}
