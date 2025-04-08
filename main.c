// I THINK I GNOE REGERT THIS

/**
so what is the steps for s-des
1. key genrate key for encription --first
    - p10(k) == A
    - lshift(A)
    - p8(lshift(A)) - genearte key 1
    # for key 2 - lshift2(A) # shifting for 2
    - p8(lshift(A))
    - genearte key 2
**/

#include <stdio.h>
#include "structs.h"
#include "helpers/shifting.h"
#include "helpers/spliting.h"

int main() {

    // starting with define the matrix for p10 and p8 and p4
    const int p10[10] = {3,5,2,7,4,10,1,9,8,6};
    const int p8[8] = {6, 3, 7, 4, 8, 5, 10, 6};
    const int p4[4] = {2, 4, 3, 1};
    const int Ip[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    const int Ep[8] = {4, 1, 2, 3, 2, 3, 4, 1};
    const int Ip_1[8] = {4, 1, 3, 5, 7, 2, 8, 6};

    const int s_box1[4][4] = {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    };

    const int s_box2[4][4] = {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    };

    const char plain_text[8+1] = "00101000";
    const char main_key[10+1] = "1100011110";

    char *key_one;
    char *key_two;

    split_array sp_array = spliting(main_key, sizeof(main_key));

    printf("the left value: %s\n", sp_array.left_array);
    printf("the right value: %s\n", sp_array.right_array);

    sarr s_arr = shifting(sp_array, 2);

    return 0;
}
