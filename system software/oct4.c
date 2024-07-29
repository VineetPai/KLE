#include <stdio.h>

int main() {
    FILE *inputFile, *outputFile;
    char ch;

    // Open the input file for reading
    inputFile = fopen("input.txt", "r");

    // Check if the input file opened successfully
    if (inputFile == NULL) {
        printf("Input file couldn't be opened.\n");
        return 1;
    }

    // Open the output file for writing
    outputFile = fopen("output.txt", "w");

    // Check if the output file opened successfully
    if (outputFile == NULL) {
        printf("Output file couldn't be opened.\n");
        fclose(inputFile); // Close the input file before exiting
        return 1;
    }

    // Read characters from the input file and write them to the output file
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile);
    }

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("File contents copied to output.txt successfully.\n");

    return 0;
}
