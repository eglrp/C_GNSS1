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
	/*1 平近角速度*/
	 //星历-根号A sqrtA;
	 //参考时刻toe的平均角速度 n0;
	 //星历-摄动参数△n dltN; 
	 //观测时刻卫星的平均角速度n n;		

	/*2 平近点角*/	
	 //观测瞬间卫星的平近点角M  M;	
	 //星历-参考时刻toe的平近点角 M0;	

	/*3 偏近点角*/
	// E;

	/*4 真近点角f*/
	// e;		 //星历-偏心率
	// f;

	/*5 升交角距u'*/
	// w;		//星历-little OMEGA

	/*6 摄动改正项δu,δr,δi*/
	// dltU; //三个改正项:δu,δr,δi
	// dltR;
	// dltI;
	//星历-六个摄动参数
	/* Cuc;  
	 Cus;
	 Crc;
	 Crs;
	 Cic;
	 Cis;
	*/
	/*7 对u',r',i0摄动改正*/
	// uP;	 //星历- 
	// rP;
	// i0;

	// u;
	// r;

	/*8 计算卫星轨道平面位置*/
	//double x;
	//double y;

	/*9 计算观测瞬间升交点经度L */
	// OMEGA0;   // 星历-OMEGAtoe - GASTweek
	// OMEGAdot; // 星历-Ω头上一点:升交点对事件的变化率
	// L;

	/*10 计算卫星瞬时地球坐标系中的位置*/
	//double i;	      // 星历-轨道平面倾角i