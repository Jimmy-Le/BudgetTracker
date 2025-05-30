#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"


int choice;
int validChoice;


// This function will print out the menu and get the user's input
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



// Get an input from the user and return their choice
// if the choice is invalid, return 0
// bottom: the lower bound limit of the input
// top: the upper bound limit of the input
int getUserInput(int bottom, int top){

    // printMenu();
    validChoice = scanf("%d", &choice);

    if(validChoice != 1 || choice < bottom || choice > top){
        system("clear");

        printf("Invalid input\n");
        return 0;
    }
    return choice;
}


// This function will calculate the total income, expenses, wants and needs as well as the net balance
void getExpenseDistribution(){
    double totalIncome = 0;
    double totalExpenses = 0;
    double totalNeeds = 0;
    double totalWants = 0;

    Node* temp = getStart();

    while(temp){
        // Making sure to skip the header nodes
        if (temp->next == NULL ||temp->previous == NULL){
        }else{
            // Check if the Type is "income" and add up the amount
            if(strcasecmp(temp->dataItem.entryType, "income") == 0){
                totalIncome = totalIncome + temp->dataItem.amount;

            // Check if the Type is "expense" and add up the amount
            } else if(strcasecmp(temp->dataItem.entryType, "expense") == 0){
                totalExpenses = totalExpenses + temp->dataItem.amount;

                // Check if the Subtype is "needs" and add up the amount
                if(strcasecmp(temp->dataItem.entrySubType, "needs") == 0){
                    totalNeeds = totalNeeds + temp->dataItem.amount;

                // Check if the Subtype is "wants" and add up the amount
                } else if (strcasecmp(temp->dataItem.entrySubType, "wants") == 0){
                    totalWants = totalWants + temp->dataItem.amount;
                }
            }
        }
        temp = temp->next;
    }


    printf("======== Expense Distribution Report ======== \n");
    printf("Total Income: $%.2f \n", totalIncome);
    printf("Total Expenses: $%.2f \n", totalExpenses);
    printf("Total Needs: $%.2f (%.2f%% of expenses, %.2f%% of income) \n", totalNeeds, (totalNeeds/totalExpenses)*100, (totalNeeds/totalIncome)*100);
    printf("Total Wants: $%.2f (%.2f%% of expenses, %.2f%% of income) \n", totalWants, (totalWants/totalExpenses)*100, (totalWants/totalIncome)*100);
    printf("Net Balance: $%.2f \n", totalIncome - totalExpenses);
    printf("============================================= \n");
}



Node* getNodeIDChoice(){

    Node* nodeToModify = getStart();
    // Get user input for ID
    validChoice = scanf("%d", &choice);

    // Making sure that the input is an Integer
    if(validChoice != 1){
        printf("Invalid input\n");
        return nodeToModify;

    } else {
        Node* temp = getStart();
        while(temp){
            // Making sure to skip printing the header nodes
            if (temp->next == NULL ||temp->previous == NULL){
            }else if (temp->dataItem.entryID == choice){

                nodeToModify = temp;
            }
            temp = temp->next;
        }
        return nodeToModify;
    }
}


int addEntry(){

    char *dateAnswer = malloc(2);
    
    time_t currentTime;
    time(&currentTime);

    int newYear;
    int newMonth;
    int newDay;
    char *newDate = malloc(10); // Year = 4, Month = 2, Day = 2, +2 for dashes + 1 for terminal
    char *newType = malloc(10); // expenses = 7 , + 1 for terminal + 2 for emergency
    char *newSubtype = malloc(10); // passive = 7 , + 1 for terminal + 2 for emergency
    char *newDescription = malloc(25); // descriptions can be long

    double newAmount;

    printf("Adding Income/Expenses\n");
    printf("------------------------\n");
    printf("Use today's date? (y/n): ");
    validChoice = scanf("%s", dateAnswer);

    // Validating user input
    if (validChoice != 1){
        printf("\nInvalid input");
        return 1;
    } 
    

    // Setting up the Date
    if (strcasecmp(dateAnswer, "y") == 0){
        newYear = localtime(&currentTime)->tm_year + 1900;
        newMonth = localtime(&currentTime)->tm_mon + 1;
        newDay = localtime(&currentTime)->tm_mday;

    } else if (strcasecmp(dateAnswer, "n") == 0){

        int tripleValidation = 0;

        printf("\nEnter new year (YYYY): ");
        validChoice = scanf("%d",&newYear);
        tripleValidation = tripleValidation + validChoice;

        printf("\nEnter new month (MM): ");
        validChoice = scanf("%d",&newMonth);
        tripleValidation = tripleValidation + validChoice;

        printf("\nEnter new day (DD): ");
        validChoice = scanf("%d", &newDay);
        tripleValidation = tripleValidation + validChoice;

        // validChoice is valid when it is 1, thus if we add all of the valid choices we should get a total of 3
        if(tripleValidation != 3){
            printf("\nInvalid input");
            return 1;
        }

    } else {
        printf("\nInvalid input");
        return 1;
    }
    
    sprintf(newDate, "%d-%02d-%02d", newYear, newMonth,newDay);
    // Set up Sections
    // We'll assume a perfect user for now
    printf("\nType (income/expense): ");
    scanf("%s", newType);
    printf("\nCategory: ");
    scanf("%s", newSubtype);
    printf("\nDescription: ");
    scanf(" %[^\t\n]", newDescription);
    printf("\nAmount: $");
    scanf("%lf", &newAmount);

    Node *newNode = createNode(generateNewID(),newDate,newType,newSubtype, newDescription,newAmount);
    push(newNode);
    if(addToFile() == 0){
        printf("\nEntry added successfully with ID %d", newNode->dataItem.entryID);
    }

    free(dateAnswer);
    free(newDate);
    free(newType);
    free(newDescription);
    return 0;

}



