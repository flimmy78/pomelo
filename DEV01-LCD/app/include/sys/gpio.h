/**
* gpio -- GPIO�����ӿ�ͷ�ļ�
* 
* 
* ����ʱ��: 2010-4-23
* ����޸�ʱ��: 2010-4-23
*/

#ifndef _GPIO_H
#define _GPIO_H

//GPIO�ܽź�
//x = 0~31
#define GPIO_PA(x)		((unsigned char)0x00|((x)&0x1f))
#define GPIO_PB(x)		((unsigned char)0x20|((x)&0x1f))
#define GPIO_PC(x)		((unsigned char)0x40|((x)&0x1f))
#define GPIO_PD(x)		((unsigned char)0x60|((x)&0x1f))

/**
* @brief ����GPIO�ܽŷ���
* @param io �ܽź�
* @param direct ����, 0����, 1���
*/
void GpioSetDirect(unsigned char io, int direct);
/**
* @brief ����GPIO�ܽ������˲�
* @param io �ܽź�
* @param ison 0�ر�, 1��
*/
void GpioSetDeglitch(unsigned char io, int ison);
/**
* @brief ����GPIO�ܽ������ƽ
* @param io �ܽź�
* @param value 0�͵�ƽ, 1�ߵ�ƽ
*/
void GpioSetValue(unsigned char io, int value);
/**
* @brief ��ȡGPIO�ܽ������ƽ
* @param io �ܽź�
* @return 0�͵�ƽ, 1�ߵ�ƽ
*/
int GpioGetValue(unsigned char io);
/**
* @brief ����CPU�ڲ�UARTģʽ(����)
* @param port UART�˿ں�
* @param mode ģʽ,1ΪRS485ģʽ
*/
void GpioSetUartMode(int port, int mode);

//�ⲿʱ�Ӹ�ʽ
typedef struct {
	unsigned char century;
	unsigned char year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	unsigned char second;
	unsigned char week;
} extclock_t;

/**
* @brief ��ȡ�ⲿʱ��
* @param ʱ�ӱ���ָ��
* @return 0�ɹ�, ����ʧ��
*/
int ExtClockRead(extclock_t *clock);

/**
* @brief �����ⲿʱ��
* @param ʱ�ӱ���ָ��
* @return 0�ɹ�, ����ʧ��
*/
int ExtClockWrite(const extclock_t *clock);

/**
* @brief ��ȡ��������汾��Ϣ
*        �汾��Ϣ����:���汾��(1), �ΰ汾��(1), ����������(3)(BCD��ʽ), ��(1)
* @param buf ������ָ��
* @param len ����������
* @return �ɹ����ض�ȡ����(6�ֽ�), ���򷵻�-1
*/
int ReadDriverVersion(unsigned char *buf, int len);

/**
* @brief ��ȡ��ģ����
* @return ��ģ����
*/
unsigned char ReadLeftModuleNo(void);

/**
* @brief ��ȡ��ģ����
* @return ��ģ����
*/
unsigned char ReadRightModuleNo(void);

//int ReadDriverVersion(unsigned char *buf, int len);

#define GPIO_POWER_12V			GPIO_PB(2)
#define GPIO_POWER_BAT			GPIO_PB(4)

#define GPIO_POWER_STATUS		GPIO_PA(19)
#define GPIO_BATLOW				GPIO_PB(3)
#define GPIO_BAT_CHARGE			GPIO_PB(5)
#define GPIO_POWER_RMODULE		GPIO_PA(24)

#define GPIO_IGT				GPIO_PC(9)

#define GPIO_485_SEL0			GPIO_PC(0)
#define GPIO_485_SEL1			GPIO_PC(2)

#define GPIO_SPI_SEL0			GPIO_PA(20)
#define GPIO_SPI_SEL1			GPIO_PA(21)

#define GPIO_ALARM				GPIO_PC(14)


#define PIN_BASE		32

#define MAX_GPIO_BANKS		5

/* these pin numbers double as IRQ numbers, like AT91xxx_ID_* values */

