/*
  This is a library written for the BNO080
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/14686

  Written by Nathan Seidle @ SparkFun Electronics, December 28th, 2017

  The BNO080 IMU is a powerful triple axis gyro/accel/magnetometer coupled with an ARM processor
  to maintain and complete all the complex calculations for various VR, inertial, step counting,
  and movement operations.

  This library handles the initialization of the BNO080 and is able to query the sensor
  for different readings.

  https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.5

	SparkFun code, firmware, and software is released under the MIT License.
	Please see LICENSE.md for further details.
*/

#include "SparkFun_BNO080_Arduino_Library.h"
#include "main.h"
#include "Debug.hpp"
#include "i2c.h"

uint16_t BNO080::sequence_Number[ CHANNEL_NUM ] = { 0, 0, 0, 0, 0, 0 };
uint8_t BNO080::shtp_data_RX[ MAX_PACKET_SIZE ] = { 0 };

//Attempt communication with the device
//Return true if we got a 'Polo' back from Marco
bool BNO080::begin( void )
{
//	softReset();
	this -> modesleep();
	this -> modeon();

	this -> shtp_data_TX[ 0 ] = SHTP_REPORT_PRODUCT_ID_REQUEST;
	this -> shtp_data_TX[ 1 ] = 0;

	//Check communication with device

	//Transmit packet on channel 2, 2 bytes
	this -> sendPacket( CHANNEL_CONTROL, 2 );

	//Now we wait for response
	if (receivePacket() == true)
		return (true);
	else
		return (false); //Something went wrong

}

void BNO080::modeon( void )
{

	this -> shtp_data_TX[ 0 ] = 2;
	this -> sendPacket( CHANNEL_EXECUTABLE, 1 );

}

void BNO080::modesleep( void )
{

	this -> shtp_data_TX[ 0 ] = 3;
	this -> sendPacket( CHANNEL_EXECUTABLE, 1 );

}


//Calling this function with nothing sets the debug port to Serial
//You can also call it with other streams like Serial1, SerialUSB, etc.

//Updates the latest variables if possible
//Returns false if new readings are not available

/*
uint16_t BNO080::getReadings(void)
{
	//If we have an interrupt pin connection available, check if data is available.
	//If int pin is not set, then we'll rely on receivePacket() to timeout
	//See issue 13: https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library/issues/13
	if (_int != 255)
	{
		if (digitalRead(_int) == HIGH)
			return 0;
	}

	if (receivePacket() == true)
	{
		//Check to see if this packet is a sensor reporting its data to us
		if (shtpHeader[2] == CHANNEL_REPORTS && shtpData[0] == SHTP_REPORT_BASE_TIMESTAMP)
		{
			return parseInputReport(); //This will update the rawAccelX, etc variables depending on which feature report is found
		}
		else if (shtpHeader[2] == CHANNEL_CONTROL)
		{
			return parseCommandReport(); //This will update responses to commands, calibrationStatus, etc.
		}
    else if(shtpHeader[2] == CHANNEL_GYRO)
    {
      return parseInputReport(); //This will update the rawAccelX, etc variables depending on which feature report is found
    }
	}
	return 0;
}

float BNO080::getYaw()
{
	float dqw = getQuatReal();
	float dqx = getQuatI();
	float dqy = getQuatJ();
	float dqz = getQuatK();

	float norm = sqrt(dqw*dqw + dqx*dqx + dqy*dqy + dqz*dqz);
	dqw = dqw/norm;
	dqx = dqx/norm;
	dqy = dqy/norm;
	dqz = dqz/norm;

	float ysqr = dqy * dqy;

	// yaw (z-axis rotation)
	float t3 = +2.0 * (dqw * dqz + dqx * dqy);
	float t4 = +1.0 - 2.0 * (ysqr + dqz * dqz);
	float yaw = atan2(t3, t4);

	return (yaw);
}

//Gets the full quaternion
//i,j,k,real output floats
void BNO080::getQuat(float &i, float &j, float &k, float &real, float &radAccuracy, uint8_t &accuracy)
{
	i = qToFloat(rawQuatI, rotationVector_Q1);
	j = qToFloat(rawQuatJ, rotationVector_Q1);
	k = qToFloat(rawQuatK, rotationVector_Q1);
	real = qToFloat(rawQuatReal, rotationVector_Q1);
	radAccuracy = qToFloat(rawQuatRadianAccuracy, rotationVector_Q1);
	accuracy = quatAccuracy;
}

//Return the rotation vector quaternion I
float BNO080::getQuatI()
{
	float quat = qToFloat(rawQuatI, rotationVector_Q1);
	if (_printDebug == true)
	{
		if ((quat < -1.0) || (quat > 1.0))
		{
			_debugPort->print(F("getQuatI: quat: ")); // Debug the occasional non-unitary Quat
			_debugPort->print(quat, 2);
			_debugPort->print(F(" rawQuatI: "));
			_debugPort->print(rawQuatI);
			_debugPort->print(F(" rotationVector_Q1: "));
			_debugPort->println(rotationVector_Q1);
		}
	}
	return (quat);
}

//Return the rotation vector quaternion J
float BNO080::getQuatJ()
{
	float quat = qToFloat(rawQuatJ, rotationVector_Q1);
	if (_printDebug == true)
	{
		if ((quat < -1.0) || (quat > 1.0)) // Debug the occasional non-unitary Quat
		{
			_debugPort->print(F("getQuatJ: quat: "));
			_debugPort->print(quat, 2);
			_debugPort->print(F(" rawQuatJ: "));
			_debugPort->print(rawQuatJ);
			_debugPort->print(F(" rotationVector_Q1: "));
			_debugPort->println(rotationVector_Q1);
		}
	}
	return (quat);
}

//Return the rotation vector quaternion K
float BNO080::getQuatK()
{
	float quat = qToFloat(rawQuatK, rotationVector_Q1);
	if (_printDebug == true)
	{
		if ((quat < -1.0) || (quat > 1.0)) // Debug the occasional non-unitary Quat
		{
			_debugPort->print(F("getQuatK: quat: "));
			_debugPort->print(quat, 2);
			_debugPort->print(F(" rawQuatK: "));
			_debugPort->print(rawQuatK);
			_debugPort->print(F(" rotationVector_Q1: "));
			_debugPort->println(rotationVector_Q1);
		}
	}
	return (quat);
}

//Return the rotation vector quaternion Real
float BNO080::getQuatReal()
{
	float quat = qToFloat(rawQuatReal, rotationVector_Q1);
	return (quat);
}

//Return the rotation vector accuracy
}
*/

