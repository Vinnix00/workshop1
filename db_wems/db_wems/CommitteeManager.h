#include "Committee.h"
#ifndef COMMITTEEMANAGER_H
#define COMMITTEEMANAGER_H

class CommitteeManager
{
public:
	//Committee
	bool login(Committee* committee);
	int insertCommittee(Committee* committee);
	void showAllCommittee();
	int updateCommittee(string ID, string att, string data);
    Committee* selectCommittee(string committeeID);
	Committee* selectCommitteeNO(int no);
    int deleteCommittee(string ID);
	int searchCommittee(int lastCommitteeID);


};

#endif 
