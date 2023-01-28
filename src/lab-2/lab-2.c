#include <stdio.h>
#include <stdlib.h>

void checkAllocation();

void task1();
void removeElements(int* array, int startsFrom, int howMuchDelete);
void printArray1D(int* array, int length, char* message);

void task2();
void printArray2D(int** array, int rows, int columns, char* message);
void markArrayPointers(int** array, int rows, int columns);

int main(int argc, char* argv[]) {
  task1();
  task2();
}

void task1() {
  int length;
  printf("Task 1. Enter length of the array:");
  scanf("%i", &length);
  int* array = (int*)malloc(sizeof(int) * length * 1.2);
  checkAllocation(array, "Task 1. Array is not allocated.\n");

  for (int i = 0; i < length; ++i) {
    array[i] = i;
  }
  printArray1D(array, length, "Initial array --> ");

  int howMuchDelete;
  int startsFrom;
  printf("From which index elements must be deleted?\n");
  scanf("%i", &startsFrom);
  printf("How much elements do you want to delete?\n");
  scanf("%i", &howMuchDelete);

  if (howMuchDelete + startsFrom > length) {
    printf("The wrong input. Seems you want to delete too much elements.\n");
    exit(1);
  }

  for (int counter = 0; counter < howMuchDelete; counter++) {
    for (int i = startsFrom; i < length - 1; i++) {
      array[i] = array[i + 1];
    }
    length -= 1;
  }
  printArray1D(array, length, "Result array --> ");
  free(array);
}

void task2() {
  printf("Task 2\n");
  int rows = 3, columns = 4;
  int** array;

  int memory = sizeof(int*) * rows + sizeof(int) * columns * rows;
  array = (int**)malloc(memory);
  checkAllocation(array, "Task 2. Array is not allocated.\n");
  markArrayPointers(array, rows, columns);

  int count = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      array[i][j] = ++count; //. *(*(array+i)+j) = ++count
    }
  }
  printArray2D(array, rows, columns, "initial:\n");

  columns += 1;
  memory += sizeof(int) * rows;
  array = (int**)realloc(array, memory);
  checkAllocation(array, "Task 2. Array is not allocated.\n");
  markArrayPointers(array, rows, columns);
  printArray2D(array, rows, columns, "realloc:\n");

  int addedElement = 0;
  while (addedElement < rows) {
    for (int i = rows - 1; i >= 0 + addedElement; i--) {
      for (int j = columns - 1; j >= 0; j--) {
        array[i][j + 1] = array[i][j];
      }
    }
    addedElement++;
  }
  array[0][0] = 24;
  array[1][0] = 8;
  array[2][0] = 1991;
  printArray2D(array, rows, columns, "result:\n");
  free(array);
}

//*   for loop to point rows pointer to appropriate location in 2D array
void markArrayPointers(int** array, int rows, int columns) {
  int* ptrFirstElement = (int*)(array + rows);
  for (int i = 0; i < rows; i++) {
    array[i] = (ptrFirstElement + columns * i);
  }
}

void checkAllocation(int* pointer, char* errorMessage) {
  if (NULL == pointer) {
    printf("Allocation failed.\n %s", errorMessage);
    exit(1);
  }
}

void printArray1D(int* array, int length, char* message) {
  printf("%s", message);
  for (int i = 0; i < length; i++) {
    printf("%i ", array[i]);
  }
  printf("\n");
}

void printArray2D(int** array, int rows, int columns, char* message) {
  printf("%s", message);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      printf("%4i ", array[i][j]);
    }
    printf("\n");
  }
}
