/*********************************************************************
* AgendController.cpp  Version 1.00  <Mon Aug 01 14:45:09 2012>
* 
* Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
* LiMingkuan is a student majoring in Software Engineering,
* from the School of Software, 
* SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
********************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <cctype>
#include <algorithm>
#include <string.h>
#include <list>
#include "AgendaController.h"
#include "Language.h"

using namespace std;
/* This function can load all data to Agenda System */
void AgendaController::inputAllDateFromFile(){
	/* load Users Data*/
	list<User> users;
	list<Meeting> meetings;
	ifstream inFile;
	inFile.open("Agenda.tmp",ios::in);
	int count_user = 0, count_meeting = 0, i;
	string username, password, email, phone;
	inFile >> count_user;
	for(i = 0;i < count_user ;i++){
		inFile >> username >> password >> email >> phone;
		User newUser(username, password, email, phone);
		users.insert(users.end(),newUser);
	}
	agendaService.setAllUser(users);
	/* load Meetings Data */
	inFile >> count_meeting;
	string title, sponsor, participator, start, end;
	for(i = 0;i < count_meeting ;i++){
		inFile >> title >> sponsor >> participator >> start >> end;
		Meeting newMeeting(sponsor, participator, Date::convertStringToDate(start), Date::convertStringToDate(end), title);
		meetings.insert(meetings.end(),newMeeting);
	}
	agendaService.setAllMeeting(meetings);

	inFile.close();
}

/* This function can save all Data to File */
void AgendaController::outputAllDataToFile(){
	list<User> users;
	list<User>::iterator user_index;
	list<Meeting> meetings;
	list<Meeting>::iterator meeting_index;
	int count_user = 0, count_meeting = 0;
	ofstream outFile;
	outFile.open("Agenda.tmp",ios::out);

	/* Saving Users Data */
	users = agendaService.listAllUser();
	count_user = users.size();
	outFile << count_user << endl;
	for(user_index = users.begin(); user_index != users.end(); user_index++){
		outFile << setiosflags(ios::left) << setw(10) << user_index->getName()
			<< setiosflags(ios::left) << setw(10) << user_index->getPassword()
			<< setiosflags(ios::left) << setw(20) << user_index->getEmail()
			<< setiosflags(ios::left) << setw(20) << user_index->getPhone()
			<< endl;
	}
	/* Saving Meetings Data */
	meetings = agendaService.getAllMeeting();
	count_meeting = meetings.size();
	outFile << count_meeting << endl;
	for(meeting_index = meetings.begin(); meeting_index != meetings.end(); meeting_index++){
		outFile << setiosflags(ios::left) << setw(10) << meeting_index->getTitle() 
			<< setiosflags(ios::left) << setw(10) << meeting_index->getSponsor()
			<< setiosflags(ios::left) << setw(15) << meeting_index->getParticipator()
			<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting_index->getStartDate())
			<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting_index->getEndDate())
			<< endl;
	}
	outFile.close();
}

/* Login a user */
void AgendaController::userLogIn(){
	if(Language::getLanguage() == 0)
		cout << "[user name] : " ;
	else if(Language::getLanguage() == 1)
		cout << "[用户名] " ;
	else cout << "error";

	string userName, password;
	char c;
	cin >> userName ;
	if(Language::getLanguage() == 0)
		cout << "[password] : " ;
	else if(Language::getLanguage() == 1)
		cout << "[密码] " ;
	else cout << "error";
	fflush(stdin);
	 /* 加密用户密码 */
    /*	while(1){
		c = getch();
		if(c == char(13)){
			cout << endl;
			break;
		}
		password += c;
		cout << "*" ;
	}
    */
    cin >> password;
	currentUser = agendaService.userLogIn(userName, password);
	if(Language::getLanguage() == 0){
		if(currentUser == NULL){
			cout << "[error] log in fail!" << endl;
		}
		else{
			cout << "[log in] succeed!" << endl;
		}
	}
	else if(Language::getLanguage() == 1){
		if(currentUser == NULL){
			cout << "[登陆] 失败！" << endl;
		}
		else{
			cout << "[登陆] 成功！" << endl;
		}
	}
	else cout << "error" << endl;
}

