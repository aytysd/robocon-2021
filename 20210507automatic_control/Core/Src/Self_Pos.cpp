/*
 * Self_Pos.cpp
 *
 *  Created on: 7 May 2021
 *
 *@Author: Ayato Yoshida
 *
 *@Purpose_of_this_class:(description_about_thisclass)
 *
 *@Input(value)in(variable)of(functionname)
 *
 *@Output(value)to(where)
 *
 *@Attention_(description)
 *
 *@Usertouch(functionname)&_(variable_name)
 *
 */

#include <General_command.hpp>
#include "main.h"
#include "Self_Pos.hpp"
#include "bno055.h"
#include "stdio.h"
#include <math.h>
#include "Error_Handling.hpp"
#include "LED.hpp"
#include "PWM.hpp"
#include "Gyro.hpp"
#include "Function.hpp"

int Self_Pos::Self_Pos_X = 0; //(mm)
int Self_Pos::Self_Pos_Y = 0; //(mm)

int Self_Pos::out_angle = 0;
//----------------------------------------------------------------------
//Self_Pos* self_pos = new Self_Pos();

int Self_Pos::get_Self_Pos_X() {
	return this->Self_Pos_X;
}

int Self_Pos::get_Self_Pos_Y() {
	return this->Self_Pos_Y;
}

void Self_Pos::add_Self_Pos(int add_x, int add_y) {
	this->Self_Pos_Y += add_x;
	this->Self_Pos_X += add_y;

}

void Self_Pos::set_initial_pos(E_robot_name robot) {
	switch (robot) {
	case E_robot_name::A:

		this->Self_Pos_X = -2643;
		this->Self_Pos_Y = 2643;

		break;
	case E_robot_name::B:

		this->Self_Pos_X = -2643;
		this->Self_Pos_Y = -2643;

		break;
	case E_robot_name::C:

		this->Self_Pos_X = 2643;
		this->Self_Pos_Y = -2643;

		break;

	case E_robot_name::NONE:

		this->Self_Pos_X = 2643;
		this->Self_Pos_Y = -2643;

		break;
	}

}
//delete self_pos;
//-------------------------------------
//Self_Pos* self_pos = new Self_Pos();
void Self_Pos::update_self_pos(void) {
	Gyro *gyro = new Gyro();

	int d1 = -2 * OD_RADIUS * M_PI
			* ((double) this->encoder_read_5() / (double) 2048); //encoder5_moving distance(mm) 55.5=wheel radius 2048=encoder resolution
	int d2 = 2 * OD_RADIUS * M_PI
			* ((double) this->encoder_read_2() / (double) 2048); //encoder5_moving distance(mm) 55.5=wheel radius 2048=encoder resolution

	this->Self_Pos_X += d1
			* cos((double) gyro->get_direction(&hi2c1) * M_PI / (double) 180)
			- d2
					* sin(
							(double) gyro->get_direction(&hi2c1) * M_PI
									/ (double) 180); //X_coordinate
	this->Self_Pos_Y += d1
			* sin((double) gyro->get_direction(&hi2c1) * M_PI / (double) 180)
			+ d2
					* cos(
							(double) gyro->get_direction(&hi2c1) * M_PI
									/ (double) 180); //Y_coordinate

	delete gyro;
}
//delete self_pos;
//---------------------------------------
void Self_Pos::update_self_pos_ToF() {
	ToF *tof = new ToF();
	this->Self_Pos_X;
	this->Self_Pos_Y;
	delete tof;
}
//---------------------------------------
int Self_Pos::encoder_read_5(void) {
	static int prev_encoder_value = 0;
	uint32_t enc_buff_5 = TIM5->CNT;
	int encoder_value = 0;

	/*
	 Error_Handling* error_handling = new Error_Handling();
	 error_handling -> TIM5_error_handling();
	 delete error_handling;
	 */

	if (enc_buff_5 <= 2147483647) {
		encoder_value = enc_buff_5;
	} else if (enc_buff_5 >= 2147483649) {
		encoder_value = enc_buff_5 - 4294967295;
	}

	int encoder_diff = encoder_value - prev_encoder_value;

	prev_encoder_value = encoder_value;

	return encoder_diff;

}
//------------------------------------------------------
int Self_Pos::encoder_read_2(void) {

	static int prev_encoder_value = 0;
	uint32_t enc_buff_2 = TIM2->CNT;
	int encoder_value = 0;

	/*
	 Error_Handling* error_handling = new Error_Handling();
	 error_handling -> TIM2_error_handling();
	 delete error_handling;
	 */

	if (enc_buff_2 <= 2147483647) {
		encoder_value = enc_buff_2;
	} else if (enc_buff_2 >= 2147483649) {
		encoder_value = enc_buff_2 - 4294967295;
	}

	int encoder_diff = encoder_value - prev_encoder_value;

	prev_encoder_value = encoder_value;

	return encoder_diff;

}

