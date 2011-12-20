/*****************************************************************************
	许继电气股份有限公司			版权：2008-2015

	本源代码及其相关文档为河南许昌许继电气股份有限公司独家所有，未经明文许
	可不得擅自修改或发布，否则将追究相关的法律责任。

						河南许昌许继股份有限公司
						www.xjgc.com
						(0374) 321 2924
*****************************************************************************/


/******************************************************************************
	项目名称	：SGE800计量智能终端平台
	文件名	：dbs.h
	描述		：本文件定义了数据库模块接口
	版本		：0.1
	作者		：孙锐
	创建日期	：2009.11
******************************************************************************/

#ifndef _DBS_H
#define _DBS_H

#include "typedef.h"
/*************************************************
  宏定义
*************************************************/
#define DBS_POS_RAM           5                    //在内存中打开或者创建数据库
#define DBS_POS_FLASH_CODE    1                    //在FLASH程序区中打开或创建数据库
#define DBS_POS_FLASH_DATA    2                    //在FLASH数据区中打开或创建数据库
#define DBS_POS_SD            3                    //在SD卡中打开或创建数据库
#define DBS_POS_U             4                    //在U盘中打开或创建数据库

#define DBS_MODE_OPEN         0                    //以读写方式打开数据库，数据库不存在报错
#define DBS_MODE_CREAT        1                    //创建新的数据库，此标号数据库已存在时报错
#define DBS_MODE_RW           2                    //以读写方式打开数据库，数据库不存在时创建新库
#define DBS_MODE_RD           3                    //以只读方式打开数据库，数据库不存在时报错

#define DBS_SEEK_SET          0                    //多重记录数据起始位置
#define DBS_SEEK_END          1                    //多重记录数据结束位置

#define DBS_SEEK_FORWARD      0                    //表示在新的读写位置向前插入新的记录
#define DBS_SEEK_BACKWARD     1                    //表示在新的读写位置向后插入新的记录

#define MPOOL_SIZE_MIN        20*1024			   //内存池的最小值

/*************************************************
  结构类型定义
*************************************************/
typedef struct{
	u8 whence;    //基准
	u8 offset;    //位移量
}dbs_set_t;


/*************************************************
  API
*************************************************/

/******************************************************************************
*	函数:	dbs_init
*	功能:	初始化数据库
*	参数:	无
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	参数无效
			-ERR_BUSY		-	已经初始化

*	说明:	初始化数据库环境和数据库变量。
******************************************************************************/
int dbs_init();

/******************************************************************************
*	函数:	dbs_open
*	功能:	打开数据库
*	参数:	id				-	数据库标号
			pose			-	打开位置
			mode			-	打开方式
*	返回:	0				-	成功
			-ERR_INVAL		-	参数错误
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	没初始化
			-ERR_BUSY		-	已打开/已存在
			-ERR_NOFILE     -   数据库文件不存在
*	说明:	以DBS_MODE_CREAT方式打开数据库，如果数据库已经创建则会报错-ERR_BUSY，
以DBS_MODE_RD方式打开只读数据库，数据库不存在报错-ERR_NOFILE。
 ******************************************************************************/
int dbs_open(u8 id, u8 pos, u8 mode);

/******************************************************************************
*	函数:	dbs_insert
*	功能:	写多重记录数据（在该数据关键字的指定位置插入单条记录）
*	参数:	id				-	数据库标号
			key_size		-	关键字长度
			key             -   关键字
            set             -   多重记录定位
            flag            -   多重记录插入标志
            data_size       -   数据大小
            data            -   数据
*	返回:	0				-	成功
			-ERR_INVA		-   接口参数配置错误；
			-ERR_NOFILE		-	数据库未打开
			-ERR_NOFUN		-	不具备写权限
			-ERR_NODISK		-	数据长度越限
			-ERR_TIMEOUT	-	超时
			-ERR_NORECORD	-	记录不存在
			-ERR_NOMEM		-   内存错误
*	说明:	插入记录
 ******************************************************************************/
 int dbs_insert(u8 id, u8 key_size, void *key, dbs_set_t *set, u8 flag, u16 data_size, void  *data);

 /******************************************************************************
 *	函数:	dbs_write
 *	功能:	写多重记录数据（在该数据关键字的指定位置修改替换单条记录）
 *	参数:	id				-	数据库标号
 			key_size		-	关键字长度
 			key             -   关键字
            set             -   多重记录定位
            data_size       -   数据大小
            data            -   数据
 *	返回:	0				-	成功
 			-ERR_INVA		-   接口参数配置错误；
 			-ERR_NOFILE		-	数据库未打开
 			-ERR_NOFUN		-	不具备写权限
 			-ERR_NODISK		-	数据长度越限
 			-ERR_TIMEOUT	-	超时
 			-ERR_NORECORD	-	数据纪录不存在
 *	说明:	修改记录，但是如果修改第一条记录，但是记录不存在不算成错误，直接添加第一条
******************************************************************************/
 int dbs_write(u8 id, u8 key_size, void *key, dbs_set_t *set,u16 data_size, void  *data);
 
 /******************************************************************************
  *	函数:	dbs_multiple_count
  *	功能:	统计多重记录数据的记录条数
  *	参数:	id				-	数据库标号
  			key_size		-	关键字长度
  			key             -   关键字
            count_num       -	多重记录条数（返回）
  *	返回:	0				-	成功
  			-ERR_INVA		-   接口参数配置错误；
  			-ERR_NOFILE		-	数据库未打开
  			-ERR_NODISK		-	数据长度越限
  			-ERR_TIMEOUT	-	超时
  			-ERR_NORECORD	-	数据纪录不存在
  *	说明:	无
 ******************************************************************************/
 int dbs_count(u8 id, u8 key_size, void *key,u32 *count_num);
 
 /******************************************************************************
  *	函数:	dbs_read
  *	功能:	读多重记录数据项中的单条记录数据
  *	参数:	id				-	数据库标号
  			key_size		-	关键字长度
  			key             -   关键字
            set             -	多重记录定位
            max_size        -	data元素指向大小（即返回data缓冲区大小）
 			data_size       -	实际返回数据的长度(输出)
 			data            -	数据（包括记录的长度和数据记录）
  *	返回:	0				-	成功
  			-ERR_INVA		-   接口参数配置错误；
  			-ERR_NOINIT		-	数据库模块未初始化
  			-ERR_NOFILE		-	数据库未打开
  			-ERR_NOMEM		-	内存错误，数据长度超过接口参数的最大长度
  			-ERR_TIMEOUT	-	超时
  			-ERR_NORECORD	-	数据纪录不存在
  *	说明:	无
 ******************************************************************************/
 int dbs_read(u8 id, u8 key_size, void *key, dbs_set_t *set, u16 max_size, u16 *data_size, void  *data);
 
 /******************************************************************************
   *	函数:	dbs_read_bulk
   *	功能:	读多重记录数据项中的多条记录数据
   *	参数:	id				-	数据库标号
				key_size		-	关键字长度
				key             -   关键字
				from            -	读取多重记录一组记录起始定位
				to              -	结束定位
				max_size        -	data元素指向大小（即返回data缓冲区大小）
				data_size       -	实际返回数据的长度(输出)
				data            -	数据（包括记录的长度和数据记录）
   *	返回:	0				-	成功
				-ERR_INVA		-   接口参数配置错误；
				-ERR_NOINIT		-	数据库模块未初始化
				-ERR_NOFILE		-	数据库未打开
				-ERR_NOMEM		-	内存错误，数据长度超过接口参数的最大长度
				-ERR_TIMEOUT	-	超时
				-ERR_NORECORD	-	数据纪录不存在
   *	说明:	数据返回结构是长度+数据的形式
 ******************************************************************************/
