#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct operand
{
    char reg[8];
    char constant[8];
};

char* convertToBinary(long num) {
    char* binaryString = (char*)malloc(9);
    if (!binaryString) {
        exit(EXIT_FAILURE);
    }

    binaryString[8] = '\0';

    for (int i = 7; i >= 0; i--) {
        binaryString[7 - i] = ((num >> i) & 1) + '0';
    }

    return binaryString;
}

struct operand separator(char operand[])
{
    struct operand op;
    char reg[3];
    char constant[5];
    int i=1,p=0;
    for(i=1;i<strlen(operand);i++)
    {
        if(operand[i]!=',')
            reg[i-1]=operand[i];
        else
        {
            reg[i]='\0';
            break;
        }
    }
    i++;
    if(operand[i]=='r'||operand[i]=='R')
        i++;
    else if(operand[i+1]=='x'||operand[i+1]=='X')
        i=i+2;
    while(i<strlen(operand))
    {
        constant[p]=operand[i];
        i++;
        p++;
    }
    constant[p]='\0';

    long int d=strtol(reg, NULL, 10);
    long int k=strtol(constant, NULL, 10);
    strcpy(op.reg,convertToBinary(d));
    strcpy(op.constant,convertToBinary(k));
    return op;
}

struct operand symbolConst(char operand[])
{
    struct operand op;
    char reg[3];
    char constant[5];
    int i=1,p=0;
    for(i=1;i<strlen(operand);i++)
    {
        if(operand[i]!=',')
            reg[i-1]=operand[i];
        else
        {
            reg[i]='\0';
            break;
        }
    }
    i++;
    if(operand[i+1]=='x'||operand[i+1]=='X')
        i=i+2;
    while(i<strlen(operand))
    {
        constant[p]=operand[i];
        i++;
        p++;
    }
    constant[p]='\0';
    long int k=strtol(constant, NULL, 10);
    strcpy(op.reg,reg);
    strcpy(op.constant,convertToBinary(k));
    return op;
};

char* getIO(char op[])
{
    if(!strcmp(op,"UDR"))
        return "00001100";
    else if(!strcmp(op,"PIND"))
        return "00010000";
    else if(!strcmp(op,"DDRD"))
        return "00010001";
    else if(!strcmp(op,"PORTD"))
        return "00010010";
    else if(!strcmp(op,"PINC"))
        return "00010011";
    else if(!strcmp(op,"DDRC"))
        return "00010100";
    else if(!strcmp(op,"PORTC"))
        return "00010101";
    else if(!strcmp(op,"PINB"))
        return "00010110";
    else if(!strcmp(op,"DDRB"))
        return "00010111";
    else if(!strcmp(op,"PORTB"))
        return "00011000";
    else if(!strcmp(op,"PINA"))
        return "00011001";
    else if(!strcmp(op,"DDRA"))
        return "00011010";
    else if(!strcmp(op,"PORTA"))
        return "00011011";
    else if(!strcmp(op,"SPL"))
        return "00111101";
    else if(!strcmp(op,"SPH"))
        return "00111110";
    else if(!strcmp(op,"SREG"))
        return "00111111";
    else
        return "00000000";

}

