# Calculate total logging time for MicroMouse log packets

# User settings
PACKET_SIZE_BYTES = 1+1+1+(3*2)+2+(2*4)+3+3+1  # Size of MicroMouseLog_t in bytes
TOTAL_LOG_BYTES = 256 * 1024  # 256KB
SAMPLING_RATE_HZ = 25  # Samples per second

# Calculations
num_packets = TOTAL_LOG_BYTES // PACKET_SIZE_BYTES
logging_time_seconds = num_packets / SAMPLING_RATE_HZ
logging_time_minutes = logging_time_seconds / 60
logging_time_hours = logging_time_minutes / 60

print(f"Packet size: {PACKET_SIZE_BYTES} bytes")
print(f"Total log space: {TOTAL_LOG_BYTES} bytes")
print(f"Sampling rate: {SAMPLING_RATE_HZ} Hz")
print(f"Number of packets: {num_packets}")
print(f"Total logging time: {logging_time_seconds:.2f} seconds")
print(f"Total logging time: {logging_time_minutes:.2f} minutes")
print(f"Total logging time: {logging_time_hours:.2f} hours")
