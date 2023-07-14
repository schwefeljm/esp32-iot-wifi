#ifndef hashmap
    #define hashmap

    void initializeHashMap();
    void insert(char* key, char* value);
    void delete (char* key);
    char* postSearch(char* key);
    int postDataToHashMap(char *string[]);
    void stringSplitter(char *string, char *delimeter, char *tokenArrayeter[]);
    int tokenCount(char *string, char *delim );
#endif