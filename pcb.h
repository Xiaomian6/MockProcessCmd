#pragma once

#include <iostream>
#include <string>
#include "rcb.h"

using namespace std;

extern class PCB;
extern class RCB;

enum processType { READY, RUNNING, BLOCKED };     // 进程状态
enum processList { READYLIST, BLOCKLIST };         // 进程队列
enum processPriorities { INIT, USER, SYSTEM };    // 进程优先级

struct processResource
{
	// todo 构造初始化
};

struct processStatus
{
	processType pType; // 进程状态
	processList pList; // 进程队列
};

struct processCreationTree
{
	PCB* parent;
	list<PCB*> child;
};

class PCB {

public:
	PCB(int pid, string pName, processPriorities priority, PCB* parent);
	~PCB();
public:
	

public:
	void showThisProcess();
	int getPid();
	string getPname();

private:
	int pid;                       // 进程ID
	string pName;                  // 进程名
	// processResource pResource;     // 占有资源
	processStatus pStatus;         // 进程状态 
								   //         - Type[READY就绪态, RUNNING运行态, BLOCKED阻塞态]
								   //         - List[READYLIST就绪等待队列, BLOCKLIST阻塞等待队列]
	processCreationTree pTree;     // 进程树 					   
	processPriorities priority;    // 进程优先级 INIT-0 USER-1 SYSTEM-2
};

