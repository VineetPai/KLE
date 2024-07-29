#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char variable[30];
    int value;
}var_tab;

var_tab vartab[100];
int main()
{   int Register[32]={1,2,3,4,5,6,67};
    int var_tab_pointer = 0;
    int i=0,j=0;
        int R,RHS_R_val;
        char temp[100];
        char lhs[30];
        char rhs[30];
        strcpy(temp,"vineet=R01");
        while(temp[i]!='=')
        {
            lhs[i]=temp[i];
            printf("%c\n",lhs[i]);
            i++;
        }
        i++;
        printf("------------");
        while(temp[i]!="\n")
        {
            rhs[i]=temp[i];
            printf("%c\n",rhs[i]);
            i++;
        }
        if(rhs[0]=='R')
        {
            char r_num[5];
            while(rhs[j]!="\n")
            {
                r_num[j]=rhs[j];
                j++;
            }
            R = atoi(r_num);
            RHS_R_val = Register[R];
            strcpy(vartab[var_tab_pointer].variable,lhs);
            vartab[var_tab_pointer++].value = RHS_R_val;
        }
        return 0;

}
