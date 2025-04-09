// I THINK I GNOE REGERT THIS

/**
so what is the steps for s-des
1. key genrate key for encription --first
    - p10(k) == A
    - lshift(A)
    - p8(lshift(A)) - genearte key 1
    # for key 2 
    - lshift2(A) # shifting for 2
    - p8(lshift(A))
    - genearte key 2
**/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "helpers/shifting.h"
#include "helpers/spliting.h"
#include "des_operation/pn.h"

int main() {

    // starting with define the matrix for p10 and p8 and p4
    int p10[10] = {3,5,2,7,4,10,1,9,8,6};
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 6};
    int p4[4] = {2, 4, 3, 1};
    int Ip[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    int Ep[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    int Ip_1[8] = {4, 1, 3, 5, 7, 2, 8, 6};

    int s_box1[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    int s_box2[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    // main encryption text and key
    char plain_text[8+1] = "00101000";
    char main_key[10+1] = "1100011110";

    // starting with p10
    int size_of_p10 = sizeof(p10) / sizeof(p10[0]);
    char* p10_value = pn_operation(main_key, p10, size_of_p10);

    printf("===========\n");
    printf("the value for p10: %s\n", p10_value);
    printf("===========\n");

    char *key_one;
    char *key_two;

    // for spliting the p10_value
    split_array sp_array = spliting(p10_value, sizeof(p10_value) + 2);
    printf("after spliting left: %s\n", sp_array.left_array);
    printf("after spliting right: %s\n", sp_array.right_array);
    printf("===========\n");


    // for - lshift(A)
    sarr s_arr = shifting(sp_array, 1);
    printf("the value for shifted array: %s\n", s_arr.s_arr);
    printf("===========\n");

    // - p8(lshift(A)) - genearte key 1
    int size_of_p8 = sizeof(p8) / sizeof(p8[0]);
    key_one  = pn_operation(s_arr.s_arr, p8, size_of_p8);
    printf("key one: %s\n", key_one);

    // starting for key2 now
    s_arr = shifting(sp_array, 2);

    key_one  = pn_operation(s_arr.s_arr, p8, size_of_p8);
    printf("key two: %s\n", key_one);
    printf("===========\n");

    free(p10_value);

    return 0;
}
