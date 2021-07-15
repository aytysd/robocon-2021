from Modules.Serial_A import A_connection
import time

def main():
    pass


if __name__ == "__main__":
    main()
    a_connection = A_connection()
    while(1):
        a_connection.Serial_A_write()
        #time.sleep( 1 )
