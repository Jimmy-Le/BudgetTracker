#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"
#include "data.h"



int main(int argc, char * argv[]) {
    int programOver = 0;

    // get data (from command line) (from data.c)
    getData(argv[1]);
    system("clear");
    while(programOver == 0){
        printf("\n");
        system("clear");
        printMenu();
        programOver = callChoice(getUserInput(1, 7));
    }
    
    
    freeAllNodes();
    // printData();
    return 0;
}