#include "rcb.h"

using namespace std;

RCB::RCB(int rid, string rName, int initNum)
{
	this->rid = rid;
	this->rName = rName;
	this->initNum = initNum;
	this->rStatus = initNum;
}

RCB::~RCB()
{

}


/*************************************************************
 *  RCB
 *  get() show()
 *************************************************************/

int RCB::getRid()
{
	return this->rid;
}

string RCB::getRname()
{
	return this->rName;
}

int RCB::getNumber()
{
	return this->rStatus;
}

int RCB::getInitNum()
{
	return this->initNum;
}