/*****************************************************************************
	许继电气股份有限公司			版权：2008-2015

	本源代码及其相关文档为河南许昌许继电气股份有限公司独家所有，未经明文许
	可不得擅自修改或发布，否则将追究相关的法律责任。

						河南许昌许继股份有限公司
						www.xjgc.com
						(0374) 321 2924
*****************************************************************************/


/******************************************************************************
	项目名称	：  SGE800计量智能终端平台
	文件		：  comport.c
	描述		：  本文件实现了串口模块中的API函数
	版本		：  0.1
	作者		：  路冉冉
	创建日期	：  2010.01
******************************************************************************/
//库配置头文件
#include "private/config.h"

#ifdef CFG_COMPORT_MODULE
//驱动调用头文件

//C库头文件

#include <stdio.h>						//printf
#include <fcntl.h>						//open
#include <unistd.h>						//read,write
#include <termios.h>					//串口设置及宏定义
#include <string.h>						//bzero,memcyp
#include <sys/ioctl.h>					//ioctl
#include <errno.h>
#include <sys/mman.h>

//提供给用户的头文件
#include "include/comport.h"
#include "include/error.h"
#include "include/pinio.h"

/*************************************************
  静态全局变量及宏定义
*************************************************/
#ifdef  CFG_GSERIAL_MODULE
#define MAX_COMNUM 8		//如果定义usb转串口，则最大串口数为8
#else
#define MAX_COMNUM 7		//如果没有定义usb转串口，则最大串口数为7
#endif
//#define RS485CMD 0x545f	//设置485模式的控制命令
static struct{
	comport_config_t com;	//配置选项
	int fd;
	struct termios opt;
	u8 count;				//打开计数
	u8 mode;
//	pthread_mutex_t mutex;	
}comport[MAX_COMNUM];

static void * sys_base;
static void * usart_base;
static int mem_fd;
/*************************************************
  API函数实现
*************************************************/

/*************************************************
  操作底层所用到的函数
*************************************************/
#define AT91_SYS			(0xffffc000 )
#define AT91_GPIO_BASE		(0xFFFFF400 - AT91_SYS)
#define AT91_USART_BASE		(0xfffb0000)
#define AT91_USART0			(0xfffb0000 - AT91_USART_BASE)
#define AT91_USART1			(0xfffb4000 - AT91_USART_BASE)
#define AT91_USART2			(0xfffb8000 - AT91_USART_BASE)
#define AT91_USART3			(0xfffd0000 - AT91_USART_BASE)

#define AT91_USART_MR		(0x0004)
//GPIO
#define PIO_PDR		0x04	/* Disable Register */
#define PIO_IDR		0x44	/* Interrupt Disable Register */
#define PIO_PUDR	0x60	/* Pull-up Disable Register */
#define PIO_PUER	0x64	/* Pull-up Enable Register */
#define PIO_ASR		0x70	/* Peripheral A Select Register */
#define PIO_BSR		0x74	/* Peripheral B Select Register */

//static inline void at91_sys_write(unsigned int reg_offset, unsigned long value)
//{
//	//void __iomem *addr = (void __iomem *)AT91_VA_BASE_SYS;
//	*(volatile unsigned long*)(usart_base + reg_offset) = value;
//	//__raw_writel(value, addr + reg_offset);
//}

#define __raw_writel(a,b) (*(volatile unsigned int*)(b) = (a) )
static inline void  *pin_to_controller(unsigned pin)
{
	pin /= 32;
	return sys_base + pin*512 + AT91_GPIO_BASE;

}
static inline unsigned pin_to_mask(unsigned pin)
{
	return 1 << (pin % 32);
}

