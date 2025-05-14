
import os
import re
import random
import zlib


def c_array_to_image(c_array_file, output_folder):
    os.makedirs(output_folder, exist_ok=True)
    
    with open(c_array_file, 'r') as file:
        content = file.read()
    
    # Extract all 8-bit binary strings (e.g., 0b10001001)
    binaries = re.findall(r'0b([01]{8})', content)
    
    if not binaries:
        print("Error: No binary data found in input file")
        return
    
    # Convert binary strings to bytes
    encrypted_bytes = bytes(int(b, 2) for b in binaries)
    
    # Debug output
    print(f"Found {len(binaries)} bytes")
    print("First 8 bytes (encrypted):", encrypted_bytes[:8].hex(' '))
    
    # ===== KEY FIXES =====
    # 1. Check if data is already a valid PNG
    if encrypted_bytes.startswith(b'\x89PNG'):
        print("Data is already a valid PNG, writing directly...")
        output_path = os.path.join(output_folder, f"image_{random.randint(1000,9999)}.png")
        with open(output_path, 'wb') as f:
            f.write(encrypted_bytes)
        return
    
    # 2. If data is compressed (small size), decompress first
    try:
        # Estimate decompressed size (adjust multiplier as needed)
        decompressed_size = len(encrypted_bytes) * 10  
        decompressed_data = zlib.decompress(encrypted_bytes)
        print(f"Decompressed {len(encrypted_bytes)} → {len(decompressed_data)} bytes")
        byte_data = decompressed_data
    except zlib.error:
        print("Data is not compressed, using raw bytes")
        byte_data = encrypted_bytes
    
    # 3. Ensure PNG header exists
    png_header = b'\x89PNG\r\n\x1a\n'
    if not byte_data.startswith(png_header):
        print("Adding PNG header to data...")
        byte_data = png_header + byte_data
    
    # Generate output filename
    output_path = os.path.join(output_folder, f"image_{random.randint(1000,9999)}.png")
    
    # Create PNG from the processed data
    create_png_from_data(byte_data, output_path)
    
    print(f"Image saved to {output_path}")
    print(f"Final size: {os.path.getsize(output_path)} bytes")
