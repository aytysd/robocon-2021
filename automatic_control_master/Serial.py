import serial
import time


def Serial_A():
    SERIALPORT = "COM3"
    BAUDRATE = 115200

    ser = serial.Serial(SERIALPORT, BAUDRATE)
    ser.bytesize = serial.EIGHTBITS

    Rxdata = ser.read()
    Rxdata = int.from_bytes(Rxdata, "big")

    print(Rxdata)

    return Rxdata
