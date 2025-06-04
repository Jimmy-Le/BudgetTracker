#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "ordering.h"


int choice;                 // This will store the numerical input that the user needs to make
int validChoice;            // This will store the result of the validity of the user inputs

/// @brief This function will print out the menu and get the user's input
/// @return integer status
int printMenu() {
    printf("Budget Tracking System\n");
    printf("=======================\n");
    printf("1. Display all entries\n");
    printf("2. Expense Distribution\n");
    printf("3. Sort Entries\n");
    printf("4. Add Income/Expense Entry\n");
    printf("5. Modify Entry\n");
    printf("6. Filter by Month\n");
    printf("7. Exit\n");
    printf("Choice: ");
    return 0;
}

/// @brief Get an integer input from the user and return their choice
/// if the choice is invalid, return -1
/// @param bottom integer the lower bound limit of the input
/// @param top integer the upper bound limit of the input
/// @return integer, either the result of the user input or -1 if invalid input
int getUserInput(int bottom, int top){

    validChoice = scanf("%d", &choice);

    if(validChoice != 1 || choice < bottom || choice > top){    // Check if the user input matches the datatype and if it is within the given range
        system("clear");      
        printf("Invalid input\n");
        return -1;                                              // return 1 if invalid
    }
    return choice;
}

/// @brief This function will calculate the total income, expenses, wants and needs as well as the net balance
void getExpenseDistribution(){
    double totalIncome = 0;
    double totalExpenses = 0;
    double totalNeeds = 0;
    double totalWants = 0;

    Node* temp = getStart();

    while(temp){
        if (temp->next == NULL ||temp->previous == NULL){                           // Making sure to skip the header nodes
        }else{
            if(strcasecmp(temp->dataItem.entryType, "income") == 0){                // Check if the Type is "income" and add up the amount
                totalIncome = totalIncome + temp->dataItem.amount;
            
            } else if(strcasecmp(temp->dataItem.entryType, "expense") == 0){        // Check if the Type is "expense" and add up the amount
                totalExpenses = totalExpenses + temp->dataItem.amount;

                if(strcasecmp(temp->dataItem.entrySubType, "needs") == 0){          // Check if the Subtype is "needs" and add up the amount
                    totalNeeds = totalNeeds + temp->dataItem.amount;

                } else if (strcasecmp(temp->dataItem.entrySubType, "wants") == 0){  // Check if the Subtype is "wants" and add up the amount
                    totalWants = totalWants + temp->dataItem.amount;
                }
            }
        }
        temp = temp->next;
    }


    printf("======== Expense Distribution Report ======== \n");                     // Print out the results
    printf("Total Income: $%.2f \n", totalIncome);
    printf("Total Expenses: $%.2f \n", totalExpenses);
    printf("Total Needs: $%.2f (%.2f%% of expenses, %.2f%% of income) \n", totalNeeds, (totalNeeds/totalExpenses)*100, (totalNeeds/totalIncome)*100);
    printf("Total Wants: $%.2f (%.2f%% of expenses, %.2f%% of income) \n", totalWants, (totalWants/totalExpenses)*100, (totalWants/totalIncome)*100);
    printf("Net Balance: $%.2f \n", totalIncome - totalExpenses);
    printf("============================================= \n");
}

/// @brief This function prints out the sorting menu and call for user input
/// @return integer status
int sortingMenu(){

    printf("Sort Menu\n");
    printf("-----------\n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Amount\n");
    printf("4. Sort by Description\n");

    int res = getUserInput(1,4);                                    // Get the user input from between 1 and 4

    if(res == -1){                                                  // If invalid input, return 1 status
        return 1;
    }
    sortByChoice(choice);                                           // send the user input to sortByChoice which will handle which kind of sorting will occur
    return 0;
}

/// @brief This function will handle getting the user input for an ID and return the corresponding Node
/// @return Node with corresponding ID, if not found then return the start sentinel
Node* getNodeIDChoice(){

    Node* nodeToModify = getStart();
    
    validChoice = scanf("%d", &choice);                             // Get user input for ID

    if(validChoice != 1){                                           // Making sure that the input is an Integer
        printf("Invalid input\n");
        return nodeToModify;

    } else {
        Node* temp = getStart();
        while(temp){
            
            if (temp->previous == NULL){                            // Making sure to skip printing the header node, but allowing the tail to go through
            }else if (temp->dataItem.entryID == choice){            // Comparing Node ID with the user input
                nodeToModify = temp;        
                return nodeToModify;                        
            }
            temp = temp->next;
        }
        return nodeToModify;                                        // If not found, this should return the tail sentinel
    }
}


