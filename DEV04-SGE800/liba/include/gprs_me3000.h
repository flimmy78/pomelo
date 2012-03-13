/*****************************************************************************
	���̵����ɷ����޹�˾			��Ȩ��2008-2015

	��Դ���뼰������ĵ�Ϊ�����������̵����ɷ����޹�˾�������У�δ��������
	�ɲ��������޸Ļ򷢲�������׷����صķ������Ρ�

						�����������̹ɷ����޹�˾
						www.xjgc.com
						(0374) 321 2924
*****************************************************************************/


/******************************************************************************
	��Ŀ����	��  SGE800���������ն�ҵ��ƽ̨
	�ļ�		��  gprs_me3000.h
	����		��  ���ļ�������gprs3000ģ���API�ӿ�
	�汾		��  0.1
	����		��  ����
	��������	��  2010.4
******************************************************************************/

#ifndef _ME3000_H
#define _ME3000_H

#include "typedef.h"

/*************************************************
  �궨��
*************************************************/

//GPRSģ�������
#define CFG_DATA_MAX			512				//���û���������󳤶ȣ�������ʾ�����ֽ�����
#define CFG_SEND_TIMEOUT		2				//���ͳ�ʱ
#define CFG_RECV_TIMEOUT		1				//���ճ�ʱ���и����㷽���������ν���֮�����Сʱ�����������п��ܻᶪ���ݣ�
#define CFG_SMS_MAX				8				//�����ŷ�֡��
#define	CFG_SMS_LEN_MAX			140				//����������󳤶�
#define	CFG_RECV_BACKMAX		20				//���յ����ؽ����������󳤶�
#define CFG_SMS_CENTER			"13800210500"	//�������ĺ���

#define CFG_GPRS_POWER_IO		5				//gprsģ�鿪�ػ������ź�
#define	CFG_GPRS_POWER_IO_VAL	1				//���ؿ����ź�״̬
#define CFG_GPRS_POWER_IO_OD	1				//OD��ʹ�ܱ�ʶ��1ʹ��
#define CFG_GPRS_POWER_IO_PU	1				//��������ʹ�ܱ�ʶ��1ʹ��




/*************************************************
  API
*************************************************/
/******************************************************************************
*	����:	gprs_me3000_init
*	����:	me3000��ʼ��
*	����:
*	����:	0				-	�ɹ�(�յ�ȷ������)
			-ERR_SYS		-	ϵͳ����
*	˵��:	��
******************************************************************************/
int gprs_me3000_init();

/******************************************************************************
*	����:	gprs_me3000_setconfig
*	����:	���ô��ڻ�gprsģ��
*	����:	cmd				-	0�����ô��ڣ�1������gprsģ��
			cfg				-	���ýӿ�
*	����:	0				-	�ɹ�
			-ERR_SYS		-	ϵͳ����
			-ERR_INVAL		-	�ӿڲ������ô���

*	˵��:	��
******************************************************************************/
int gprs_me3000_setconfig(u8 cmd, void *cfg);

/******************************************************************************
*	����:	gprs_me3000_getconfig
*	����:	��ȡ���ڻ�gprsģ������
*	����:	cmd				-	0�����ô��ڣ�1������gprsģ��
			cfg				-	���ýӿ�
*	����:	0				-	�ɹ�
			-ERR_SYS		-	ϵͳ����
			-ERR_INVAL		-	�ӿڲ������ô���

*	˵��:	��
******************************************************************************/
int gprs_me3000_getconfig(u8 cmd, void *cfg);

/******************************************************************************
*	����:	gprs_me3000_send
*	����:	GPRS��������
*	����:	buf				-	����������ʼָ��
			count			-	�������ݳ���
*	����:	>0				-	�ɹ�(����ʵ�ʷ��ͳɹ����ֽ���)
			-ERR_SYS		-	ϵͳ����
			-ERR_INVAL		-	�ӿڲ������ô���
 		    -ERR_DISCONNECT	-	δ����
 		    -ERR_BUSY		-	�豸æ

*	˵��:	��ʱʱ��ͨ�����÷��ͳ�ʱ��
******************************************************************************/
int gprs_me3000_send(u8 *buf, u32 count);

