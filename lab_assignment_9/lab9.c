#include <stdio.h>
#include <stdlib.h>
// RecordType
#define SIZE 300
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

struct node {
	struct RecordType* records;
	struct node* next;
};

// Fill out this structure
struct HashType
{
	struct node** lists[SIZE];
};

// Compute the hash function
int hash(int x)
{
	return x%SIZE;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
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
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
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

	for (i=0;i<hashSz;++i)
	{
		int indexOccupied = 0;
        struct node* currentNode = pHashArray->lists[i];
		if(currentNode != NULL) {
			printf("Index %d -> ", i);
			indexOccupied = 1;
		}
        while (currentNode != NULL)
        {
            printf("%d %c %d -> ", currentNode->records->id, currentNode->records->name, currentNode->records->order);
            currentNode = currentNode->next;
        }
		if (indexOccupied == 1) {
			printf("NULL \n");
		}
		// if index is occupied with any records, print all
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input_lab_9.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation

	struct HashType* table = (struct HashType*)malloc(sizeof(struct HashType));	
	for(int i = 0; i < SIZE; i++) {
		table->lists[i] = NULL;
	}

	for (int i = 0; i < recordSz; i++) {
		int hashValue = hash(pRecords[i].id);
		struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->records = &pRecords[i];
        newNode->next = table->lists[hashValue];
        table->lists[hashValue] = newNode;
	}

	displayRecordsInHash(table, SIZE);
}