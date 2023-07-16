#ifndef hashmap
    #define hashmap

    void initializeHashMap(int count);
    void insertHashEntry(char* key, char* value);
    void delete (char* key);
    char* searchHashEntry(char* key);
    int postDataToHashMap(char *string[]);
    void stringSplitter(char *string, char *delimeter, char *tokenArrayeter[]);
    int tokenCount(char *string, char *delim );
    void createPostHashFromPostData(char *string, char *delimeter);
#endif