#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "pcb.h"
#include "rcb.h"
#include "processManager.h"
#include "splitTool.h"

using namespace std;

void inputCmd(vector<string>& argvs);
void initCmd();
void createProcessCmd(const vector<string>& argvs);
void destroyProcessCmd(const vector<string>& argvs);
void requestResourcesCmd(const vector<string>& argvs);
void releaseResoursesCmd(const vector<string>& argvs);
void showReadyListCmd(const vector<string>& argvs);
void showResourcesListCmd(const vector<string>& argvs);
void timeOutCmd(const vector<string>& argvs);
void quitCmd(const vector<string>& argvs);
void showHelpCmd(const vector<string>& argvs);
void showProcessTable(const vector<string>& argvs);
void showOneProcess(const vector<string>& argvs);

static const map<string, void(*)(const vector<string> &)> mapCmd = {
	//{ "init"    , initCmd               },   //
	{ "cr"      , createProcessCmd      },   //
	{ "de"      , destroyProcessCmd     },   //
	{ "req"     , requestResourcesCmd   },   //
	{ "rel"     , releaseResoursesCmd   },   //
	{ "sready"  , showReadyListCmd      },   //
	{ "sres"    , showResourcesListCmd  },   //
	{ "to"      , timeOutCmd            },   //
	{ "quit"    , quitCmd               },    //
	{ "ps"      , showProcessTable      },    //
	{ "pr"      , showOneProcess        }    //
};

static bool quit_flag = true;  // 关闭按钮

// 实例化一个进程管理类
static processManager processManagerRun;

int main()
{
	cout << "Mock Process Cmd ..." << endl;
	cout << "==================================================" << endl;
	cout << "====================" << "Test Shell" << "====================" << endl;
	cout << "==================================================" << endl;
	
	// 自动调用initCmd（）
	initCmd();

	// 调用创建资源并初始化函数
	processManagerRun.createResources();

	while (quit_flag)
	{
		vector<string> argvs;  // 局部变量，自动清空

		inputCmd(argvs);   // 输入处理

		try {
			mapCmd.at(argvs[0])(argvs);
		}
		catch (const exception&) {
			cout << "命令：\"" << argvs[0] << "\" 不合法!" << endl;
		}
	}

	return 0;
}

void inputCmd(vector<string>& argvs)
{
	while (argvs.size() == 0)
	{
		cout << "$shell >";
		string input;
		getline(cin, input);
		split(input, ' ' , argvs);   // 自定义 String: split函数 位于splitTool.h

		// Test this function
		/*
		cout << "===" << "inputArray" << endl;
		for (int i = 0; i < argvs.size(); i++)
		{
			cout << "["<< i << "]"<< argvs[i] << endl;
		}
		cout << "===" << endl;
		*/
	}
}
/*************************************************************
 *  Function: init进程
 *  Format: init
 *************************************************************/
void initCmd()  
{
	int illegalShow = 0; // 不合法显示 
	illegalShow = processManagerRun.createProcess("init", 0);
	if (illegalShow == 1)
	{
		cout << "[sucess]init进程成功创建!" << endl;
	}
	else {
		cout << "BUG BUG BUG BUG" << endl;
	}
}

/*************************************************************
 *  Function: Create new process
 *  Format: cr [pName] [priority]=( 0-INIT, 1-USER, 2-SYSTEM )
 *   (none) -> ready 
 *************************************************************/
void createProcessCmd(const vector<string>& argvs)
{
	int illegalShow = 0; // 不合法显示 
	int priority = 0;
	
	switch (argvs.size())
	{
	case 2:  // default priority 默认USER优先级
		cout << "[prompt]缺省优先级,默认USER优先级" << endl;
		illegalShow = processManagerRun.createProcess(argvs[1], 1);
		break;
	case 3:  // 

		priority = stoi(argvs[2]); // 把string转为int
		if ((priority == 1) || (priority == 2))
		{
			illegalShow = processManagerRun.createProcess(argvs[1], priority);
		}
		else
		{
			illegalShow = 3;
		}
		break;
	default:
		cout << "[error]cr 命令不合法!" << endl;
		break;
	}

	// 1 - 合法
	// 2 - 进程名重复
	// 3 - 优先级不合法
	switch (illegalShow)
	{
	case 1:
		cout << "[success]进程(name:"<< argvs[1] <<")创建成功!" << endl;
		break;

	case 2:
		cout << "[error]进程名重复!" << endl;
		break;

	case 3:
		cout << "[error]优先级不合法!" << endl;
		break;

	default:
		break;
	}
}

/*************************************************************
 *  Function: delete process
 *  Format: de [pname]
 *************************************************************/
