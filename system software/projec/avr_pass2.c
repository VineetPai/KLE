#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token
{
    char label[100];
    char opcode[100];
    char operands[100];
    char operands1[100];
    char operands2[100];
};

int result, start = 000000, locctr = 0000, length = 0;
char line2[100], symbol[100];
int loc;

int tokenise(char line[1000], struct Token *token)
{
    FILE *foutput, *symtab, *optab;
    char code[10], mnemonic[3];
    int isDuplicate = 0;

    foutput = fopen("avr_output.txt", "a");
    symtab = fopen("avr_symbolTable.txt", "a");
    optab = fopen("avr_opcodeTable.txt", "r");

    result = sscanf(line, "%s %s %s", token->label, token->opcode, token->operands);

    // ... (rest of the code remains the same)

    fclose(foutput);
    return length;
}

void pass2(FILE *finput, FILE *foutput) {
    struct Token token;
    char line[1000];

    fseek(finput, 0, SEEK_SET); // Reset file pointer to the beginning

    while (fgets(line, 1000, finput) != NULL) {
        tokenise(line, &token);
        // Additional logic for pass 2, e.g., generating machine code
        // Example: fprintf(foutput, "Machine Code for %s\n", token.opcode);
    }
}

int main()
{
    int d = 0;
    struct Token token;
    FILE *finput, *foutput;
    char line[1000];

    finput = fopen("AVR_input.txt", "r");
    foutput = fopen("avr_output_pass2.txt", "a"); // You might want to use a different output file for pass 2

    while (fgets(line, 1000, finput) != NULL)
    {
        d = tokenise(line, &token);
    }

    pass2(finput, foutput);

    fclose(finput);
    fclose(foutput);

    printf("The length of the code is %x\n", d);
    return 0;
}