unsigned long objectCode(char opcode[], char operand[]) {
    char objCode[17], line[256],addr_str[12], objCode32[33];
    unsigned long hex;
    struct operand op;
    int addr;
    int PC=9, k=0;
    char hexString[4];

    if (!strcmp(opcode, "CLC")) {
        strcpy(objCode, "1001010010001000");
    }
    else if(!strcmp(opcode, "SEC")) {
        strcpy(objCode, "1001010000001000");
    }
    else if(!strcmp(opcode, "CLN")) {
        strcpy(objCode, "1001010010101000");
    }
    else if(!strcmp(opcode, "SEN")) {
        strcpy(objCode, "1001010000101000");
    }
    else if(!strcmp(opcode, "CLZ")) {
        strcpy(objCode, "1001010010011000");
    }
    else if(!strcmp(opcode, "SEZ")) {
        strcpy(objCode, "1001010000011000");
    }
    else if(!strcmp(opcode, "RET")) {
        strcpy(objCode, "1001010100001000");
    }
    else if(!strcmp(opcode, "RETI")) {
        strcpy(objCode, "1001010100011000");
    }
    else if(!strcmp(opcode, "NOP")) {
        strcpy(objCode, "0000000000000000");
    }
    else if(!strcmp(opcode, "LDI")) {
        op=separator(operand);
        strcpy(objCode, "1110kkkkddddkkkk");
        printf("%s\n",op.constant);
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "LDI")) {
        op=separator(operand);
        strcpy(objCode, "1110kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "CPI")) {
        op=separator(operand);
        strcpy(objCode, "0011kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "ANDI")) {
        op=separator(operand);
        strcpy(objCode, "0111kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "ORI")) {
        op=separator(operand);
        strcpy(objCode, "0110kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "SUBI")) {
        op=separator(operand);
        strcpy(objCode, "0101kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "PUSH") || !strcmp(opcode, "POP") || !strcmp(opcode, "LSR") || !strcmp(opcode, "ROR") || !strcmp(opcode, "INC") || !strcmp(opcode, "DEC")|| !strcmp(opcode, "SWAP")){

        if(!strcmp(opcode, "PUSH"))
            strcpy(objCode, "1001001ddddd1111");
        else if(!strcmp(opcode, "POP"))
            strcpy(objCode, "1001000ddddd1111");
        else if(!strcmp(opcode, "LSR"))
            strcpy(objCode, "1001010ddddd0110");
        else if(!strcmp(opcode, "ROR"))
            strcpy(objCode, "1001010ddddd0111");
        else if(!strcmp(opcode, "INC"))
            strcpy(objCode, "1001010ddddd0011");
        else if(!strcmp(opcode, "DEC"))
            strcpy(objCode, "1001010ddddd1010");
        else if(!strcmp(opcode, "SWAP"))
            strcpy(objCode, "1001010ddddd0010");

        op=separator(operand);
        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "LSL") || !strcmp(opcode, "ROL") || !strcmp(opcode, "CLR")){
        if(!strcmp(opcode, "LSL"))
            strcpy(objCode, "00001100dddddddd");
        else if(!strcmp(opcode, "ROL"))
            strcpy(objCode, "00011100dddddddd");
        else if(!strcmp(opcode, "CLR"))
            strcpy(objCode, "00100100dddddddd");

        op=separator(operand);
        for(int x=15;x>7;x--)
            objCode[x]=op.reg[x-8];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "LSL") || !strcmp(opcode, "ROL") || !strcmp(opcode, "CLR")){
        if(!strcmp(opcode, "LSL"))
            strcpy(objCode, "00001100dddddddd");
        else if(!strcmp(opcode, "ROL"))
            strcpy(objCode, "00011100dddddddd");
        else if(!strcmp(opcode, "CLR"))
            strcpy(objCode, "00100100dddddddd");

        op=separator(operand);
        for(int x=15;x>7;x--)
            objCode[x]=op.reg[x-8];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "MOV") || !strcmp(opcode, "ADD") || !strcmp(opcode, "ADC") || !strcmp(opcode, "SUB") || !strcmp(opcode, "AND") || !strcmp(opcode, "OR")|| !strcmp(opcode, "EOR")||!strcmp(opcode, "CP")||!strcmp(opcode, "CPC")){

        if(!strcmp(opcode, "MOV"))
            strcpy(objCode, "001011rdddddrrrr");
        else if(!strcmp(opcode, "ADD"))
            strcpy(objCode, "000011rdddddrrrr");
        else if(!strcmp(opcode, "ADC"))
            strcpy(objCode, "000111rdddddrrrr");
        else if(!strcmp(opcode, "SUB"))
            strcpy(objCode, "000110rdddddrrrr");
        else if(!strcmp(opcode, "AND"))
            strcpy(objCode, "001000rdddddrrrr");
        else if(!strcmp(opcode, "OR"))
            strcpy(objCode, "001010rdddddrrrr");
        else if(!strcmp(opcode, "EOR"))
            strcpy(objCode, "001001rdddddrrrr");
        else if(!strcmp(opcode, "CP"))
            strcpy(objCode, "000101rdddddrrrr");
        else if(!strcmp(opcode, "CPC"))
            strcpy(objCode, "000001rdddddrrrr");
        op=separator(operand);
        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        for(int x=15;x>11;x--)
            objCode[x]=op.constant[x-8];
        objCode[6]=op.constant[3];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "SBRS") || !strcmp(opcode, "SBRC")){
        if(!strcmp(opcode, "SBRS"))
            strcpy(objCode, "1111111rrrrr0bbb");
        else if(!strcmp(opcode, "SBRC"))
            strcpy(objCode, "1111110rrrrr0bbb");

        op=separator(operand);
        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        for(int x=15;x>12;x--)
            objCode[x]=op.constant[x-8];
        objCode[16]='\0';

    }
    else if(!strcmp(opcode, "BREQ") || !strcmp(opcode, "BRNE") || !strcmp(opcode, "BRCS") || !strcmp(opcode, "BRCC")){

        if(!strcmp(opcode, "BREQ"))
            strcpy(objCode, "111100kkkkkkk001");
        else if(!strcmp(opcode, "BRNE"))
            strcpy(objCode, "111101kkkkkkk001");
        else if(!strcmp(opcode, "BRCS"))
            strcpy(objCode, "111100kkkkkkk000");
        else if(!strcmp(opcode, "BRCC"))
            strcpy(objCode, "111101kkkkkkk000");

        FILE* symtab = fopen("symbolTable.txt", "r");
        char* str;
        while (fgets(line, 256, symtab) != NULL)
        {
            sscanf(line,"%s %s",str,addr_str);
            if(strcmp(str,operand)==0)
            {
                addr = strtoul(addr_str, NULL, 16);
                k = addr - PC - 1;             // negative decimal integer
                strcpy(op.constant , convertToBinary(k));  //binary string
            }
        }
        fclose(symtab);
        for(int x=12;x>4;x--)
            objCode[x]=op.constant[x-5];
        objCode[16]='\0';
    }

    else if(!strcmp(opcode, "IN") ){
        strcpy(objCode, "10110aadddddaaaa");
        int i,p=0;
        for(i=1;i<strlen(operand);i++)
        {
            if(operand[i]!=',')
                op.reg[i-1]=operand[i];
            else
            {
                op.reg[i-1]='\0';
                break;
            }
        }
        i++;
        while(i<strlen(operand))
        {
            op.constant[p]=operand[i];
            i++;
            p++;
        }
        op.constant[p]='\0';
        strcpy(op.constant,getIO(op.constant));
        long int d=strtol(op.reg, NULL, 10);
        strcpy(op.reg,convertToBinary(d));

        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        for(int x=15;x>11;x--)
            objCode[x]=op.constant[x-8];
        objCode[6]=op.constant[3];
        objCode[5]=op.constant[2];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "OUT") ){
        strcpy(objCode, "10111aadddddaaaa");
        int i,p=0;
        for(i=0;i<strlen(operand);i++)
        {
            if(operand[i]!=',')
                op.reg[i]=operand[i];
            else
            {
                op.reg[i]='\0';
                break;
            }
        }
        i+=2;
        while(i<strlen(operand))
        {
            op.constant[p]=operand[i];
            i++;
            p++;
        }
        op.constant[p]='\0';
        long int d=strtol(op.constant, NULL, 10);
        strcpy(op.constant,convertToBinary(d));
        strcpy(op.reg,getIO(op.reg));
        for(int x=11;x>6;x--)
            objCode[x]=op.constant[x-4];
        for(int x=15;x>11;x--)
            objCode[x]=op.reg[x-8];
        objCode[6]=op.reg[3];
        objCode[5]=op.reg[2];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "SBI") || !strcmp(opcode, "CBI")){
        if(!strcmp(opcode, "SBI"))
            strcpy(objCode, "10011010AAAAABBB");
        else
            strcpy(objCode, "10011000AAAAABBB");


        int i,p=0;
        for(i=0;i<strlen(operand);i++)
        {
            if(operand[i]!=',')
                op.reg[i]=operand[i];
            else
            {
                op.reg[i]='\0';
                break;
            }
        }
        i++;
        while(i<strlen(operand))
        {
            op.constant[p]=operand[i];
            i++;
            p++;
        }
        op.constant[p]='\0';
        long int d=strtol(op.constant, NULL, 10);
        strcpy(op.constant,convertToBinary(d));
        strcpy(op.reg,getIO(op.reg));
        for(int x=12;x>7;x--)
            objCode[x]=op.reg[x-5];
        for(int x=15;x>12;x--)
            objCode[x]=op.constant[x-8];
    }
    else if(!strcmp(opcode, "JMP") || !strcmp(opcode, "CALL"))
    {
        if(!strcmp(opcode, "JMP"))
            strcpy(objCode32, "1001010kkkkk110kkkkkkkkkkkkkkkkk");
        else
            strcpy(objCode32, "1001010kkkkk111kkkkkkkkkkkkkkkkk");

        FILE* symtab = fopen("symbolTable.txt", "r");
        if (symtab == NULL) {
            perror("Error opening file");
            return 1;
        }
        char str[15];
        char temp[24];
        strcpy(temp,"00000000000000000000000");
        while (fgets(line, 256, symtab) != NULL)
        {
            sscanf(line,"%s %s",str,addr_str);
            if(strcmp(str,operand)==0)
            {
                //printf("here");
                addr = strtoul(addr_str, NULL, 16);
                k = addr;
                strcpy(temp , convertToBinary(k));
            }

        }
        for(int x=31;x>24;x--)
            objCode32[x]=temp[x-24];
        for(int x=24;x>14;x--)
            objCode32[x]='0';
        for(int x=7;x<12;x++)
            objCode32[x]='0';
        objCode[33]='\0';
        hex = strtoul(objCode32, NULL, 2);
        return hex;
    }
    printf("Binary value--%s\n", objCode);
    hex = strtoul(objCode, NULL, 2);
    return hex;
}

