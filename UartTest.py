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

def send_String(degree):
    ser1.write(degree.encode())