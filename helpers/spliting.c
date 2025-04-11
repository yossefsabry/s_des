
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structs.h"

split_array spliting(const char array[], int len) {
    // starting with spliting the array to left and right side
    split_array sp_arr;
    sp_arr.left_array = "";
    sp_arr.right_array = "";
    if (len <= 0) { // check if there is values in array
        perror("not vaild memory");
        return sp_arr;
    }

    // starting with left hand side of array
    int left_len = len / 2;
    char* l_arr = (char*)malloc(left_len); // Allocate memory for left part
    l_arr[0] = '\0';
    if (l_arr == NULL) { // if error happend in malloc
        perror("Memory allocation failed");
        return sp_arr;
    }
    memcpy(l_arr, array, left_len); // copy a array to left

    // started with the right hand side
    int right_len = len - left_len;
    char* r_arr = (char*)malloc(right_len); // Allocate memory for right part
    r_arr[left_len] = '\0';
    if (r_arr == NULL) {
        perror("Memory allocation failed");
        free(l_arr);
        return sp_arr;
    }
    memcpy(r_arr, array + left_len, right_len);

    // for dobuger
    // printf("the array left value: %s\n", l_arr);
    // printf("the array right value: %s\n", r_arr);

    // return copy from right and left array
    sp_arr.left_array = strdup(l_arr);
    sp_arr.right_array = strdup(r_arr);
    free(l_arr); // free memory
    free(r_arr);
    return sp_arr; // return a struct value
}

