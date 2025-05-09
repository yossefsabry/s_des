// I THINK I GNOE REGERT THIS
// I HATE THIS

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
#include "helpers/handle_bits.h"
#include "run.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {


    read_and_print_bits("./img_operation/src/img.txt", "./img_operation/src/img_encryption.txt");

    char* value = run("00000000");
    printf("the encrypted value: %s\n", value);
    printf("the len for value: %lu", strlen(value));

    free(value);
    return 0;
}
