#include <stdbool.h>
#include <stdio.h>
#include <string.h>
struct Company {
  char name[20];
  int foundationYear;
  char tax[20];
  char legalAddress[20];
  char actualAddress[20];
};
const char COMPANY_FORMAT_OUT[] =
    "{name:%s foundationYear:%d tax:%s legalAddress:%s, "
    "actualAddress:%s}\n";
const char COMPANY_FORMAT_IN[] =
    "{name:%s foundationYear:%d tax:%s legalAddress:%[0-9a-zA-Z ], "
    "actualAddress:%[0-9a-zA-Z ]}";
void printCompany(struct Company *pCom);
void movePointerToSpecificLine(FILE *file, int lineNumber);

int main(int argc, char const *argv[]) {
  struct Company companies[3] = {
      {"x1", 100, "1", "leg1 street", "act1 street"},
      {"x2", 2000, "2", "lega2 street", "actua2 street"},
      {"x3", 30000, "3", "legal3 street", "actual3 street"}};

  printf("\nInitial structure\n");
  //   printCompany(&initial);

  FILE *file = fopen("./companies.txt", "w+");
  if (file == NULL) {
    printf("File is not opened.");
    return 1;
  }

  for (int i = 0; i < 3; i++) {
    fprintf(file, COMPANY_FORMAT_OUT, companies[i].name,
            companies[i].foundationYear, companies[i].tax,
            companies[i].legalAddress, companies[i].actualAddress);
  }

  struct Company deserialized;
  int index = 2;
  movePointerToSpecificLine(file, 2);
  fscanf(file, COMPANY_FORMAT_IN, deserialized.name,
         &deserialized.foundationYear, deserialized.tax,
         deserialized.legalAddress, deserialized.actualAddress);
  printf("\nSerialized structure\n");
  printCompany(&deserialized);
  return 0;
}

void printCompany(struct Company *pCom) {
  printf("Name: %s\nYear of fundation: %d\nTax number: %s\nLegal address: "
         "%s\nActual"
         "address: %s\n\n",
         pCom->name, pCom->foundationYear, pCom->tax, pCom->legalAddress,
         pCom->actualAddress);
}

void movePointerToSpecificLine(FILE *file, int lineNumber) {
  fseek(file, 0, SEEK_SET);
  int bytesCounter = 0;
  int linesCounter = 1;
  do {
    bytesCounter++;
    char c = fgetc(file);
    if (feof(file)) {
      break;
    }
    printf("%c", c);
    if ('}' == c) {
      linesCounter++;
    }
    if (linesCounter == lineNumber) {
      fseek(file, bytesCounter + 1, SEEK_SET);
      return;
    }
  } while (1);
  return;
}
