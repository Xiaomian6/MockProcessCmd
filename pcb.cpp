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

/* 添加进程的子进程 */
int PCB::addChild(PCB* child)
{
	this->pTree.child.push_back(child);
	return 1;
}

/* 添加进程的资源块 */
int PCB::addResource(int num, RCB* rcb)
{
	// 遍历进程占有资源列表是否有相同的 RCB 块
	for (vector<Resource>::iterator iter = Resources.begin(); iter != Resources.end(); iter++)
	{
		if (iter->rcb == rcb)
		{
			iter->ownNum = iter->ownNum + num;
			return 1;
		}
	}

	// 没有找到 则添加
	Resource newResource(rcb->getRid(), num, rcb);   // 创建 pcb 的资源块 Resource
	this->Resources.push_back(newResource);        // 添加到进程的占有资源列表
	return 0;
}

/* 移除进程的资源块 */
int PCB::deleteResource(int num, RCB* rcb)
{
	int number = 0;
	int i = 0;
	int temp = 0;
	bool flag = false;

	// 遍历进程占有资源列表是否有相同的 RCB 块
	for (vector<Resource>::iterator iter = Resources.begin(); iter != Resources.end(); iter++)
	{
		if (iter->rcb == rcb)
		{
			if (iter->ownNum > num)  // 有效, 但不移除 Resource 块
			{
				number = iter->ownNum; // 占用的数量
			}
			else if (iter->ownNum == num)  // 有效, 但移除 Resource 块
			{
				number = iter->ownNum; // 占用的数量
				temp = i;
				flag = true;
			}
			else  // 无效，返回 0
			{
				return 0;
			}
			
		}
		i++;
	}

	if (i == Resources.size()+1)  // 资源块不在
	{
		return -1;
	}

	if (flag == true)  // 移除 Resource 块
	{
		Resources.erase(Resources.begin() + i - 1);
	}

	return number;  // 返回占用的数量,error = 0
}

/* 进程设置为阻塞态 */
int PCB::changeBLOCKED()
{
	this->pStatus.pType = BLOCKED;
	return 0;
}

/* 进程设置为运行态 */
int PCB::changeRUNNING()
{
	this->pStatus.pType = RUNNING;
	return 0;
}

/* 进程设置为就绪态 */
int PCB::changeREADY()
{
	this->pStatus.pType = READY;
	return 0;
}

/* 进程设置为阻塞列表 */
int PCB::changeBLOCKLIST()
{
	this->pStatus.pList = BLOCKLIST;
	return 0;
}

/* 进程设置为就绪队列 */
int PCB::changeREADYLIST()
{
	this->pStatus.pList = READYLIST;
	return 0;
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

/* 返回占有资源列表的占有数量 */
int PCB::getResourcesOwnNum(int RCBID)
{
	// 遍历进程占有资源列表是否有相同的 RCB 块
	for (vector<Resource>::iterator iter = Resources.begin(); iter != Resources.end(); iter++)
	{
		if (iter->ownID == RCBID)
		{
			return iter->ownNum;
		}
	}
	return 0;
}