#include <stdio.h>
#include <string.h>

// Define a structure to store ALP code
struct ALPCode {
    char label[50];
    char opcode[10];
    char operand[50];
};

int main() {
    // Open the input file for reading
    FILE *filePointer = fopen("input.txt", "r");

    // Check if the file opened successfully
    if (filePointer == NULL) {
        printf("File couldn't be opened.\n");
        return 1;
    }

    // Define an array of structures to store ALP code
    struct ALPCode alpCodes[100]; // Adjust the size as needed

    char line[256]; // Buffer to store each line
    int lineCount = 0;

    // Read and parse each line from the file
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        // Tokenize the line using strtok
        char *token = strtok(line, " \t\n"); // Tokenize based on spaces, tabs, and newline characters

        if (token != NULL) {
            // Store the token as the label
            strcpy(alpCodes[lineCount].label, token);

            // Tokenize and store the opcode
            token = strtok(NULL, " \t\n");
            if (token != NULL) {
                strcpy(alpCodes[lineCount].opcode, token);
            }

            // Tokenize and store the operand
            token = strtok(NULL, "\n");
            if (token != NULL) {
                strcpy(alpCodes[lineCount].operand, token);
            }

            // Increment the line count
            lineCount++;
        }
    }

    // Close the file
    fclose(filePointer);

    // Print the stored ALP code
    for (int i = 0; i < lineCount; i++) {
        printf("Line %d: Label: %s, Opcode: %s, Operand: %s\n", i + 1, alpCodes[i].label, alpCodes[i].opcode, alpCodes[i].operand);
    }

    return 0;
}
