import serial
import time


SERIALPORT = "/dev/ttyUSB0"
BAUDRATE = 115200

ser = serial.Serial(SERIALPORT, BAUDRATE)
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE

ser.timeout = None
ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = False
ser.writeTimeout = 0


print( "Starting up serial monitor")

try:
    ser.open()
except Exception as e:
    print ("Exception: Opening serial port: " + str(e))
    
if ser.isOpen():
    try:
        ser.flushInput()
        ser.flushOutput()
        ser.write("1\r\n".encode('ascii'))
        print("write data: 1")
        time.sleep(0.5)
        numberOfLine = 0
        while True:
            response = ser.readline().decode('ascii')
            print("read data: " + response)
            numberOfLine = numberOfLine + 1
            if (numberOfLine >= 5):
                break
        ser.close()
    except Exception as e:
        print ("Error communicating...: " + str(e))
else:
    print("Cannot open serial port.")