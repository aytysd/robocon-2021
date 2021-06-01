import serial
import time
import sys
import os

from Python.exe import P_controller

#sys.path.append("C:\Users\Ayato Yoshida\robocon\robocon_2021\automatic_control_master\Python\exe\P_controller")

def main():
    pass

if __name__ == "__main__":


    controller = P_controller.Controller_identify.controller()

    controller.identify_stop_button()
 #   os.chdir("Python")
    currentdir = os.getcwd()

    print(currentdir)
    print("lets go")

    print(sys.path)
    main()