static int at91_set_A_periph(unsigned pin, int use_pullup)
{
	void *pio = pin_to_controller(pin);
	unsigned	mask = pin_to_mask(pin);

	if (!pio)
		return -1;

	__raw_writel(mask, pio + PIO_IDR);
	__raw_writel(mask, pio + (use_pullup ? PIO_PUER : PIO_PUDR));
	__raw_writel(mask, pio + PIO_ASR);
	__raw_writel(mask, pio + PIO_PDR);
	return 0;
}
static int at91_set_B_periph(unsigned pin, int use_pullup)
{
	void *pio = pin_to_controller(pin);
	unsigned	mask = pin_to_mask(pin);

	if (!pio)
		return -1;

	__raw_writel(mask, pio + PIO_IDR);
	__raw_writel(mask, pio + (use_pullup ? PIO_PUER : PIO_PUDR));
	__raw_writel(mask, pio + PIO_BSR);
	__raw_writel(mask, pio + PIO_PDR);
	return 0;
}
static void  comport_set_serial(u8 comport, u8 is_rtscts)
{

	//COMPORT0用作控制台调试串口，已经在版级驱动中配置。
	switch(comport){
	case COMPORT1:
		at91_set_A_periph(PIN_PB4, 1);		/* TXD0 */
		at91_set_A_periph(PIN_PB5, 0);		/* RXD0 */
		if(is_rtscts){
			at91_set_A_periph(PIN_PB26, 0);	/* RTS0 */
			at91_set_A_periph(PIN_PB27, 0);	/* CTS0 */
		}
		break;
	case COMPORT2:
		at91_set_A_periph(PIN_PB6, 1);		/* TXD1 */
		at91_set_A_periph(PIN_PB7, 0);		/* RXD1 */
		if(is_rtscts){
			at91_set_A_periph(PIN_PB28, 0);	/* RTS1 */
			at91_set_A_periph(PIN_PB29, 0);	/* CTS1 */
		}
	case COMPORT3:
		at91_set_A_periph(PIN_PB8, 1);		/* TXD2 */
		at91_set_A_periph(PIN_PB9, 0);		/* RXD2 */
		if(is_rtscts){
			at91_set_A_periph(PIN_PA4, 0);	/* RTS2 */
			at91_set_A_periph(PIN_PA5, 0);	/* CTS2 */
		}
	case COMPORT4:
		at91_set_A_periph(PIN_PB10, 1);		/* TXD3 */
		at91_set_A_periph(PIN_PB11, 0);		/* RXD3 */
		if(is_rtscts){
			at91_set_B_periph(PIN_PC8, 0);		/* RTS3 */
			at91_set_B_periph(PIN_PC10, 0);	/* CTS3 */
		}
	case COMPORT5:
		at91_set_B_periph(PIN_PA31, 1);		/* TXD4 */
		at91_set_B_periph(PIN_PA30, 0);		/* RXD4 */

	case COMPORT6:
		at91_set_A_periph(PIN_PB12, 1);		/* TXD5 */
		at91_set_A_periph(PIN_PB13, 0);		/* RXD5 */
		break;
	default:
		break;
	}
}
static inline void at91_usmr_write(unsigned int reg_offset)
{
#define		ATMEL_US_USMODE		(0xf <<  0)		/* Mode of the USART */
	//void __iomem *addr = (void __iomem *)AT91_VA_BASE_SYS;
	*(volatile unsigned long*)(usart_base + reg_offset + AT91_USART_MR) &= ~ATMEL_US_USMODE;
	*(volatile unsigned long*)(usart_base + reg_offset + AT91_USART_MR) |= 1;
	//__raw_writel(value, addr + reg_offset);
}
static void  comport_set_485(u8 comport)
{

	switch(comport){
	case COMPORT1:
		at91_set_A_periph(PIN_PB26, 0);	/* RTS0 */
		at91_usmr_write(AT91_USART0);
		break;
	case COMPORT2:
		at91_set_A_periph(PIN_PB28, 0);	/* RTS1 */
		at91_usmr_write(AT91_USART1);
		break;
	case COMPORT3:
		at91_set_A_periph(PIN_PA4, 0);	/* RTS2 */
		at91_usmr_write(AT91_USART2);
		break;
	case COMPORT4:
		at91_set_B_periph(PIN_PC8, 0);	/* RTS3 */
		at91_usmr_write(AT91_USART3);
		break;
	default:
		break;
	}

}
/******************************************************************************
*	函数:	comport_init
*	功能:	打开并初始化串口
*	参数:	port			-	串口端口号
			mode			-	串口操作模式
*	返回:	0				-	成功
			-ERR_SYS			-	错误
			-ERR_INVAL		-	参数错误
			-ERR_BUSY		-	已经打开
*	说明:	无
 ******************************************************************************/
