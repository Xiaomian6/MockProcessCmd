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

/* 请求资源 */ // delete
int RCB::requestR(const int num, PCB* pcb)
{
	if (this->rStatus >= num)  // 剩余资源足够
	{
		this->rStatus = this->rStatus - num;
		return 1;
	}
	else // 剩余资源不够，阻塞
	{

	}
	return 0;
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