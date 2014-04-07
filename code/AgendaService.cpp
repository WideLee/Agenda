/*********************************************************************
 * AgendaService.cpp  Version 1.00  <Mon August 01 13:49:54 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#include <iostream>
#include <string>
#include <list>
#include "AgendaService.h"
#include "ErrorInformation.h"

using namespace std;

AgendaService::AgendaService(){
	userManage = UserManage::getInstance();
	meetingManage = MeetingManage::getInstance();
}

/* manage user login */
User * AgendaService::userLogIn(string userName, string password){
	User *temp;
	temp = userManage->FindUserByName(userName);
	if(temp != NULL ){
		if(temp->getPassword() == password){
			return temp;
		}
		else{
			ErrorInformation::PasswordError();
			return NULL;
		}
	}
	else {
		ErrorInformation::UserNotFoundError();
		return NULL;
	}
}

/* manage user register */
bool AgendaService::userRegister(string userName, string password, string email, string phone){
	User *temp;
	temp = userManage->FindUserByName(userName);
	if(temp == NULL){
		userManage->createUser(userName, password, email, phone);
		return true;
	}
	ErrorInformation::UserNameConflictError();
	return false;
}

/* manage user delete */
bool AgendaService::deleteUser(User user){
	return userManage->deleteUser(user);
}

/* To set user list force, use in load user massage from file */
void AgendaService::setAllUser(list<User> newlist){
	userManage->setAllUsers(newlist);
}

list<User> AgendaService::listAllUser(){
	return userManage->listAllUsers();
}

bool AgendaService::createMeeting(string userName, string title, string participator, Date stime, Date etime){
	if(userManage->FindUserByName(participator) != NULL)
		return meetingManage->addMeeting(userName,participator,stime,etime,title);
	else {
		ErrorInformation::UserNotFoundError();
		return false;
	}
}

/* Find meetings */
Meeting * AgendaService::meetingQuery(string title){
	return meetingManage->queryMeetingByTitle(title);
}

list<Meeting> AgendaService::meetingQuery(string userName, Date stime, Date etime){
	return meetingManage->queryMeetingsByTime(userName,stime,etime);
}

list<Meeting> AgendaService::listAllMeetings(string userName){
	return meetingManage->listAllMeetings(userName);
}

list<Meeting> AgendaService::listAllSponsorMeetings(string userName){
	return meetingManage->listAllSponsorMeetings(userName);
}

list<Meeting> AgendaService::listallParticipateMeetings(string userName){
	return meetingManage->listAllParticipateMeetings(userName);
}
bool AgendaService::deleteMeeting(string userName, string title){
	return meetingManage->deleteMeeting(userName, title);
}

bool AgendaService::deleteAllMeetings(string userName){
	return meetingManage->deleteAllMeetings(userName);
}
/* Update User's property */
bool AgendaService::updateUserPassword(User u, string oldPassword, string newPassword){
	if(u.getPassword() != oldPassword){
		ErrorInformation::PasswordError();
		return false;
	}
	else {
		return userManage->updateUserPassword(u,newPassword);
	}
}

bool AgendaService::updateUserEmail(User u, string newEmail){
	return userManage->updateUserEmail(u, newEmail);
}

bool AgendaService::updateUserPhone(User u, string newPhone){
	return userManage->updateUserPhone(u, newPhone);
}

/* Update Meeting's property */
bool AgendaService::updateMeetingParticipator(User u, string title, string newParticipator ){
	if(userManage->FindUserByName(newParticipator) == NULL){
		ErrorInformation::UserNotFoundError();
		return false;
	}
	if(meetingQuery(title) == NULL){
		ErrorInformation::MeetingNotFoundError();
		return false;
	}
	if(meetingQuery(title)->getSponsor() != u.getName()){
		ErrorInformation::MeetingUpdateError();
		return false;
	}
	return meetingManage->updateMeetingParticipator(title, newParticipator);
}

bool AgendaService::updateMeetingStartDate( User u,string title, Date newStartDate ){
	if(meetingQuery(title) == NULL){
		ErrorInformation::MeetingNotFoundError();
		return false;
	}
	if(meetingQuery(title)->getSponsor() != u.getName()){
		ErrorInformation::MeetingUpdateError();
		return false;
	}
	return meetingManage->updateMeetingStartDate(title, newStartDate);
}

bool AgendaService::updateMeetingEndDate(User u, string title, Date newEndDate ){
	if(meetingQuery(title) == NULL){
		ErrorInformation::MeetingNotFoundError();
		return false;
	}
	if(meetingQuery(title)->getSponsor() != u.getName()){
		ErrorInformation::MeetingUpdateError();
		return false;
	}
	return meetingManage->updateMeetingEndDate(title, newEndDate);
}

void AgendaService::setAllMeeting(list<Meeting> newlist){
	meetingManage->setAllMeetings(newlist);
}
list<Meeting> AgendaService::getAllMeeting(){
	return meetingManage->getAllMeetings();
}