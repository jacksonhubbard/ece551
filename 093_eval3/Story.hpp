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

/*
Class that represents a story. Uses a vector of Pages, an indicator
variable on if it has a winning page and if it has a losing page, and
a int variable to store the total number of pages.
 */
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

  /*
  Function to check if a story is valid. It is valid if it contains
  at least 1 winning page, at least one losing page, every page is referenced,
  and every reference is to a valid page. 
  */
  void checkValidStory() {
    set<int> pagesReferenced;
    // set indicators for if it contains a winning and losing page
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
    // check every page is referenced 1+ times
    for (int i = 2; i < numPages; i++) {
      if (pagesReferenced.find(i) == pagesReferenced.end()) {
        cout << "given page is not refernced: " << i;
        exit(EXIT_FAILURE);
      }
    }
  }

  /*
  Allows the user to interact with the page passed in as parameter
  If the page is a winning/losing page, exit. If not, take in
  input from user on their next selection and return the page number
  */
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

  /*
  Takes in a directory name and then checks for page 1. If present
  proceeds to read the remaining pages, and parse each page into story.
  Returns the built up story with all the pages inside it
  */
  Story buildupStory(string directoryName) {
    string baseFileName = directoryName + "/page";
    string page1Name = baseFileName + "1.txt";
    std::ifstream input(page1Name.c_str());
    if (!input) {
      perror("no page 1, cannot proceed");
      exit(EXIT_FAILURE);
    }
    Page pageObject;
    pageObject.parseFile(input, 1, false);  // do not print as we go
    pageObject.addPageNumber();
    pages.push_back(pageObject);
    numPages++;

    int i = 2;
    bool lookingForFiles = true;
    while (lookingForFiles) {
      stringstream ss;
      ss << i;
      string i_str;
      ss >> i_str;
      std::ifstream input((baseFileName + i_str + ".txt").c_str());
      if (!input) {
        // no page i, break
        lookingForFiles = false;
      }
      else {
        Page pageObject;
        pageObject.parseFile(input, i, false);  // do not print as we go
        pageObject.addPageNumber();
        pages.push_back(pageObject);
        numPages++;
        i++;
      }
    }
    return *this;
  }

  /*
  Displays page 1, and then allows the user to interact with the page.
  Proceeds through whole story with the user's interactions
  */
  void playStory() {
    // start with page1, display it
    Page page1 = pages.front();
    page1.displayPage();

    // user selects page number, go to that pageObject in vector and display it
    int nextPage = interactWithPage(page1);
    while (true) {  // will exit when story is won/lost
      for (vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it) {
        if (it->pageNumber == nextPage) {
          Page pageToDisplay = *it;
          pageToDisplay.displayPage();
          nextPage = interactWithPage(pageToDisplay);
        }
      }
    }
  }

  // Helper functions to return next element from stack/queue
  // Uses parametric polymorphism to call correct nextHelper()
  int nextHelper(stack<int> s) { return s.top(); }
  int nextHelper(queue<int> q) { return q.front(); }

  /*
  Takes in a starting vertex and then searches story to
  find depth of each page. Templated over the type of worklist
  that is to be created (stack or a queue). Calls helper function
  to print the depth of each page it discovered 
  */
  template<typename Worklist>
  void searchForDepths(int startVertex) {
    Worklist todo;
    bool * visitedArr = new bool[numPages];
    for (int i = 0; i < numPages; i++) {
      visitedArr[i] = false;
    }
    visitedArr[startVertex] = true;
    todo.push(startVertex);

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
          int referencedPageIndex = referencedPages[i] - 1;
          if (visitedArr[referencedPageIndex] == false) {
            visitedArr[referencedPageIndex] = true;
            todo.push(referencedPageIndex);
            // referencedPage depth is one more than currnt page depth
            depthArr[referencedPageIndex] = depthArr[pageIndex] + 1;
          }
        }
      }
    }
    printDepths(depthArr);
    delete[] depthArr;
    delete[] visitedArr;
  }

  template<typename Worklist>
  void searchForPaths(int vertex) {
    Worklist todo;
    bool * visitedArr = new bool[numPages + 1];
    for (int i = 0; i <= numPages; i++) {
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
          if (visitedArr[pageIndex2] == false) {
            visitedArr[pageIndex2] = true;
            todo.push(pageIndex2);
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
          //          currentPath.pop_back();
          // if child page is not visited, don't delete
          if (currentPath.size() > 1) {
            currentPath.pop_back();
            Page currPage = currentPath.back();
            for (size_t j = 0; j < currPage.referencedPages.size(); j++) {
              int refPage = currPage.referencedPages[j];
              //cout << refPage << endl;
              //              cout << visitedArr[refPage] << endl;
              if (visitedArr[refPage] == false) {
                needToDelete = false;
              }
            }
          }
          else {
            needToDelete = false;
          }
        }
      }
    }
    printPaths(allPaths);
    delete[] visitedArr;
  }
  /*
  Takes in an array of depths, which represent the depth of
  each page in the story. It then prints out the depths
  */
  void printDepths(int * depthArr) {
    for (int i = 0; i < numPages; i++) {
      if (depthArr[i] == -1) {  // value -1 indicates not reachable
        cout << "Page " << i + 1 << " is not reachable\n";
      }
      else {
        cout << "Page " << i + 1 << ":" << depthArr[i] << "\n";
      }
    }
  }

  /*
  Takes in a vector of vectors that stores the paths through
  the story to a winning page. It then prints these out, along
  with the options the user must select on each page 
  */
  void printPaths(vector<vector<Page> > allPaths) {
    for (size_t i = 0; i < allPaths.size(); i++) {
      vector<Page> currentPath = allPaths[i];
      for (size_t j = 0; j < currentPath.size(); j++) {
        Page currentPage = currentPath[j];

        if (currentPage.winLossIndicator == 1) {
          cout << currentPage.pageNumber << "(win)\n";
        }
        else {  // not a winning page, so also print selection
          int selection = -1;
          // see which referencedPage is equal to next page in path
          for (size_t k = 0; k < currentPage.referencedPages.size(); k++) {
            if (currentPage.referencedPages[k] == currentPath[j + 1].pageNumber) {
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
