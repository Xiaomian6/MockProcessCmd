#include "processManager.h"

using namespace std;

processManager::processManager() // todo
{
	this->allocation_pid = 1; // pid 自增 从 PID = 1 开始
	this->runningProcess = nullptr;
}

processManager::~processManager()
{

}

/* 创建新进程 */
int processManager::createProcess(const string pName, int priority)
{
	int pid = 0;

	// 查看进程表是否有重名进程 error = 2
	if (checkProcessName(pName) == true)
	{
		return 2;
	}
	// 申请一个PCB (申请pid)
	pid = this->allocation_pid++;
	// 初始化PCB
	PCB* pcb = new PCB(pid, pName, (processPriorities)priority, runningProcess);

	pcb->showThisProcess();
	
	// 放入进程表
	this->processTable.push_back(pcb);

	// init进程处理
	if (priority == 0)
	{
		this->runningProcess = pcb;
	}

	// 放入就绪队列
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

	// 调度 todo
	return 1;
}

/* 撤销进程 Process can be destroyed by any of its ancestors or by itself (exit)  */
int processManager::destroyProcess(const string delname)
{
	vector<PCB*>::iterator delData;

	// 查看撤销进程ID是否在进程表
	if (checkProcessName(delname) == false)
	{
		return 2;
	}
	
	// 根据 pname 寻找进程，返回 进程块
	delData = this->findProcessbypName(delname);

	PCB* pcb = (*delData);

	// free resources 


	// 嵌套调用，撤销所有子孙进程 



	// delete PCB and update all pointers 


	return 1;
}

/* 进程调度 */
void processManager::Schedule()
{

}

/* 删除child node 进程 */
int processManager::deleteChildProcess(int pid)
{

	return 1;
}

/* 根据 pid 在进程表中寻找进程  */
vector<PCB*>::iterator processManager::findProcessbypID(int pid)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPid() == pid)
			return data;

	return data;
}

/* 根据 pname 在进程表中寻找进程  */
vector<PCB*>::iterator processManager::findProcessbypName(string pname)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPname() == pname)
			return data;

	return data;
}

/* 检查进程名是否存在 */
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

/* 检查进程表是否存在此ID */
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

/* 创建并初始化资源列表 */
void processManager::createResources()
{
	// 创建4类资源
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

/* 请求资源 */
int processManager::requestResources(const string rName, const int number)
{
	int operand = 0; // 操作数

	// 检查是否有此资源 error = 2
	if (checkResourcesName(rName) == false)
	{
		return 2;
	}

	// 检查请求是否超过此资源总量 error = 3
	if (checkResourcesInitnum(rName, number) == false)
	{
		return 3;
	}

	// 根据 rName 找到相应 RCB块
	RCB* rcb = findResourcesByName(rName);

	// request
	if (rcb->getNumber() >= number)  // 剩余资源足够
	{
		operand = rcb->requestR(number, runningProcess);  // 减去请求数量资源
		runningProcess->addResource(number, rcb);         // 把rcb插入pcb的占有资源列表
	}
	else // 剩余资源不够，阻塞
	{
		// 进程设置 阻塞状态
		runningProcess->changeBLOCKED();

		// 进程加入 阻塞列表
		runningProcess->changeBLOCKLIST();

		// 因为运行进程位于绪队列首部，所以此时将它从 就绪队列 移除
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

		// 插入 RCB 资源阻塞等待队列

		// 调度

	}




	return 1;
}

/* 根据rname在资源列表中寻找资源  */
RCB* processManager::findResourcesByName(string rname)
{
	vector<RCB*>::iterator data;

	for (data = resourcesTable.begin(); data != resourcesTable.end(); data++)
		if ((*data)->getRname() == rname)
			return *data;

	return *data;
}

/* 检查资源名是否存在 */
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

/* 检查请求是否超过此资源总量 */
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

/* 移除 Init 就绪队列首部 */
bool processManager::removeInitReadyListFirst()
{
	

	return false; // error
}

/* 移除 User 就绪队列首部 */
bool processManager::removeUserReadyListFirst()
{

}

/* 移除 System 就绪队列首部 */
bool processManager::removeSystemReadyListFirst()
{

}

/*************************************************************
 *  processManager
 *  get() - show()
 *************************************************************/

/* 获取正在执行进程的ID */
int processManager::getRunningProcess()
{
	return this->runningProcess->getPid();
}

/* 显示就绪进程队列 */
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

/* 显示主进程表 */
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

/* 显示资源列表 */
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