/******************************************************************************
 * 许继电气股份有限公司                                    版权：2008-2015    *
 ******************************************************************************
 * 本源代码及其相关文档为河南许昌许继电气股份有限公司独家所有，未经明文许     *
 * 可不得擅自修改或发布，否则将追究相关的法律责任。                           *
 *                                                                            *
 *                       河南许昌许继股份有限公司                             *
 *                       www.xjgc.com                                         *
 *                       (0374) 321 2924                                      *
 *                                                                            *
 ******************************************************************************
 * 
 * 项目名称		:	掉电上电检测驱动程序库头文件
 * 文件名		:	powrdlib.h
 * 描述			:	应用程序所用到的ioctl函数的命令
 * 版本			:	1.0.1
 * 作者			:	路冉冉
 *
 ******************************************************************************/
	
#ifndef _POWERCHECKLIB_H
#define _POWERCHECKLIB_H


#define PWRD_IOC_MAGIC 0xEF			//ioctl cmd幻数

#define PWRD_SET_IO		_IO(PWRD_IOC_MAGIC, 2)	//设置要监控的io
#define PWRD_TIMEOUT	_IO(PWRD_IOC_MAGIC, 3)	//设置监控超时时间，单位jiffies
#define PWRD_SET_MODE	_IO(PWRD_IOC_MAGIC, 4)	//设置监控模式，掉电，上电，掉上电

#endif  /* _POWERCHECKLIB_H */
