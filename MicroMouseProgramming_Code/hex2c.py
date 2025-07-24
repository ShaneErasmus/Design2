#!/usr/bin/env python3
import sys
import os

def hex2c_array(hex_file, output_file, array_name):
    try:
        with open(hex_file, 'r') as f:
            hex_data = f.readlines()
        
        # Parse Intel HEX format
        data_bytes = []
        base_address = 0
        for line in hex_data:
            line = line.strip()
            if line.startswith(':'):
                # Remove the colon
                line = line[1:]
                # Byte count (first byte)
                byte_count = int(line[0:2], 16)
                # Address (next two bytes)
                address = int(line[2:6], 16)
                # Record type (next byte)
                record_type = int(line[6:8], 16)
                
                # Data record
                if record_type == 0:
                    # Extract data bytes
                    for i in range(0, byte_count):
                        data_bytes.append(int(line[8 + i*2:10 + i*2], 16))
                # End of file record
                elif record_type == 1:
                    break
                # Extended Segment Address record
                elif record_type == 2:
                    segment = int(line[8:12], 16)
                    base_address = segment << 4
                # Extended Linear Address record
                elif record_type == 4:
                    base_address = int(line[8:12], 16) << 16
        
        # Generate C array
        with open(output_file, 'w') as f:
            f.write(f"/* Auto-generated C array from {os.path.basename(hex_file)} */\n")
            f.write(f"#include <stdint.h>\n\n")
            f.write(f"#define {array_name.upper()}_SIZE {len(data_bytes)}\n\n")
            f.write(f"const uint8_t {array_name}[{array_name.upper()}_SIZE] __attribute__((section(\".preformatted_flash\"))) = {{\n")
            
            # Write data bytes in rows of 16 bytes
            for i in range(0, len(data_bytes), 16):
                row = data_bytes[i:i+16]
                hex_vals = [f"0x{b:02X}" for b in row]
                f.write("    " + ", ".join(hex_vals))
                if i + 16 < len(data_bytes):
                    f.write(",")
                f.write("\n")
            
            f.write("};\n")
        
        print(f"Successfully converted {hex_file} to C array in {output_file}")
        
    except Exception as e:
        print(f"Error: {e}")
        return False
    
    return True

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python hex2c.py <input_hex_file> <output_c_file> <array_name>")
        sys.exit(1)
    
    hex_file = sys.argv[1]
    output_file = sys.argv[2]
    array_name = sys.argv[3]
    
    if not hex2c_array(hex_file, output_file, array_name):
        sys.exit(1)
