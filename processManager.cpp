#include "processManager.h"

using namespace std;

processManager::processManager() // todo
{
	this->allocation_pid = 0;
}

processManager::~processManager()
{

}

/* 创建新进程 */
int processManager::createProcess(string pName, int priority)
{
	int pid = 0;
	// 查看进程表是否有重名进程 error=2
	if (checkProcessName(pName) == false)
	{
		return 2;
	}
	// 申请一个PCB (申请pid)
	pid = this->allocation_pid++;
	// 初始化PCB
	PCB* pcb = new PCB(pid, pName, (processPriorities)priority, runningProcess);

	// 放入进程表
	processTable.push_back(pcb);

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

	return 1;
}

/* 进程调度 */
void processManager::Schedule()
{

}



/* 根据pid在进程表中寻找进程 (用于释放进程) */
vector<PCB*>::iterator processManager::findProcess(int pid)
{
	vector<PCB*>::iterator data;

	for (data = processTable.begin(); data != processTable.end(); data++)
		if ((*data)->getPid() == pid)
			return data;

	return data;
}

/* 检查进程名是否重名 */
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