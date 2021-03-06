#include "Story.hpp"

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/*
  Function to check if a story is valid. It is valid if it contains
  at least 1 winning page, at least one losing page, every page is referenced,
  and every reference is to a valid page. 
  */
void Story::checkValidStory() {
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
    for (vector<long>::iterator navigationIterator = it->referencedPages.begin();
         navigationIterator != it->referencedPages.end();
         ++navigationIterator) {
      // add current referenced page to set
      pagesReferenced.insert(*navigationIterator);
      if (*navigationIterator > numPages) {
        // throw error= page with invalid reference
        perror("invalid refernced page ");
        exit(EXIT_FAILURE);
      }
    }
  }
  if (!hasWinningPage || !hasLosingPage) {
    // throw error= no winnging/losing page
    perror("no winning/losing page");
    exit(EXIT_FAILURE);
  }
  // check every page is referenced 1+ times
  for (int i = 2; i < numPages; i++) {
    if (pagesReferenced.find(i) == pagesReferenced.end()) {
      perror("given page is not refernced");
      exit(EXIT_FAILURE);
    }
  }
}

/*
  Allows the user to interact with the page passed in as parameter
  If the page is a winning/losing page, exit. If not, take in
  input from user on their next selection and return the page number
  */
long Story::interactWithPage(Page currentPage) {
  if (currentPage.winLossIndicator >= 0) {
    exit(EXIT_SUCCESS);
  }
  long nextPage;
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
Story Story::buildupStory(string directoryName) {
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
    if (!input) {  // no page i, break
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
void Story::playStory() {
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

/*
  Takes in a starting vertex and then searches story to
  find depth of each page. Templated over the type of worklist
  that is to be created (stack or a queue). Calls helper function
  to print the depth of each page it discovered 
  */
template<typename Worklist>
void Story::searchForDepths(int startVertex) {
  Worklist todo;
  bool * visitedArr = new bool[numPages];
  for (long i = 0; i < numPages; i++) {
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
    long pageIndex = nextHelper(todo);
    todo.pop();

    currentPage = pages[pageIndex];
    if (currentPage.winLossIndicator < 0) {
      vector<long> referencedPages = currentPage.referencedPages;
      for (size_t i = 0; i < referencedPages.size(); i++) {
        long referencedPageIndex = referencedPages[i] - 1;
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

/*
  Takes in a starting vertex and then searches story to
  find path to all winning pages. Templated over the type of worklist
  that is to be created (stack or a queue). Calls helper function
  to print the winning paths it discovered
  */
template<typename Worklist>
void Story::searchForPaths(int vertex) {
  Worklist todo;
  bool * visitedArr = new bool[numPages + 1];
  for (long i = 0; i <= numPages; i++) {
    visitedArr[i] = false;
  }
  todo.push(vertex);
  Page currentPage;
  int currentDepth = 0;
  vector<Page> currentPath;
  vector<vector<Page> > allPaths;

  while (todo.size() != 0) {
    currentDepth++;
    long pageIndex = nextHelper(todo);
    visitedArr[pageIndex] = true;
    todo.pop();
    currentPage = pages[pageIndex];
    currentPath.push_back(currentPage);
    if (currentPage.winLossIndicator < 0) {
      vector<long> referencedPages = currentPage.referencedPages;
      for (size_t i = 0; i < referencedPages.size(); i++) {
        long pageIndex2 = referencedPages[i];
        if (visitedArr[pageIndex2] == false) {
          todo.push(pageIndex2);
        }
      }
    }
    else {
      //if winning page, add currentPath to allPaths
      if (currentPage.winLossIndicator == 1) {
        allPaths.push_back(currentPath);
      }
      // delete nodes as we recurse up
      bool needToDelete = true;
      while (needToDelete) {
        // if child page is not visited, don't delete
        if (currentPath.size() > 1) {
          currentPath.pop_back();
          Page currPage = currentPath.back();
          for (size_t j = 0; j < currPage.referencedPages.size(); j++) {
            long refPage = currPage.referencedPages[j];
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
void Story::printDepths(int * depthArr) {
  for (long i = 0; i < numPages; i++) {
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
void Story::printPaths(vector<vector<Page> > allPaths) {
  if (allPaths.size() == 0) {
    cout << "This story is unwinnable!\n";
  }
  for (size_t i = 0; i < allPaths.size(); i++) {
    vector<Page> currentPath = allPaths[i];
    for (size_t j = 0; j < currentPath.size(); j++) {
      Page currentPage = currentPath[j];

      if (currentPage.winLossIndicator == 1) {
        cout << currentPage.pageNumber << "(win)\n";
      }
      else {  // not a winning page, so also print selection
        long selection = -1;
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
