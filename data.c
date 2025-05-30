#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"



FILE *fptr;

// The character we look for when parsing
const char separator[2] = "|"; // use #Define

// These are the for storing the data from the files and later turned into a DataEntry struct
int tempID;
char* tempDate;
char* tempType;
char* tempSubType;
char* tempDesc;
double tempAmount;

// This counter is used to figure out what collumn we are at for parsing the file
int counter;                            

// Save the filename
char* financeFilename;

// These are the Headers for the doubly linked list
Node* start;
Node* end;


Node* getStart(){
    return start;
}

Node* getEnd(){
    return end;
}

// Create the head and tail of the Linked List
void createLinkedList(){

    start = (Node*) malloc(sizeof(Node)); 
    end = (Node*) malloc(sizeof(Node)); 

    // Check for memory allocation errors
    if(!start || !end){
        exit(1);
    }

    // Set the next node for start to be end
    start->next = end;
    start->previous = NULL;

    // Set the previous node for end to be start
    end->previous = start;
    end->next = NULL;
}

// This function will a DataEntry object with the information passed into it
DataEntry createDataEntry(int id, char *date, char* entryType, char *entrySubType, char *entryDesc, double amount){

    DataEntry newEntry;
    newEntry.entryID = id;
    newEntry.date = strdup(date);
    newEntry.entryType = strdup(entryType);
    newEntry.entrySubType = strdup(entrySubType);
    newEntry.entryDescription = strdup(entryDesc);
    newEntry.amount = amount;

    return newEntry;
}

// This function will create a Node for the linked list, containing a new DataEntry object
Node* createNode(int id, char *date, char *entryType, char *entrySubType, char *entryDesc, double amount){
    Node *newNode = (Node*) malloc(sizeof(Node));
    if(!newNode){
        exit(1);
    }

    newNode->dataItem = createDataEntry(id, date, entryType, entrySubType, entryDesc, amount);
    newNode->next = NULL;
    newNode->previous = NULL;

    return newNode;
}


// This function will insert a new Node before the end header
void push(Node* newEntry){

    // Place the Node before the end header, before the new Node
    newEntry->previous = end->previous;

    // Place the end right after the new Node
    newEntry->next = end;

    // Replace the old Node's Next to be the New Node
    end->previous->next = newEntry;

    // Replace the Node stored in the end header to be the new Node
    end->previous = newEntry;

}

void printHeader(){
    printf("%-5s %-12s %-10s %-12s %-20s %-10s \n", 
        "ID",
        "Date",
        "Type",
        "Category",
        "Description",
        "Amount"

    );
    printf("---------------------------------------------------------------------------\n");
}

// This function will print out all the fields in a Node
// There are modes to choose from
// 0: Print all in a row
// 1: Print in a line
void printNode(Node* newEntry, int mode){

    if(mode == 0){
        printf("%-5d %-12s %-10s %-12s %-20s $%-10.2f \n", 
            newEntry->dataItem.entryID, 
            newEntry->dataItem.date,
            newEntry->dataItem.entryType,
            newEntry->dataItem.entrySubType,
            newEntry->dataItem.entryDescription,
            newEntry->dataItem.amount
        ); 
    } else if (mode == 1){
        printf("ID: %d \n", newEntry->dataItem.entryID);
        printf("Date: %s \n", newEntry->dataItem.date);
        printf("Type: %s \n", newEntry->dataItem.entryType);
        printf("Category: %s \n", newEntry->dataItem.entrySubType);
        printf("Description: %s \n", newEntry->dataItem.entryDescription);
        printf("Amount: $%.2f \n \n", newEntry->dataItem.amount);

    }
    
    

}

// This function will print out all of the Nodes in the list
void printData(){
   Node *temp = start;

    printf("Finances Summary \n");
    printf("================== \n \n");
    printHeader();
    while(temp){
        // Making sure to skip printing the header nodes
        if (temp->next == NULL ||temp->previous == NULL){
        }else{
            printNode(temp, 0);
        }

        temp = temp->next;
    }
    printf("\n");
}



// This function will take a row in the data file and split each collumn into its own separate field, and add it to the linked list
int parseData(char *fileLine){
    counter = 0;
    char *res;

    res = strtok(fileLine, separator);
    while (res != NULL){

        switch (counter)
        {
        case 0:                         // ID
            tempID = atoi(res);
            break;
        case 1:                         // Date
            tempDate = res;
            break;
        case 2:                         // Type
            tempType = res;
            break;
        case 3:                         // Subtype
            tempSubType = res;
            break;
        case 4:                         // Description
            tempDesc = res;
            break;
        case 5:                         // Amount
            tempAmount = atof(res);
            break;
        default:                        // End of the line
            break;
        }

        counter = counter + 1;
        res = strtok(NULL, separator);
    }

    Node* tempNode = createNode(tempID, tempDate, tempType, tempSubType, tempDesc, tempAmount);
    push(tempNode);

    return 0;
}



// Takes in a file name and read through it line by line
int getData(char * fileName){
    financeFilename = fileName;

    createLinkedList();

    fptr = fopen(fileName, "r");
    if (!fptr){
        perror("Invalid File Name");
        exit(1);
    }
    char myString[200];

    while(fgets(myString, 100, fptr)){
        parseData(myString);
    }
    
    fclose(fptr);
    return 0;
}

// This function free up dynamically allocated memory for all the char array in a DataEntry struct
void freeData(DataEntry *data){
    free(data->date);
    free(data->entryType);
    free(data->entrySubType);
    free(data->entryDescription);
}


// This function will free up allocated memory from a Node, including its data
void freeNode(Node *node){
    // Make sure that the node isn't already freed
    if (!node){
        return;
    }
    freeData(&node->dataItem);

    free(node);

}

char* convertBackToFile(Node *node){
    int totalSize = sizeof(node->dataItem.entryID) 
    + sizeof(node->dataItem.date) 
    + sizeof(node->dataItem.entryType) 
    + sizeof(node->dataItem.entrySubType)
    + sizeof(node->dataItem.entryDescription) 
    + sizeof(node->dataItem.amount) 
    + 8; // 5 pipes, 2 for new line (in case of windows) and 1 end terminal character

    char *newLine = malloc(totalSize);

    sprintf(newLine, "%d|%s|%s|%s|%s|%0.2f\n",
        node->dataItem.entryID,
        node->dataItem.date,
        node->dataItem.entryType,
        node->dataItem.entrySubType,
        node->dataItem.entryDescription,
        node->dataItem.amount
    );
    return (newLine);
    
}


// Updates the file based on the given mode
// Mode "a": add new entry to the list
// Mode "w": update the entire file with new modified entry
int updateFile(char *mode){

    fptr = fopen(financeFilename, mode);
    if (!fptr){
        perror("Invalid File Name");
        exit(1);
    }
    
    Node *temp = getStart();
    while(temp){
        // Making sure to skip printing the header nodes
        if (temp->next == NULL ||temp->previous == NULL){
        }else{
            char* newLine = convertBackToFile(temp);
            if(newLine){
                fprintf(fptr, "%s", newLine);
                free(newLine);
                newLine = NULL;
            }
        }
        temp = temp->next;
    }
    
    fclose(fptr);
    return 0;
}


