from math import sqrt
import enum


class Route_Gen:

    def __init__(self):

        g = 1
        
        A_X = 0
        A_Y = 0
        B_X = 0
        B_Y = 0
        C_X = 0
        C_Y = 0

        A_B_distance = 0
        A_C_distance = 0
        B_C_distance = 0

    def get_distance(self):

        Route_Gen.A_B_distance = sqrt( Route_Gen.A_X**2 + Route_Gen.A_Y**2 )
        Route_Gen.A_C_distance = sqrt( Route_Gen.A_X**2 + Route_Gen.A_Y**2 )
        Route_Gen.B_C_distance = sqrt( Route_Gen.A_X**2 + Route_Gen.A_Y**2 )


    def limit_distance(self):

        if( Route_Gen.A_B_distance < 750 ):
            pass

        if( Route_Gen.A_C_distance < 750 ):
            pass

        if( Route_Gen.B_C_distance < 750 ):
            pass

    


class Route(enum):
    Two_One_ready = [-1000, 0]
    