int Self_Pos::calc_diff(int prev_x, int prev_y, int current_x, int current_y) {
	int x_diff = current_x - prev_x;
	int y_diff = current_y - prev_y;

	int diff = sqrt(pow(x_diff, 2) + pow(y_diff, 2));

	return diff;
}

int Self_Pos::Self_Pos_config_Limit(void) {
	uint8_t reset_pos = 0;
	int diff = 0;
	char output[10];

	PWM *pwm = new PWM();

	if (this->get_Self_Pos_X() > 0) {
		reset_pos |= true;
	} else {
		reset_pos |= true << 1;
	}

	if (this->get_Self_Pos_Y() > 0) {
		reset_pos |= true << 2;
	} else {
		reset_pos |= true << 3;
	}

	switch (reset_pos) {
	case 0b00000101: {

		pwm->rotate(500, 270);

		pwm->V_output(500, 0, 0, 270, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(2000);

		pwm->V_output(500, 90, 0, 270, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);

		int prev_x = this->get_Self_Pos_X();
		int prev_y = this->get_Self_Pos_Y();

		this->set_initial_pos(E_robot_name::NONE);

		diff = this->calc_diff(prev_x, prev_y, this->get_Self_Pos_X(),
				this->get_Self_Pos_Y());

		break;
	}
	case 0b00001001: {
		pwm->rotate(500, 180);

		pwm->V_output(500, 0, 0, 180, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(2000);

		pwm->V_output(500, 270, 0, 180, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);

		int prev_x = this->get_Self_Pos_X();
		int prev_y = this->get_Self_Pos_Y();

		this->set_initial_pos(E_robot_name::C);

		diff = this->calc_diff(prev_x, prev_y, this->get_Self_Pos_X(),
				this->get_Self_Pos_Y());

		break;
	}
	case 0b00000110: {
		pwm->rotate(500, 0);

		pwm->V_output(500, 180, 0, 0, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(2000);

		pwm->V_output(500, 90, 0, 0, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);

		int prev_x = this->get_Self_Pos_X();
		int prev_y = this->get_Self_Pos_Y();

		this->set_initial_pos(E_robot_name::A);

		diff = this->calc_diff(prev_x, prev_y, this->get_Self_Pos_X(),
				this->get_Self_Pos_Y());

		break;
	}
	case 0b00001010: {
		pwm->rotate(500, 90);

		pwm->V_output(500, 180, 0, 90, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_F_V2_GPIO_Port, LIMIT_F_V2_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_F_V3_GPIO_Port, LIMIT_F_V3_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);
		HAL_Delay(2000);

		pwm->V_output(500, 270, 0, 90, E_move_status::MOVE);
		while ((HAL_GPIO_ReadPin(LIMIT_L_V3_GPIO_Port, LIMIT_L_V3_Pin)
				== GPIO_PIN_RESET)
				|| (HAL_GPIO_ReadPin( LIMIT_L_V4_GPIO_Port, LIMIT_L_V4_Pin)
						== GPIO_PIN_RESET)) {
		}
		pwm->V_output(0, 0, 0, 0, E_move_status::STOP);

		int prev_x = this->get_Self_Pos_X();
		int prev_y = this->get_Self_Pos_Y();

		this->set_initial_pos(E_robot_name::B);

		diff = this->calc_diff(prev_x, prev_y, this->get_Self_Pos_X(),
				this->get_Self_Pos_Y());

		break;
	}
	}

	delete pwm;

	sprintf(output, "%d\r\n", diff);
	HAL_UART_Transmit(&huart2, (uint8_t*) output, sizeof(output), 100);

	return diff;

}

void Self_Pos::Self_Pos_correction(int pos_x) {
	Gyro *gyro = new Gyro();

	int direction = gyro->get_direction(&hi2c1);
	int line_angle;
	int photoelectric_angle;

	int out = direction + line_angle + photoelectric_angle + 180;
	while (out > 359) {
		out -= 360;
	}
	this->out_angle = out;

	int low_angle = 280;
	int high_angle = 440;
	int tower[][2] = { { 1500, 750 }, { 1500, -750 } };
	GPIO::plus = 1;
	if (pos_x <= 0) {
		tower[0][0] *= -1;
		tower[1][0] *= -1;
		low_angle -= 180;
		high_angle -= 180;
		GPIO::plus = -1;
	}

	int d = 0;
	this->Spin(low_angle, false);
	int a[2] = { high_angle, low_angle };
	while (GPIO::count != 2) {
		GPIO::count = 0;
		this->Spin(a[d], true);
		d = -d + 1;
	}
	float a0 = tan(GPIO::angle[0]);
	float a1 = tan(GPIO::angle[1]);
	if (GPIO::plus * a0 <= 0) {
		int a = a0;
		a0 = a1;
		a1 = a;
	}
	this -> Self_Pos_X = (tower[1][1] - tower[0][1] + tower[0][0] * a0
			- tower[1][0] * a1) / (a0 - a1);
	this -> Self_Pos_Y = a0
			* (tower[1][1] - tower[0][1] + a1 * (tower[0][0] - tower[1][0]))
			/ (a0 - a1) + tower[0][1];

	delete gyro;
}

void Self_Pos::Spin(int goal_angle, bool scan) {

	Function *function = new Function();
	Gyro *gyro = new Gyro();

	I2C_HandleTypeDef *gyrovar = &hi2c3;
	int speed = 0;
	int motor_number = 0;

	int now_angle = gyro->get_direction(gyrovar);
	int k[3] = { fabs(goal_angle - now_angle), fabs(
			goal_angle + 360 - now_angle), fabs(goal_angle - 360 - now_angle) };
	int d = (0 <= k[0] && k[0] <= 180) ? 0 :
			(0 <= k[1] && k[1] <= 180) ? 1 : -1;
	int n = (d == 1) ? 2 : d;
	int dire = (goal_angle + d * 360 - now_angle) / k[n];
	int lo = (dire == 1) ? now_angle + (n == 2) ? 360 : 0
				: goal_angle + (n == 1) ? 360 : 0;
	int hi = (dire == -1) ? now_angle + (n == 2) ? 360 : 0
				: goal_angle + (n == 1) ? 360 : 0;
	if (hi < lo) {
		int l = lo;
		lo = hi;
		hi = l;
	}
	if (scan) {
		GPIO::allow = true;
		int n0 =
				(lo <= this->out_angle && this->out_angle <= hi) ? 1 :
				(lo <= this->out_angle + 360 && this->out_angle + 360 <= hi) ?
						-1 : 0;
		if (n0 == 0) {
			function->drive_motor_Rope(motor_number, (int) 0.5 * dire + 1.5,
					speed, true);
			HAL_Delay(1000 * k[n] / speed);
			function->drive_motor_Rope(motor_number, 3, 0, true);
			GPIO::allow = false;
		} else {
			int out_d = fabs(
					now_angle + (n == 2) ?
							360 :
							0 - this->out_angle + (-0.5 * n0 + 0.5) * 360);
			function->drive_motor_Rope(motor_number, (int) 0.5 * dire + 1.5,
					speed, false);

			HAL_Delay(1000 * out_d / speed);

			function->drive_motor_Rope(motor_number, 3, 0, false);
			GPIO::allow = false;
			function->drive_motor_Rope(motor_number, (int) -0.5 * dire + 1.5,
					speed, false);

			HAL_Delay(1000 * 359 / speed);

			function->drive_motor_Rope(motor_number, 3, 0, false);
			GPIO::allow = true;
			function->drive_motor_Rope(motor_number, (int) 0.5 * dire + 1.5,
					speed, false);

			HAL_Delay(1000 * (k[n] - out_d) / speed);
			function->drive_motor_Rope(motor_number, 3, 0, false);
			GPIO::allow = false;
		}
	} else {
		int n0 =
				((lo <= this->out_angle && this->out_angle <= hi)
						|| (lo <= this->out_angle + 360
								&& this->out_angle + 360 <= hi)) ? -1 : 1;
		int spin_d = (int) 0.5 * n0 * dire + 1.5;
		int spin_a = (int) (-0.5 * n0 + 0.5) * 360 + n0 * k[n];
		function -> drive_motor_Rope(motor_number, spin_d, speed, false);
		HAL_Delay(1000 * spin_a / speed);
		function->drive_motor_Rope(motor_number, 3, 0, false);
	}

	delete function;
	delete gyro;

}