int comport_init (u8 port, u8 mode)
{
	int ret = -1;	

	if((mem_fd = open("/dev/mem",O_RDWR|O_SYNC))==-1){
		ret = -1;
		return ret;
	}
	sys_base = mmap(0,0x3fff, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd,AT91_SYS);
	usart_base = mmap(0,0x24fff, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd,AT91_USART_BASE);

	//ttygs0为usb虚拟串口设备
	char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2","/dev/ttyS3",
				"/dev/ttyS4","/dev/ttyS5","/dev/ttyS6","/dev/ttyGS0"};

	if((port == (MAX_COMNUM - 1)) && (mode == COMPORT_MODE_485)){
		ret = -ERR_INVAL;
		goto err;
	}
	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 1){
		ret = -ERR_BUSY;		//已经打开
		goto err;
	}
	if((mode == COMPORT_MODE_485) || (mode == COMPORT_MODE_NORMAL)){
		;
	}else{
		ret = -ERR_INVAL;
		goto err;
	}
	// com5 com6 不支持485模式
	if((mode == COMPORT_MODE_485) && ((port > COMPORT4)||(port == 0))){
		ret = -ERR_NOFUN;
		goto err;
	}


	//打开串口
	comport[port].fd = open(dev[port], O_RDWR|O_NOCTTY|O_NDELAY);
	if (comport[port].fd < 0){
		//perror("Can't Open Serial Port");
		ret = -ERR_SYS;
		goto err;
	}


	fcntl(comport[port].fd, F_SETFL,0);	//恢复串口阻塞模式

	//测试是否为终端设备
	if(isatty(STDIN_FILENO)==0){
		ret = -ERR_SYS;
		goto err;
	}

	//配置默认串口属性	
	comport[port].com.baud = 9600;	//设置波特率-9600
	comport[port].com.verify = COMPORT_VERIFY_NO;
	comport[port].com.ndata = 8;	//设置数据位-8位
	comport[port].com.nstop = 1;
	comport[port].com.timeout = 0;	//默认阻塞
	comport[port].com.rtscts = COMPORT_RTSCTS_DISABLE;
	
	memset( &comport[port].opt, 0,sizeof( comport[port].opt ) );		
	comport[port].opt.c_cflag  |=  CLOCAL | CREAD; //设置字符大小	
	comport[port].opt.c_cflag &= ~CSIZE; 	
	
	comport[port].opt.c_cflag |= CS8;			//设置数据位-8位
	
	comport[port].opt.c_cflag &= ~PARENB;		//设置奇偶校验-无	

	cfsetispeed(&comport[port].opt, B9600);	//设置波特率-9600
	cfsetospeed(&comport[port].opt, B9600);	
	
	comport[port].opt.c_cflag &=  ~CSTOPB;		//设置停止位-1位
	
	comport[port].opt.c_cc[VTIME]  = 0;		//默认永久阻塞
	comport[port].opt.c_cc[VMIN] = 1;
	
	comport[port].opt.c_cflag &= ~CRTSCTS;		//设置硬件流控-无硬件软件流控
	comport[port].opt.c_iflag &= ~(IXON|IXOFF);

	if((tcsetattr(comport[port].fd, TCSANOW, &comport[port].opt)) != 0)//激活配置
	{
		ret = -ERR_SYS;
		goto err;
	}	
	tcflush(comport[port].fd,TCIFLUSH);//处理未接收字符

	//配置io口引脚功能
	comport_set_serial(port, COMPORT_RTSCTS_DISABLE);

	comport[port].mode = mode;
	comport[port].count = 1;
	if(comport[port].mode == COMPORT_MODE_485){
		comport_set_485(port);
//		ret = ioctl(comport[port].fd, RS485CMD, 0);
//		if(ret < 0){
//			perror("com set error");
//			ret = -ERR_SYS;
//			goto err;
//		}
	}
	ret = 0;
