#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "Story.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  if (argc != 2) {
    perror("invalid syntax, one parameter = directory of story");
    return EXIT_FAILURE;
  }
  Story storyObject;
  string directoryName = argv[1];
  // read page files and build story
  storyObject.buildupStory(directoryName);

  // check if valid story
  storyObject.checkValidStory();

  //Page firstPage = storyObject.pages[0];

  storyObject.searchForDepths<queue<int> >(0);

  //  storyObject.search(0);
  return EXIT_SUCCESS;
}
