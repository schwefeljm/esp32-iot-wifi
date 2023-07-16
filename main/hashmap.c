// https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/

#include "globals.h"
#include "log.h"
#include "hashmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// like constructor
void setNode(struct node_s* node, char* key, char* value)
{
	node->key = key;
	node->value = value;
	node->next = NULL;
	return;
};

// like constructor
void initializeHashMap(int count)
{
	postData->capacity = count;
	postData->numOfElements = 0;


	// array of size = 1
	postData->arr = (struct node_s**)malloc(sizeof(struct node_s*)
									* postData->capacity);
	
	insertHashEntry("TestKey", "ValueTest");

	return;
}

int hashFunction(char* key)
{
	int bucketIndex;
	int sum = 0, factor = 31;
	for (int i = 0; i < strlen(key); i++) {

		// sum = sum + (ascii value of
		// char * (primeNumber ^ x))...
		// where x = 1, 2, 3....n
		sum = ((sum % postData->capacity)
			+ (((int)key[i]) * factor) % postData->capacity)
			% postData->capacity;

		// factor = factor * prime
		// number....(prime
		// number) ^ x
		factor = ((factor % __INT16_MAX__)
				* (31 % __INT16_MAX__))
				% __INT16_MAX__;
	}

	bucketIndex = sum;
	return bucketIndex;
}

void insertHashEntry(char* key, char* value)
{

	// Getting bucket index for the given
	// key - value pair
	// printf("key: %s -- value %s\n", key, value);
	int bucketIndex = hashFunction(key);
	struct node_s* newNode = (struct node_s*)malloc(

		// Creating a new node
		sizeof(struct node_s));

	// Setting value of node
	setNode(newNode, key, value);

	// Bucket index is empty....no collision
	if (postData->arr[bucketIndex] == NULL) {
		postData->arr[bucketIndex] = newNode;
		
	}
	

	// Collision
	else {

		// Adding newNode at the head of
		// linked list which is present
		// at bucket index....insertion at
		// head in linked list
		newNode->next = postData->arr[bucketIndex];
		postData->arr[bucketIndex] = newNode;
	}
	return;
}

void delete (char* key)
{

	// Getting bucket index for the
	// given key
	int bucketIndex = hashFunction(key);

	struct node_s* prevNode = NULL;

	// Points to the head of
	// linked list present at
	// bucket index
	struct node_s* currNode = postData->arr[bucketIndex];

	while (currNode != NULL) {

		// Key is matched at delete this
		// node from linked list
		if (strcmp(key, currNode->key) == 0) {

			// Head node
			// deletion
			if (currNode == postData->arr[bucketIndex]) {
				postData->arr[bucketIndex] = currNode->next;
			}

			// Last node or middle node
			else {
				prevNode->next = currNode->next;
			}
			free(currNode);
			break;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}
	return;
}

char* searchHashEntry(char* key)
{

	// Getting the bucket index
	// for the given key
	int bucketIndex = hashFunction(key);

	// Head of the linked list
	// present at bucket index
	struct node_s* bucketHead = postData->arr[bucketIndex];
	//
	// Load Access Fault happens here when passing a non-existant 'key'
	// Fix later.
	//

	while (bucketHead != NULL) {

		// Key is found in the hashMap
		if (bucketHead->key == key) {
			return bucketHead->value;
		}
		bucketHead = bucketHead->next;
	}

	// If no key found in the hashMap
	// equal to the given key
	char* errorMssg = (char*)malloc(sizeof(char) * 25);
	errorMssg = "Oops! No data found.\n";
	return errorMssg;
}

int postDataToHashMap(char *string[])
{
	// Extract the first token
	char * token = strtok(*string, " ");
	// loop through the string to extract all other tokens
	while( token != NULL ) {
		token = strtok(NULL, " ");
    }
    return 0;


	return 0;
}
// This could be made better I think. But it works.
void stringSplitter(char *string, char *delimeter, char *tokenArray[])
{
    int tokenArrayPos = 0;
    char* token;

    char* delim = delimeter;
    char* str = string;

    while
            (
            (token = strtok_r(str, delim, &str))
            )
    {
        tokenArray[tokenArrayPos] = token;
        tokenArrayPos++;
    }


}

int tokenCount(char *string, char *delimeter)
{
	const char letter = delimeter[0];
	int count = 0;
	
    for(int i = 0; string[i]; i++)  
    {
    	if(string[i] == letter)
    	{
          count++;
        }
    }
	return count;
}


void createPostHashFromPostData(char *string, char *delimeter)
{
    int count = tokenCount(string, delimeter);
	char* tokenArray[count+1];
    
    stringSplitter(string, delimeter, tokenArray);



    int arrayElements = (sizeof(tokenArray) / sizeof(tokenArray[0]));
    for(int i=0; i <= arrayElements-1; i++)
    {

        char* paramArray[2]; // params are just key/value pairs. Always 2

		// not sure why, but this keeps past strings from padding new ones.
		char* dummy = "";
		//sprintf(dummy, "%s", paramArray[1]);
        int stringSize = strlen(tokenArray[i]);
        char string[stringSize];
        strncpy((char*)string, (char*)tokenArray[i], stringSize);
        char delimeter[] = "=";
        stringSplitter(string, delimeter, paramArray);
        printf("\n---------------------------\n%s:%s\n-------------------------\n", paramArray[0], paramArray[1]); 
		insertHashEntry(paramArray[0], paramArray[1]);
		
    }

    
}


/* 	Keep this around for looping.

	int loop;
	int arrayElements = (sizeof(tokenArray) / sizeof(tokenArray[0]));
	for(loop = 0; loop <= arrayElements-1; loop++)
    	 printf("%s ", tokenArray[loop]);
        
 */	
