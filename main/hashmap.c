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
void initializeHashMap()
{
	ESP_LOGI(TAG, "4 %i", (int) &postData);
	ESP_LOGI(TAG, "5 %i", (int) &postData);
	postData->capacity = 100;
	postData->numOfElements = 0;


	// array of size = 1
	postData->arr = (struct node_s**)malloc(sizeof(struct node_s*)
									* postData->capacity);
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

void insert(char* key, char* value)
{

	// Getting bucket index for the given
	// key - value pair
	int bucketIndex = hashFunction(key);
	struct node_s* newNode = (struct node_s*)malloc(

		// Creating a new node
		sizeof(struct node_s));

	// Setting value of node
	setNode(newNode, key, value);

	// Bucket index is empty....no collision
	if (postData->arr[bucketIndex] == NULL) {
		postData->arr[bucketIndex] = newNode;
		ESP_LOGI(TAG, "8 %i", (int) &postData);
	}
	

	// Collision
	else {

		// Adding newNode at the head of
		// linked list which is present
		// at bucket index....insertion at
		// head in linked list
		newNode->next = postData->arr[bucketIndex];
		postData->arr[bucketIndex] = newNode;
		ESP_LOGI(TAG, "8.1 %i", (int) &postData);
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

char* postSearch(char* key)
{

	// Getting the bucket index
	// for the given key
	int bucketIndex = hashFunction(key);

	// Head of the linked list
	// present at bucket index
	ESP_LOGI(TAG, "9 %i", (int) &postData);
	struct node_s* bucketHead = postData->arr[bucketIndex];
	ESP_LOGI(TAG, "10 %i", (int) &postData);
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
//	char string[50] = "Hello! We are learning about strtok";
	// Extract the first token
	char * token = strtok(*string, " ");
	// loop through the string to extract all other tokens
	while( token != NULL ) {
		printf( " %s\n", token ); //printing each token
		token = strtok(NULL, " ");
    }
    return 0;
	//ESP_LOGI(TAG, "String: %s, Delimeter: %s", &string, &delimiter);	

	return 0;
}
// This could be made better I think. But it works.
void stringSplitter(char *string, char *delimeter, char *tokenArray[])
{
    int count = tokenCount(string, delimeter);

    //tokenArray[count + 1];

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

    //return tokenArray;
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

/* 	Keep this around for looping.

	int loop;
	int arrayElements = (sizeof(tokenArray) / sizeof(tokenArray[0]));
	for(loop = 0; loop <= arrayElements-1; loop++)
    	 printf("%s ", tokenArray[loop]);
        
 */	
