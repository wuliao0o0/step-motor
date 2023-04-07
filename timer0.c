#include <REGX52.H>
void Timer0Init(void)	
{
	TMOD &= 0x0f;		//设置定时器模式
	TL0 = 0x20;		//设置定时初值
	TH0 = 0xd1;
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;
	EA=1;
	PT0=0;
}

//void Timer0_Routine() interrupt 1
//{
//	static uint T0count;
//	TL0 = 0x66;		
//	TH0 = 0xFC;
//	T0count++;
//	if(T0count>=1000)
//	{
//		T0count=0;
//	}
//	
//}