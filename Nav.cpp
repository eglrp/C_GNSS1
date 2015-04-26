#include "Nav.h"
#include "Cal.h"
#include <cstdlib>
#include <cstdio>
#include <algorithm>
Nav::Nav(string path=""){
	ifstream fin(path);
	if(!fin){
		cout << "Open" << path << "failed :< " << endl;
		exit(1);
	}

	string navLine;
	fin.seekg(COLUMNS * NAV_HEAD_ROW );
	int lineNo = 0;
	int groups = 0;
	//¶ÁÈ¡²ÎÊı
	while(groups < PAR_SET_TOTAL){
		groups++;
		lineNo = 0;
		Prmt * prmt = new Prmt;
		this->prmts.push_back(prmt);
		while(lineNo < PAR_SET_LINES && getline(fin,navLine)){
			lineNo %= PAR_SET_LINES; 
			replace(navLine.begin(),navLine.end(),'D','e');
			switch (lineNo){
				case 0:
					prmt->insert( pair<string,double>( "PRN",this->s2d(navLine,0,2)));//strtod( navLine.substr(0,2).c_str(),NULL) ));
					prmt->insert( pair<string,double>( "Hour",this->s2d(navLine,12,2)));//strtod( navLine.substr(12,2).c_str(),NULL) ));
					prmt->insert( pair<string,double>( "Min",this->s2d(navLine,15,2)));//strtod( navLine.substr(15,2).c_str(),NULL) ));
					prmt->insert( pair<string,double>( "Sec",this->s2d(navLine,18,4)));//strtod( navLine.substr(18,4).c_str(),NULL) ));
					break;
				case 1:
					//cout << navLine.substr(23,18) << "--" <<endl;
					prmt->insert( pair<string,double>( "Crs", this->s2d(navLine,23,18)));
					prmt->insert( pair<string,double>( "dltN", this->s2d(navLine,42,18)));
					prmt->insert( pair<string,double>( "M0", this->s2d(navLine,61,18)));
					//cout << prmt->operator[]("dltN") << " ::: "<<endl;
					//prmt->insert( pair<string,double>( "dltN",strtod( navLine.substr(4,18).replace(15,18,'D','e').c_str(),NULL) ));
					break;
				case 2:
					prmt->insert( pair<string,double>( "Cuc", this->s2d(navLine,4,18)));
					prmt->insert( pair<string,double>( "e", this->s2d(navLine,23,18)));
					prmt->insert( pair<string,double>( "Cus", this->s2d(navLine,42,18)));
					prmt->insert( pair<string,double>( "sqrtA", this->s2d(navLine,61,18)));
					break;
				case 3:
					prmt->insert( pair<string,double>( "TOE", this->s2d(navLine,4,18)));
					prmt->insert( pair<string,double>( "Cic", this->s2d(navLine,23,18)));
					prmt->insert( pair<string,double>( "OMG", this->s2d(navLine,42,18)));
					prmt->insert( pair<string,double>( "Cis", this->s2d(navLine,61,18)));
					break;
				case 4:
					prmt->insert( pair<string,double>( "i0", this->s2d(navLine,4,18)));
					prmt->insert( pair<string,double>( "Crc", this->s2d(navLine,23,18)));
					prmt->insert( pair<string,double>( "ltOMG", this->s2d(navLine,42,18)));
					prmt->insert( pair<string,double>( "dotOMG", this->s2d(navLine,61,18)));
					break;
				case 5:
					prmt->insert( pair<string,double>( "dotI", this->s2d(navLine,4,18)));
					break;
				default:
					break;
			}
			lineNo++;
		}
	}
	this->ob_s.insert( pair<string,double>("Hour",OBS_H));
	this->ob_s.insert( pair<string,double>("Min",OBS_M));
	this->ob_s.insert( pair<string,double>("Sec",OBS_S));
	this->ob_e.insert(pair<string,double>("Hour",OBE_H));
	this->ob_e.insert(pair<string,double>("Min",OBE_M));
	this->ob_e.insert(pair<string,double>("Sec",OBE_S));

	fin.close();

}

double Nav::s2d(string &tS,int beginNo, int endNo){
	//double tmp;	
	//sscanf(tS.substr(beginNo,endNo).c_str(),"%lf",&tmp);
	//return tmp;
	return strtod(tS.substr(beginNo,endNo).c_str(),NULL);
}

int Nav::s2i(string &tS,int beginNo, int endNo){
	int tmp;	
	sscanf(tS.substr(beginNo,endNo).c_str(),"%d",&tmp);
	return tmp;
}

Prmt & Nav::getOb_s(){
		return ob_s;
	}
Prmt & Nav::getOb_e(){
		return ob_e;
}

Prmts & Nav::getPrmts(){
	return this->prmts;
}

Nav::~Nav(){
	
}
