#ifndef utils
    #define utils

    void setNode(struct node *node, char *key, char *value);

    void initializeHashMap(struct hashMap *mp);

    int hashFunction(struct hashMap *mp, char *key);

    void insert(struct hashMap *mp, char *key, char *value);

    void delete(struct hashMap *mp, char *key);

    char *search(struct hashMap *mp, char *key);

    int hashmain(void);


#endif