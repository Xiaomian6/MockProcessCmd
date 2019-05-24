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
	int createProcess(const string pName,int priority);
	int destroyProcess(const string delname);

	void Schedule();

	int deleteChildProcess(int pid);

	vector<PCB*>::iterator findProcessbypID(int pid);
	vector<PCB*>::iterator findProcessbypName(string pname);
	bool checkProcessName(string name);
	bool checkProcessID(int pid);

public:
	int getRunningProcess();
	void showReadyList();
	void showProcessTable();

private:
	PCB* runningProcess;                // ����ִ�н���ָ��
	vector<PCB*> processTable;          // ���̱�
	int allocation_pid;                 // ����id����

	// �����������̶���
	vector<PCB*> initReadyList;
	vector<PCB*> userReadyList;
	vector<PCB*> systemReadyList;

};