import sys

def trim_bin(input_file, output_file, offset=0x00000008):
    with open(input_file, 'rb') as f:
        f.seek(offset)
        data = f.read()
    with open(output_file, 'wb') as f:
        f.write(data)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python trim_bin.py <input.bin> <output.bin>")
        sys.exit(1)
    trim_bin(sys.argv[1], sys.argv[2])