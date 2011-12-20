/*****************************************************************************/
/*许继电气股份有限公司                                     版权：2008-2015   */
/*****************************************************************************/
/* 本源代码及其相关文档为河南许昌许继电气股份有限公司独家所有，未经明文许    */
/* 可不得擅自修改或发布，否则将追究相关的法律责任。                          */
/*                                                                           */
/*                      河南许昌许继股份有限公司                             */
/*                      www.xjgc.com                                         */
/*                      (0374) 321 2924                                      */
/*                                                                           */
/*****************************************************************************/


/******************************************************************************
    项目名称    ：  SGE800计量终端业务平台
    文件名         ：  cyclicdb.h
    描          述    ：  本文件用于业务平台库循环存储数据库功能的实现
    版          本    ：  0.1
    作          者    ：  孙锐
    创建日期    ：  2010.04
******************************************************************************/
#ifndef _CYCLICDB_H_
#define _CYCLICDB_H_

/*****************************************************************************
****API
******************************************************************************/
/******************************************************************************
*	函数:	cyclicdb_init
*	功能:	初始化并打开循环数据库
*	参数:	id				-	数据库标号
			pose			-	打开位置
			mode			-	打开方式
			record_len      -   循环存储最大记录数
*	返回:	0				-	成功
			-ERR_INVAL		-	参数错误
			-ERR_SYS		-	系统错误
			-ERR_NOINIT		-	没初始化
			-ERR_BUSY		-	已打开/已存在
			-ERR_NOFILE     -   数据库文件不存在
*	说明:	以DBS_MODE_CREAT方式打开数据库，如果数据库已经创建则会报错-ERR_BUSY，
以DBS_MODE_RD方式打开只读数据库，数据库不存在报错-ERR_NOFILE。
******************************************************************************/
int cyclicdb_init(u8 id, u8 pos, u8 mode, u8 record_len);

/******************************************************************************
 *	函数:	cyclicdb_write
 *	功能:	写循环记录数据（最新的一条记录）
 *	参数:	id				-	数据库标号
 			key_size		-	关键字长度
 			key             -   关键字
            data_size       -   数据大小
            data            -   数据
 *	返回:	0				-	成功
 			-ERR_INVA		-   接口参数配置错误；
 			-ERR_NOFILE		-	数据库未打开
 			-ERR_NOFUN		-	不具备写权限
 			-ERR_NODISK		-	数据长度越限
 			-ERR_TIMEOUT	-	超时
 			-ERR_NORECORD	-	数据纪录不存在
 *	说明:	如果记录数已达到最大记录数，则删除最早的记录，添加最新的第一条记录。
                               如果该关键字下记录不存在，则直接添加第一条新记录
******************************************************************************/
int cyclicdb_write(u8 id, u8 key_size, void *key, u16 data_size, void *data);

/******************************************************************************
  *	函数:	cyclicdb_read
  *	功能:	读取循环记录数据
  *	参数:	id				-	数据库标号
  			key_size		-	关键字长度
  			key             -   关键字
            set             -	记录定位
            max_size        -	data元素指向大小（即返回data缓冲区大小）
 			data_size       -	实际返回数据的长度(输出)
 			data            -	数据
  *	返回:	0				-	成功
  			-ERR_INVA		-   接口参数配置错误；
  			-ERR_NOINIT		-	数据库模块未初始化
  			-ERR_NOFILE		-	数据库未打开
  			-ERR_NOMEM		-	内存错误，数据长度超过接口参数的最大长度
  			-ERR_TIMEOUT	-	超时
  			-ERR_NORECORD	-	数据纪录不存在
  *	说明:	无
 ******************************************************************************/
int cyclicdb_read(u8 id, u8 key_size, void *key, dbs_set_t *set, u16 max_size, u16 *data_size, void  *data);

/******************************************************************************
 *	函数:	cyclicdb_write_t
 *	功能:	写带时间标示的循环记录数据（最新的一条记录）
 *	参数:	id				-	数据库标号
 			key_size		-	关键字长度
 			key             -   关键字
 			time			-   指定时间
            data_size       -   数据大小
            data            -   数据
 *	返回:	0				-	成功
 			-ERR_INVA		-   接口参数配置错误；
 			-ERR_NOFILE		-	数据库未打开
 			-ERR_NOFUN		-	不具备写权限
 			-ERR_NODISK		-	数据长度越限
 			-ERR_TIMEOUT	-	超时
 			-ERR_NORECORD	-	数据纪录不存在
 *	说明:	如果记录数已达到最大记录数，则删除最早的记录，添加最新的第一条记录。
                                如果该关键字下记录不存在，则直接添加第一条新记录
            ！该记录时刻应该大于上一写数据库记录的时刻
******************************************************************************/
int cyclicdb_write_t(u8 id, u8 key_size, void *key, db_t *time, u16 data_size, void  *data);

