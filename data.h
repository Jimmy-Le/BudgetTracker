#ifndef DATA_H

#define DATA_H

// Datastructure for an entry
typedef struct DataEntry{
    int entryID;
    char *date;
    char *entryType;
    char *entrySubType;
    char *entryDescription;
    double amount; 
} DataEntry;

// Datastructure for a doubly linked list which will hold all the entries
typedef struct Node {
    DataEntry dataItem;
    struct Node *next;
    struct Node *previous;
}Node;

Node* createNode(int id, char *date, char* entryType, char *entrySubType, char *entryDesc, double amount);
Node* getStart();
Node* getEnd();
int getListSize();
void push(Node *newEntry);
void printHeader();
void printNode(Node *newEntry, int mode);
void printData();
int getData(char *fileName);
void freeNode(Node *node);
void freeAllNodes();
char* convertBackToFile(Node *node);
int generateNewID();
int addToFile();
int updateFile();
#endif