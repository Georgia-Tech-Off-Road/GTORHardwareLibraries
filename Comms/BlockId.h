
/*******************************************************************************************
This is an auto generated file. DO NOT edit this file. To make changes to the SensorId list, 
go to Application>DataAcquisition>SensorId.py and edit the dictionary there. Then regenerate
this file by using Application>GenerateSensorIdHFile.py (It will automatically place the
file in the correct location i.e. Libraries>Comms>BlockId.h)

Generated at: 2022-04-10 17:29:17.996064

*******************************************************************************************/

#ifndef BLOCKID_H
#define BLOCKID_H

#include <Arduino.h>

enum block_id_t : uint16_t
{

    /**
     * 000 - DEFAULTS, FLAGS, COMMANDS, MISC
     */
	DEFAULT_NO_SENSOR               = 0,	//NumBytes: 0
	FLAG_DATACOLLECTING             = 1,	//NumBytes: 1
	COMMAND_SDCARDFILENAMESTRING    = 2,	//NumBytes: 12
	COMMAND_TOGGLE_TEENSY_LED       = 3,	//NumBytes: 1
	COMMAND_TARE_LOAD_CELL          = 4,	//NumBytes: 1
	COMMAND_MOTOR_SPEED             = 5,	//NumBytes: 1
	COMMAND_MOTOR_ENABLE            = 6,	//NumBytes: 1
	COMMAND_SCALE_LOAD_CELL         = 7,	//NumBytes: 4
	GPS_SENSOR                      = 8,	//NumBytes: [4, 4, 4] - Contains lattitude, longitude, and speed (knots)
	COMMAND_AUXDAQ_SDWRITE          = 9,	//NumBytes: 1
	FLAG_AUXDAQ_SDWRITE             = 10,	//NumBytes: 1
	TEST_SENSOR_0                   = 90,	//NumBytes: 4
	TEST_SENSOR_1                   = 91,	//NumBytes: 4
	TEST_SENSOR_2                   = 92,	//NumBytes: 4
	TEST_SENSOR_3                   = 93,	//NumBytes: 4
	TEST_SENSOR_4                   = 94,	//NumBytes: 4
	TEST_SENSOR_5                   = 95,	//NumBytes: 4
	TEST_SENSOR_6                   = 96,	//NumBytes: 4
	TEST_SENSOR_7                   = 97,	//NumBytes: 4
	TEST_SENSOR_8                   = 98,	//NumBytes: 4
	TEST_SENSOR_9                   = 99,	//NumBytes: 4

    /**
     * 100 - TIME "SENSORS"
     */
	TIME_GENERIC                    = 100,	//NumBytes: 4
	TIME_INTERNAL_SECONDS           = 101,	//NumBytes: 2
	TIME_DASH_MS                    = 102,	//NumBytes: 2
	TIME_DASH_US                    = 103,	//NumBytes: 4
	TIME_AUXDAQ_MS                  = 104,	//NumBytes: 2
	TIME_AUXDAQ_US                  = 105,	//NumBytes: 4
	TIME_DIFF_MS                    = 106,	//NumBytes: 2
	TIME_DIFF_US                    = 107,	//NumBytes: 4
	TIME_DAATA_MS                   = 108,	//NumBytes: 2
	TIME_DAATA_US                   = 109,	//NumBytes: 4
	RTC_UNIXTIME                    = 199,	//NumBytes: 4

