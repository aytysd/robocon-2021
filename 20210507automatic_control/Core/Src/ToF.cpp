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
#include "ToF.hpp"

extern I2C_HandleTypeDef  XNUCLEO53L1A1_hi2c;



#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1

#define SYSTEM__MODE_START                 					0x0087

#ifndef VL53L1_GetI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L1_GetI2cBus(...) (void)0
#endif

#ifndef VL53L1_PutI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L1_PutI2cBus(...) (void)0
#endif

uint8_t _I2CBuffer[256];



const uint8_t VL51L1X_DEFAULT_CONFIGURATION[] = {
0x00, /* 0x2d : set bit 2 and 5 to 1 for fast plus mode (1MHz I2C), else don't touch */
0x00, /* 0x2e : bit 0 if I2C pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
0x00, /* 0x2f : bit 0 if GPIO pulled up at 1.8V, else set bit 0 to 1 (pull up at AVDD) */
0x01, /* 0x30 : set bit 4 to 0 for active high interrupt and 1 for active low (bits 3:0 must be 0x1), use SetInterruptPolarity() */
0x02, /* 0x31 : bit 1 = interrupt depending on the polarity, use CheckForDataReady() */
0x00, /* 0x32 : not user-modifiable */
0x02, /* 0x33 : not user-modifiable */
0x08, /* 0x34 : not user-modifiable */
0x00, /* 0x35 : not user-modifiable */
0x08, /* 0x36 : not user-modifiable */
0x10, /* 0x37 : not user-modifiable */
0x01, /* 0x38 : not user-modifiable */
0x01, /* 0x39 : not user-modifiable */
0x00, /* 0x3a : not user-modifiable */
0x00, /* 0x3b : not user-modifiable */
0x00, /* 0x3c : not user-modifiable */
0x00, /* 0x3d : not user-modifiable */
0xff, /* 0x3e : not user-modifiable */
0x00, /* 0x3f : not user-modifiable */
0x0F, /* 0x40 : not user-modifiable */
0x00, /* 0x41 : not user-modifiable */
0x00, /* 0x42 : not user-modifiable */
0x00, /* 0x43 : not user-modifiable */
0x00, /* 0x44 : not user-modifiable */
0x00, /* 0x45 : not user-modifiable */
0x20, /* 0x46 : interrupt configuration 0->level low detection, 1-> level high, 2-> Out of window, 3->In window, 0x20-> New sample ready , TBC */
0x0b, /* 0x47 : not user-modifiable */
0x00, /* 0x48 : not user-modifiable */
0x00, /* 0x49 : not user-modifiable */
0x02, /* 0x4a : not user-modifiable */
0x0a, /* 0x4b : not user-modifiable */
0x21, /* 0x4c : not user-modifiable */
0x00, /* 0x4d : not user-modifiable */
0x00, /* 0x4e : not user-modifiable */
0x05, /* 0x4f : not user-modifiable */
0x00, /* 0x50 : not user-modifiable */
0x00, /* 0x51 : not user-modifiable */
0x00, /* 0x52 : not user-modifiable */
0x00, /* 0x53 : not user-modifiable */
0xc8, /* 0x54 : not user-modifiable */
0x00, /* 0x55 : not user-modifiable */
0x00, /* 0x56 : not user-modifiable */
0x38, /* 0x57 : not user-modifiable */
0xff, /* 0x58 : not user-modifiable */
0x01, /* 0x59 : not user-modifiable */
0x00, /* 0x5a : not user-modifiable */
0x08, /* 0x5b : not user-modifiable */
0x00, /* 0x5c : not user-modifiable */
0x00, /* 0x5d : not user-modifiable */
0x01, /* 0x5e : not user-modifiable */
0xcc, /* 0x5f : not user-modifiable */
0x0f, /* 0x60 : not user-modifiable */
0x01, /* 0x61 : not user-modifiable */
0xf1, /* 0x62 : not user-modifiable */
0x0d, /* 0x63 : not user-modifiable */
0x01, /* 0x64 : Sigma threshold MSB (mm in 14.2 format for MSB+LSB), use SetSigmaThreshold(), default value 90 mm  */
0x68, /* 0x65 : Sigma threshold LSB */
0x00, /* 0x66 : Min count Rate MSB (MCPS in 9.7 format for MSB+LSB), use SetSignalThreshold() */
0x80, /* 0x67 : Min count Rate LSB */
0x08, /* 0x68 : not user-modifiable */
0xb8, /* 0x69 : not user-modifiable */
0x00, /* 0x6a : not user-modifiable */
0x00, /* 0x6b : not user-modifiable */
0x00, /* 0x6c : Intermeasurement period MSB, 32 bits register, use SetIntermeasurementInMs() */
0x00, /* 0x6d : Intermeasurement period */
0x0f, /* 0x6e : Intermeasurement period */
0x89, /* 0x6f : Intermeasurement period LSB */
0x00, /* 0x70 : not user-modifiable */
0x00, /* 0x71 : not user-modifiable */
0x00, /* 0x72 : distance threshold high MSB (in mm, MSB+LSB), use SetD:tanceThreshold() */
0x00, /* 0x73 : distance threshold high LSB */
0x00, /* 0x74 : distance threshold low MSB ( in mm, MSB+LSB), use SetD:tanceThreshold() */
0x00, /* 0x75 : distance threshold low LSB */
0x00, /* 0x76 : not user-modifiable */
0x01, /* 0x77 : not user-modifiable */
0x0f, /* 0x78 : not user-modifiable */
0x0d, /* 0x79 : not user-modifiable */
0x0e, /* 0x7a : not user-modifiable */
0x0e, /* 0x7b : not user-modifiable */
0x00, /* 0x7c : not user-modifiable */
0x00, /* 0x7d : not user-modifiable */
0x02, /* 0x7e : not user-modifiable */
0xc7, /* 0x7f : ROI center, use SetROI() */
0xff, /* 0x80 : XY ROI (X=Width, Y=Height), use SetROI() */
0x9B, /* 0x81 : not user-modifiable */
0x00, /* 0x82 : not user-modifiable */
0x00, /* 0x83 : not user-modifiable */
0x00, /* 0x84 : not user-modifiable */
0x01, /* 0x85 : not user-modifiable */
0x00, /* 0x86 : clear interrupt, use ClearInterrupt() */
0x00  /* 0x87 : start ranging, use StartRanging() or StopRanging(), If you want an automatic start after VL53L1X_init() call, put 0x40 in location 0x87 */
};