#define	AT91_PIN_PA0	(PIN_BASE + 0x00 + 0)		//0x20
#define	AT91_PIN_PA1	(PIN_BASE + 0x00 + 1)		//0x21
#define	AT91_PIN_PA2	(PIN_BASE + 0x00 + 2)		//0x22
#define	AT91_PIN_PA4	(PIN_BASE + 0x00 + 4)
#define	AT91_PIN_PA5	(PIN_BASE + 0x00 + 5)
#define	AT91_PIN_PA6	(PIN_BASE + 0x00 + 6)
#define	AT91_PIN_PA7	(PIN_BASE + 0x00 + 7)
#define	AT91_PIN_PA8	(PIN_BASE + 0x00 + 8)
#define	AT91_PIN_PA9	(PIN_BASE + 0x00 + 9)
#define	AT91_PIN_PA10	(PIN_BASE + 0x00 + 10)
#define	AT91_PIN_PA11	(PIN_BASE + 0x00 + 11)
#define	AT91_PIN_PA12	(PIN_BASE + 0x00 + 12)
#define	AT91_PIN_PA13	(PIN_BASE + 0x00 + 13)
#define	AT91_PIN_PA14	(PIN_BASE + 0x00 + 14)
#define	AT91_PIN_PA15	(PIN_BASE + 0x00 + 15)
#define	AT91_PIN_PA16	(PIN_BASE + 0x00 + 16)
#define	AT91_PIN_PA17	(PIN_BASE + 0x00 + 17)
#define	AT91_PIN_PA18	(PIN_BASE + 0x00 + 18)
#define	AT91_PIN_PA19	(PIN_BASE + 0x00 + 19)
#define	AT91_PIN_PA20	(PIN_BASE + 0x00 + 20)
#define	AT91_PIN_PA21	(PIN_BASE + 0x00 + 21)
#define	AT91_PIN_PA22	(PIN_BASE + 0x00 + 22)
#define	AT91_PIN_PA23	(PIN_BASE + 0x00 + 23)
#define	AT91_PIN_PA24	(PIN_BASE + 0x00 + 24)
#define	AT91_PIN_PA25	(PIN_BASE + 0x00 + 25)
#define	AT91_PIN_PA26	(PIN_BASE + 0x00 + 26)
#define	AT91_PIN_PA27	(PIN_BASE + 0x00 + 27)
#define	AT91_PIN_PA28	(PIN_BASE + 0x00 + 28)
#define	AT91_PIN_PA29	(PIN_BASE + 0x00 + 29)
#define	AT91_PIN_PA30	(PIN_BASE + 0x00 + 30)
#define	AT91_PIN_PA31	(PIN_BASE + 0x00 + 31)	//0x3F

#define	AT91_PIN_PB0	(PIN_BASE + 0x20 + 0)
#define	AT91_PIN_PB1	(PIN_BASE + 0x20 + 1)
#define	AT91_PIN_PB2	(PIN_BASE + 0x20 + 2)
#define	AT91_PIN_PB3	(PIN_BASE + 0x20 + 3)
#define	AT91_PIN_PB4	(PIN_BASE + 0x20 + 4)
#define	AT91_PIN_PB5	(PIN_BASE + 0x20 + 5)
#define	AT91_PIN_PB6	(PIN_BASE + 0x20 + 6)
#define	AT91_PIN_PB7	(PIN_BASE + 0x20 + 7)
#define	AT91_PIN_PB8	(PIN_BASE + 0x20 + 8)
#define	AT91_PIN_PB9	(PIN_BASE + 0x20 + 9)
#define	AT91_PIN_PB10	(PIN_BASE + 0x20 + 10)
#define	AT91_PIN_PB11	(PIN_BASE + 0x20 + 11)
#define	AT91_PIN_PB12	(PIN_BASE + 0x20 + 12)
#define	AT91_PIN_PB13	(PIN_BASE + 0x20 + 13)
#define	AT91_PIN_PB14	(PIN_BASE + 0x20 + 14)
#define	AT91_PIN_PB15	(PIN_BASE + 0x20 + 15)
#define	AT91_PIN_PB16	(PIN_BASE + 0x20 + 16)
#define	AT91_PIN_PB17	(PIN_BASE + 0x20 + 17)
#define	AT91_PIN_PB18	(PIN_BASE + 0x20 + 18)
#define	AT91_PIN_PB19	(PIN_BASE + 0x20 + 19)
#define	AT91_PIN_PB20	(PIN_BASE + 0x20 + 20)
#define	AT91_PIN_PB21	(PIN_BASE + 0x20 + 21)
#define	AT91_PIN_PB22	(PIN_BASE + 0x20 + 22)
#define	AT91_PIN_PB23	(PIN_BASE + 0x20 + 23)
#define	AT91_PIN_PB24	(PIN_BASE + 0x20 + 24)
#define	AT91_PIN_PB25	(PIN_BASE + 0x20 + 25)
#define	AT91_PIN_PB26	(PIN_BASE + 0x20 + 26)
#define	AT91_PIN_PB27	(PIN_BASE + 0x20 + 27)
#define	AT91_PIN_PB28	(PIN_BASE + 0x20 + 28)
#define	AT91_PIN_PB29	(PIN_BASE + 0x20 + 29)
#define	AT91_PIN_PB30	(PIN_BASE + 0x20 + 30)
#define	AT91_PIN_PB31	(PIN_BASE + 0x20 + 31)