    /**
     * 200 - SPEED/POSITION SENSORS
     */
	SPEED_GENERIC                   = 200,	//NumBytes: 2
	POSITION_GENERIC                = 201,	//NumBytes: 4
	SPEED_POSITION_GENERIC4         = 202,	//NumBytes: [4, 4] - Speed in RPM and position in ticks (4ppr sensor)
	SPEED_POSITION_GENERIC30        = 203,	//NumBytes: [4, 4] - Speed in RPM and position in ticks (30ppr sensor)
	SPEED_POSITION_GENERIC500       = 204,	//NumBytes: [4, 4] - Speed in RPM and position in ticks (500ppr sensor)
	SPEED_POSITION_GENERIC600       = 205,	//NumBytes: [4, 2] - Speed in RPM and position in ticks (600ppr sensor)
	SPEED_POSITION_ENGINE600        = 206,	//NumBytes: [4, 4] - Speed in RPM and position in ticks (600ppr sensor)
	SPEED_POSITION_ENGINE4          = 207,	//NumBytes: [4, 4] - Speed in RPM and position in ticks (4ppr sensor)
	SPEED_POSITION_SECONDARY30      = 208,	//NumBytes: [4, 4] - Speed in RPM and position in ticks (30ppr on gear)
	SPEED_ENGINE600_RPM             = 209,	//NumBytes: 2 - Speed in RPM (600ppr sensor)
	SPEED_ENGINE4_RPM               = 210,	//NumBytes: 2 - Speed in RPM (4ppr sensor)
	SPEED_SECONDARY30_RPM           = 211,	//NumBytes: 2 - Speed in RPM (30ppr sensor)
	SPEED_DYNOENGINE600_RPM         = 212,	//NumBytes: [4, 2] - Speed in RPM and position in ticks (600ppr sensor)
	SPEED_DYNOSECONDARY30_RPM       = 213,	//NumBytes: [4, 2] - Speed in RPM and position in ticks (600ppr sensor)
	SPEED_2021CAR_ENGINE600_RPM     = 214,	//NumBytes: [4, 2] - Speed in RPM and position in ticks (600ppr sensor)
	SPEED_2021CAR_SECONDARY30_RPM   = 215,	//NumBytes: [4, 2] - Speed in RPM and position in ticks (600ppr sensor)

    /**
     * 300 - FORCE/PRESSURE SENSORS
     */
	PRESSURE_GENERIC                = 300,	//NumBytes: 2
	FORCE_GENERIC                   = 301,	//NumBytes: 4
	BRAKE_SENSOR1                   = 302,	//NumBytes: 4
	BRAKE_SENSOR2                   = 303,	//NumBytes: 4
	PRESSURE_FRONTBRAKE_PSI         = 304,	//NumBytes: 4
	PRESSURE_REARBRAKE_PSI          = 305,	//NumBytes: 4
	FORCE_ENGINEDYNO_LBS            = 306,	//NumBytes: 4
	FORCE_SHOCKDYNO_LBS             = 307,	//NumBytes: 4
	WHEEL_FORCE_TRANSDUCER_ANALOG_1 = 308,	//NumBytes: [4, 4, 4, 4] - FX, FY, FZ, MX
	WHEEL_FORCE_TRANSDUCER_ANALOG_2 = 309,	//NumBytes: [4, 4, 4, 4] - MY, MZ, Vel, Pos
	WHEEL_FORCE_TRANSDUCER_ANALOG_3 = 310,	//NumBytes: [4, 4, 4, 4] - AccelX, AccelY
	FORCE_STRAINGAUGE_STRAIN        = 311,	//NumBytes: 4
	LOADCELL_CHASSISSTIFFNESS_LBS   = 312,	//NumBytes: 4

    /**
     * 400 - LDS SENSORS
     */
	LDS_GENERIC                     = 400,	//NumBytes: 1
	LDS_FRONTLEFTSHOCK_MM           = 401,	//NumBytes: 4
	LDS_FRONTRIGHTSHOCK_MM          = 402,	//NumBytes: 4
	LDS_BACKLEFTSHOCK_MM            = 403,	//NumBytes: 4
	LDS_BACKRIGHTSHOCK_MM           = 404,	//NumBytes: 4
	LDS_SHOCKDYNO_MM                = 405,	//NumBytes: 1
	LDS_PEDAL_MM                    = 406,	//NumBytes: 4 - This sensor probably only used for testing day 4/2/22

    /**
     * 500 - IMU SENSORS
     */
	IMU_SENSOR                      = 500,	//NumBytes: [4, 4, 4, 4, 4, 4, 4] - Accel X, Y, Z; Gyro X, Y, Z; Temp


    MAX_SENSOR_NUM = 65535
};

#endif
