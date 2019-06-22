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

	// pcb->showThisProcess(); // show test
	
	// ������̱�
	this->processTable.push_back(pcb);

	// init���̴���
	if (priority == 0)
	{
		this->runningProcess = pcb;
		runningProcess->changeRUNNING();
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
	// this->runningProcess = pcb;

	// ���� 
	// ����½����̱�����ִ�н������ȼ���
	if (runningProcess->getPriority() < pcb->getPriority())
	{
		runningProcess->changeREADY();
		this->runningProcess = pcb;
		runningProcess->changeRUNNING();
		cout << "[warnning]�л����� " + runningProcess->getPname() + " ����" << endl;
	}

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

	// Ƕ�׵��ã���������������� 
	deleteChildProcess(pcb);

	return 4;
}

/* ���̵���Schedule */
void processManager::Schedule()
{
	// ����2������
	if (systemReadyList.size() != 0)
	{
		systemReadyList.pop_front();                // �Ƴ�system �����б��һ��
		systemReadyList.push_back(runningProcess);  // ����������������ĩβ
		runningProcess->changeREADY();
		runningProcess->changeREADYLIST();
		runningProcess = systemReadyList.front();   // ����ִ�н���ָ�� ָ��������е�һ��
		runningProcess->changeRUNNING();
	}
	else  // ��û��2�����̵�, ֻ��1����������
	{
		userReadyList.pop_front();                  // �Ƴ�user �����б��һ��
		userReadyList.push_back(runningProcess);    // ����������������ĩβ
		runningProcess->changeREADY();
		runningProcess->changeREADYLIST();
		runningProcess = userReadyList.front();     // ����ִ�н���ָ�� ָ��������е�һ��
		runningProcess->changeRUNNING();
	}

}

