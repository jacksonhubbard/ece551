#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "Story.hpp"

using namespace std;

int main(int argc, char * argv[]) {
  if (argc != 2) {
    perror("invalid syntax, one parameter = directory name");
    return EXIT_FAILURE;
  }
  Story storyObject;
  string directoryName = argv[1];
  // read page files and build story
  storyObject.buildupStory(directoryName);

  // check if valid story
  storyObject.checkValidStory();

  // allow user to play story (read through it and interact)
  storyObject.playStory();

  return EXIT_SUCCESS;
}
