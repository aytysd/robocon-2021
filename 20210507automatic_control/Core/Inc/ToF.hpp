/*
 * ToF.hpp
 *
 *  Created on: 19 May 2021
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
#ifndef INC_TOF_HPP_
#define INC_TOF_HPP_

#include "main.h"
#include "Self_Pos.hpp"
#define TOF_ADDRESS 0x52

class ToF{
public:
	uint16_t get_distance(uint16_t mode);
	void init_ToF(void);
private:
	static uint16_t distance;
	int _I2CWrite(uint16_t Dev, uint8_t *pdata, uint32_t count);
	int _I2CRead(uint16_t Dev, uint8_t *pdata, uint32_t count);
	int8_t VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data);
	int8_t VL53L1_WrWord(uint16_t Dev, uint16_t index, uint16_t data);
	int8_t VL53L1_RdWord(uint16_t Dev, uint16_t index, uint16_t *data);
	void VL53L1X_StartRanging(uint16_t dev);
	void VL53L1X_StopRanging(uint16_t dev);
	uint8_t VL53L1X_SetI2CAddress(uint16_t dev, uint8_t new_address);
	void VL53L1X_SensorInit(uint16_t dev);
	int8_t VL53L1X_GetTimingBudgetInMs(uint16_t dev, uint16_t *pTimingBudget);
	int8_t VL53L1X_SetDistanceMode(uint16_t dev, uint16_t DM);
	int8_t VL53L1X_GetDistance(uint16_t dev, uint16_t *distance);
};


#endif /* INC_TOF_HPP_ */
