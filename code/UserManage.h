/*********************************************************************
 * UserManage.h  Version 1.00  <Tue Jul 31 08:18:49 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _USERMANAGE_H_INCLUDE_
#define _USERMANAGE_H_INCLUDE_

#include <iostream>
#include <string>
#include <list>
#include "User.h"
#include "ErrorInformation.h"

using namespace std;

/* a class to manage all Users*/
class UserManage {
 private:
	static bool instanceFlag;
	static UserManage * instance;
	UserManage();

	list<User> users;
 public:
	static UserManage *getInstance();
	~UserManage();

    User * FindUserByName(string name);
    bool createUser(string name, string password, string email, string phone);
    bool deleteUser(User u);
    bool updateUserPassword(User u, string newPassword);
    bool updateUserEmail(User u, string newEmail);
    bool updateUserPhone(User u, string newPhone);

    list<User> listAllUsers();
	void setAllUsers(list<User> newList);
};

#endif
    
