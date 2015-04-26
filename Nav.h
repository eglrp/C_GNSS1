#ifndef NAV_H
#define NAV_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Global.h"
using namespace std;

class Nav{
public:
	Nav(string);
	~Nav();
	double s2d(string&,int,int);
	int s2i(string&,int,int);
	Prmt & getOb_s();
	Prmt & getOb_e();
	Prmts & getPrmts();
private:
	Prmts prmts;
	Prmt ob_s;
	Prmt ob_e;

};

#endif

	/* 
	/*1 ƽ�����ٶ�*/
	 //����-����A sqrtA;
	 //�ο�ʱ��toe��ƽ�����ٶ� n0;
	 //����-�㶯������n dltN; 
	 //�۲�ʱ�����ǵ�ƽ�����ٶ�n n;		

	/*2 ƽ�����*/	
	 //�۲�˲�����ǵ�ƽ�����M  M;	
	 //����-�ο�ʱ��toe��ƽ����� M0;	

	/*3 ƫ�����*/
	// E;

	/*4 ������f*/
	// e;		 //����-ƫ����
	// f;

	/*5 �����Ǿ�u'*/
	// w;		//����-little OMEGA

	/*6 �㶯�������u,��r,��i*/
	// dltU; //����������:��u,��r,��i
	// dltR;
	// dltI;
	//����-�����㶯����
	/* Cuc;  
	 Cus;
	 Crc;
	 Crs;
	 Cic;
	 Cis;
	*/
	/*7 ��u',r',i0�㶯����*/
	// uP;	 //����- 
	// rP;
	// i0;

	// u;
	// r;

	/*8 �������ǹ��ƽ��λ��*/
	//double x;
	//double y;

	/*9 ����۲�˲�������㾭��L */
	// OMEGA0;   // ����-OMEGAtoe - GASTweek
	// OMEGAdot; // ����-��ͷ��һ��:��������¼��ı仯��
	// L;

	/*10 ��������˲ʱ��������ϵ�е�λ��*/
	//double i;	      // ����-���ƽ�����i