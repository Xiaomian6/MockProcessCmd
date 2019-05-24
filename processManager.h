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
	PCB* runningProcess;                // ����ִ�н���ָ��
	vector<PCB*> processTable;          // ���̱�
	int allocation_pid;                 // ����id����

	// �����������̶���
	vector<PCB*> initReadyList;
	vector<PCB*> userReadyList;
	vector<PCB*> systemReadyList;

};