/* Register a user */
void AgendaController::userRegister(){
	if(Language::getLanguage() == 0){
		cout << "[register] [user name] [email] [phone]: " << endl;
		cout << "[register] ";
	}
	else if(Language::getLanguage() == 1){
		cout << "[注册] [用户名] [邮箱] [电话号码] " << endl;
		cout << "[注册] ";
	}
	else cout << "error";
	string username, password, email, phone;
	char c;
	bool test;
	cin >> username >> email >> phone;
	if(Language::getLanguage() == 0)
		cout << "[Please enter you password]: " ;
	else if(Language::getLanguage() == 1)
		cout << "[请输入密码]: " ;
	else cout << "error";
	fflush(stdin);
	/* 加密用户密码 *//*
	while(1){
		c = getch();
		if(c == char(13)){
			cout << endl;
			break;
		}
		password += c;
		cout << "*" ;
	}
                      */
    cin >> password;
	test = agendaService.userRegister(username, password, email, phone);
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[register] succeed!" << endl;
		else cout << "[error] register fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[注册] 成功！" << endl;
		else cout << "[错误] 注册失败！";
	}
	else cout << "error";
}

/* User logout */
void AgendaController::userLogOut(){
	currentUser = NULL;
}

/* Change System Language */
void AgendaController::updateLanguage(){
	print_setLanguage();
}

/* delete a user */
void AgendaController::deleteUser(){
	bool test;
	test = agendaService.deleteUser(*currentUser);
	if(Language::getLanguage() == 0){
		if(test){
			cout << "[delete agenda account] succeed!" << endl;
			currentUser = NULL;
		}
		else cout << "[error] delete agenda account fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test){
			cout << "[删除账号] 成功！" << endl;
			currentUser = NULL;
		}
		else cout << "[错误] 删除账号失败！" << endl;
	}
	else cout << "error";
} 

/*List Meeting*/
void AgendaController::listAllUsers(){
	list<User> userlist;
	list<User>::iterator index;
	userlist = agendaService.listAllUser();
	if(Language::getLanguage() == 0){
		cout << "[list all users] " << endl;
		cout << setiosflags(ios::left) << setw(10) << "name" 
			<< setiosflags(ios::left) << setw(20) << "email"
			<< setiosflags(ios::left) << setw(20) << "phone"
			<< endl;
	}
	else if(Language::getLanguage() == 1){
		cout << "[列出所有用户] " << endl;
		cout << setiosflags(ios::left) << setw(10) << "姓名" 
			<< setiosflags(ios::left) << setw(20) << "邮箱"
			<< setiosflags(ios::left) << setw(20) << "电话号码"
			<< endl;
	}
	else cout << "error";

	for(index = userlist.begin(); index != userlist.end(); index++){
		cout << setiosflags(ios::left) << setw(10) << index->getName() 
			<< setiosflags(ios::left) << setw(20) << index->getEmail()
			<< setiosflags(ios::left) << setw(20) << index->getPhone()
			<< endl;
	}
	/* Important to test whether is true */
}

void AgendaController::createMeeting(){
	if(Language::getLanguage() == 0){
		cout << "[creat meeting] [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh/mm)]: " << endl;
		cout << "[creat meeting] ";
	}
	else if(Language::getLanguage() == 1){
		cout << "[新建会议] [主题] [参与者] [开始时间(yyyy-mm-dd/hh:mm)] [结束时间(yyyy-mm-dd/hh:mm)] " << endl;
		cout << "[新建会议] " ;
	}
	else cout << "error";

	string title, participator, start, end;
	cin >> title >> participator >> start >> end;
	bool test;
	test = agendaService.createMeeting(currentUser->getName(),title, participator, Date::convertStringToDate(start), Date::convertStringToDate(end));
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[creat meeting] succeed!" << endl;
		else cout << "[error] creat meeting fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[新建会议] 成功！" << endl;
		else cout << "[错误] 新建会议失败！" << endl;
	}
	else cout << "error";
}

