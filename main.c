

#include "stm32l476xx.h"
#include "buttonInterrupts.h"
#include "throttle.h"
#include "initializations.h"
#include "I2C.h"
#include "LCD.h"
#include "SysCLock.h"
#include "INA260.h"
#include "SysTimer.h"
#include "L3GD20.h"
#include "angle.h"
#include "nRF24L01.h"
#include "SPI.h"

int main()
{
	// Initialization
	//	System Clock = 80 MHz
	System_Clock_Init();
	SysTick_Init();

	//	joystick_init();
	//	interrupt_init();

	//PWM starts at 2ms period, 6.5% duty cycle (130us)
	PWM_Init();

	LCD_Initialization();
	LCD_Clear();
	VoltSensor_Init();
	GYRO_Init();
	TRX_RX_Init();

	uint8_t pBuffer[4] = {0};
	uint8_t NumByteToRead = 4;
	uint32_t integerReceived = 0;
	char number[4];

	while (1)
	{

		// //read data recieved
		// readRecievedData(pBuffer, NumByteToRead);
		// integerReceived = 0;
		// integerReceived |= pBuffer[3] << 24;
		// integerReceived |= pBuffer[2] << 16;
		// integerReceived |= pBuffer[1] << 8;
		// integerReceived |= pBuffer[0];

		// sprintf(number, "%d", integerReceived);

		// LCD_DisplayString((uint8_t *)number);
		// //print data recieved

		// //delay 1s
		// delay(1000);
	};

	return 0;
}
