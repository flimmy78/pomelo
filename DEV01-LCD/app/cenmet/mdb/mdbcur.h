/**
* mdbcur.h -- ��ǰ��������
* 
* 
* ����ʱ��: 2010-5-10
* ����޸�ʱ��: 2010-5-10
*/

#ifndef _MDB_CUR_H
#define _MDB_CUR_H

/*
������Ϊ����:
��ʱ����: ��Ӧ��վ���ʱ����
��������: ������ʱ������ȡ��Ҫ����������ı���
���᳭��:������ʱ�������������

�����������ݿ⣺����RAM��)
�����⣺�������������������ݣ�һ��ΪHEX��, mdbana_t
��ǰ�⣺��������㵱ǰ�����ݣ���������������µ����ݿ�), 
        һ��ΪBCD��(���չ����ʽ), mdbcur_t
����⣺���涳�������, һ��ΪBCD��(���չ����ʽ), mdbfrz_t

485��������ȡ����:
��ʱ����: �����·����������Ʋ���ȡ,���µ�ǰ��,��ȡ��ǰ��
��������: ������ʱ������ȡ���ݣ�Ȼ����·�����/��ǰ��
���᳭��: ��ȡ��ʱ�⣬Ȼ����¶���Ⲣ������FLASH�����ݿ�

����/����������ȡ����:
��ʱ����: ��ȡ��ǰ��
��������: ��һ���Ӽ����ȡ���ݣ�Ȼ����·�����/��ǰ��
���᳭��: ��ȡ��ʱ�⣬Ȼ����¶���Ⲣ������FLASH�����ݿ�

485���ڱ���ȡ����
��ʱ����: ��ȡ��ǰ��
��������: ������ʱ������ȡ���ݣ�Ȼ����·�����/��ǰ��
���᳭��: ��ȡ��ʱ�⣬Ȼ����¶���Ⲣ������FLASH�����ݿ�
*/

#include "cenmet/mdb/mdbconf.h"

#define FLAG_MDBEMPTY	0xee  //��Ч����

