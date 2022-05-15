#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define indexForDeserialization 3 //* just change it from 0 to 3
struct Company {
  char name[20];
  int foundationYear;
  char tax[20];
  char legalAddress[20];
  char actualAddress[20];
};
const char COMPANY_FORMAT_OUT[] =
    "{name:%s, foundationYear:%d, tax:%s, legalAddress:%s, "
    "actualAddress:%s}\n";
const char COMPANY_FORMAT_IN[] =
    "{name:%[0-9a-zA-Z ], foundationYear:%d, "
    "tax:%[0-9a-zA-Z ], legalAddress:%[0-9a-zA-Z ], "
    "actualAddress:%[0-9a-zA-Z ]}";

void printCompany(struct Company *pCom);
void movePointerToSpecificLine(FILE *file, int lineNumber);

int main(int argc, char const *argv[]) {
  struct Company companies[4] = {
      {"x0", 0, "2343242", "leg 0 street", "act 0 street"},
      {"x1", 1022, "4234234", "lega 1 street", "actua 1 street"},
      {"x2", 2022, "465468", "legal 2 street", "actual 2 street"},
      {"x3", 3022, "5467578", "legal 3 street", "actual 3 street"},
  };

  FILE *file = fopen("./companies.txt", "w+");
  if (file == NULL) {
    printf("File is not opened.");
    return 1;
  }

  printf("\nArray of structures\n");
  for (int i = 0; i < 4; i++) {
    fprintf(file, COMPANY_FORMAT_OUT, companies[i].name,
            companies[i].foundationYear, companies[i].tax,
            companies[i].legalAddress, companies[i].actualAddress);
    printCompany(&companies[i]);
  }

  struct Company deserialized;
  movePointerToSpecificLine(file, indexForDeserialization + 1);
  fscanf(file, COMPANY_FORMAT_IN, deserialized.name,
         &deserialized.foundationYear, deserialized.tax,
         deserialized.legalAddress, deserialized.actualAddress);
  printf("\nDeserialized structure\n");
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
  if (1 == lineNumber) {
    return;
  }
  int bytesCounter = 0;
  int linesCounter = 1;
  do {
    bytesCounter++;
    char c = fgetc(file);
    if (feof(file)) {
      return;
    }
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
