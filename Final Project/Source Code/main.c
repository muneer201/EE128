/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab6_Part1
 **     Processor   : MK64FN1M0VLL12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2019-11-03, 13:08, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "FX1.h"
#include "GI2C1.h"
#include "WAIT1.h"
#include "CI2C1.h"
#include "CsIO1.h"
#include "IO1.h"
#include "MCUC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	/* Write your code here */
	uint32_t delay;
	uint8_t ret, who;
	int8_t temp;
	int16_t accX, accY, accZ;
	int16_t magX, magY, magZ;

	printf("Hello\n");

	FX1_Init();

	for(;;) {
		// get WHO AM I values
		if (FX1_WhoAmI(&who)!=ERR_OK) {
			return ERR_FAILED;
		}
		printf("Who Am I value in decimal \t: %4d\n",who);
		for(delay = 0; delay < 300000; delay++); //delay

		// get raw temperature values
		if (FX1_GetTemperature(&temp)!=ERR_OK) {
			return ERR_FAILED;
		}
		printf("RAW Temperature value in decimal \t: %4d\n",temp);
		for(delay = 0; delay < 300000; delay++); //delay

		// Set up registers for accelerometer and magnetometer values
		if (FX1_WriteReg8(FX1_CTRL_REG_1, 0x00) != ERR_OK) {
			return ERR_FAILED;
		}
		if (FX1_WriteReg8(FX1_M_CTRL_REG_1, 0x1F) != ERR_OK) {
			return ERR_FAILED;
		}
		if (FX1_WriteReg8(FX1_M_CTRL_REG_2, 0x20) != ERR_OK) {
			return ERR_FAILED;
		}
		if (FX1_WriteReg8(FX1_XYZ_DATA_CFG, 0x00) != ERR_OK) {
			return ERR_FAILED;
		}
		if (FX1_WriteReg8(FX1_CTRL_REG_1, 0x0D) != ERR_OK) {
			return ERR_FAILED;
		}

		// Get the X Y Z accelerometer values
		accX = FX1_GetX();
		accY = FX1_GetY();
		accZ = FX1_GetZ();
		printf("Accelerometer value \tX: %4d\t Y: %4d\t Z: %4d\n", accX, accY, accZ);
		for(delay = 0; delay < 300000; delay++); //delay

		// Get the X Y Z magnetometer values
		if (FX1_GetMagX(&magX)!=ERR_OK) {
			return ERR_OK;
		}
		if (FX1_GetMagY(&magY)!=ERR_OK) {
			return ERR_OK;
		}
		if (FX1_GetMagZ(&magZ)!=ERR_OK) {
			return ERR_OK;
		}
		printf("Magnetometer value \tX: %4d\t Y: %4d\t Z: %4d\n", magX, magY, magZ);
		for(delay = 0; delay < 300000; delay++); //delay
	}


	/* For example: for(;;) { } */

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.4 [05.11]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
