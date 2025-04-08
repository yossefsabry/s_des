#include "../structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// shifting: main function for shifting a specific bits
sarr shifting(split_array sp_arr, int sf_s){
    sarr s_arr;

    // starting with shift left
    int len = strlen(sp_arr.left_array);
    if (len <= 1 || sf_s % len == 0) {
        perror("nothing to shif in left side");
        return s_arr;
    }
    sf_s = (sf_s % len + len) % len; // Ensure positive sf_s value
    char* l_shifted = strdup(sp_arr.left_array);
    if (l_shifted == NULL) {
        perror("Memory allocation failed");
        return s_arr;
    }
    // starting shifting left side
    for (int i = 0; i < len; i++) {
        l_shifted[i] = sp_arr.left_array[(i - sf_s + len) % len];
    }

    
    // starting with shift right
    len = strlen(sp_arr.right_array);
    if (len <= 1 || sf_s % len == 0) {
        perror("nothing to shif in left side");
        return s_arr;
    }
    sf_s = (sf_s % len + len) % len; // Ensure positive sf_s value
    char* r_shifted = strdup(sp_arr.left_array);
    if (l_shifted == NULL) {
        perror("Memory allocation failed");
        return s_arr;
    }
    // starting shifting left side
    for (int i = 0; i < len; i++) {
        r_shifted[i] = sp_arr.right_array[(i - sf_s + len) % len];
    }
    
    printf("the left side shifting: %s\n", l_shifted); 
    printf("the right side shifting: %s\n", r_shifted); 

    free(l_shifted);
    free(r_shifted);

    return s_arr;
};
