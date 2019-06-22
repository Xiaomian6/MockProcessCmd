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
	int ownID;            // ռ�е���Դid
	int ownNum;           // ռ�õ�����
	RCB* rcb;             // ָ��RCB��

	Resource(int ownID, int ownNum, RCB* rcb)
	{
		this->ownID = ownID;
		this->ownNum = ownNum;
		this->rcb = rcb;
	}
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
	int addResource(int num, RCB *rcb);
	int deleteResource(int num, RCB* rcb);
	int changeBLOCKED();
	int changeRUNNING();
	int changeREADY();
	int changeBLOCKLIST();
	int changeREADYLIST();

public:
	void showThisProcess();
	int getPid();
	string getPname();
	int getPriority();
	string getType();
	string getList();
	string getFather();
	void showChilds();        //���������
	int getResourcesOwnNum(int RCBID);

private:
	int pid;                       // ����ID
	string pName;                  // ������
	vector<Resource> Resources;    // ռ����Դ�б�
	processStatus pStatus;         // ����״̬ 
								   //         - Type[READY����̬, RUNNING����̬, BLOCKED����̬]
								   //         - List[READYLIST�����ȴ�����, BLOCKLIST�����ȴ�����]
	processCreationTree pTree;     // ������ 					   
	processPriorities priority;    // �������ȼ� INIT-0 USER-1 SYSTEM-2
};

