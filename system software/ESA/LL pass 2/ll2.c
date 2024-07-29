#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct exttable
{
  char cextsym[20], extsym[20];
  int address,length;
}estab[20];

struct objectcode
{
 unsigned char code[15];
 int add;
}obcode[500];

void main()
{
 char temp[10];
 FILE *fp1,*fp2,*fp3;
 int i,j,x,y,pstart,exeloc,start,textloc,loc,textlen,length,location,st,s;
 int n=0,num=0,inc=0,count=0,record=0,mloc[30],mlen[30];
 signed long int newadd;
 char operation,lbl[10],input[10],label[50][10],opr[30],ch,*add1,address[10];
 fp1=fopen("input.txt","r");
 fp2=fopen("ESTAB.txt","r");
 fp3=fopen("OUTPUT.txt","w");
 while(!feof(fp2))
 {
fscanf(fp2,"%s %s %x %x", estab[num].cextsym, estab[num].extsym, &estab[num].address,&estab[num].length);
num++;
 }
 exeloc=estab[0].address;
 loc=exeloc;
 start=loc;
 st=start;
 while(!feof(fp1))
 {
fscanf(fp1,"%s",input);
if(strcmp(input,"H")==0)
{
fscanf(fp1,"%s",input);
for(i=0;i<num;i++)
if(strcmp(input,estab[i].cextsym)==0)
{
pstart=estab[i].address;
break;
}
while(strcmp(input,"T")!=0)
fscanf(fp1,"%s",input);
}
do
{
if(strcmp(input,"T")==0)
{
fscanf(fp1,"%x",&textloc);
textloc=textloc+pstart;
for(i=0;i<(textloc-loc);i++)
{
strcpy(obcode[inc].code,"..");
obcode[inc++].add=start++;
}
fscanf(fp1,"%x",&textlen);
loc=textloc+textlen;
}
else if(strcmp(input,"M")==0)
{
fscanf(fp1,"%x",&mloc[record]);
mloc[record]=mloc[record]+pstart;
fscanf(fp1,"%x",&mlen[record]);
fscanf(fp1,"%s",label[record++]);
}
else
{
length=strlen(input);
x=0;
for(i=0;i<length;i++)
{
obcode[inc].code[x++]=input[i];
if(x>1)
{
obcode[inc++].add=start++;
x=0;
}
}
}
fscanf(fp1,"%s",input);
}while(strcmp(input,"E")!=0);
if(strcmp(input,"E")==0)
fscanf(fp1,"%s",input);
 }
for(n=0;n<record;n++)
{
operation=label[n][0];
length=strlen(label[n]);
for(i=1;i<length;i++)
{
lbl[i-1]=label[n][i];
}
lbl[length-1]='\0';
length=0;
strcpy(address,"\0");
location=mloc[n]-exeloc;
loc=location;
count=0;
while(length<mlen[n])
{
strcat(address,obcode[location++].code);
count++;
length+=2;
}
for(i=0;i<num;i++)
{
if(strcmp(lbl,estab[i].cextsym)==0)
break;
if(strcmp(lbl,estab[i].extsym)==0)
break;
}
switch(operation)
{
case '+':
newadd=strtol(address,&add1,16)+(long int)estab[i].address;
break;
case '-':
newadd=strtol(address,&add1,16)-(long int)estab[i].address;
break;
}
  ltoa(newadd,address,16);
  x=0; y=0;
  while(count>0)
  {
   obcode[loc].code[x++]=address[y++];
   if(x>1)
   {
x=0; loc++;
count--;
   }
  }
  }
 count=0;
 n=0;
 s=st-16;
 fprintf(fp3,"%x\t",s);
 for(i=1;i<=16;i++)
 {
  fprintf(fp3,"xx");
  if(i==4||i==8||i==12)
  {
   fprintf(fp3,"\t");
  }
 }
 fprintf(fp3,"\n\n%x\t",obcode[0].add);
 for(i=0;i<inc;i++)
 {
fprintf(fp3,"%s",obcode[i].code);
n++;
if(n>3)
{
fprintf(fp3,"\t");
n=0;
        count++;
}
if(count>3)
{
fprintf(fp3,"\n\n%x\t",obcode[i+1].add);
count=0;
}
  }
fclose(fp1);
fclose(fp2);
fclose(fp3);
 printf("\n\t*** PASS TWO OF A LINKING LOADER ***\n");
 printf("\nThe contents of the output file :");
 printf("\n---------------------------------------------------------------");
 printf("\nAddress\t\t\t\tContents");
 printf("\n---------------------------------------------------------------\n");
 fp3=fopen("OUTPUT2.txt","r");
 ch=fgetc(fp3);
 while(ch!=EOF)
 {
  printf("%c",ch);
  ch=fgetc(fp3);
 }
 fclose(fp3);
}


/*
H PROGA 000000 000063
D LISTA 000054 ENDA 000064
R LISTB ENDB LISTC ENDC
T 000020 0A 03201D 77100004 050014
T 000054 0F 100014 000008 004051 000004 100000
M 000024 05 +LISTA
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
END


PROGA ** 2000 63
** LISTA 2054
** ENDA 2064
PROGB ** 2063 7f
** LISTB 20c3
** ENDB 20d3
PROGC ** 20e2 51
** LISTC 2112
** ENDC 2124


3ff0 xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx

4000 ........ ........ ........ ........

4010 ........ ........ ........ ........

4020 03201D77 10405805 0014.... ........

4030 ........ ........ ........ ........

4040 ........ ........ ........ ........

4050 ........ 10412600 00080040 51000004

4060 10006f.. ........ ........ ........

4070 ........ ........ ........ ........

4080 ........ ........ ........ ........

4090 ........ ........ ..031040 54772027

40a0 05fbfac ........ ........ ........

40b0 ........ ........ ........ ........

40c0 ........ ........ ........ ........

40d0 ......10 00be0000 08004051 00000410

40e0 006f.... ........ ........ ........

40f0 ........ ........ ....0310 00007710

4100 40c705fb fac.... ........ ........

4110 ........ ........ ........ ........

4120 ........ 1000be00 00080040 51000004

4130 10006f
*/
