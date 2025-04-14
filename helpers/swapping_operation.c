
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* swapping(char *key_one, char* key_two){
    int len = strlen(key_one);
    char* results = (char*)malloc( ((len - 1) * 2)  * sizeof(char));

    // if you don't know what is this it's the best thing in c
    // it's over write any data and remove in length of the array
    // because it's there is always dummy data thanks c ;( ;( ;(
    results[0] = '\0';

    if (results == NULL) { // if error happened in malloc
        perror("Memory allocation failed");
        return results;
    }

    strcat(results, key_two);
    strcat(results, key_one);

    return results;
};
