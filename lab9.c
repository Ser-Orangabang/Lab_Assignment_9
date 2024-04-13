#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 23

// RecordType
struct RecordType
{
  int		id;
  char	name;
  int		order; 
};

struct Node
{
struct RecordType* record;
struct Node* next;
};

// Fill out this structure
struct HashType
{
    struct Node* heads[TABLE_SIZE];
};
// Compute the hash function
int hash(int x)
{
  unsigned int hash_value = x % TABLE_SIZE;
  return hash_value;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData, struct HashType** ppHashTable)
{
  FILE* inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n;
  char c;
  struct RecordType *pRecord;
  *ppData = NULL;

  if (inFile)
  {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    // Implement parse data block
    if (*ppData == NULL)
    {
      printf("Cannot allocate memory\n");
      exit(-1);
    }
    
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        (*ppHashTable)->heads[i] = NULL;
    }
    
    for (i = 0; i < dataSz; ++i)
    {
      pRecord = *ppData + i;
      fscanf(inFile, "%d ", &n);
      pRecord->id = n;
      fscanf(inFile, "%c ", &c);
      pRecord->name = c;
      fscanf(inFile, "%d ", &n);
      pRecord->order = n;

      int index = hash(pRecord->id);
      struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
      newNode->record = pRecord;
      newNode->next = (*ppHashTable)->heads[index];
      (*ppHashTable)->heads[index] = newNode;
    }

    fclose(inFile);
  }

  return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
  int i;
  printf("\nRecords:\n");
  for (i = 0; i < dataSz; ++i)
  {
    printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
  }
  printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
  int i;
  struct Node *currentNode;

  for (i = 0; i < hashSz; ++i)
  {
    printf("index %d", i);

    currentNode = pHashArray->heads[i];
    
    
    while (currentNode != NULL)
    {
      printf(" -> ");
      printf("%d %c %d", currentNode->record->id, currentNode->record->name, currentNode->record->order);
      currentNode = currentNode->next;
    }

    printf("\n");
  }
}

int main(void)
{
  struct RecordType *pRecords;
  int recordSz = 0;

  struct HashType* pHashInstance = malloc(sizeof(struct HashType));

  recordSz = parseData("input.txt", &pRecords, &pHashInstance);
  printRecords(pRecords, recordSz);
  // Your hash implementation

  displayRecordsInHash(pHashInstance, TABLE_SIZE);
}