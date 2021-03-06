#include <algorithm>  // std::sort
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void noInputs() {
  string line;
  vector<string> strings;

  while (std::getline(std::cin, line)) {
    strings.push_back(line);
  }

  std::sort(strings.begin(), strings.end());
  for (std::vector<string>::iterator it = strings.begin(); it != strings.end(); ++it)
    std::cout << *it << "\n";
}

void inputs(char * filename) {
  string line;
  vector<string> strings;

  ifstream file(filename);
  if (file.is_open()) {
    while (getline(file, line)) {
      //     cout << line << '\n';
      strings.push_back(line);
    }
    file.close();
  }
  else {
    perror("Could not open file");
    cout << "Unable to open file";
    exit(EXIT_FAILURE);
  }
  std::sort(strings.begin(), strings.end());
  for (std::vector<string>::iterator it = strings.begin(); it != strings.end(); ++it)
    std::cout << *it << "\n";
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!

  if (argc == 1) {
    noInputs();
  }
  else {
    for (int i = 1; i < argc; i++) {
      inputs(argv[i]);
    }
  }

  return EXIT_SUCCESS;
}
