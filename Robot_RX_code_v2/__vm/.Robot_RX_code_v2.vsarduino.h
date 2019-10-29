/* 
	Editor: https://www.visualmicro.com/
			visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
			the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
			all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
			note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: ATmega328 on a breadboard (8 MHz internal clock), Platform=avr, Package=breadboard
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 10800
#define ARDUINO_MAIN
#define F_CPU 8000000L
#define __AVR__
//
//
void servoControl();

#include "Arduino.h"
#include "Robot_RX_code_v2.ino"