void AgendaController::listAllMeetings(){
	list<Meeting> meetinglist;
	meetinglist = agendaService.listAllMeetings(currentUser->getName());
	if(Language::getLanguage() == 0){
		cout << "[list all meeting]" << endl;
	}
	else if(Language::getLanguage() == 1){
		cout << "[列出所有会议]" << endl;
	}
	else cout << "error";

	printMeetings(meetinglist);
	/* Important to test whether is true */
}

void AgendaController::listAllSponsorMeetings(){
	list<Meeting> meetinglist;
	meetinglist = agendaService.listAllSponsorMeetings(currentUser->getName());
	if(Language::getLanguage() == 0){
		cout << "[list all sponsor meeting]" << endl;
	}
	else if(Language::getLanguage() == 1){
		cout << "[列出所有您发起的会议]" << endl;
	}
	else cout << "error";

	printMeetings(meetinglist);
}

void AgendaController::listAllParticipateMeetings(){
	list<Meeting> meetinglist;
	meetinglist = agendaService.listallParticipateMeetings(currentUser->getName());
	if(Language::getLanguage() == 0){
		cout << "[list all participate meeting]" << endl;
	}
	else if(Language::getLanguage() == 1){
		cout << "[列出所有您参与的会议]" << endl;
	}
	else cout << "error";

	printMeetings(meetinglist);
}

/* Find Meeting */

void AgendaController::queryMeetingByTitle(){
	if(Language::getLanguage() == 0){
		cout << "[query meeting] [title]: " << endl;
		cout << "[query meeting]: " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[查询会议] [会议主题]: " << endl;
		cout << "[查询会议] " ;
	}
	else cout << "error";
	string title;
	cin >> title;
	Meeting * meeting;
	meeting = agendaService.meetingQuery(title);
	if(Language::getLanguage() == 0){
		if(meeting != NULL && ( meeting->getSponsor() == currentUser->getName() || meeting->getParticipator() == currentUser->getName())){
			cout << setiosflags(ios::left) << setw(10) << "sponsor"
				<< setiosflags(ios::left) << setw(15) << "participator"
				<< setiosflags(ios::left) << setw(20) << "start time"
				<< setiosflags(ios::left) << setw(20) << "end time"
				<< endl;
			cout << setiosflags(ios::left) << setw(10) << meeting->getSponsor()
				<< setiosflags(ios::left) << setw(15) << meeting->getParticipator()
				<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting->getStartDate())
				<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting->getEndDate())
				<< endl;
		}
		else cout << "Can't Found any meeting!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(meeting != NULL && ( meeting->getSponsor() == currentUser->getName() || meeting->getParticipator() == currentUser->getName())){
			cout << setiosflags(ios::left) << setw(10) << "发起者"
				<< setiosflags(ios::left) << setw(15) << "参与者"
				<< setiosflags(ios::left) << setw(20) << "开始时间"
				<< setiosflags(ios::left) << setw(20) << "结束时间"
				<< endl;
			cout << setiosflags(ios::left) << setw(10) << meeting->getSponsor()
				<< setiosflags(ios::left) << setw(15) << meeting->getParticipator()
				<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting->getStartDate())
				<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting->getEndDate())
				<< endl;
		}
		else cout << "没能找到任何符合条件的会议！" << endl;
	}
	else cout << "error";
	/* Important to test whether is true */
}