int main() {

    unsigned long objCode = objectCode("OUT", "DDRB,R11");
    printf("0x%lX", objCode);
    return 0;
}








/*
000000		LDI 	R25,0X05
000001 		LDI 	R26,0X01
000002		LDI 	R27,0X02
000003		LDI	    R16,0X200
000005		DEC 	R25
000006	BACK:   LDI	R18,20
000007 		CP 	R16,R18
000008 		BRCS 	DOWN
000009 		MOV 	R16,R18
00000a 	DOWN:   DEC 	R25
00000b 		BRNE 	BACK
*/
























/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct operand
{
    char* reg;
    char* constant;
};

char* convertToBinary(long num) {
    char* binaryString = (char*)malloc(9);
    if (!binaryString) {
        exit(EXIT_FAILURE);
    }

    binaryString[8] = '\0';

    for (int i = 7; i >= 0; i--) {
        binaryString[7 - i] = ((num >> i) & 1) + '0';
    }

    return binaryString;
}

struct operand separator(char operand[])
{
    struct operand op;
    char reg[3];
    char constant[5];
    int i=1,p=0;
    for(i=1;i<strlen(operand);i++)
    {
        if(operand[i]!=',')
            reg[i-1]=operand[i];
        else
        {
            reg[i]='\0';
            break;
        }
    }
    i++;
    if(operand[i]=='r'||operand[i]=='R')
        i++;
    while(i<strlen(operand))
    {
        constant[p]=operand[i];
        i++;
        p++;
    }
    constant[p]='\0';

