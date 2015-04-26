#include "Nav.h"
#include "Cal.h"

int main(){
	string NavPath = "shidun0707.13N" ;//读取.N的文件路径
	string outPath = "test_out.txt"; //输出的文件路径
	Nav * nav = new Nav(NavPath); 
	Cal * cal = new Cal(outPath, nav);
	return 0;
}