void AgendaController::queryMeetingByTimeInterval(){
	if(Language::getLanguage() == 0){
		cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]: " << endl;
		cout << "[query meetings]: " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[查询会议] [开始时间(yyyy-mm-dd/hh:mm)] [结束时间(yyyy-mm-dd/hh:mm)]: " << endl;
		cout << "[查询会议] " ;
	}
	else cout << "error";
	string stime, etime;
	cin >> stime >> etime ;
	list<Meeting> meetinglist;
	meetinglist = agendaService.meetingQuery(currentUser->getName(),Date::convertStringToDate(stime),Date::convertStringToDate(etime));
	cout << "[query meetings]" << endl;
	if(Language::getLanguage() == 0){
		cout << "[query meetings]" << endl;
	}
	else if(Language::getLanguage() == 1){
		cout << "[列出您在这时间段参加的所有会议]" << endl;
	}
	else cout << "error";

	printMeetings(meetinglist);
}

/* delete Meeting */
void AgendaController::deleteMeetingByTitle(){
	if(Language::getLanguage() == 0){
		cout << "[delete meeting] [title]: " << endl;
		cout << "[delete meeting]: " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[删除会议] [会议主题]: " << endl;
		cout << "[删除会议] " ;
	}
	else cout << "error";

	string title;
	cin >> title;
	bool test;
	test = agendaService.deleteMeeting(currentUser->getName(),title);
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[delete meeting by title] succeed! " << endl;
		else cout << "[error] delete meeting fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[根据主题删除会议] 成功！ " << endl;
		else cout << "[错误] 删除会议失败！" << endl;
	}
	else cout << "error";
}

void AgendaController::deleteAllMeetings(){
	bool test;
	test = agendaService.deleteAllMeetings(currentUser->getName());
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[delete all meetings] succeed!" << endl;
		else cout << "[error] delete all meetings fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[删除所有会议] 成功！ " << endl;
		else cout << "[错误] 删除所有会议失败！" << endl;
	}
	else cout << "error";
}

/* print a list of Meetings */
void AgendaController::printMeetings(list<Meeting> meetings){
	list<Meeting>::iterator index;
	if(Language::getLanguage() == 0){
		if(meetings.empty())
			cout << "Can't Found Any Meeting!\n" << endl;
		else{
			cout << setiosflags(ios::left) << setw(10) << "title" 
				<< setiosflags(ios::left) << setw(10) << "sponsor"
				<< setiosflags(ios::left) << setw(15) << "participator"
				<< setiosflags(ios::left) << setw(20) << "start time"
				<< setiosflags(ios::left) << setw(20) << "end time"
				<< endl;
			for(index = meetings.begin(); index != meetings.end(); index++){
				cout << setiosflags(ios::left) << setw(10) << index->getTitle() 
					<< setiosflags(ios::left) << setw(10) << index->getSponsor()
					<< setiosflags(ios::left) << setw(15) << index->getParticipator()
					<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(index->getStartDate())
					<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(index->getEndDate())
					<< endl;
			}
		}
	}
	else if(Language::getLanguage() == 1){
		if(meetings.empty())
			cout << "不能找到任何符合条件的会议！\n" << endl;
		else{
			cout << setiosflags(ios::left) << setw(10) << "会议主题" 
				<< setiosflags(ios::left) << setw(10) << "发起者"
				<< setiosflags(ios::left) << setw(15) << "参与者"
				<< setiosflags(ios::left) << setw(20) << "开始时间"
				<< setiosflags(ios::left) << setw(20) << "结束时间"
				<< endl;
			for(index = meetings.begin(); index != meetings.end(); index++){
				cout << setiosflags(ios::left) << setw(10) << index->getTitle() 
					<< setiosflags(ios::left) << setw(10) << index->getSponsor()
					<< setiosflags(ios::left) << setw(15) << index->getParticipator()
					<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(index->getStartDate())
					<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(index->getEndDate())
					<< endl;
			}
		}
	}
	else cout << "error";

}

