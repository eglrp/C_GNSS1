#include "Cal.h"
#include "Nav.h"
#include <math.h>
Cal::Cal(string path = "", Nav* nav = NULL){
	ofstream fout(path);
	if(!fout){
		cout << "Write to " << path << "failed." << endl;
		exit(1);
	}
	fout.width(5);
	fout.setf(ios::left);
	fout << "****************************GIS*************************** " << endl;
	fout << "[   时     间   ][PRN][       X      ] [       Y      ] [       Z      ]" << endl;
		 double TotalInSec = 0;
		 TotalInSec += nav->getOb_e().at("Sec") - nav->getOb_s().at("Sec");
		 TotalInSec += 60 * (nav->getOb_e().at("Min") - nav->getOb_s().at("Min"));
		 TotalInSec += 60 * 60 * (nav->getOb_e().at("Hour") - nav->getOb_s().at("Hour"));
		 Prmts* stltDate = new Prmts; //获取所有观测时间,同时对所有导航数据匹配
		 int paraLen = nav->getPrmts().size();
		 int step = 0;
		 
		 while(step * 3 < TotalInSec ){
			 Prmt* obDate = new Prmt;     //对每个观测值进行分析
			 stltDate->push_back(obDate);
			 obDate->insert(pair<string,double>("OYear",YEAR));
			 obDate->insert(pair<string,double>("OMonth",MONTH));
			 obDate->insert(pair<string,double>("ODay",DAY));
			 obDate->insert(pair<string,double>("OHour",OBS_H));
			 obDate->insert(pair<string,double>("OMin",OBS_M));
			 obDate->insert(pair<string,double>("OSec",OBS_S));

			 //stltDate->push_back(obDate);
			 this->moveObDate(obDate, step); // step  
			 step += 1;
		 }

		 int obLen = stltDate->size();
		 int j = 0;
		 for(; j < obLen; j++){
			 Prmt * obDate = stltDate->operator[](j);
			 if( j > 116){
					j--;
					j++;
			 }
			 int i = 0;
			 for(; i < paraLen; i++){
				 if(this->isCal(obDate, nav->getPrmts().operator[](i))){
					 this->getPos(nav->getPrmts().operator[](i),obDate);
							 fout 
							 << obDate->at("OYear") << "-"
							 << obDate->at("OMonth") << "-"
							 << obDate->at("ODay") << " "
							 << obDate->at("OHour") << ":"
							 ;
							 fout.fill(0);
							 fout.width(2);
							 fout << std::right << obDate->at("OMin") << ":";
							 fout.fill(0);
							 fout.width(2);
							 fout << std::right << obDate->at("OSec") << " ";
						  
							 fout<< "[";
								 
							 fout.width(2);
							 fout
							 << std::right 
								 << nav->getPrmts().operator[](i)->at("PRN"); 
							 fout << "] ";
							
							 fout << "["  ;
							 fout.width(14);
							 fout << std::right	<< obDate->at("X"); 
							 fout << "] " ;

						 	 fout << "[" ;
							 fout.width(14);
							 fout << std::right << obDate->at("Y");
							 fout << "] " ;

							 fout << "[" ;
							 fout.width(14);
							 fout << std::right << obDate->at("Z");
							 fout << "]" ;
					 fout << endl;
				 }
			 }

		 }

		 
		 /*
		 		// fout.flags(10);*/
	
		 fout.close();


}

void Cal::moveObDate(Prmt* obDate, int step){
	double tmpS = 0;
	tmpS = obDate->at("OSec") + 3 * step;
	
	double addH = (int)tmpS / (60 * 60);
	double addM = ((int)tmpS - (int)addH * 60 * 60) / 60;
	double addS = (int)tmpS % 60;
	
		obDate->at("OSec") = addS;//

		double tmpM = 0;
		tmpM = obDate->at("OMin") + addM;
		if(tmpM >= 60){
			double newMin = (int)tmpM % 60;
			addH += (int)tmpM / 60;
			obDate->at("OMin") = newMin;
		}
		else{
			obDate->at("OMin") = tmpM;
		}

		double tmpH = 0;
		tmpH = obDate->at("OHour");
		obDate->at("OHour") = tmpH + (int)addH;

}

void Cal::sec2Date(int sec, Prmt* date){

	date->insert( pair<string,double>("Hour", sec / (60 * 60)));
	date->insert( pair<string,double>("Min", (sec % (60 * 60)) / 60 ));
	date->insert( pair<string,double>("Sec", sec % 60));
}

