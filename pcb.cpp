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
	cout << "Status: " << this->pStatus.pType << " -- " << this->pStatus.pList << endl;
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