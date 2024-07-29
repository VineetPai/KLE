
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent entries in the symbol table.
struct SymbolEntry {
    char label[100];
    int address;
};

// Define a list of valid operation codes.
const char* validOpCodes[] = {
    "ADD", "SUB", "MUL", "DIV", // Add more as needed
    "WORD", "RESW", "RESB", "BYTE",
    "END", // Include the END marker
};

int main()
{
    FILE* input_file = fopen("input1.txt", "r");
    FILE* symbol_table_file = fopen("symbol_table.txt", "w");

    if (input_file == NULL)
        {
            printf("Error: Unable to open input file.\n");
            return 1;
        }

    if (symbol_table_file == NULL)
        {
            printf("Error: Unable to create symbol table file.\n");
            return 1;
        }

    // Initialize variables
    struct SymbolEntry symbol_table[100]; // Maximum of 100 symbols
    int symbol_count = 0;
    int valid_opcode;

    char line[256];
    int locctr = 1000;

    while (fgets(line, sizeof(line), input_file) != NULL)
        {
            char label[100];
            char opcode[10];
            char operand[100];

        // Parse the line into label, opcode, and operand
            if (sscanf(line, "%s %s %s", label, opcode, operand) == 3)
                {
                // Check if it's not a comment line
                if (opcode[0] != '.')
                {
                    // Check if the operation code is valid
                    valid_opcode = 0;
                    for (int i = 0; i < sizeof(validOpCodes) / sizeof(validOpCodes[0]); i++)
                    {
                        if (strcmp(validOpCodes[i], opcode) == 0)
                        {
                            valid_opcode = 1;
                            break;
                        }
                    }

                    if (!valid_opcode)
                        {
                        printf("Error: Invalid operation code '%s' at address %d\n", opcode, locctr);
                        }

                    if (strcmp(label, "START") == 0)
                        {
                        // Set the initial LOCCTR value
                        locctr = strtol(operand, NULL, 10);
                        }

                    if (label[0] != '\0' && strcmp(label, "START") != 0)
                        {
                        // Add the symbol to the symbol table
                        strcpy(symbol_table[symbol_count].label, label);
                        symbol_table[symbol_count].address = locctr;
                        symbol_count++;
                        }

                    if (valid_opcode)
                        {
                        if (strcmp(opcode, "WORD") == 0)
                        {
                            locctr += 3;
                        }
                        else if (strcmp(opcode, "RESW") == 0)
                            {
                                locctr += 3 * atoi(operand);
                            }
                        else if (strcmp(opcode, "RESB") == 0)
                            {
                                locctr += atoi(operand);
                            }
                        else if (strcmp(opcode, "BYTE") == 0)
                            {
                            // Calculate the length of the constant in bytes and add it to LOCCTR.
                                int constant_length = strlen(operand);
                                locctr += constant_length;
                            }
                        else
                            {
                                locctr += 3; // Default instruction length
                            }
                        }
                    }
                }
        }

    // Write the symbol table to the output file
    fprintf(symbol_table_file, "Symbol Table:\n");
    fprintf(symbol_table_file, "Label\tAddress\n");
    for (int i = 0; i < symbol_count; i++)
        {
            fprintf(symbol_table_file, "%s\t%d\n", symbol_table[i].label, symbol_table[i].address);
        }

    // Close files
    fclose(input_file);
    fclose(symbol_table_file);

    printf("Symbol table written to 'symbol_table.txt'\n");

    return 0;
}