/******************************************************************************
*	����:	gprs_me3000_recv
*	����:	GPRS�������ݣ�N��δ��ȡ���ܱ���գ�
*	����:	buf				-	����������ʼָ��
			count			-	���ջ���������
*	����:	>0				-	�ɹ�(����ʵ�ʷ��ͳɹ����ֽ���)
			-ERR_SYS		-	ϵͳ����
			-ERR_INVAL		-	�ӿڲ������ô���
 		    -ERR_DISCONNECT	-	δ����
 		    -ERR_BUSY		-	�豸æ
 		    -ERR_NOMEM		-	�ӿڴ洢�ռ�С---��֡

*	˵��:	typeΪ0�յ����ţ�type = 1�յ�tcp���ݣ�type=2�յ�udp���ݣ�type=3���յ���Ϣ��ʾ
			ѭ�����øĺ����������ݣ�2s��δ�����ѽ��յ����ݿ��ܱ��µ������滻�������ؽ��յ����ݺ�Ӧ�ý����ݿ�����������
			�����µ��øú���������������ֱ������Ϊ0,����һ��ʱ�䣨2S�ڣ����µ��á�
******************************************************************************/
int gprs_me3000_recv(u8 *buf, u32 count, u8 *type, u8 *tel);

/******************************************************************************
*	����:	gprs_me3000_sendsmg
*	����:	���Ͷ�Ϣ
*	����:	buf				-	����������ʼָ��
			count			-	�������ݳ���
			telnum			-	���ͷ��绰������ʼָ�루������11���ֽڵĵ绰����Ҳ������6���ֽڵ�udp�����ʽ��
			tellen			-	�绰���볤��
*	����:	>0				-	�ɹ�(����ʵ�ʷ��ͳɹ����ֽ���)�ۼ�������
			-ERR_SYS		-	ϵͳ����
			-ERR_INVAL		-	�ӿڲ������ô���
 		    -ERR_DISCONNECT	-	δ����
 		    -ERR_BUSY		-	�豸æ
 		    -ERR_NOMEM		-	�ӿڴ洢�ռ�С---��֡

*	˵��:
******************************************************************************/
int gprs_me3000_sendsmg(u8 *buf, u32 count, u8 *telnum, u8 tellen);

/******************************************************************************
*	����:	gprs_me3000_recvsmg
*	����:	gprsģ�������
*	����:
*	����:	0				-	�ɹ�(�յ�ȷ������)
			-ERR_TIMEOUT	-	���ӳ�ʱ

*	˵��:	��
******************************************************************************/
int gprs_me3000_recvsmg(u8 *buf, u32 count);

/******************************************************************************
*	����:	gprs_me3000_connect
*	����:	gprsģ�齨������
*	����:	mode			-	���ӷ�ʽ��0���������ӣ�1��������
*	����:	0				-	�ɹ�(�յ�ȷ������)
			-ERR_TIMEOUT	-	���ӳ�ʱ

*	˵��:	��
******************************************************************************/
int gprs_me3000_connect(u8 mode);

/******************************************************************************
*	����:	gprs_me3000_disconnect
*	����:	gprsģ��Ͽ�����
*	����:
*	����:	0				-	�ɹ�(�յ�ȷ������)
			-ERR_TIMEOUT	-	���ӳ�ʱ

*	˵��:	��
******************************************************************************/
int gprs_me3000_disconnect(void);

/******************************************************************************
*	����:	gprs_me3000_getstat
*	����:	���״̬
*	����:
*	����:	0				-	�ɹ�


*	˵��:	��
******************************************************************************/
int gprs_me3000_getstat(u8 cmd, void *stat);

/******************************************************************************
*	����:	gprs_me3000_turnon
*	����:	����
*	����:
*	����:	0				-	�ɹ�


*	˵��:	��
******************************************************************************/
int gprs_me3000_turnon(void);

/******************************************************************************
*	����:	gprs_me3000_turnoff
*	����:	�ػ�
*	����:
*	����:	0				-	�ɹ�
			-ERR_TIMEOUT	-	��ʱ

*	˵��:	Ӳ���ϵ�ǰӦ�����ػ�������GPRSģ��
******************************************************************************/
int gprs_me3000_turnoff(void);


/******************************************************************************
*	����:	gprs_me3000_poweron
*	����:	�ϵ�
*	����:
*	����:	0				-	�ɹ�


*	˵��:	��
******************************************************************************/
int gprs_me3000_poweron(void);

/******************************************************************************
*	����:	gprs_me3000_poweroff
*	����:	����
*	����:
*	����:	0				-	�ɹ�


*	˵��:	��
******************************************************************************/
int gprs_me3000_poweroff(void);

/******************************************************************************
*	����:	gprs_me3000_reset
*	����:	��������
*	����:
*	����:	0				-	�ɹ�


*	˵��:	��
******************************************************************************/
int gprs_me3000_reset(void);


#endif  /* _ME3000_H */