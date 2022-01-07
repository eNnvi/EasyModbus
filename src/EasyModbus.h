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
	GENERIC, ///< When none of the above..
};


#endif