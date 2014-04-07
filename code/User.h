/*********************************************************************
 * User.h  Version 1.00  <Mon Jul 30 09:58:16 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _USER_H_INCLUDE_
#define _USER_H_INCLUDE_

#include <iostream>
#include <string>
#include <vector>
#include "Meeting.h"
#include "MeetingManage.h"

using namespace std;

/* A class contain attribute of user*/
class User {
 private:
    string name;
    string password;
    string email;
    string phone;

	MeetingManage *meetingManage;

 public:
    User(string name, string passwd, string email, string phone);

    string getName() const;
    void setName(string name);

    string getPassword() const;
    void setPassword(string passwd);

    string getEmail() const;
    void setEmail(string email);
        
    string getPhone() const;
    void setPhone(string phone);

    list<Meeting> getAllMeetings();
    list<Meeting> getAllSponsorMeetings();
	list<Meeting> getAllParticipateMeetings();
};

#endif
