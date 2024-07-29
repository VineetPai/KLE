
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

typedef struct
{
    char variable[30];
    int value;
}var_tab;

var_tab vartab[100];

int result, start = 000000, locctr = 0000, length = 0, var_tab_pointer=0;
char line2[100],symbol[100];
int loc;
int Register[32]={1,2,3,4,5,6};
int tokenise(char line[1000], struct Token *token)
{
    FILE *foutput, *symtab, *optab;
    char code[10], mnemonic[3];
    int isDuplicate=0;
    foutput = fopen("avr_output.txt","a");
    symtab = fopen("avr_symbolTable.txt", "a");
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
    else if(strcmp(token->opcode, ".DEF")==0)
    {

    char temp[30];
    char variable[20];  // Adjust the size based on your requirements
    char value[20];  // Adjust the size based on your requirements
      strcpy(temp,token->operands);
    // Find the position of the '=' character
    char* equalSign = strchr(temp, '=');

    if (equalSign != NULL) {
        // Copy characters before the '=' to the 'name' variable
        strncpy(name, temp, equalSign - temp);
        name[equalSign - temp] = '\0';  // Null-terminate the 'name' string

        // Copy characters after the '=' to the 'code' variable
        strcpy(code, equalSign + 1);
    } else {
        // Handle the case where '=' is not found
        printf("Error: '=' not found in the input string\n");
        return 1;
    }

    // Print the separated strings
    printf("Name: %s\n", name);
    printf("Code: %s\n", code);


    }




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
    int temp = 0;
    struct Token token;

    FILE *finput,*foutput;
    char line[1000];
    finput = fopen("AVR_input.txt", "r");

    while (fgets(line, 1000, finput) != NULL)
    {
        d = tokenise(line, &token);
    }

    fclose(finput);

    foutput = fopen("avr_output.txt", "a");
    fprintf(foutput, "%04x\t%s\t%s\n", locctr, token.label, token.opcode, token.operands);
    fclose(foutput);
    printf("the length of the code is %x\n", d);
    printf("var tab \n");
    for(temp;temp<=var_tab_pointer;temp++)
    {
        printf("%s\t\t%d",vartab[temp].variable,vartab[temp].value);
    }
    return 0;
}



