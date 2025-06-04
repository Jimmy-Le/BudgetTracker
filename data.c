#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"



FILE *fptr;

// The character we look for when parsing
#define SEPARATOR "|" // use #Define

// These are the for storing the data from the files and later turned into a DataEntry struct
int tempID;
char* tempDate;
char* tempType;
char* tempSubType;
char* tempDesc;
double tempAmount;

// This counter is used to figure out what collumn we are at for parsing the file
int counter;         
int firstAdd = 0;                   

// Save the filename
char* financeFilename;

// These are the Headers for the doubly linked list
Node* start;
Node* end;
int elements = 0;

// This will be to generate a new bigger ID
int maxID = 0;

 
/// @brief This function will return the head sentinel
/// @return Header Node
Node* getStart(){
    return start;
}

/// @brief This function will return the Tail Sentinel
/// @return Tail Node
Node* getEnd(){
    return end;
}

/// @brief This function returns the amount of elements in the list
/// I don't think im using it, but im scared it wll break if i delete it
/// @return Integer size of linked list
int getListSize(){
    return elements;
}

/// @brief Creates the Head and Tail sentinels for a linked list
void createLinkedList(){

    start = (Node*) malloc(sizeof(Node));       // Header Sentinel
    end = (Node*) malloc(sizeof(Node));         // Tail Sentinel

    if(!start || !end){                         // Check for memory allocation errors
        exit(1);
    }
                                    
    start->next = end;                          // Set the next node for start to be end
    start->previous = NULL;

    end->previous = start;                      // Set the previous node for end to be start
    end->next = NULL;
}

/// @brief This function will create a DataEntry object with the information passed into it
/// @param id integer id
/// @param date char[] date
/// @param entryType char[] entry type
/// @param entrySubType char[] Category
/// @param entryDesc  char[] description
/// @param amount float amount
/// @return DataEntry struct
DataEntry createDataEntry(int id, char *date, char* entryType, char *entrySubType, char *entryDesc, double amount){

    // Store the inputs into a new DataEntry Struct
    DataEntry newEntry;
    newEntry.entryID = id;                              // ID
    newEntry.date = strdup(date);                       // Date
    newEntry.entryType = strdup(entryType);             // EntryType
    newEntry.entrySubType = strdup(entrySubType);       // Category
    newEntry.entryDescription = strdup(entryDesc);      // Description
    newEntry.amount = amount;                           // Amount

    return newEntry;
}


/// @brief This function will create a Node for linked list containing a new DataEntry object
/// @param id integer ID 
/// @param date char[] date
/// @param entryType char[] entry Type
/// @param entrySubType char[] Category
/// @param entryDesc char[] description
/// @param amount  float amount
/// @return 
Node* createNode(int id, char *date, char *entryType, char *entrySubType, char *entryDesc, double amount){
    // Allocate some memory for a new Node
    Node *newNode = (Node*) malloc(sizeof(Node));
    
    if(!newNode){               // Make sure that it allocate correctly
        exit(1);
    }

    // Populate the new node with the data from the input 
    newNode->dataItem = createDataEntry(id, date, entryType, entrySubType, entryDesc, amount);
    newNode->next = NULL;               // Initialize the next node to be null
    newNode->previous = NULL;           // initialize the previous node to be null

    return newNode;
}

/// @brief This function will insert a given Node at the end of the linked list
/// @param newEntry Node to be appended
void push(Node* newEntry){
    
    newEntry->previous = end->previous;             // Place the Node before the end header, before the new Node
    
    newEntry->next = end;                           // Place the end right after the new Node
    
    end->previous->next = newEntry;                 // Replace the old Node's Next to be the New Node
 
    end->previous = newEntry;                       // Replace the Node stored in the end header to be the new Node
    
    elements = elements + 1;                        // Increment that amount of elements in the list
}

/// @brief This function will print out the header for the display
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


/// @brief This function will print out all the fields in a Node, based on the mode
/// Mode 0: print all information in a single line
/// Mode 1: print each field on separate lines
/// @param newEntry Node to print
/// @param mode integer mode (0 or 1)
void printNode(Node* newEntry, int mode){

    // Print all information in 1 line
    if(mode == 0){
        printf("%-5d %-12s %-10s %-12s %-20s $%-10.2f \n", 
            newEntry->dataItem.entryID, 
            newEntry->dataItem.date,
            newEntry->dataItem.entryType,
            newEntry->dataItem.entrySubType,
            newEntry->dataItem.entryDescription,
            newEntry->dataItem.amount
        ); 
    // Print all fields separately
    } else if (mode == 1){
        printf("ID: %d \n", newEntry->dataItem.entryID);
        printf("Date: %s \n", newEntry->dataItem.date);
        printf("Type: %s \n", newEntry->dataItem.entryType);
        printf("Category: %s \n", newEntry->dataItem.entrySubType);
        printf("Description: %s \n", newEntry->dataItem.entryDescription);
        printf("Amount: $%.2f \n \n", newEntry->dataItem.amount);

    }
}


