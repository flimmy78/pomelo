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
    项目名称   	 ：  SGE800计量智能终端平台
    文件名     	 ：  c-qd-adc-close.c
    描述       		 ：  本文件用于平台库adc_close函数的测试
    版本      		  ：  0.1
    作者        	：  左伟杰
    创建日期   	 ：  2010.03
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
#include "../include/adc.h"

int main()
{
	int ret;
	u16 set_timeout = 12;
	u8 id = 2;
	u16 result;
	//环境初始化
	inittest();

	//测试用例1
	adc_init();
	adc_setwaittime(set_timeout);

	adc_read(id,&result);

	ret = adc_close();
	assert(ret == 0,"adc_close error");

	//测试用例2
	ret = adc_close();
	assert(ret == -ERR_NOINIT,"adc_close error");
	//测试用例3

	//测试用例4

	finaltest();
	return 0;
}



