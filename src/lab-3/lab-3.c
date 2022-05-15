#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct Company {
  char name[20];
  int fundationYear;
  char *tax;
  char *legalAddress;
  char *actualAddress;
};
const char *COMPANY_FORMAT_OUT = "(%s,%d,%s,%s,%s)";
const char *COMPANY_FORMAT_IN = "(%[^,],%d,%[^,],%[^,],%[^,])";

int main(int argc, char const *argv[]) {
  struct Company initial = {
      .name = "x", .fundationYear = 2022
      /*   .tax = "8023234238",
        .legalAddress = "y avenue",
        .actualAddress = "z avenue", */
  };
  FILE *file = fopen("./initial-company", "w+");
  if (file == NULL) {
    printf("File is not opened.");
    return 1;
  }
  fprintf(file, COMPANY_FORMAT_OUT, initial.name, initial.fundationYear,
          initial.tax, initial.legalAddress, initial.actualAddress);
  fseek(file, 0, SEEK_SET);

  struct Company serialized;
  fscanf(file, COMPANY_FORMAT_IN , serialized.name /* 20,
         &serialized.fundationYear/* , &serialized.tax, 30,
         &serialized.legalAddress, 30, &serialized.actualAddress, 3 0*/);
  printf("initial: %s", initial.name);

  printf("year: %s", serialized.name);

  return 0;
}
