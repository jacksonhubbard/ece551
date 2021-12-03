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
      vector<int> currentPath = allPaths[i];
      for (size_t j = 0; j < currentPath.size(); j++) {
        Page currentPage = story.pages[currentPath[j]];

        if (currentPage.winLossIndicator == 1) {
          cout << currentPage.pageNumber << "(win)\n";
        }
        else {  // not a winning page, so also print selection
          int selection = -1;
          // see which referencedPage is equal to next page in path
          for (size_t k = 0; k < currentPage.referencedPages.size(); k++) {
            if (currentPage.referencedPages[k] ==
                story.pages[currentPath[j + 1]].pageNumber) {
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
