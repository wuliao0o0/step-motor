#include <REGX52.H>
#include "delay.h"
#include "step motor.h"
#include "Timer0.h"
#include "AT24C02.h"
#include "EEPROM.h"
#include "project.h"
void main()
{
//	int dat=50,speed=85;
//	if(dat>0 && dat <100)
//	{
//		dat=AT24C02_ReadByte(1)*45/512+1;
//	}
//	else
//	{
//		dat=100;
//	}
	mark=AT24C02_ReadByte(2);
	while(1)
	{
			MotorRun(100,mark,2);

//		delay(100);
	}
		
}
