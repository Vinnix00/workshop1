#include "Webinar.h"
#ifndef WEBINARMANAGER_H
#define WEBINARMANAGER_H

class WebinarManager
{
public:
	int insertWebinar(Webinar* webinar);
	void showAllWebinar();
	int searchWebinar(int lastWebinarID);
	Webinar* selectWebinar(string webinarID);
	Webinar* selectWebinarNO(int no);
	int deleteWebinar(string ID);
	int updateWebinar(string ID, string att, string data);



};

#endif 
