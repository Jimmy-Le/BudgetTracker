#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
// #include "budget.h"
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






// Function to merge two sorted doubly linked lists
Node *merge( Node *first, Node *second, int mode) {
  
    // If either list is empty, return the other list
    if (first == NULL)
        return second;
    if (second == NULL)
        return first;

    // Pick the smaller value between first and 

    int sortCondition;
    switch (mode){
    case 1:
        sortCondition = first->dataItem.entryID < second->dataItem.entryID;
        break;
    case 2:
        sortCondition = compareDates(first, second);
        break;
    case 3:
        sortCondition = first->dataItem.amount < second->dataItem.amount;
        break;
    case 4:
        sortCondition = strcasecmp(first->dataItem.entryDescription, second->dataItem.entryDescription) < 0;
        break;
    default:
        break;
    }

   // second nodes
    if (sortCondition) {
      
        // Recursively merge the rest of the lists and
        // link the result to the current node
        first->next = merge(first->next, second, mode);
        if (first->next != NULL) {
            first->next->previous = first;
        }
        first->previous = NULL;
        return first;
    }
    else {
      
        // Recursively merge the rest of the lists and
        // link the result to the current node
        second->next = merge(first, second->next, mode);
        if (second->next != NULL) {
            second->next->previous = second;
        }
        second->previous = NULL;
        return second;
    }
}


// Function to perform merge sort on a doubly linked list
Node *iDSort(Node *head, int mode) {
  
    // Base case: if the list is empty or has only
    // one node, it's already sorted
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Split the list into two halves
    Node *second = split(head);

    // Recursively sort each half
    head = iDSort(head, mode);
    second = iDSort(second, mode);

    // Merge the two sorted halves
    return merge(head, second, mode);
}






void sortByChoice(int sortChoice){
    
    // Ensure that the Header blocks are not included in the sort
    Node *temp = getStart()->next;
    getEnd()->previous->next = NULL; // Remove the pointer to the end
    getStart()->next = iDSort(temp, sortChoice);
   
    


    getStart()->next->previous = getStart();

    // Get to the tail node and attach the End Node to it
    temp = getStart();
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = getEnd();
    getEnd()->previous = temp;
    system("clear");
    printData();
}

