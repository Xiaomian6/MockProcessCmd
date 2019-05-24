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
void initCmd(const vector<string>& argvs);
void createProcessCmd(const vector<string>& argvs);
void destroyProcessCmd(const vector<string>& argvs);
void requestResourcesCmd(const vector<string>& argvs);
void releaseResoursesCmd(const vector<string>& argvs);
void showReadyListCmd(const vector<string>& argvs);
void showResourcesListCmd(const vector<string>& argvs);
void timeOutCmd(const vector<string>& argvs);
void quitCmd(const vector<string>& argvs);
void showHelpCmd(const vector<string>& argvs);

static const map<string, void(*)(const vector<string> &)> mapCmd = {
	{ "init"    , initCmd               },   //
	{ "cr"      , createProcessCmd      },   //
	{ "de"      , destroyProcessCmd     },   //
	{ "req"     , requestResourcesCmd   },   //
	{ "rel"     , releaseResoursesCmd   },   //
	{ "sready"  , showReadyListCmd      },   //
	{ "sres"    , showResourcesListCmd  },   //
	{ "to"      , timeOutCmd            },   //
	{ "quit"    , quitCmd               }    //
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
	
	// 自动调用initCmd（）todo

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
		cout << "shell$ >";
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
void initCmd(const vector<string>& argvs)  
{
	
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
 *  Function: init进程
 *  Format: init
 *************************************************************/
void destroyProcessCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init进程
 *  Format: init
 *************************************************************/
void requestResourcesCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init进程
 *  Format: init
 *************************************************************/
void releaseResoursesCmd(const vector<string>& argvs)
{

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
 *  Function: init进程
 *  Format: init
 *************************************************************/
void showResourcesListCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init进程
 *  Format: init
 *************************************************************/
void timeOutCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init进程
 *  Format: init
 *************************************************************/
void quitCmd(const vector<string>& argvs)
{
	cout << "Quit!" << endl;
	quit_flag = false;
}

/*************************************************************
 *  Function: init进程
 *  Format: init
 *************************************************************/
void showHelpCmd(const vector<string>& argvs)
{

}