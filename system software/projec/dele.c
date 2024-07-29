#include <stdio.h>
#include <string.h>

int main() {
    char inputString[] = "vineet=R01";
    char name[20];  // Adjust the size based on your requirements
    char code[20];  // Adjust the size based on your requirements

    // Find the position of the '=' character
    char* equalSign = strchr(inputString, '=');

    if (equalSign != NULL) {
        // Copy characters before the '=' to the 'name' variable
        strncpy(name, inputString, equalSign - inputString);
        name[equalSign - inputString] = '\0';  // Null-terminate the 'name' string

        // Copy characters after the '=' to the 'code' variable
        strcpy(code, equalSign + 1);
    } else {
        // Handle the case where '=' is not found
        printf("Error: '=' not found in the input string\n");
        return 1;
    }

    // Print the separated strings
    printf("Name: %s\n", name);
    printf("Code: %s\n", code);

    return 0;
}
