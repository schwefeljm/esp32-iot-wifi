#include "utils.h"
#include <string.h>

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
