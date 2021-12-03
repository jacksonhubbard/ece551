#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
Class to represent a page of the story. The navigation section
is used for the options, winLossInidcator to state if the page
is a winning/losing page, referencedPages is to store
the page numbers of the options in the navigation section, and the
page number stores the page's page number.
*/
class Page {
 public:
  vector<string> navigation_section;
  vector<string> text;
  int winLossIndicator;  // 1 for win, 0 for loss, -1 for stillPlaying
  vector<long> referencedPages;
  long pageNumber;

  // Default constructor
  Page() :
      navigation_section(vector<string>()),
      text(vector<string>()),
      winLossIndicator(-1),
      referencedPages(vector<long>()),
      pageNumber(0){};

  /*
  Takes in a file, the index which represents the page number
  and an indicaor variable specifying if it should print as it parses
  Returns a Page object with data correctly parsed.
  */
  Page parseFile(ifstream & file, int index, bool print);

  /*
  Helper finction that takes in a line and exits the 
  program with an error message if it is not in the right format
  */
  void checkForValidNavSection(string line);

  /*
  Helper function that takes in a string and checks to see 
  if it is a valid number 
  */
  bool checkForValidNumber(const string & s);

  /*
  Displays the current page to the user and uses helper function
  to take in user's input to allow for interaction
  */
  void displayPage();

  /*
  Formats the navigation options and prints them out 
  Adjusts page number and gets rid of colon formatting
  */
  void printOptions();

  /*
  Helper function to add Page numbers to the referencedPages field
  of a given page
  */
  void addPageNumber();
};
