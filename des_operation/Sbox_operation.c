#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structs.h"
#include "../helpers/spliting.h"

typedef struct{
    int x; 
    int y;
    int new_values;
}sbox_values;


char* decimalToBinary(int num, int num2) {
    char *results = (char*)malloc(4 + 1);
    // enough for two 2-bit binary numbers and a separator (optional) + null
    results[0] = '\0';

    // convert num to binary (up to 2 bits since max is 3)
    for (int i = 1; i >= 0; i--) {
        // explain >> how this works
        /*
       first round:
           num = 2 - represent by binary(0010)
           when shift right >> taking from right to left, 
           if shifting from left << taking from left to right

           - 0001 == 1
        - & what and mean it's AND operating in bitwase
        0001 & 0001 = 0001 (mean true)

        second round:
            num = 0001 = 1
            after shifting right another time 1000 = 8
            so 1000 & 0001 = 0000 = 0 this mean false even if it's represet 
            something not zero for example 5 0101 it's gone be false too, 
            only 1 represent true so gone go for else and adding 0


        hint: if num = 3 0011
        // FIX
        first round 1001 & 0001 = 0001
        second round 1100 & 0001 = 0000
        */
        if ((num >> i) & 1) {
            strcat(results, "1");
        } else {
            strcat(results, "0");
        }
    }

    // add a separator (optional, but makes it clearer)
    // strcat(results, "-");

    // Convert num2 to binary (up to 2 bits since max is 3)
    for (int i = 1; i >= 0; i--) {
        if ((num2 >> i) & 1) {
            strcat(results, "1");
        } else {
            strcat(results, "0");
        }
    }

    return results;
}

int binaryToDecimal(const char *binaryString) {
    char *endptr;
    long decimalValue = strtol(binaryString, &endptr, 2);

    // error checking (optional, but recommended)
    if (*endptr != '\0') {
        fprintf(stderr, "Error: Invalid binary string: %s\n", binaryString);
        return -1; // Or some other error indicator
    }
    return (int)decimalValue;
}


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
