#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
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

    while (!(cin >> nextPage) || nextPage < 1 || nextPage > maxNum) {
      cin.clear();
      cin.ignore();
      cout << "That is not a valid choice, please try again\n";
      cout << "Enter the page number of your choice: ";
    }
    return currentPage.referencedPages[nextPage - 1];
  }

  int nextHelper(stack<int> s) { return s.top(); }
  int nextHelper(queue<int> q) { return q.front(); }

  template<typename Worklist>
  void search(int vertex) {
    Worklist todo;
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
      currentDepth++;
      int pageIndex = nextHelper(todo);
      todo.pop();

      currentPage = pages[pageIndex];
      if (currentPage.winLossIndicator < 0) {
        vector<int> referencedPages = currentPage.referencedPages;
        for (size_t i = 0; i < referencedPages.size(); i++) {
          int pageIndex2 = referencedPages[i];
          if (visitedArr[pageIndex2 - 1] == false) {
            visitedArr[pageIndex2 - 1] = true;
            todo.push(pageIndex2 - 1);
            depthArr[pageIndex2 - 1] = depthArr[pageIndex] + 1;
          }
        }
      }
    }
    printDepths(depthArr);
    delete[] depthArr;
    delete[] visitedArr;
  }

  template<typename Worklist>
  void search2(int vertex) {
    Worklist todo;
    bool * visitedArr = new bool[numPages];
    for (int i = 0; i < numPages; i++) {
      visitedArr[i] = false;
    }
    visitedArr[vertex] = true;
    todo.push(vertex);

    Page currentPage;
    int currentDepth = 0;

    vector<Page> currentPath;
    vector<vector<Page> > allPaths;

    while (todo.size() != 0) {
      currentDepth++;
      int pageIndex = nextHelper(todo);
      //      cout << "in while loop with page: " << pageIndex << "\n";
      todo.pop();
      currentPage = pages[pageIndex];
      currentPath.push_back(currentPage);
      //      cout << "just added " << currentPage.pageNumber << "to currrentPath" << endl;
      //cout << "printing current Path\n";
      //for (size_t d = 0; d < currentPath.size(); d++) {
      //cout << currentPath[d].pageNumber << ", ";
      //}
      //cout << endl;

      if (currentPage.winLossIndicator < 0) {
        vector<int> referencedPages = currentPage.referencedPages;
        for (size_t i = 0; i < referencedPages.size(); i++) {
          int pageIndex2 = referencedPages[i];
          if (visitedArr[pageIndex2 - 1] == false) {
            visitedArr[pageIndex2 - 1] = true;
            todo.push(pageIndex2 - 1);
          }
        }
      }
      else {
        visitedArr[pageIndex] = true;
        //if winning page, add currentPath to allPaths
        if (currentPage.winLossIndicator == 1) {
          allPaths.push_back(currentPath);
        }

        bool needToDelete = true;
        while (needToDelete) {
          currentPath.pop_back();
          // if child page is not visited, don't delete
          Page currPage = currentPath.back();
          for (size_t j = 0; j < currPage.referencedPages.size(); j++) {
            int refPage = currPage.referencedPages[j];
            if (visitedArr[refPage] == false) {
              needToDelete = false;
            }
          }
        }
      }
    }
    printPaths(allPaths);
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

  void printPaths(vector<vector<Page> > allPaths) {
    for (size_t i = 0; i < allPaths.size(); i++) {
      vector<Page> currentPath = allPaths[i];
      //      cout << "currPath size " << currentPath.size() << endl;
      for (size_t j = 0; j < currentPath.size(); j++) {
        Page currentPage = currentPath[j];
        //cout << currentPage.pageNumber;

        if (currentPage.winLossIndicator == 1) {
          cout << currentPage.pageNumber << "(win)\n";
        }
        else {
          int selection = -1;
          for (size_t k = 0; k < currentPage.referencedPages.size(); k++) {
            if (currentPage.referencedPages[k] == currentPath[j + 1].pageNumber) {
              //              selection = currentPage.referencedPages[k];
              selection = k + 1;
            }
          }
          if (selection != -1) {
            cout << currentPage.pageNumber << "(" << selection << ")";
          }
        }
      }
    }
  }
};
