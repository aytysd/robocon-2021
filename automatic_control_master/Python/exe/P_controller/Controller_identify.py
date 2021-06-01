from . import General_command

class controller():
    def __init__(self):
        Rxdata = []

        
    def _identify_stop_button(self):
        stop_button = [128, 64, 0, 64, 64, 64, 64, 64]
        count = 0
        
        for i in range(8):
            if( controller.Rxdata[i] == stop_button[i]):
                count += 1
        
        if( count == 8 ):
            return General_command.E_move_status.STOP

