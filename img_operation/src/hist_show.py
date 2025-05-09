import os
import re
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def create_image_histograms(original_img_path, encrypted_img_path, output_folder):
    """
    Create comparative histograms for original and encrypted images with both images displayed
    
    Args:
        original_img_path: Path to the original image file
        encrypted_img_path: Path to the encrypted image file
        output_folder: Folder to save histogram plots
    """
    
    # Create output directory if it doesn't exist
    os.makedirs(output_folder, exist_ok=True)
    
    # Create figure with 4 subplots (2 images + 2 histograms)
    plt.figure(figsize=(16, 8))
    
    # Load and process original image
    try:
        original_img = Image.open(original_img_path)
        original_arr = np.array(original_img)
        
        # Display original image
        plt.subplot(2, 2, 1)
        plt.imshow(original_img)
        plt.title('Original Image')
        plt.axis('off')
        
        # Original image histogram
        plt.subplot(2, 2, 3)
        if len(original_arr.shape) == 3:  # Color image
            colors = ('red', 'green', 'blue')
            for i, color in enumerate(colors):
                hist = np.histogram(original_arr[:,:,i], bins=256, range=(0,256))
                plt.plot(hist[1][:-1], hist[0], color=color, alpha=0.7)
            plt.title('Original Image Histogram (RGB)')
        else:  # Grayscale
            hist = np.histogram(original_arr, bins=256, range=(0,256))
            plt.plot(hist[1][:-1], hist[0], color='black')
            plt.title('Original Image Histogram (Grayscale)')
        plt.xlabel('Pixel Value')
        plt.ylabel('Frequency')
        plt.grid(True, alpha=0.3)
        
    except Exception as e:
        print(f"Error processing original image: {e}")
        plt.subplot(2, 2, 1)
        plt.text(0.5, 0.5, 'Original Image Load Failed', ha='center', va='center')
        plt.axis('off')
        plt.subplot(2, 2, 3)
        plt.text(0.5, 0.5, 'Histogram Unavailable', ha='center', va='center')
    
    # Load and process encrypted image
    try:
        encrypted_img = Image.open(encrypted_img_path)
        encrypted_arr = np.array(encrypted_img)
        
        # Display encrypted image
        plt.subplot(2, 2, 2)
        plt.imshow(encrypted_img, cmap='gray' if len(encrypted_arr.shape) == 2 else None)
        plt.title('Encrypted Image')
        plt.axis('off')
        
        # Encrypted image histogram
        plt.subplot(2, 2, 4)
        if len(encrypted_arr.shape) == 3:  # Color
            colors = ('red', 'green', 'blue')
            for i, color in enumerate(colors):
                hist = np.histogram(encrypted_arr[:,:,i], bins=256, range=(0,256))
                plt.plot(hist[1][:-1], hist[0], color=color, alpha=0.7)
            plt.title('Encrypted Image Histogram (RGB)')
        else:  # Grayscale
            hist = np.histogram(encrypted_arr, bins=256, range=(0,256))
            plt.plot(hist[1][:-1], hist[0], color='black')
            plt.title('Encrypted Image Histogram (Grayscale)')
        plt.xlabel('Pixel Value')
        plt.ylabel('Frequency')
        plt.grid(True, alpha=0.3)
        
    except Exception as e:
        print(f"Error processing encrypted image: {e}")
        plt.subplot(2, 2, 2)
        plt.text(0.5, 0.5, 'Encrypted Image Load Failed', ha='center', va='center')
        plt.axis('off')
        plt.subplot(2, 2, 4)
        plt.text(0.5, 0.5, 'Histogram Unavailable', ha='center', va='center')
    
    # Save and show
    plt.tight_layout()
    output_path = os.path.join(output_folder, 'image_histograms_comparison.png')
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    plt.show()
    print(f"Comparative analysis saved to {output_path}")

# Example usage:
create_image_histograms(
    original_img_path='./linux_binguaen.png',
    encrypted_img_path='./outputs/img_5972.png',
    output_folder='./analysis_results/'
)
