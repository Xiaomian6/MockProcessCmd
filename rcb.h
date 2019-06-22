#pragma once

#include <iostream>
#include <string>
#include <list>
#include "pcb.h"

using namespace std;

extern class PCB;
extern class RCB;

struct waiting
{
	int BlockPID;           // 阻塞的进程ID
	int BlockNum;           // 阻塞的资源数量
	PCB* pcb;             // 指向PCB块

	waiting(int BlockPID, int BlockNum, PCB* pcb)
	{
		this->BlockPID = BlockPID;
		this->BlockNum = BlockNum;
		this->pcb = pcb;
	}
};


class RCB
{
public:
	RCB(int rid, string rName, int initNum);
	~RCB();

public:  
	int requestR(const int num);
	int releaseR(const int num);
	int addWaitingList(int number, PCB* pcb);
	int deleteWaitingList();
	bool isWaitingListFirst();

public: // get() show()
	int getRid();
	string getRname();
	int getNumber();
	int getInitNum();
	bool waitingListEmpty();
	int getWaitingListFirstNum();
	int getWaitingListFirstPID();
	void showWaitingListEach();

private:
	int rid;                      // 资源ID
	string rName;                 // 资源名
	int rStatus;                  // 资源状态 数量
	int initNum;                  // 初始化数量
	list<waiting> waitingList;    // 资源阻塞等待队列

};