//Return the acceleration component

//Gets the full acceleration
//x,y,z output floats
void BNO080::getGyro(float &x, float &y, float &z, uint8_t &accuracy)
{
	z = qToFloat(rawGyroZ, gyro_Q1);
	accuracy = gyroAccuracy;
}

//Return the gyro component
//Return the gyro component

//Gets the full mag vector
//x,y,z output floats
//Gets the full high rate gyro vector
//x,y,z output floats

//Given a record ID, read the resolution value from the metaData record in the FRS for a given sensor
//Given a record ID, read the range value from the metaData record in the FRS for a given sensor
//This seems to work reliably.
void BNO080::softReset(void)
{
	this -> shtp_data_TX[ 0 ] = 1;
	sendPacket(CHANNEL_EXECUTABLE, 1); //Transmit packet on channel 1, 1 byte
}

//Set the operating mode to "On"
//(This one is for @jerabaul29)

//Set the operating mode to "Sleep"
//(This one is for @jerabaul29)
//Sends the packet to enable the rotation vector
void BNO080::enableRotationVector(uint16_t timeBetweenReports)
{
	setFeatureCommand(SENSOR_REPORTID_ROTATION_VECTOR, timeBetweenReports);
}

//Sends the packet to enable the ar/vr stabilized rotation vector
//Sends the packet to enable the gyro
void BNO080::enableGyro(uint16_t timeBetweenReports)
{
	setFeatureCommand(SENSOR_REPORTID_GYROSCOPE, timeBetweenReports);
}

//Sends the packet to enable the magnetometer
//Sends the packet to enable the high refresh-rate gyro-integrated rotation vector
void BNO080::enableGyroIntegratedRotationVector(uint16_t timeBetweenReports)
{
	setFeatureCommand(SENSOR_REPORTID_GYRO_INTEGRATED_ROTATION_VECTOR, timeBetweenReports);
}

//Sends the packet to enable the tap detector
//Note you must enable basic reporting on the sensor as well
void BNO080::enableRawGyro(uint16_t timeBetweenReports)
{
	setFeatureCommand(SENSOR_REPORTID_RAW_GYROSCOPE, timeBetweenReports);
}

//Sends the packet to enable the raw accel readings

//Sends the commands to begin calibration of the gyro
void BNO080::calibrateGyro()
{
	sendCalibrateCommand(CALIBRATE_GYRO);
}

