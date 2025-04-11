
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* swapping(char *key_one, char* key_two){
    int len = strlen(key_one);
    char* results = (char*)malloc( (len*2)  * sizeof(char));
    if (results == NULL) { // if error happend in malloc
        perror("Memory allocation failed");
        return results;
    }

    strcat(results, key_two);
    strcat(results, key_one);

    return results;
};
