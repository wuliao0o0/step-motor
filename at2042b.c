/********************************************************************
                            ��ϿƼ�

ʵ�ֹ���:STC12C5A60S2��Ƭ��֮AT24C04���Գ���12T
ʹ��оƬ��STC12C5A60S2
����11.0592MHZ
�����ʣ�115200
���뻷����Keil
���ߣ�zhangxinchun
��վ��www.ourhc.cn
�Ա��꣺
��ϿƼ� http://ourhc.taobao.com
֣�˵���ֱ���� http://shop68451856.taobao.com
���������˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��  
  

*********************************************************************/
#include "REG52.H"
#include "INTRINS.H"
#include "delay.h"

typedef unsigned char BYTE;
typedef unsigned short WORD;

sbit SCL = P1^4;                //AT24C04��ʱ��
sbit SDA = P1^3;                //AT24C04������

BYTE BUF[16];                   //���ݻ�����

BYTE code res[6] _at_ 0x23;

BYTE code TESTDATA[] =
{
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
};

/**************************************
��AT24C04д1ҳ(16�ֽ�)����
��TESTDATA��ʼ��16����������д���豸��00~0F��ַ��
**************************************/

void AT24C04_Start()
{
    SDA = 1;                    //-ٟ˽ߝП
    SCL = 1;                    //-ٟʱדП
    Delay5us();                 //ғʱ
    SDA = 0;                    //ӺʺЂݵҘ
    Delay5us();                 //ғʱ
    SCL = 0;                    //-֍ʱדП
}

/**************************************
ֹͣхۅ
**************************************/
void AT24C04_Stop()
{
    SDA = 0;                    //-֍˽ߝП
    SCL = 1;                    //-ٟʱדП
    Delay5us();                 //ғʱ
    SDA = 1;                    //ӺʺʏʽҘ
    Delay5us();                 //ғʱ
}

void AT24C04_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
bit AT24C04_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ

    return CY;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void AT24C04_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    AT24C04_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
BYTE AT24C04_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }

    return dat;
}

void AT24C04_WritePage()
{
    BYTE i;

    AT24C04_Start();            //ǰʼхۅ
    AT24C04_SendByte(0xa0);     //ע̍ʨѸַ֘+дхۅ
    AT24C04_SendByte(0x00);     //ע̍զԢեԪַ֘
    for (i=0; i<16; i++)
    {
        AT24C04_SendByte(TESTDATA[i]);
    }
    AT24C04_Stop();             //ֹͣхۅ
}

void AT24C04_ReadPage()
{
    BYTE i;

    AT24C04_Start();            //ǰʼхۅ
    AT24C04_SendByte(0xa0);     //ע̍ʨѸַ֘+дхۅ
    AT24C04_SendByte(0x00);     //ע̍զԢեԪַ֘
    AT24C04_Start();            //ǰʼхۅ
    AT24C04_SendByte(0xa1);     //ע̍ʨѸַ֘+ׁхۅ
    for (i=0; i<16; i++)
    {
        BUF[i] = AT24C04_RecvByte();
        if (i == 15)
        {
            AT24C04_SendACK(1); //خ۳һٶ˽ߝѨҪܡNAK
        }
        else
        {
            AT24C04_SendACK(0); //ܘӦACK
        }
    }
    AT24C04_Stop();             //ֹͣхۅ
}