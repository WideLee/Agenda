/*********************************************************************
 * AgendaService.h  Version 1.00  <Mon Aug 01 13:49:54 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _ANGNDASERVICE_H_INCLUDE_
#define _ANGNDASERVICE_H_INCLUDE_

#include <iostream>
#include <string>
#include <list>
#include "UserManage.h"
#include "MeetingManage.h"

using namespace std;
/* a class can combine user and system */
class AgendaService {
private:
	UserManage *userManage;
	MeetingManage *meetingManage;
public:
	AgendaService();
	User * userLogIn(string userName, string password);
	bool userRegister(string userName, string password, string email, string phone);
	bool deleteUser(User user);
	void setAllUser(list<User> newlist);
	list<User> listAllUser();

	bool createMeeting(string userName, string title, string participator, Date stime, Date etime);
	Meeting * meetingQuery(string title);
	list<Meeting> meetingQuery(string userName, Date stime, Date etime);
	list<Meeting> listAllMeetings(string userName);
	list<Meeting> listAllSponsorMeetings(string userName);
	list<Meeting> listallParticipateMeetings(string userName);
	bool deleteMeeting(string userName, string title);
	bool deleteAllMeetings(string userName);

	bool updateUserPassword(User u, string oldPassword, string newPassword);
	bool updateUserEmail(User u, string newEmail);
	bool updateUserPhone(User u, string newPhone);

	bool updateMeetingParticipator( User u, string title, string newParticipator );
	bool updateMeetingStartDate( User u, string title, Date newStartDate );
	bool updateMeetingEndDate(User u, string title, Date newEndDate );

	void setAllMeeting(list<Meeting> newlist);
	list<Meeting> getAllMeeting();

};

#endif