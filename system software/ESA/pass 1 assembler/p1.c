#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token
{
    char label[100];
    char opcode[100];
    char operands[100];
};

struct opTable
{
    char mnemonic[10];
    int length;
};

int searchOPTAB(struct opTable optab[], char opcode[], int optab_size)
{
    for (int i = 0; i < optab_size; i++)
    {
        if (strcmp(optab[i].mnemonic, opcode) == 0)
        {
            return i;
        }
    }
    return -1;
}

int result, start = 0x0000, locctr = 0x0000, length = 0;

int tokenise(char line[1000], struct Token *token)
{
    FILE *foutput, *symtab, *fopt;
    char code[10];
    int optsize = 0, optindex;
    struct opTable optab[100];

    foutput = fopen("output.txt", "a");
    symtab = fopen("symtab.txt", "a");
    fopt = fopen("optab.txt", "r");

    while (fscanf(fopt, "%s %d", optab[optsize].mnemonic, &optab[optsize].length) != EOF)
    {
        optsize++;
    }
    fclose(fopt);

    result = sscanf(line, "%s %s %s", token->label, token->opcode, token->operands);

    if (result == 2)
    {
        char temp[1000], temp1[1000];
        strcpy(temp1, token->opcode);
        strcpy(temp, token->label);
        strcpy(token->opcode, temp);
        strcpy(token->operands, temp1);
        strcpy(token->label, "\0");
    }
    else if (result == 1)
    {
        strcpy(token->opcode, token->label);
        strcpy(token->operands, "\0");
        strcpy(token->label, "\0");
    }

    if (strcmp(token->opcode, "START") == 0)
    {
        start = strtol(token->operands, NULL, 16);
        locctr = start;
        fprintf(foutput, "%04X\t%s\t%s\t%s\n", locctr, token->label, token->opcode, token->operands);
    }
    else if (strcmp(token->opcode, "END") != 0)
    {
        fprintf(foutput, "%04X\t", locctr);
        if (token->label[0] != '\0')
        {
            char line2[100], symbol[100];
            int loc;
            int isDuplicate = 0;

            // Close and reopen symtab file for reading
            fclose(symtab);
            symtab = fopen("symtab.txt", "r");

            while (fgets(line2, 100, symtab) != NULL)
            {
                sscanf(line2, "%s %x", symbol, &loc);
                if (strcmp(token->label, symbol) == 0)
                {
                    printf("%s is a duplicate symbol\n", symbol);
                    isDuplicate = 1;
                    break;
                }
            }

            // Close symtab file after reading
            fclose(symtab);

            if (!isDuplicate)
            {
                symtab = fopen("symtab.txt", "a");
                fprintf(symtab, "%s\t%04X\n", token->label, locctr);
                fclose(symtab);
            }
        }

        optindex = searchOPTAB(optab, token->opcode, optsize);
        if (optindex != -1)
        {
            locctr = locctr + 3;
        }

        else if (strcmp(token->opcode, "WORD") == 0)
        {
            locctr += 3;
        }
        else if (strcmp(token->opcode, "RESW") == 0)
        {
            locctr += (3 * (atoi(token->operands)));
        }
        else if (strcmp(token->opcode, "RESB") == 0)
            locctr += atoi(token->operands);
        else if (strcmp(token->opcode, "BYTE") == 0)
        {
            if (token->operands[0] == 'C')
            {
                int operand_length = strlen(token->operands) - 3;
                locctr += operand_length;
            }
            else if (token->operands[0] == 'X')
            {
                int operand_length = strlen(token->operands) - 3;
                locctr += operand_length / 2;
            }
        }
        else
        {
            printf("%s is an invalid opcode\n", token->opcode);
        }
        fprintf(foutput, " %s\t%s\t%s\n", token->label, token->opcode, token->operands);
    }
    else if (strcmp(token->opcode, "END") == 0)
        printf("");

    length = (locctr - start);
    fclose(foutput);
    return length;
}

int main()
{
    int d = 0;
    struct Token token;
    FILE *finput, *foutput,*flength;
    char line[1000];
    finput = fopen("input.txt", "r");
    flength = fopen("length.txt","w");
    while (fgets(line, 1000, finput) != NULL)
    {
        d = tokenise(line, &token);
    }
    fclose(finput);
    printf("the length of program is %04X\n", d);
    fprintf(flength,"%04X\n", d);
    return 0;
}

/*
COPY START 1000
FIRST   STL  RETADR
CLOOP  JSUB      RDREC
LDA   LENGTH
COMP ZERO
JEQ   ENDFIL
JSUB   WRREC
J    CLOOP
ENDFIL LDA EOF
STA  BUFFER
LDA THREE
ENDFIL STA EOF
CLOOP STA LENGTH
JSUB WRREC
SHRADDHA 2
LDL RETADR
RSUB
EOF BYTE  C'EOF'
THREE WORD 3
INPUT   BYTE X'F1F2'
ZERO WORD 0
RETADR RESW 1
LENGTH RESW 7
BUFFEND   RESB   10
equ
BUFFER SHRADDHA 4096
END


LDX  04
MUL  20
RD   D8
RSUB  4C
STA  0C
STCH  54
STL  14
STX  10
TD  E0
TIX  2C
WD  DC
ADD  18
COMP  28
J  3C
JEQ  30
JGT  34
JLT  38
JSUB  48
LDA  00
LDB  68
LDCH  50
LDL  08


FIRST 1000
CLOOP 1003
ENDFIL 1015
EOF 102D
THREE 1030
INPUT 1033
ZERO 1035
RETADR 1038
LENGTH 103B
BUFFEND 1050
*/
