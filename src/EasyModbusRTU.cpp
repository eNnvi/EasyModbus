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
    @file EasyModbusRTU.cpp
    @author Lorenzo Carloni
    @version 0.0.1 06/01/2022
*/

#include "EasyModbusRTU.h"


// Private methods
// Calcs CRC of the message, LSB first
uint16_t EasyModbusRTU::calcCrc(uint8_t* buf, int len) {
	uint16_t crc = 0xFFFF;
  
  for (int pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc
  
    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  uint16_t le_crc = (crc>>8) | (crc<<8);
  return le_crc; 
}

// Checks wether 2 arrays are equal
bool EasyModbusRTU::isEqual(uint8_t* arr1, uint8_t* arr2, int length) {
	for(int i = 0; i < length; i++) {
    if(arr1[i] != arr2[i])
      return false;
  }
  return true;
}


void EasyModbusRTU::clearReadBuffer() {
	while(comm_stream->available()) comm_stream->read(); // clear read buffer!
}

/*
 * On call resets last_error, performs communication, check wether there's any common problem (NO_RESPONSE, WRONG_CRC, WRONG_DEVICE)
 * Performs communication to the slave device
 */
ModbusError EasyModbusRTU::performCommunication(uint8_t payload[], uint8_t payload_size, uint8_t response[], uint8_t expected_response_size, bool raw_data) {
	// reset last error
	last_error = ModbusError::SUCCESS;

	
  uint16_t crc = calcCrc(payload, payload_size); // calculating CRC

  if(comm_pin != -1) { // if using a half duplex TTL converter put in transimt mode
    digitalWrite(comm_pin, CP_TRANSMIT_LEVEL);
  }
	
	clearReadBuffer();
	
  delay(min_timing); // 3.5 char time delay
  comm_stream->write(payload, payload_size);
	comm_stream->write((uint8_t)crc);
	comm_stream->write((uint8_t)(crc >> 8));
  comm_stream->flush(); // waiting end of transmission

  if(comm_pin != -1) { // getting back to receive mode if needed
    digitalWrite(comm_pin, CP_RECEIVE_LEVEL);
  }
	
	// getting response
  long started = millis();
  while(comm_stream->available() < 8 && millis()-started < COMM_TIMEOUT_TIME); // wait response
	
  if(comm_stream->available() != -1 && comm_stream->available() < expected_response_size) { // data size mismatch
    last_error = ModbusError::UNEXPECTED_RESPONSE;
		// even if we have unexpected response could be because of exception handling
  }

  if(comm_stream->available() == -1) {  // if nothing in buffer timeout happened
    last_error = ModbusError::NO_RESPONSE;
    return last_error; // nothing in buffer...
  }
  
  // get the data
  int i = 0;
  while(comm_stream->available()) response[i++] = comm_stream->read();
	
	// if we want raw data only basic checks are made, no CRC control
	if(raw_data) return ModbusError::SUCCESS;

  if(response[0] != address) {  // is the device who's calling our device?
    last_error = ModbusError::WRONG_DEVICE;
    return last_error;
  }
	
	// check exception
	if(last_error == ModbusError::UNEXPECTED_RESPONSE) {
		if(response[1] == payload[1] + 0x80) {	// exception code!
			last_error = errorMappingTable[payload[1] - 1][response[2] - 1];
		}
		return last_error; // exception code or unexpected response
	}
	
	// calc crc on the response
  uint16_t response_crc = calcCrc(response, expected_response_size-2); // calc on all bytes except 2 CRC bytes
  if((uint8_t)(response_crc >> 8) != response[expected_response_size-2] || (uint8_t)response_crc != response[expected_response_size-1]) { // CRC mismatch
    last_error = ModbusError::WRONG_CRC;
    return last_error;
  }
	
	return last_error;
}


// Public Methods

// Constructors
EasyModbusRTU::EasyModbusRTU(uint8_t address, Stream& comm_stream) {
	this->comm_stream = &comm_stream;
  this->address = address;
  this->comm_pin = -1;
  this->last_error = ModbusError::SUCCESS;
}
EasyModbusRTU::EasyModbusRTU(uint8_t address, Stream& comm_stream, uint8_t comm_pin) {
	this->comm_stream = &comm_stream;
  this->address = address;
  this->comm_pin = comm_pin;
  this->last_error = ModbusError::SUCCESS;
}

// Other Methods
void EasyModbusRTU::begin(unsigned long baud) {
	// if we have a half-duplex comm we need to initialize pin direction...
  if(comm_pin != -1) {
    pinMode(comm_pin, OUTPUT);
    digitalWrite(comm_pin, CP_RECEIVE_LEVEL); // ... and get in receive mode
  }
	
	this->baud_rate = baud;
	this->serial_config = serial_config;
	
	this->min_timing = (uint8_t)floor(1000/(baud/10)*3.5f);

	// start serial with our settings!
	//comm_stream->begin(baud_rate, serial_config);
}

// return last error
ModbusError EasyModbusRTU::lastError() {
	return this->last_error;
}

// return a string with error info given the error code
char* EasyModbusRTU::errorToString(ModbusError error_number) {
	switch(error_number) {
		case SUCCESS:
			return "No error";
		case WRONG_CRC:
			return "CRC Mismatch";
		case NO_RESPONSE:
			return "Device did not respond";
		case WRONG_DEVICE:
			return "Wrong device did respond";
		case UNEXPECTED_RESPONSE:
			return "Unexpected response";
		case UNIMPLEMENTED:
			return "Func unimplemented yet";
		case GENERIC:
			return "Generic error";
		case UNEQUAL:
			return "Response is not equal to request";
		case FUNCTION_CODE_UNSUPPORTED:
			return "Device doesn't allow this function";
		case OUTPUT_OUT_OF_RANGE:
			return "Request over device limits";
		case OUT_OF_ADDRESS:
			return "Request over address limits";
		case DEVICE_ERROR:
			return "Error in device";
		case WRONG_DATA_VALUE:
			return "Wrong data format";
		default:
			return "Unknown error";
	}
}

// return a string with last error info
char* EasyModbusRTU::lastErrorToString() {
	return errorToString(last_error);
}

ModbusError EasyModbusRTU::readCoils(uint16_t start_coil, uint16_t coils_to_read, uint16_t return_var[]) {
	return ModbusError::UNIMPLEMENTED;
}

ModbusError EasyModbusRTU::readDiscreteInputs(uint16_t start_input, uint16_t inputs_to_read, uint16_t return_var[]) {
	return ModbusError::UNIMPLEMENTED;
}

ModbusError EasyModbusRTU::readHoldingRegister(uint16_t start_register, uint16_t registers_to_read, uint16_t return_var[]) {
	// request format:
  //  1. address
  //  2. operation (read single register (0x03))
  //  3. First register address high
  //  4. First register address low
  //  5. Number of register to read high
  //  6. Number of register to read low
	uint8_t request[6] = {address, 0x03, (uint8_t)(start_register >> 8), (uint8_t)start_register, (uint8_t)(registers_to_read >> 8), (uint8_t)registers_to_read};
	
	// array wich will contain the response, size is header (3) + registers_to_read*2 + crc (2)
	uint8_t response_size = 5 + (registers_to_read * 2);
	uint8_t response[response_size] = {0};
	
	// request data
	ModbusError comm = performCommunication(request, 6, response, response_size);
	
	if(comm != SUCCESS) return comm; // error handling communication
	
	// now mapping data to given array (or variable)
	for(int i = 0; i < registers_to_read*2; i += 2) {
		return_var[i/2] = (response[i + 3] << 8) | (response[i + 4]);
	}
	
	return SUCCESS;
}

ModbusError EasyModbusRTU::readInputRegister(uint16_t start_register, uint16_t registers_to_read, uint16_t return_var[]) {
	return ModbusError::UNIMPLEMENTED;
}

ModbusError EasyModbusRTU::writeSingleCoil(uint16_t coil_address, bool value) {
	return ModbusError::UNIMPLEMENTED;
}

ModbusError EasyModbusRTU::writeSingleRegister(uint16_t register_addr, uint16_t value) {
	// request format:
  //  1. address
  //  2. operation (write single register (0x06))
  //  3. Register address high
  //  4. Register address low
  //  5. Value high
  //  6. Value low
	uint8_t request[6] = {address, 0x06, (uint8_t)(register_addr >> 8), (uint8_t)register_addr, (uint8_t)(value >> 8), (uint8_t)value};
	
	// array wich will contain the response, response is echo of request, so we have 8 bytes (6 of the request + 2 crc)
	uint8_t response_size = 8;
	uint8_t response[response_size] = {0};
	
	// request data
	ModbusError comm = performCommunication(request, 6, response, response_size);
	
	if(comm != SUCCESS) return comm; // error handling communication
	
	// now check if response is equal
	if(!isEqual(request, response, 6)) {
		last_error = ModbusError::UNEQUAL;
		return ModbusError::UNEQUAL;
	}
	
	return SUCCESS;
}

ModbusError EasyModbusRTU::writeMultipleRegister(uint16_t start_register, uint16_t registers_to_write, uint16_t value[]) {
	return ModbusError::UNIMPLEMENTED;
}

ModbusError EasyModbusRTU::customFunction(uint8_t function, uint8_t data_to_send[], uint16_t data_to_send_size, uint8_t response[], uint16_t expected_response_size) {
	uint8_t payload[data_to_send_size + 2] = {0};
	payload[0] = address;
	payload[1] = function;
	memcpy(payload + 2, data_to_send, data_to_send_size);
	
	uint8_t return_var[expected_response_size + 4] = {0};
	
	// request data (raw format)
	ModbusError comm = performCommunication(payload, data_to_send_size + 2, return_var, expected_response_size + 4, true);
	
	if(comm != SUCCESS) return comm; // error handling communication
	
	// return variable memory copy
	memcpy(response, return_var + 3, expected_response_size);
	
	return SUCCESS;
}