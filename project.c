#include <REGX52.H>
#include "delay.h"
#define uint unsigned int
#define uchar unsigned char
sbit s17=P3^7;
sbit s18=P3^6;
sbit s20=P3^4;
sbit s21=P3^3;

 int key()
{
	int keynumber=0;
	if(s17==0){delay(20);if(s17==0){keynumber=1;}}
	if(s18==0){delay(20);if(s18==0){keynumber=2;}}
	if(s20==0){delay(20);if(s18==0){keynumber=3;}}
	if(s21==0){delay(20);if(s18==0){keynumber=4;}}
	return keynumber;
}