#pragma once

#include <iostream>
#include <string>
#include <list>
#include "pcb.h"

using namespace std;

extern class PCB;
extern class RCB;

class RCB
{
public:

private:
	int rid;
	string rName;
	int rStatus;
	list<PCB*> waitingList;


};