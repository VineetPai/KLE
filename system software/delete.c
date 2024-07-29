#include<stdio.h>
#include<string.h>

int main()
{
    char *str = "12345";
    int a = strtol(str,NULL, 10);

    printf("%d",a);
}
