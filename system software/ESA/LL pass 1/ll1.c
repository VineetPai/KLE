
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int estab_cnt = -1;
int rec_cnt = -1;

struct ext_sym_table //Structure Declaration for storing each instructions from SIC Program text
{
    char cnt_name[30], sym_name[30], sym_addrs[30], cnt_len[30];
}ESTAB[100];

struct red_records
{
    char record[150];
}REC[100];

void initialize()
{
    for(int i=0;i<100;i++)
    {
        strcpy(ESTAB[i].cnt_len,"");
        strcpy(ESTAB[i].cnt_name,"");
        strcpy(ESTAB[i].sym_addrs,"");
        strcpy(ESTAB[i].sym_name,"");
        strcpy(REC[i].record,"");
    }
}
void read_record()
{
    char buff[150];
    FILE *f1 = fopen("object_program.txt","r");
    if(f1 == NULL)
    {
        printf("Sorry the file cannot be opened!!");
        exit(0);
    }
    while(fgets(buff,100,f1))
    {
        if(buff[0] == '\n')
            continue;
        buff[strlen(buff)-1] = '\0';
        rec_cnt ++;
        strcpy(REC[rec_cnt].record,buff);
    }
    fclose(f1);
}

int dupe_control(char cnt_name[30])
{
    int flag = 0;
    for(int i=0;i<=estab_cnt;i++)
        if(strcmp(ESTAB[i].cnt_name,cnt_name) == 0)
            return 1;
    return flag;
}

int dupe_symbol(char symbol[30])
{
    int flag = 0;
    for(int i=0;i<=estab_cnt;i++)
        if(strcmp(ESTAB[i].sym_name,symbol) == 0)
            return 1;
    return flag;
}

void process_rec()
{
    int prog_addrs, csaddr, cslth, sym_addr;
    char *token, sym_name[30], cnt_name[30], sym_addrs[30], cnt_len[30],garbage[30];
    printf("Enter Program Address:");
    scanf("%x",&prog_addrs);
    csaddr = prog_addrs;
    for(int i=0;i<=rec_cnt;i++)
    {
        if(REC[i].record[0] == 'H')
        {
            token = strtok(&REC[i].record[2]," ");
            strcpy(cnt_name,token);
            token = strtok(NULL, " ");
            strcpy(garbage,token);
            token = strtok(NULL, " ");
            strcpy(cnt_len,token);
            if(dupe_control(cnt_name) == 1)
                printf("\n!!!  Control Section Name: %s is repeated  !!!\n",cnt_name);
            else
            {
                estab_cnt ++;
                cslth = strtol(cnt_len,NULL,16);
                strcpy(ESTAB[estab_cnt].cnt_name,cnt_name);
                strcpy(ESTAB[estab_cnt].cnt_len,cnt_len);
            }
        }
        else if(REC[i].record[0] == 'D')
        {
            token = strtok(&REC[i].record[2]," ");
            while(token != NULL)
            {
                strcpy(sym_name,token);
                token = strtok(NULL, " ");
                strcpy(sym_addrs,token);
                token = strtok(NULL," ");
                if(dupe_symbol(sym_name) == 1)
                    printf("\n!!!  Symbol Name: %s is repeated  !!!\n", sym_name);
                else
                {
                    estab_cnt ++;
                    sym_addr = strtol(sym_addrs,NULL,16);
                    sym_addr = sym_addr + csaddr;
                    sprintf(sym_addrs,"%04x",sym_addr);
                    strcpy(ESTAB[estab_cnt].sym_name,sym_name);
                    strcpy(ESTAB[estab_cnt].sym_addrs,sym_addrs);
                }
            }
        }
        else if(REC[i].record[0] == 'E')
            csaddr = csaddr + cslth;
    }
}

void display_rec()
{
    for(int i=0;i<=rec_cnt;i++)
        printf("%s\n",REC[i].record);
}

void display_estab()
{
    printf("\nCNTRL NAME\tSYMBOL NAME\tSYMBOL ADDRS\tCNTRL LNGTH\n---\t\t---\t\t---\t\t---");
    for(int i=0;i<=estab_cnt;i++)
        printf("\n%s\t\t%s\t\t%s\t\t%s",ESTAB[i].cnt_name,ESTAB[i].sym_name,ESTAB[i].sym_addrs,ESTAB[i].cnt_len);
    printf("\n");
}

void main()
{
    initialize();
    read_record();
    //display_rec();
    printf("Input record has been read\n");
    process_rec();
    display_estab();
}
/*
H PROGA 000000 000063
D LISTA 000054
R LISTB ENDB LISTC ENDC
T 000020 0A 03201D 77100004 050014
T 000054 0F 100014 000008 004051 000004 100000
M 000024 05 +LISTB
M 000054 06 +LISTC
M 000060 06 +LISTB
M 000060 06 -LISTA
E 000020

H PROGB 000000 00007F
D LISTB 000060 ENDB 000070
R LISTA LISTC ENDY
T 000036 0B 03100000 772027 05100000
T 000070 0F 100000 000008 004051 000004 100060
M 000037 05 +LISTA
M 00003E 05 -LISTA
M 000070 06 -LISTA
M 000070 06 +LISTC
M 00007C 06 +PROGB
M 00007C 06 -LISTA
E 000000

H PROGC 000000 0000051
D LISTC 000030 ENDC 000042
R LISTA LISTB ENDB
T 000018 0C 03100000 77100004 05100000
T 000042 0F 100030 000008 004051 000004 100000
M 00001D 05 +LISTB
M 000021 05 -LISTA
M 000042 06 -LISTA
M 000042 06 +PROGC
M 00004E 06 +LISTB
M 00004E 06 -LISTA
E
END*/
