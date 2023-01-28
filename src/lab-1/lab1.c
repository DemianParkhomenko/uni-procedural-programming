#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define sizeOfCLIArray 7 // a predefined size for this exercise by the teacher 
#define pathToTxtFile "./lab1.txt"
#define pathToBakFile "./lab1.bak"

bool fprintfCLIArray(int argc, char* argv[], int size, FILE* destination);
void doBackup(FILE* fromFile, FILE* toFile);

int main(int argc, char* argv[]) {
  FILE* initial, * backup;

  initial = fopen(pathToTxtFile, "a");
  bool isSuccessful = fprintfCLIArray(argc, argv, sizeOfCLIArray, initial);
  if (!isSuccessful) {
    return 1;
  }
  fclose(initial);

  initial = fopen(pathToTxtFile, "r");
  backup = fopen(pathToBakFile, "w");
  doBackup(initial, backup);
  fclose(initial);
  fclose(backup);
}

bool fprintfCLIArray(int argc, char* argv[], int size, FILE* toFile) {
  if (argc - 1 != size * size) {
    printf("Wrong CLI agruments\n");
    return false;
  }
  fprintf(toFile, "\nArray:\n");
  for (int i = 0, argsCounter = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      fprintf(toFile, "%.2f ", atof(argv[1 + argsCounter]));
      argsCounter++;
    }
    fprintf(toFile, "\n");
  }
  return true;
}

void doBackup(FILE* fromFile, FILE* toFile) {
  const char RED[] = "\033[0;31m", GREEN[] = "\033[0;32m", RESET[] = "\033[0m";
  if (fromFile == NULL || toFile == NULL) {
    printf("%sError: A wrong directory of the file. Backup is failed.\n%s", RED,
      RESET);
    return;
  }
  char ch;
  while ((ch = fgetc(fromFile)) != EOF) {
    fputc(ch, toFile);
  }
  printf("%sFile successfully backuped\n%s", GREEN, RESET);
}
