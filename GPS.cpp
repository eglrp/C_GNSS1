#include "Nav.h"
#include "Cal.h"

int main(){
	string NavPath = "shidun0707.13N" ;//��ȡ.N���ļ�·��
	string outPath = "test_out.txt"; //������ļ�·��
	Nav * nav = new Nav(NavPath); 
	Cal * cal = new Cal(outPath, nav);
	return 0;
}