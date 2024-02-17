#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	int length = 0;
	struct node* current_node = head;
	while (current_node != NULL) {
		if (current_node->letter != NULL) {
			length++;
			current_node = current_node->next;
		}
	}
	return length;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	struct node* current_node = head;
	int string_length = length(head);
	char* str = (char*) malloc(sizeof(char*) * string_length);

	for(int i = 0; i < string_length; i++) {
		str[i] = current_node->letter;
		current_node = current_node->next;
	}
	return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node*));
	new_node->letter = c;
	new_node->next = NULL;
	struct node* current_node = *pHead;
	int strlen = length(*pHead);
	for (int i = 0; i < strlen - 1; i++) {
		current_node = current_node->next;
	}
	if (*pHead == NULL) {
		*pHead = new_node;
	}
	else {
		current_node->next = new_node;
	}

}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	*pHead = NULL;
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}