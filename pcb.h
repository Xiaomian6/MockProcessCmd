#pragma once

#include <iostream>
#include <string>
#include "rcb.h"

using namespace std;

extern class PCB;
extern class RCB;

enum processType { READY, RUNNING, BLOCKED };     // ����״̬
enum processList { READYLIST, BLOCKLIST };         // ���̶���
enum processPriorities { INIT, USER, SYSTEM };    // �������ȼ�

struct processResource
{
	// todo �����ʼ��
};

struct processStatus
{
	processType pType; // ����״̬
	processList pList; // ���̶���
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
	int pid;                       // ����ID
	string pName;                  // ������
	// processResource pResource;     // ռ����Դ
	processStatus pStatus;         // ����״̬ 
								   //         - Type[READY����̬, RUNNING����̬, BLOCKED����̬]
								   //         - List[READYLIST�����ȴ�����, BLOCKLIST�����ȴ�����]
	processCreationTree pTree;     // ������ 					   
	processPriorities priority;    // �������ȼ� INIT-0 USER-1 SYSTEM-2
};

