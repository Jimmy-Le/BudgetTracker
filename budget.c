#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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
int getUserInput(){

    printMenu();
    validChoice = scanf("%d", &choice);

    if(validChoice != 1 || choice < 1 || choice > 7){
        system("clear");

        printf("Invalid input\n");
        return 0;
    }
    return choice;
}


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
        printf("number is: %d \n", chosenNumber );
        break;
    case 5:
        printf("number is: %d \n", chosenNumber );
        break;
    case 6:
        printf("number is: %d \n", chosenNumber );
        break;
    case 7:
    default:
        printf("Goodbye and thanks for using our budget tracker app!!!\n");
        break;
    }


}