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
	文件名	：net.h
	描述		：本文件定义了网络模块接口
	版本		：0.1
	作者		：孙锐
	创建日期	：2009.12
******************************************************************************/

#ifndef _NET_H
#define _NET_H

#include "typedef.h"

//网络接收阻塞
#define NET_BLOCK				0           //阻塞方式
#define NET_NONBLOCK			0xff		//非阻塞方式
#define NET_LISTEN_SELECT		1           //服务器监听单线程实现
#define NET_LISTEN				0			//服务器监听多线程实现
/******************************************************************************
*	函数:	net_ip_set
*	功能:	设置IP
*	参数:	ipaddr			-	ip地址
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	参数无效
*	说明:	修改ip后重新建立连接
******************************************************************************/
int net_ip_set(char *ipaddr);

/******************************************************************************
*	函数:	net_gateway_set
*	功能:	设置网关
*	参数:	gateway			-	网关地址
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	参数无效
*	说明:	修改网关后重新建立连接
******************************************************************************/
int net_gateway_set(char *gateway);

/******************************************************************************
*	函数:	net_mask_set
*	功能:	设置mask
*	参数:	mask			-	mask子网掩码地址
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	参数无效
*	说明:	修改后重新建立连接
******************************************************************************/
int net_mask_set(char *mask);

/******************************************************************************
*	函数:	net_client_init
*	功能:	初始化客户端
*	参数:	timout			-	阻塞模式下接收发送超时时间
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
*	说明:	无
******************************************************************************/
int net_client_init(u8 num, u16 timeout);

/******************************************************************************
*	函数:	net_client_connect
*	功能:	客户端与服务器建立连接
*	参数:	ip				-	服务器IP地址
			port			-	服务器端口号
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	接口参数设置错误
 		    -ERR_DISCONNECT	-	服务器未打开
*	说明:	无
******************************************************************************/
int net_client_connect(u8 num, char *ip,u16 port);

/******************************************************************************
*	函数:	net_client_receive
*	功能:	客户端接收数据
*	参数:	buf				-	接收缓冲区地址
            len				-	接收缓冲区大小
            length			-	实际接收大小（输出）
            flag			-	阻塞非阻塞属性：flag=0为阻塞方式（超时时间在初始化中设），0xffff为非阻塞
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	接口参数设置错误
 		    -ERR_TIMEOUT	-	连接超时
 		    -ERR_DISCONNECT	-	网络断开
*	说明:	无
******************************************************************************/
int net_client_receive(u8 num ,u8 *buf, u16 max_length, u16 *length, u8 flag);

/******************************************************************************
*	函数:	net_client_send
*	功能:	客户端发送数据
*	参数:	buf				-	发送缓冲区地址
            length			-	发送字节数
*	返回:	>0				-	成功发送的字节数
			-ERR_INVAL		-	接口参数设置错误
 		    -ERR_TIMEOUT	-	连接超时
 		    -ERR_DISCONNECT	-	网络断开

*	说明:	无
******************************************************************************/
int net_client_send(u8 num, u8 *buf, u16 length);
/******************************************************************************
*	函数:	net_client_disconnect
*	功能:	客户端断开连接
*	参数:	无
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
*	说明:	无
******************************************************************************/
int net_client_disconnect(u8 num);

/******************************************************************************
*	函数:	net_server_init
*	功能:	初始化服务器端
*	参数:	port			-	服务器端口号
			timout			-	阻塞模式下接收发送超时
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
*	说明:	无
******************************************************************************/
int net_server_init(u16 port, u16 timeout);

/******************************************************************************
*	函数:	net_server_connect
*	功能:	与客户端建立新连接
*	参数:	id 				-	连接分配的套接字号（返回）
*	返回:	0				-	成功
			-ERR_TIMEOUT	-	连接超时
			-ERR_SYS		-	系统错误
*	说明:	超时时间在服务器端初始化中设置
******************************************************************************/
 int net_server_connect(u8 *id);

/******************************************************************************
*	函数:	net_server_listen
*	功能:	服务器监听
*	参数:	id 				-	返回监听到的套接字号
			mode			-	（NET_LISTEN_SELECT服务器端单线程实现方式）同时监听服务器套接字和已连接客户端的多个套接字
							-	NET_LISTEN:监听服务器套接字，这种模式下id接口无效
*	返回:	0				-	成功
			-ERR_SYS		-	系统错误
			-ERR_INVAL		-	接口错误

*	说明:	服务器端单线程实现方式id返回Oxff表示有新的连接应调用建立连接函数，
			id返回其他为套接字号为id的连接有数据，应调用服务器接收函数
******************************************************************************/
int net_server_listen(u8 *id, u8 mode);

 /******************************************************************************
 *	函数:	net_server_receive
 *	功能:	服务器接受函数
 *	参数:	id 				-	输入监听到的接收到数据的套接字号
 			buf				- 	返回数据缓冲区
 			max_length		-	返回数据缓冲区的最大
            length			-	实际返回数据的大小
            flag	      	-	flag=0为阻塞方式（超时时间在初始化中设），0xffff为非阻塞
 *	返回:	0				-	成功
 			-ERR_SYS		-	系统错误
 			-ERR_INVAL		-	接口错误
 			-ERR_DISCONNECT	-	连接断开
  			-ERR_TIMEOUT	-	超时
 *	说明:	无
 ******************************************************************************/
 int net_server_receive(u8 id, u8 *buf, u16 max_length,u16 *length, u8 flag);

 /******************************************************************************
 *	函数:	net_server_send
 *	功能:	服务器发送函数
 *	参数:	id 				-	输入要返回数据连接的套接字号
 			buf				- 	发送数据缓冲区
             length			-	发送数据的大小
 *	返回:	>0				-	成功发送的字节数
 			-ERR_INVAL		-	接口错误
 			-ERR_SYS		-	系统错误
 			-ERR_DISCONNECT	-	连接断开
  			-ERR_TIMEOUT	-	超时

 *	说明:	无
 ******************************************************************************/
 int net_server_send(u8 id, u8 *buf,u16 length);

 /******************************************************************************
 *	函数:	net_server_disconnect
 *	功能:	服务器断开连接
 *	参数:	id 				-	输入要返回数据连接的套接字号
 *	返回:	0				-	成功
 			-ERR_SYS		-	系统错误
 			-ERR_INVAL		-	接口错误
 			—ERR_BUSY		-	已断开
 *	说明:	无
 ******************************************************************************/
 int net_server_disconnect(u8 id);

/******************************************************************************
 *	函数:	net_server_close
 *	功能:	服务器关闭
 *	参数:	无
 *	返回:	0				-	成功
 			-ERR_SYS		-	系统错误
 			—ERR_BUSY		-	已关闭
 *	说明:	无
******************************************************************************/
int net_server_close();

#endif
