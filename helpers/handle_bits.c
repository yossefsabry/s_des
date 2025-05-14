#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "../run.h"  // Assuming you have SDES encryption in this header

// Function to create PNG file from encrypted data
void create_png_from_data(const uint8_t *data, size_t data_len, const char *output_file) {
    FILE *f = fopen(output_file, "wb");
    if (!f) {
        perror("Failed to open output file");
        return;
    }

    // PNG signature
    uint8_t png_header[] = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
    fwrite(png_header, 1, sizeof(png_header), f);

    // Image dimensions (dummy size based on data_len)
    int width = 100, height = (data_len / 3) / 100;

    // IHDR chunk
    uint8_t ihdr[25] = {0};
    *((uint32_t *)(ihdr + 4)) = htonl(width);
    *((uint32_t *)(ihdr + 8)) = htonl(height);
    ihdr[12] = 8; // Bit depth
    ihdr[13] = 2; // Color type (RGB)

    uint32_t crc = crc32(0, ihdr + 4, 17);
    fwrite("\x00\x00\x00\x0DIHDR", 1, 8, f);
    fwrite(ihdr + 4, 1, 17, f);
    fwrite(&crc, 1, 4, f);

    // IDAT chunk (compress data)
    uLongf compressed_size = compressBound(data_len);
    uint8_t *compressed_data = malloc(compressed_size);

    if (compress(compressed_data, &compressed_size, data, data_len) != Z_OK) {
        fprintf(stderr, "Compression failed\n");
        fclose(f);
        free(compressed_data);
        return;
    }

    fwrite("\x00\x00\x00\x00IDAT", 1, 8, f);
    fwrite(compressed_data, 1, compressed_size, f);
    crc = crc32(0, (const Bytef *)"IDAT", 4);
    crc = crc32(crc, compressed_data, compressed_size);
    fwrite(&crc, 1, 4, f);

    free(compressed_data);

    // IEND chunk
    fwrite("\x00\x00\x00\x00IEND\xAE\x42\x60\x82", 1, 12, f);
    fclose(f);
    printf("Created PNG: %s\n", output_file);
}

// Function to encrypt data bit-by-bit using SDES
void encrypt_bits_and_save(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        perror("Input file error");
        return;
    }

    uint8_t *encrypted_data = malloc(100000);
    size_t data_len = 0;
    char line[1024];

    while (fgets(line, sizeof(line), in)) {
        char binary[9] = {0};
        int bit_count = 0;

        // Convert binary data to encrypted binary data
        for (int i = 0; line[i]; i++) {
            if (line[i] == '0' || line[i] == '1') {
                if (bit_count < 8) {
                    binary[bit_count++] = line[i];
                }
                if (bit_count == 8) {
                    binary[8] = '\0';
                    
                    // Encrypt the binary string using SDES and convert it to integer
                    char *encrypted = run(binary);  // run() should perform SDES encryption on the binary
                    encrypted_data[data_len++] = (uint8_t)strtol(encrypted, NULL, 2);
                    free(encrypted);
                    bit_count = 0;
                }
            }
        }
    }

    fclose(in);

    // Save the encrypted data in binary form to the output file
    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Output file error");
        free(encrypted_data);
        return;
    }

    for (size_t i = 0; i < data_len; i++) {
        fprintf(out, "0b");
        for (int bit = 7; bit >= 0; bit--) {
            fprintf(out, "%d", (encrypted_data[i] >> bit) & 1);
        }
        fprintf(out, ",\n");
    }

    fclose(out);
    free(encrypted_data);

    printf("Encrypted binary data written to %s\n", output_file);
}

