#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ANSI_RESET = "\033[0m";
char *ANSI_CYAN = "\033[36;1m";

char *BACK_UP_FILE_PATH = "./backup.txt";

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
    "actualAddress:%[0-9a-zA-Z ]}\n";

struct Node {
  struct Company *value;
  struct Node *next;
};

struct Node *head = NULL;
struct Node *tail = NULL;

struct Node *allocateNode() {
  return (struct Node *)malloc(sizeof(struct Node));
}

struct Company *allocateCompany() {
  return (struct Company *)malloc(sizeof(struct Company));
}

void printCompany(struct Company *pCom) {
  printf("Name: %s\nYear of foundation: %d\nTax number: %s\nLegal address: "
         "%s\nActual"
         "address: %s\n\n",
         pCom->name, pCom->foundationYear, pCom->tax, pCom->legalAddress,
         pCom->actualAddress);
}

void add(struct Company *value) {
  struct Node *n = allocateNode();
  n->value = value;
  n->next = NULL;

  if (NULL == head) {
    head = n;
    tail = n;
  } else {
    tail->next = n;
    tail = n;
  }
}

struct Node *searchByName(char *name) {
  int index = 0;
  struct Node *n = head;
  while (NULL != n) {
    if (strcmp(name, n->value->name) == 0) {
      printf("%sSearched by name. Element with name %s has index %d %s\n",
             ANSI_CYAN, name, index, ANSI_RESET);
      printCompany(n->value);
      return n;
    }
    n = n->next;
    index++;
  }
  return NULL;
}

struct Node *searchByFoundationYear(int year) {
  int index = 0;
  struct Node *n = head;
  while (NULL != n) {
    if (year == n->value->foundationYear) {
      printf("%sSearched by year of foundation. Element with year %d has index "
             "%d %s \n ",
             ANSI_CYAN, year, index, ANSI_RESET);
      printCompany(n->value);
      return n;
    }
    n = n->next;
    index++;
  }
  return NULL;
}

struct Node *deleteTail() {
  struct Node *deletedTail = tail;

  if (head == tail) {
    head = NULL;
    tail = NULL;
    return deletedTail;
  }
  struct Node *currentNode = head;
  while (currentNode->next) {
    if (!currentNode->next->next) {
      free(currentNode->next);
      currentNode->next = NULL;
    } else {
      currentNode = currentNode->next;
    }
  }
  tail = currentNode;
  return deletedTail;
}

void printList() {
  struct Node *n = head;
  while (n != NULL) {
    printCompany(n->value);
    n = n->next;
  }
}

void serializeList() {
  FILE *pFile = fopen(BACK_UP_FILE_PATH, "w");
  if (pFile == NULL) {
    printf("Cannot open file %s", BACK_UP_FILE_PATH);
    exit(1);
  }
  struct Node *n = head;
  while (n != NULL) {
    fprintf(pFile, COMPANY_FORMAT_OUT, n->value->name, n->value->foundationYear,
            n->value->tax, n->value->legalAddress, n->value->actualAddress);
    n = n->next;
  }
  fclose(pFile);
}

void freeList() {
  struct Node *n = head;
  struct Node *temp = NULL;

  while (n != NULL) {
    temp = n;
    n = n->next;
    free(temp);
  }
  head = NULL;
  tail = NULL;
}

void deSerializeList() {
  FILE *pFile = fopen(BACK_UP_FILE_PATH, "r");
  if (pFile == NULL) {
    printf("Cannot open file %s", BACK_UP_FILE_PATH);
    exit(1);
  }
  while (1) {
    struct Company *deserialized = allocateCompany();
    if (fscanf(pFile, COMPANY_FORMAT_IN, deserialized->name,
               &(deserialized->foundationYear), deserialized->tax,
               deserialized->legalAddress,
               deserialized->actualAddress) == EOF) {
      free(deserialized);
      break;
    }
    add(deserialized);
  }
  fclose(pFile);
}

int main() {
  //* just make array because it is too long for manual input
  // all operations are implemented with linked list.
  struct Company companies[] = {
      {"x0", 0, "2343242", "leg 0 street", "act 0 street"},
      {"x1", 1022, "4234234", "lega 1 street", "actua 1 street"},
      {"x2", 2022, "465468", "legal 2 street", "actual 2 street"},
      {"x3", 3022, "5467578", "legal 3 street", "actual 3 street"},
  };
  size_t length = sizeof companies / sizeof companies[0];
  for (int i = 0; i < length; i++) {
    add(&companies[i]);
  }

  printf("%sInitialList: %s\n", ANSI_CYAN, ANSI_RESET);
  printList();
  searchByName("x0");
  struct Node *foundNode = searchByFoundationYear(3022);
  foundNode->value->foundationYear = 1111;
  printf("%sChange foundation year in found node: %s\n", ANSI_CYAN, ANSI_RESET);
  printCompany(foundNode->value);
  printf("%sLet`s delete tail\nList after deletion. This list will be "
         "serialized.%s\n",
         ANSI_CYAN, ANSI_RESET);
  deleteTail();
  printList();

  serializeList();
  freeList();
  printf("%sList after serialization/deserialization.%s\n", ANSI_CYAN,
         ANSI_RESET);
  deSerializeList();
  printList();

  return 0;
}