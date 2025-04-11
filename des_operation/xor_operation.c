#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xor_operation(char* key_one, char* Ep_R) {
    if (strlen(key_one) != strlen(Ep_R) || key_one == NULL || strlen(key_one) == 0) {
        perror("error happened in in operation check EP_R nad key");
        return NULL; // Return NULL to indicate an error
    }
    int nsize = strlen(key_one);
    char *results = (char*)malloc((nsize + 1) * sizeof(char)); 
    // Allocate space for nsize characters + null terminator
    if (results == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    results[0] = '\0'; // Initialize as an empty, null-terminated string
    for (int i = 0; i < nsize; i++) {
        char temp_key = key_one[i];
        char temp_ep = Ep_R[i];
        int results_cmp = (temp_ep == temp_key) ? 0 : 1;

        if (results_cmp == 0) {
            strcat(results, "0");
        } else {
            strcat(results, "1");
        }
    }
    return results;
}
