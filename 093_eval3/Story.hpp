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

    //cout << "Enter the page number of your choice: ";
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
