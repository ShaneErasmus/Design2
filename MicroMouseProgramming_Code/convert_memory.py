#!/usr/bin/env python3
"""
Memory Dump Converter
Converts memory dumps to Intel HEX format with adjusted start address.
"""

import sys
import re
import os

def convert_to_hex(input_file, output_file, original_base_addr, target_base_addr):
    # Parse the original memory dump
    memory_data = {}
    
    with open(input_file, 'r') as f:
        for line in f:
            # Skip empty lines
            if not line.strip():
                continue
                
            # Try to match both formats (with/without line prefix)
            match = re.match(r'(?:(\w+)\s+)?([0-9a-f]{2}(?:\s+[0-9a-f]{2})*)', line.lower())
            if match:
                # If there's an address at the start of the line
                if match.group(1):
                    try:
                        addr = int(match.group(1), 16)
                    except ValueError:
                        continue
                else:
                    # For dumps without address, we need to keep track
                    addr = len(memory_data) * 16
                
                # Extract the bytes
                byte_str = match.group(2)
                bytes_data = [int(b, 16) for b in byte_str.split()]
                
                # Store in our memory map
                for i, b in enumerate(bytes_data):
                    memory_data[addr + i] = b
    
    # Sort addresses to ensure sequential processing
    sorted_addrs = sorted(memory_data.keys())
    if not sorted_addrs:
        print(f"Error: No valid data found in {input_file}")
        return
    
    # Calculate the base address from the data
    base_addr = sorted_addrs[0] & 0xFFFFFFF0  # Round down to nearest 16-byte boundary
    
    # Calculate the offset to apply
    if original_base_addr is None:
        # Try to determine from the data
        for addr in sorted_addrs:
            if (addr & 0xFFFFFFF0) == addr:  # This is a line start address
                original_base_addr = addr
                break
        if original_base_addr is None:
            original_base_addr = base_addr
    
    offset = target_base_addr - original_base_addr
    
    # Create Intel HEX file
    with open(output_file, 'w') as out:
        # Process 16 bytes at a time for Intel HEX records
        current_addr = base_addr
        while current_addr <= max(sorted_addrs):
            # Get bytes for this record
            record_bytes = []
            for i in range(16):
                if current_addr + i in memory_data:
                    record_bytes.append(memory_data[current_addr + i])
                else:
                    record_bytes.append(0xFF)  # Fill with 0xFF for missing bytes
            
            if any(b != 0xFF for b in record_bytes):  # Only output non-empty records
                # Calculate adjusted address
                adjusted_addr = current_addr + offset
                
                # Intel HEX record: :LLAAAATTDD...CC
                # LL = length of data (16)
                # AAAA = address (adjusted)
                # TT = record type (00 for data)
                # DD... = data bytes
                # CC = checksum
                
                record = [16, (adjusted_addr >> 8) & 0xFF, adjusted_addr & 0xFF, 0]
                record.extend(record_bytes)
                
                # Calculate checksum (2's complement of sum of all bytes)
                checksum = (0x100 - (sum(record) & 0xFF)) & 0xFF
                
                # Write the record
                out.write(':' + ''.join(f'{b:02X}' for b in record) + f'{checksum:02X}\n')
            
            current_addr += 16
        
        # Write End Of File record
        out.write(':00000001FF\n')
    
    print(f"Converted {input_file} to {output_file} with adjusted base address: 0x{target_base_addr:08X}")

def main():
    if len(sys.argv) < 2:
        print("Usage: python convert_memory.py <input_file.txt> [original_base_addr] [target_base_addr]")
        sys.exit(1)
    
    input_file = sys.argv[1]
    
    # Default addresses
    original_base_addr = 0x20002a30 if len(sys.argv) <= 2 else int(sys.argv[2], 16)
    target_base_addr = 0x08040000 if len(sys.argv) <= 3 else int(sys.argv[3], 16)
    
    # Generate output filename
    base_name = os.path.splitext(input_file)[0]
    output_file = f"{base_name}_converted.hex"
    
    convert_to_hex(input_file, output_file, original_base_addr, target_base_addr)

if __name__ == "__main__":
    main()