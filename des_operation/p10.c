
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* p10_operation(char arr[], const int p10[]) {
    char* results = (char*)malloc(11 * sizeof(char)); // Allocate memory on the heap
    if (results == NULL) {
        perror("Memory allocation failed");
        return NULL; // Handle allocation failure
    }

    for (int i = 0; i < 10; i++) {
        // Adjust the p10 value to be a 0-based index
        int index = p10[i] - 1;

        // Check if the adjusted index is within the bounds of arr
        if (index >= 0 && index < strlen(arr)) {
            results[i] = arr[index];
        } else {
            fprintf(stderr, "Error: Invalid index in p10 permutation\n");
            free(results);
            return NULL; // Handle invalid permutation
        }
    }
    results[10] = '\0'; // Null-terminate the result string
    return results;
}