#define	AT91_PIN_PC0	(PIN_BASE + 0x40 + 0)
#define	AT91_PIN_PC1	(PIN_BASE + 0x40 + 1)
#define	AT91_PIN_PC2	(PIN_BASE + 0x40 + 2)
#define	AT91_PIN_PC3	(PIN_BASE + 0x40 + 3)
#define	AT91_PIN_PC4	(PIN_BASE + 0x40 + 4)
#define	AT91_PIN_PC5	(PIN_BASE + 0x40 + 5)
#define	AT91_PIN_PC6	(PIN_BASE + 0x40 + 6)
#define	AT91_PIN_PC7	(PIN_BASE + 0x40 + 7)
#define	AT91_PIN_PC8	(PIN_BASE + 0x40 + 8)
#define	AT91_PIN_PC9	(PIN_BASE + 0x40 + 9)
#define	AT91_PIN_PC10	(PIN_BASE + 0x40 + 10)
#define	AT91_PIN_PC11	(PIN_BASE + 0x40 + 11)
#define	AT91_PIN_PC12	(PIN_BASE + 0x40 + 12)
#define	AT91_PIN_PC13	(PIN_BASE + 0x40 + 13)
#define	AT91_PIN_PC14	(PIN_BASE + 0x40 + 14)
#define	AT91_PIN_PC15	(PIN_BASE + 0x40 + 15)
#define	AT91_PIN_PC16	(PIN_BASE + 0x40 + 16)
#define	AT91_PIN_PC17	(PIN_BASE + 0x40 + 17)
#define	AT91_PIN_PC18	(PIN_BASE + 0x40 + 18)
#define	AT91_PIN_PC19	(PIN_BASE + 0x40 + 19)
#define	AT91_PIN_PC20	(PIN_BASE + 0x40 + 20)
#define	AT91_PIN_PC21	(PIN_BASE + 0x40 + 21)
#define	AT91_PIN_PC22	(PIN_BASE + 0x40 + 22)
#define	AT91_PIN_PC23	(PIN_BASE + 0x40 + 23)
#define	AT91_PIN_PC24	(PIN_BASE + 0x40 + 24)
#define	AT91_PIN_PC25	(PIN_BASE + 0x40 + 25)
#define	AT91_PIN_PC26	(PIN_BASE + 0x40 + 26)
#define	AT91_PIN_PC27	(PIN_BASE + 0x40 + 27)
#define	AT91_PIN_PC28	(PIN_BASE + 0x40 + 28)
#define	AT91_PIN_PC29	(PIN_BASE + 0x40 + 29)
#define	AT91_PIN_PC30	(PIN_BASE + 0x40 + 30)
#define	AT91_PIN_PC31	(PIN_BASE + 0x40 + 31)

