import zlib

def image_to_binary_file(image_path, output_path):
    with open(image_path, 'rb') as img_file:
        data = img_file.read()

    # Check if it's a PNG file
    if data.startswith(b'\x89PNG\r\n\x1a\n'):
        print("PNG file detected, extracting image data...")

        idat_start = data.find(b'IDAT')
        if idat_start == -1:
            print("Error: No IDAT chunk found in PNG")
            return

        data_start = idat_start + 4  # Skip 'IDAT'
        idat_end = data.find(b'IEND')
        if idat_end == -1:
            print("Error: No IEND chunk found in PNG")
            return

        compressed_data = data[data_start:data_start + (idat_end - data_start - 8)]

        try:
            image_data = zlib.decompress(compressed_data)
            print(f"Extracted {len(image_data)} bytes of image data")
        except zlib.error as e:
            print(f"Error decompressing image data: {e}")
            return
    else:
        print("Not a PNG file, using raw data...")
        image_data = data

    # Write only the binary digits, no 0b, no commas, no comments
    with open(output_path, 'w') as out_file:
        for byte in image_data:
            binary_rep = bin(byte)[2:].zfill(8)
            out_file.write(binary_rep)
        out_file.write('\n')

if __name__ == "__main__":
    image_to_binary_file("linux_binguaen.png", "img.txt")

