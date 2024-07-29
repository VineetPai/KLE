#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token
{
    char label[100];
    char opcode[100];
    char operands[100];
};

void tokenise(char line[1000], struct Token *token)
{
    int result;
    result = sscanf(line, "%s %s %s", token->label, token->opcode, token->operands);
    if (result == 2)
    {
        char temp[1000], temp1[1000];
        strcpy(temp1, token->opcode);
        strcpy(temp, token->label);
        strcpy(token->opcode, temp);
        strcpy(token->operands, temp1);
        strcpy(token->label, "");
    }
    else if (result == 1)
    {
        strcpy(token->opcode, token->label);
        strcpy(token->operands, "");
        strcpy(token->label, "");
    }
}

void display() {

    char str;
    char line[1000];
    FILE *fp1, *fp2, *fp3;

    // 1. Input Table
    printf("\nThe contents of Input Table :\n\n");
    fp1 = fopen("evalpass1.txt", "r");
    if (fp1 == NULL)
    {
    printf("Error opening files.\n");
    exit(1);
    }
    while((fgets(line,1000,fp1))!=NULL)
    {
        printf("%s",line);
    }
    fclose(fp1);

    //2. Output Table
    printf("\n\nThe contents of Output Table :\n\n");
    fp2 = fopen("out.txt", "r");
    if (fp2 == NULL)
    {
    printf("Error opening files.\n");
    exit(1);
    }
    while((fgets(line,1000,fp2))!=NULL)
    {
        printf("%s",line);
    }
    fclose(fp2);

    // 3. Symtable
    printf("\n\nThe contents of Symbol Table :\n\n");
    fp3 = fopen("samp.txt", "r");
    if (fp3 == NULL)
    {
    printf("Error opening files.\n");
    exit(1);
    }
   while((fgets(line,1000,fp3))!=NULL)
    {
        printf("%s",line);
    }
    fclose(fp3);
}

int main()
{
    struct Token token;
    struct Token token2;
    FILE *finput, *foutput,*fp2,*fp3 , *fp4;
    char line[1000],line2[1000],mnemonic[1000];
    int address,start ; // Initialize address in hexadecimal
    // Flag to track the first instruction

    finput = fopen("evalpass1.txt", "r");
    fp2 = fopen("evaloptab.txt", "r");
    fp4=fp2;
    fp3 = fopen("samp.txt", "w");
    if (fp3 == NULL || fp2==NULL)
    {
    printf("Error opening files.\n");
    exit(1);
    }
    if (finput == NULL)
    {
        printf("File open error\n");
        exit(0);
    }

    foutput = fopen("out.txt", "w");

    if (foutput == NULL)
    {
        printf("Output file open error\n");
        exit(0);
    }
    fgets(line, 1000, finput);
    tokenise(line,&token);
    if(strcmp(token.opcode, "START") == 0)
        {

            fprintf(foutput,"\t%s\t%s\t%s\n",token.label, token.opcode, token.operands);
            start=address=atoi(token.operands);
            //"atoi" is a function used to convert a string to an integer. It's a standard
            //library function that takes a string as input and returns the equivalent integer value
        }
    else

        {
            address=0;
        }

while (fgets(line, 1000, finput) != NULL)
    {
        tokenise(line, &token);

       fprintf(foutput,"%d\t%s\t%s\t%s\n",address,token.label, token.opcode, token.operands);

       if (strcmp(token.label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", token.label, address);
        }
     rewind(fp2);
    while(fgets(line2,1000,fp2)!=NULL)
      {
          tokenise(line2,&token2);
          if(strcmp(token2.opcode,token.opcode)==0) // if opcode in input matches the one in optab, increment locctr by 3
          {
              address+=3;
              break;
          }
      }
        if (strcmp(token.opcode, "WORD") == 0) {
            address += 3;
        }
                // RESW -> add 3*operand to locctr
        else if (strcmp(token.opcode, "RESW") == 0) {
            address += (3 * (atoi(token.operands)));                        // convert operand to integer and multiply with 3
        }
                // BYTE -> add 1 to locctr
        else if (strcmp(token.opcode, "BYTE") == 0) {
                if(token.operands[0]=='C')
                {
                    address+=strlen(token.operands)-3;
                }
                else if(token.operands[0]=='X')
                {
                    address+=(strlen(token.operands)-3)/2;
                }


        }
                // RESB -> add operand to locctr
        else if (strcmp(token.opcode, "RESB") == 0) {
            address += atoi(token.operands);
        }



    }
    fclose(finput);
    fclose(foutput);
    fclose(fp2);
    fclose(fp3);
int length=address-start;
printf("%d",length);
    display();


    return 0;
}