#define SOFT_RESET											0x0000
#define VL53L1_I2C_SLAVE__DEVICE_ADDRESS					0x0001
#define VL53L1_VHV_CONFIG__TIMEOUT_MACROP_LOOP_BOUND        0x0008
#define ALGO__CROSSTALK_COMPENSATION_PLANE_OFFSET_KCPS 		0x0016
#define ALGO__CROSSTALK_COMPENSATION_X_PLANE_GRADIENT_KCPS 	0x0018
#define ALGO__CROSSTALK_COMPENSATION_Y_PLANE_GRADIENT_KCPS 	0x001A
#define ALGO__PART_TO_PART_RANGE_OFFSET_MM					0x001E
#define MM_CONFIG__INNER_OFFSET_MM							0x0020
#define MM_CONFIG__OUTER_OFFSET_MM 							0x0022
#define GPIO_HV_MUX__CTRL									0x0030
#define GPIO__TIO_HV_STATUS       							0x0031
#define SYSTEM__INTERRUPT_CONFIG_GPIO 						0x0046
#define PHASECAL_CONFIG__TIMEOUT_MACROP     				0x004B
#define RANGE_CONFIG__TIMEOUT_MACROP_A_HI   				0x005E
#define RANGE_CONFIG__VCSEL_PERIOD_A        				0x0060
#define RANGE_CONFIG__VCSEL_PERIOD_B						0x0063
#define RANGE_CONFIG__TIMEOUT_MACROP_B_HI  					0x0061
#define RANGE_CONFIG__TIMEOUT_MACROP_B_LO  					0x0062
#define RANGE_CONFIG__SIGMA_THRESH 							0x0064
#define RANGE_CONFIG__MIN_COUNT_RATE_RTN_LIMIT_MCPS			0x0066
#define RANGE_CONFIG__VALID_PHASE_HIGH      				0x0069
#define VL53L1_SYSTEM__INTERMEASUREMENT_PERIOD				0x006C
#define SYSTEM__THRESH_HIGH 								0x0072
#define SYSTEM__THRESH_LOW 									0x0074
#define SD_CONFIG__WOI_SD0                  				0x0078
#define SD_CONFIG__INITIAL_PHASE_SD0        				0x007A
#define ROI_CONFIG__USER_ROI_CENTRE_SPAD					0x007F
#define ROI_CONFIG__USER_ROI_REQUESTED_GLOBAL_XY_SIZE		0x0080
#define SYSTEM__SEQUENCE_CONFIG								0x0081
#define VL53L1_SYSTEM__GROUPED_PARAMETER_HOLD 				0x0082
#define SYSTEM__INTERRUPT_CLEAR       						0x0086
#define SYSTEM__MODE_START                 					0x0087
#define VL53L1_RESULT__RANGE_STATUS							0x0089
#define VL53L1_RESULT__DSS_ACTUAL_EFFECTIVE_SPADS_SD0		0x008C
#define RESULT__AMBIENT_COUNT_RATE_MCPS_SD					0x0090
#define VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0				0x0096
#define VL53L1_RESULT__PEAK_SIGNAL_COUNT_RATE_CROSSTALK_CORRECTED_MCPS_SD0 	0x0098
#define VL53L1_RESULT__OSC_CALIBRATE_VAL					0x00DE
#define VL53L1_FIRMWARE__SYSTEM_STATUS                      0x00E5
#define VL53L1_IDENTIFICATION__MODEL_ID                     0x010F
#define VL53L1_ROI_CONFIG__MODE_ROI_CENTRE_SPAD				0x013E




