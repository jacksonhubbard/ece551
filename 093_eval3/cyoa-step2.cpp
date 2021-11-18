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
        if (*navigationIterator > numPages) {
          // throw error= page with invalid reference
          cout << "invalid refernced page " << *navigationIterator;
          exit(EXIT_FAILURE);
        }
      }
    }

    if (!hasWinningPage || !hasLosingPage) {
      // throw error= no winnging/losing page
      cout << "no winning/losing page";
      exit(EXIT_FAILURE);
    }

    for (int i = 2; i < numPages; i++) {
      if (pagesReferenced.find(i) == pagesReferenced.end()) {
        // page i is not refernced
        //throw error= given page is not refernced
        cout << "given page is not refernced: " << i;
        exit(EXIT_FAILURE);
      }
    }
  }

  int interactWithPage(Page currentPage) {
    if (currentPage.winLossIndicator >= 0) {
      exit(EXIT_SUCCESS);
    }

    int nextPage;
    int maxNum = currentPage.referencedPages.size();

    cout << "Enter the page number of your choice: ";
    while (!(cin >> nextPage) || nextPage < 1 || nextPage > maxNum) {
      cin.clear();
      cin.ignore();
      cout << "That is not a valid choice, please try again\n";
      cout << "Enter the page number of your choice: ";
    }
    return currentPage.referencedPages[nextPage - 1];
    //return nextPage;
  }
};
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
