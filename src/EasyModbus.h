/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
    Easy library for Arduino to read modbus devices
    @file EasyModbus.h
    @author Lorenzo Carloni
    @version 0.0.1 06/01/2022
*/

#ifndef __EASYMODBUS_H__
#define __EASYMODBUS_H__

#include <Arduino.h>
#include "EasyModbusRTU.h"

#ifndef CP_TRANSMIT_LEVEL
	/// Pin level of transmit mode
  #define CP_TRANSMIT_LEVEL HIGH
#endif
/// Pin level of receive mode
#define CP_RECEIVE_LEVEL  !CP_TRANSMIT_LEVEL

#ifndef COMM_TIMEOUT_TIME
  /// Default timeout time in mS
  #define COMM_TIMEOUT_TIME 100
#endif

/// ModbusError enum class is used to check if there's been a bad communication
enum ModbusError {
  SUCCESS=0, ///< Success in communication, no error
  WRONG_CRC, ///< CRC calculation differs..
  NO_RESPONSE, ///< No response in communication timeout time
  WRONG_DEVICE, ///< Device that responded differs from called one
	UNEXPECTED_RESPONSE, ///< Response byte count differs from what expected (might need to increase timeout time)
	UNIMPLEMENTED,	///< Function yet TBI
	UNEQUAL,	///< In writing modes the response should be echo of the request, if not this error triggers
	// EXCEPTION CODES!
	FUNCTION_CODE_UNSUPPORTED,		///< Device doesn't support tish function
	OUTPUT_OUT_OF_RANGE,				///< Too many or too few registers/coils requested
	OUT_OF_ADDRESS,				///< Device can't find all addresses
	DEVICE_ERROR,					///< Device unable to complete operation
	WRONG_DATA_VALUE,			///< Device didn't get good data
	GENERIC, ///< When none of the above..
};

/*
	Every function has an error code for different scenarios.
	
	Function 0x01 (read coils)
		0x01	FUNCTION_CODE_UNSUPPORTED
		0x02  OUTPUT_OUT_OF_RANGE
		0x03	OUT_OF_ADDRESS
		0x04	DEVICE_ERROR
	
	Almost every functions gives same kind of error.
	Big differences:
		- in write operations codes 0x02 and 0x03 are inverted 
		- in serial line only operations there are error codes 0x01 and 0x04

*/
const ModbusError errorMappingTable[][4] PROGMEM = {
	{FUNCTION_CODE_UNSUPPORTED, OUTPUT_OUT_OF_RANGE, OUT_OF_ADDRESS, DEVICE_ERROR},	// 0x01
	{FUNCTION_CODE_UNSUPPORTED, OUTPUT_OUT_OF_RANGE, OUT_OF_ADDRESS, DEVICE_ERROR},	// 0x02
	{FUNCTION_CODE_UNSUPPORTED, OUTPUT_OUT_OF_RANGE, OUT_OF_ADDRESS, DEVICE_ERROR},	// 0x03
	{FUNCTION_CODE_UNSUPPORTED, OUTPUT_OUT_OF_RANGE, OUT_OF_ADDRESS, DEVICE_ERROR},	// 0x04
	{FUNCTION_CODE_UNSUPPORTED, OUT_OF_ADDRESS, OUTPUT_OUT_OF_RANGE, DEVICE_ERROR}, // 0x05
	{FUNCTION_CODE_UNSUPPORTED, OUT_OF_ADDRESS, OUTPUT_OUT_OF_RANGE, DEVICE_ERROR}, // 0x06
	{FUNCTION_CODE_UNSUPPORTED, SUCCESS, SUCCESS, DEVICE_ERROR}, // 0x07
	{FUNCTION_CODE_UNSUPPORTED, SUCCESS, WRONG_DATA_VALUE, DEVICE_ERROR}, // 0x08
	{SUCCESS, SUCCESS, SUCCESS, SUCCESS}, // 0x09
	{SUCCESS, SUCCESS, SUCCESS, SUCCESS}, // 0x0A
	{FUNCTION_CODE_UNSUPPORTED, SUCCESS, SUCCESS, DEVICE_ERROR}, // 0x0B
	{FUNCTION_CODE_UNSUPPORTED, SUCCESS, SUCCESS, DEVICE_ERROR}, // 0x0C
	{SUCCESS, SUCCESS, SUCCESS, SUCCESS}, // 0x0D
	{SUCCESS, SUCCESS, SUCCESS, SUCCESS}, // 0x0E
	{FUNCTION_CODE_UNSUPPORTED, OUT_OF_ADDRESS, OUTPUT_OUT_OF_RANGE, DEVICE_ERROR}, // 0x0F
	{FUNCTION_CODE_UNSUPPORTED, OUT_OF_ADDRESS, OUTPUT_OUT_OF_RANGE, DEVICE_ERROR}, // 0x10
};


#endif