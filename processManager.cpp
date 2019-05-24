#include "processManager.h"

using namespace std;

processManager::processManager() // todo
{
	this->allocation_pid = 1;
	this->runningProcess = nullptr;
}

processManager::~processManager()
{

}

/* �����½��� */
int processManager::createProcess(const string pName, int priority)
{
	int pid = 0;

	// �鿴���̱��Ƿ����������� error=2
	if (checkProcessName(pName) == true)
	{
		return 2;
	}
	// ����һ��PCB (����pid)
	pid = this->allocation_pid++;
	// ��ʼ��PCB
	PCB* pcb = new PCB(pid, pName, (processPriorities)priority, runningProcess);
	pcb->showThisProcess();
	
	// ������̱�
	processTable.push_back(pcb);

	// init���̴���
	if (priority == 0)
	{
		this->runningProcess = pcb;
	}

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

	// del test
	this->runningProcess = pcb;

	// ���� todo
	return 1;
}

/* �������� Process can be destroyed by any of its ancestors or by itself (exit)  */
int processManager::destroyProcess(const string delname)
{
	vector<PCB*>::iterator delData;

	// �鿴��������ID�Ƿ��ڽ��̱�
	if (checkProcessName(delname) == false)
	{
		return 2;
	}
	
	// ����pnameѰ�ҽ���
	delData = this->findProcessbypName(delname);

	PCB* pcb = (*delData);

	// free resources 


	// Ƕ�׵��ã���������������� 



	// delete PCB and update all pointers 


	return 1;
}

/* ���̵��� */
void processManager::Schedule()
{

}
/* ɾ��child node ���� */
int processManager::deleteChildProcess(int pid)
{

}

/* ����pid�ڽ��̱���Ѱ�ҽ���  */
vector<PCB*>::iterator processManager::findProcessbypID(int pid)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPid() == pid)
			return data;

	return data;
}

/* ����pname�ڽ��̱���Ѱ�ҽ���  */
vector<PCB*>::iterator processManager::findProcessbypName(string pname)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPname() == pname)
			return data;

	return data;
}

/* ���������Ƿ���� */
bool processManager::checkProcessName(string name)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
	{
		if ((*data)->getPname() == name)
		{
			return true;
		}
	}

	return false;
}

/* �����̱��Ƿ���ڴ�ID */
bool processManager::checkProcessID(int id)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
	{
		if ((*data)->getPid() == id)
		{
			return true;
		}
	}

	return false;
}

/*************************************************************
 *  processManager
 *  get() show()
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

/* ��ʾ�����̱� */
void processManager::showProcessTable()
{
	vector<PCB*>::iterator data;
	cout << "****** Process Table ******" << endl;
	cout << "PID  NAME PRIORITY TYPE LIST FATHER " << endl;
	for (data = processTable.begin(); data != processTable.end(); data++)
	{
		cout << (*data)->getPid() << "    ";
		cout << (*data)->getPname() << "    ";
		cout << (*data)->getPriority() << "    ";
		cout << (*data)->getType() << "    ";
		cout << (*data)->getList() << "    ";
		if (((*data)->getFather()) != "null")
		{
			cout << (*data)->getFather() << "    ";
		}
		else {
			cout << "     " << "    ";
		}
		(*data)->showChilds();
		cout << endl;
	}
	cout << "*************************" << endl;
}