void BNO080::setFeatureCommand(uint8_t reportID, uint16_t timeBetweenReports )
{
	long microsBetweenReports = (long)timeBetweenReports * 1000L;

	this -> shtpData[0] = SHTP_REPORT_SET_FEATURE_COMMAND;	 //Set feature command. Reference page 55
	this -> shtpData[1] = reportID;							   //Feature Report ID. 0x01 = Accelerometer, 0x05 = Rotation vector
	this -> shtpData[2] = 0;								   //Feature flags
	this -> shtpData[3] = 0;								   //Change sensitivity (LSB)
	this -> shtpData[4] = 0;								   //Change sensitivity (MSB)
	this -> shtpData[5] = (microsBetweenReports >> 0) & 0xFF;  //Report interval (LSB) in microseconds. 0x7A120 = 500ms
	this -> shtpData[6] = (microsBetweenReports >> 8) & 0xFF;  //Report interval
	this -> shtpData[7] = (microsBetweenReports >> 16) & 0xFF; //Report interval
	this -> shtpData[8] = (microsBetweenReports >> 24) & 0xFF; //Report interval (MSB)
	this -> shtpData[9] = 0;								   //Batch Interval (LSB)
	this -> shtpData[10] = 0;								   //Batch Interval
	this -> shtpData[11] = 0;								   //Batch Interval
	this -> shtpData[12] = 0;								   //Batch Interval (MSB)
	this -> shtpData[13] = 0;	   //Sensor-specific config (LSB)
	this -> shtpData[14] = 0;	   //Sensor-specific config
	this -> shtpData[15] = 0;	  //Sensor-specific config
	this -> shtpData[16] = 0;	  //Sensor-specific config (MSB)

	//Transmit packet on channel 2, 17 bytes
	this -> sendPacket(CHANNEL_CONTROL, 17);
}

//Tell the sensor to do a command
//See 6.3.8 page 41, Command request
//The caller is expected to set P0 through P8 prior to calling
void BNO080::sendCommand(uint8_t command)
{
	shtpData[0] = SHTP_REPORT_COMMAND_REQUEST; //Command Request
	shtpData[1] = commandSequenceNumber++;	 //Increments automatically each function call
	shtpData[2] = command;					   //Command

	//Caller must set these
	/*shtpData[3] = 0; //P0
	shtpData[4] = 0; //P1
	shtpData[5] = 0; //P2
	shtpData[6] = 0;
	shtpData[7] = 0;
	shtpData[8] = 0;
	shtpData[9] = 0;
	shtpData[10] = 0;
	shtpData[11] = 0;*/

	//Transmit packet on channel 2, 12 bytes
//	sendPacket(CHANNEL_CONTROL, 12);
}

//This tells the BNO080 to begin calibrating
//See page 50 of reference manual and the 1000-4044 calibration doc
/*
void BNO080::sendCalibrateCommand(uint8_t thingToCalibrate)
{
	shtpData[3] = 0; //P0 - Accel Cal Enable
	shtpData[4] = 0; //P1 - Gyro Cal Enable
	shtpData[5] = 0; //P2 - Mag Cal Enable
	shtpData[6] = 0; //P3 - Subcommand 0x00
	shtpData[7] = 0; //P4 - Planar Accel Cal Enable
	shtpData[8] = 0; //P5 - Reserved
	shtpData[9] = 0; //P6 - Reserved
	shtpData[10] = 0; //P7 - Reserved
	shtpData[11] = 0; //P8 - Reserved

	for (uint8_t x = 3; x < 12; x++) //Clear this section of the shtpData array
		shtpData[x] = 0;

	if (thingToCalibrate == CALIBRATE_ACCEL)
		shtpData[3] = 1;
	else if (thingToCalibrate == CALIBRATE_GYRO)
		shtpData[4] = 1;
	else if (thingToCalibrate == CALIBRATE_MAG)
		shtpData[5] = 1;
	else if (thingToCalibrate == CALIBRATE_PLANAR_ACCEL)
		shtpData[7] = 1;
	else if (thingToCalibrate == CALIBRATE_ACCEL_GYRO_MAG)
	{
		shtpData[3] = 1;
		shtpData[4] = 1;
		shtpData[5] = 1;
	}
	else if (thingToCalibrate == CALIBRATE_STOP)
		; //Do nothing, bytes are set to zero

	//Make the internal calStatus variable non-zero (operation failed) so that user can test while we wait
	calibrationStatus = 1;

	//Using this shtpData packet, send a command
	sendCommand(COMMAND_ME_CALIBRATE);
}
*/

