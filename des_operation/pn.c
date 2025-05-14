
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// this sucks but work i guess ;)
char* pn_operation(char arr[], int *pn, int s_pn) {
    // for debuger
    // printf("size of n: %d, size of s_pn: %d\n", n, s_pn);

    // for example p10 => so array with size of 9, and p8 array with size 4...
    char* results = (char*)malloc(s_pn + 1 * sizeof(char)); 

    results[0] = '\0';

    if (results == NULL) {
        perror("Memory allocation failed");
        return NULL; // Handle allocation failure
    }

    for (int i = 0; i < s_pn; i++) {
        // adjust the pn value to be a 0-based index
        int index = pn[i] - 1;

        // check if the adjusted index is within the bounds of arr
        if (index >= 0 && index < strlen(arr)){
            results[i] = arr[index];
        } else {
            fprintf(stderr, "Error: Invalid index in pn permutation\n");
            free(results);
            return NULL; // Handle invalid permutation
        }
    }
    results[s_pn] = '\0';  // null terminate it for safety and end this
    return results;
}


// this more sucks and useless
/*char* pn_operation(char arr[], int *pn, int s_pn, int arr_size) {*/
/*    // Allocate memory for result + 1 for null terminator if needed*/
/*    char* results = (char*)malloc((s_pn + 1) * sizeof(char));*/
/*    if (results == NULL) {*/
/*        perror("Memory allocation failed");*/
/*        return NULL;*/
/*    }*/
/**/
/*    for (int i = 0; i < s_pn; i++) {*/
/*        int index = pn[i] - 1;  // Convert to 0-based index*/
/*        printf("pn[%d] = %d, index = %d\n", i, pn[i], index);*/
/**/
/*        if (index >= 0 && index < arr_size) {*/
/*            results[i] = arr[index];*/
/*        } else {*/
/*            fprintf(stderr, "Error: Invalid index in pn permutation\n");*/
/*            free(results);*/
/*            return NULL;*/
/*        }*/
/*    }*/
/**/
/*    results[s_pn] = '\0';  // null terminate it for safety*/
/*    return results;*/
/*}*/
