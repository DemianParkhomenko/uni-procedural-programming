#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

struct Company {
  char name[20];
  int foundationYear;
  char tax[20];
  char legalAddress[20];
  char actualAddress[20];
};
const char *COMPANY_FORMAT_OUT =
    "name:%s foundationYear:%d tax:%s legalAddress:%s, actualAddress:%s";
const char *COMPANY_FORMAT_IN =
    "name:%s foundationYear:%d tax:%s legalAddress:%[0-9a-zA-Z ], "
    "actualAddress:%[0-9a-zA-Z ]";
void printCompany(struct Company *pCom);

int main(int argc, char const *argv[]) {
  struct Company initial = {"x", 2200, "21321332", "y avenue", "z avenue"};

  printf("\nInitial structure\n");
  printCompany(&initial);

  FILE *file = fopen("./initial-company", "w+");
  if (file == NULL) {
    printf("File is not opened.");
    return 1;
  }

  struct Company serialized;
  fprintf(file, COMPANY_FORMAT_OUT, initial.name, initial.foundationYear,
          initial.tax, initial.legalAddress, initial.actualAddress);
  fseek(file, 0, SEEK_SET);
  fscanf(file, COMPANY_FORMAT_IN, serialized.name, &serialized.foundationYear,
         serialized.tax, serialized.legalAddress, serialized.actualAddress);

  printf("\nSerialized structure\n");
  printCompany(&serialized);

  return 0;
}

void printCompany(struct Company *pCom) {
  printf("Name: %s\nYear of fundation: %d\nTax number: %s\nLegal address: "
         "%s\nActual"
         "address: %s\n\n",
         pCom->name, pCom->foundationYear, pCom->tax, pCom->legalAddress,
         pCom->actualAddress);
}