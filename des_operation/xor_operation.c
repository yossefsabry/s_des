#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xor_operation(char* key_one, char* key_two) {

    // FIX THIS TOOO THE LENGTH ELEMENT NOT WRITE FOR ONE KEY AND SECOND
    // KEY CHECK THE 
    // char* sbox_larr = xor_operation(sbox_p4, ip_array.left_array);
    /*printf("%lu, %lu",strlen(key_one), strlen(key_two));*/
    /*if (strlen(key_one) != strlen(key_two) || key_one == NULL || strlen(key_one) == 0) {*/
    /*    perror("error happened in in operation check key_one and key_two");*/
    /*    return NULL; // Return NULL to indicate an error*/
    /*}*/
    int nsize = strlen(key_two);
    char *results = (char*)malloc((nsize - 1) * sizeof(char)); 
    results[0] = '\0';
    // Allocate space for nsize characters + null terminator
    if (results == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    results[0] = '\0'; 
    // Initialize as an empty, null-terminated string
    for (int i = 0; i < nsize; i++) {
        char temp_key = key_one[i];
        char temp_ep = key_two[i];
        int results_cmp = (temp_ep == temp_key) ? 0 : 1;

        if (results_cmp == 0) {
            strcat(results, "0");
        } else {
            strcat(results, "1");
        }
    }
    return results;
}
