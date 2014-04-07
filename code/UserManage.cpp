//====================================================================
// UserManage.cpp  Version 1.00  <Tue Jul 31 08:28:27 2012>
// 
// Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
// LiMingkuan is a student majoring in Software Engineering,
// from the School of Software, 
// SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
//====================================================================
#include <iostream>
#include <string>
#include <list>
#include "UserManage.h"
#include "User.h"

using namespace std;

bool UserManage::instanceFlag = false;
UserManage * UserManage::instance = NULL;

UserManage::UserManage() {

}
/* UserManage Use a Singleton */
UserManage * UserManage::getInstance() {
	if( !instanceFlag ) {
		instance = new UserManage();
		instanceFlag = true;
	}
	return instance;
}

UserManage::~UserManage(){
	instanceFlag = false;
}

/* Find a User by name */
User * UserManage::FindUserByName(string name) {
    list<User>::iterator index, end;
    end = users.end();
    for(index = users.begin(); index != end; index++) {
        if((*index).getName() == name)
            return &(*index);
    }
    return NULL;
}

/* creat a new User */
bool UserManage::createUser(string name, string password, string email, string phone) {
    if(FindUserByName(name) != NULL){
		ErrorInformation::UserNameConflictError();
        return false;
	}
    User newUser(name, password, email, phone);
    users.insert(users.end(), newUser);
    return true;
}

/* delete a user */
bool UserManage::deleteUser(User u){
    list<User>::iterator index;
    for(index = users.begin(); index != users.end(); index++) {
        if((*index).getName() == u.getName()) {
			if(!u.getAllMeetings().empty()){
				ErrorInformation::UserDeleteError();
				return false;
			}
            users.erase(index);
            return true;
        }
    }
    return false;
}

bool UserManage::updateUserPassword(User u, string newPassword) {
    list<User>::iterator index;
    for(index = users.begin(); index != users.end(); index++){
        if((*index).getName() == u.getName()) {
            (*index).setPassword( newPassword );
            return true;
        }
    }
    return false;
}

bool UserManage::updateUserEmail(User u, string newEmail) {
    list<User>::iterator index;
    for(index = users.begin(); index != users.end(); index++){
        if((*index).getName() == u.getName()) {
            (*index).setEmail( newEmail );
            return true;
        }
    }
    return false;
}

bool UserManage::updateUserPhone(User u, string newPhone) {
    list<User>::iterator index;
    for(index = users.begin(); index != users.end(); index++){
        if((*index).getName() == u.getName()) {
            (*index).setPhone( newPhone );
            return true;
        }
    }
    return false;
}
list<User> UserManage::listAllUsers() {
    return users;
}

void UserManage::setAllUsers(list<User> newlist){
	users = newlist;
}
