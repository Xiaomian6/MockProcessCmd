#include <string>
#include "pcb.h"

using namespace std;

PCB::PCB(int pid, string pName, processPriorities priority, PCB* parent)
{
	this->pid = pid;
	this->pName = pName;
	this->priority = priority;
	this->pTree.parent = parent;
	// this->pTree.child NULL
	this->pStatus.pType = READY;
	this->pStatus.pList = READYLIST;
	// todo 占用资源表
} 

PCB::~PCB() // 
{

}


/*************************************************************
 *  PCB
 *  get()
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

	cout << "Father: " << this->pTree.parent->getPname() << endl;

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