#define	AT91_PIN_PD0	(PIN_BASE + 0x60 + 0)
#define	AT91_PIN_PD1	(PIN_BASE + 0x60 + 1)
#define	AT91_PIN_PD2	(PIN_BASE + 0x60 + 2)
#define	AT91_PIN_PD3	(PIN_BASE + 0x60 + 3)
#define	AT91_PIN_PD4	(PIN_BASE + 0x60 + 4)
#define	AT91_PIN_PD5	(PIN_BASE + 0x60 + 5)
#define	AT91_PIN_PD6	(PIN_BASE + 0x60 + 6)
#define	AT91_PIN_PD7	(PIN_BASE + 0x60 + 7)
#define	AT91_PIN_PD8	(PIN_BASE + 0x60 + 8)
#define	AT91_PIN_PD9	(PIN_BASE + 0x60 + 9)
#define	AT91_PIN_PD10	(PIN_BASE + 0x60 + 10)
#define	AT91_PIN_PD11	(PIN_BASE + 0x60 + 11)
#define	AT91_PIN_PD12	(PIN_BASE + 0x60 + 12)
#define	AT91_PIN_PD13	(PIN_BASE + 0x60 + 13)
#define	AT91_PIN_PD14	(PIN_BASE + 0x60 + 14)
#define	AT91_PIN_PD15	(PIN_BASE + 0x60 + 15)
#define	AT91_PIN_PD16	(PIN_BASE + 0x60 + 16)
#define	AT91_PIN_PD17	(PIN_BASE + 0x60 + 17)
#define	AT91_PIN_PD18	(PIN_BASE + 0x60 + 18)
#define	AT91_PIN_PD19	(PIN_BASE + 0x60 + 19)
#define	AT91_PIN_PD20	(PIN_BASE + 0x60 + 20)
#define	AT91_PIN_PD21	(PIN_BASE + 0x60 + 21)
#define	AT91_PIN_PD22	(PIN_BASE + 0x60 + 22)
#define	AT91_PIN_PD23	(PIN_BASE + 0x60 + 23)
#define	AT91_PIN_PD24	(PIN_BASE + 0x60 + 24)
#define	AT91_PIN_PD25	(PIN_BASE + 0x60 + 25)
#define	AT91_PIN_PD26	(PIN_BASE + 0x60 + 26)
#define	AT91_PIN_PD27	(PIN_BASE + 0x60 + 27)
#define	AT91_PIN_PD28	(PIN_BASE + 0x60 + 28)
#define	AT91_PIN_PD29	(PIN_BASE + 0x60 + 29)
#define	AT91_PIN_PD30	(PIN_BASE + 0x60 + 30)
#define	AT91_PIN_PD31	(PIN_BASE + 0x60 + 31)

#define	AT91_PIN_PE0	(PIN_BASE + 0x80 + 0)
#define	AT91_PIN_PE1	(PIN_BASE + 0x80 + 1)
#define	AT91_PIN_PE2	(PIN_BASE + 0x80 + 2)
#define	AT91_PIN_PE3	(PIN_BASE + 0x80 + 3)
#define	AT91_PIN_PE4	(PIN_BASE + 0x80 + 4)
#define	AT91_PIN_PE5	(PIN_BASE + 0x80 + 5)
#define	AT91_PIN_PE6	(PIN_BASE + 0x80 + 6)
#define	AT91_PIN_PE7	(PIN_BASE + 0x80 + 7)
#define	AT91_PIN_PE8	(PIN_BASE + 0x80 + 8)
#define	AT91_PIN_PE9	(PIN_BASE + 0x80 + 9)
#define	AT91_PIN_PE10	(PIN_BASE + 0x80 + 10)
#define	AT91_PIN_PE11	(PIN_BASE + 0x80 + 11)
#define	AT91_PIN_PE12	(PIN_BASE + 0x80 + 12)
#define	AT91_PIN_PE13	(PIN_BASE + 0x80 + 13)
#define	AT91_PIN_PE14	(PIN_BASE + 0x80 + 14)
#define	AT91_PIN_PE15	(PIN_BASE + 0x80 + 15)
#define	AT91_PIN_PE16	(PIN_BASE + 0x80 + 16)
#define	AT91_PIN_PE17	(PIN_BASE + 0x80 + 17)
#define	AT91_PIN_PE18	(PIN_BASE + 0x80 + 18)
#define	AT91_PIN_PE19	(PIN_BASE + 0x80 + 19)
#define	AT91_PIN_PE20	(PIN_BASE + 0x80 + 20)
#define	AT91_PIN_PE21	(PIN_BASE + 0x80 + 21)
#define	AT91_PIN_PE22	(PIN_BASE + 0x80 + 22)
#define	AT91_PIN_PE23	(PIN_BASE + 0x80 + 23)
#define	AT91_PIN_PE24	(PIN_BASE + 0x80 + 24)
#define	AT91_PIN_PE25	(PIN_BASE + 0x80 + 25)
#define	AT91_PIN_PE26	(PIN_BASE + 0x80 + 26)
#define	AT91_PIN_PE27	(PIN_BASE + 0x80 + 27)
#define	AT91_PIN_PE28	(PIN_BASE + 0x80 + 28)
#define	AT91_PIN_PE29	(PIN_BASE + 0x80 + 29)
#define	AT91_PIN_PE30	(PIN_BASE + 0x80 + 30)
#define	AT91_PIN_PE31	(PIN_BASE + 0x80 + 31)


char get_io_value(unsigned int pin);
void set_io(unsigned int pin,unsigned char cmd);













#endif /*_GPIO_H*/