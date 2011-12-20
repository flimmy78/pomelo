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
	文件		：  led.h
	描述		：  本文件定义了继电器模块的接口
	版本		：  0.1
	作者		：  路冉冉
	创建日期	：  2010.04
******************************************************************************/
#ifndef _LED_H
#define _LED_H

#include "typedef.h"
	
/*************************************************
  静态全局变量及宏定义
*************************************************/
//led编号
#define LED0		0		//端口0
#define LED1		1		//端口1
#define LED2		2		//端口2
#define LED3		3		//端口3
#define LED4		4		//端口4
#define LED5		5		//端口5
#define LED6		6		//端口6
#define LED7		7		//端口7

/*************************************************
  API
*************************************************/
/******************************************************************************
*	函数:	led_init
*	功能:	led模块初始化
*	参数:	无
*	返回:	0				-	成功
			-ERR_CFG		-	配置超限
			-ERR_BUSY		-	已经打开
			-ERR_SYS		-	系统错误
			-ERR_NOFILE		-	没有此路径
 ******************************************************************************/
int led_init(void);

/******************************************************************************
*	函数:	led_on
*	功能:	led条件点亮
*	参数:	id				-	led编号
*			delay			-	延时时间，单位为ms，为0表示没有延时
			last			-	持续时间，单位为ms，为0表示没有持续
			period			-	周期时间，单位为ms，为0表示没有周期
*	返回:	0				-	成功
			-ERR_INVAL		-	参数错误
			-ERR_NOINIT		-	没有初始化
			-ERR_NODEV		-	没有此设备
			-ERR_CFG		-	配置出错
			-ERR_SYS		-	系统错误
*	说明:	3个时间全为0时，表示一直亮, 此处时间精度不高，应>20ms.
 ******************************************************************************/
int led_on(u8 id, u32 delay, u32 last, u32 period);

/******************************************************************************
*	函数:	led_off
*	功能:	led熄灭
*	参数:	id				-	led号
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_CFG		-	配置IO高低与led动作之间的联系出错
*	说明:
 ******************************************************************************/
int led_off(u8 id);

/******************************************************************************
*	函数:	led_check
*	功能:	检查led状态
*	参数:	id				-	led通道号
*	返回:	1				-	动作
			0				-	不动作
			-ERR_TIMEOUT	-	超时
			-ERR_NODEV 		-	无此设备
			-ERR_NOINIT		-	锁没有初始化化
			-ERR_OTHER:		-	其他关于线程互斥锁的错误
			-ERR_SYS		-	系统错误
*	说明:
 ******************************************************************************/
int led_check(u8 id);

/******************************************************************************
*	函数:	led_close
*	功能:	led模块关闭函数
*	参数:	无
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	没有初始化
			-ERR_OTHER		-	其他关于线程互斥锁的错误
			-ERR_CFG		-	配置IO高低与led动作之间的联系出错
*	说明:	无
 ******************************************************************************/
int led_close(void);

#endif		//_LED_H
