#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct exttable
{
    char csect[20], sname[20];
    int padd, plen;
} estab[20];

struct objectcode
{
    unsigned char code[15];
    int add;
} obcode[500];

int main()
{
    FILE *fp1, *fp2, *fp3;
    int i, x, y, pstart, exeloc, start, textloc, loc, textlen, length, location, st, s;
    int n = 0, num = 0, inc = 0, count = 0, record = 0, mloc[30], mlen[30];
    signed long int newadd;
    char operation, lbl[10], input[10], label[50][10], ch, *add1, address[20];

    fp1 = fopen("L2IN.txt", "r");
    fp2 = fopen("L1OUT.txt", "r");
    fp3 = fopen("L2OUT.txt", "w");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
    perror("Error opening file");
    return 1; // Or exit the program with an error code
    }

    while (!feof(fp2))
    {
        fscanf(fp2, "%s %s %x %x", estab[num].csect, estab[num].sname, &estab[num].padd,
               &estab[num].plen);


        num++;
    }
    exeloc = estab[0].padd;
    loc = exeloc;
    start = loc;
    st = start;

    while (!feof(fp1))
    {
        fscanf(fp1, "%s", input);
        printf("%s\n",input);
    }


    return 0;
}
