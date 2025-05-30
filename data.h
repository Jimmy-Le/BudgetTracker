#ifndef DATA_H

#define DATA_H


typedef struct DataEntry{
    int entryID;
    char *date;
    char *entryType;
    char *entrySubType;
    char *entryDescription;
    double amount; // Reformat the print
} DataEntry;


typedef struct Node {
    DataEntry dataItem;
    struct Node *next;
    struct Node *previous;
}Node;

// Get rid of unused
Node* createNode(int id, char *date, char* entryType, char *entrySubType, char *entryDesc, double amount);
Node* getStart();
Node* getEnd();
void push(Node *newEntry);
void printHeader();
void printNode(Node *newEntry, int mode);
void printData();
int parseData(char *fileName);
int getData(char *fileName);
void freeData(DataEntry *data);
void freeNode(Node *node);
char* convertBackToFile(Node *node);
int updateFile(char *mode);
#endif