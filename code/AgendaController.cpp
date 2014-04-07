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
		cout << "[�û���] " ;
	else cout << "error";

	string userName, password;
	char c;
	cin >> userName ;
	if(Language::getLanguage() == 0)
		cout << "[password] : " ;
	else if(Language::getLanguage() == 1)
		cout << "[����] " ;
	else cout << "error";
	fflush(stdin);
	 /* �����û����� */
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
			cout << "[��½] ʧ�ܣ�" << endl;
		}
		else{
			cout << "[��½] �ɹ���" << endl;
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
		cout << "[ע��] [�û���] [����] [�绰����] " << endl;
		cout << "[ע��] ";
	}
	else cout << "error";
	string username, password, email, phone;
	char c;
	bool test;
	cin >> username >> email >> phone;
	if(Language::getLanguage() == 0)
		cout << "[Please enter you password]: " ;
	else if(Language::getLanguage() == 1)
		cout << "[����������]: " ;
	else cout << "error";
	fflush(stdin);
	/* �����û����� *//*
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
			cout << "[ע��] �ɹ���" << endl;
		else cout << "[����] ע��ʧ�ܣ�";
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
			cout << "[ɾ���˺�] �ɹ���" << endl;
			currentUser = NULL;
		}
		else cout << "[����] ɾ���˺�ʧ�ܣ�" << endl;
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
		cout << "[�г������û�] " << endl;
		cout << setiosflags(ios::left) << setw(10) << "����" 
			<< setiosflags(ios::left) << setw(20) << "����"
			<< setiosflags(ios::left) << setw(20) << "�绰����"
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
		cout << "[�½�����] [����] [������] [��ʼʱ��(yyyy-mm-dd/hh:mm)] [����ʱ��(yyyy-mm-dd/hh:mm)] " << endl;
		cout << "[�½�����] " ;
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
			cout << "[�½�����] �ɹ���" << endl;
		else cout << "[����] �½�����ʧ�ܣ�" << endl;
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
		cout << "[�г����л���]" << endl;
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
		cout << "[�г�����������Ļ���]" << endl;
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
		cout << "[�г�����������Ļ���]" << endl;
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
		cout << "[��ѯ����] [��������]: " << endl;
		cout << "[��ѯ����] " ;
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
			cout << setiosflags(ios::left) << setw(10) << "������"
				<< setiosflags(ios::left) << setw(15) << "������"
				<< setiosflags(ios::left) << setw(20) << "��ʼʱ��"
				<< setiosflags(ios::left) << setw(20) << "����ʱ��"
				<< endl;
			cout << setiosflags(ios::left) << setw(10) << meeting->getSponsor()
				<< setiosflags(ios::left) << setw(15) << meeting->getParticipator()
				<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting->getStartDate())
				<< setiosflags(ios::left) << setw(20) << Date::convertDateToString(meeting->getEndDate())
				<< endl;
		}
		else cout << "û���ҵ��κη��������Ļ��飡" << endl;
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
		cout << "[��ѯ����] [��ʼʱ��(yyyy-mm-dd/hh:mm)] [����ʱ��(yyyy-mm-dd/hh:mm)]: " << endl;
		cout << "[��ѯ����] " ;
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
		cout << "[�г�������ʱ��βμӵ����л���]" << endl;
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
		cout << "[ɾ������] [��������]: " << endl;
		cout << "[ɾ������] " ;
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
			cout << "[��������ɾ������] �ɹ��� " << endl;
		else cout << "[����] ɾ������ʧ�ܣ�" << endl;
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
			cout << "[ɾ�����л���] �ɹ��� " << endl;
		else cout << "[����] ɾ�����л���ʧ�ܣ�" << endl;
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
			cout << "�����ҵ��κη��������Ļ��飡\n" << endl;
		else{
			cout << setiosflags(ios::left) << setw(10) << "��������" 
				<< setiosflags(ios::left) << setw(10) << "������"
				<< setiosflags(ios::left) << setw(15) << "������"
				<< setiosflags(ios::left) << setw(20) << "��ʼʱ��"
				<< setiosflags(ios::left) << setw(20) << "����ʱ��"
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
		cout << "[�����������]�� " ;
	}
	else cout << "error";
	fflush(stdin);
	/* �����û����� *//*
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
		cout << "[������������]�� " ;
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
			cout << "[�޸�����] �ɹ��� " << endl;
		else cout << "[����] �޸�����ʧ�ܣ�" << endl;
	}
	else cout << "error";
	
}

void AgendaController::updateUserEmail(){
	if(Language::getLanguage() == 0){
		cout << "[update email] [new email address]" << endl;
		cout << "[update email] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[�޸�����] [������] " << endl;
		cout << "[�޸�����] " ;
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
			cout << "[�޸�����] �ɹ��� " << endl;
		else cout << "[����] �޸�����ʧ�ܣ�" << endl;
	}
	else cout << "error";

}

void AgendaController::updateUserPhone(){
	if(Language::getLanguage() == 0){
		cout << "[update phone] [new phone number]" << endl;
		cout << "[update phone] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[�޸ĵ绰����] [�µ绰����] " << endl;
		cout << "[�޸ĵ绰����] " ;
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
			cout << "[�޸ĵ绰����] �ɹ��� " << endl;
		else cout << "[����] �޸ĵ绰����ʧ�ܣ�" << endl;
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
		cout << "[�޸Ļ��������] [��������] [�²�����] " << endl;
		cout << "[�޸Ļ��������] " ;
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
			cout << "[�޸Ļ��������] �ɹ��� " << endl;
		else cout << "[����] �޸Ļ��������ʧ�ܣ�" << endl;
	}
	else cout << "error";

}

void AgendaController::updateMeetingStartDate(){
	if(Language::getLanguage() == 0){
		cout << "[update start time] [meeting title] [new start time]" << endl;
		cout << "[update start time] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[�޸Ļ��鿪ʼʱ��] [��������] [�¿�ʼʱ��] " << endl;
		cout << "[�޸Ļ��鿪ʼʱ��] " ;
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
			cout << "[�޸Ļ��鿪ʼʱ��] �ɹ��� " << endl;
		else cout << "[����] �޸Ļ��鿪ʼʱ��ʧ�ܣ�" << endl;
	}
	else cout << "error";

}

void AgendaController::updateMeetingEndDate(){
	if(Language::getLanguage() == 0){
		cout << "[update end time] [meeting title] [new end time]" << endl;
		cout << "[update end time] " ;
	}
	else if(Language::getLanguage() == 1){
		cout << "[�޸Ļ������ʱ��] [��������] [�½���ʱ��] " << endl;
		cout << "[�޸Ļ������ʱ��] " ;
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
			cout << "[�޸Ļ������ʱ��] �ɹ��� " << endl;
		else cout << "[����] �޸Ļ������ʱ��ʧ�ܣ�" << endl;
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
		cout << "--------------------------- ��̹���ϵͳ ---------------------------" << endl;
		cout << "���� :" << endl;
		cout << "l       - ͨ���û����������½��̹���ϵͳ" << endl;
		cout << "r       - ע��һ����̹���ϵͳ�û�" << endl;
		cout << "q       - �˳���̹���ϵͳ" << endl;
		cout << "lng     - �޸�����" << endl;
		cout << "help/h  - �����������Ϣ " << endl;
		cout << "clear/c - �����Ļ��Ϣ " << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
	else {
		cout << "--------------------------- ��̹���ϵͳ ---------------------------" << endl;
		cout << "���� :" << endl;
		cout << "o       - ע����̹���ϵͳ" << endl;
		cout << "dc      - ɾ����̹���ϵͳ�û�" << endl;
		cout << "lu      - �г�������ע���û�" << endl;
		cout << "cm      - �½�һ������" << endl;
		cout << "la      - �г�������ص����л���" << endl;
		cout << "las     - �г�����������л���" << endl;
		cout << "lap     - �г������������μӵ����л���" << endl;
		cout << "qm      - ͨ������������һ���" << endl;
		cout << "qt      - ͨ������ʱ����һ���" << endl;
		cout << "upw     - �޸��û����� " << endl;
		cout << "ue      - �޸��û�����" << endl;
		cout << "uph     - �޸��û��绰����" << endl;
		cout << "ump     - �޸Ļ��������" << endl;
		cout << "ums     - �޸Ļ��鿪ʼʱ��" << endl;
		cout << "ume     - �޸Ļ������ʱ��" << endl;
		cout << "dm      - ͨ����������ɾ������" << endl;
		cout << "da      - ɾ������������л���" << endl;
		cout << "help/h  - ���������Ϣ" << endl;
		cout << "clear/c - �����Ļ��Ϣ" << endl;
		cout << "--------------------------------------------------------------" << endl;
	}
}

/* print set system language message */
void AgendaController::print_setLanguage(){
	cout << "Please choose your language(��ѡ�����Ľ�������)" << endl;
	cout << "E ----English   C ----���� " << endl;
	cout << "Please choose(��ѡ��): " ;
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
				cout << "��̹���: ~$ ";
			else
				cout << "error" << endl;
		}
		else {
			if(Language::getLanguage() == 0)
				cout << "Agenda@" << currentUser->getName() << " : # " ;
			else if(Language::getLanguage() == 1 )
				cout << "��̹���@" << currentUser->getName() << ": # " ;
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
				cout << "�ޣ��Ҳ�������˵ʲô~~" << endl;
				cout << "���� help/h ��ø������" << endl;
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
