import serial
import time
import os
from serial.tools.list_ports import comports

class A_connection:

    def __init__(self):
        X_pos = 0
        Y_pos = 0
        direction = 0
        Move_status = 0
        time.sleep(2)
        


    def Serial_A_read(self):

        print("your are using Serial_A")

        SERIALPORT = "COM6"
        BAUDRATE = 115200

        ser = serial.Serial(SERIALPORT, BAUDRATE)
        ser.bytesize = serial.EIGHTBITS

        Rxdata = ser.read()
        Rxdata = int.from_bytes(Rxdata, "big")

        print(Rxdata)

        return Rxdata


    def Serial_A_write(self):

        print( "you are using Serial_A ")

        SERIALPORT = "COM6"
        BAUDRATE = 115200

        ser = serial.Serial(SERIALPORT, BAUDRATE)
        ser.bytesize = serial.EIGHTBITS

        Rxdata = ser.write( 123 )





    def check_connection(self):

        print("you are using check_connection")

        list = comports()
        connected = []
        for element in list:
            connected.append(element.device)
        print("Connected COM ports: " + str(connected))

        if ( "COM3" in connected ) == True:
            return True


    