/******************************************************************************
  *	函数:	cyclicdb_read_t
  *	功能:	按指定时间读取循环记录数据库中的记录
  *	参数:	id				-	数据库标号
  			key_size		-	关键字长度
  			key             -   关键字
  			time			-	指定时间
            max_size        -	data元素指向大小（即返回data缓冲区大小）
 			data_size       -	实际返回数据的长度(输出)
 			data            -	数据
  *	返回:	0				-	成功
  			-ERR_INVA		-   接口参数配置错误；
  			-ERR_NOINIT		-	数据库模块未初始化
  			-ERR_NOFILE		-	数据库未打开
  			-ERR_NOMEM		-	内存错误，数据长度超过接口参数的最大长度
  			-ERR_TIMEOUT	-	超时
  			-ERR_NORECORD	-	数据纪录不存在
  *	说明:	无
 ******************************************************************************/
int cyclicdb_read_t(u8 id, u8 key_size, void *key, db_t *time, u16 max_size, u16 *data_size, void  *data);

/******************************************************************************
   *	函数:	cyclicdb_read_p
   *	功能:	读指定一段时间内循环存储数据库中的记录数据
   *	参数:	id				-	数据库标号
				key_size		-	关键字长度
				key             -   关键字
				from            -	读取记录起始时间
				to              -	读取记录结束时间
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
   *	说明:	数据返回结构是记录长度（时间+数据）+ 时间+记录数据的形式，为低字节在前
******************************************************************************/
int cyclicdb_read_p(u8 id, u8 key_size, void *key, db_t *from, db_t *to, u16 max_size, u16 *size, void *data);

/******************************************************************************
   *	函数:	cyclicdb_read_p
   *	功能:	读指定一段时间内循环存储数据库中的记录数据
   *	参数:	id				-	数据库标号
				key_size		-	关键字长度
				key             -   关键字
				from            -	读取记录起始时间
				to              -	读取记录结束时间
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
   *	说明:	数据返回结构是记录长度（时间+数据）+ 时间+记录数据的形式，为低字节在前
******************************************************************************/
int cyclicdb_read_p(u8 id, u8 key_size, void *key, db_t *from, db_t *to, u16 max_size, u16 *size, void *data);

/******************************************************************************
    *	函数:	cyclicdb_close
    *	功能:	关闭循环记录数据库
    *	参数:	id				-	数据库标号
    *	返回:	0				-	成功
 				-ERR_INVA		-   接口参数配置错误
 				-ERR_NOINIT		-	数据库模块未初始化
 				-ERR_NOFILE		-	数据库未打开
 				-ERR_BUSY		-	未关闭
				-ERR_SYS		-	系统错误
    *	说明:	无
******************************************************************************/
int  cyclicdb_close(u8 id);

/******************************************************************************
      *	函数:	cyclicdb_remove
      *	功能:	删除循环记录数据库
      *	参数:	id				-	数据库标号
      *	返回:	0				-	成功
   				-ERR_INVA		-   接口参数配置错误
   				-ERR_NOINIT		-	数据库模块未初始化
   				-ERR_NOFILE		-	数据库未打开
   				-ERR_BUSY		-	未关闭
 				-ERR_SYS		-	系统错误
      *	说明:	无
 ******************************************************************************/
int  cyclicdb_remove(u8 id);

/******************************************************************************
      *	函数:	cyclicdb_remove
      *	功能:	删除循环记录数据库
      *	参数:	id				-	数据库标号
      *	返回:	0				-	成功
   				-ERR_INVA		-   接口参数配置错误
   				-ERR_NOINIT		-	数据库模块未初始化
   				-ERR_NOFILE		-	数据库未打开
   				-ERR_BUSY		-	未关闭
 				-ERR_SYS		-	系统错误
      *	说明:	无
 ******************************************************************************/
int  cyclicdb_remove(u8 id);
#endif /* CYCLICDB_H_ */
