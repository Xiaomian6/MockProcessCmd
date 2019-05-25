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

static bool quit_flag = true;  // �رհ�ť

// ʵ����һ�����̹�����
static processManager processManagerRun;

int main()
{
	cout << "Mock Process Cmd ..." << endl;
	cout << "==================================================" << endl;
	cout << "====================" << "Test Shell" << "====================" << endl;
	cout << "==================================================" << endl;
	
	// �Զ�����initCmd����
	initCmd();

	// ���ô�����Դ����ʼ������
	processManagerRun.createResources();

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
		cout << "$shell >";
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
void initCmd()  
{
	int illegalShow = 0; // ���Ϸ���ʾ 
	illegalShow = processManagerRun.createProcess("init", 0);
	if (illegalShow == 1)
	{
		cout << "[sucess]init���̳ɹ�����!" << endl;
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
 *  Function: delete process
 *  Format: de [pname]
 *************************************************************/
void destroyProcessCmd(const vector<string>& argvs)
{
	int illegalShow = 0; // ���Ϸ���ʾ 

	switch (argvs.size())
	{
	case 2:  // de [pname]
		illegalShow = processManagerRun.destroyProcess(argvs[1]);
		break;

	default:
		cout << "[error]de ����Ϸ�!" << endl;
		break;
	}

	// 1 - �Ϸ�
	// 2 - ������������
	// 3 - 
	switch (illegalShow)
	{
	case 1:
		cout << "[success]����(name:" << argvs[1] << ")�����ɹ�!" << endl;
		break;

	case 2:
		cout << "[error]������������!" << endl;
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
	int illegalShow = 0; // ���Ϸ���ʾ 
	int requestNum = 0;

	switch (argvs.size())
	{
	case 2:  // default number Ĭ��number = 1
		illegalShow = processManagerRun.requestResources(argvs[1], 1);
		break;
	case 3:  // req R1 2
		requestNum = stoi(argvs[2]); // ��stringתΪint
		illegalShow = processManagerRun.requestResources(argvs[1], requestNum);
		break;
	default:
		cout << "[error]req ����Ϸ�!" << endl;
		break;
	}

	// 1 - �Ϸ�
	// 2 - ������Դ������
	// 3 - ���󳬹�����Դ����
	switch (illegalShow)
	{
	case 1:
		cout << "[success]��Դ(name:" << argvs[1] << ")����ɹ�!" << endl;
		break;

	case 2:
		cout << "[error]������Դ������!" << endl;
		break;

	case 3:
		cout << "[error]���󳬹�����Դ����!" << endl;
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
	int illegalShow = 0; // ���Ϸ���ʾ 

	switch (argvs.size())
	{
	case 2:  // de [pname]
		illegalShow = processManagerRun.destroyProcess(argvs[1]);
		break;

	default:
		cout << "[error]de ����Ϸ�!" << endl;
		break;
	}

	// 1 - �Ϸ�
	// 2 - ������������
	// 3 - 
	switch (illegalShow)
	{
	case 1:
		cout << "[success]����(name:" << argvs[1] << ")�����ɹ�!" << endl;
		break;

	case 2:
		cout << "[error]������������!" << endl;
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
		cout << "[error]sres ����Ϸ�!" << endl;
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
		cout << "[error]ps ����Ϸ�!" << endl;
		break;
	}
}

/*************************************************************
 *  Function: show process information by name
 *  Format: pr [p-name]
 *************************************************************/
void showOneProcess(const vector<string>& argvs)
{
	int illegalShow = 0; // ���Ϸ���ʾ 

	switch (argvs.size())
	{
	case 2:  // pr [p-name]
		
		break;

	default:
		cout << "[error]pr ����Ϸ�!" << endl;
		break;
	}

	// 1 - �Ϸ�
	// 2 - ������������
	// 3 - 
	switch (illegalShow)
	{
	case 1:
		cout << "[success]����(name:" << argvs[1] << ")�����ɹ�!" << endl;
		break;

	case 2:
		cout << "[error]������������!" << endl;
		break;

	case 3:
		cout << "[error]!" << endl;
		break;

	default:
		break;
	}
}