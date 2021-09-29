#include "pandemic.h"

#include <stdio.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;

  char * name = strtok(line, ",");
  char * pop_string = strtok(NULL, ",");

  size_t len_name = strlen(name);

  if (len_name > 64) {
    char error_desc[] = "The country name is too long";
    printf("%s\n", error_desc);
    exit(EXIT_FAILURE);
  }

  // assign the country name currently stored in name to ans.name
  for (size_t i = 0; i < len_name; i++) {
    ans.name[i] = *(name + i);
  }
  ans.name[len_name] = '\0';

  uint64_t pop_int = atoi(pop_string);
  ans.population = pop_int;

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
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
  if (n_days < 7) {
    return;
  }

  uint64_t cases_times_100k;
  uint64_t sum_cases = 0;

  for (size_t day = 0; day < n_days; day++) {
    sum_cases += data[day];
    cases_times_100k = sum_cases * 100000;
    double cum_per_100k = (double)cases_times_100k / (double)pop;
    cum[day] = cum_per_100k;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (n_countries == 0 || n_days == 0) {
    return;
  }

  uint64_t max_cases = 0;
  int index_of_max_country =
      -1;  // initialized to -1 to indicate no current max, but will get updated to first country in for loop
  int tie_flag = 0;  // used as a marker to indicate if there is a tie in number of cases

  for (size_t country_index = 0; country_index < n_countries; country_index++) {
    for (size_t day = 0; day < n_days; day++) {
      uint64_t current_cases = data[country_index][day];
      if (current_cases > max_cases) {
        // current country/day pair is new max so reset fields and set tie_flag to 0 meaning no ties to the new max
        index_of_max_country = country_index;
        max_cases = current_cases;
        tie_flag = 0;
      }
      else if (current_cases == max_cases && (int)country_index != index_of_max_country) {
        // current country/day pair ties the max so set the tie_flag accordingly
        // only do this if the current country index is not the same as the current maxs country's index
        tie_flag = 1;
      }
    }
  }

  if (tie_flag) {
    printf("%s", "There is a tie between at least two countries\n");
  }
  else {
    printf("%s has the most daily cases with %u\n",
           countries[index_of_max_country].name,
           (int)max_cases);
  }
}
