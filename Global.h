#ifndef GLOBAL_H
#define GLOBAL_H
#include <map>
#include <vector>
using namespace std;

#define COLUMNS 82 //�ļ����-80��,��������Ļ��з���Ȼռ������
#define NAV_HEAD_ROW 7 //�����ļ�ͷ��
#define OB_HEAD_ROW 15 //�۲��ļ�ͷ��

#define PAR_SET_LINES 8  //.N ÿ�����ռ8��
#define PAR_SET_TOTAL 27 //.N ��27��

#define GM 3.986005e+14 //������������G,����������M, m3/s2
#define WE 7.292115e-5 //������ת���ٶ�
#define OBS_H 8
#define OBS_M 57
#define OBS_S 9.0000000
#define OBE_H 10
#define OBE_M 33
#define OBE_S 9.0000000
#define OB_GAP 3 //�۲���
#define GPS_GAP 5 //1980/1/6�����賿��ʱ
#define YEAR 2013
#define MONTH 7
#define DAY 7
#define DAYS20130707 188 //20130707��188�죨��7�ţ�
typedef map<string,double> Prmt;
typedef vector<Prmt *> Prmts;

//abstract 
#endif