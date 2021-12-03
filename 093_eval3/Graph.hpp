#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "Story.hpp"

using namespace std;

class Graph {
 public:
  Story story;
  vector<int> currentPath;
  vector<vector<int> > allPaths;
  vector<bool> visited;

  Graph() :
      story(),
      currentPath(vector<int>()),
      allPaths(vector<vector<int> >()),
      visited(vector<bool>()) {}

  void pathsFromRoot() {
    vector<bool> visitedArr;
    cout << "here";
    for (int i = 0; i < story.numPages; i++) {
      visitedArr.push_back(false);
    }
    //int * path = new int[story.numPages];
    cout << "eher";
    vector<int> path;
    path.push_back(0);
    int visitedCount = 0;
    Page currPage = story.pages[0];
    pathHelper(currPage, visitedArr, path, visitedCount);
  }

  void pathHelper(Page currentPage,
                  vector<bool> & visitedArr,
                  vector<int> & path,
                  int visitedCount) {
    cout << "in func\n";
    visitedArr[currentPage.pageNumber - 1] = true;
    path[visitedCount] = currentPage.pageNumber;
    visitedCount++;

    if (currentPage.winLossIndicator == 1) {
      allPaths.push_back(path);
    }
    else if (currentPage.winLossIndicator == 0) {
    }
    else {
      for (size_t i = 0; i < currentPage.referencedPages.size(); i++) {
        if (visitedArr[currentPage.referencedPages[i]] == false) {
          pathHelper(story.pages[currentPage.referencedPages[i]],
                     visitedArr,
                     path,
                     visitedCount);
        }
      }
    }

    visitedArr[currentPage.pageNumber - 1] = false;
    visitedCount--;
  }

  void dfs(int pageNum) { dfsHelper(pageNum, vector<int>(), 0); }

  void dfsHelper(int pageNum, vector<int> path, int pathLength) {
    cout << "printing Paths\n";

    for (size_t j = 0; j < path.size(); j++) {
      cout << path[j] << ", ";
    }
    cout << endl;

    path[pathLength] = pageNum;
    pathLength++;
    Page currentPage = story.pages[pageNum];
    if (currentPage.winLossIndicator == 1) {
      allPaths.push_back(path);
    }
    else {
      for (size_t i = 0; i < currentPage.referencedPages.size(); i++) {
        dfsHelper(currentPage.referencedPages[i], path, pathLength);
      }
    }
  }

  /*
  Takes in a vector of vectors that stores the paths through
  the story to a winning page. It then prints these out, along
  with the options the user must select on each page 
  */
  void printPaths() {
    for (size_t i = 0; i < allPaths.size(); i++) {
      cout << "in first loop";
      vector<int> currPath = allPaths[i];
      for (size_t j = 0; j < currPath.size(); j++) {
        cout << "in second loop";
        Page currentPage = story.pages[currPath[j]];

        if (currentPage.winLossIndicator == 1) {
          cout << currentPage.pageNumber << "(win)\n";
        }
        else {  // not a winning page, so also print selection
          int selection = -1;
          // see which referencedPage is equal to next page in path
          for (size_t k = 0; k < currentPage.referencedPages.size(); k++) {
            if (currentPage.referencedPages[k] ==
                story.pages[currPath[j + 1]].pageNumber) {
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
