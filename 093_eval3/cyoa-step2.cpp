#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

// #include "Page.hpp"
#include "Story.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  //  cout << "in main\n";

  if (argc != 2) {
    // need to report error
    return EXIT_FAILURE;
  }
  Story storyObject;

  // check dir for page1.txt
  string directoryName = argv[1];
  string baseFileName = directoryName + "/page";
  string page1Name = baseFileName + "1.txt";
  std::ifstream input(page1Name.c_str());
  if (!input) {
    // no page 1, throw error
  }
  // read pag1
  Page pageObject;
  pageObject.parseFile(input, 1, false);  // do not print as we go
  pageObject.addPageNumber();
  storyObject.pages.push_back(pageObject);
  storyObject.numPages++;

  // while loop over pages, incremint i to check
  // store up list of files
  int i = 2;
  bool lookingForFiles = true;
  while (lookingForFiles) {
    //cout << i << "\n";
    stringstream ss;
    ss << i;
    string i_str;
    ss >> i_str;
    std::ifstream input((baseFileName + i_str + ".txt").c_str());
    //cout << baseFileName;

    if (!input) {
      // no page i, break
      lookingForFiles = false;
    }
    else {
      //      cout << "parsing page " << i << "\n";
      Page pageObject;
      pageObject.parseFile(input, i, false);  // do not print as we go
      pageObject.addPageNumber();
      storyObject.pages.push_back(pageObject);
      storyObject.numPages++;
      i++;
    }
  }

  // read current file, check if WIN/LOSE and reference pages
  storyObject.checkValidStory();

  // start with page1, display it
  Page page1 = storyObject.pages.front();
  page1.displayPage();

  // user selects page number, go to that pageObject in vector and display it
  int nextPage = storyObject.interactWithPage(page1);

  while (true) {
    for (vector<Page>::iterator it = storyObject.pages.begin();
         it != storyObject.pages.end();
         ++it) {
      if (it->pageNumber == nextPage) {
        Page pageToDisplay = *it;
        pageToDisplay.displayPage();
        nextPage = storyObject.interactWithPage(pageToDisplay);
      }
    }
  }

  return EXIT_SUCCESS;
}
