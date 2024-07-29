#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

typedef struct {
    char label[20];
    int address;
} Symbol;

void processLine(char *line, Symbol *symbolTable, int *symbolCount);

int main() {
    FILE *inputFile = fopen("suman.txt", "r");

    if (!inputFile) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    Symbol symbolTable[100];  // Adjust the size as needed
    int symbolCount = 0;

    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        processLine(line, symbolTable, &symbolCount);
    }

    // Print the symbol table
    printf("Symbol Table:\n");
    for (int i = 0; i < symbolCount; ++i) {
        printf("%s\t%d\n", symbolTable[i].label, symbolTable[i].address);
    }

    fclose(inputFile);

    return 0;
}

void processLine(char *line, Symbol *symbolTable, int *symbolCount) {
    char label[20];
    char instruction[20];

    int address;
    int parsedItems = sscanf(line, "%s %s %x", label, instruction, &address);

    if (parsedItems >= 2) {
        if (parsedItems == 3) {
            // If an address is present, update the symbol table
            strcpy(symbolTable[*symbolCount].label, label);
            symbolTable[*symbolCount].address = address;
            (*symbolCount)++;
        }
    }
}
