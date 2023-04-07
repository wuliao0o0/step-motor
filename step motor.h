#ifndef __STEPMOTOR_H__
#define __STEPMOTOR_H__
#define uint unsigned int
#define uchar unsigned char
//void corotation(unsigned char speed);
//void rollback(unsigned char speed);
void MotorRun(uint angle,uint drct,uint speed);
extern uchar mark;
extern uint nangle;
#endif