//====================================================================
// User.cpp  Version 1.00  <Mon Jul 30 10:32:35 2012>
// 
// Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
// LiMingkuan is a student majoring in Software Engineering,
// from the School of Software, 
// SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
//====================================================================

#include <iostream>
#include <string>
#include <vector>
#include "Meeting.h"
#include "MeetingManage.h"
#include "User.h"

using namespace std;

User::User(string name, string password, string email, string phone) {
    this -> name = name;
    this -> password = password;
    this -> email = email;
    this -> phone = phone;

	meetingManage = MeetingManage::getInstance();
}

string User::getName() const {
    return name;
}
void User::setName(string n) {
    name = n;
}

string User::getPassword() const {
    return password;
}
void User::setPassword(string passwd) {
    password = passwd;
}

string User::getEmail() const {
    return email;
}
void User::setEmail(string email) {
    this -> email = email;
}
        
string User::getPhone() const {
    return phone;
}
void User::setPhone(string phone) {
    this -> phone = phone;
}

/* List all meeting the user sponsor or participate */
list<Meeting> User::getAllMeetings(){
	return (*meetingManage).listAllMeetings(name);
}

/* List all meeting the user sponsor */
list<Meeting> User::getAllSponsorMeetings(){
	return (*meetingManage).listAllSponsorMeetings(name);
}

/* List all meeting the user participate */
list<Meeting> User::getAllParticipateMeetings(){
	return (*meetingManage).listAllParticipateMeetings(name);
}

