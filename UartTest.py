import time
import serial

ser1 = serial.Serial(

    port='/dev/ttyAMA3',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1,
    dsrdtr=False
)

data = 1
 
while True:
    
    degree = input()
    if degree.isdigit():
        ser1.write(degree.encode())
          
 
