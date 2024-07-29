#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Token
{
    char address[100];
    char label[100];
    char opcode[100];
    char operands[100];
};
struct SymbolTable
{
    char label[100];
    int address;
};
struct SymbolTable sym[100];
void tokenise(char line[1000], struct Token *token)
{
   int res = sscanf(line, "%s %s %s %s", token->address, token->label, token->opcode, token->operands);
    if(res==3)
        strcpy(token->operands,"  ");
    if(res==2)
    {
        strcpy(token->opcode,token->address);
        strcpy(token->operands,token->label);
    }
}
struct Token search_opcode(FILE *optab,struct Token token)
{
    struct Token token2;
    char line2[1000];
    while(fgets(line2,1000,optab)!=NULL)
    {
          tokenise(line2,&token2);
          if(strcmp(token2.opcode,token.opcode)==0)
              return token2;
    }
}
int main()
{
    struct Token token;
    struct Token token1;
    int Line = 1,tar_address;
    FILE *input_pass1, *output_pass2,*optab,*fp2;
    char line[1000];

    input_pass1 = fopen("output.txt", "r");
    output_pass2 = fopen("output_pass2.txt", "w");
    fp2 = fopen("symtab.txt", "r");
    optab=fopen("optab.txt","r");

    while (fscanf(fp2, "%s %x", sym[Line].label, &sym[Line].address) != EOF)
        Line++;

    rewind(fp2);
    fgets(line, 1000, input_pass1);
    while (fgets(line, 1000, input_pass1) != NULL)
    {
        tokenise(line, &token);
        if (strcmp(token.opcode, "WORD") == 0)
        {
            fprintf(output_pass2,"%s\t%s\t%s\t%s\t%06X\n",token.address,token.label,token.opcode,token.operands,atoi(token.operands));
        }
        else if(strcmp(token.opcode, "BYTE")==0)
        {
            int len=strlen(token.operands);
            if(token.operands[0]=='C')
            {
                fprintf(output_pass2,"%s\t%s\t%s\t%s\t\t",token.address,token.label,token.opcode,token.operands);
                for(int j=2;j<len-1;j++){
                    fprintf(output_pass2,"%X",token.operands[j]);
                }
            }
            else if(token.operands[0]=='X')
            {
                fprintf(output_pass2,"%s\t%s\t%s\t%s\t\t",token.address,token.label,token.opcode,token.operands);
                for(int j=2;j<len-1;j++){
                    fprintf(output_pass2,"%c",token.operands[j]);
                }
            }
            fprintf(output_pass2,"\n");
        }
        else
        {
            rewind(optab);
            token1=search_opcode(optab,token);
            for(int i=0;i<Line;i++)
            {
                 if(strcmp(token.operands,sym[i].label)==0)
                  tar_address=sym[i].address;
            }
            fprintf(output_pass2,"%s\t%s\t%s\t%s\t\t%s%x\n",token.address,token.label,token.opcode,token.operands,token1.operands,tar_address);
        }
    }
    fclose(input_pass1);
    fclose(output_pass2);
    fclose(fp2);
    return 0;
}