void destroyProcessCmd(const vector<string>& argvs)
{
	int illegalShow = 0; // 不合法显示 

	switch (argvs.size())
	{
	case 2:  // de [pname]
		illegalShow = processManagerRun.destroyProcess(argvs[1]);
		break;

	default:
		cout << "[error]de 命令不合法!" << endl;
		break;
	}

	// 1 - 合法
	// 2 - 进程名不存在
	// 3 - 
	switch (illegalShow)
	{
	case 1:
		cout << "[success]进程(name:" << argvs[1] << ")撤销成功!" << endl;
		break;

	case 2:
		cout << "[error]进程名不存在!" << endl;
		break;

	case 3:
		cout << "[error]!" << endl;
		break;

	default:
		break;
	}
}

/*************************************************************
 *  Function: request resources
 *  Format: req [r-name] [number]
 *  Now: R1 - 1
         R2 - 2
		 R3 - 3
		 R4 - 4
 *************************************************************/
void requestResourcesCmd(const vector<string>& argvs)
{
	int illegalShow = 0; // 不合法显示 
	int requestNum = 0;

	switch (argvs.size())
	{
	case 2:  // default number 默认number = 1
		illegalShow = processManagerRun.requestResources(argvs[1], 1);
		break;
	case 3:  // req R1 2
		requestNum = stoi(argvs[2]); // 把string转为int
		illegalShow = processManagerRun.requestResources(argvs[1], requestNum);
		break;
	default:
		cout << "[error]req 命令不合法!" << endl;
		break;
	}

	// 1 - 合法
	// 2 - 请求资源不存在
	// 3 - 请求超过此资源总量
	switch (illegalShow)
	{
	case 1:
		cout << "[success]资源(name:" << argvs[1] << ")请求成功!" << endl;
		break;

	case 2:
		cout << "[error]请求资源不存在!" << endl;
		break;

	case 3:
		cout << "[error]请求超过此资源总量!" << endl;
		break;

	default:
		break;
	}
}

/*************************************************************
 *  Function: release resources
 *  Format: del [r-name] [number]
 *************************************************************/
void releaseResoursesCmd(const vector<string>& argvs)
{
	int illegalShow = 0; // 不合法显示 

	switch (argvs.size())
	{
	case 2:  // de [pname]
		illegalShow = processManagerRun.destroyProcess(argvs[1]);
		break;

	default:
		cout << "[error]de 命令不合法!" << endl;
		break;
	}

	// 1 - 合法
	// 2 - 进程名不存在
	// 3 - 
	switch (illegalShow)
	{
	case 1:
		cout << "[success]进程(name:" << argvs[1] << ")撤销成功!" << endl;
		break;

	case 2:
		cout << "[error]进程名不存在!" << endl;
		break;

	case 3:
		cout << "[error]!" << endl;
		break;

	default:
		break;
	}
}

/*************************************************************
 *  Function: show ready list
 *  Format: sready
 *************************************************************/
void showReadyListCmd(const vector<string>& argvs)
{
	processManagerRun.showReadyList();
}

/*************************************************************
 *  Function: show resources table
 *  Format: sres
 *************************************************************/
void showResourcesListCmd(const vector<string>& argvs)
{
	switch (argvs.size())
	{
	case 1:
		processManagerRun.showResourcesTable();
		break;

	default:
		cout << "[error]sres 命令不合法!" << endl;
		break;
	}
}

/*************************************************************
 *  Function: 
 *  Format: to
 *************************************************************/
void timeOutCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: quit cmd
 *  Format: quit
 *************************************************************/
void quitCmd(const vector<string>& argvs)
{
	cout << "Quit!" << endl;
	quit_flag = false;
}

/*************************************************************
 *  Function: show cmd help
 *  Format: 
 *************************************************************/
void showHelpCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: show process table
 *  Format: ps
 *************************************************************/
void showProcessTable(const vector<string>& argvs)
{
	switch (argvs.size())
	{
	case 1:  
		processManagerRun.showProcessTable();
		break;

	default:
		cout << "[error]ps 命令不合法!" << endl;
		break;
	}
}

/*************************************************************
 *  Function: show process information by name
 *  Format: pr [p-name]
 *************************************************************/
void showOneProcess(const vector<string>& argvs)
{
	int illegalShow = 0; // 不合法显示 

	switch (argvs.size())
	{
	case 2:  // pr [p-name]
		
		break;

	default:
		cout << "[error]pr 命令不合法!" << endl;
		break;
	}

	// 1 - 合法
	// 2 - 进程名不存在
	// 3 - 
	switch (illegalShow)
	{
	case 1:
		cout << "[success]进程(name:" << argvs[1] << ")撤销成功!" << endl;
		break;

	case 2:
		cout << "[error]进程名不存在!" << endl;
		break;

	case 3:
		cout << "[error]!" << endl;
		break;

	default:
		break;
	}
}