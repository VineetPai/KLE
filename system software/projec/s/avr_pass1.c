
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
char line2[100],symbol[100];
int loc;

int tokenise(char line[1000], struct Token *token)
{
    FILE *foutput, *symtab, *optab;
    char code[10], mnemonic[3];
    int isDuplicate=0;

    foutput = fopen("avr_output.txt","w");
    symtab = fopen("avr_symbolTable.txt", "w");
    optab = fopen("avr_opcodeTable.txt", "r");

    result = sscanf(line, "%s %s %s", token->label, token->opcode, token->operands);
    if (result == 2)
    {
        char temp[1000], temp1[1000],temp2[1000];
        strcpy(temp1, token->opcode);
        strcpy(temp, token->label);
        strcpy(token->opcode, temp);
        strcpy(token->operands, temp1);
        //strcpy(token->operands2, temp2);
        strcpy(token->label, "\0");
    }
    else if (result == 1)
    {
        strcpy(token->opcode, token->label);
        strcpy(token->operands,"\0");
        strcpy(token->operands1, "\0");
        strcpy(token->operands2, "\0");
        strcpy(token->label, "\0");
    }
    else if(result ==3)
    {
        while (fgets(line2, 100, symtab) != NULL)
        {
            sscanf(line2, "%s %x", symbol, &loc);
            if (strcmp(token->label, symbol) == 0) {
                printf("%s is a duplicate symbol\n");
                isDuplicate = 1; // Set the flag to indicate a duplicate symbol
                break; // No need to continue checking
        }
        }

        if (!isDuplicate) {
            fprintf(symtab, "%s\t%04x\n", token->label, locctr);
        }

    }

    if (strcmp(token->opcode, ".ORG") == 0)
    {
        int i,j=0;
        char loc[10];

        j=0;
        for(i=2;i<strlen(token->operands);i++)
        {
            loc[j]=token->operands[i];
            j++;
        }
        //loc[j]='/0';
        //printf("%s ",loc);
        //start = strtol(loc, NULL, 10);
        start =strtol(loc, NULL, 16);
        printf("%d",start);
        locctr = start;

        fprintf(foutput, "%04x\t%s\t%s\t%s\n", locctr, token->label, token->opcode, token->operands);
    }

    else if (strcmp(token->opcode, "NOP") != 0)
    {
        fprintf(foutput, "%04x\t", locctr);
        printf("%04x\n",locctr);


        if(strcmp(token->opcode, "LDS")==0)
        {
            locctr += 4;
        }
        else if(strcmp(token->opcode, "STS")==0)
        {
            locctr += 4;
        }
        else if(strcmp(token->opcode, "CALL")==0)
        {
            locctr += 4;
        }
        else  if(strcmp(token->opcode, "JMP")==0)
        {
            locctr += 4;
        }
        else{
            locctr += 2;
        }

        fprintf(foutput, " %s\t%s\t%s\n", token->label, token->opcode, token->operands);


    }
    else if(strcmp(token->opcode,"NOP")==0)
            printf("");
    else
        {
            printf("%s is invalid opcode\n",token->opcode);
        }

    length = (locctr - start);
    fclose(foutput);
    return length;
}

int main()
{
    int d = 0;
    struct Token token;
    FILE *finput,*foutput;
    char line[1000];
    finput = fopen("AVR_input.txt", "r");

    while (fgets(line, 1000, finput) != NULL)
    {
        d = tokenise(line, &token);
    }

    fclose(finput);

    //foutput = fopen("avr_output.txt", "w");
    //fprintf(foutput, "%04x\t%s\t%s\n", locctr, token.label, token.opcode, token.operands);
    //fclose(foutput);
    printf("the length of the code is %x\n", d);
    return 0;
}