//Request ME Calibration Status from BNO080
//See page 51 of reference manual
//Returns false if failed


//Blocking wait for BNO080 to assert (pull low) the INT pin
//indicating it's ready for comm. Can take more than 104ms
//after a hardware reset
bool BNO080::receivePacket(void)
{

	uint8_t received_data[ 16 ] = { 0 };
	HAL_I2C_Master_Receive( &hi2c1, BNO080_DEFAULT_ADDRESS, received_data, sizeof( received_data ), 100 );
//	HAL_Delay( 1000 );

	for( int i = 0; i < 16; i++ )
		Debug::TTO_val( received_data[ i ], "received_data:" );



	if ( received_data[ 0 ] == SHTP_REPORT_PRODUCT_ID_RESPONSE )
	{
		Debug::TTO_val( 0, "success:" );
		return true;
	}
	else
		return false;

/*
	if ( received_data[ 0 ] == SHTP_REPORT_PRODUCT_ID_RESPONSE)
		return true; //We're done!
	else
		return false;
*/

}

//Sends multiple requests to sensor until all data bytes are received from sensor
//The shtpData buffer has max capacity of MAX_PACKET_SIZE. Any bytes over this amount will be lost.
//Arduino I2C read limit is 32 bytes. Header is 4 bytes, so max data we can read per interation is 28 bytes

//Given the data packet, send the header then the data
//Returns false if sensor does not ACK
//TODO - Arduino has a max 32 byte send. Break sending into multi packets if needed.
void BNO080::sendPacket(uint8_t channelNumber, uint8_t size )
{
	uint16_t packetLength = size + 4; //Add four bytes for the header

	//if(packetLength > I2C_BUFFER_LENGTH) return(false); //You are trying to send too much. Break into smaller packets.

	for( int i = 0; i < size; i++ )
		this -> shtp_data_TX[ 4 + i ] = this -> shtp_data_TX[ i ];

	this -> shtp_data_TX[ 0 ] = ( packetLength & 0xFF00 ) >> 8;
	this -> shtp_data_TX[ 1 ] = packetLength;
	this -> shtp_data_TX[ 2 ] = channelNumber;
	this -> shtp_data_TX[ 3 ] = BNO080::sequence_Number[channelNumber]++;
	BNO080::sequence_Number[channelNumber]++;

	HAL_I2C_Master_Transmit( &hi2c1, BNO080_DEFAULT_ADDRESS, this -> shtp_data_TX, packetLength, 100 );
}

