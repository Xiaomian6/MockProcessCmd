#include "processManager.h"

using namespace std;

processManager::processManager() // todo
{
	this->allocation_pid = 1; // pid ���� �� PID = 1 ��ʼ
	this->runningProcess = nullptr;
}

processManager::~processManager()
{

}

/* �����½��� */
int processManager::createProcess(const string pName, int priority)
{
	int pid = 0;

	// �鿴���̱��Ƿ����������� error = 2
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
	this->processTable.push_back(pcb);

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
	
	// ���� pname Ѱ�ҽ��̣����� ���̿�
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

	return 1;
}

/* ���� pid �ڽ��̱���Ѱ�ҽ���  */
vector<PCB*>::iterator processManager::findProcessbypID(int pid)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPid() == pid)
			return data;

	return data;
}

/* ���� pname �ڽ��̱���Ѱ�ҽ���  */
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
 *  RCB
 *************************************************************/

/* ��������ʼ����Դ�б� */
void processManager::createResources()
{
	// ����4����Դ
	// R1  1 
	// R2  2
	// R3  3
	// R4  4

	RCB* rcb1 = new RCB(1,"R1", 1);
	RCB* rcb2 = new RCB(2,"R2", 2);
	RCB* rcb3 = new RCB(3,"R3", 3);
	RCB* rcb4 = new RCB(4,"R4", 4);

	this->resourcesTable.push_back(rcb1);
	this->resourcesTable.push_back(rcb2);
	this->resourcesTable.push_back(rcb3);
	this->resourcesTable.push_back(rcb4);
}

/* ������Դ */
int processManager::requestResources(const string rName, const int number)
{
	int operand = 0; // ������

	// ����Ƿ��д���Դ error = 2
	if (checkResourcesName(rName) == false)
	{
		return 2;
	}

	// ��������Ƿ񳬹�����Դ���� error = 3
	if (checkResourcesInitnum(rName, number) == false)
	{
		return 3;
	}

	// ���� rName �ҵ���Ӧ RCB��
	RCB* rcb = findResourcesByName(rName);

	// request
	if (rcb->getNumber() >= number)  // ʣ����Դ�㹻
	{
		operand = rcb->requestR(number, runningProcess);  // ��ȥ����������Դ
		runningProcess->addResource(number, rcb);         // ��rcb����pcb��ռ����Դ�б�
	}
	else // ʣ����Դ����������
	{
		// �������� ����״̬
		runningProcess->changeBLOCKED();

		// ���̼��� �����б�
		runningProcess->changeBLOCKLIST();

		// ��Ϊ���н���λ���������ײ������Դ�ʱ������ �������� �Ƴ�
		switch (runningProcess->getPriority)
		{
		case 0: // INIT
			
			break;

		case 1: // USER
			
			break;

		case 2: // SYSTEM
			
			break;

		default:
			break;
		}

		// ���� RCB ��Դ�����ȴ�����

		// ����

	}




	return 1;
}

/* ����rname����Դ�б���Ѱ����Դ  */
RCB* processManager::findResourcesByName(string rname)
{
	vector<RCB*>::iterator data;

	for (data = resourcesTable.begin(); data != resourcesTable.end(); data++)
		if ((*data)->getRname() == rname)
			return *data;

	return *data;
}

/* �����Դ���Ƿ���� */
bool processManager::checkResourcesName(string name)
{
	vector<RCB*>::iterator data;

	for (data = resourcesTable.begin(); data != resourcesTable.end(); data++)
	{
		if ((*data)->getRname() == name)
		{
			return true;
		}
	}

	return false; // error
}

/* ��������Ƿ񳬹�����Դ���� */
bool  processManager::checkResourcesInitnum(string name, int num)
{
	vector<RCB*>::iterator data;

	for (data = resourcesTable.begin(); data != resourcesTable.end(); data++)
	{
		if ((*data)->getInitNum() >= num)
		{
			return true;
		}
	}

	return false; // error
}

/* �Ƴ� Init ���������ײ� */
bool processManager::removeInitReadyListFirst()
{
	

	return false; // error
}

/* �Ƴ� User ���������ײ� */
bool processManager::removeUserReadyListFirst()
{

}

/* �Ƴ� System ���������ײ� */
bool processManager::removeSystemReadyListFirst()
{

}

/*************************************************************
 *  processManager
 *  get() - show()
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

/* ��ʾ��Դ�б� */
void processManager::showResourcesTable()
{
	vector<RCB*>::iterator data;

	cout << "**** Resources Table ****" << endl;
	cout << "Name  number" << endl;
	for (data = resourcesTable.begin(); data != resourcesTable.end(); data++)
	{
		cout << (*data)->getRname() << "       ";
		cout << (*data)->getNumber() << endl;
	}
	cout << "*************************" << endl;
}