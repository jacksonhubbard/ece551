#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

//#include "Story.hpp"
#include "Graph.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  if (argc != 2) {
    // need to report error
    perror("invalid syntax, one parameter = directory of story");
    return EXIT_FAILURE;
  }
  Story storyObject;

  // check dir for page1.txt
  string directoryName = argv[1];
  // read page files and build story
  storyObject.buildupStory(directoryName);

  // check if valid story
  storyObject.checkValidStory();

  // call path finding helper function
  storyObject.searchForPaths<stack<int> >(0);

  //Graph graph;
  //graph.story = storyObject;
  //cout << "assigned storyto graph\n";
  // //for (int i = 0; i <= storyObject.numPages; i++) {
  ////  graph.visited.push_back(false);
  //// }
  //graph.pathsFromRoot();

  ////graph.dfs(0);
  //cout << "printing paths" << endl;
  //graph.printPaths();
  return EXIT_SUCCESS;
}
