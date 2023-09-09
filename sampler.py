# Imports
from time import time
from machine import Timer, UART

# Constants
RESET_RATE_S = 60
SAMPLE_RATE_MS = 1000
UART_BAUD_RATE = 2400
UART_TYPE = 1

try:
    # Global variables
    bytes_read = 0
    last_time_read = time()
    
    # Functions
    def rst_stats(argv):
        global bytes_read
        global last_time_read
        
        bytes_read = 0
        last_time_read = time()
        print("DATA RESET")
    
    def shw_stats(argv):
        global bytes_read
        global last_time_read
        
        current_time = time()
        if current_time == last_time_read:
            return
        
        speed = float(bytes_read / (current_time - last_time_read))
        print(f'{speed:.2f}')
    
    # Global objects
    uart = UART(UART_TYPE)
    uart.init(UART_BAUD_RATE, bits = 8, parity = None, stop = 1)
    
    rstimer = Timer()
    rstimer.init(mode = Timer.PERIODIC, period = (RESET_RATE_S * 1000), callback = rst_stats)
    
    sttimer = Timer()
    sttimer.init(mode = Timer.PERIODIC, period = SAMPLE_RATE_MS, callback = shw_stats)
    
    while True:
        # Read bytes from the UART
        if rbytes := uart.read(1):
            bytes_read += 1

except KeyboardInterrupt:
    print("Requested program halt")

except Exception as e:
    print("Catched exception: {e}")
    
except:
    print("An unknown exception ocurred")