/// @brief get the user input and create a new entry into the file
/// @return integer status
int addEntry(){

    char *dateAnswer = malloc(3);           // Variable to store the y/n answer from the user
    
    time_t currentTime;                     // Variable to store the current time 
    time(&currentTime);

    int newYear;                            // Variables for storing parts of a date
    int newMonth;
    int newDay;

    char *newDate = malloc(10);             // Year = 4, Month = 2, Day = 2, +2 for dashes + 1 for terminal
    char *newType = malloc(10);             // expenses = 7 , + 1 for terminal + 2 for emergency
    char *newSubtype = malloc(10);          // passive = 7 , + 1 for terminal + 2 for emergency
    char *newDescription = malloc(25);      // descriptions can be long

    double newAmount;                       // Variable to store the amount


    printf("Adding Income/Expenses\n");                         // Print and get user y/n input
    printf("------------------------\n");
    printf("Use today's date? (y/n): ");
    validChoice = scanf("%s", dateAnswer);
                                              
    if (validChoice != 1){                                      // Validating user input
        printf("\nInvalid input");
        return 1;
    } 
    

    
    if (strcasecmp(dateAnswer, "y") == 0){                      // Setting up the current Date
        newYear = localtime(&currentTime)->tm_year + 1900;
        newMonth = localtime(&currentTime)->tm_mon + 1;
        newDay = localtime(&currentTime)->tm_mday;

    } else if (strcasecmp(dateAnswer, "n") == 0){               // Let user input their own date

        int tripleValidation = 0;                               // This lets me validate all 3 inputs at once

        printf("\nEnter new year (YYYY): ");                    // Get the Year
        validChoice = scanf("%d",&newYear);
        tripleValidation = tripleValidation + validChoice;

        printf("\nEnter new month (MM): ");                     // Get the month
        validChoice = scanf("%d",&newMonth);
        tripleValidation = tripleValidation + validChoice;

        printf("\nEnter new day (DD): ");                       // Get the day
        validChoice = scanf("%d", &newDay);
        tripleValidation = tripleValidation + validChoice;

        
        if(tripleValidation != 3){                              // validChoice is valid when it is 1, thus if we add all of the valid choices we should get a total of 3
            printf("\nInvalid input");
            return 1;
        }

    } else {                                                    // One of the inputs was invalid
        printf("\nInvalid input");
        return 1;
    }
    
    sprintf(newDate, "%d-%02d-%02d", newYear, newMonth,newDay);     // Convert the inputted date into a string

    // Set up Sections
    // We'll assume a perfect user for now
    printf("\nType (income/expense): ");                            // Get Type
    scanf("%s", newType);

    printf("\nCategory: ");                                         // Get Subtype
    scanf("%s", newSubtype);

    printf("\nDescription: ");                                      // Get Description
    scanf(" %[^\t\n]", newDescription);

    printf("\nAmount: $");                                          // Get Amount
    scanf("%lf", &newAmount);

    if (newAmount < 0){                                             // Make sure that the amount is not negative
        printf("\nInvalid Input: Negative Number\n");   
        return 1;
    }

    Node *newNode = createNode(generateNewID(),newDate,newType,newSubtype, newDescription,newAmount);   // Create a new node
    push(newNode);                                                                                      // Push the new node on the list

    if(updateFile() == 0){          // Update the file (Usually we want to use the addToFile() function but theres bugs that might breal)
        printf("\nEntry added successfully with ID %d", newNode->dataItem.entryID);
    }

    free(dateAnswer);               // Free all the temporary variables initialized in this function
    free(newDate);
    free(newType);
    free(newDescription);
    return 0;

}


