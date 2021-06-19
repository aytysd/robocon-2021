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
#define TOF_ADDRESS 0x52

class ToF{
public:
	uint16_t get_distance(void);
	void update_distance(void);
	void init_ToF(void);
private:
	static uint16_t distance;
	int _I2CWrite(uint16_t Dev, uint8_t *pdata, uint32_t count) ;
	int _I2CRead(uint16_t Dev, uint8_t *pdata, uint32_t count);
	void VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data);
	void VL53L1X_StartRanging(uint16_t dev);
	void VL53L1X_SensorInit(uint16_t dev);
	void VL53L1X_SetDistanceMode(uint16_t dev, uint16_t DM);
	void VL53L1X_SetTimingBudgetInMs(uint16_t dev, uint16_t TimingBudgetInMs);
	void VL53L1X_SetInterMeasurementInMs(uint16_t dev, uint16_t InterMeasMs);
	void VL53L1X_SetInterMeasurementInMs(uint16_t dev, uint16_t InterMeasMs);
	void VL53L1X_SetROI(uint16_t dev, uint16_t X, uint16_t Y);

};


#endif /* INC_TOF_HPP_ */
