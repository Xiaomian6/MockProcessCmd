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

/* 请求资源 */ 
int RCB::requestR(const int num)
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

/* 释放资源 */
int RCB::releaseR(const int num)
{
	this->rStatus = this->rStatus + num;

	if (this->rStatus > this->initNum)
	{
		cout << "BUG BUG BUG" << endl;
	}
	return 0;
}

/* 添加入资源阻塞等待队列 */
int RCB::addWaitingList(int number, PCB* pcb)
{

	// 遍历资源阻塞等待队列是否有相同的 PCB 块
	for (list<waiting>::iterator iter = waitingList.begin(); iter != waitingList.end(); iter++)
	{
		if (iter->pcb == pcb)
		{
			iter->BlockNum = iter->BlockNum + number;
			return 1;
		}
	}

	// 没有找到 则添加
	waiting newWaiting(pcb->getPid(), number, pcb);   // 创建 rcb 的资源阻塞资源块 waiting
	this->waitingList.push_back(newWaiting);         // 添加到进程的占有资源列表
	return 0;
}

/* 移除资源阻塞等待队列 */
int RCB::deleteWaitingList()
{
	waitingList.pop_front();    // 删除列表第一个元素 
	return 0;
}

/* 判断阻塞队列首部进程需求的资源数是否小于等于可用资源数量 u */
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