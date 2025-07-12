import os
import re
import random
import struct
import zlib
from binascii import hexlify

def create_png_from_image_data(image_data, output_path, width=100, height=100):
    """Create PNG with proper structure from image data"""
    with open(output_path, 'wb') as f:
        # PNG signature
        f.write(b'\x89PNG\r\n\x1a\n')
        
        # IHDR chunk
        ihdr_data = struct.pack('>IIBBBBB', width, height, 8, 2, 0, 0, 0)
        ihdr_chunk = b'IHDR' + ihdr_data
        f.write(struct.pack('>I', 13))  # Length
        f.write(ihdr_chunk)
        f.write(struct.pack('>I', zlib.crc32(ihdr_chunk) & 0xffffffff))
        
        # IDAT chunk (compress the image data)
        compressed_data = zlib.compress(image_data)
        idat_chunk = b'IDAT' + compressed_data
        f.write(struct.pack('>I', len(compressed_data)))  # Length
        f.write(idat_chunk)
        f.write(struct.pack('>I', zlib.crc32(idat_chunk) & 0xffffffff))
        
        # IEND chunk
        iend_chunk = b'IEND'
        f.write(struct.pack('>I', 0))  # Length
        f.write(iend_chunk)
        f.write(struct.pack('>I', zlib.crc32(iend_chunk) & 0xffffffff))

def analyze_data(byte_data):
    """Check if data is compressed or encrypted"""
    # PNG signature check
    png_sig = b'\x89PNG\r\n\x1a\n'
    is_png = byte_data.startswith(png_sig)
    
    # Zlib compression check (look for zlib header)
    is_compressed = False
    if len(byte_data) > 2:
        zlib_header = byte_data[:2]
        is_compressed = (zlib_header[0] == 0x78 and 
                        zlib_header[1] in (0x01, 0x5E, 0x9C, 0xDA))

    return {
        'is_png': is_png,
        'is_compressed': is_compressed,
        'size': len(byte_data),
        'header': hexlify(byte_data[:8]).decode('utf-8')
    }

def process_image_data(byte_data):
    """Handle different data types"""
    analysis = analyze_data(byte_data)
    print(f"Data Analysis:\n"
          f"- Size: {analysis['size']} bytes\n"
          f"- Header: {analysis['header']}\n"
          f"- Is PNG: {'Yes' if analysis['is_png'] else 'No'}\n"
          f"- Is Compressed: {'Yes' if analysis['is_compressed'] else 'No'}")

    if analysis['is_compressed']:
        try:
            decompressed = zlib.decompress(byte_data)
            print(f"Decompressed {len(byte_data)} → {len(decompressed)} bytes")
            return decompressed
        except zlib.error:
            print("Decompression failed - using raw data")
            return byte_data
    return byte_data

def c_array_to_image(c_array_file, output_folder):
    os.makedirs(output_folder, exist_ok=True)
    
    with open(c_array_file, 'r') as file:
        content = file.read()
    
    # Extract binary data (0bxxxxxxxx format)
    binaries = re.findall(r'0b([01]{8})', content)
    if not binaries:
        print("Error: No binary data found")
        return
    
    # Convert binary strings to bytes
    byte_data = bytes(int(b, 2) for b in binaries)
    print(f"Extracted {len(byte_data)} bytes from encrypted data")
    
    # Process the data
    processed_data = process_image_data(byte_data)
    
    # Create output filename
    output_path = os.path.join(output_folder, f"image_{random.randint(1000,9999)}.png")
    
    # Calculate reasonable dimensions based on data size
    # Assuming RGB format (3 bytes per pixel)
    total_pixels = len(processed_data) // 3
    if total_pixels > 0:
        # Try to make it roughly square
        width = int(total_pixels ** 0.5)
        height = (total_pixels + width - 1) // width  # Ceiling division
    else:
        width, height = 100, 100
    
    print(f"Creating PNG with dimensions: {width}x{height}")
    
    # Create PNG from the processed data
    create_png_from_image_data(processed_data, output_path, width, height)
    
    print(f"\nFinal image saved to {output_path}")
    print(f"Final size: {os.path.getsize(output_path)} bytes")

if __name__ == "__main__":
    c_array_to_image("./img_encryption.txt", "./outputs/")
