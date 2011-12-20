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
	文件		：  gpio.h
	描述		：  本文件定义了IO操作模块的接口
	版本		：  0.1
	作者		：  路冉冉
	创建日期	：  2009.12
******************************************************************************/

#ifndef _GPIO_H
#define _GPIO_H


#include "typedef.h"

/*************************************************
  宏定义
*************************************************/
//输入输出
#define GPIO_OUT		0
#define GPIO_IN			1

//od门使能
#define GPIO_ODD		0	//禁止
#define GPIO_ODE		1	//使能

//上拉电阻使能
#define GPIO_PUD		0	//禁止
#define GPIO_PUE		1	//使能


/*************************************************
  结构类型定义
*************************************************/



/*************************************************
  API
*************************************************/
/******************************************************************************
*	函数:	gpio_init
*	功能:	GPIO模块初始化
*	参数:	无
*	返回:	0				-	成功
			-ERR_NOFILE		-	没有此路径
			-ERR_BUSY		-	设备忙，已经打开
			-ERR_SYS		-	初始化锁失败，如内存不足；已经初始化化，但还没销毁；互斥锁地址无效等
*	说明:	无
 ******************************************************************************/
int gpio_init(void);


/******************************************************************************
*	函数:	gpio_set
*	功能:	单个IO设置
*	参数:	io				-	IO口编号
			mode			-	工作模式（输入或输出）
			od				-	OD门使能标志，1表示使能
			pu				-	上拉电阻使能标志，1表示使能
*	返回:	0				-	成功
			-ERR_INVAL 	 	-	参数错误
			-ERR_NODEV 	 	-	无此设备
			-ERR_SYS 	 	-	系统错误，ioctl调用失败
			-ERR_NOINIT  	-	锁没有初始化化
*	说明:	无
 ******************************************************************************/
int gpio_set(u8 io, u8 mode, u8 od, u8 pu);


/******************************************************************************
*	函数:	gpio_output_set
*	功能:	输出模式下设置输出电平状态
*	参数:	io				-	IO口编号
			val				-	输出状态
*	返回:	0				-	成功
			-ERR_INVAL		-	参数错误
			-ERR_NODEV		-	无此设备
			-ERR_NOFUN		-	无此功能
			-ERR_NOCFG		-	没有设置
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	锁没有初始化化
			-ERR_OTHER		-	其他关于线程互斥锁的错误
*	说明:	无
 ******************************************************************************/
int gpio_output_set(u8 io, u8 val);


/******************************************************************************
*	函数:	gpio_output_get
*	功能:	输出模式下获取输出电平状态
*	参数:	io				-	IO口编号
			val				-	输出状态（数据传出）
*	返回:	0				-	成功
			-ERR_NODEV		-	无此设备
			-ERR_NOFUN		-	无此功能
			-ERR_NOCFG		-	没有设置
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	锁没有初始化化
			-ERR_OTHER		-	其他关于线程互斥锁的错误
*	说明:	无
 ******************************************************************************/
int gpio_output_get(u8 io, u8 *val);


/******************************************************************************
*	函数:	gpio_input_get
*	功能:	输入模式下获取输入电平状态
*	参数:	io 				-	IO口编号
			val				-	输入电平状态（数据传出）
*	返回:	0				-	成功
			-ERR_NODEV		-	无此设备
			-ERR_NOFUN		-	无此功能
			-ERR_NOCFG		-	没有设置
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	锁没有初始化化
*	说明:	无
 ******************************************************************************/
int gpio_input_get(u8 io,u8 *val);

/******************************************************************************
*	函数:	gpio_close
*	功能:	GPIO模块关闭函数
*	参数:	无
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	模块未初始化
			-ERR_OTHER		-	当前线程不拥有互斥锁，或锁未初始化
*	说明:	无
 ******************************************************************************/
int gpio_close(void);

#endif  /* _GPIO_H */
