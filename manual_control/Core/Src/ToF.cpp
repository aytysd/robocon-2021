/*
 * ToF.cpp
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

#include "main.h"


/*
void VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data) {

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    _I2CBuffer[2] = data;

    I2CWrite(Dev, _I2CBuffer, 3);
}

void VL53L1X_StartRanging(uint16_t dev)
{
	VL53L1_WrByte(dev, SYSTEM__MODE_START, 0x40);	 Enable VL53L1X
}
void VL53L1X_SensorInit(uint16_t dev)
{
	uint8_t Addr = 0x00, tmp;

	for (Addr = 0x2D; Addr <= 0x87; Addr++){
		VL53L1_WrByte(dev, Addr, VL51L1X_DEFAULT_CONFIGURATION[Addr - 0x2D]);
	}
	VL53L1X_StartRanging(dev);

	VL53L1X_StopRanging(dev);
}

void VL53L1X_SetDistanceMode(uint16_t dev, uint16_t DM)
{
	uint16_t TB;


	switch (DM) {
	case 1:
		VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x14);
		VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_A, 0x07);
		VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_B, 0x05);
		VL53L1_WrByte(dev, RANGE_CONFIG__VALID_PHASE_HIGH, 0x38);
		VL53L1_WrWord(dev, SD_CONFIG__WOI_SD0, 0x0705);
		VL53L1_WrWord(dev, SD_CONFIG__INITIAL_PHASE_SD0, 0x0606);
		break;
	case 2:
		VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
		VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_A, 0x0F);
		VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_B, 0x0D);
		VL53L1_WrByte(dev, RANGE_CONFIG__VALID_PHASE_HIGH, 0xB8);
		VL53L1_WrWord(dev, SD_CONFIG__WOI_SD0, 0x0F0D);
		VL53L1_WrWord(dev, SD_CONFIG__INITIAL_PHASE_SD0, 0x0E0E);
		break;
	default:
		break;
	}

	VL53L1X_SetTimingBudgetInMs(dev, TB);
}

void VL53L1X_SetTimingBudgetInMs(uint16_t dev, uint16_t TimingBudgetInMs)
{
	uint16_t DM;

	VL53L1X_GetDistanceMode(dev, &DM);
	if (DM == 0)
		return 1;
	else if (DM == 1) {	 Short DistanceMode
		switch (TimingBudgetInMs) {
		case 15:  only available in short distance mode
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x01D);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0027);
			break;
		case 20:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0051);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E);
			break;
		case 33:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x00D6);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E);
			break;
		case 50:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x1AE);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x01E8);
			break;
		case 100:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x02E1);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0388);
			break;
		case 200:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x03E1);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0496);
			break;
		case 500:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0591);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x05C1);
			break;
		default:
			break;
		}
	} else {
		switch (TimingBudgetInMs) {
		case 20:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x001E);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x0022);
			break;
		case 33:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x0060);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x006E);
			break;
		case 50:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x00AD);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x00C6);
			break;
		case 100:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x01CC);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x01EA);
			break;
		case 200:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x02D9);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI,
					0x02F8);
			break;
		case 500:
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, 0x048F);
			VL53L1_WrWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_B_HI, 0x04A4);
			break;
		default:
			break;
		}
	}
}
void VL53L1X_SetInterMeasurementInMs(uint16_t dev, uint16_t InterMeasMs)
{
	uint16_t ClockPLL;

	VL53L1_RdWord(dev, VL53L1_RESULT__OSC_CALIBRATE_VAL, &ClockPLL);
	ClockPLL = ClockPLL&0x3FF;
	VL53L1_WrDWord(dev, VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD,
			(uint32_t)(ClockPLL * InterMeasMs * 1.075));

}

void VL53L1X_SetInterMeasurementInMs(uint16_t dev, uint16_t InterMeasMs)
{
	uint16_t ClockPLL;

	VL53L1_RdWord(dev, VL53L1_RESULT__OSC_CALIBRATE_VAL, &ClockPLL);
	ClockPLL = ClockPLL&0x3FF;
	VL53L1_WrDWord(dev, VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD,
			(uint32_t)(ClockPLL * InterMeasMs * 1.075));

}

void VL53L1X_SetROI(uint16_t dev, uint16_t X, uint16_t Y)
{
	uint8_t OpticalCenter;

	VL53L1_RdByte(dev, VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD, &OpticalCenter);
	if (X > 16)
		X = 16;
	if (Y > 16)
		Y = 16;
	if (X > 10 || Y > 10){
		OpticalCenter = 199;
	}
	VL53L1_WrByte(dev, ROI_CONFIG__USER_ROI_CENTRE_SPAD, OpticalCenter);
	VL53L1_WrByte(dev, ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE,
		       (Y - 1) << 4 | (X - 1));
}


*/


