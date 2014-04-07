/*********************************************************************
 * Meeting.h  Version 1.00  <Mon Jul 30 13:41:44 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _MEETING_H_INCLUDE_
#define _MEETING_H_INCLUDE_

#include <iostream>
#include <string>
#include "Date.h"
using namespace std;
/* a class contain data of each meeting */
class Meeting {
 private:
    string sponsor;
    string participator;
    Date startDate;
    Date endDate;
    string title;

 public:
    Meeting(string sponsor, string participator, Date startDate, Date endDate, string title);

 	string getSponsor() const;
	void setSponsor(string sponsor);

	string getParticipator() const;
	void setParticipator(string participator);

	Date getStartDate() const;
	void setStartDate(Date startDate);

	Date getEndDate() const;
	void setEndDate(Date endDate);

	string getTitle() const;
	void setTitle(string title);
};

#endif

