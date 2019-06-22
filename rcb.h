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
	int BlockPID;           // �����Ľ���ID
	int BlockNum;           // ��������Դ����
	PCB* pcb;             // ָ��PCB��

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
	int rid;                      // ��ԴID
	string rName;                 // ��Դ��
	int rStatus;                  // ��Դ״̬ ����
	int initNum;                  // ��ʼ������
	list<waiting> waitingList;    // ��Դ�����ȴ�����

};