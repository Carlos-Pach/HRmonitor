/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : BT1.h
**     Project     : HRmonitor
**     Processor   : MK64FN1M0VLL12
**     Component   : Bluetooth_EGBT
**     Version     : Component 01.053, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-12-20, 14:30, # CodeGen: 115
**     Abstract    :
**          Driver for e-Gizmo Bluetooth module
**     Settings    :
**          Component name                                 : BT1
**          Firmware                                       : HC06
**          Response timeout (ms)                          : 650
**          CMD Pin                                        : Disabled
**          State Pin                                      : Disabled
**          Rx Pull-Up                                     : Enabled
**            Pin Name                                     : C
**            Pin Number                                   : 14
**          Interfaces                                     : 
**            Shell                                        : CLS1
**            Utility                                      : UTIL1
**            Wait                                         : WAIT1
**            Serial                                       : Serial
**     Contents    :
**         Init                      - void BT1_Init(void);
**         Deinit                    - void BT1_Deinit(void);
**         GetLastError              - BT1_TEnumErrors BT1_GetLastError(void);
**         GetErrorString            - BT1_TConstStringPtr BT1_GetErrorString(BT1_TEnumErrors errorNo);
**         SendATCommand             - byte BT1_SendATCommand(byte *cmd, byte *rxBuf, size_t rxBufSize, byte...
**         StdCmd                    - byte BT1_StdCmd(byte *cmd, byte *rxBuf, size_t rxBufSize, byte...
**         StdOKCmd                  - byte BT1_StdOKCmd(byte *cmd);
**         QueryString               - byte BT1_QueryString(byte *cmd, byte *expectedResponse, byte *string, size_t...
**         btTestUART                - byte BT1_btTestUART(void);
**         btQueryFirmwareVersionStr - byte BT1_btQueryFirmwareVersionStr(byte *buf, size_t bufSize);
**         btSetDeviceName           - byte BT1_btSetDeviceName(byte *name);
**         btSetPairingPasskey       - byte BT1_btSetPairingPasskey(byte *pwd);
**         btSetBaud                 - byte BT1_btSetBaud(dword baud);
**         ParseCommand              - byte BT1_ParseCommand(const unsigned char* cmd, bool *handled, const...
**         RecvChar                  - byte BT1_RecvChar(byte *ch);
**         SendChar                  - byte BT1_SendChar(byte ch);
**         GetCharsInRxBuf           - word BT1_GetCharsInRxBuf(void);
**         StdIOKeyPressed           - bool BT1_StdIOKeyPressed(void);
**         StdIOReadChar             - void BT1_StdIOReadChar(byte *c);
**         StdIOSendChar             - void BT1_StdIOSendChar(byte ch);
**
**Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**All Rights Reserved.
**
**Redistribution and use in source and binary forms, with or without modification,
**are permitted provided that the following conditions are met:
**
**o Redistributions of source code must retain the above copyright notice, this list
**  of conditions and the following disclaimer.
**
**o Redistributions in binary form must reproduce the above copyright notice, this
**  list of conditions and the following disclaimer in the documentation and/or
**  other materials provided with the distribution.
**
**o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**  contributors may be used to endorse or promote products derived from this
**  software without specific prior written permission.
**
**THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**http: www.freescale.com
**mail: support@freescale.com
** ###################################################################*/
/*!
** @file BT1.h
** @version 01.00
** @brief
**          Driver for e-Gizmo Bluetooth module
*/         
/*!
**  @addtogroup BT1_module BT1 module documentation
**  @{
*/         

#ifndef __BT1_H
#define __BT1_H

/* MODULE BT1. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */
#include "CLS1.h"
#include "UTIL1.h"
#include "WAIT1.h"
#include "Serial1.h"

#include "Cpu.h"
#include <stddef.h> /* for size_t */


/* different error IDs as reported by the module */
typedef enum {
  /*  0 */ BT1_COMMAND_ERROR_INVALID_COMMAND=0,
  /*  1 */ BT1_RESULTS_IN_DEFAULT_VALUE,
  /*  2 */ BT1_PSKEY_WRITE_ERROR,
  /*  3 */ BT1_DEVICE_NAME_TOO_LONG,
  /*  4 */ BT1_NO_DEVICE_NAME_SPECIFIED,
  /*  5 */ BT1_BLUETOOTH_ADDRESS_NAP_TOO_LONG,
  /*  6 */ BT1_BLUETOOTH_ADDRESS_UAP_TOO_LONG,
  /*  7 */ BT1_BLUETOOTH_ADDRESS_LAP_TOO_LONG,
  /*  8 */ BT1_PIO_MAP_NOT_SPECIFIED,
  /*  9 */ BT1_INVALID_PIO_PORT_NUMBER,
  /*  A */ BT1_DEVICE_CLASS_NOT_SPECIFIED,
  /*  B */ BT1_DEVICE_CLASS_TOO_LONG,
  /*  C */ BT1_INQUIRE_ACCESS_CODE_NOT_SPECIFIED,
  /*  D */ BT1_INQUIRE_ACCESS_CODE_TOO_LONG,
  /*  E */ BT1_INVALID_INQUIRE_ACCESS_CODE_ENTERED,
  /*  F */ BT1_PAIRING_PASSWORD_NOT_SPECIFIED,
  /* 10 */ BT1_PAIRING_PASSWORD_TOO_LONG,
  /* 11 */ BT1_INVALID_ROLE_ENTERED,
  /* 12 */ BT1_INVALID_BAUD_RATE_ENTERED,
  /* 13 */ BT1_INVALID_STOP_BIT_ENTERED,
  /* 14 */ BT1_INVALID_PARITY_BIT_ENTERED,
  /* 15 */ BT1_NO_DEVICE_IN_PARING_LIST,
  /* 16 */ BT1_SPP_NOT_SPECIFIED,
  /* 17 */ BT1_SPP_ALREADY_INITIALIZED,
  /* 18 */ BT1_INVALID_INQUIRY_MODE,
  /* 19 */ BT1_INQUIRY_TIMEOUT_OCCURED,
  /* 1A */ BT1_INVALID_ZERO_LENGTH_ADDRESS_ENTERED,
  /* 1B */ BT1_INVALID_SECURITY_MODE_ENTERED,
  /* 1C */ BT1_INVALID_ENCRYPTION_MODE_ENTERED,
           BT1_NO_ERROR /* must be last in list!!! */
} BT1_TEnumErrors;

typedef enum {
  BT1_BAUD_1200 = 1200,
  BT1_BAUD_2400 = 2400,
  BT1_BAUD_4800 = 4800,
  BT1_BAUD_9600 = 9600,
  BT1_BAUD_19200 = 19200,
  BT1_BAUD_38400 = 38400,
  BT1_BAUD_57600 = 57600,
  BT1_BAUD_115200 = 115200
  /* higher baud is intentionally not supported here, as it might be impossible to connect to the module */
} BT1_BaudMode;

typedef const unsigned char *BT1_TConstStringPtr; /* type for constant string pointer */

#define BT1_MAX_AT_CMD_SIZE                         (sizeof("AT+NAME=LongestPossibleName\r\n"))  /* longest AT command */
#define BT1_MAX_RESPONSE_SIZE                       42  /* maximum response size, e.g. "+NAME:abcdef\r\nOK\r\n" */
#define BT1_MAX_ERR_RESPONSE_SIZE                   (sizeof("ERROR:(32)\r\n"))  /* max size of error response */
#define BT1_MAX_DEVICE_NAME_SIZE                    31  /* device name can be up to 31 characters */
#define BT1_TIMEOUT_MS                              650 /* timeout in ms to wait for response */
#define BT1_TIMEOUT_MS_AFTER_RESET                  2000 /* timeout in ms after a reset command */
#define BT1_TIMEOUT_MS_AFTER_FACTORY_DEFAULT        BT1_TIMEOUT_MS_AFTER_RESET /* timeout after a factory default command */

#define BT1_PARSE_COMMAND_ENABLED  1  /* set to 1 if method ParseCommand() is present, 0 otherwise */

extern CLS1_ConstStdIOType BT1_stdio; /* default standard I/O */
extern uint8_t BT1_DefaultShellBuffer[CLS1_DEFAULT_SHELL_BUFFER_SIZE]; /* default buffer which can be used by the application */

/* Either BT1_FIRMWARE_HC05 or BT1_FIRMWARE_HC06 is defined here */
#define BT1_FIRMWARE_HC06 /* limited Linvor/HC06 firmware, no \r\n, only slave mode, limited set of commands */

BT1_TEnumErrors BT1_GetLastError(void);
/*
** ===================================================================
**     Method      :  BT1_GetLastError (component Bluetooth_EGBT)
**     Description :
**         Returns the last error reported by the device.
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

BT1_TConstStringPtr BT1_GetErrorString(BT1_TEnumErrors errorNo);
/*
** ===================================================================
**     Method      :  BT1_GetErrorString (component Bluetooth_EGBT)
**     Description :
**         Returns for a given error code the error string describing
**         the problem.
**     Parameters  :
**         NAME            - DESCRIPTION
**         errorNo         - 
**     Returns     :
**         ---             - Error string
** ===================================================================
*/

void BT1_Init(void);
/*
** ===================================================================
**     Method      :  BT1_Init (component Bluetooth_EGBT)
**     Description :
**         Initializes the module
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void BT1_Deinit(void);
/*
** ===================================================================
**     Method      :  BT1_Deinit (component Bluetooth_EGBT)
**     Description :
**         Deinitializes the module
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

byte BT1_btTestUART(void);
/*
** ===================================================================
**     Method      :  BT1_btTestUART (component Bluetooth_EGBT)
**     Description :
**         Tests the UAR connection with AT
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_StdCmd(byte *cmd, byte *rxBuf, size_t rxBufSize, byte *expectedResponse);
/*
** ===================================================================
**     Method      :  BT1_StdCmd (component Bluetooth_EGBT)
**     Description :
**         Send standard command: "<cmd>\r
**         " ==> "<expectedResponse>"
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command string
**       * rxBuf           - Pointer to buffer for the answer
**         rxBufSize       - 
**       * expectedResponse - Pointer to
**                           expected response
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_StdOKCmd(byte *cmd);
/*
** ===================================================================
**     Method      :  BT1_StdOKCmd (component Bluetooth_EGBT)
**     Description :
**         Send standard command: "<cmd>\r
**         " ==> "OK\r
**         "
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command string
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_QueryString(byte *cmd, byte *expectedResponse, byte *string, size_t stringSize);
/*
** ===================================================================
**     Method      :  BT1_QueryString (component Bluetooth_EGBT)
**     Description :
**         get string from device: "<cmd>\r
**         " ==> "<response><string>\r
**         OK\r
**         "
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command string
**       * expectedResponse - Pointer to
**                           expected response string
**       * string          - Pointer to buffer where to store the
**                           string value
**         stringSize      - 
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_btQueryFirmwareVersionStr(byte *buf, size_t bufSize);
/*
** ===================================================================
**     Method      :  BT1_btQueryFirmwareVersionStr (component Bluetooth_EGBT)
**     Description :
**         Queries the firmware version
**     Parameters  :
**         NAME            - DESCRIPTION
**       * buf             - Pointer to buffer where to store the string
**         bufSize         - Size of the buffer in bytes.
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_btSetDeviceName(byte *name);
/*
** ===================================================================
**     Method      :  BT1_btSetDeviceName (component Bluetooth_EGBT)
**     Description :
**         Sets the device name
**     Parameters  :
**         NAME            - DESCRIPTION
**       * name            - Pointer to new device name
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_btSetPairingPasskey(byte *pwd);
/*
** ===================================================================
**     Method      :  BT1_btSetPairingPasskey (component Bluetooth_EGBT)
**     Description :
**         Sets the pairing passkey
**     Parameters  :
**         NAME            - DESCRIPTION
**       * pwd             - Pointer to new pairing passkey
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_SendATCommand(byte *cmd, byte *rxBuf, size_t rxBufSize, byte *expectedTailStr);
/*
** ===================================================================
**     Method      :  BT1_SendATCommand (component Bluetooth_EGBT)
**     Description :
**         Sends an AT command string (with the AT in it) to the module.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to AT command string with the AT
**                           in it
**       * rxBuf           - Pointer to buffer for the response
**                           from the device
**         rxBufSize       - size of the receiving buffer
**                           in bytes
**       * expectedTailStr - Pointer to the
**                           function will read from the device until
**                           the expected tail string is read. Typically
**                           this is "OK" terminated by backslash r and
**                           backslash n
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

byte BT1_ParseCommand(const unsigned char* cmd, bool *handled, const CLS1_StdIOType *io);
/*
** ===================================================================
**     Method      :  BT1_ParseCommand (component Bluetooth_EGBT)
**     Description :
**         Shell Command Line parser. Method is only available if Shell
**         is enabled in the component properties.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * cmd             - Pointer to command string
**       * handled         - Pointer to variable which tells if
**                           the command has been handled or not
**       * io              - Pointer to I/O structure
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define BT1_RecvChar(chP) \
  Serial1_RecvChar(chP)
/*
** ===================================================================
**     Method      :  BT1_RecvChar (component Bluetooth_EGBT)
**     Description :
**         Receives a character from the Bluetooth serial bridge
**     Parameters  :
**         NAME            - DESCRIPTION
**       * ch              - Pointer to character buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define BT1_SendChar(ch) \
  Serial1_SendChar(ch)
/*
** ===================================================================
**     Method      :  BT1_SendChar (component Bluetooth_EGBT)
**     Description :
**         Sends a character to the Bluetooth serial bridge
**     Parameters  :
**         NAME            - DESCRIPTION
**         ch              - Character to be sent
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define BT1_GetCharsInRxBuf() \
  Serial1_GetCharsInRxBuf()
/*
** ===================================================================
**     Method      :  BT1_GetCharsInRxBuf (component Bluetooth_EGBT)
**     Description :
**         Returns the numbers of character in the receiver buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of characters.
** ===================================================================
*/

bool BT1_StdIOKeyPressed(void);
/*
** ===================================================================
**     Method      :  BT1_StdIOKeyPressed (component Bluetooth_EGBT)
**     Description :
**         StdIO handler for Shell
**     Parameters  : None
**     Returns     :
**         ---             - True if there are characters in the
**                           input/RX buffer
** ===================================================================
*/

void BT1_StdIOReadChar(byte *c);
/*
** ===================================================================
**     Method      :  BT1_StdIOReadChar (component Bluetooth_EGBT)
**     Description :
**         StdIO Handler for reading a character. It reads a zero byte
**         if there is no character.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * c               - Pointer to result character
**     Returns     : Nothing
** ===================================================================
*/

void BT1_StdIOSendChar(byte ch);
/*
** ===================================================================
**     Method      :  BT1_StdIOSendChar (component Bluetooth_EGBT)
**     Description :
**         StdIO handler to sends a character 
**     Parameters  :
**         NAME            - DESCRIPTION
**         ch              - character to send
**     Returns     : Nothing
** ===================================================================
*/

byte BT1_btSetBaud(dword baud);
/*
** ===================================================================
**     Method      :  BT1_btSetBaud (component Bluetooth_EGBT)
**     Description :
**         Sets the baud rate of the device.
**     Parameters  :
**         NAME            - DESCRIPTION
**         baud            - 1200, 2400, 4800, 9600, 19200, 38400,
**                           57600, 115200
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

/* END BT1. */

#endif
/* ifndef __BT1_H */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
