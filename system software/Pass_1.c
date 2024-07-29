#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// LL : Linked List
// sprintf(): Used to convert an integer value to string with same numbers
// strtol(): Used to convert strings to integers with different bases (hex used for Hex)
// atoi(): used to convert strings to integers with base 10

/* In SIC_Input File,
Each fields are separated by \t (Tabspace)
If any field is empty, ( ) - single space is given in the place
After last non-empty line, an empty line is required for reading
*/

/*
In Optab File, each field is separated by \t (Tabspace),
and after last non-empty line, an empty line is required for reading
*/

struct instruction //Structure Declaration for storing each instructions from SIC Program text
{
    int line_no;
    char label[30],opcode[30],operand[30];
    struct instruction *nlink;
};
typedef struct instruction INS;

struct opcode_table //Structure Declaration for storing each Opcode from Opcode Table text
{
    char addrs[30],opcode[30];
    struct opcode_table *nlink;
};
typedef struct opcode_table OPTAB;

struct symbol_table //Structure Declaration for storing each symbols, generated in SIC program
{
    char addrs[30],label[30];
    struct symbol_table *nlink;
};
typedef struct symbol_table SYMTAB;

INS *create_instruction(char a[30],char b[30],char c[30]) //Function to create new Instruction Nodes
{
    INS *n;
    n=(INS *)malloc(sizeof(INS));
    n->nlink=NULL;
    n->line_no = 0;
    strcpy(n->label,a);
    strcpy(n->opcode,b);
    strcpy(n->operand,c);
    return n; //Returns the pointer of newly created Node to insert_instruction() function
}

OPTAB *create_optab(char a[30],char b[30]) //Function to create new Optab Nodes
{
    OPTAB *n;
    n=(OPTAB *)malloc(sizeof(OPTAB));
    n->nlink=NULL;
    strcpy(n->opcode,a);
    strcpy(n->addrs,b);
    return n; //Returns the pointer of newly created Node to insert_optab() function
}

INS *insert_instruction(INS *head,char a[30],char b[30],char c[30]) //Function to append newly created Instruction nodes to the end of Instructions LL
{
    INS *temp=create_instruction(a,b,c),*p=head;
    if(head==NULL)
        head=temp;
    else
    {
        while(p->nlink!=NULL)
            p=p->nlink;
        p->nlink=temp;
    }
    return head;
}

OPTAB *insert_optab(OPTAB *head,char a[30],char b[30]) //Function to append newly created Optab Nodes (Opcodes from Optab text file) to the end of Optab LL
{
    OPTAB *temp=create_optab(a,b),*p=head;
    if(head==NULL)
        head=temp;
    else
    {
        while(p->nlink!=NULL)
            p=p->nlink;
        p->nlink=temp;
    }
    return head;
}

INS *read_sic() //Function to read and store Instructions from SIC program Text to Instructions
{
    int line_no=0;
    FILE *f1;
    f1 = fopen("input_alp.txt","r");
    INS *ihead = NULL,*temp;
    char label[15],opcode[15],operand[15],*token,addrs[15];
    char buff[30];
    if(f1 == NULL)
    {
        printf("Sorry the file cannot be opened!!");
        exit(0);
    }
    while(fgets(buff,30,f1))
    {
        if(buff[0] == '.')
            continue;
        buff[strlen(buff)-1] = '\0';
        token = strtok(buff, "\t");
        strcpy(label,token);
        token = strtok(NULL, "\t");
        strcpy(opcode,token);
        token = strtok(NULL, "\t");
        strcpy(operand,token);
        ihead = insert_instruction(ihead,label,opcode,operand);
    }
    fclose(f1);
    temp = ihead;
    while(temp != NULL) //adds line numbers to all the instructions
    {
        line_no += 1;
        temp->line_no = line_no;
        temp = temp->nlink;
    }
    printf("\n--- Input Program File has been read with number of lines: %d ---\n",line_no);
    return ihead; //Returns the head pointer of Instructions LL to main function
}

OPTAB *read_optab() //Function to read Optab Text and store the Opcodes with addresses to Optab LL
{
    FILE *f2;
    f2 = fopen("optab.txt","r");
    OPTAB *ohead = NULL;
    char opcode[15],*token,addrs[15];
    char buff[30];
    if(f2 == NULL)
    {
        printf("Sorry the file cannot be opened!!");
        exit(0);
    }
    while(fgets(buff,30,f2))
    {
        buff[strlen(buff)-1] = '\0';
        token = strtok(buff, "\t");
        strcpy(opcode,token);
        token = strtok(NULL, "\t");
        strcpy(addrs,token);
        ohead = insert_optab(ohead,opcode,addrs);
    }
    fclose(f2);
    printf("\n--- Input OPTAB File has been read ---\n");
    return ohead; //Returns the head pointer of Optab LL to main function
}

SYMTAB *create_symbol(char a[30],char b[30]) //Function to create new Symbol Nodes
{
    SYMTAB *n;
    n=(SYMTAB *)malloc(sizeof(SYMTAB));
    n->nlink=NULL;
    strcpy(n->label,a);
    strcpy(n->addrs,b);
    return n; //Returns the pointer of newly created Node to insert_symtab() function
}

SYMTAB *insert_symtab(SYMTAB *head,char a[30],char b[30]) //Function to append newly created Symtab Nodes to the end of Symtab LL
{
    SYMTAB *temp=create_symbol(a,b),*p=head;
    if(head==NULL)
        head=temp;
    else
    {
        while(p->nlink!=NULL)
            p=p->nlink;
        p->nlink=temp;
    }
    return head;
}

