#include <string>
#include "pcb.h"

using namespace std;

/* 构造函数 (新建PCB) */
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
	// todo 占用资源表
} 

/* 析构函数 */
PCB::~PCB() 
{

}

int PCB::addChild(PCB* child)
{
	this->pTree.child.push_back(child);
	return 1;
}


/*************************************************************
 *  PCB
 *  get() show()
 *************************************************************/

/* 显示单个进程信息 */
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

// 函数内输出
void PCB::showChilds()
{
	vector<PCB*>::iterator data;
	
	for (data = pTree.child.begin(); data != pTree.child.end(); data++)
	{
		cout << (*data)->getPname() << "    ";
	}

}