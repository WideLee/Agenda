/*********************************************************************
 * AgendaController.h  Version 1.00  <Mon Aug 01 14:43:36 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _AGENDACONTROLLER_H_INCLUDE_
#define _AGENDACONTROLLER_H_INCLUDE_

#include <iostream>
#include "AgendaService.h"

using namespace std;
/* a class can control all operation of user */
class AgendaController {
private:
	User *currentUser;
	AgendaService agendaService;

	bool executeOperation( string op );

	void userLogIn( );
	void userRegister( );
	void userLogOut( );
	void updateLanguage();
	void deleteUser( );
	void listAllUsers( );
	
	void createMeeting( );
	void listAllMeetings( );
	void listAllSponsorMeetings( );
	void listAllParticipateMeetings( );
	void queryMeetingByTitle( );
	void queryMeetingByTimeInterval( );
	void deleteMeetingByTitle( );
	void deleteAllMeetings( );

	void printMeetings( list<Meeting> meetings );

	void updateUserPassword();
	void updateUserEmail();
	void updateUserPhone();

	void updateMeetingParticipator();
	void updateMeetingStartDate();
	void updateMeetingEndDate();

public:
	AgendaController( );
	void getOperation( );
	void print_English();
	void print_Chinese();
	void print_setLanguage();
	void inputAllDateFromFile();
	void outputAllDataToFile();
};

#endif
