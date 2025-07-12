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
    printf("=== S-DES Image Encryption System ===\n\n");
    
    // Step 1: Show encryption process for a sample 8-bit block
    printf("Step 1: Demonstrating S-DES encryption process\n");
    printf("===============================================\n");
    char* value = run("00000000");
    printf("Sample encryption result: %s\n", value);
    printf("Length: %lu bits\n\n", strlen(value));
    free(value);
    
    // Step 2: Encrypt the image file
    // printf("Step 2: Encrypting image file\n");
    // printf("==============================\n");
    // printf("Input file: ./img_operation/src/img.txt\n");
    // printf("Output file: ./img_operation/src/img_encryption.txt\n");

    // encrypt_bits_and_save("./img_operation/src/img.txt", 
    //                       "./img_operation/src/img_encryption.txt");

    // printf("\n=== Encryption Complete ===\n");
    // printf("Next steps:\n");
    // printf("1. Run: cd img_operation/src && python convert_binary_img.py\n");
    // printf("2. Check the outputs/ folder for the encrypted image\n");
    
    return 0;
}