int search_opcode(char a[30], OPTAB *ohead) //Function to Search the given Opcode in the Optab table LL
{
    OPTAB *temp = ohead;
    int flag = 0;
    while(temp != NULL)
    {
        if(strcmp(a,temp->opcode) == 0)
        {
            flag = 1;
            break;
        }
        temp = temp->nlink;
    }
    return flag; //Return 1 if opcode is present in Optab else return 0
}

void write_inter(OPTAB *ohead,INS *ihead) //Program to write the instructions with addresses to Intermediate file and also create and write Symbol Table file
{
    int size_1,size_2;
    FILE *f_sym = fopen("symtab.txt","a");
    FILE *f_inter = fopen("intermediate.txt","a");
    if(!f_sym || !f_inter)
    {
        printf("Sorry, Output files couldn't be created!!!");
        exit(0);
    }

    fseek(f_sym,0,SEEK_END); //relocate the file pointer to last position
    fseek(f_inter,0,SEEK_END);
    size_1 = ftell(f_sym); //calculate the position of current file pointer with respect to start of the file
    size_2 = ftell(f_inter);

    if(size_1 != 0) //if the position of file pointer is not 0, print warning
        printf("\n!!! Sorry, the SYMTAB already has values present in it !!!\n");
    if(size_2 != 0)
        printf("!!! Sorry, the Intermediate file is not empty !!!\n");

    int start_addrs = 0,locctr = 0,sym_flag = 0;
    FILE *f_len = fopen("prog_length.txt","w");
    f_sym = fopen("symtab.txt","w");
    f_inter = fopen("intermediate.txt","w");
    INS *tempi = ihead->nlink;
    SYMTAB *shead = NULL,*temps;
    char sym_addrs[30],hex_str[30],i_addrs[30];//,empty_zeros[3][4] = {"000","00","0"}, temp_str[30];

    printf("\n--- Generating Intermediate File ---\n");
    if(f_inter == NULL || f_sym == NULL)
    {
        printf("Sorry, Output files couldn't be created!!!");
        exit(0);
    }
    printf("\n--- Generating Symbol Table ---\n");
    if(strcmp(ihead->opcode,"START") == 0) //Check if Opcode of first Line in SIC program is START
    {
        locctr = start_addrs = strtol(ihead->operand,NULL,16); //If Opcode is START, assign the Hex converted value of Operand in first line to start_addrs, locctr
        fprintf(f_inter," \t%s\t%s\t%s\n",ihead->label,ihead->opcode,ihead->operand);
    }
    while(tempi != NULL && strcmp(tempi->opcode,"END") !=0 )
    {
        sprintf(i_addrs,"%04x",locctr); //this part adds zeros as prefix of location counter if the current location has less than 4 characters in it
        fprintf(f_inter,"%s\t%s\t%s\t%s\n",i_addrs,tempi->label,tempi->opcode,tempi->operand);
        if(strcmp(tempi->label," ") != 0) //to check if a symbol is present in the label field or not
        {
            sym_flag = 0;
            temps = shead;
            while(temps != NULL)
            {
                if(strcmp(temps->label,tempi->label) == 0) //check if the symbol table already has the current label
                {
                    sym_flag = 1;
                    break;
                }
                temps = temps->nlink;
            }
            if(sym_flag == 0) //symbol in label field doesn't have any duplicate, add it to SYMTAB LL
                shead = insert_symtab(shead,tempi->label,i_addrs);
            else //if a duplicate label is encountered, Print the duplicate label and terminate the assembler
            {
                printf("!!! Duplicate Symbol detected -- %s, at line number: %d !!!\n",tempi->label,tempi->line_no);
                //printf("Terminating Assembler !!!\n");
                //exit(0);
            }
        }

        if(strcmp(tempi->opcode,"WORD") == 0)
            locctr = locctr + 3;
        else if(strcmp(tempi->opcode,"BYTE") == 0)
        {
            if(tempi->operand[0] == 'C')
                locctr = locctr + (strlen(tempi->operand)-3);
            else
            {
                if((strlen(tempi->operand)-3)%2==1)
                    locctr = locctr + ((strlen(tempi->operand)-3)/2) + 1;
                else
                    locctr = locctr + ((strlen(tempi->operand)-3)/2);
            }
        }
        else if(strcmp(tempi->opcode,"RESB") == 0)
            locctr = locctr + atoi(tempi->operand);
        else if(strcmp(tempi->opcode,"RESW") == 0)
            locctr = locctr + (3*atoi(tempi->operand));
        else if(search_opcode(tempi->opcode,ohead) == 1)
            locctr = locctr + 3;
        else //If opcode is not recognized, Print the unknown opcode and end assembler
        {
            printf("!!! Opcode could not be recognized -- %s, at line number: %d !!!\n",tempi->opcode,tempi->line_no);
            //printf("\nTerminating Assembler !!!\n");
            //exit(0);
        }
        tempi = tempi->nlink;
    }
    fprintf(f_inter," \t \tEND\t \n");
    temps = shead;
    while(temps != NULL) //print Symtab LL to Symbol table text file
    {
        fprintf(f_sym,"%s\t%s\n",temps->addrs,temps->label);
        temps = temps->nlink;
    }
    printf("\n--- Symbol Table Generated ---\n");
    printf("\n--- Intermediate File Generated ---\n");
    printf("\n--- Generating Program Length File ---\n");
    fprintf(f_len,"%x",locctr-start_addrs);
    printf("\n--- Program Length File Generated ---\n");
}

void main()
{
    INS *ihead=read_sic();
    OPTAB *ohead=read_optab();
    write_inter(ohead,ihead);
    printf("\n--- Pass_1 Phase Successful ---\n");
}
