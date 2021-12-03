#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "Page.cpp"

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
  void checkValidStory();

  /*
  Allows the user to interact with the page passed in as parameter
  If the page is a winning/losing page, exit. If not, take in
  input from user on their next selection and return the page number
  */
  long interactWithPage(Page currentPage);

  /*
  Takes in a directory name and then checks for page 1. If present
  proceeds to read the remaining pages, and parse each page into story.
  Returns the built up story with all the pages inside it
  */
  Story buildupStory(string directoryName);

  /*
  Displays page 1, and then allows the user to interact with the page.
  Proceeds through whole story with the user's interactions
  */
  void playStory();

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
  void searchForDepths(int startVertex);

  /*
  Takes in a starting vertex and then searches story to
  find path to all winning pages. Templated over the type of worklist
  that is to be created (stack or a queue). Calls helper function
  to print the winning paths it discovered
  */
  template<typename Worklist>
  void searchForPaths(int vertex);

  /*
  Takes in an array of depths, which represent the depth of
  each page in the story. It then prints out the depths
  */
  void printDepths(int * depthArr);

  /*
  Takes in a vector of vectors that stores the paths through
  the story to a winning page. It then prints these out, along
  with the options the user must select on each page 
  */
  void printPaths(vector<vector<Page> > allPaths);
};
