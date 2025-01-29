#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compare integers for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

#define MAX_ELEMENTS 10000 // Assuming no more than 100 elements

int main() {
    FILE *file;
    char filename[] = "input.txt";
    int arr1[MAX_ELEMENTS], arr2[MAX_ELEMENTS];
    int n = 0;

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read numbers from file into static arrays
    while (n < MAX_ELEMENTS && fscanf(file, "%d %d", &arr1[n], &arr2[n]) == 2) {
        n++;
    }

    fclose(file);

    // Check if we've reached the limit of our array
    if (n == MAX_ELEMENTS) {
        fprintf(stderr, "Warning: Array size limit reached. Some data might have been ignored.\n");
    }

    // Sort arrays
    qsort(arr1, n, sizeof(int), compare);
    qsort(arr2, n, sizeof(int), compare);

    // Calculate sum of absolute differences
    long long sum = 0; // Use long long for larger sums
    for (int i = 0; i < n; i++) {
        sum += labs(arr2[i] - arr1[i]); // labs for long int, since we're not expecting overflow here
    }

    // Output result
    printf("Sum of absolute differences: %lld\n", sum);

    return 0;
}