#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "pcb.h"
#include "rcb.h"

using namespace std;

class processManager
{

public:
	processManager();
	~processManager();

public:
	int createProcess(string pName, int priority);
	int destroyProcess(int pid);

	void Schedule();

	vector<PCB*>::iterator findProcess(int pid);
	bool checkProcessName(string name);

public:
	int getRunningProcess();
	void showReadyList();
	void showProcessTable();

private:
	PCB* runningProcess;                // 正在执行进程指针
	vector<PCB*> processTable;          // 进程表
	int allocation_pid;                 // 进程id分配

	// 三级就绪进程队列
	vector<PCB*> initReadyList;
	vector<PCB*> userReadyList;
	vector<PCB*> systemReadyList;

};