#include "processManager.h"

using namespace std;

processManager::processManager() // todo
{
	this->allocation_pid = 0;
}

processManager::~processManager()
{

}

/* �����½��� */
int processManager::createProcess(string pName, int priority)
{
	int pid = 0;
	// �鿴���̱��Ƿ����������� error=2
	if (checkProcessName(pName) == false)
	{
		return 2;
	}
	// ����һ��PCB (����pid)
	pid = this->allocation_pid++;
	// ��ʼ��PCB
	PCB* pcb = new PCB(pid, pName, (processPriorities)priority, runningProcess);

	// ������̱�
	processTable.push_back(pcb);

	// �����������
	switch (priority)
	{
	case 0:
		initReadyList.push_back(pcb);
		break;
	case 1:
		userReadyList.push_back(pcb);
		break;
	case 2:
		systemReadyList.push_back(pcb);
		break;
	default:
		cout << "BUG BUG BUG BUG" << endl;
		break;
	}

	return 1;
}

/* ���̵��� */
void processManager::Schedule()
{

}



/* ����pid�ڽ��̱���Ѱ�ҽ��� (�����ͷŽ���) */
vector<PCB*>::iterator processManager::findProcess(int pid)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPid() == pid)
			return data;

	return data;
}

/* ���������Ƿ����� */
bool processManager::checkProcessName(string name)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
	{
		if ((*data)->getPname() == name)
		{
			return false;
		}
	}

	return true;
}

/*************************************************************
 *  processManager
 *  get()
 *************************************************************/

/* ��ȡ����ִ�н��̵�ID */
int processManager::getRunningProcess()
{
	return this->runningProcess->getPid();
}

/* ��ʾ�������̶��� */
void processManager::showReadyList()
{
	vector<PCB*>::iterator initList;
	vector<PCB*>::iterator userList;
	vector<PCB*>::iterator systemList;

	cout << "[show] ReadyList" << endl;

	cout << "2: ";
	for (systemList = systemReadyList.begin(); systemList != systemReadyList.end(); systemList++)
	{
		cout << (*systemList)->getPname() << " ";
	}
	cout << endl;

	cout << "1: ";
	for (userList = userReadyList.begin(); userList != userReadyList.end(); userList++)
	{
		cout << (*userList)->getPname() << " ";
	}
	cout << endl;

	cout << "0: ";
	for (initList = initReadyList.begin(); initList != initReadyList.end(); initList++)
	{
		cout << (*initList)->getPname() << " ";
	}
	cout << endl;
}