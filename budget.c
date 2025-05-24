#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>



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

int callChoice(int chosenNumber){
    
    switch (chosenNumber){
    case 1:
        printf("number is: %d \n", chosenNumber );
        break;
    case 2:
        printf("number is: %d \n", chosenNumber );
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