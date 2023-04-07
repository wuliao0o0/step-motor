#ifndef __EEPROM_H__
#define __EEPROM_H__
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);

#endif