    long int d=strtol(reg, NULL, 10);
    long int k=strtol(constant, NULL, 10);
    op.reg=convertToBinary(d);
    op.constant=convertToBinary(k);
    return op;
}

struct operand symbolConst(char operand[])
{
    struct operand op;
    char reg[3];
    char constant[5];
    int i=1,p=0;
    for(i=1;i<strlen(operand);i++)
    {
        if(operand[i]!=',')
            reg[i-1]=operand[i];
        else
        {
            reg[i]='\0';
            break;
        }
    }
    i++;

    while(i<strlen(operand))
    {
        constant[p]=operand[i];
        i++;
        p++;
    }
    constant[p]='\0';

    long int k=strtol(constant, NULL, 10);
    op.reg=reg;
    op.constant=convertToBinary(k);
    return op;
};

char* getIO(char op[])
{
    if(!strcmp(op,"UDR"))
        return "00001100";
    else if(!strcmp(op,"PIND"))
        return "00010000";
    else if(!strcmp(op,"DDRD"))
        return "00010001";
    else if(!strcmp(op,"PORTD"))
        return "00010010";
    else if(!strcmp(op,"PINC"))
        return "00010011";
    else if(!strcmp(op,"DDRC"))
        return "00010100";
    else if(!strcmp(op,"PORTC"))
        return "00010101";
    else if(!strcmp(op,"PINB"))
        return "00010110";
    else if(!strcmp(op,"DDRB"))
        return "00010111";
    else if(!strcmp(op,"PORTB"))
        return "00011000";
    else if(!strcmp(op,"PINA"))
        return "00011001";
    else if(!strcmp(op,"DDRA"))
        return "00011010";
    else if(!strcmp(op,"PORTA"))
        return "00011011";
    else if(!strcmp(op,"SPL"))
        return "00111101";
    else if(!strcmp(op,"SPH"))
        return "00111110";
    else if(!strcmp(op,"SREG"))
        return "00111111";
    else
        return "00000000";

}