//F25~F40,��ǰ��
typedef struct {
	unsigned char rdtime[5];    //����ʱ��, ��ʱ������

	//F25, 58
	unsigned char pwra[12];   //�й�����, SABC, 0.0001kW
	unsigned char pwri[12];    //�޹�����, SABC, 0.0001kvar
	unsigned char pwrf[8];    //��������, SABC, 0.001
	unsigned char vol[6];    //��ѹ, ABC, 0.1V
	unsigned char amp[8];    //����, ABCN, 0.01A
	unsigned char pwrv[12];  //���ڹ���, SABC, 0.0001kVA
	
	//F26, 52
	unsigned char volbr_cnt[8];    //�������,SABC
	unsigned char volbr_times[12];  //�����ۼ�ʱ��,SABC, min
	unsigned char volbr_timestart[16];    //���һ�ζ�����ʼʱ��,SABC,��ʱ����
	unsigned char volbr_timeend[16];    //���һ�ζ������ʱ��,SABC,��ʱ����
	
	//F27, 55
	unsigned char met_clock[6];    //�������ʱ��,���ʱ������
	unsigned char bat_runtime[4];  //��ع���ʱ��, ����
	unsigned char prog_cnt[3];    //����ܴ���
	unsigned char prog_time[6];  //���һ�α��ʱ��,���ʱ������
	unsigned char metclr_cnt[3];  //��������ܴ���
	unsigned char metclr_time[6];  //���һ�����㷢��ʱ��, ���ʱ������
	unsigned char dmnclr_cnt[3];  //���������ܴ���
	unsigned char dmnclr_time[6];  //���һ�����㷢��ʱ��, ���ʱ������
	unsigned char evclr_cnt[3];  //�¼������ܴ���
	unsigned char evclr_time[6];  //���һ�����㷢��ʱ��, ���ʱ������
	unsigned char chktime_cnt[3];  //Уʱ�ܴ���
	unsigned char chktime_time[6];  //���һ��Уʱ����ʱ��, ���ʱ������

	//F28, 28
	unsigned char flagchg_state[2*7];  //�������״̬�ֱ�λ��־
	unsigned char met_runstate[2*7];  //�������״̬��

	//F29, 50
	unsigned char enecopper[5*MAXNUM_METPRD];  //��ǰͭ���й��ܵ���ʾֵ, 0.0001kWh
	unsigned char eneiron[5*MAXNUM_METPRD];  //��ǰ�����й��ܵ���ʾֵ, 0.0001kWh

	//F30, 50
	unsigned char enecopper_lm[5*MAXNUM_METPRD];  //��һ������ͭ���й��ܵ��ܲ����� 0.0001kWh
	unsigned char eneiron_lm[5*MAXNUM_METPRD];  //��һ�����������й��ܵ��ܲ����� 0.0001kWh

	//F31, 54
	unsigned char enepa_a[5];  //��ǰA�������й�����ʾֵ, 0.0001KWh
	unsigned char enena_a[5];  //��ǰA�෴���й�����ʾֵ, 0.0001kWh
	unsigned char enepi_a[4];  //��ǰA������޹�1����ʾֵ, 0.01kvarh
	unsigned char eneni_a[4];  //��ǰA������޹�2����ʾֵ, 0.01kvarh
	unsigned char enepa_b[5];  //��ǰB�������й�����ʾֵ, 0.0001KWh
	unsigned char enena_b[5];  //��ǰB�෴���й�����ʾֵ, 0.0001kWh
	unsigned char enepi_b[4];  //��ǰB������޹�1����ʾֵ, 0.01kvarh
	unsigned char eneni_b[4];  //��ǰB������޹�2����ʾֵ, 0.01kvarh
	unsigned char enepa_c[5];  //��ǰC�������й�����ʾֵ, 0.0001KWh
	unsigned char enena_c[5];  //��ǰC�෴���й�����ʾֵ, 0.0001kWh
	unsigned char enepi_c[4];  //��ǰC������޹�1����ʾֵ, 0.01kvarh
	unsigned char eneni_c[4];  //��ǰC������޹�2����ʾֵ, 0.01kvarh

	//F32, 54
	unsigned char enepa_a_lm[5];  //��һ������A�������й�����ʾֵ, 0.0001KWh
	unsigned char enena_a_lm[5];  //��һ������A�෴���й�����ʾֵ, 0.0001kWh
	unsigned char enepi_a_lm[4];  //��һ������A������޹�1����ʾֵ, 0.01kvarh
	unsigned char eneni_a_lm[4];  //��һ������A������޹�2����ʾֵ, 0.01kvarh
	unsigned char enepa_b_lm[5];  //��һ������B�������й�����ʾֵ, 0.0001KWh
	unsigned char enena_b_lm[5];  //��һ������B�෴���й�����ʾֵ, 0.0001kWh
	unsigned char enepi_b_lm[4];  //��һ������B������޹�1����ʾֵ, 0.01kvarh
	unsigned char eneni_b_lm[4];  //��һ������B������޹�2����ʾֵ, 0.01kvarh
	unsigned char enepa_c_lm[5];  //��һ������C�������й�����ʾֵ, 0.0001KWh
	unsigned char enena_c_lm[5];  //��һ������C�෴���й�����ʾֵ, 0.0001kWh
	unsigned char enepi_c_lm[4];  //��һ������C������޹�1����ʾֵ, 0.01kvarh
	unsigned char eneni_c_lm[4];  //��һ������C������޹�2����ʾֵ, 0.01kvarh
	

	//F33, 85
	unsigned char enepa[5*MAXNUM_METPRD];  //�����й�����, 0~4, 0.0001kWh
	unsigned char enepi[4*MAXNUM_METPRD];  //�����޹�����, 0~4, 0.01kvarh
	unsigned char enepi1[4*MAXNUM_METPRD];  //�����޹�һ���޵���, 0~4, 0.01kvarh
	unsigned char enepi4[4*MAXNUM_METPRD];  //�����޹������޵���, 0~4, 0.01kvarh

	//F34, 85
	unsigned char enena[5*MAXNUM_METPRD];  //�����й�����, 0~4, 0.0001kWh
	unsigned char eneni[4*MAXNUM_METPRD];  //�����޹�����, 0~4, 0.01kvarh
	unsigned char eneni2[4*MAXNUM_METPRD];  //�����޹������޵���, 0~4, 0.01kvarh
	unsigned char eneni3[4*MAXNUM_METPRD];  //�����޹������޵���, 0~4, 0.01kvarh

	//F35, 70
	unsigned char dmnpa[3*MAXNUM_METPRD];  //���������й��������,0~4,0.0001kW
	unsigned char dmntpa[4*MAXNUM_METPRD];  //���������й������������ʱ��,0~4,��ʱ����
	unsigned char dmnpi[3*MAXNUM_METPRD];  //���������޹��������,0~4,0.0001kvar
	unsigned char dmntpi[4*MAXNUM_METPRD];  //���������޹������������ʱ��,0~4,��ʱ����
	
	//F36, 70
	unsigned char dmnna[3*MAXNUM_METPRD];  //���·����й��������,0~4,0.0001kW
	unsigned char dmntna[4*MAXNUM_METPRD];  //���·����й������������ʱ��,0~4,��ʱ����
	unsigned char dmnni[3*MAXNUM_METPRD];  //���·����޹��������,0~4,0.0001kvar
	unsigned char dmntni[4*MAXNUM_METPRD];  //���·����޹������������ʱ��,0~4,��ʱ����
	
	//F37, 85
	unsigned char enepa_lm[5*MAXNUM_METPRD];  //���������й�����, 0~4, 0.0001kWh
	unsigned char enepi_lm[4*MAXNUM_METPRD];  //���������޹�����, 0~4, 0.01kvarh
	unsigned char enepi1_lm[4*MAXNUM_METPRD];  //���������޹�һ���޵���, 0~4, 0.01kvarh
	unsigned char enepi4_lm[4*MAXNUM_METPRD];  //���������޹������޵���, 0~4, 0.01kvarh

	//F38, 85
	unsigned char enena_lm[5*MAXNUM_METPRD];  //���·����й�����, 0~4, 0.0001kWh
	unsigned char eneni_lm[4*MAXNUM_METPRD];  //���·����޹�����, 0~4, 0.01kvarh
	unsigned char eneni2_lm[4*MAXNUM_METPRD];  //���·����޹������޵���, 0~4, 0.01kvarh
	unsigned char eneni3_lm[4*MAXNUM_METPRD];  //���·����޹������޵���, 0~4, 0.01kvarh
	
	//F39, 70
	unsigned char dmnpa_lm[3*MAXNUM_METPRD];  //���������й��������,0~4,0.0001kW
	unsigned char dmntpa_lm[4*MAXNUM_METPRD];  //���������й������������ʱ��,0~4,��ʱ����
	unsigned char dmnpi_lm[3*MAXNUM_METPRD];  //���������޹��������,0~4,0.0001kvar
	unsigned char dmntpi_lm[4*MAXNUM_METPRD];  //���������޹������������ʱ��,0~4,��ʱ����
	
	//F40, 70
	unsigned char dmnna_lm[3*MAXNUM_METPRD];  //���·����й��������,0~4,0.0001kW
	unsigned char dmntna_lm[4*MAXNUM_METPRD];  //���·����й������������ʱ��,0~4,��ʱ����
	unsigned char dmnni_lm[3*MAXNUM_METPRD];  //���·����޹��������,0~4,0.0001kvar
	unsigned char dmntni_lm[4*MAXNUM_METPRD];  //���·����޹������������ʱ��,0~4,��ʱ����

	//F49, 12
	unsigned char phase_arc[12];  //��ǰ��ѹ��������λ��, 0.1��

	//F57, 217
	unsigned char syntony_value[216+1]; //��ǰA��B��C�����ѹ������2~N��г����Чֵ

	//F58, 229
	unsigned char syntony_rating[222+1];  //��ǰA��B��C�����ѹ������2~N��г��������

	unsigned short cnt_comerr;  //ͨ�Ŵ���
	unsigned char flag_comerr;
} mdbcur_t;

#define UPCURFLAG_ERROR    0x80
#define UPCURFLAG_645      0x00
#define UPCURFLAG_GB      0x01
#define UPCURFLAG_MASK    0x0f

#ifndef DEFINE_MDBCURRENT
extern const mdbcur_t MdbCurrent[MAX_CENMETP];
#endif
#define mdbcur(mid)		(MdbCurrent[mid])
void UpdateMdbCurrent(unsigned short metpid, unsigned int itemid, const unsigned char *buf, int len, unsigned char flag);
int ReadMdbCurrent(unsigned short metpid, unsigned short itemid, unsigned char *buf, int len);
void UpdateMdbCurRdTime(unsigned short mid);


#endif /*_MDB_CUR_H*/
