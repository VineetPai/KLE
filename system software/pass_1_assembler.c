#include<stdio.h>
#include<stdlib.h>

struct Token
{
    char label[100];
    char opcode[100];
    char operands[100];
};
void tokenize(char line[1000],struct Token *token)
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
        strcpy(token->label, "  ");
    }
}
main()
{   int h;
    int multiline_comment;
    int line_length;
    printf("enter ADDRESS\n");
    scanf("%x",&h);
    struct Token token;
    FILE *finput,*foutput;
    char line[1000];
    finput=fopen("input_alp.txt","r");
    foutput=fopen("output.txt","w");
    if(finput == NULL)
    {
        printf("File open error\n");
        exit(0);
    }
    int f=0;
    int g=0;
    int k;
    int z = 0x3;
    int size;
    while(fgets(line,1000,finput)!=NULL)
    {
        if(line[0]==';')
    {
        //printf("%d\n",strlen(line));
        //printf("%c\n",line[strlen(line)-2]);
        continue;
    }
    if(line[0]=='/' && line[1]=='*')
    {
        multiline_comment=1;
        //printf("%c\n",line[strlen(line)-2]);
    }
    line_length = strlen(line);

    if(line[strlen(line)-2]=='/' && line[strlen(line)-3]=='*')
    {
        multiline_comment=0;
        continue;
    }
     if(multiline_comment==1)
    {
        continue;
    }


        if(f<=1)
        { if(g==0)
           {f++;}
        }
        else{h=h+z;}
        tokenize(line,&token);
        if(strcmp(token.opcode,"BYTE")==0)
        {
            size = strlen(token.operands);
            size = size -3;
            if(size!=3)
            {
                z=size;
            }
        }
        if(strcmp(token.label,"BUFFER")==0 && strcmp(token.opcode,"RESB")==0)
        {
            printf("%x\n",(int)token.operands);
        }
        printf("%x %s\t %s\t %s\n",h,token.label,token.opcode,token.operands);
        fprintf(foutput,"%x  %s\t %s\t %s\n",h,token.label,token.opcode,token.operands);
    }
}

