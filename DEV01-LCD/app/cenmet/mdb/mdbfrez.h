/**
* mdbfrez.h -- ��������ʷ���ݽṹ
* 
* 
* ����ʱ��: 2010-5-12
* ����޸�ʱ��: 2010-5-12
*/

#ifndef _MDBFREZ_H
#define _MDBFREZ_H

#include "include/sys/timeal.h"

typedef struct {
	unsigned char tpwra[2];   //�ܼ��й�����
	unsigned char tpwri[2];    //�ܼ��޹�����
	unsigned char tenea[4];     //�ܼ��й�������
	unsigned char tenei[4];    //�ܼ��޹�������
} db_tgrpcurve_t;


typedef struct {//��������
	unsigned char pwra[12];   //�й�����, SABC, 0.0001kW
	unsigned char pwri[12];    //�޹�����, SABC, 0.0001kvar
	unsigned char pwrf[8];    //��������, SABC, 0.001
	unsigned char vol[6];    //��ѹ, ABC, 0.1V
	unsigned char amp[8];    //����, ABC, 0.01A

	unsigned char uenepa[4];    //�����й��ܵ���, 0.0001kWh
	unsigned char uenepi[4];    //�����޹��ܵ���, 0.0001kvarh
	unsigned char uenena[4];    //�����й��ܵ���, 0.0001kWh
	unsigned char ueneni[4];    //�����޹��ܵ���, 0.0001kvarh

	unsigned char enepa[4];    //�����й��ܵ���ʾֵ, 0.01kWh
	unsigned char enepi[4];    //�����޹��ܵ���ʾֵ, 0.01kvarh
	unsigned char enena[4];    //�����й��ܵ���ʾֵ, 0.01kWh
	unsigned char eneni[4];    //�����޹��ܵ���ʾֵ, 0.01kvarh

	unsigned char vol_arc[6];  //��ѹ��λ��, ��
	unsigned char amp_arc[6];  //������λ��, ��

	unsigned char enepi1[4];  //һ�����޹��ܵ���ʾֵ, 0.01kvarh
	unsigned char enepi4[4];  //�������޹��ܵ���ʾֵ, 0.01kvarh
	unsigned char eneni2[4];  //�������޹��ܵ���ʾֵ, 0.01kvarh
	unsigned char eneni3[4];  //�������޹��ܵ���ʾֵ, 0.01kvarh
} db_metcurve_t;

void SetUTimeFrez(utime_t utime);
utime_t GetUTimeFrez(void);

void UpdateMdbFrez(void);
int ReadMdbFrez(unsigned short metpid, unsigned short itemid, unsigned char *buf, int len);

#endif /*_MDBFREZ_H*/

