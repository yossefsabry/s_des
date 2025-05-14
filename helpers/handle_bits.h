#include <stdint.h>
#include <stddef.h>
#include <stdint.h>



#ifndef READ_BITS
#define READ_BITS


// void read_and_encrypt_bits(const char *input_file, const char *output_file);
// void create_png_from_data(const uint8_t *data, size_t data_len, const char *output_file);
void create_png_from_data(const uint8_t *data, size_t data_len, const char *output_file);
void encrypt_bits_and_save(const char *input_file, const char *output_file);


#endif // READ_BITS
