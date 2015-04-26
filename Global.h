#ifndef GLOBAL_H
#define GLOBAL_H
#include <map>
#include <vector>
using namespace std;

#define COLUMNS 82 //文件规格-80列,但是猥琐的换行符居然占了两个
#define NAV_HEAD_ROW 7 //导航文件头部
#define OB_HEAD_ROW 15 //观测文件头部

#define PAR_SET_LINES 8  //.N 每组参数占8行
#define PAR_SET_TOTAL 27 //.N 共27组

#define GM 3.986005e+14 //万有引力常数G,地球总质量M, m3/s2
#define WE 7.292115e-5 //地球自转角速度
#define OBS_H 8
#define OBS_M 57
#define OBS_S 9.0000000
#define OBE_H 10
#define OBE_M 33
#define OBE_S 9.0000000
#define OB_GAP 3 //观测间隔
#define GPS_GAP 5 //1980/1/6当天凌晨计时
#define YEAR 2013
#define MONTH 7
#define DAY 7
#define DAYS20130707 188 //20130707共188天（含7号）
typedef map<string,double> Prmt;
typedef vector<Prmt *> Prmts;

//abstract 
#endif