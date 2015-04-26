#ifndef CAL_H
#define CAL_H
#include <string>
#include "Nav.h"
using namespace std;



class Cal{
public:
	Cal(string, Nav* );
	~Cal();

	void sec2Date(int, Prmt* );
	bool isCal(Prmt*, Prmt*);
	bool isObDate(Prmt*);
	void moveObDate(Prmt* ,int);
	void getPos(Prmt*, Prmt*);
	int date2GPSWeek(Prmt*);
	int date2GPSSec(Prmt*);
	bool isLeap(int);



};



#endif