err:
	return ret;
}

/******************************************************************************
*	函数:	comport_setconfig
*	功能:	配置串口
*	参数:	port			-	串口端口号
			cfg				-	配置项（数据传入）
*	返回:	0				-	成功
			-ESYS			-	系统错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	本串口支持的波特率为 50，110，150，300，600，1200，2400，4800，9600
 			115200，460800，4000000
 ******************************************************************************/
int comport_setconfig (u8 port, comport_config_t *cfg)
{
	int ret = -1;

	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 0){
		ret = -ERR_NOINIT;		//没有初始化
		goto err;
	}
	memset( &comport[port].opt, 0,sizeof( comport[port].opt ) );		

	//设置数据位
	switch( cfg->ndata ){
		case 6:		//设置数据位6位
			comport[port].opt.c_cflag |= CS6;
			break;
		case 7:		//设置数据位
			comport[port].opt.c_cflag |= CS7;
			break;
		case 8:		//设置数据位
			comport[port].opt.c_cflag |= CS8;
			break;
		default:
			return -ERR_INVAL;
			break;
	}
	
	//设置奇偶校验位
	switch( cfg->verify){
	case COMPORT_VERIFY_EVEN://奇数
		comport[port].opt.c_cflag |= PARENB;
		comport[port].opt.c_cflag |= PARODD;
		comport[port].opt.c_iflag |= (INPCK | ISTRIP);
		break;
	case COMPORT_VERIFY_ODD: //偶数
		comport[port].opt.c_iflag |= (INPCK | ISTRIP);
		comport[port].opt.c_cflag |= PARENB;
		comport[port].opt.c_cflag &= ~PARODD;
		break;
	case COMPORT_VERIFY_NO:  //无奇偶校验位
		comport[port].opt.c_cflag &= ~PARENB;
		break;
	default:
		return -ERR_INVAL;
		break;
	}
	
	//设置波特率
	switch( cfg->baud){
		case 50:	//波特率
			cfsetispeed(&comport[port].opt, B50);
			cfsetospeed(&comport[port].opt, B50);
			break;
		case 110:	//波特率
			cfsetispeed(&comport[port].opt, B110);
			cfsetospeed(&comport[port].opt, B110);
			break;
		case 150:	//波特率
			cfsetispeed(&comport[port].opt, B150);
			cfsetospeed(&comport[port].opt, B150);
			break;
		case 300:	//波特率
			cfsetispeed(&comport[port].opt, B300);
			cfsetospeed(&comport[port].opt, B300);
			break;
		case 600:	//波特率
			cfsetispeed(&comport[port].opt, B600);
			cfsetospeed(&comport[port].opt, B600);
			break;
		case 1200:	//波特率
			cfsetispeed(&comport[port].opt, B1200);
			cfsetospeed(&comport[port].opt, B1200);
			break;
		case 2400:	//波特率
			cfsetispeed(&comport[port].opt, B2400);
			cfsetospeed(&comport[port].opt, B2400);
			break;
		case 4800:	//波特率
			cfsetispeed(&comport[port].opt, B4800);
			cfsetospeed(&comport[port].opt, B4800);
			break;
		case 9600:	//波特率
			cfsetispeed(&comport[port].opt, B9600);
			cfsetospeed(&comport[port].opt, B9600);
			break;
		case 19200:	//波特率
			cfsetispeed(&comport[port].opt, B19200);
			cfsetospeed(&comport[port].opt, B19200);
			break;
		case 38400:	//波特率
			cfsetispeed(&comport[port].opt, B38400);
			cfsetospeed(&comport[port].opt, B38400);
			break;
		case 57600:	//波特率
			cfsetispeed(&comport[port].opt, B57600);
			cfsetospeed(&comport[port].opt, B57600);
			break;
		case 115200:	//波特率
			cfsetispeed(&comport[port].opt, B115200);
			cfsetospeed(&comport[port].opt, B115200);
			break;
		case 230400:	//波特率
			cfsetispeed(&comport[port].opt, B230400);
			cfsetospeed(&comport[port].opt, B230400);
			break;
		case 460800:	//波特率
			cfsetispeed(&comport[port].opt, B460800);
			cfsetospeed(&comport[port].opt, B460800);
			break;
		case 500000:	//波特率
			cfsetispeed(&comport[port].opt, B500000);
			cfsetospeed(&comport[port].opt, B500000);
			break;
		case 576000:	//波特率
			cfsetispeed(&comport[port].opt, B576000);
			cfsetospeed(&comport[port].opt, B576000);
			break;
		case 921600:	//波特率
			cfsetispeed(&comport[port].opt, B921600);
			cfsetospeed(&comport[port].opt, B921600);
			break;
		case 1000000:	//波特率
			cfsetispeed(&comport[port].opt, B1000000);
			cfsetospeed(&comport[port].opt, B1000000);
			break;
		case 1152000:	//波特率
			cfsetispeed(&comport[port].opt, B1152000);
			cfsetospeed(&comport[port].opt, B1152000);
			break;
	
		case 1500000:	//波特率
			cfsetispeed(&comport[port].opt, B1500000);
			cfsetospeed(&comport[port].opt, B1500000);
			break;
		case 2000000:	//波特率
			cfsetispeed(&comport[port].opt, B2000000);
			cfsetospeed(&comport[port].opt, B2000000);
			break;
		case 2500000:	//波特率
			cfsetispeed(&comport[port].opt, B2500000);
			cfsetospeed(&comport[port].opt, B2500000);
			break;
		case 3000000:	//波特率
			cfsetispeed(&comport[port].opt, B3000000);
			cfsetospeed(&comport[port].opt, B3000000);
			break;		
		case 3500000:	//波特率
			cfsetispeed(&comport[port].opt, B3500000);
			cfsetospeed(&comport[port].opt, B3500000);
			break;
		case 4000000:	//波特率
			cfsetispeed(&comport[port].opt, B4000000);
			cfsetospeed(&comport[port].opt, B4000000);
			break;
		default:
			ret = -ERR_INVAL;
			goto err;
			break;
	}

	
	//设置停止位
	if( cfg->nstop == 1 )
		comport[port].opt.c_cflag &=  ~CSTOPB;
	else if ( cfg->nstop == 2 )				//设置2位停止位
		comport[port].opt.c_cflag |=  CSTOPB;
	else{
		ret = -ERR_INVAL;
		goto err;
	}
	//设定超时时间
	if( (cfg->timeout < 0) || (cfg->timeout > 255) ){
		ret = -ERR_INVAL;
		goto err;
	}
	if(cfg->timeout == 0) {
		comport[port].opt.c_cc[VTIME] 	= 0;
		comport[port].opt.c_cc[VMIN] 	= 1;
	}else if( cfg->timeout == 0xff) {		//不阻塞
		comport[port].opt.c_cc[VTIME]	= 0;
		comport[port].opt.c_cc[VMIN]	= 0;
	}else{
		comport[port].opt.c_cc[VTIME]	= cfg->timeout;
		comport[port].opt.c_cc[VMIN] 	= 0;
	}
	
	//设置硬件流控
	if( cfg->rtscts == COMPORT_RTSCTS_ENABLE ){
		comport[port].opt.c_cflag |= CRTSCTS;
		comport_set_serial(port, 0);
	}else if ( cfg->rtscts == COMPORT_RTSCTS_DISABLE )
		comport[port].opt.c_cflag &= ~CRTSCTS;
	else{
		ret = -ERR_INVAL;
		goto err;
	}
	//激活配置
	if((tcsetattr(comport[port].fd, TCSANOW, &comport[port].opt)) != 0)
	{
		ret = -ERR_SYS;
		goto err;
	}
	//处理未接收字符
	tcflush(comport[port].fd,TCIFLUSH);
	if(comport[port].mode == COMPORT_MODE_485){
		comport_set_485(port);
	}

	memcpy(&comport[port].com,cfg,sizeof(comport_config_t));
	ret = 0;
