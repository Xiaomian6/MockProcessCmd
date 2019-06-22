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
int RCB::requestR(const int num)
{
	if (this->rStatus >= num)  // ʣ����Դ�㹻
	{
		this->rStatus = this->rStatus - num;
		return 1;
	}
	else // ʣ����Դ����������
	{

	}
	return 0;
}

/* �ͷ���Դ */
int RCB::releaseR(const int num)
{
	this->rStatus = this->rStatus + num;

	if (this->rStatus > this->initNum)
	{
		cout << "BUG BUG BUG" << endl;
	}
	return 0;
}

/* �������Դ�����ȴ����� */
int RCB::addWaitingList(int number, PCB* pcb)
{

	// ������Դ�����ȴ������Ƿ�����ͬ�� PCB ��
	for (list<waiting>::iterator iter = waitingList.begin(); iter != waitingList.end(); iter++)
	{
		if (iter->pcb == pcb)
		{
			iter->BlockNum = iter->BlockNum + number;
			return 1;
		}
	}

	// û���ҵ� �����
	waiting newWaiting(pcb->getPid(), number, pcb);   // ���� rcb ����Դ������Դ�� waiting
	this->waitingList.push_back(newWaiting);         // ��ӵ����̵�ռ����Դ�б�
	return 0;
}

/* �Ƴ���Դ�����ȴ����� */
int RCB::deleteWaitingList()
{
	waitingList.pop_front();    // ɾ���б��һ��Ԫ�� 
	return 0;
}

/* �ж����������ײ������������Դ���Ƿ�С�ڵ��ڿ�����Դ���� u */
bool RCB::isWaitingListFirst()
{
	if (waitingList.front().pcb->getResourcesOwnNum(this->getRid()) <= this->rStatus)
	{
		return true;
	}
	else
	{
		return false;
	}
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

bool RCB::waitingListEmpty()
{
	if (waitingList.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int RCB::getWaitingListFirstNum()
{
	return waitingList.front().BlockNum;
}

int RCB::getWaitingListFirstPID()
{
	return waitingList.front().BlockPID;
}

void RCB::showWaitingListEach()
{
	list<waiting>::iterator data;

	for (data = waitingList.begin(); data != waitingList.end(); data++)
	{
		cout << data->pcb->getPname() << "  ";
	}
}