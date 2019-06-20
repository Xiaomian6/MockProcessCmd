#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "rcb.h"

using namespace std;

extern class PCB;
extern class RCB;

enum processType { READY, RUNNING, BLOCKED };     // ����״̬
enum processList { READYLIST, BLOCKLIST };        // ���̶���
enum processPriorities { INIT, USER, SYSTEM };    // �������ȼ�

struct Resource
{
	int owned;            // ռ�е���Դid
	int ownNum;           // ռ�õ�����
};

struct processStatus
{
	processType pType; // ����״̬
	processList pList; // ���̶���
};

struct processCreationTree
{
	PCB* parent;
	vector<PCB*> child;
};

class PCB {

public:
	PCB(int pid, string pName, processPriorities priority, PCB* parent);
	~PCB();
public:
	int addChild(PCB* child);

public:
	void showThisProcess();
	int getPid();
	string getPname();
	int getPriority();
	string getType();
	string getList();
	string getFather();
	void showChilds();        //���������

private:
	int pid;                       // ����ID
	string pName;                  // ������
	vector<Resource> Resources;    // ռ����Դ
	processStatus pStatus;         // ����״̬ 
								   //         - Type[READY����̬, RUNNING����̬, BLOCKED����̬]
								   //         - List[READYLIST�����ȴ�����, BLOCKLIST�����ȴ�����]
	processCreationTree pTree;     // ������ 					   
	processPriorities priority;    // �������ȼ� INIT-0 USER-1 SYSTEM-2
};

