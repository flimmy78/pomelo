/*****************************************************************************/
/*���̵����ɷ����޹�˾                                     ��Ȩ��2008-2015   */
/*****************************************************************************/
/* ��Դ���뼰������ĵ�Ϊ�����������̵����ɷ����޹�˾�������У�δ��������    */
/* �ɲ��������޸Ļ򷢲�������׷����صķ������Ρ�                          */
/*                                                                           */
/*                      �����������̹ɷ����޹�˾                             */
/*                      www.xjgc.com                                         */
/*                      (0374) 321 2924                                      */
/*                                                                           */
/*****************************************************************************/


/******************************************************************************
    ��Ŀ����    ��  SGE800���������ն�ƽ̨
    �ļ���      ��  c-qd-din-init.c
    ����        ��  ���ļ�����ƽ̨��din_init�����Ĳ���
    �汾        ��  0.1
    ����        ��  ��ΰ��
    ��������    ��  2010.03
******************************************************************************/

//C��ͷ�ļ�
#include <stdio.h>			//printf
#include <stdlib.h>		//exit
#include <unistd.h>		//sleep
#include <db.h>

//ƽ̨��ͷ�ļ�
#include "../include/dbs.h"
#include "../include/xj_assert.h"

//���Գ���ͷ�ļ�
#include "../include/din.h"

int main()
{
	int ret;
	//������ʼ��
	inittest();

	//��������1
	ret = din_init();
	assert(ret == 0,"din_init error");

	//��������2

	//��������3

	//��������4

	finaltest();
	return 0;
}
