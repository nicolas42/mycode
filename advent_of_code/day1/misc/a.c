#include <stdio.h>

int main() {
    // Open the file in read mode
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    int num1, num2;

    // Read integers from the file line by line
    while (fscanf(file, "%d %d", &num1, &num2) == 2) {
        // Process the integers (here we simply print them)
        printf("Read numbers: %d and %d\n", num1, num2);
    }



    // Close the file
    fclose(file);
    return 0;
}
