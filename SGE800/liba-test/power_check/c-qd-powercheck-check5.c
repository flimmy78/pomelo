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
    项目名称    ：  SGE800计量智能终端平台
    文件名      ：  c-qd-powercheck-check.c
    描述        ：  本文件用于平台库powercheck_check函数的测试用例4，性能测试2
    版本        ：  0.1
    作者        ：  左伟杰
    创建日期    ：  2010.03
******************************************************************************/

//C库头文件
#include <stdio.h>		//printf
#include <stdlib.h>		//exit
#include <unistd.h>		//sleep
#include <db.h>

//平台库头文件
#include "../include/dbs.h"
#include "../include/xj_assert.h"
#include "../include/error.h"

//测试程序头文件
#include "../include/powercheck.h"
#include "../include/gpio.h"
#include "../include/thread.h"

//声明线程处理函数
void *thread_function1(void *arg);
void *thread_function2(void *arg);


//声明全局变量
u8 io_check = 32;						//pb0检测掉电处理时间
u8 io_clearval = 0;
u8 io_setval = 1;						//I/O口输出高
u8 io_trigger = 35;						//pb3触发掉电处理

int main()
{
	/*power_check相关变量*/
	int ret = -1;
	u8 mode;
	u16 set_timeout = 1000;

	/*I/O口相关变量*/
	u8 io_mode, io_od, io_pu;


	/*线程相关变量*/
	u8 mode_thread1, mode_thread2, prio_thread1, prio_thread2;
	u8 id_thread1, id_thread2;						//线程ID
	mode_thread1 = THREAD_MODE_NORMAL;
	mode_thread2 = THREAD_MODE_REALTIME;
	prio_thread1 = 0;
	prio_thread2 = 1;

	int i;

	//环境初始化
	inittest();

	//测试用例4
	io_mode = GPIO_OUT;
	io_od = GPIO_ODD;
	io_pu = GPIO_PUD;

	ret = gpio_init();										//初始化I/O口
	if(ret != 0){
		printf("gpio_init error\r\n");
	}

	ret = gpio_set(io_check, io_mode, io_od, io_pu);		//设置pb0为输出口
	if(ret != 0){
		printf("gpio_set error\r\n");
	}
	ret = gpio_set(io_trigger, io_mode, io_od, io_pu);		//设置pb0为输出口
	if(ret != 0){
		printf("gpio_set error\r\n");
	}
	gpio_output_set(io_trigger, io_setval);					//PB3口输出低，模拟为掉电
	gpio_output_set(io_check, io_setval);					//PB0口输出低，掉电检测函数执行完成后置高


	ret = thread_init();									//初始化线程处理模块
	if(ret != 0){
		printf("thread init error\r\n");
	}

	mode = POWERCHECK_MODE_BLOCK_DOWN;
	powercheck_init(mode);
	powercheck_setwaittime(0);					//掉电处理模块处于阻塞状态

	/*创建线程，触发掉电处理*/
	id_thread1 = 3;
	for(i = 0; i < 20; i++){
		ret = thread_create(id_thread1, thread_function1, NULL, mode_thread1, prio_thread1);
		if(ret != 0){
			printf("thread creat error1 \r\n");
		}
		id_thread1++;
	}

	id_thread2 = 30;
	ret = thread_create(id_thread2, thread_function2, NULL, mode_thread2, prio_thread2);
	if(ret != 0){
		printf("thread creat error2 \r\n");
	}
	while(1)
	{
	}
	powercheck_close();

	finaltest();
	return 0;
}

void *thread_function1(void *arg)
{
	int i;
	while(1)
	{
	}
	return NULL;
}

void *thread_function2(void *arg)
{
	int ret = -1;
	while(1)
	{
		gpio_output_set(io_check, io_setval);
		ret = powercheck_check();
		gpio_output_set(io_check, io_clearval);					//PB0口输出高
		printf("ret = %d\r\n",ret);
		assert(ret == 0,"powercheck_check 1 error");
		sleep(1);
	}
	return NULL;
}