/// @brief Modify an entry in the files using entry ID
/// @return integer status
int modifyEntry(){
    printData();                                                        // Display all the entries

    printf("\nEnter ID of entry to modify: ");

    Node* nodeToModify = getNodeIDChoice();                             // Get the Node to modify
    if(nodeToModify->previous == NULL || nodeToModify->next == NULL){   // If the Node is one of the sentinels, then there was an invalid input
        printf("No Entry with that ID was found\n");
        return 1;
    }

    printf("\nCurrent Details: \n");                                    
    printNode(nodeToModify, 1);                                         // Print out all the data of the nodes in a line by line format

    printf("What would you like to modify?\n");
    printf("1. Date\n");
    printf("2. Amount\n");
    printf("Choice: ");
    choice = getUserInput(1,2);                                         // Get user input from between 1 and 2

    if (choice == 1){                                                   // User decided to modify the date
        int newYear;
        int newMonth;
        int newDay;

        int tripleValidation = 0;                                       // Allows me to verify all 3 entries at once

        printf("\nEnter new year (YYYY): ");                            // Get Year
        validChoice = scanf("%d",&newYear);
        tripleValidation = tripleValidation + validChoice;

        printf("\nEnter new month (MM): ");                             // Get Month
        validChoice = scanf("%d",&newMonth);
        tripleValidation = tripleValidation + validChoice;

        printf("\nEnter new day (DD): ");                               // Get Day
        validChoice = scanf("%d", &newDay);
        tripleValidation = tripleValidation + validChoice;

        if(tripleValidation != 3){                                      // validChoice is valid when it is 1, thus if we add all of the valid choices we should get a total of 3
            printf("\nInvalid input");
            return 1;
        }

        // This will store the new date of format "YYYY-MM-DD" where the +3 includes the dashes and terminal symbol
        char *newDate = malloc(sizeof(newYear) + sizeof(newMonth) + sizeof(newDay) + 3);
        sprintf(newDate, "%d-%02d-%02d", newYear, newMonth,newDay);         // Convert data to string

        strcpy(nodeToModify->dataItem.date, newDate);                       // Add it in the newDate 

        
        if(updateFile("w") == 0){                                           // Update the actual file
            printf("\nEntry updated sucessfully");
        }
        
        free(newDate);                                                      // Free newDate

    } else if (choice == 2){                // The user chose to update the amount
        
        double newAmount;
        printf("\nEnter new amount: $");
        validChoice = scanf("%lf",&newAmount);                              // Get user input
        
        if(validChoice != 1){                                               // Make sure that it is a number
            printf("\nInvalid input");
            return 1;
        }

        nodeToModify->dataItem.amount = newAmount;                          // Directly update the amount in the node
        if(updateFile() == 0){                                              // Update the file
            printf("\nEntry updated sucessfully");
        }
 
    } 
    
    return 0;
}


/// @brief Display the results that corresponds to the year and month inputted by the user
/// @return integer status
int filterByMonth(){
    int year;                                   // Stores the users input
    int month;

    int storedYear;                             // These will hold the stored dates separated
    int storedMonth;

    char dateData[20];                          // This will hold the stored dates
    char *parsedDate;

    int itemCounter = 0;                        // This is to help display to the user that no entry has been found


    printf("Filter by Month \n");
    printf("------------------\n");
    printf("Please enter year (YYYY): ");

    
    year = getUserInput(0, 9999);               // Get user input for a year with a range of 0 to 9999
    if (year < 0){
        return 1;
    }

    printf("Please enter month (1-12): ");

    month = getUserInput(1,12);                 // Get user input for a month with a range of 1 to 12

    if(month < 0){
        return 1;
    }
 
    printf("\n");
    printHeader();                              // Print the header
    Node* temp = getStart();
    while(temp){
        if (temp->next == NULL ||temp->previous == NULL){       // Making sure to skip printing the header nodes
        }else{
            
            strncpy(dateData, temp->dataItem.date, sizeof(dateData));       // copy the stored date to be parsed

            parsedDate = strtok(dateData, "-");                             // Split the date into sections
            storedYear = atoi(parsedDate);       

            parsedDate = strtok(NULL, "-");
            storedMonth = atoi(parsedDate);

            if(storedYear == year && storedMonth == month){                 // Compare the stored dates with user input
                printNode(temp,0);
                itemCounter = itemCounter + 1;                              // increment the number of entries found
            }
            
        }
        temp = temp->next;
    }
    if(itemCounter == 0){                                                   // No entries has been found, print that out
        printf("No Data Found\n");
    } 
    return 0;

}


/// @brief This function will call other functions depending on the user choice
/// @param chosenNumber integer user chosen number
/// @return integer status 
int callChoice(int chosenNumber){
    system("clear");
    switch (chosenNumber){
    case 1:                                 // Display all entries
        printData();                                     
        break;
    case 2:                                 // Get Expense Distribution
        getExpenseDistribution();
        break;
    case 3:                                 // Sort 
        sortingMenu();                      
        break;
    case 4:                                 // Add Entry
        addEntry();
        break;
    case 5:                                 // Modify Entry
        modifyEntry(); 
        break;
    case 6:                                 // Filter by month
        filterByMonth();
        break;
    default:                                // Any input not within 1-7
        printf("Invalid Input \n");
        break;
    case 7:                                 // Exit Program
        printf("\nGoodbye and thanks for using our budget tracker app!!!\n\n");
        return 1;
        break;
    }
    
    // To ensure that we can return back to the main menu
    char enterKey[10];
    printf("\nPress any key then ENTER to continue: ");
    scanf("%s", enterKey);

    return 0;
}