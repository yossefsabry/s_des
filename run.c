
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

2. encryption process --second
    - IP(plaintext) == split into L0, R0
    # ROUND 1
    - E/P(R0) == expand/permute right half
    - XOR(E/P(R0), K1) == mix with key 1
    - S-box(XOR result) == substitute using S-boxes
    - P4(S-box result) == permute S-box output
    - XOR(P4 result, L0) == mix with left half
    - swap(L1, R0) == prepare for round 2
    # ROUND 2  
    - E/P(R1) == expand/permute right half
    - XOR(E/P(R1), K2) == mix with key 2
    - S-box(XOR result) == substitute using S-boxes
    - P4(S-box result) == permute S-box output
    - XOR(P4 result, L1) == mix with left half
    - combine(L2, R1) == combine final halves
    - IP^-1(combined) == final inverse permutation
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des_operation/Sbox_operation.h"
#include "helpers/swapping_operation.h"
#include "structs.h"
#include "helpers/shifting.h"
#include "helpers/spliting.h"
#include "des_operation/pn.h"
#include "des_operation/xor_operation.h"

char* run(char *bits) {
    // printf("=== S-DES Encryption Process ===\n");
    // printf("Input plaintext: %s\n", bits);
    
    // main encryption text and key
    char plain_text[8] = "";
    char main_key[10+1] = "1100011110";
    strcat(plain_text, bits);

    // starting with define the matrix for p10 and p8 and p4
    int p10[10] = {3,5,2,7,4,10,1,9,8,6};
    int p8[8] = {6, 3, 7, 4, 8, 5, 10, 9};
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

    // printf("Main key: %s\n", main_key);

    // starting with p10
    int size_of_p10 = sizeof(p10) / sizeof(p10[0]);
    char* p10_value = pn_operation(main_key, p10, size_of_p10);
    // printf("P10 result: %s\n", p10_value);

    char *key_one;
    char *key_two;

    // for spliting the p10_value
    split_array sp_array = spliting(p10_value, sizeof(p10_value) + 2);
    // printf("After splitting - Left: %s, Right: %s\n", sp_array.left_array, sp_array.right_array);

    // freee some stuff
    free(p10_value);

    // for - lshift(A)
    sarr s_arr = shifting(sp_array, 1);
    // printf("After 1-bit left shift: %s\n", s_arr.s_arr);

    // - p8(lshift(A)) - genearte key 1
    int size_of_p8 = sizeof(p8) / sizeof(p8[0]);
    key_one  = pn_operation(s_arr.s_arr, p8, size_of_p8);
    // printf("Key 1: %s\n", key_one);

    // starting for key2 now
    // FIX PROBLEM IN FIX  SHIFTING BY 2
    s_arr = shifting(sp_array, 2);
    // printf("After 2-bit left shift: %s\n", s_arr.s_arr);

    key_two  = pn_operation(s_arr.s_arr, p8, size_of_p8);
    // printf("Key 2: %s\n", key_two);

    // getting ip from Plain_text
    int size_ip = sizeof(Ip)/ sizeof(Ip[0]);
    char* ip = pn_operation(plain_text, Ip, size_ip);
    // printf("Initial permutation (IP): %s\n", ip);

    // spliting the ip to right andd left part
    split_array ip_array = spliting(ip, size_ip);
    // printf("After IP splitting - Left: %s, Right: %s\n", ip_array.left_array, ip_array.right_array);

    // free some stuff
    free(ip);

    // === ROUND 1 ===
    // printf("\n--- ROUND 1 ---\n");
    
    // applaying EP on R hand side of ip_array
    int size_of_ep = sizeof(Ep) / sizeof(Ep[0]);
    char *Ep_R = pn_operation(ip_array.right_array, Ep, size_of_ep);
    // printf("E/P(R): %s\n", Ep_R);

    // making a xor with the first key and Ep_R
    char *results = xor_operation(key_one, Ep_R);
    // printf("XOR with Key1: %s\n", results);

    // free some stuff ;)
    free(Ep_R);

    // making a Sbox operation
    char* new_value = Sbox_operation(results, s_box1, s_box2);
    // printf("S-box output: %s\n", new_value);

    // free some stuff ;)
    free(results);

    // p4 on sbox
    int size_of_p4 = sizeof(p4) / sizeof(p4[0]);
    char *sbox_p4 = pn_operation(new_value, p4, size_of_p4);
    // printf("P4(S-box): %s\n", sbox_p4);

    // free some stuff
    free(new_value);

    // making a xor with the sbox_p4, left side split of plain_text
    char* sbox_larr = xor_operation(sbox_p4, ip_array.left_array);
    // printf("XOR with left half: %s\n", sbox_larr);

    char* round_one = swapping(sbox_larr, ip_array.right_array);
    // printf("After swapping (Round 1 output): %s\n", round_one);

    // free some stuff ;)
    free(sbox_p4);
    free(sbox_larr);  // Free sbox_larr after using it in swapping

    // === ROUND 2 ===
    // printf("\n--- ROUND 2 ---\n");
    
    // Step 1: Split round_one output into left and right halves (L1, R1)
    split_array key_split = spliting(round_one, 8);  // Fixed: use 8 instead of size_ip
    // printf("Round 1 output splitting - Left: %s, Right: %s\n", key_split.left_array, key_split.right_array);

    // Step 2: Apply E/P (Expansion/Permutation) on right half R1
    size_of_ep = sizeof(Ep) / sizeof(Ep[0]);
    char *Ep_R2 = pn_operation(key_split.right_array, Ep, size_of_ep);
    // printf("E/P(R): %s\n", Ep_R2);

    // Step 3: XOR E/P(R1) with Key2
    results = xor_operation(key_two, Ep_R2);
    // printf("XOR with Key2: %s\n", results);

    // free some stuff ;)
    free(Ep_R2);

    // Step 4: Apply S-box substitution on XOR result
    new_value = Sbox_operation(results, s_box1, s_box2);
    // printf("S-box output: %s\n", new_value);

    // free some stuff ;)
    free(results);

    // Step 5: Apply P4 permutation on S-box output
    size_of_p4 = sizeof(p4) / sizeof(p4[0]);
    sbox_p4 = pn_operation(new_value, p4, size_of_p4);
    // printf("P4(S-box): %s\n", sbox_p4);

    // free some stuff
    free(new_value);

    // Step 6: XOR P4 result with left half L1
    char* sp4_xor_ls = xor_operation(key_split.left_array, sbox_p4);
    // printf("XOR with left half: %s\n", sp4_xor_ls);

    // Step 7: Combine XOR result with right half R1 (L2 || R1)
    char combine_value[8];
    strcpy(combine_value, sp4_xor_ls);  // Fixed: use strcpy instead of strcat
    strcat(combine_value, key_split.right_array);
    // printf("Combined value: %s\n", combine_value);

    // Step 8: Apply final inverse permutation IP^-1
    int size_of_ip_1 = sizeof(Ip_1) / sizeof(Ip_1[0]);  // Fixed: use Ip_1 size
    char* final_value = pn_operation(combine_value, Ip_1, size_of_ip_1);
    // printf("Final permutation (IP^-1): %s\n", final_value);

    // printf("=== Encryption Complete ===\n\n");

    // Cleanup
    free(sp4_xor_ls);
    free(round_one);
    free(key_one);
    free(key_two);

    return final_value;
}