int modifyEntry(){
    printData();


    printf("\nEnter ID of entry to modify: ");

    Node* nodeToModify = getNodeIDChoice();
    if(nodeToModify->previous == NULL){
        // DO ERROR TODO
        return 1;
    }
    printf("\nCurrent Details: \n");
    printNode(nodeToModify, 1);

    printf("What would you like to modify?\n");
    printf("1. Date\n");
    printf("2. Amount\n");
    printf("Choice: ");
    choice = getUserInput(1,2);

    if (choice == 1){
        int newYear;
        int newMonth;
        int newDay;
        printf("\nEnter new year (YYYY): ");
        validChoice = scanf("%d",&newYear);

        printf("\nEnter new month (MM): ");
        validChoice = scanf("%d",&newMonth);

        printf("\nEnter new day (DD): ");
        validChoice = scanf("%d", &newDay);

        // TODO DATA VALIDATION

        // This will store the new date of format "YYYY-MM-DD" where the +3 includes the dashes and terminal symbol
        char *newDate = malloc(sizeof(newYear) + sizeof(newMonth) + sizeof(newDay) + 3);
        sprintf(newDate, "%d-%02d-%02d", newYear, newMonth,newDay);

        strcpy(nodeToModify->dataItem.date, newDate);


        
        if(updateFile("w") == 0){
            printf("\nEntry updated sucessfully");
        }
        
        free(newDate);

    } else if (choice == 2){
        
        double newAmount;
        printf("\nEnter new amount: $");
        validChoice = scanf("%lf",&newAmount);

        // TODO Data validation
        
        nodeToModify->dataItem.amount = newAmount;
        if(updateFile() == 0){
            printf("\nEntry updated sucessfully");
        }
 
    }
    
    return 0;
}



void filterByMonth(){ // TODO

    char year;
    char month;
    // char* res;

    printf("\nPlease enter year (YYYY): ");

    // Get user input for ID
    int yearValidity = scanf("%s", &year);

    printf("\nPlease enter month (1-12): ");

    int monthValidity = scanf("%s", &month);

    // Making sure that the input is an Integer
    if(yearValidity != 0 || monthValidity != 0){
        printf("Invalid input\n");

    } else {
        Node* temp = getStart();
        while(temp){
            // Making sure to skip printing the header nodes
            if (temp->next == NULL ||temp->previous == NULL){
            }else if( strcmp(strtok(temp->dataItem.date, "-"), &year) == 0){
                //  strcasecmp(strtok(temp->dataItem.date, "-"), year) == 0 &&  strcasecmp(strtok(NULL, "-"), month) == 0
                printNode(temp, 0);
             
            }
            temp = temp->next;
        }
    
    }

}




// This function will call other functions depending on the user choice
int callChoice(int chosenNumber){
    system("clear");
    switch (chosenNumber){
    case 1:
        printData();
        break;
    case 2:
        getExpenseDistribution();
        break;
    case 3:
        printf("number is: %d \n", chosenNumber );
        break;
    case 4:
        addEntry();
        break;
    case 5:
        modifyEntry(); 
        break;
    case 6:
        filterByMonth();
        break;
    default:
        printf("Invalid Input \n");
    case 7:
        printf("\nGoodbye and thanks for using our budget tracker app!!!\n\n");
        return 1;
        break;
    }
    
    char enterKey;
    printf("\nPress any key then ENTER to continue: ");
    scanf("%s", &enterKey);

    return 0;



}