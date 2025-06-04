#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Split the doubly linked list in half
Node *split(Node *head) {
    Node *fast = head;
    Node *slow = head;

    // Move fast pointer two steps and slow pointer
    // one step until fast reaches the end
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL){
            slow = slow->next;
        }    
    }

    // Split the list into two halves
    Node *temp = slow->next;
    slow->next = NULL;
    if (temp != NULL) {
        temp->previous = NULL;
    }
    return temp;
}

/// @brief This function will extract and convert the dates of two entry and compare the year, month and day of both entries
/// @param first 
/// @param second 
/// @return returns 0 if the first one is smaller, 1 if the second one is smaller
int compareDates(Node *first, Node *second){
    int firstYear;
    int firstMonth;
    int firstDay;

    int secondYear;
    int secondMonth;
    int secondDay;

    char *firstDate;
    char *secondDate;


    // Converting the string date of the first node into separate integer year, month and day 
    char firstData[20];
    strncpy(firstData, first->dataItem.date, sizeof(firstData));

    firstDate = strtok(firstData, "-");
    firstYear = atoi(firstDate);       

    firstDate = strtok(NULL, "-");
    firstMonth = atoi(firstDate);

    firstDate = strtok(NULL, "-");
    firstDay = atoi(firstDate);


    // Converting the string date of the second node into separate integer year, month and day 
    char secondData[20];
    strncpy(secondData, second->dataItem.date, sizeof(secondData));

    secondDate = strtok(secondData, "-");
    secondYear = atoi(secondDate);           

    secondDate = strtok(NULL, "-");
    secondMonth = atoi(secondDate);
    
    secondDate = strtok(NULL, "-");
    secondDay = atoi(secondDate);


    // If the first year is bigger than the second year, the second date is smaller, return 0 (the second date)
    if(firstYear > secondYear){
        return 0;

    // If the  first year is smaller than the second year, the first date is smaller, return 1 (the first date)
    } else if(firstYear < secondYear) {
        return 1;
    }
    
    // If the first month is bigger than the second month, the second date is smaller, return 0 (the second date)
    if (firstMonth > secondMonth){
        return 0;

    // If the  first month is smaller than the second month, the first date is smaller, return 1 (the first date)
    } else if (firstMonth < secondMonth) {
        return 1;
    }

    // If the  first day is bigger than the second year, the second date is smaller, return 0 (the second date)
    if(firstDay > secondDay){
        return 0;
    } 

    // Otherwise, the first date is smaller or equal, return 1 (the first date)
    return 1;
}

/// @brief Function to merge two sorted doubly linked lists
/// @param first First Node to compare
/// @param second  Second Node to compare
/// @param mode integer the chosen method to sort
/// @return Node that is smaller based on the sorting condition
Node *merge( Node *first, Node *second, int mode) {
  
    // If either list is empty, return the other list
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    int sortCondition;
    switch (mode){  // Set up the conditions to sort to
    case 1:     // Sort by ID
        sortCondition = first->dataItem.entryID < second->dataItem.entryID;
        break;
    case 2:     // Sort by Date
        sortCondition = compareDates(first, second);
        break;
    case 3:     // Sort by Amount
        sortCondition = first->dataItem.amount < second->dataItem.amount;
        break;
    case 4:     // Sort by Description
        sortCondition = strcasecmp(first->dataItem.entryDescription, second->dataItem.entryDescription) < 0;
        break;
    default:    // Other wrong inputs
        break;
    }

   // second nodes
    if (sortCondition) {
        first->next = merge(first->next, second, mode);         // Recursively merge the rest of the lists
        if (first->next != NULL) {
            first->next->previous = first;                      // link the result to the current node
        }

        first->previous = NULL;
        return first;
    }
    else {
        second->next = merge(first, second->next, mode);        // Recursively merge the rest of the lists and
        if (second->next != NULL) {
            second->next->previous = second;                    // link the result to the current node
        }
        second->previous = NULL;
        return second;
    }
}

/// @brief Function to perform merge sort on a doubly linked list
/// @param head Node that is immediately after the start sentinel
/// @param mode integer choice that the user wants to sort to
/// @return Node the new Head node
Node *iDSort(Node *head, int mode) {
  
    if (head == NULL || head->next == NULL) {               // If the list is empty or has only one node, it's already sorted
        return head;
    }
    
    Node *second = split(head);                             // Split the list into two

    head = iDSort(head, mode);                              // Recursively sort each half
    second = iDSort(second, mode);

    return merge(head, second, mode);                       // Merge the two sorted halves
}

/// @brief Function gets called when the user decides to sort
/// @param sortChoice integer sorting mode
void sortByChoice(int sortChoice){
    
    Node *temp = getStart()->next;                          // Ensure that the Header blocks are not included in the sort
    getEnd()->previous->next = NULL;                        // Remove the pointer to the end

    getStart()->next = iDSort(temp, sortChoice);            // Start sorting based on chosen method and get the new head node
    getStart()->next->previous = getStart();                // Reattach the head node back to the start sentinel

    
    temp = getStart();                                 
    while(temp->next != NULL){                              // Find the new tail node
        temp = temp->next;
    }

    temp->next = getEnd();                                  // Reattach the end sentinel to the tail node
    getEnd()->previous = temp;                              // Reattach the new tail node to the end sentinel
    
    system("clear");
    printData();                                            // Display the sorted results
}

