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

/* ������Դ */
int RCB::requestR(RCB* rcb, const int num, PCB* pcb)
{
	if (rcb->rStatus >= num)  // ʣ����Դ�㹻
	{
		rcb->rStatus = rcb->rStatus - num;

	}
	else // ʣ����Դ����������
	{

	}
	return 1;
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