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

static bool quit_flag = true;  // �رհ�ť

// ʵ����һ�����̹�����
static processManager processManagerRun;

int main()
{
	cout << "Mock Process Cmd ..." << endl;
	cout << "==================================================" << endl;
	cout << "====================" << "Test Shell" << "====================" << endl;
	cout << "==================================================" << endl;
	
	// �Զ�����initCmd����todo

	while (quit_flag)
	{
		vector<string> argvs;  // �ֲ��������Զ����

		inputCmd(argvs);   // ���봦��

		try {
			mapCmd.at(argvs[0])(argvs);
		}
		catch (const exception&) {
			cout << "���\"" << argvs[0] << "\" ���Ϸ�!" << endl;
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
		split(input, ' ' , argvs);   // �Զ��� String: split���� λ��splitTool.h

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
 *  Function: init����
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
	int illegalShow = 0; // ���Ϸ���ʾ 
	int priority = 0;
	
	switch (argvs.size())
	{
	case 2:  // default priority Ĭ��USER���ȼ�
		cout << "[prompt]ȱʡ���ȼ�,Ĭ��USER���ȼ�" << endl;
		illegalShow = processManagerRun.createProcess(argvs[1], 1);
		break;
	case 3:  // 

		priority = stoi(argvs[2]); // ��stringתΪint
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
		cout << "[error]cr ����Ϸ�!" << endl;
		break;
	}

	// 1 - �Ϸ�
	// 2 - �������ظ�
	// 3 - ���ȼ����Ϸ�
	switch (illegalShow)
	{
	case 1:
		cout << "[success]����(name:"<< argvs[1] <<")�����ɹ�!" << endl;
		break;

	case 2:
		cout << "[error]�������ظ�!" << endl;
		break;

	case 3:
		cout << "[error]���ȼ����Ϸ�!" << endl;
		break;

	default:
		break;
	}
}

/*************************************************************
 *  Function: init����
 *  Format: init
 *************************************************************/
void destroyProcessCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init����
 *  Format: init
 *************************************************************/
void requestResourcesCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init����
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
 *  Function: init����
 *  Format: init
 *************************************************************/
void showResourcesListCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init����
 *  Format: init
 *************************************************************/
void timeOutCmd(const vector<string>& argvs)
{

}

/*************************************************************
 *  Function: init����
 *  Format: init
 *************************************************************/
void quitCmd(const vector<string>& argvs)
{
	cout << "Quit!" << endl;
	quit_flag = false;
}

/*************************************************************
 *  Function: init����
 *  Format: init
 *************************************************************/
void showHelpCmd(const vector<string>& argvs)
{

}