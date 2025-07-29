import subprocess

# OpenOCD configuration file (update path if needed)
interface_cfg = "stlink.cfg"  # Use your actual config file if different


# Memory dump parameters
start_addr = 0x08040000
dump_size = 256*1024  # 256KB, adjust as needed
output_file = "MicroMouseLog.bin"

# OpenOCD command to dump memory
cmd = [
    "openocd",
    "-f", openocd_cfg,
    "-c", f"init; halt; dump_image {output_file} {start_addr:#x} {dump_size}; exit"
]

print("Running OpenOCD to dump STM32L476Ve memory...")
result = subprocess.run(cmd, capture_output=True, text=True)

if result.returncode == 0:
    print(f"Memory dumped successfully to {output_file}")
else:
    print("OpenOCD failed:")
    print(result.stderr)