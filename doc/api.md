# class `EasyModbusRTU` {#class_easy_modbus_r_t_u}

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`EasyModbusRTU`](#class_easy_modbus_r_t_u_1af39a609e166e6d7ab4dd8944917aa42b)`(uint8_t address,Stream & comm_stream)` | Constructor.
`public  `[`EasyModbusRTU`](#class_easy_modbus_r_t_u_1a4ee434c99b7a665c03ae35f12867ce0b)`(uint8_t address,Stream & comm_stream,uint8_t comm_pin)` | 
`public void `[`begin`](#class_easy_modbus_r_t_u_1af8f23f5462b568bc453c7d69c28d79b7)`(unsigned long baud)` | Starts communication settings.
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`lastError`](#class_easy_modbus_r_t_u_1ad6c4ee4387f17974ba30d658014e06a5)`()` | Retrieves last modbus error.
`public char * `[`errorToString`](#class_easy_modbus_r_t_u_1af86c1702bde17bffe165eb2494c052cf)`(`[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` error_number)` | Retrieves a given modbus error in human readable.
`public char * `[`lastErrorToString`](#class_easy_modbus_r_t_u_1a5fe6714effbea36ab102095a2a656cbc)`()` | Retrieves last modbus error in human readable format.
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readCoils`](#class_easy_modbus_r_t_u_1a55b19363f9ed31b79d503cdf79aed46e)`(uint16_t start_coil,uint16_t coils_to_read,uint16_t return_var)` | Reads coils status (function 0x01)
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readDiscreteInputs`](#class_easy_modbus_r_t_u_1a9baeda5ca90ddd73ce45987d105ad01d)`(uint16_t start_input,uint16_t inputs_to_read,uint16_t return_var)` | Reads dicrete input status (function 0x02)
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readHoldingRegister`](#class_easy_modbus_r_t_u_1a0be60db0719f135012f5bee3fd38b1d3)`(uint16_t start_register,uint16_t registers_to_read,uint16_t return_var)` | Reads multiple holding registers (function 0x03)
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readInputRegister`](#class_easy_modbus_r_t_u_1aef2ad2f01d50ed3077413ad2ca782e2b)`(uint16_t start_register,uint16_t registers_to_read,uint16_t return_var)` | Reads multiple input registers (function 0x04)
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`writeSingleCoil`](#class_easy_modbus_r_t_u_1a89653c68dd6ac1ca9ceac195eb77e9a8)`(uint16_t coil_address,bool value)` | Write in to a single holding register (function 0x05)
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`writeSingleRegister`](#class_easy_modbus_r_t_u_1a702673f7d42024a55468e0b9e075709a)`(uint16_t register_addr,uint16_t value)` | Write in to a single holding register (function 0x06)
`public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`writeMultipleRegister`](#class_easy_modbus_r_t_u_1a8e52c75e6cf4640566f5a57270b64684)`(uint16_t start_register,uint16_t registers_to_write,uint16_t value)` | Write in to multiple holding register (function 0x16)

## Members

#### `public  `[`EasyModbusRTU`](#class_easy_modbus_r_t_u_1af39a609e166e6d7ab4dd8944917aa42b)`(uint8_t address,Stream & comm_stream)` {#class_easy_modbus_r_t_u_1af39a609e166e6d7ab4dd8944917aa42b}

Constructor.

Create a new [EasyModbusRTU](#class_easy_modbus_r_t_u) object. Required params address and comm_stream. If no comm_pin specified doesn't switch during comm (use with full-duplex adapter). 
#### Parameters
* `address` address of the [EasyModbusRTU](#class_easy_modbus_r_t_u) (param P03.01). 

* `comm_stream` communication stream (Serial1, Serial, VirtualSerial, ecc...). 

* `baud` [EasyModbusRTU](#class_easy_modbus_r_t_u) communication baudrate (param P03.00). 

* `comm_pin` Arduino pin for commutating trasmit/receive mode (added for MAX485 interface). 

* `serial_config` serial data config (data bits, parity, stop)

#### `public  `[`EasyModbusRTU`](#class_easy_modbus_r_t_u_1a4ee434c99b7a665c03ae35f12867ce0b)`(uint8_t address,Stream & comm_stream,uint8_t comm_pin)` {#class_easy_modbus_r_t_u_1a4ee434c99b7a665c03ae35f12867ce0b}

#### `public void `[`begin`](#class_easy_modbus_r_t_u_1af8f23f5462b568bc453c7d69c28d79b7)`(unsigned long baud)` {#class_easy_modbus_r_t_u_1af8f23f5462b568bc453c7d69c28d79b7}

Starts communication settings.

#### Parameters
* `baud` baudrate 

*

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`lastError`](#class_easy_modbus_r_t_u_1ad6c4ee4387f17974ba30d658014e06a5)`()` {#class_easy_modbus_r_t_u_1ad6c4ee4387f17974ba30d658014e06a5}

Retrieves last modbus error.

#### Returns
error or ModbusError::SUCCESS if ok

#### `public char * `[`errorToString`](#class_easy_modbus_r_t_u_1af86c1702bde17bffe165eb2494c052cf)`(`[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` error_number)` {#class_easy_modbus_r_t_u_1af86c1702bde17bffe165eb2494c052cf}

Retrieves a given modbus error in human readable.

#### Parameters
* `error_number` error to be "translated" 

#### Returns
C string of last modbus error in human readable format

#### `public char * `[`lastErrorToString`](#class_easy_modbus_r_t_u_1a5fe6714effbea36ab102095a2a656cbc)`()` {#class_easy_modbus_r_t_u_1a5fe6714effbea36ab102095a2a656cbc}

Retrieves last modbus error in human readable format.

#### Returns
C string of last modbus error in human readable format

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readCoils`](#class_easy_modbus_r_t_u_1a55b19363f9ed31b79d503cdf79aed46e)`(uint16_t start_coil,uint16_t coils_to_read,uint16_t return_var)` {#class_easy_modbus_r_t_u_1a55b19363f9ed31b79d503cdf79aed46e}

Reads coils status (function 0x01)

#### Parameters
* `start_coil` 2 byte coil address 

* `coils_to_read` number of coils to read 

* `return_var` pointer to the variable array to save the coils status into 

#### Returns
error or ModbusError::SUCCESS if ok

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readDiscreteInputs`](#class_easy_modbus_r_t_u_1a9baeda5ca90ddd73ce45987d105ad01d)`(uint16_t start_input,uint16_t inputs_to_read,uint16_t return_var)` {#class_easy_modbus_r_t_u_1a9baeda5ca90ddd73ce45987d105ad01d}

Reads dicrete input status (function 0x02)

#### Parameters
* `start_input` 2 byte input address 

* `inputs_to_read` number of coils to read 

* `return_var` pointer to the variable array to save the inputs status into 

#### Returns
error or ModbusError::SUCCESS if ok

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readHoldingRegister`](#class_easy_modbus_r_t_u_1a0be60db0719f135012f5bee3fd38b1d3)`(uint16_t start_register,uint16_t registers_to_read,uint16_t return_var)` {#class_easy_modbus_r_t_u_1a0be60db0719f135012f5bee3fd38b1d3}

Reads multiple holding registers (function 0x03)

#### Parameters
* `start_register` 2 byte register address 

* `registers_to_read` number of registers to read 

* `return_var` pointer to the variable array to save the registers status into 

#### Returns
error or ModbusError::SUCCESS if ok

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`readInputRegister`](#class_easy_modbus_r_t_u_1aef2ad2f01d50ed3077413ad2ca782e2b)`(uint16_t start_register,uint16_t registers_to_read,uint16_t return_var)` {#class_easy_modbus_r_t_u_1aef2ad2f01d50ed3077413ad2ca782e2b}

Reads multiple input registers (function 0x04)

#### Parameters
* `start_register` 2 byte register address 

* `registers_to_read` number of registers to read 

* `return_var` pointer to the variable array to save the registers status into 

#### Returns
error or ModbusError::SUCCESS if ok

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`writeSingleCoil`](#class_easy_modbus_r_t_u_1a89653c68dd6ac1ca9ceac195eb77e9a8)`(uint16_t coil_address,bool value)` {#class_easy_modbus_r_t_u_1a89653c68dd6ac1ca9ceac195eb77e9a8}

Write in to a single holding register (function 0x05)

#### Parameters
* `coil_address` address of the coil to write 

* `value` true to set the coil on, false to set the coil off 

#### Returns
error or ModbusError::SUCCESS if ok

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`writeSingleRegister`](#class_easy_modbus_r_t_u_1a702673f7d42024a55468e0b9e075709a)`(uint16_t register_addr,uint16_t value)` {#class_easy_modbus_r_t_u_1a702673f7d42024a55468e0b9e075709a}

Write in to a single holding register (function 0x06)

#### Parameters
* `register_addr` 2 byte register to write into 

* `value` 2 byte value to write into register 

#### Returns
error or ModbusError::SUCCESS if ok

#### `public `[`ModbusError`](#_easy_modbus_8h_1a3e91ea9ea1b4d5927573e6ec1d1cce6e)` `[`writeMultipleRegister`](#class_easy_modbus_r_t_u_1a8e52c75e6cf4640566f5a57270b64684)`(uint16_t start_register,uint16_t registers_to_write,uint16_t value)` {#class_easy_modbus_r_t_u_1a8e52c75e6cf4640566f5a57270b64684}

Write in to multiple holding register (function 0x16)

#### Parameters
* `start_register` 2 byte register to write into 

* `registers_to_write` number of registers to write into 

* `value` array containing data to write 

#### Returns
error or ModbusError::SUCCESS if ok

Generated by [Moxygen](https://sourcey.com/moxygen)