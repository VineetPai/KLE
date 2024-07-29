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
    struct ALPCode Inc[100]; // Adjust the size as needed

    char line[256]; // Buffer to store each line
    int lineCount = 0;

    // Read and parse each line from the file
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        // Tokenize the line using strtok
        char *token = strtok(line, " \t\n"); // Tokenize based on spaces, tabs, and newline characters

        if (token != NULL) {
            // Check if the line contains three words (label is present)
            char *secondToken = strtok(NULL, " \t\n");
            char *thirdToken = strtok(NULL, " \t\n");

            if (secondToken != NULL && thirdToken != NULL) {
                // It's a label, so store it
                strcpy(Inc[lineCount].label, token);
                strcpy(Inc[lineCount].opcode, secondToken);
                strcpy(Inc[lineCount].operand, thirdToken);
            } else {
                // It's not a label, so there is no label on this line
                strcpy(Inc[lineCount].label, ""); // No label on this line
                strcpy(Inc[lineCount].opcode, token);
                if (secondToken != NULL) {
                    strcpy(Inc[lineCount].operand, secondToken);
                } else {
                    strcpy(Inc[lineCount].operand, ""); // No operand on this line
                }
            }

            // Increment the line count
            lineCount++;
        }
    }

    // Close the file
    fclose(filePointer);

    // Print the stored ALP code
    for (int i = 0; i < lineCount; i++) {
        printf("Line %d: Label: %s, Opcode: %s, Operand: %s\n", i + 1, Inc[i].label, Inc[i].opcode, Inc[i].operand);
    }

    return 0;
}