err:
	return ret;
}

/******************************************************************************
*	函数:	comport_getconfig
*	功能:	获取串口配置
*	参数:	port			-	串口端口号
			cfg				-	配置项（数据传出）
*	返回:	0				-	成功
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_getconfig (u8 port, comport_config_t *cfg)
{
	int ret = -1;
	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 0){
		ret = -ERR_NOINIT;		//没有打开
		goto err;
	}
	memcpy(cfg,&comport[port].com,sizeof(comport_config_t));
	ret = 0;
err:
	return ret;
}

/******************************************************************************
*	函数:	comport_send
*	功能:	串口发送
*	参数:	port			-	串口端口号
			buf				-	数据缓冲区（数据传入）
			count			-	请求字节数
*	返回:	>=0				-	发送成功的字节数
			-ESYS			-	系统错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_send (u8 port, u8 *buf, u32 count)
{
	int ret = -1;
	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if (count == 0){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 0){
		ret = -ERR_NOINIT;		//没有打开
		goto err;
	}
	ret = write(comport[port].fd, buf, count);
	if(ret < 0){
		ret = -ERR_SYS;
		goto err;
	}

err:
	return ret;
}

/******************************************************************************
*	函数:	comport_recv
*	功能:	串口接收
*	参数:	port			-	串口端口号
			buf				-	数据缓冲区（数据传出）
			count			-	请求字节数
*	返回:	>=0				-	接收成功的字节数
			-ERR_SYS		-	错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_recv (u8 port, u8 *buf, u32 count)
{	
	int ret = -1;
	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 0){
		ret = -ERR_NOINIT;		//没有打开
		goto err;
	}
	ret = read(comport[port].fd, buf, count);
	if(ret == 0){		
		ret = -ERR_TIMEOUT;
		goto err;		
	}
	if(ret < 0){		
		ret = -ERR_SYS;		
		goto err;
	}
		
err:
	return ret;
}

/******************************************************************************
*	函数:	comport_flush
*	功能:	清串口缓冲区
*	参数:	port			-	串口端口号
			mode			-	清缓冲区模式
*	返回:	0				-	成功
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_flush (u8 port, u8 mode)
{
	int ret = -1;
	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 0){
		ret = -ERR_NOINIT;		//没有打开
		goto err;
	}
	if(mode == COMPORT_FLUSH_ALL)
		ret = tcflush(comport[port].fd,TCIOFLUSH);
	else if(mode == COMPORT_FLUSH_RD)
		ret = tcflush(comport[port].fd,TCIFLUSH);
	else if(mode == COMPORT_FLUSH_WR)
		ret = tcflush(comport[port].fd,TCOFLUSH);
	else{
		ret = -ERR_INVAL;
		goto err;
	}
	if(ret < 0){		
		ret = -ERR_SYS;		
		goto err;
	}
	ret = 0;
err:
	return ret;
}
	

/******************************************************************************
*	函数:	comport_close
*	功能:	关闭串口
*	参数:	port			-	串口端口号
*	返回:	0				-	成功
			-ERR_SYS		-	错误
			-ERR_INVAL		-	参数无效
			-ERR_NOINIT		-	没有初始化
*	说明:	无
 ******************************************************************************/
int comport_close (u8 port)
{
	int ret = -1;
	if(port < 0 || port >= MAX_COMNUM){
		ret = -ERR_INVAL;
		goto err;
	}
	if(comport[port].count == 0){
		ret = -ERR_NOINIT;		//没有打开
		goto err;
	}
	ret = close(comport[port].fd);
	if(ret < 0){
		return -ERR_SYS;
	}
	comport[port].count = 0;	
	ret = 0;
err:
	return ret;
}
#endif		 //CFG_ADC_MODULE
