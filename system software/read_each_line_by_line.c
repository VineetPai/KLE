#include <stdio.h>

int main() {
    // Open the text file for reading
    FILE *filePointer = fopen("input.txt", "r");

    // Check if the file opened successfully
    if (filePointer == NULL) {
        printf("File couldn't be opened.\n");
        return 1;
    }

    char line[256]; // Buffer to store each line (adjust the size as needed)

    // Read and print each line until the end of the file
    while (fgets(line, sizeof(line), filePointer) != NULL) {
        printf("Line: %s", line); // You can process the line here
    }

    // Close the file
    fclose(filePointer);

    return 0;
}

