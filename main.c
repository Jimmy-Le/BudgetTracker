#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"
#include "data.h"



/// @brief The main function
/// @param argc idk
/// @param argv List of arguments, ideally filename at index 1
/// @return integer status
int main(int argc, char * argv[]) {
    int programOver = 0;
    getData(argv[1]);           // get data (from command line)
    system("clear");
    while(programOver == 0){    // Continuously loop the program
        printf("\n");
        system("clear");
        printMenu();
        programOver = callChoice(getUserInput(1, 7));   // If there is an error status code, or the program exits, it will stop the program
    }
    
    freeAllNodes();                     // Free the list of entries
    return 0;
}