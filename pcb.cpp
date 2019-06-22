#include <string>
#include "pcb.h"

using namespace std;

/* ���캯�� (�½�PCB) */
PCB::PCB(int pid, string pName, processPriorities priority, PCB* parent)
{
	this->pid = pid;
	this->pName = pName;
	this->priority = priority;

	this->pTree.parent = parent;
	if (parent != nullptr)
	{
		parent->addChild(this);
	}

	this->pStatus.pType = READY;
	this->pStatus.pList = READYLIST;
	// todo ռ����Դ��
} 

/* �������� */
PCB::~PCB() 
{

}

/* ��ӽ��̵��ӽ��� */
int PCB::addChild(PCB* child)
{
	this->pTree.child.push_back(child);
	return 1;
}

/* ��ӽ��̵���Դ�� */
int PCB::addResource(int num, RCB* rcb)
{
	// ��������ռ����Դ�б��Ƿ�����ͬ�� RCB ��
	for (vector<Resource>::iterator iter = Resources.begin(); iter != Resources.end(); iter++)
	{
		if (iter->rcb == rcb)
		{
			iter->ownNum = iter->ownNum + num;
			return 1;
		}
	}

	// û���ҵ� �����
	Resource newResource(rcb->getRid(), num, rcb);   // ���� pcb ����Դ�� Resource
	this->Resources.push_back(newResource);        // ��ӵ����̵�ռ����Դ�б�
	return 0;
}

/* �Ƴ����̵���Դ�� */
int PCB::deleteResource(int num, RCB* rcb)
{
	int number = 0;
	int i = 0;
	int temp = 0;
	bool flag = false;

	// ��������ռ����Դ�б��Ƿ�����ͬ�� RCB ��
	for (vector<Resource>::iterator iter = Resources.begin(); iter != Resources.end(); iter++)
	{
		if (iter->rcb == rcb)
		{
			if (iter->ownNum > num)  // ��Ч, �����Ƴ� Resource ��
			{
				number = iter->ownNum; // ռ�õ�����
			}
			else if (iter->ownNum == num)  // ��Ч, ���Ƴ� Resource ��
			{
				number = iter->ownNum; // ռ�õ�����
				temp = i;
				flag = true;
			}
			else  // ��Ч������ 0
			{
				return 0;
			}
			
		}
		i++;
	}

	if (i == Resources.size()+1)  // ��Դ�鲻��
	{
		return -1;
	}

	if (flag == true)  // �Ƴ� Resource ��
	{
		Resources.erase(Resources.begin() + i - 1);
	}

	return number;  // ����ռ�õ�����,error = 0
}

/* ��������Ϊ����̬ */
int PCB::changeBLOCKED()
{
	this->pStatus.pType = BLOCKED;
	return 0;
}

/* ��������Ϊ����̬ */
int PCB::changeRUNNING()
{
	this->pStatus.pType = RUNNING;
	return 0;
}

/* ��������Ϊ����̬ */
int PCB::changeREADY()
{
	this->pStatus.pType = READY;
	return 0;
}

/* ��������Ϊ�����б� */
int PCB::changeBLOCKLIST()
{
	this->pStatus.pList = BLOCKLIST;
	return 0;
}

/* ��������Ϊ�������� */
int PCB::changeREADYLIST()
{
	this->pStatus.pList = READYLIST;
	return 0;
}

/*************************************************************
 *  PCB
 *  get() show()
 *************************************************************/

/* ��ʾ����������Ϣ */
void PCB::showThisProcess()
{
	cout << "------------------" << endl;
	cout << "pid: " << this->pid << endl;
	cout << "name: " << this->pName << endl;

	switch (this->pStatus.pType)
	{
	case 0:
		cout << "Status: " << "READY" << endl;
		break;
	case 1:
		cout << "Status: " << "RUNNING" << endl;
		break;
	case 2:
		cout << "Status: " << "BLOCKED" << endl;
		break;
	default:
		cout << "BUG BUG BUG BUG" << endl;
		break;
	}

	switch (this->pStatus.pList)
	{
	case 0:
		cout << "        " << "READYLIST" << endl;
		break;
	case 1:
		cout << "        " << "BLOCKLIST" << endl;
		break;
	default:
		cout << "BUG BUG BUG BUG" << endl;
		break;
	}

	if (this->pTree.parent != nullptr)
	{
		cout << "Father: " << this->pTree.parent->getPname() << endl;
	}

	cout << "priority: " << this->priority << endl;
	cout << "------------------" << endl;
}

int PCB::getPid()
{
	return this->pid;
}

string PCB::getPname()
{
	return this->pName;
}

int PCB::getPriority()
{
	return this->priority;
}

string PCB::getType()
{
	switch (this->pStatus.pType)
	{
	case 0:
		return "READY" ;
		break;
	case 1:
		return "RUNNING" ;
		break;
	case 2:
		return "BLOCKED" ;
		break;
	default:
		cout << "BUG BUG BUG BUG" << endl;
		break;
	}
	return "ERROR";
}

string PCB::getList()
{
	switch (this->pStatus.pList)
	{
	case 0:
		return "READYLIST" ;
		break;
	case 1:
		return "BLOCKLIST" ;
		break;
	default:
		cout << "BUG BUG BUG BUG" << endl;
		break;
	}
	return "ERROR";
}

string PCB::getFather()
{
	if (this->pTree.parent == nullptr)
	{
		return "null";
	}
	return this->pTree.parent->getPname();
}

// ���������
void PCB::showChilds()
{
	vector<PCB*>::iterator data;
	
	for (data = pTree.child.begin(); data != pTree.child.end(); data++)
	{
		cout << (*data)->getPname() << "    ";
	}

}

/* ����ռ����Դ�б��ռ������ */
int PCB::getResourcesOwnNum(int RCBID)
{
	// ��������ռ����Դ�б��Ƿ�����ͬ�� RCB ��
	for (vector<Resource>::iterator iter = Resources.begin(); iter != Resources.end(); iter++)
	{
		if (iter->ownID == RCBID)
		{
			return iter->ownNum;
		}
	}
	return 0;
}