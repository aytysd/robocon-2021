/*
 * Init_Move.hpp
 *
 *  Created on: 14 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(execute initial movement for each robot)
 *
 *@Input(the robot name you want to activate( E_robot_name:: ))in( E_robot_name robot )of( void init_move( E_robot_name robot ))
 *
 *@Output(value)to(where)
 *
 *@Attention_(description)
 *
 *@Usertouch( void init_move( E_robot_name robot ) )
 *
 */
#ifndef INC_INIT_MOVE_HPP_
#define INC_INIT_MOVE_HPP_

#include "General_command.hpp"

class Init_Move{
public:
	void init_move(E_robot_name robot);

	static bool SBDBT_OK;

private:
	void SBDBT_Init( E_robot_name robot );
	void Initialize(E_robot_name robot);
};



#endif /* INC_INIT_MOVE_HPP_ */
