from math import sqrt


class Route_Gen:

    def __init__(self):

        A_X = 0
        A_Y = 0
        B_X = 0
        B_Y = 0
        C_X = 0
        C_Y = 0

    def get_distance(self):

        A_B_distance = sqrt( Route_Gen.A_X**2 + Route_Gen.A_Y**2 )
        A_C_distance = sqrt( Route_Gen.A_X**2 + Route_Gen.A_Y**2 )
        B_C_distance = sqrt( Route_Gen.A_X**2 + Route_Gen.A_Y**2 )

