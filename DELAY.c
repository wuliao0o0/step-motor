void delay(int xms)
{
	int i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}
void Delay5us()		//@12.000MHz
{
	unsigned char i;

	i = 12;
	while (--i);
}
