#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double invest(retire_info currentInfo, double currentBalance, int currentAgeInMonths) {
  int ageYears = currentAgeInMonths / 12;
  int ageMonths = currentAgeInMonths % 12;

  printf("Age %3d month %2d you have $%.2lf\n", ageYears, ageMonths, currentBalance);

  double currentContribution = currentInfo.contribution;
  double rateOfReturn = currentInfo.rate_of_return;

  double previousMult = currentBalance * rateOfReturn;
  double newBalance = currentBalance + previousMult + currentContribution;

  return newBalance;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int workingMonth = 0;
  int retiredMonth = 0;
  double currentBalance = initial;

  while (workingMonth < working.months) {
    // do working calc
    currentBalance = invest(working, currentBalance, startAge + workingMonth);
    workingMonth++;
  }

  while (retiredMonth < retired.months) {
    // do retired calc
    currentBalance =
        invest(retired, currentBalance, startAge + workingMonth + retiredMonth);
    retiredMonth++;
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000.0;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000.0;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345.0, working, retired);
  return EXIT_SUCCESS;
}