uint16_t BNO080::parseInputReport(void)
{

	for( int i = 0; i < 4; i++ )
		this -> shtpHeader[ i ] = this -> shtpData[ i ];

	for( int i = 0; i < 16; i++ )
		this -> shtpData[ i ] = shtpData[ i + 4 ];

	//Calculate the number of data bytes in this packet
	int16_t dataLength = ((uint16_t)shtpHeader[1] << 8 | shtpHeader[0]);


	// The gyro-integrated input reports are sent via the special gyro channel and do no include the usual ID, sequence, and status fields
	if( this -> shtpHeader[2] == CHANNEL_GYRO) {
		rawQuatI = (uint16_t)shtpData[1] << 8 | shtpData[0];
		rawQuatJ = (uint16_t)shtpData[3] << 8 | shtpData[2];
		rawQuatK = (uint16_t)shtpData[5] << 8 | shtpData[4];
		rawQuatReal = (uint16_t)shtpData[7] << 8 | shtpData[6];
		rawFastGyroX = (uint16_t)shtpData[9] << 8 | shtpData[8];
		rawFastGyroY = (uint16_t)shtpData[11] << 8 | shtpData[10];
		rawFastGyroZ = (uint16_t)shtpData[13] << 8 | shtpData[12];

		return SENSOR_REPORTID_GYRO_INTEGRATED_ROTATION_VECTOR;
	}

/*
	uint8_t status = shtpData[5 + 2] & 0x03; //Get status bits
	uint16_t data1 = (uint16_t)shtpData[5 + 5] << 8 | shtpData[5 + 4];
	uint16_t data2 = (uint16_t)shtpData[5 + 7] << 8 | shtpData[5 + 6];
	uint16_t data3 = (uint16_t)shtpData[5 + 9] << 8 | shtpData[5 + 8];
	uint16_t data4 = 0;
	uint16_t data5 = 0; //We would need to change this to uin32_t to capture time stamp value on Raw Accel/Gyro/Mag reports

	if (dataLength - 5 > 9)
	{
		data4 = (uint16_t)shtpData[5 + 11] << 8 | shtpData[5 + 10];
	}
	if (dataLength - 5 > 11)
	{
		data5 = (uint16_t)shtpData[5 + 13] << 8 | shtpData[5 + 12];
	}

	//Store these generic values to their proper global variable
	if (shtpData[5] == SENSOR_REPORTID_ACCELEROMETER)
	{
		accelAccuracy = status;
		rawAccelX = data1;
		rawAccelY = data2;
		rawAccelZ = data3;
	}
	else if (shtpData[5] == SENSOR_REPORTID_LINEAR_ACCELERATION)
	{
		accelLinAccuracy = status;
		rawLinAccelX = data1;
		rawLinAccelY = data2;
		rawLinAccelZ = data3;
	}
	else if (shtpData[5] == SENSOR_REPORTID_GYROSCOPE)
	{
		gyroAccuracy = status;
		rawGyroX = data1;
		rawGyroY = data2;
		rawGyroZ = data3;
	}
	else if (shtpData[5] == SENSOR_REPORTID_MAGNETIC_FIELD)
	{
		magAccuracy = status;
		rawMagX = data1;
		rawMagY = data2;
		rawMagZ = data3;
	}
	else if (shtpData[5] == SENSOR_REPORTID_ROTATION_VECTOR ||
		shtpData[5] == SENSOR_REPORTID_GAME_ROTATION_VECTOR ||
		shtpData[5] == SENSOR_REPORTID_AR_VR_STABILIZED_ROTATION_VECTOR ||
		shtpData[5] == SENSOR_REPORTID_AR_VR_STABILIZED_GAME_ROTATION_VECTOR)
	{
		quatAccuracy = status;
		rawQuatI = data1;
		rawQuatJ = data2;
		rawQuatK = data3;
		rawQuatReal = data4;

		//Only available on rotation vector and ar/vr stabilized rotation vector,
		// not game rot vector and not ar/vr stabilized rotation vector
		rawQuatRadianAccuracy = data5;
	}
	else if (shtpData[5] == SENSOR_REPORTID_TAP_DETECTOR)
	{
		tapDetector = shtpData[5 + 4]; //Byte 4 only
	}
	else if (shtpData[5] == SENSOR_REPORTID_STEP_COUNTER)
	{
		stepCount = data3; //Bytes 8/9
	}
	else if (shtpData[5] == SENSOR_REPORTID_STABILITY_CLASSIFIER)
	{
		stabilityClassifier = shtpData[5 + 4]; //Byte 4 only
	}
	else if (shtpData[5] == SENSOR_REPORTID_PERSONAL_ACTIVITY_CLASSIFIER)
	{
		activityClassifier = shtpData[5 + 5]; //Most likely state

		//Load activity classification confidences into the array
		for (uint8_t x = 0; x < 9; x++)					   //Hardcoded to max of 9. TODO - bring in array size
			_activityConfidences[x] = shtpData[5 + 6 + x]; //5 bytes of timestamp, byte 6 is first confidence byte
	}
	else if (shtpData[5] == SENSOR_REPORTID_RAW_ACCELEROMETER)
	{
		memsRawAccelX = data1;
		memsRawAccelY = data2;
		memsRawAccelZ = data3;
	}
	else if (shtpData[5] == SENSOR_REPORTID_RAW_GYROSCOPE)
	{
		memsRawGyroX = data1;
		memsRawGyroY = data2;
		memsRawGyroZ = data3;
	}
	else if (shtpData[5] == SENSOR_REPORTID_RAW_MAGNETOMETER)
	{
		memsRawMagX = data1;
		memsRawMagY = data2;
		memsRawMagZ = data3;
	}
	else if (shtpData[5] == SHTP_REPORT_COMMAND_RESPONSE)
	{
		if (_printDebug == true)
		{
			_debugPort->println(F("!"));
		}
		//The BNO080 responds with this report to command requests. It's up to use to remember which command we issued.
		uint8_t command = shtpData[5 + 2]; //This is the Command byte of the response

		if (command == COMMAND_ME_CALIBRATE)
		{
			if (_printDebug == true)
			{
				_debugPort->println(F("ME Cal report found!"));
			}
			calibrationStatus = shtpData[5 + 5]; //R0 - Status (0 = success, non-zero = fail)
		}
	}
	else
	{
		//This sensor report ID is unhandled.
		//See reference manual to add additional feature reports as needed
		return 0;
	}
*/

	//TODO additional feature reports may be strung together. Parse them all.
	return shtpData[5];
}

//Pretty prints the contents of the current shtp header and data packets
