#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

// step1
void parseFile(FILE * f);

// step2
int checkIndexForCategory(char * currentCategory, catarray_t * all_categories);
catarray_t * parseLine(char * line, catarray_t * all_categories);
void freeSingleCategory(category_t * currCategory);
void freeCatArray(catarray_t * all_categories);
catarray_t * parseFileForPairs(FILE * f, catarray_t * all_categories);

#endif
