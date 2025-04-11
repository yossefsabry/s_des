
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