/* ɾ��child node ���� */
int processManager::deleteChildProcess(PCB* pcb)
{
	int temp = -1;
	int tempID = 0;
	vector<PCB*>::iterator delData;

	while (pcb->getpTreeEmpty() == true) // ѭ��Kill childs
	{
		tempID = pcb->getpTreeFirstChild();// ��ȡ�ý��̵�һ���ӽ���
		delData = this->findProcessbypID(tempID);
		PCB* tempPCB = (*delData);
		pcb->deleteChild();  // �Ƴ��ý��̵�һ���ӽ���
		deleteChildProcess(tempPCB);    // Ƕ���²�
	}

	RCB* rcb;
	// Kill myself
	// free resources
	temp = freeResources(pcb);
	if (temp != 1)  // test bug
	{
		cout << "BUG BUG BUG!!!" << endl;
	}

	// ����
	if (pcb == runningProcess)  // ����ִ��̬���� ��һ������̬
	{
		if (systemReadyList.size() == 1)  // ����߼�system�������̶��о�ʣ��ִ��̬�����Լ�һ�� ����
		{
			runningProcess = userReadyList.back();
			systemReadyList.pop_back();
		}else if(userReadyList.size() == 1)  // ����߼�user�������̶��о�ʣ��ִ��̬�����Լ�һ�� ����
		{
			runningProcess = initReadyList.back();
			userReadyList.pop_back();
		}
		else {
			Schedule(); // ����
			if (pcb->getPriority() == 1)
			{
				deleteUserReadyList(pcb);
			}
			else if (pcb->getPriority() == 2)
			{
				deleteSystemReadyList(pcb);
			}
			else
			{

			}
		}
	}
	else if (pcb->getType() == "READY")  // ����
	{
		if (pcb->getPriority() == 1)
		{
			deleteUserReadyList(pcb);
		}
		else if (pcb->getPriority() == 2)
		{
			deleteSystemReadyList(pcb);
		}
		else   
		{

		}
	}  // ǰ���Ѿ������� ����̬
	cout << "���� " + pcb->getPname() + "�ѳ���!" << endl;
	// �ͷ� PCB �ռ�
	deleteProcessTable(pcb);
	pcb->deleteFather();
	delete(pcb);
	return 0;
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

/* ѭ�� freeResources */
int processManager::freeResources(PCB* pcb)
{
	int tempPID = -1;
	int temp = 0;
	int tempNUM = 0;
	RCB* rcb;
	vector<PCB*>::iterator tempPCB;

	// ��ѯ���� �Ƿ���ռ�е���Դ
	while (pcb->getResourcesEmpty() == false)  // ��Ϊ��
	{
		rcb = pcb->getResourcesFirstRCB();  // ��ȡ��һ��RCB
		// ����Դ rcb ��pcb ���� Resourcesռ����Դ�б����Ƴ�
	    // ����Դ״̬ ����rStatus + number
		temp = pcb->deleteResource(pcb->getResourcesOwnNum(rcb->getRid()), rcb);
		rcb->releaseR(temp);

		// ������ִ�н����޹�
	    // ��� RCB �������в�Ϊ��, �����������ײ������������Դ�� req С�ڵ��ڿ�����Դ���� u����������������̣������������
		while ((rcb->waitingListEmpty() == false) && (rcb->isWaitingListFirst() == true))
		{
			rcb->requestR(rcb->getWaitingListFirstNum());  // ��ȥ����������Դ
			tempPID = rcb->getWaitingListFirstPID();
			tempNUM = rcb->getWaitingListFirstNum();
			tempPCB = findProcessbypID(tempPID);
			PCB* changePCB = (*tempPCB);  // �ҵ�RCB ��Դ�����ȴ����� ��һ������

			rcb->deleteWaitingList();   // ����Դ�������������Ƴ� ��һ������

			changePCB->changeREADY();
			changePCB->changeREADYLIST();
			// �� rcb ���뵽 changePCB ռ����Դ�б���
			changePCB->addResource(tempNUM, rcb);         // ��rcb����pcb��ռ����Դ�б�

			// ���� changePCB ���������� 
			// �������ȼ�����ռʽ���Ȳ��ԣ���˵��н��̻����Դʱ����Ҫ�鿴��ǰ�����ȼ���������е���
			switch (changePCB->getPriority())
			{
			case 0: // INIT update
				deleteBlockList(changePCB);
				initReadyList.push_back(changePCB);
				// �����ж�
				break;

			case 1: // USER 
				// �����ж�
				if (userReadyList.size() == 0)
				{
					deleteBlockList(changePCB);
					userReadyList.push_back(changePCB);				
					runningProcess = changePCB;  // �����ȼ���ռ����
					changePCB->changeRUNNING();
				}
				else
				{
					deleteBlockList(changePCB);
					userReadyList.push_back(changePCB);
				}
				break;

			case 2: // SYSTEM 
				// �����ж�
				if (systemReadyList.size() == 0)
				{
					deleteBlockList(changePCB);
					systemReadyList.push_back(changePCB);
					runningProcess = changePCB;  // �����ȼ���ռ����
					changePCB->changeRUNNING();
				}
				else
				{
					deleteBlockList(changePCB);
					systemReadyList.push_back(changePCB);
				}
				break;

			default:
				break;
			}

		}
	}
	
	return 1;
}

/* ɾ��userReadyListָ�������� */
int processManager::deleteUserReadyList(PCB* pcb)
{
	list<PCB*>::iterator data;

	for (data = userReadyList.begin(); data != userReadyList.end(); )
	{
		if ((*data)->getPid() == pcb->getPid())
		{
			userReadyList.erase(data++);
			return 1;
		}
		else
		{
			data++;
		}

	}
	return 0;
}

/* ɾ��systemReadyListָ�������� */
int processManager::deleteSystemReadyList(PCB* pcb)
{
	list<PCB*>::iterator data;

	for (data = systemReadyList.begin(); data != systemReadyList.end(); )
	{
		if ((*data)->getPid() == pcb->getPid())
		{
			systemReadyList.erase(data++);
			return 1;
		}
		else
		{
			data++;
		}

	}
	return 0;
}

/* ɾ��������ĳ�� */
int processManager::deleteProcessTable(PCB* pcb)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); )
	{
		if ((*data)->getPid() == pcb->getPid())
		{
			processTable.erase(data++);
			return 1;
		}
		else
		{
			data++;
		}

	}
	return 0;
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
		operand = rcb->requestR(number);  // ��ȥ����������Դ
		runningProcess->addResource(number, rcb);         // ��rcb����pcb��ռ����Դ�б�
		return 1;
	}
	else // ʣ����Դ����������
	{
		// �������� ����״̬
		runningProcess->changeBLOCKED();

		// ���̼��� �����б�
		runningProcess->changeBLOCKLIST();

		// ���� RCB ��Դ�����ȴ�����
		rcb->addWaitingList(number, runningProcess);

		// ��Ϊ���н���λ���������ײ������Դ�ʱ������ �������� �Ƴ�, ����
		switch (runningProcess->getPriority())
		{
		case 0: // INIT
			initReadyList.pop_front();   // ɾ���������е�һ��Ԫ��
			blockList.push_back(runningProcess);
			cout << "BUG:init��������,�������!" << endl; // BUG
			exit(1);
			cout << "[warnning]���� " + runningProcess->getPname() + " ����!" << endl;
			runningProcess = initReadyList.front();   // ����ִ�н���ָ�� ָ��������е�һ��
			runningProcess->changeRUNNING();
			break;

		case 1: // USER
			userReadyList.pop_front();
			blockList.push_back(runningProcess);
			cout << "[warnning]���� " + runningProcess->getPname() + " ����!" << endl;
			// �����ж�
			if (userReadyList.size() != 0)
			{
				runningProcess = userReadyList.front();   // ����ִ�н���ָ�� ָ��������е�һ��
				runningProcess->changeRUNNING();
			}
			else
			{
				runningProcess = initReadyList.front();   // ����ִ�н���ָ�� ָ��������е�һ��
				runningProcess->changeRUNNING();
			}
			break;

		case 2: // SYSTEM
			systemReadyList.pop_front();
			blockList.push_back(runningProcess);
			cout << "[warnning]���� " + runningProcess->getPname() + " ����!" << endl;
			// �����ж�
			if (systemReadyList.size() != 0)
			{
				runningProcess = systemReadyList.front();   // ����ִ�н���ָ�� ָ��������е�һ��
				runningProcess->changeRUNNING();
			}
			else
			{
				runningProcess = userReadyList.front();   // ����ִ�н���ָ�� ָ��������е�һ��
				runningProcess->changeRUNNING();
			}
			break;

		default:
			break;
		}


		// ������̵���
		cout << "[warnning]�л����� " + runningProcess->getPname() + " ִ��!" << endl;
	}

	return 4;
}

