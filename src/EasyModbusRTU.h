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
    @file EasyModbusRTU.h
    @author Lorenzo Carloni
    @version 0.0.1 06/01/2022
*/

#ifndef __EASYMODBUSRTU_H__
#define __EASYMODBUSRTU_H__

#include <Arduino.h>
#include "EasyModbus.h"


class EasyModbusRTU {
	uint8_t address, comm_pin, min_timing, serial_config;
	int baud_rate;
	ModbusError last_error;
	Stream* comm_stream;
	
	
	/**
     * @brief Calcs CRC of the message, LSB first
     * @param buf buffer of the request
     * @param len length of the buffer
     * @return 2 byte CRC (LSB fisrt)
  */
  uint16_t calcCrc(uint8_t* buf, int len);
	
	/**
     * @brief Checks wether 2 arrays are equal
     * @param arr1 first array to compare
     * @param arr2 second array to compare
     * @param length size of the arrays
     * @return true if equal, false otherwise
  */
  bool isEqual(uint8_t* arr1, uint8_t* arr2, int length);
	
	/**
		 * @brief Clears read buffer
  */
	void clearReadBuffer();
	
		/**
		On call resets last_error, performs communication, check wether there's any common problem (NO_RESPONSE, WRONG_CRC, WRONG_DEVICE)
		 * @brief Performs communication to the slave device
		 * @param payload byte array with data to send (without CRC)
		 * @param payload_size size of payload
		 * @param response pointer to response array
		 * @param expected_response_size size of response (including header and crc)
		 * @return last communication error, ModbusError::SUCCESS on success
	*/	
	ModbusError performCommunication(uint8_t payload[], uint8_t payload_size, uint8_t response[], uint8_t expected_response_size, bool raw_data = false);

	
public:

  /**
     * Create a new EasyModbusRTU object. Required params address and comm_stream.
     * If no comm_pin specified doesn't switch during comm (use with full-duplex adapter).
     * @brief Constructor.
     * @param address address of the EasyModbusRTU (param P03.01).
     * @param comm_stream communication stream (Serial1, Serial, VirtualSerial, ecc...).
     * @param baud EasyModbusRTU communication baudrate (param P03.00).
     * @param comm_pin Arduino pin for commutating trasmit/receive mode (added for MAX485 interface).
		 * @param serial_config serial data config (data bits, parity, stop)
  */
  EasyModbusRTU(uint8_t address, Stream& comm_stream);
	EasyModbusRTU(uint8_t address, Stream& comm_stream, uint8_t comm_pin);
	
	
	/**
	   * @brief Starts communication settings
		 * @param baud baudrate
		 * @param 
	*/
	//void begin(unsigned long baud) { begin(baud, SERIAL_8N1); }
  void begin(unsigned long baud);
	
	/**
     * @brief Retrieves last modbus error
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError lastError();
	
	/**
     * @brief Retrieves a given modbus error in human readable 
		 * @param error_number error to be "translated"
     * @return C string of last modbus error in human readable format
  */
	char* errorToString(ModbusError error_number);
	
	/**
     * @brief Retrieves last modbus error in human readable format
     * @return C string of last modbus error in human readable format
  */
  char* lastErrorToString();
	
	/**
     * @brief Reads coils status (function 0x01)
     * @param start_coil 2 byte coil address
     * @param coils_to_read number of coils to read
		 * @param return_var pointer to the variable array to save the coils status into
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError readCoils(uint16_t start_coil, uint16_t coils_to_read, uint16_t return_var[]);
	
	/**
     * @brief Reads dicrete input status (function 0x02)
     * @param start_input 2 byte input address
     * @param inputs_to_read number of coils to read
		 * @param return_var pointer to the variable array to save the inputs status into
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError readDiscreteInputs(uint16_t start_input, uint16_t inputs_to_read, uint16_t return_var[]);
	
	/**
     * @brief Reads multiple holding registers (function 0x03)
     * @param start_register 2 byte register address
     * @param registers_to_read number of registers to read
		 * @param return_var pointer to the variable array to save the registers status into
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError readHoldingRegister(uint16_t start_register, uint16_t registers_to_read, uint16_t return_var[]);
	
	/**
     * @brief Reads multiple input registers (function 0x04)
     * @param start_register 2 byte register address
     * @param registers_to_read number of registers to read
		 * @param return_var pointer to the variable array to save the registers status into
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError readInputRegister(uint16_t start_register, uint16_t registers_to_read, uint16_t return_var[]);
	
	
	/**
     * @brief Write in to a single holding register (function 0x05)
     * @param coil_address address of the coil to write
     * @param value true to set the coil on, false to set the coil off
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError writeSingleCoil(uint16_t coil_address, bool value);
	
	/**
     * @brief Write in to a single holding register (function 0x06)
     * @param register_addr 2 byte register to write into
     * @param value 2 byte value to write into register
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError writeSingleRegister(uint16_t register_addr, uint16_t value);
	
	
	/**
     * @brief Write in to multiple holding register (function 0x16)
     * @param start_register 2 byte register to write into
     * @param registers_to_write number of registers to write into
     * @param value array containing data to write
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError writeMultipleRegister(uint16_t start_register, uint16_t registers_to_write, uint16_t value[]);
	
	/**
	  This functions allow to perform a custom function in the slave.
		Many devices are not 100% modbus compliant or have custom functions.
		This method will add the address and the CRC checksum to the data_to_send payload.
		WARNING: Error checking will cover only a missing and size mismatching response, no other checks (even CRC control) will be performed!
     * @brief Creates a custom function (many "modbus" devices are not 100% modbus compliant)
     * @param function is the custom function wich will be executed
     * @param data_to_send pointer to the array with data to send
     * @param data_to_send_size size of data to send
     * @param response pointer to the array wich will store the response
     * @param expected_response_size expected return bytes
     * @return error or ModbusError::SUCCESS if ok
  */
  ModbusError customFunction(uint8_t function, uint8_t data_to_send[], uint16_t data_to_send_size, uint8_t response[], uint16_t expected_response_size);
	
};


#endif