bool Cal::isObDate(Prmt* obDate){
	if(obDate->at("OYEAR") == YEAR && obDate->at("OMonth") == MONTH && obDate->at("ODay") == DAY){
		if(obDate->at("OHour") <= OBE_H && obDate->at("OMin") <= OBE_M && obDate->at("OSec") <= OBE_S){
			return true;
		}
		else{
			return false;
		}
	}
}

bool Cal::isCal(Prmt* obDate, Prmt* navDate){
	int ob = obDate->at("OHour") * 60 * 60 + obDate->at("OMin") * 60 + obDate->at("OSec");
	int nav = navDate->at("Hour") * 60 * 60 + navDate->at("Min") * 60 + navDate->at("Sec");
	if( fabs((double) (nav - ob)) <= 60 * 60){
		return true;
	}
	else{
		return false;
	}
}

void Cal::getPos(Prmt* navPtr, Prmt* obPtr){
	double n0, n, M, E, tmp, f, uP,u, i, r, L, x, y, dltU,dltR,dltI;
	n0 = sqrt(GM) / (navPtr->at("sqrtA") * navPtr->at("sqrtA") * navPtr->at("sqrtA"));
	n = n0+navPtr->at("dltN");
	M = navPtr->at("M0") + n * (this->date2GPSSec(obPtr) - navPtr->at("TOE"));
	
	tmp=M;//迭代的初始值
	E = M + navPtr->at("e") * sin(tmp);
	while(fabs(E-tmp) > 1e-012){   
		tmp = E;
		E = M + navPtr->at("e") * sin(tmp);
	}
	
	f = atan(sqrt(1 - navPtr->at("e") * navPtr->at("e")) * sin(E) / (cos(E) - navPtr->at("e")));
	uP = navPtr->at("ltOMG") + f;
	dltU = navPtr->at("Cuc") * cos(2 * uP) + navPtr->at("Cus") * sin(2 * uP);
	dltR = navPtr->at("Crc") * cos(2 * uP) + navPtr->at("Crs") * sin(2 * uP);
	dltI = navPtr->at("Cic") * cos(2 * uP) + navPtr->at("Cis") * sin(2 * uP);

	u = uP + dltU;
	r = navPtr->at("sqrtA") * navPtr->at("sqrtA") * (1 - navPtr->at("e") * cos(E))+dltR;
	i = navPtr->at("i0") + dltI + navPtr->at("dotI") * ( this->date2GPSSec(obPtr) - navPtr->at("TOE"));

	x = r * cos(u);
	y = r * sin(u);

	L=navPtr->at("OMG")+(navPtr->at("dotOMG")-WE) * this->date2GPSSec(obPtr) - navPtr->at("dotOMG")*navPtr->at("TOE");
	if(obPtr->find("X") == obPtr->end()) {
		obPtr->insert(pair<string,double>("X",x * cos(L) - y * cos(i) * sin(L)));
		obPtr->insert(pair<string,double>("Y",x * sin(L) + y * cos(i) * cos(L)));
		obPtr->insert(pair<string,double>("Z",y * sin(i)));
	}
	else{ // 存在即更新
		obPtr->at("X") = x * cos(L) - y * cos(i) * sin(L);
		obPtr->at("Y") = x * sin(L) + y * cos(i) * cos(L);
		obPtr->at("Z") = y*sin(i);
	}
}

int Cal::date2GPSWeek(Prmt* date){
	int TotalDays = 0;
	int Year = 1980;
	if(Year < YEAR){
		if(isLeap(Year)){
			TotalDays += 366;
		}
		else{
			TotalDays += 365;
		}
		Year++;
	}
	TotalDays += DAYS20130707;
	date->insert(pair<string,double>("Days",(double)TotalDays));
	return (TotalDays - GPS_GAP) / 7;
}

int Cal::date2GPSSec(Prmt* date){
	this->date2GPSWeek(date);
	return (((int)date->at("Days") - GPS_GAP) % 7 - 1) * 24 * 60 * 60 + date->at("OHour") * 60 * 60 + date->at("OMin") * 60 + date->at("OSec") ;

}

bool Cal::isLeap(int tmpYear){
	if( tmpYear % 4 == 0 && tmpYear % 100 != 0 || tmpYear % 100 == 0 && tmpYear % 400 == 0){
		return false;
	}
	else{
		return false;
	}
}

Cal::~Cal(){}