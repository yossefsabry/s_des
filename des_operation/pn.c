
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* pn_operation(char arr[], int *pn, int s_pn) {
    int n = strlen(arr);

    // for debuger
    // printf("size of n: %d, size of s_pn: %d\n", n, s_pn);

    // for example p10 => so array with size of 9, and p8 array with size 4...
    char* results;
    if (n <= s_pn)
        results = (char*)malloc(n * sizeof(char)); // Allocate memory on the heap
    else
        results = (char*)malloc(s_pn * sizeof(char)); // Allocate memory on the heap
    
    if (results == NULL) {
        perror("Memory allocation failed");
        return NULL; // Handle allocation failure
    }

    for (int i = 0; i < s_pn; i++) {
        // Adjust the pn value to be a 0-based index
        int index = pn[i] - 1;

        // Check if the adjusted index is within the bounds of arr
        if (index >= 0 && index < strlen(arr)) {
            results[i] = arr[index];
        } else {
            fprintf(stderr, "Error: Invalid index in pn permutation\n");
            free(results);
            return NULL; // Handle invalid permutation
        }
    }
    return results;
}

