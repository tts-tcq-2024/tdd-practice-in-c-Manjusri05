#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_NUMBERS 1000

// Function to calculate the sum from a string input
int CalculateAdd(const char* input) {
    if (strlen(input) == 0) return 0; // Handle empty input

    int sum = 0;
    char* token;
    char* endptr;
    char* str = strdup(input); // Duplicate input for tokenization
    const char* delimiters = ",\n"; // Default delimiters

    // Check for custom delimiter
    if (str[0] == '/' && str[1] == '/') {
        // Extract custom delimiter
        char* customDelim = strtok(str + 2, "\n");
        delimiters = customDelim;
        str = strtok(NULL, ""); // Get the rest of the string
    }

    token = strtok(str, delimiters);
    while (token != NULL) {
        int number = strtol(token, &endptr, 10);

        // Handle non-numeric input
        if (*endptr != '\0') {
            free(str);
            return 0; // Non-numeric input returns zero
        }

        // Handle negative numbers
        if (number < 0) {
            free(str);
            fprintf(stderr, "Negative numbers are not allowed: %d\n", number);
            exit(EXIT_FAILURE); // Raise an error for negative numbers
        }

        // Ignore numbers greater than 1000
        if (number <= MAX_NUMBERS) {
            sum += number;
        }

        token = strtok(NULL, delimiters);
    }

    free(str);
    return sum;
}

// Test cases
void testEmptyInput() {
    int result = CalculateAdd("");
    printf("Expect Zero For Empty Input: %s\n", result == 0 ? "Passed" : "Failed");
}

void testSingleZero() {
    int result = CalculateAdd("0");
    printf("Expect Zero For Single Zero: %s\n", result == 0 ? "Passed" : "Failed");
}

void testTwoNumbers() {
    int result = CalculateAdd("1,2");
    printf("Expect Sum For Two Numbers: %s\n", result == 3 ? "Passed" : "Failed");
}

void testNegativeNumbers() {
    // This will exit the program; hence only print the intention
    printf("Expect Exception For Negative Numbers: (check stderr)\n");
    char input[] = "-1,2";
    if (CalculateAdd(input) == 0) {
        printf("  Passed\n");
    }
}

void testNewlineDelimiter() {
    int result = CalculateAdd("1\n2,3");
    printf("Expect Sum With Newline Delimiter: %s\n", result == 6 ? "Passed" : "Failed");
}

void testIgnoreNumbersGreaterThan1000() {
    int result = CalculateAdd("1,1001");
    printf("Ignore Numbers Greater Than 1000: %s\n", result == 1 ? "Passed" : "Failed");
}

void testCustomDelimiter() {
    int result = CalculateAdd("//;\n1;2");
    printf("Expect Sum With Custom Delimiter: %s\n", result == 3 ? "Passed" : "Failed");
}

void testBoundaryConditions() {
    int result1 = CalculateAdd("999,2");
    printf("Numbers Greater Than 1000 Ignored In Sum (999,2): %s\n", result1 == 1001 ? "Passed" : "Failed");

    int result2 = CalculateAdd("1001,2");
    printf("Numbers Greater Than 1000 Ignored In Sum (1001,2): %s\n", result2 == 2 ? "Passed" : "Failed");
}

void testNonNumericInput() {
    int result = CalculateAdd("Hello, world!");
    printf("Non-Numeric Input Returns Zero: %s\n", result == 0 ? "Passed" : "Failed");
}

int main() {
    testEmptyInput();
    testSingleZero();
    testTwoNumbers();
    testNegativeNumbers();
    testNewlineDelimiter();
    testIgnoreNumbersGreaterThan1000();
    testCustomDelimiter();
    testBoundaryConditions();
    testNonNumericInput();

    return 0;
}
