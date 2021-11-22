#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
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

  //  template<typename Worklist>
  void search(int vertex) {
    //Worklist todo;
    queue<int> todo;

    bool * visitedArr = new bool[numPages];
    for (int i = 0; i < numPages; i++) {
      visitedArr[i] = false;
    }
    visitedArr[vertex] = true;
    todo.push(vertex);

    Page currentPage;

    int currentDepth = 0;
    int * depthArr = new int[numPages];
    for (int i = 0; i < numPages; i++) {
      depthArr[i] = -1;
    }
    depthArr[0] = currentDepth;

    while (todo.size() != 0) {
      //      cout << "in while\n";
      currentDepth++;
      int pageIndex = todo.front();
      todo.pop();
      currentPage = pages[pageIndex];
      if (currentPage.winLossIndicator < 0) {
        vector<int> referencedPages = currentPage.referencedPages;
        //        cout << "Page: " << pageIndex << referencedPages[0] << referencedPages[1]
        //     << referencedPages[2] << "\n";

        for (size_t i = 0; i < referencedPages.size(); i++) {
          int pageIndex2 = referencedPages[i];
          if (visitedArr[pageIndex2 - 1] == false) {
            visitedArr[pageIndex2 - 1] = true;
            todo.push(pageIndex2 - 1);
            depthArr[pageIndex2 - 1] = depthArr[pageIndex] + 1;
          }
        }
      }
      //currentDepth++;
    }
    printDepths(depthArr);
    //    free(depthArr);
    //free(visitedArr);
    delete[] depthArr;
    delete[] visitedArr;
  }

  void printDepths(int * depthArr) {
    for (int i = 0; i < numPages; i++) {
      if (depthArr[i] == -1) {
        cout << "Page " << i + 1 << " is not reachable\n";
      }
      else {
        cout << "Page " << i + 1 << ":" << depthArr[i] << "\n";
      }
    }
  }
};
