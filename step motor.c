#include  "reg51.h"
#include <intrins.h>
#include "delay.h"
#include "at24c02.h"
#define uint unsigned int
#define uchar unsigned char
uchar mark;
uint nangle;
sbit MA=P2^0;
sbit MB=P2^1;
sbit MC=P2^2;
sbit MD=P2^3;
sbit MA_2=P1^0;
sbit MB_2=P1^1;
sbit MC_2=P1^2;
sbit MD_2=P1^3;




/*
angle：角度，范围[0,360]
drct：旋转方向，0：顺时针，1：逆时针
speed：转速，范围[1,100]
*/
void MotorRun(uint angle,uint drct,uint speed)
{
	uint step;
	step=0;
	nangle=512*angle/45;//将角度换算成拍数，计算结果自动取整
	if(drct==0)
	{
		while(nangle--)
		{
			
			delay(5);
			switch(step)//8拍方式驱动，每拍转(5.265/64)度
			{
				case 0:MA=1;MB=0;MC=0;MD=0;MA_2=1;MB_2=0;MC_2=0;MD_2=0;break;
				case 1:MA=1;MB=1;MC=0;MD=0;MA_2=1;MB_2=1;MC_2=0;MD_2=0;break;
				case 2:MA=0;MB=1;MC=0;MD=0;MA_2=0;MB_2=1;MC_2=0;MD_2=0;break;
				case 3:MA=0;MB=1;MC=1;MD=0;MA_2=0;MB_2=1;MC_2=1;MD_2=0;break;
				case 4:MA=0;MB=0;MC=1;MD=0;MA_2=0;MB_2=0;MC_2=1;MD_2=0;break;
				case 5:MA=0;MB=0;MC=1;MD=1;MA_2=0;MB_2=0;MC_2=1;MD_2=1;break;
				case 6:MA=0;MB=0;MC=0;MD=1;MA_2=0;MB_2=0;MC_2=0;MD_2=1;break;
				case 7:MA=1;MB=0;MC=0;MD=1;MA_2=1;MB_2=0;MC_2=0;MD_2=1;break;
			}
			if(step==7)step=0;
			else step++;


//			AT24C02_WriteByte(1,nangle);
//			AT24C02_WriteByte(2,0);
			delay(speed);//这里可以适当改动，延时时间短则转速快，但是时间太短会造成电机堵转（不转了）
			
		}
		mark=1;
	}
	else
	{
		while(nangle--)
		{
			
			switch(step)
			{
				case 0:MA=1;MB=0;MC=0;MD=1;MA_2=1;MB_2=0;MC_2=0;MD_2=1;break;
				case 1:MA=0;MB=0;MC=0;MD=1;MA_2=0;MB_2=0;MC_2=0;MD_2=1;break;
				case 2:MA=0;MB=0;MC=1;MD=1;MA_2=0;MB_2=0;MC_2=1;MD_2=1;break;
				case 3:MA=0;MB=0;MC=1;MD=0;MA_2=0;MB_2=0;MC_2=1;MD_2=0;break;
				case 4:MA=0;MB=1;MC=1;MD=0;MA_2=0;MB_2=1;MC_2=1;MD_2=0;break;
				case 5:MA=0;MB=1;MC=0;MD=0;MA_2=0;MB_2=1;MC_2=0;MD_2=0;break;
				case 6:MA=1;MB=1;MC=0;MD=0;MA_2=1;MB_2=1;MC_2=0;MD_2=0;break;
				case 7:MA=1;MB=0;MC=0;MD=0;MA_2=1;MB_2=0;MC_2=0;MD_2=0;break;
			}
			if(step==7)step=0;
			else step++;

//			AT24C02_WriteByte(2,1);
//			AT24C02_WriteByte(1,nangle);
			delay(speed);//这里可以适当改动，延时时间短则转速快，但是时间太短会造成电机堵转（不转了）
			
			delay(5);
		}
		mark=0;
	}
//	MA=0;MB=0;MC=0;MD=0;
}
