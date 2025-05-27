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

void createLinkedList();
DataEntry createDataEntry(int id, char *date, char* entryType, char *entrySubType, char *entryDesc, double amount);
Node* createNode(int id, char *date, char* entryType, char *entrySubType, char *entryDesc, double amount);
void push(Node *newEntry);
void printNode(Node *newEntry);
void printData();
int parseData(char *fileName);
int getData(char *fileName);
void freeData(DataEntry *data);
void freeNode(Node *node);
#endif