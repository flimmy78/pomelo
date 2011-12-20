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
	文件		：  rtc.h
	描述		：  本文件定义了实时时钟模块接口
	版本		：  0.1
	作者		：  路冉冉
	创建日期	：  2009.12
******************************************************************************/

#ifndef _RTC_H
#define _RTC_H

#include "typedef.h"
/*************************************************
  宏定义
*************************************************/

/*************************************************
  结构类型定义
*************************************************/
typedef struct {
	 u8 sec;		//秒：[0 - 59]
	 u8 min;		//分：[0 - 59]
	 u8 hour;		//时：[0 - 23]
	 u8 day;		//日：[1 - 31]
	 u8 mon;		//月: [1 - 12]
	 u8 year;		//年: [0 - 255]自从2000年以来的年
	 u8 wday;		//周：[1 - 7]
} rtc_time_t;

/*************************************************
  API
*************************************************/
/******************************************************************************
*	函数:	rtc_init
*	功能:	初始化RTC模块
*	参数:	无
*	返回:	0				-	成功
			-ERR_NODEV		-	无此设备
			-ERR_BUSY		-	设备忙，已经打开
			-ERR_SYS		-	初始化锁失败，如内存不足；已经初始化化，但还没销毁；互斥锁地址无效等
*	说明:	无
 ******************************************************************************/
int rtc_init (void);


/******************************************************************************
*	函数:	rtc_gettime
*	功能:	获取实时时钟
*	参数:	time			-	时钟（数据传出）
*	返回:	0				-	成功
			-ERR_INVAL		-	参数错误
			-ERR_NOINIT		-	设备或锁未初始化
			-ERR_SYS		-	系统错误
*	说明:	无
 ******************************************************************************/
int rtc_gettime (rtc_time_t *time);


/******************************************************************************
*	函数:	rtc_settime
*	功能:	设置实时时钟
*	参数:	time			-	时钟（数据传入）
*	返回:	0				-	成功
			-ERR_INVAL		-	参数错误
			-ERR_NOINIT		-	设备或锁未初始化
			-ERR_SYS		-	系统错误
			-ERR_OTHER		-	其他关于线程锁不能解锁的错误
*	说明:	无
 ******************************************************************************/
int rtc_settime (rtc_time_t *time);

/******************************************************************************
*	函数:	rtc_getstat
*	功能:	查询实时时钟的工作状态，是否停振
*	参数:	stat			-	状态（数据传出）
*	返回:	0				-	成功
			-ERR_NOINIT		-	设备或锁未初始化
			-ERR_SYS		-	系统错误
*	说明:	无
 ******************************************************************************/
int rtc_getstat (u8 *stat);

/******************************************************************************
*	函数:	rtc_close
*	功能:	关闭RTC模块
*	参数:	无
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	模块未初始化
			-ERR_OTHER		-	当前线程不拥有互斥锁，或锁未初始化
*	说明:	无
 ******************************************************************************/
int rtc_close (void);


#endif  /* _RTC_H */

