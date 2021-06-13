import serial
import time
import sys
import os
#import P_controller
import serial
import time
from serial.tools.list_ports import comports


sys.path.append("C:\\Users\\Ayato Yoshida\\robocon\\robocon_2021\\automatic_control_master")

from . import Serial

#sys.path.append("C:\Users\Ayato Yoshida\robocon\robocon_2021\automatic_control_master\Python\exe\P_controller")

def main():
    SERIALPORT = 'COM3'
    BAUDRATE = 115200

    ser = serial.Serial("COM3", 115200)#port='COM3', baudrate=115200, parity=serial.PARITY_NONE)
    line = 'ayato'

    print(line)

    line = ser.read()
    int_data = int.from_bytes(line, 'big')
    print(int_data)
    ser.close()

    print(' ayato')

if __name__ == "__main__":
    print('ayato')
    a = comports()
    print(a)

    list = comports()
    connected = []
    for element in list:
        connected.append(element.device)
    print("Connected COM ports: " + str(connected)) 

    time.sleep(2)
    
    while(True):
        
        # os.chdir("C:\\Users\\Ayato Yoshida\\robocon\\robocon_2021\\automatic_control_master\\exe")
        print(os.getcwd())
        Serial.Serial_A
        #main()