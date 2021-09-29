#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;

  char * name = strtok(line, ",");
  char * pop_string = strtok(NULL, ",");

  size_t len_name = strlen(name);

  if (len_name > 64) {
    char error_desc[] = "The country name is too long";
    printf("%s\n", error_desc);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < len_name; i++) {
    ans.name[i] = *(name + i);
  }
  ans.name[len_name] = '\0';

  uint64_t pop_int = atoi(pop_string);
  ans.population = pop_int;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < 7) {
    return;
  }
  int sum = 0;
  for (size_t day = 0; day < (n_days - 6); day++) {
    sum = 0;
    for (size_t day_offset = day; day_offset < (day + 7); day_offset++) {
      sum += data[day_offset];
    }
    double curr_avg = sum / 7.0;
    avg[day] = curr_avg;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (n_days < 7) {
    return;
  }

  uint64_t cases_times_100k;
  //printf("pop: %lu\n", pop);
  uint64_t sum_cases = 0;

  for (size_t day = 0; day < n_days; day++) {
    sum_cases += data[day];
    cases_times_100k = sum_cases * 100000;
    //    printf("cases: %d\n", data[day]);
    // printf("cases * 100k: %li\n", cases_times_100k);
    double cum_per_100k = (double)cases_times_100k / (double)pop;
    //printf("cum per 100k: %f\n", cum_per_100k);
    cum[day] = cum_per_100k;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
