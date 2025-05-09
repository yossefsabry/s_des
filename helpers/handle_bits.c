#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../run.h"

void read_and_print_bits(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");

    if (!in || !out) {
        perror("Failed to open files");
        return;
    }

    fprintf(out, "const unsigned char image_data[] = {\n");

    char line[1024];
    while (fgets(line, sizeof(line), in)) {
        char binary[9] = {0}; // 8 bits + null terminator
        int bit_count = 0;

        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '0' || line[i] == '1') {
                binary[bit_count++] = line[i];
                
                if (bit_count == 8) {
                    binary[8] = '\0';
                    char *encrypted = run(binary);
                    
                    // Verify encryption output is valid
                    if (strlen(encrypted) == 8) {
                        fprintf(out, "0b%s, ", encrypted);
                    } else {
                        fprintf(stderr, "Invalid encryption output: %s\n", encrypted);
                    }
                    
                    free(encrypted);
                    bit_count = 0;
                }
            }
        }
        fprintf(out, "\n");
    }

    fprintf(out, "};\n");
    fclose(in);
    fclose(out);
}
