#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char bitmask[4];
char binary_mask[13];

void convert_binary(char bitmask[4])
{
    strcpy(binary_mask, "");
    for (int i = 0; i < strlen(bitmask); i++)
    {
        switch (bitmask[i])
        {
        case '0':
            strcat(binary_mask, "0000");
            break;
        case '1':
            strcat(binary_mask, "0001");
            break;
        case '2':
            strcat(binary_mask, "0010");
            break;
        case '3':
            strcat(binary_mask, "0011");
            break;
        case '4':
            strcat(binary_mask, "0100");
            break;
        case '5':
            strcat(binary_mask, "0101");
            break;
        case '6':
            strcat(binary_mask, "0110");
            break;
        case '7':
            strcat(binary_mask, "0111");
            break;
        case '8':
            strcat(binary_mask, "1000");
            break;
        case '9':
            strcat(binary_mask, "1001");
            break;
        case 'A':
            strcat(binary_mask, "1010");
            break;
        case 'B':
            strcat(binary_mask, "1011");
            break;
        case 'C':
            strcat(binary_mask, "1100");
            break;
        case 'D':
            strcat(binary_mask, "1101");
            break;
        case 'E':
            strcat(binary_mask, "1110");
            break;
        case 'F':
            strcat(binary_mask, "1111");
            break;
        }
    }
}

int main()
{
    int start;
    int address;
    int opcode;
    int final_addr;
    int text_rec_len;

    char rec_type;
    char prog_name[10];
    char rec_addr[6];
    char length[10];
    char col_one[10];
    char obj_code[6];

    FILE *fp = fopen("RL_input.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }
    printf("Enter starting address: ");
    scanf("%x", &start);
    printf("\nLocation\tObject Code");
    while (fscanf(fp, " %c", &rec_type) != EOF)
    {
        if (rec_type == 'H')
        {
            fscanf(fp, "%s %s %s", prog_name, rec_addr, length);
        }
        else if (rec_type == 'T')
        {
            fscanf(fp, "%x %x %s", &address, &text_rec_len, bitmask);
            address += start;

            convert_binary(bitmask);
            int j=0;
            for (int i = 3; i <= text_rec_len; i =i+3)
            {
                fscanf(fp, "%6s", obj_code);

                opcode = (int)strtol(obj_code, NULL, 16) >> 16;
                final_addr = (int)strtol(obj_code, NULL, 16) & 0xFFFF;

                if (binary_mask[j] == '1')
                    final_addr += start;

                printf("\n%x\t\t%x%04x", address, opcode, final_addr);
                address += 3;
                j++;
            }
        }
    }
    fclose(fp);
    return 0;
}




/*H COPY 000000 00107A
T 000000 1E FFC 140033 481039 100036 280030 300015 481061 3C0003 20002A 1C0039 300002
T 002500 12 E00 1C0036 481061 180033 4C0000 801000 601003
E 000000
*/