/* Update user's property */
void AgendaController::updateUserPassword(){
	string oldPassword, newPassword;
	char c;
	if(Language::getLanguage() == 0)
		cout << "[Please enter oldPassword]: ";
	else if(Language::getLanguage() == 1){
		cout << "[请输入旧密码]： " ;
	}
	else cout << "error";
	fflush(stdin);
	/* 加密用户密码 *//*
	while(1){
		c = getch();
		if(c == char(13)){
			cout << endl;
			break;
		}
		oldPassword += c;
		cout << "*" ;
        }*/
    cin >> oldPassword;

	if(Language::getLanguage() == 0)
		cout << "[Please enter newPassword]: ";
	else if(Language::getLanguage() == 1){
		cout << "[请输入新密码]： " ;
	}
	else cout << "error";
	fflush(stdin);/*
	while(1){
		c = getch();
		if(c == char(13)){
			cout << endl;
			break;
		}
		newPassword += c;
		cout << "*" ;
	}
                  */
    cin >> newPassword;

	bool test;
	test = agendaService.updateUserPassword(*currentUser,oldPassword , newPassword);
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[update password] succeed!" << endl;
		else cout << "[error] update password fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[修改密码] 成功！ " << endl;
		else cout << "[错误] 修改密码失败！" << endl;
	}
	else cout << "error";
	
}

void AgendaController::updateUserEmail(){
	if(Language::getLanguage() == 0){
		cout << "[update email] [new email address]" << endl;
		cout << "[update email] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[修改邮箱] [新邮箱] " << endl;
		cout << "[修改邮箱] " ;
	}
	else cout << "error";

	string newEmail;
	cin >> newEmail;
	bool test;
	test = agendaService.updateUserEmail(*currentUser,newEmail);
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[update email] succeed!" << endl;
		else cout << "[error] update email fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[修改邮箱] 成功！ " << endl;
		else cout << "[错误] 修改邮箱失败！" << endl;
	}
	else cout << "error";

}

void AgendaController::updateUserPhone(){
	if(Language::getLanguage() == 0){
		cout << "[update phone] [new phone number]" << endl;
		cout << "[update phone] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[修改电话号码] [新电话号码] " << endl;
		cout << "[修改电话号码] " ;
	}
	else cout << "error";


	string newPhone;
	cin >> newPhone;
	bool test;
	test = agendaService.updateUserPhone(*currentUser,newPhone);
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[update phone] succeed!" << endl;
		else cout << "[error] update phone fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[修改电话号码] 成功！ " << endl;
		else cout << "[错误] 修改电话号码失败！" << endl;
	}
	else cout << "error";

}

/* Update property of meeting*/
void AgendaController::updateMeetingParticipator(){
	if(Language::getLanguage() == 0){
		cout << "[update participator] [meeting title] [new participator] " << endl;
		cout << "[update participator] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[修改会议参与者] [会议主题] [新参与者] " << endl;
		cout << "[修改会议参与者] " ;
	}
	else cout << "error";

	string title, newParticipator;
	cin >> title >> newParticipator;
	bool test;
	test = agendaService.updateMeetingParticipator(*currentUser, title, newParticipator);
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[update participator] succeed!" << endl;
		else cout << "[error] update participator fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[修改会议参与者] 成功！ " << endl;
		else cout << "[错误] 修改会议参与者失败！" << endl;
	}
	else cout << "error";

}

void AgendaController::updateMeetingStartDate(){
	if(Language::getLanguage() == 0){
		cout << "[update start time] [meeting title] [new start time]" << endl;
		cout << "[update start time] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[修改会议开始时间] [会议主题] [新开始时间] " << endl;
		cout << "[修改会议开始时间] " ;
	}
	else cout << "error";

	string title, newStime;
	cin >> title >> newStime;
	bool test;
	test = agendaService.updateMeetingStartDate(*currentUser, title, Date::convertStringToDate(newStime));
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[update start time] succeed!" << endl;
		else cout << "[error] update start time fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[修改会议开始时间] 成功！ " << endl;
		else cout << "[错误] 修改会议开始时间失败！" << endl;
	}
	else cout << "error";

}

