def image_to_c_array(image_path, output_path):
    with open(image_path, 'rb') as img_file:
        data = img_file.read()

    with open(output_path, 'w') as out_file:
        out_file.write("const unsigned char image_data[] = {\n")
        for i, byte in enumerate(data):
            if i % 12 == 0:
                out_file.write("    ")
            binary_rep = bin(byte)[2:].zfill(8)
            out_file.write(f"{binary_rep}, ")
            if (i + 1) % 12 == 0:
                out_file.write("\n")
        if len(data) % 12 != 0:
            out_file.write("\n")
        out_file.write("};\n")

# Example usage:
image_to_c_array("linux_binguaen.png", "img.txt")

