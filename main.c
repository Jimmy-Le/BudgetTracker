#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "budget.h"
#include "data.h"









int main(int argc, char * argv[]) {
    // get data (from command line) (from data.c)
    // callChoice(getUserInput());
    getData(argv[1]);
    printData();
    return 0;
}