unsigned long objectCode(char opcode[], char operand[]) {
    char objCode[17];
    unsigned long hex;
    struct operand op;

    if (!strcmp(opcode, "CLC")) {
        strcpy(objCode, "1001010010001000");
    }
    else if(!strcmp(opcode, "SEC")) {
        strcpy(objCode, "1001010000001000");
    }
    else if(!strcmp(opcode, "CLN")) {
        strcpy(objCode, "1001010010101000");
    }
    else if(!strcmp(opcode, "SEN")) {
        strcpy(objCode, "1001010000101000");
    }
    else if(!strcmp(opcode, "CLZ")) {
        strcpy(objCode, "1001010010011000");
    }
    else if(!strcmp(opcode, "SEZ")) {
        strcpy(objCode, "1001010000011000");
    }
    else if(!strcmp(opcode, "RET")) {
        strcpy(objCode, "1001010100001000");
    }
    else if(!strcmp(opcode, "RETI")) {
        strcpy(objCode, "1001010100011000");
    }
    else if(!strcmp(opcode, "NOP")) {
        strcpy(objCode, "0000000000000000");
    }
    else if(!strcmp(opcode, "LDI")) {
        op=separator(operand);
        strcpy(objCode, "1110kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "LDI")) {
        op=separator(operand);
        strcpy(objCode, "1110kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "CPI")) {
        op=separator(operand);
        strcpy(objCode, "0011kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "ANDI")) {
        op=separator(operand);
        strcpy(objCode, "0111kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "ORI")) {
        op=separator(operand);
        strcpy(objCode, "0110kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "SUBI")) {
        op=separator(operand);
        strcpy(objCode, "0101kkkkddddkkkk");
        for(int x=0;x<4;x++)
            objCode[x+4]=op.constant[x];
        for(int x=4;x<8;x++)
            objCode[x+8]=op.constant[x];
        for(int x=11;x>7;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "PUSH") || !strcmp(opcode, "POP") || !strcmp(opcode, "LSR") || !strcmp(opcode, "ROR") || !strcmp(opcode, "INC") || !strcmp(opcode, "DEC")|| !strcmp(opcode, "SWAP")){

        if(!strcmp(opcode, "PUSH"))
            strcpy(objCode, "1001001ddddd1111");
        else if(!strcmp(opcode, "POP"))
            strcpy(objCode, "1001000ddddd1111");
        else if(!strcmp(opcode, "LSR"))
            strcpy(objCode, "1001010ddddd0110");
        else if(!strcmp(opcode, "ROR"))
            strcpy(objCode, "1001010ddddd0111");
        else if(!strcmp(opcode, "INC"))
            strcpy(objCode, "1001010ddddd0011");
        else if(!strcmp(opcode, "DEC"))
            strcpy(objCode, "1001010ddddd1010");
        else if(!strcmp(opcode, "SWAP"))
            strcpy(objCode, "1001010ddddd0010");

        op=separator(operand);
        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "LSL") || !strcmp(opcode, "ROL") || !strcmp(opcode, "CLR")){
        if(!strcmp(opcode, "LSL"))
            strcpy(objCode, "00001100dddddddd");
        else if(!strcmp(opcode, "ROL"))
            strcpy(objCode, "00011100dddddddd");
        else if(!strcmp(opcode, "CLR"))
            strcpy(objCode, "00100100dddddddd");

        op=separator(operand);
        for(int x=15;x>7;x--)
            objCode[x]=op.reg[x-8];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "LSL") || !strcmp(opcode, "ROL") || !strcmp(opcode, "CLR")){
        if(!strcmp(opcode, "LSL"))
            strcpy(objCode, "00001100dddddddd");
        else if(!strcmp(opcode, "ROL"))
            strcpy(objCode, "00011100dddddddd");
        else if(!strcmp(opcode, "CLR"))
            strcpy(objCode, "00100100dddddddd");

        op=separator(operand);
        for(int x=15;x>7;x--)
            objCode[x]=op.reg[x-8];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "MOV") || !strcmp(opcode, "ADD") || !strcmp(opcode, "ADC") || !strcmp(opcode, "SUB") || !strcmp(opcode, "AND") || !strcmp(opcode, "OR")|| !strcmp(opcode, "EOR")||!strcmp(opcode, "CP")||!strcmp(opcode, "CPC")){

        if(!strcmp(opcode, "MOV"))
            strcpy(objCode, "001011rdddddrrrr");
        else if(!strcmp(opcode, "ADD"))
            strcpy(objCode, "000011rdddddrrrr");
        else if(!strcmp(opcode, "ADC"))
            strcpy(objCode, "000111rdddddrrrr");
        else if(!strcmp(opcode, "SUB"))
            strcpy(objCode, "000110rdddddrrrr");
        else if(!strcmp(opcode, "AND"))
            strcpy(objCode, "001000rdddddrrrr");
        else if(!strcmp(opcode, "OR"))
            strcpy(objCode, "001010rdddddrrrr");
        else if(!strcmp(opcode, "EOR"))
            strcpy(objCode, "001001rdddddrrrr");
        else if(!strcmp(opcode, "CP"))
            strcpy(objCode, "000101rdddddrrrr");
        else if(!strcmp(opcode, "CPC"))
            strcpy(objCode, "000001rdddddrrrr");
        op=separator(operand);
        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        for(int x=15;x>11;x--)
            objCode[x]=op.constant[x-8];
        objCode[6]=op.constant[3];
        objCode[16]='\0';
    }
    else if(!strcmp(opcode, "SBRS") || !strcmp(opcode, "SBRC")){
        if(!strcmp(opcode, "SBRS"))
            strcpy(objCode, "1111111rrrrr0bbb");
        else if(!strcmp(opcode, "SBRC"))
            strcpy(objCode, "1111110rrrrr0bbb");

        op=separator(operand);
        for(int x=11;x>6;x--)
            objCode[x]=op.reg[x-4];
        for(int x=15;x>12;x--)
            objCode[x]=op.constant[x-8];
        objCode[16]='\0';

    }
    else if(!strcmp(opcode, "BREQ") || !strcmp(opcode, "BRNE") || !strcmp(opcode, "BRCS") || !strcmp(opcode, "BRCC")){

        if(!strcmp(opcode, "BREQ"))
            strcpy(objCode, "111100kkkkkkk001");
        else if(!strcmp(opcode, "BRNE"))
            strcpy(objCode, "111101kkkkkkk001");
        else if(!strcmp(opcode, "BRCS"))
            strcpy(objCode, "111100kkkkkkk000");
        else if(!strcmp(opcode, "BRCC"))
            strcpy(objCode, "111101kkkkkkk000");

        op=separator(operand);
        for(int x=12;x>4;x--)
            objCode[x]=op.reg[x-5];
        objCode[16]='\0';
        printf("%s   \n\n",objCode);
    }
    else if(!strcmp(opcode, "IN")){
        strcpy(objCode, "111100kkkkkkk001");
        op=symbolConst(operand);
        printf("%s %s",op.reg,op,constant);
        strcpy(objCode, "000000000000");
    }
    printf("Binary value--%s\n", objCode);
    hex = strtoul(objCode, NULL, 2);
    return hex;
}

int main() {
    unsigned long objCode = objectCode("BREQ", "BACK");
    printf("0x%04lX", objCode);
    return 0;
}
*/