void AgendaController::updateMeetingEndDate(){
	if(Language::getLanguage() == 0){
		cout << "[update end time] [meeting title] [new end time]" << endl;
		cout << "[update end time] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[修改会议结束时间] [会议主题] [新结束时间] " << endl;
		cout << "[修改会议结束时间] " ;
	}
	else cout << "error";

	string title, newEtime;
	cin >> title >> newEtime;
	bool test;
	test = agendaService.updateMeetingEndDate(*currentUser, title, Date::convertStringToDate(newEtime));
	if(Language::getLanguage() == 0){
		if(test)
			cout << "[update end time] succeed!" << endl;
		else cout << "[error] update end time fail!" << endl;
	}
	else if(Language::getLanguage() == 1){
		if(test)
			cout << "[修改会议结束时间] 成功！ " << endl;
		else cout << "[错误] 修改会议结束时间失败！" << endl;
	}
	else cout << "error";

}

/* print help message in English */
void AgendaController::print_English(){
	if(currentUser == NULL){
		cout << "--------------------------- Agenda ---------------------------" << endl;
		cout << "Action :" << endl;
		cout << "l       - log in Agenda by user name and password" << endl;
		cout << "r       - register an Agenda account" << endl;
		cout << "q       - quit Agenda" << endl;
		cout << "lng     - change language" << endl;
		cout << "help/h  - output this help message " << endl;
		cout << "clear/c - clear all screen " << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
	else {
		cout << "--------------------------- Agenda ---------------------------" << endl;
		cout << "Action :" << endl;
		cout << "o       - log out Agenda" << endl;
		cout << "dc      - delete Agenda account" << endl;
		cout << "lu      - list all Agenda user" << endl;
		cout << "cm      - creat a meeting" << endl;
		cout << "la      - list all meetings" << endl;
		cout << "las     - list all sponsor meetings" << endl;
		cout << "lap     - list all participate meetings" << endl;
		cout << "qm      - query meeting by title" << endl;
		cout << "qt      - query meeting by time interval" << endl;
		cout << "upw     - update user password " << endl;
		cout << "ue      - update user email" << endl;
		cout << "uph     - update user phone number " << endl;
		cout << "ump     - update meeting participator" << endl;
		cout << "ums     - update meeting start time" << endl;
		cout << "ume     - update meeting end time" << endl;
		cout << "dm      - delete meeting by title" << endl;
		cout << "da      - delete all meetings" << endl;
		cout << "help/h  - output this help message " << endl;
		cout << "clear/c - clear all screen " << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
}

/* print help information in Chinese */
void AgendaController::print_Chinese(){
	if(currentUser == NULL){
		cout << "--------------------------- 议程管理系统 ---------------------------" << endl;
		cout << "操作 :" << endl;
		cout << "l       - 通过用户名和密码登陆议程管理系统" << endl;
		cout << "r       - 注册一个议程管理系统用户" << endl;
		cout << "q       - 退出议程管理系统" << endl;
		cout << "lng     - 修改语言" << endl;
		cout << "help/h  - 输出本帮助信息 " << endl;
		cout << "clear/c - 清空屏幕信息 " << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
	else {
		cout << "--------------------------- 议程管理系统 ---------------------------" << endl;
		cout << "操作 :" << endl;
		cout << "o       - 注销议程管理系统" << endl;
		cout << "dc      - 删除议程管理系统用户" << endl;
		cout << "lu      - 列出所有已注册用户" << endl;
		cout << "cm      - 新建一个会议" << endl;
		cout << "la      - 列出与您相关的所有会议" << endl;
		cout << "las     - 列出您发起的所有会议" << endl;
		cout << "lap     - 列出别人邀请您参加的所有会议" << endl;
		cout << "qm      - 通过会议主题查找会议" << endl;
		cout << "qt      - 通过会议时间查找会议" << endl;
		cout << "upw     - 修改用户密码 " << endl;
		cout << "ue      - 修改用户邮箱" << endl;
		cout << "uph     - 修改用户电话号码" << endl;
		cout << "ump     - 修改会议参与者" << endl;
		cout << "ums     - 修改会议开始时间" << endl;
		cout << "ume     - 修改会议结束时间" << endl;
		cout << "dm      - 通过会议主题删除会议" << endl;
		cout << "da      - 删除您发起的所有会议" << endl;
		cout << "help/h  - 输出帮助信息" << endl;
		cout << "clear/c - 清空屏幕信息" << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
}

/* print set system language message */
void AgendaController::print_setLanguage(){
	cout << "Please choose your language(请选择您的界面语言)" << endl;
	cout << "E ----English   C ----中文 " << endl;
	cout << "Please choose(请选择): " ;
	char language;
	cin >> language;
	if(language == 'c' || language == 'C')
		Language::setLanguage(1);
	else 
		Language::setLanguage(0);
	if(Language::getLanguage() == 0)
		print_English();
	else if(Language::getLanguage() == 1 )
		print_Chinese();
	else
		cout << "error" << endl;
}

AgendaController::AgendaController(){
	currentUser = NULL;
}

void AgendaController::getOperation(){
	string statement;

	inputAllDateFromFile();
	print_setLanguage();
	while(1){
		if(currentUser == NULL){
			if(Language::getLanguage() == 0)
				cout << "Agenda : ~$ " ;
			else if(Language::getLanguage() == 1 )
				cout << "议程管理: ~$ ";
			else
				cout << "error" << endl;
		}
		else {
			if(Language::getLanguage() == 0)
				cout << "Agenda@" << currentUser->getName() << " : # " ;
			else if(Language::getLanguage() == 1 )
				cout << "议程管理@" << currentUser->getName() << ": # " ;
			else
				cout << "error" << endl;
		}
		fflush(stdin);
		/* input a order to execute */
		cin >> statement;
		if(statement == "h" || statement == "help"){
			if(Language::getLanguage() == 0)
				print_English();
			else if(Language::getLanguage() == 1 )
				print_Chinese();
			else
				cout << "error" << endl;
			continue;
		}
		if(statement == "c" || statement == "clear"){
			continue;
		}
		if(statement == "q" && currentUser == NULL)
			break;
		if(!executeOperation(statement)){
			if(Language::getLanguage() == 0){
				cout << "Opps, I don't know what you said~~ " << endl;
				cout << "Press help/h to get more information " << endl;
			}
			else if(Language::getLanguage() == 1 ){
				cout << "噢，我不懂您在说什么~~" << endl;
				cout << "输入 help/h 获得更多帮助" << endl;
			}
			else
				cout << "error" << endl;
		}
	}
	outputAllDataToFile();
}

/* interpret a order and execute it */
bool AgendaController::executeOperation( string op ){
	bool temp = true;
	if(currentUser == NULL){
		if(op == "l")
			userLogIn();
		else if(op == "r")
			userRegister();
		else if(op == "q")
			return true;
		else if(op == "lng")
			updateLanguage();
		else
			temp = false;
	}
	else {
		if(op == "o")
			userLogOut();
		else if(op == "dc")
			deleteUser();
		else if(op == "lu")
			listAllUsers();
		else if(op == "cm")
			createMeeting();
		else if(op == "la")
			listAllMeetings();
		else if(op == "las")
			listAllSponsorMeetings();
		else if(op == "lap")
			listAllParticipateMeetings();
		else if(op == "qm")
			queryMeetingByTitle();
		else if(op == "qt")
			queryMeetingByTimeInterval();
		else if(op == "upw")
			updateUserPassword();
		else if(op == "ue")
			updateUserEmail();
		else if(op == "uph")
			updateUserPhone();
		else if (op == "ump")
			updateMeetingParticipator();
		else if(op == "ums")
			updateMeetingStartDate();
		else if(op == "ume")
			updateMeetingEndDate();
		else if(op == "dm")
			deleteMeetingByTitle();
		else if(op == "da")
			deleteAllMeetings();
		else temp = false;
	}
	return temp;
}