int ToF::_I2CWrite(uint16_t Dev, uint8_t *pdata, uint32_t count) {
    int status;
    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

    status = HAL_I2C_Master_Transmit(&XNUCLEO53L1A1_hi2c, Dev, pdata, count, i2c_time_out);
    if (status) {
        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}


int ToF::_I2CRead(uint16_t Dev, uint8_t *pdata, uint32_t count) {
    int status;
    int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

    status = HAL_I2C_Master_Receive(&XNUCLEO53L1A1_hi2c, Dev|1, pdata, count, i2c_time_out);
    if (status) {
        //VL6180x_ErrLog("I2C error 0x%x %d len", dev->I2cAddr, len);
        //XNUCLEO6180XA1_I2C1_Init(&hi2c1);
    }
    return status;
}


int8_t ToF::VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data) {
	int8_t Status = 0;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    _I2CBuffer[2] = data;

    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 3);
    if (status_int != 0) {
        Status = 1;
    }
    VL53L1_PutI2cBus();
    return Status;
}

int8_t ToF::VL53L1_WrWord(uint16_t Dev, uint16_t index, uint16_t data) {
	int8_t Status = 0;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    _I2CBuffer[2] = data >> 8;
    _I2CBuffer[3] = data & 0x00FF;

    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 4);
    if (status_int != 0) {
        Status = 1;
    }
    VL53L1_PutI2cBus();
    return Status;
}


int8_t ToF::VL53L1_RdWord(uint16_t Dev, uint16_t index, uint16_t *data) {
    int8_t Status = 0;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
	_I2CBuffer[1] = index&0xFF;
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 2);

   if( status_int ){
        Status = 1;
        goto done;
    }
    status_int = _I2CRead(Dev, _I2CBuffer, 2);
    if (status_int != 0) {
        Status = 1;
        goto done;
    }

    *data = ((uint16_t)_I2CBuffer[0]<<8) + (uint16_t)_I2CBuffer[1];
