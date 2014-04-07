/*********************************************************************
 * MeetingManage.h  Version 1.00  <Tue Jul 31 09:15:49 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _MEETINGMANAGE_H_INCLUDE_
#define _MEETINGMANAGE_H_INCLUDE_

#include <iostream>
#include <string>
#include <list>
#include "Meeting.h"

using namespace std;

/* a class to manage all meeting */
class MeetingManage{
 private:
    static bool instanceFlag;
    static MeetingManage *instance;
    MeetingManage();

    list<Meeting> meetings;
 public:
    static MeetingManage *getInstance();
    ~MeetingManage();

	list<Meeting> getAllMeetings();
	void setAllMeetings(list<Meeting> newList);
    bool addMeeting( string sponspor, string participator, Date stime, Date etime, string title );

	bool deleteMeeting( string userName, string title );
	bool deleteAllMeetings( string userName );

	bool updateMeetingParticipator( string title, string newParticipator );
	bool updateMeetingStartDate( string title, Date newStartDate );
	bool updateMeetingEndDate( string title, Date newEndDate );

	Meeting* queryMeetingByTitle( string title );
	list<Meeting> queryMeetingsByTime( string userName, Date stime, Date etime );

    list<Meeting> listAllMeetings( string userName ) ;
	list<Meeting> listAllSponsorMeetings( string userName ) ;
	list<Meeting> listAllParticipateMeetings( string userName ) ;
};

#endif
