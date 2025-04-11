#include <string.h>
#include "../structs.h"
#include "../helpers/spliting.h"
#include "../des_operation/convert_operation.h"

char* Sbox_operation(char *value, int sbox_matrix[4][4],
                     int sbox_matrix2[4][4]){
    split_array sp = spliting(value, strlen(value));

    // printf("the size of sp from sbox: %lu\n", strlen(value));
    // printf("left side: %s\n", sp.left_array);
    // printf("right side: %s\n", sp.right_array);

    sbox_values v1;
    char fa[3] = {sp.left_array[0], sp.left_array[3], '\0'};
    char fa2[3] = {sp.left_array[1], sp.left_array[2], '\0'};
    v1.x = binaryToDecimal(fa);
    v1.y = binaryToDecimal(fa2);
    v1.new_values = sbox_matrix[v1.x][v1.y];


    sbox_values v2;
    char sa[3] = {sp.right_array[0], sp.right_array[3], '\0'};
    char sa2[3] = {sp.right_array[1], sp.right_array[2], '\0'};
    v2.x = binaryToDecimal(sa);
    v2.y = binaryToDecimal(sa2);
    v2.new_values = sbox_matrix2[v2.x][v2.y];

    char *new_binary_value = decimalToBinary(v1.new_values, v2.new_values);

    // for debuger
    // printf("the value for first round the decimal value fo : X:%d, Y:%d\n" , v1.x, v1.y);
    // printf("new value one: %d\n", v1.new_values);
    // printf("the value for second round: X:%d, Y:%d\n", v2.x, v2.y);
    // printf("new value two: %d\n", v2.new_values);


    return new_binary_value;
};
