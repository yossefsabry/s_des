#include "../structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
// #include <errno.h> // For perror

// shifting: main function for shifting a specific bits
/*sarr shifting(split_array sp_arr, int sf_s) {*/
/*    sarr s_arr;*/
/*    s_arr.l_arr = NULL; // Initialize*/
/*    s_arr.r_arr = NULL; // Initialize*/
/*    s_arr.s_arr = NULL; // Initialize*/
/**/
/*    // Shifting left side (Right Circular Shift as per your desired output)*/
/*    int left_len = strlen(sp_arr.left_array);*/
/*    if (left_len > 1 && sf_s % left_len != 0) {*/
/*        sf_s = (sf_s % left_len + left_len) % left_len; // Ensure positive sf_s value*/
/*        char* l_shifted = strdup(sp_arr.left_array);*/
/*        if (l_shifted == NULL) {*/
/*            perror("Memory allocation failed for left shift\n");*/
/*            return s_arr;*/
/*        }*/
/*        for (int i = 0; i < left_len; i++) {*/
/*            l_shifted[i] = sp_arr.left_array[(i + sf_s + left_len) % left_len];*/
/*        }*/
/*        s_arr.l_arr = l_shifted;*/
/*    } else {*/
/*        s_arr.l_arr = strdup(sp_arr.left_array); // No shift needed or error*/
/*    }*/
/**/
/*    // Shifting right side (Left Circular Shift as per your desired output)*/
/*    int right_len = strlen(sp_arr.right_array);*/
/*    if (right_len > 1 && sf_s % right_len != 0) {*/
/*        sf_s = (sf_s % right_len + right_len) % right_len; // Ensure positive sf_s value*/
/*        char* r_shifted = strdup(sp_arr.right_array);*/
/*        if (r_shifted == NULL) {*/
/*            perror("Memory allocation failed for right shift\n");*/
/*            free(s_arr.l_arr);*/
/*            return s_arr;*/
/*        }*/
/*        for (int i = 0; i < right_len; i++) {*/
/*            r_shifted[i] = sp_arr.right_array[(i + sf_s) % right_len]; */
/*        }*/
/*        s_arr.r_arr = r_shifted;*/
/**/
/*        // check s_arr.s_arr*/
/*        s_arr.s_arr = strcat(s_arr.l_arr, s_arr.r_arr);*/
/*    } else {*/
/*        s_arr.l_arr = strdup(sp_arr.left_array); // Keep original left*/
/*        s_arr.r_arr = strdup(sp_arr.right_array); // No shift needed or error*/
/*        free(s_arr.l_arr); // Free previously allocated if no right shift*/
/*    }*/
/**/
/**/
/*    // for debuger*/
/*    // printf("the left side shifting: %s\n", s_arr.l_arr);*/
/*    // printf("the right side shifting: %s\n", s_arr.r_arr);*/
/*    // printf("===========\n");*/
/**/
/*    return s_arr;*/
/*}*/


// PROBLEM in FUCKING SHITING BY 2 SLOVE
sarr shifting(split_array sp_arr, int sf_s) {
    sarr s_arr = {0};

    int left_len = strlen(sp_arr.left_array);
    int right_len = strlen(sp_arr.right_array);

    // shift left side
    char* l_shifted = (char*)malloc(left_len + 1);
    if (!l_shifted) {
        perror("Memory allocation failed for left shift");
        return s_arr;
    }

    // left circular shift
    for (int i = 0; i < left_len; i++) {
        l_shifted[i] = sp_arr.left_array[(i + sf_s) % left_len];
    }
    l_shifted[left_len] = '\0';

    // shift right side
    char* r_shifted = (char*)malloc(right_len + 1);
    if (!r_shifted) {
        perror("Memory allocation failed for right shift");
        free(l_shifted);
        return s_arr;
    }

    // right circular shift
    for (int i = 0; i < right_len; i++) {
        r_shifted[i] = sp_arr.right_array[(i + sf_s) % right_len];
    }
    r_shifted[right_len] = '\0';

    // combine left and right shifted values
    s_arr.l_arr = l_shifted;
    s_arr.r_arr = r_shifted;

    // concatenate left and right parts into s_arr.s_arr
    int total_len = left_len + right_len;
    s_arr.s_arr = (char*)malloc(total_len + 1);
    if (!s_arr.s_arr) {
        perror("Memory allocation failed for s_arr.s_arr");
        free(l_shifted);
        free(r_shifted);
        return s_arr;
    }

    strcpy(s_arr.s_arr, l_shifted);
    strcat(s_arr.s_arr, r_shifted);

    return s_arr;
}
