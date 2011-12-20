/*****************************************************************************
	许继电气股份有限公司			版权：2008-2015

	本源代码及其相关文档为河南许昌许继电气股份有限公司独家所有，未经明文许
	可不得擅自修改或发布，否则将追究相关的法律责任。

						河南许昌许继股份有限公司
						www.xjgc.com
						(0374) 321 2924
*****************************************************************************/


/*****************************************************************************
	项目名称	：SGE800计量智能终端平台
	文件		：file.h
	描述		：本文件定义了文件操作模块的接口
	版本		：0.1
	作者		：万鸿俊
	创建日期	：2009.12
*****************************************************************************/
	
#ifndef _FILE_H
#define _FILE_H

#include "typedef.h"
/*************************************************
  宏定义
*************************************************/
//文件存放位置
#define FILE_POS_RAM			0					//内存中
#define FILE_POS_FLASH_CODE		1					//FLASH程序区中
#define FILE_POS_FLASH_DATA		2					//FLASH数据区中
#define FILE_POS_SD				3					//SD卡中
#define FILE_POS_U				4					//U盘中

//文件打开模式
#define FILE_MODE_OPEN			0					//以读写方式打开文件，数据库不存在报错
#define FILE_MODE_CREAT			1					//以读写方式打开文件，数据库已存在时报错
#define FILE_MODE_RW			2					//以读写方式打开文件，数据库不存在时创建新库
#define FILE_MODE_RD			3					//以只读方式打开文件，数据库不存在时报错

//偏移参考
#define FILE_SEEK_SET			0					//文件头位置
#define FILE_SEEK_CUR			1					//文件当前操作位置
#define FILE_SEEK_END			2					//文件尾位置
/*************************************************
  结构类型定义
*************************************************/
typedef struct {
	 u8 sec;		//秒：[0 - 59]
	 u8 min;		//分：[0 - 59]
	 u8 hour;		//时：[0 - 23]
	 u8 day;		//日：[1 - 31]
	 u8 mon;		//月: [1 - 12]
	 u8 year;		//年: [2000 - 2255]自从2000年以来的年
} file_time_t;
	



/*************************************************
  API
*************************************************/
/******************************************************************************
*	函数:	file_open
*	功能:	打开文件
*	参数:	name			-	文件名
 			pos				-	文件存放位置
 			mode			-	文件打开模式
*	返回:	>0				-	文件描述符
 			-ERR_INVAL		-	参数错误
 			-ERR_BUSY		-	文件已存在
*	说明:
 ******************************************************************************/
int file_open(char *name, u8 pos, u8 mode);

/******************************************************************************
*	函数:	file_write
*	功能:	写入文件
*	参数:	fd				-	文件描述符
 			buf				-	数据区（数据传入）
 			count			-	请求字节数
*	返回:	>=0				-	写入字节数
 			-ERR_INVAL		-	参数错误
 			-ERR_NOFUN		-	无此功能
 			-ERR_NOMEM		-	缓冲区错误
 			-ERR_NODISK		-	硬盘空间不足
 			-ERR_SYS		-	系统异常
*	说明:
 ******************************************************************************/
int file_write(int fd, void *buf, u32 count);

/******************************************************************************
*	函数:	file_read
*	功能:	读取文件
*	参数:	fd				-	文件描述符
 			buf				-	数据区（数据传出）
 			count			-	请求字节数
*	返回:	>=0				-	读取字节数
 			-ERR_INVAL		-	参数错误
 			-ERR_NOMEM		-	缓冲区错误
 			-ERR_SYS		-	系统异常
*	说明:
 ******************************************************************************/
int file_read(int fd, void *buf, u32 count);

/******************************************************************************
*	函数:	file_seek
*	功能:	移动文件操作指针
*	参数:	fd				-	文件描述符
 			offset			-	偏移值
 			whence			-	偏移参考
*	返回:	0				-	成功
 			-ERR_INVAL		-	参数错误
 			-ERR_SYS		-	系统异常
*	说明:
 ******************************************************************************/
int file_seek(int fd, int offset, u8 whence);

/******************************************************************************
*	函数:	file_close
*	功能:	关闭文件
*	参数:	fd				-	文件描述符
*	返回:	>0				-	文件当前的偏移
 			-ERR_INVAL		-	参数错误
 			-ERR_SYS		-	系统异常
*	说明:
 ******************************************************************************/
int file_close(int fd);

/******************************************************************************
*	函数:	file_delete
*	功能:	删除文件
*	参数:	name			-	文件名
 			pos				-	文件存放位置
*	返回:	0				-	成功
 			-ERR_NOFILE		-	无此文件
 			-ERR_NOMEM		-	内存不足
 			-ERR_SYS		-	系统异常
*	说明:
 ******************************************************************************/
int file_delete(char *name, u8 pos);

/******************************************************************************
*	函数:	file_info
*	功能:	获取文件信息
*	参数:	name			-	文件名
 			pos				-	文件存放位置
 			size			-	文件大小（数据传出）
 			time			-	修改时间（数据传出）
*	返回:	0				-	成功
 			-ERR_NOFILE		-	无此文件
 			-ERR_NOMEM		-	内存不足
 			-ERR_SYS		-	系统异常
*	说明:
 ******************************************************************************/
int file_info(char *name, u8 pos, u32 *size, file_time_t *time);


#endif  /* _FILE_H */

