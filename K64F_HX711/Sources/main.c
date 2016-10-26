/* ###################################################################
**     Filename    : main.c
**     Project     : K64F_HX711
**     Processor   : MK64FN1M0VLQ12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-10-09, 16:59, # CodeGen: 0
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
#include "AD1.h"
#include "AdcLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "PD_SCK.h"
#include "BitIoLdd1.h"
#include "DOUT.h"
#include "BitIoLdd2.h"
#include "TU1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TRIG.h"
#include "WAIT1.h"
#include "TU2.h"
#include "KSDK1.h"
#include "PushButton.h"
#include "RED.h"
#include "LEDpin1.h"
#include "BitIoLdd3.h"
#include "GREEN.h"
#include "LEDpin2.h"
#include "BitIoLdd4.h"
#include "BLUE.h"
#include "LEDpin3.h"
#include "BitIoLdd5.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Librerias.h"


static void Measure(void)
{
uint16_t us, cm;
uint8_t buf[8];

	us = US_Measure_us();
//	Term1_SendStr("us :\t");
//	Term1_SendNum(us);
//	Term1_CRLF();
	cm = US_usToCentimeters(us, 22);
	Term1_SendStr("Altura :\t\t\t");
	Term1_SendNum(cm);
	Term1_SendStr("\tcm\r\n");
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
/* Write your local variable definition here */
float peso;

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	US_Init();
	begin(128);
	Term1_SendStr("Lectura del valor del ADC:\t");
	Term1_SendNum(read());
	Term1_CRLF();
	Term1_SendStr("No ponga ningun  objeto sobre la balanza");
	Term1_CRLF();
	Term1_SendStr("Destarando...");
	Term1_CRLF();
	Term1_SendStr("...");
	Term1_CRLF();
	set_scale(5634000); //La escala por defecto es 1
	tare(20);	//El peso actual es considerado Tara.
	Term1_SendStr("Listo para pesar");
	Term1_CRLF();
	TimerDelay(1000);
	Term1_SendStr("Iniciando ...");
	Term1_CRLF();
	Term1_SendStr("------------------------------------------------------\r\n");
	Term1_SendStr("-\t\t\t\t\t\t\t-\r\n");
	Term1_SendStr("-\t\tCeti Colomos\t\t-\r\n");
	Term1_SendStr("-\t\t\t\t\t\t\t-\r\n");
	Term1_SendStr("-\tTelemetria del globo de latex\t-\r\n");
	Term1_SendStr("-\t\t\t\t\t\t\t-\r\n");
	Term1_SendStr("------------------------------------------------------\r\n");
	Term1_CRLF();
	Term1_SendStr("Presiona el boton para iniciar la prueba ...\r\n");
	RED_On();
	GREEN_On();
	BLUE_On();

	for(;;)
	{
		while(!PushButton_GetVal(NULL))
		{
			RED_Off();
			GREEN_Off();
			BLUE_On();
			gsTimer.contador = 5000;
			while(!PushButton_GetVal(NULL))
			{
				if(gsTimer.contador == 0)
				{
					BLUE_Off();
					RED_On();
					Term1_SendStr("\r\nNo ponga ningun  objeto sobre la balanza");
					Term1_CRLF();
					Term1_SendStr("Destarando...");
					Term1_CRLF();
					Term1_SendStr("...");
					Term1_CRLF();
					tare(20);
					TimerDelay(1000);
					RED_Off();
					BLUE_On();
				}
			}
			gsTimer.contador = 0;
			Term1_SendStr("Iniciando prueba ...\r\n");
			peso = get_units(20);
			Term1_SendStr("Peso:\t\t\t");
			Term1_SendFloatNum(peso);
			Term1_SendStr("\tKg\r\n");
			Term1_SendStr("Presion:\t\t");
			Term1_SendFloatNum(MPX5700_Leer());
			Term1_SendStr("\tKpa\r\n");
			Measure();
			Term1_CRLF();
			Term1_SendStr("Prueba realizada con exito\r\n");
			Term1_SendStr("...");
			Term1_CRLF();
			TimerDelay(500); /* wait at least for 50 ms until the next measurement to avoid echos */
			Term1_SendStr("Presiona el boton para reiniciar la prueba ...\r\n");
			BLUE_Off();
			GREEN_On();
		}

	}

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
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
