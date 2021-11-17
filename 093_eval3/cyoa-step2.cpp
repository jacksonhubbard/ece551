#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Page.hpp"

using namespace std;

class Story {
 public:
  vector<Page> pages;
  bool hasWinningPage;
  bool hasLosingPage;
  int numPages;

  Story() :
      pages(vector<Page>()),
      hasWinningPage(false),
      hasLosingPage(false),
      numPages(0){};

  void checkValidStory() {
    set<int> pagesReferenced;

    // check if winning and losing page
    for (vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
      if (it->winLossIndicator == 0) {
        hasLosingPage = true;
      }
      if (it->winLossIndicator == 1) {
        hasWinningPage = true;
      }

      // check each referenced page of the current page is valid (less than numPages)
      for (vector<int>::iterator navigationIterator = it->referencedPages.begin();
           navigationIterator != it->referencedPages.end();
           ++navigationIterator) {
        // add current referenced page to set
        pagesReferenced.insert(*navigationIterator);
        if (*navigationIterator >= numPages) {
          // throw error= page with invalid reference
          cout << "invalid refernced page" << to_string(*navigationIterator);
          exit(EXIT_FAILURE);
        }
      }
    }

    if (!hasWinningPage || !hasLosingPage) {
      // throw error= no winnging/losing page
      cout << "no winnging/losing page";
      exit(EXIT_FAILURE);
    }

    for (int i = 1; i < numPages; i++) {
      if (pagesReferenced.find(i) == pagesReferenced.end()) {
        // page i is not refernced
        //throw error= given page is not refernced
        cout << "given page is not refernced";
        exit(EXIT_FAILURE);
      }
    }
  }

  void interactWithPage() {}
};
int main(int argc, char * argv[]) {
  if (argc != 2) {
    // need to report error
    return EXIT_FAILURE;
  }
  Story storyObject;

  // check dir for page1.txt
  string directoryName = argv[1];
  string baseFileName = directoryName + "/page";

  std::ifstream input(baseFileName + "1.txt");
  if (!input) {
    // no page 1, throw error
  }
  // read pag1
  Page pageObject;
  pageObject.parseFile(input, false);  // do not print as we go
  storyObject.pages.push_back(pageObject);
  storyObject.numPages++;

  // while loop over pages, incremint i to check
  // store up list of files
  int i = 2;
  bool lookingForFiles = true;
  while (lookingForFiles) {
    std::ifstream input(baseFileName + to_string(i) + ".txt");
    if (!input) {
      // no page i, break
      lookingForFiles = false;
    }
    else {
      Page pageObject;
      pageObject.parseFile(input, false);  // do not print as we go
      storyObject.pages.push_back(pageObject);
      storyObject.numPages++;
      i++;
    }
  }

  // read current file, check if WIN/LOSE and reference pages
  storyObject.checkValidStory();

  // start with page1, display it

  // user selects page number, go to that pageObject in vector and display it
  storyObject.interactWithPage();
  return EXIT_SUCCESS;
}
