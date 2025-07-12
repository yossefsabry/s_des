#!/usr/bin/env python3
"""
Test script for the S-DES image encryption workflow
"""

import os
import sys

def test_image_conversion():
    """Test the complete image conversion workflow"""
    print("=== Testing S-DES Image Encryption Workflow ===\n")
    
    # Step 1: Convert image to binary (excluding PNG headers)
    print("Step 1: Converting image to binary (excluding PNG headers)...")
    try:
        from convert_img_binary import image_to_c_array
        image_to_c_array("linux_binguaen.png", "img.txt")
        print("✓ Image converted to binary successfully\n")
    except Exception as e:
        print(f"✗ Error converting image: {e}")
        return False
    
    # Step 2: Check if img.txt was created
    if not os.path.exists("img.txt"):
        print("✗ img.txt file not found")
        return False
    
    print("Step 2: Checking binary file...")
    with open("img.txt", "r") as f:
        content = f.read()
        lines = content.split('\n')
        print(f"✓ Binary file created with {len(lines)} lines")
    
    # Step 3: Simulate encryption (this would normally be done by the C program)
    print("\nStep 3: Simulating encryption process...")
    print("(In real workflow, this is done by the C program)")
    
    # Step 4: Test binary to image conversion
    print("\nStep 4: Testing binary to image conversion...")
    try:
        from convert_binary_img import c_array_to_image
        c_array_to_image("img.txt", "./outputs/")
        print("✓ Image reconstruction completed\n")
    except Exception as e:
        print(f"✗ Error reconstructing image: {e}")
        return False
    
    print("=== Test Complete ===")
    print("Check the outputs/ folder for the reconstructed image")
    return True

if __name__ == "__main__":
    # Ensure we're in the right directory
    if not os.path.exists("linux_binguaen.png"):
        print("Error: linux_binguaen.png not found in current directory")
        print("Please run this script from the img_operation/src/ directory")
        sys.exit(1)
    
    success = test_image_conversion()
    if success:
        print("\n✓ All tests passed!")
    else:
        print("\n✗ Some tests failed!")
        sys.exit(1) 