#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Story.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  if (argc != 2) {
    // need to report error
    perror("invalid syntax, one parameter = directory name");
    return EXIT_FAILURE;
  }
  Story storyObject;
  string directoryName = argv[1];
  storyObject.buildupStory(directoryName);

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
