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

public: // pcb
	int createProcess(const string pName,int priority);
	int destroyProcess(const string delname);

	void Schedule();

	int deleteChildProcess(int pid);

	vector<PCB*>::iterator findProcessbypID(int pid);
	vector<PCB*>::iterator findProcessbypName(string pname);
	bool checkProcessName(string name);
	bool checkProcessID(int pid);
public: // rcb
	void createResources();
	int requestResources(const string rName, const int number);
	RCB* findResourcesByName(string rname);
	bool checkResourcesName(string name);
	bool checkResourcesInitnum(string name, int num);

public: // get() show()
	int getRunningProcess();
	void showReadyList();
	void showProcessTable();
	void showResourcesTable();

private:
	PCB* runningProcess;                // 正在执行进程指针
	vector<PCB*> processTable;          // 进程表
	int allocation_pid;                 // 进程id分配
	vector<RCB*> resourcesTable;        // 资源列表

	// 三级就绪进程队列
	vector<PCB*> initReadyList;
	vector<PCB*> userReadyList;
	vector<PCB*> systemReadyList;

};