done:
    VL53L1_PutI2cBus();
    return Status;
}


void ToF::VL53L1X_StartRanging(uint16_t dev)
{
	VL53L1_WrByte(dev, SYSTEM__MODE_START, 0x40);	// Enable VL53L1X
}


void ToF::VL53L1X_StopRanging(uint16_t dev)
{
	VL53L1_WrByte(dev, SYSTEM__MODE_START, 0x00);	// Disable VL53L1X
}


void ToF::VL53L1X_SensorInit(uint16_t dev)
{
	uint8_t Addr = 0x00;

	for (Addr = 0x2D; Addr <= 0x87; Addr++){
		VL53L1_WrByte(dev, Addr, VL51L1X_DEFAULT_CONFIGURATION[Addr - 0x2D]);
	}
	VL53L1X_StartRanging(dev);

	VL53L1X_StopRanging(dev);
}


int8_t ToF::VL53L1X_GetTimingBudgetInMs(uint16_t dev, uint16_t *pTimingBudget)
{
	uint16_t Temp;
	int8_t status = 0;

	status = VL53L1_RdWord(dev, RANGE_CONFIG__TIMEOUT_MACROP_A_HI, &Temp);
	switch (Temp) {
		case 0x001D :
			*pTimingBudget = 15;
			break;
		case 0x0051 :
		case 0x001E :
			*pTimingBudget = 20;
			break;
		case 0x00D6 :
		case 0x0060 :
			*pTimingBudget = 33;
			break;
		case 0x1AE :
		case 0x00AD :
			*pTimingBudget = 50;
			break;
		case 0x02E1 :
		case 0x01CC :
			*pTimingBudget = 100;
			break;
		case 0x03E1 :
		case 0x02D9 :
			*pTimingBudget = 200;
			break;
		case 0x0591 :
		case 0x048F :
			*pTimingBudget = 500;
			break;
		default:
			status = 1;
			*pTimingBudget = 0;
	}
	return status;
}


int8_t ToF::VL53L1X_SetDistanceMode(uint16_t dev, uint16_t DM)
{
	uint16_t TB;
	int8_t status = 0;

	status = VL53L1X_GetTimingBudgetInMs(dev, &TB);
	if (status != 0)
		return 1;
	switch (DM) {
	case 1:
		status = VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x14);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_A, 0x07);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_B, 0x05);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VALID_PHASE_HIGH, 0x38);
		status = VL53L1_WrWord(dev, SD_CONFIG__WOI_SD0, 0x0705);
		status = VL53L1_WrWord(dev, SD_CONFIG__INITIAL_PHASE_SD0, 0x0606);
		break;
	case 2:
		status = VL53L1_WrByte(dev, PHASECAL_CONFIG__TIMEOUT_MACROP, 0x0A);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_A, 0x0F);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VCSEL_PERIOD_B, 0x0D);
		status = VL53L1_WrByte(dev, RANGE_CONFIG__VALID_PHASE_HIGH, 0xB8);
		status = VL53L1_WrWord(dev, SD_CONFIG__WOI_SD0, 0x0F0D);
		status = VL53L1_WrWord(dev, SD_CONFIG__INITIAL_PHASE_SD0, 0x0E0E);
		break;
	default:
		status = 1;
		break;
	}
	return 0;
}

int8_t ToF::VL53L1X_GetDistance(uint16_t dev, uint16_t *distance)
{
	int8_t status = 0;
	uint16_t tmp;

	status = (VL53L1_RdWord(dev,
			VL53L1_RESULT__FINAL_CROSSTALK_CORRECTED_RANGE_MM_SD0, &tmp));
	*distance = tmp;
	return status;
}

/*
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


