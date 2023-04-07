/********************************************************************
                            汇诚科技

实现功能:STC12C5A60S2单片机之AT24C04测试程序12T
使用芯片：STC12C5A60S2
晶振：11.0592MHZ
波特率：115200
编译环境：Keil
作者：zhangxinchun
网站：www.ourhc.cn
淘宝店：
汇诚科技 http://ourhc.taobao.com
郑兴电子直销部 http://shop68451856.taobao.com
【声明】此程序仅用于学习与参考，引用请注明版权和作者信息！  
  

*********************************************************************/
#include "REG52.H"
#include "INTRINS.H"
#include "delay.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;

sbit SCL = P1^4;                //AT24C04的时钟
sbit SDA = P1^3;                //AT24C04的数据

BYTE BUF[16];                   //数据缓存区

BYTE code res[6] _at_ 0x23;

BYTE code TESTDATA[] =
{
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
};

/**************************************
向AT24C04写1页(16字节)数据
将TESTDATA开始的16个测试数据写如设备的00~0F地址中
**************************************/

void AT24C04_Start()
{
    SDA = 1;                    //-贌私邼袩
    SCL = 1;                    //-贌时讚袩
    Delay5us();                 //覔时
    SDA = 0;                    //雍屎袀莸覙
    Delay5us();                 //覔时
    SCL = 0;                    //-謲时讚袩
}

/**************************************
停止褏蹍
**************************************/
void AT24C04_Stop()
{
    SDA = 0;                    //-謲私邼袩
    SCL = 1;                    //-贌时讚袩
    Delay5us();                 //覔时
    SDA = 1;                    //雍屎蕪式覙
    Delay5us();                 //覔时
}

void AT24C04_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit AT24C04_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void AT24C04_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    AT24C04_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE AT24C04_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }

    return dat;
}

void AT24C04_WritePage()
{
    BYTE i;

    AT24C04_Start();            //前始褏蹍
    AT24C04_SendByte(0xa0);     //注虓狮迅謽址+写褏蹍
    AT24C04_SendByte(0x00);     //注虓咋寓榨元謽址
    for (i=0; i<16; i++)
    {
        AT24C04_SendByte(TESTDATA[i]);
    }
    AT24C04_Stop();             //停止褏蹍
}

void AT24C04_ReadPage()
{
    BYTE i;

    AT24C04_Start();            //前始褏蹍
    AT24C04_SendByte(0xa0);     //注虓狮迅謽址+写褏蹍
    AT24C04_SendByte(0x00);     //注虓咋寓榨元謽址
    AT24C04_Start();            //前始褏蹍
    AT24C04_SendByte(0xa1);     //注虓狮迅謽址+讈褏蹍
    for (i=0; i<16; i++)
    {
        BUF[i] = AT24C04_RecvByte();
        if (i == 15)
        {
            AT24C04_SendACK(1); //禺鄢一俣私邼穴要堋NAK
        }
        else
        {
            AT24C04_SendACK(0); //軜应ACK
        }
    }
    AT24C04_Stop();             //停止褏蹍
}