/* �ͷ���Դ */
int processManager::releaseResources(const string rName, const int number)
{
	int operand = 0;  // ������
	int tempPID = -1;
	int tempNUM = 0;
	
	vector<PCB*>::iterator tempPCB;

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

	// release
	
	// ����Դ rcb �Ӵӵ�ǰ���� Resourcesռ����Դ�б����Ƴ�
	// ����Դ״̬ ����rStatus + number
	operand = runningProcess->deleteResource(number, rcb);

	if (operand == 0)  // �ͷ���Դ������Ч
	{
		return 4;
	} 
	else if (operand == -1) // �ý����޸���Դ
	{
		return 5;
	}
	else
	{
		rcb->releaseR(operand);  // rStatus + number
	}
             
	// ������ִ�н����޹�
	// ����������в�Ϊ��, �����������ײ������������Դ�� req С�ڵ��ڿ�����Դ���� u����������������̣������������
	while ((rcb->waitingListEmpty() == false) && (rcb->isWaitingListFirst() == true))
	{
		rcb->requestR(rcb->getWaitingListFirstNum());  // ��ȥ����������Դ
		tempPID = rcb->getWaitingListFirstPID();
		tempNUM = rcb->getWaitingListFirstNum();
		tempPCB = findProcessbypID(tempPID);
		PCB* changePCB = (*tempPCB);  // �ҵ�RCB ��Դ�����ȴ����� ��һ������

		rcb->deleteWaitingList();   // ����Դ�������������Ƴ� ��һ������

		changePCB->changeREADY();
		changePCB->changeREADYLIST();
		// �� rcb ���뵽 changePCB ռ����Դ�б���
		changePCB->addResource(tempNUM, rcb);         // ��rcb����pcb��ռ����Դ�б�

	    // ���� changePCB ���������� 
		// �������ȼ�����ռʽ���Ȳ��ԣ���˵��н��̻����Դʱ����Ҫ�鿴��ǰ�����ȼ���������е���
		switch (changePCB->getPriority())
		{
		case 0: // INIT update
			deleteBlockList(changePCB);
			initReadyList.push_back(changePCB);
			cout << "[warnning]���� " + changePCB->getPname() + " ����!" << endl;
			// �����ж�
			break;

		case 1: // USER 
			// �����ж�
			if (userReadyList.size() == 0)
			{
				deleteBlockList(changePCB);
				userReadyList.push_back(changePCB);
				cout << "[warnning]���� " + changePCB->getPname() + " ����!" << endl;
				runningProcess = changePCB;  // �����ȼ���ռ����
				changePCB->changeRUNNING();
				cout << "[warnning]�����ȼ����� " + runningProcess->getPname() + " ��ռ" << endl;
			}
			else
			{
				deleteBlockList(changePCB);
				userReadyList.push_back(changePCB);
				cout << "[warnning]���� " + changePCB->getPname() + " ����!" << endl;
			}
			break;

		case 2: // SYSTEM 
			// �����ж�
			if (systemReadyList.size() == 0)
			{
				deleteBlockList(changePCB);
				systemReadyList.push_back(changePCB);
				cout << "[warnning]���� " + changePCB->getPname() + " ����!" << endl;
				runningProcess = changePCB;  // �����ȼ���ռ����
				changePCB->changeRUNNING();
				cout << "[warnning]�����ȼ����� " + runningProcess->getPname() + " ��ռ" << endl;
			}
			else
			{
				deleteBlockList(changePCB);
				systemReadyList.push_back(changePCB);
				cout << "[warnning]���� " + changePCB->getPname() + " ����!" << endl;
			}
			break;

		default:
			break;
		}

	}

	return 0;
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
		if ((*data)->getRname() == name)
		{
			if ((*data)->getInitNum() >= num)
			{
				return true;
			}
		}
	}

	return false; // error
}

