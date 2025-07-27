import sys
import os

def expand_bin_to_size(input_path, output_path, target_size):
    with open(input_path, 'rb') as f:
        data = f.read()
    current_size = len(data)
    if current_size >= target_size:
        print(f"File is already {current_size} bytes, no expansion needed.")
        with open(output_path, 'wb') as f:
            f.write(data)
        return
    # Pad with 0x00s
    padding = b'\x00' * (target_size - current_size)
    with open(output_path, 'wb') as f:
        f.write(data + padding)
    print(f"Expanded {input_path} from {current_size} to {target_size} bytes.")

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python expand_bin.py <input.bin> <output.bin> <target_size>")
        sys.exit(1)
    input_bin = sys.argv[1]
    output_bin = sys.argv[2]
    try:
        size = int(sys.argv[3])
    except ValueError:
        print("Target size must be an integer.")
        sys.exit(1)
    expand_bin_to_size(input_bin, output_bin, size)
