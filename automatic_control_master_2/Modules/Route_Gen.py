from math import sqrt
import math
import enum


class Route_Gen:

    def __init__(self):

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

    def rotation(self, r, p, d_r, r_s):
        # r:半径　p:now position[0,0](回転の中心　＝　{0,0}) d_r:回転の方向('left','right') r_s:rad/s
        distance = sqrt(p[0] ** 2 + p[1] ** 2)
        d = distance
        p0 = p
        lag = distance - r
        tp = {}  # target position
        td = {}  # target direction
        if lag == 0:
            td = {1, -p[0] / p[1]}
        else:
            if lag < 0:
                d = r + lag
                p0[0] *= d / distance
                p0[1] *= d / distance
            if d_r == 'left':  # 接点を求める
                tp = {r * (p0[0] * r - p0[1] * sqrt(d ** 2 - r ** 2)) / (d ** 2),
                      r * (p0[1] * r + p0[0] * sqrt(d ** 2 - r ** 2)) / (d ** 2)}
            else:
                tp = {r * (p0[0] * r + p0[1] * sqrt(d ** 2 - r ** 2)) / (d ** 2),
                      r * (p0[1] * r - p0[0] * sqrt(d ** 2 - r ** 2)) / (d ** 2)}
            td = {p[0] - tp[0], p[1] - tp[1]}
        tan0 = p[1] / p[0]
        tan1 = math.tan(r_s / 10)
        tan = (tan0 + tan1) / (1 - tan0 * tan1)
        d0 = sqrt(td[0] ** 2 + td[1] ** 2)
        td[0] /= d0
        td[1] /= d0
        return (tan * p[0] - p[1]) / (td[1] - tan * td[0]), td

    def limit_distance(self):

        if( Route_Gen.A_B_distance < 750 ):
            pass

        if( Route_Gen.A_C_distance < 750 ):
            pass

        if( Route_Gen.B_C_distance < 750 ):
            pass

    


class Route(enum):
    Two_One_ready = [-1000, 0]
    
