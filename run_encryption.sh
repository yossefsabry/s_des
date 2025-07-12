#!/bin/bash

echo "=== S-DES Image Encryption Workflow ==="
echo ""

# Step 1: Build the C program
echo "Step 1: Building S-DES encryption program..."
make clean
make
if [ $? -ne 0 ]; then
    echo "Error: Build failed!"
    exit 1
fi
echo "✓ Build successful"
echo ""

# Step 2: Convert image to binary (excluding PNG headers)
echo "Step 2: Converting image to binary..."
cd img_operation/src
python3 convert_img_binary.py
if [ $? -ne 0 ]; then
    echo "Error: Image conversion failed!"
    exit 1
fi
echo "✓ Image converted to binary"
echo ""

# Step 3: Run S-DES encryption
echo "Step 3: Running S-DES encryption..."
cd ../..
./s_des
if [ $? -ne 0 ]; then
    echo "Error: Encryption failed!"
    exit 1
fi
echo "✓ Encryption completed"
echo ""

# Step 4: Convert encrypted binary back to image
echo "Step 4: Converting encrypted binary to image..."
cd img_operation/src
python3 convert_binary_img.py
if [ $? -ne 0 ]; then
    echo "Error: Image reconstruction failed!"
    exit 1
fi
echo "✓ Image reconstruction completed"
echo ""

echo "=== Workflow Complete ==="
echo "Check img_operation/src/outputs/ for the encrypted image"
echo "Original image: img_operation/src/linux_binguaen.png" 