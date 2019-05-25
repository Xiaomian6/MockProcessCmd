#pragma once

#include <iostream>
#include <string>
#include <list>
#include "pcb.h"

using namespace std;

extern class PCB;
extern class RCB;

class RCB
{
public:
	RCB(int rid, string rName, int initNum);
	~RCB();

public:
	int getRid();
	string getRname();
	int getNumber();
	int getInitNum();

private:
	int rid;                     // 资源ID
	string rName;                // 资源名
	int rStatus;                 // 资源状态 数量
	int initNum;                 // 初始化数量
	list<PCB*> waitingList;      // 阻塞等待队列

};