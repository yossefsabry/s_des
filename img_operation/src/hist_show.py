import os
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

def create_histograms_only(original_img_path, encrypted_img_path, output_folder):
    """
    Create ONLY histograms for original and encrypted images (no image display)
    """
    os.makedirs(output_folder, exist_ok=True)
    
    plt.figure(figsize=(12, 6))  # Wider figure for side-by-side histograms
    
    # Process original image
    try:
        original_img = Image.open(original_img_path)
        original_arr = np.array(original_img)
        
        plt.subplot(1, 2, 1)  # Left histogram
        if len(original_arr.shape) == 3:  # Color
            for i, color in enumerate(('red', 'green', 'blue')):
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
        print(f"Original image error: {e}")
        plt.subplot(1, 2, 1)
        plt.text(0.5, 0.5, 'Original Histogram Failed', ha='center', va='center')
    
    # Process encrypted image with raw data fallback
    try:
        encrypted_img = Image.open(encrypted_img_path)
        encrypted_arr = np.array(encrypted_img)
    except:
        print("Standard image load failed, trying raw data...")
        try:
            with open(encrypted_img_path, 'rb') as f:
                encrypted_data = np.frombuffer(f.read(), dtype=np.uint8)
            encrypted_arr = encrypted_data[:100*100*3].reshape((100, 100, 3))  # Adjust dimensions as needed
        except Exception as e:
            print(f"Encrypted image load failed: {e}")
            plt.subplot(1, 2, 2)
            plt.text(0.5, 0.5, 'Encrypted Histogram Failed', ha='center', va='center')
            plt.tight_layout()
            plt.savefig(os.path.join(output_folder, 'histograms_only.png'))
            plt.close()
            return
    
    # Plot encrypted histogram
    plt.subplot(1, 2, 2)  # Right histogram
    if len(encrypted_arr.shape) == 3:  # Color
        for i, color in enumerate(('red', 'green', 'blue')):
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
    
    plt.tight_layout()
    output_path = os.path.join(output_folder, 'histograms_only.png')
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    plt.close()
    print(f"Histograms saved to {output_path}")

# Example usage
create_histograms_only(
    original_img_path='./linux_binguaen.png',
    encrypted_img_path='./outputs/image_6964.png',
    output_folder='./analysis_results/'
)
