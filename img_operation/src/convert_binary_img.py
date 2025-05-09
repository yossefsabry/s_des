import os
import re
import random
import zlib
import struct

def create_png_from_data(byte_data, output_path):
    """Create a valid PNG file from raw byte data"""
    # PNG signature
    png_header = b'\x89PNG\r\n\x1a\n'
    
    # Create IHDR chunk (simplified - you may need to adjust width/height)
    width = 100  # Default width - adjust as needed
    height = 100  # Default height - adjust as needed
    ihdr = struct.pack('>I', width) + struct.pack('>I', height) + b'\x08\x02\x00\x00\x00'
    ihdr_chunk = b'IHDR' + ihdr
    ihdr_crc = struct.pack('>I', zlib.crc32(ihdr_chunk) & 0xffffffff)
    ihdr_chunk = struct.pack('>I', len(ihdr)) + ihdr_chunk + ihdr_crc
    
    # Create IDAT chunk with your data
    idat_data = byte_data
    # Compress the data (required for PNG)
    compressed_data = zlib.compress(idat_data)
    idat_chunk = b'IDAT' + compressed_data
    idat_crc = struct.pack('>I', zlib.crc32(idat_chunk) & 0xffffffff)
    idat_chunk = struct.pack('>I', len(compressed_data)) + idat_chunk + idat_crc
    
    # IEND chunk (PNG end marker)
    iend_chunk = b'\x00\x00\x00\x00IEND\xae\x42\x60\x82'
    
    # Combine all parts
    png_data = png_header + ihdr_chunk + idat_chunk + iend_chunk
    
    with open(output_path, 'wb') as f:
        f.write(png_data)

def c_array_to_image(c_array_file, output_folder):
    os.makedirs(output_folder, exist_ok=True)
    
    with open(c_array_file, 'r') as file:
        content = file.read()
    
    binaries = re.findall(r'0b([01]{8})', content)
    byte_data = bytes(int(b, 2) for b in binaries)
    
    # Debug output
    print(f"Total bytes: {len(byte_data)}")
    print(f"First 16 bytes: {byte_data[:16].hex(' ')}")
    if len(byte_data) > 16:
        print(f"Last 16 bytes: {byte_data[-16:].hex(' ')}")
    
    rand_num = random.randint(1000, 9999)
    output_path = os.path.join(output_folder, f"img_{rand_num}.png")
    
    if byte_data.startswith(b'\x89PNG'):
        print("Data already has PNG header")
        with open(output_path, 'wb') as img_file:
            img_file.write(byte_data)
    else:
        print("Creating new PNG structure from data")
        create_png_from_data(byte_data, output_path)
    
    print(f"Image written to {output_path}")
    print(f"File size: {os.path.getsize(output_path)} bytes")

if __name__ == "__main__":
    c_array_to_image("./img_encryption.txt", "./outputs/")
