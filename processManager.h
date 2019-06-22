#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

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

	void Schedule(); // 调度

	int deleteChildProcess(int pid);

	vector<PCB*>::iterator findProcessbypID(int pid);
	vector<PCB*>::iterator findProcessbypName(string pname);
	bool checkProcessName(string name);
	bool checkProcessID(int pid);
public: // rcb
	void createResources();
	int requestResources(const string rName, const int number);
	int releaseResources(const string rName, const int number);
	RCB* findResourcesByName(string rname);
	bool checkResourcesName(string name);
	bool checkResourcesInitnum(string name, int num);

public: // get() show()
	int getRunningProcess();
	void showReadyList();
	void showProcessTable();
	void showResourcesTable();
	void showBlockList();

private:
	PCB* runningProcess;                // 正在执行进程指针
	vector<PCB*> processTable;          // 进程表
	int allocation_pid;                 // 进程id分配(自增)

	vector<RCB*> resourcesTable;        // 资源列表

	// 三级就绪进程队列
	list<PCB*> initReadyList;
	list<PCB*> userReadyList;
	list<PCB*> systemReadyList;

	// 阻塞队列
	list<PCB*> blockList;             
};