/// @brief This function will print out all of the Nodes in the list, excluding the sentinels
void printData(){
    Node *temp = start;

    printf("Finances Summary \n");
    printf("================== \n \n");
    printHeader();
    
    // Loop through all the nodes and print them if they aren't the sentinel
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


/// @brief This function will split a given string into smaller sections and create and append a new node with that information
/// @param fileLine char[] a line from given file
/// @return integer status code
int parseData(char *fileLine){
    counter = 0;
    char *res;

    // Read through each sections of the file line defined by the separator
    res = strtok(fileLine, SEPARATOR);
    while (res != NULL){

        // Based on the current section we are in, parse and assign to a temporary associated variable
        switch (counter)
        {
        case 0:                         // ID
            tempID = atoi(res);
            if (tempID > maxID){
                maxID = tempID;
            }
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
        res = strtok(NULL, SEPARATOR);
    }

    Node* tempNode = createNode(tempID, tempDate, tempType, tempSubType, tempDesc, tempAmount);         // create the node
    push(tempNode);                                                                                     // Push it into the list

    return 0;
}

/// @brief Initializes a list and takes in a file name and read through it line by line
/// @param fileName char[] filename
/// @return integer status
int getData(char * fileName){
    financeFilename = fileName;

    createLinkedList();                     // Initialize Linked List

    fptr = fopen(fileName, "r");            // Start Reading the file & making sure it exists
    if (!fptr){
        perror("Invalid File Name");
        exit(1);
    }
    char myString[200];

    while(fgets(myString, 100, fptr)){      // Parse each line of the file
        parseData(myString);    
    }
    
    fclose(fptr);
    return 0;
}


/// @brief This function free up dynamically allocated memory for all the char array in a DataEntry struct
/// @param data 
void freeData(DataEntry *data){
    if(data->date != NULL){                     // Free the date & make sure that it isn't already freed
        free(data->date);
    }
    
    if(data->entryType != NULL){                // Free the entry type & make sure that it isn't already freed
        free(data->entryType);
    }

    if(data->entrySubType != NULL){             // Free the subtype & make sure that it isn't already freed
        free(data->entrySubType);
    }

    if(data->entryDescription != NULL){         // Free the description & make sure that it isn't already freed
        free(data->entryDescription);
    }
}

/// @brief This function will free up allocated memory from a Node, including its data
/// @param node 
void freeNode(Node *node){
    
    if (node == NULL){                          // Make sure that the node isn't already freed
        return;
    }
    freeData(&node->dataItem);                  // Free the data inside the node

    free(node);                                 // Free the node itself
}

/// @brief This function frees all the nodes in the list
void freeAllNodes(){
    Node *current = getStart();
    Node *nextNode;

    while(current != NULL){                     // Make sure that the node isn't already freed
        nextNode = current->next;               // Save the next node to go to before freeing

        freeNode(current);                      // Free the current node
        current = nextNode;                     // go to next node
    }
}

/// @brief Converts a node back into a format that is suitable to the txt file
/// Make sure to free the results after using it
/// @param node Node to convert
/// @return char[] all the data formatted like the txt file
char* convertBackToFile(Node *node){

    
    int totalSize = sizeof(node->dataItem.entryID)      // Calculate the total size needed to create the result string
    + sizeof(node->dataItem.date) 
    + sizeof(node->dataItem.entryType) 
    + sizeof(node->dataItem.entrySubType)
    + sizeof(node->dataItem.entryDescription) 
    + sizeof(node->dataItem.amount) 
    + 8;                                                // 5 pipes, 2 for new line (in case of windows) and 1 end terminal character

    char *newLine = malloc(totalSize);                  

    sprintf(newLine, "%d|%s|%s|%s|%s|%0.2f",            // Format the data into the same format as the original file
        node->dataItem.entryID,
        node->dataItem.date,
        node->dataItem.entryType,
        node->dataItem.entrySubType,
        node->dataItem.entryDescription,
        node->dataItem.amount
    );
    return (newLine);
    
}

/// @brief Generates a new ID using the highest used ID + 1
/// @return integer New ID
int generateNewID(){
    maxID = maxID + 1;
    return maxID;
}


/// @brief This function should append an entry to the file
/// Unused for now due to possible bugs (adding extra new lines based on the previously saved file)
/// Currently using updateFile() instead
/// @return Integer status
int addToFile(){
    fptr = fopen(financeFilename, "a");
    if (!fptr){
        perror("Invalid File Name");
        return 1;
    }

    Node *temp = getEnd()->previous;

    char* newLine = convertBackToFile(temp);
    if(newLine){
        if(firstAdd == 0){
            fprintf(fptr, "\n%s\n", newLine);
            firstAdd = 1;
        } else {
            fprintf(fptr, "%s\n", newLine);
        }
        free(newLine);
        newLine = NULL;
    }
    fclose(fptr);
    return 0;
}


/// @brief Updates the file based on the given mode
/// Mode "a": add new entry to the list
/// Mode "w": update the entire file with new modified entry
/// @return integer status
int updateFile(){

    fptr = fopen(financeFilename, "w+");                        // prepare to write and override the file
    if (!fptr){
        perror("Invalid File Name");
        return 1;
    }

    Node *temp = getStart();
    while(temp){
        if (temp->next == NULL ||temp->previous == NULL){       // Making sure to skip printing the header nodes
        }else{
            char* newLine = convertBackToFile(temp);            // convert each node into text
            if(newLine){                                        
                if(firstAdd == 0){                              // This was used to handle append, attempting to handle \n being used multiple times in the file
                    firstAdd = 1;                               // It remains unused for now
                }
                fprintf(fptr, "%s\n", newLine);                 // write the text back into the file
                free(newLine);                                  // making sure to free the space from "convertBackToFile()"
                newLine = NULL;
            }
        }
        temp = temp->next;
    }    
    fclose(fptr);
    return 0;
}