/* ɾ����������ָ�������� */
int processManager::deleteBlockList(PCB* pcb)
{
	list<PCB*>::iterator data;

	for (data = blockList.begin(); data != blockList.end(); )
	{
		if ((*data)->getPid() == pcb->getPid())
		{
			blockList.erase(data++);
			return 1;
		}
		else
		{
			data++;
		}
		
	}
	return 0;
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
	list<PCB*>::iterator initList;
	list<PCB*>::iterator userList;
	list<PCB*>::iterator systemList;

	cout << "[show] ReadyList" << endl;

	cout << "2: ";
	for (systemList = systemReadyList.begin(); systemList != systemReadyList.end(); systemList++)
	{
		if (runningProcess->getPid() == (*systemList)->getPid())
		{
			cout << "->";
		}
		cout << (*systemList)->getPname() << " ";
	}
	cout << endl;

	cout << "1: ";
	for (userList = userReadyList.begin(); userList != userReadyList.end(); userList++)
	{
		if (runningProcess->getPid() == (*userList)->getPid())
		{
			cout << "->";
		}
		cout << (*userList)->getPname() << " ";
	}
	cout << endl;

	cout << "0: ";
	for (initList = initReadyList.begin(); initList != initReadyList.end(); initList++)
	{
		if (runningProcess->getPid() == (*initList)->getPid())
		{
			cout << "->";
		}
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

/* ��ʾ������������ */
void processManager::showBlockList()
{
	list<PCB*>::iterator data;

	cout << "**** blockList ****" << endl;
	for (data = blockList.begin(); data != blockList.end(); data++)
	{
		cout << (*data)->getPname() << "  ";
	}
	cout << endl;
	cout << "*************************" << endl;
}