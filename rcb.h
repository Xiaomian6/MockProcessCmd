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
	int rid;                     // ��ԴID
	string rName;                // ��Դ��
	int rStatus;                 // ��Դ״̬ ����
	int initNum;                 // ��ʼ������
	list<PCB*> waitingList;      // �����ȴ�����

};