int dbs_read_bulk
(u8 id, u8 key_size, void *key, dbs_set_t *from, dbs_set_t *to, u16 max_size, u16 *data_size, void *data);

/******************************************************************************
   *	函数:	dbs_delete
   *	功能:	删除多重记录数据的单条记录
   *	参数:	id				-	数据库标号
				key_size		-	关键字长度
				key             -   关键字
				set             -	多重记录定位
   *	返回:	0				-	成功
				-ERR_INVA		-   接口参数配置错误；
				-ERR_NOINIT		-	数据库模块未初始化
				-ERR_NOFILE		-	数据库未打开（或已关闭）
				-ERR_NOFUN		-	没有此功能（不能删除）
				-ERR_TIMEOUT	-	超时
				-ERR_NORECORD	-	数据纪录不存在
   *	说明:	无
 ******************************************************************************/
 int  dbs_delete(u8 id, u8 key_size, void *key, dbs_set_t *set);
 
 /******************************************************************************
    *	函数:	dbs_delete_bulk
    *	功能:	删除多重记录数据的多条记录
    *	参数:	id				-	数据库标号
 				key_size		-	关键字长度
 				key             -   关键字
 				from            -	读取多重记录一组记录起始定位
 				to              -	结束定位
    *	返回:	0				-	成功
 				-ERR_INVA		-   接口参数配置错误；
 				-ERR_NOINIT		-	数据库模块未初始化
 				-ERR_NOFILE		-	数据库未打开
 				-ERR_NOFUN      -   没有此功能（不能删除）
 				-ERR_TIMEOUT	-	超时
 				-ERR_NORECORD	-	数据纪录不存在
    *	说明:	无
 ******************************************************************************/
 int dbs_delete_bulk(u8 id, u8 key_size, void *key, dbs_set_t *from, dbs_set_t *to);
 
 /******************************************************************************
     *	函数:	dbs_close
     *	功能:	关闭数据库
     *	参数:	id				-	数据库标号
     *	返回:	0				-	成功
  				-ERR_INVA		-   接口参数配置错误
  				-ERR_NODEV		-	未初始化
  				-ERR_NOINIT		-	数据库模块未初始化
  				-ERR_BUSY		-	未关闭
				-ERR_SYS		-	系统错误
     *	说明:	无
 ******************************************************************************/
 int  dbs_close(u8 id);

/******************************************************************************
      *	函数:	dbs_remove
      *	功能:	删除数据库
      *	参数:	id				-	数据库标号
      *	返回:	0				-	成功
   				-ERR_INVAL		-   接口参数配置错误
   				-ERR_NOINIT		-	数据库模块未初始化
   				-ERR_NOFILE		-	数据库未打开
   				-ERR_BUSY		-	未关闭
 				-ERR_SYS		-	系统错误
      *	说明:	无
 ******************************************************************************/
 int  dbs_remove(u8 id);

/******************************************************************************
       *	函数:	dbs_reset
       *	功能:	复位数据库（清空）
       *	参数:	id				-	数据库标号
       *	返回:	0				-	成功
    				-ERR_INVA		-   接口参数配置错误
    				-ERR_BUSY		-	未关闭
					-ERR_SYS		-	系统错误
       *	说明:	无
 ******************************************************************************/
 int  dbs_reset(u8 id);

/******************************************************************************
        *	函数:	dbs_sync
        *	功能:	同步数据库
        *	参数:	id				-	数据库标号
        *	返回:	0				-	成功
     				-ERR_INVA		-   接口参数配置错误
 					-ERR_SYS		-	系统错误
        *	说明:	无
******************************************************************************/
 int  dbs_sync(u8 id);


#endif
