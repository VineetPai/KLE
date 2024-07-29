#include<stdio.h>
#include<stdlib.h>
struct Token
{
    char label[100];
    char opcode[100];
    char operands[100];
};
void tokenise(char line[1000],struct Token *token)
{
    int result;
    result=sscanf(line,"%s %s %s ",token->label,token->opcode,token->operands);
    if (result == 2)
    {
        char temp[1000],temp1[1000];
        strcpy(temp1,token->opcode);
        strcpy(temp,token->label);
        strcpy(token->opcode, temp);
        strcpy(token->operands,temp1);
        strcpy(token->label, "  ");
    }
    else if (result == 1)
    {
        strcpy(token->opcode, token->label);
        strcpy(token->operands, "  ");
        strcpy(token->label, "");
    }
}
main()
{
    struct Token token;
    FILE *finput,*foutput;
    char line[1000];
    finput=fopen("input.txt","r");
    if(finput == NULL)
    {
        printf("File open error\n");
        exit(0);
    }
    while(fgets(line,1000,finput)!=NULL)
    {
        tokenise(line,&token);
        printf("Label: %s\tOpcode: %s\tOperands: %s\n",token.label,token.opcode,token.operands);
    }
}
