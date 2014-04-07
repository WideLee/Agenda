//====================================================================
// MeetingManage.cpp  Version 1.00  <Tue Jul 31 09:26:50 2012>
// 
// Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
// LiMingkuan is a student majoring in Software Engineering,
// from the School of Software, 
// SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
//====================================================================

#include <iostream>
#include <string>
#include <list>
#include "MeetingManage.h"

using namespace std;

bool MeetingManage::instanceFlag = false;
MeetingManage *MeetingManage::instance = NULL;

MeetingManage::MeetingManage(){

}
/* MeetingManage use a singleton */
MeetingManage * MeetingManage::getInstance() {
	if( !instanceFlag ) {
		instance = new MeetingManage();
		instanceFlag = true;
	}
	return instance;
}

MeetingManage::~MeetingManage() {
	instanceFlag = false;
}

list<Meeting> MeetingManage::getAllMeetings(){
	return meetings;
}

void MeetingManage::setAllMeetings(list<Meeting> newList){
	meetings = newList;
}

/* add a new meeting */
bool MeetingManage::addMeeting(string sponspor, string participator, Date stime, Date etime, string title) {
	list<Meeting>::iterator index;
	list<Meeting> temp;
	/* Judge whether title is conflict*/
	for(index = meetings.begin(); index != meetings.end(); index++){
		if((*index).getTitle() == title){
			ErrorInformation::MeetingTitleConflictError();
			return false;
		}
	}

	/* judge whether the sponspor of the meeting and the participator is the same person */
	if(sponspor == participator){
		ErrorInformation::MeetingSameSponsorError();
		return false;
	}

	/* Judge whether the time is valid */
	if(stime > etime) {
		ErrorInformation::StartAndEndTimeError();
		return false;
	}
	if(!Date::isValid(stime) || !Date::isValid(etime)){
		return false;
	}

	/* Judge whether the sponspor have spare time in this time */
	temp = queryMeetingsByTime(sponspor, stime, etime);
	if(!temp.empty()){
		ErrorInformation::MeetingSponsorHaveNoTimeError();
		return false;
	}

	/* Judge whether the participator have spare time in this time */
	temp = queryMeetingsByTime(participator, stime, etime);
	if(!temp.empty()){
		ErrorInformation::MeetingParticipatorNoTimeError();
		return false;
	}

	/* add a new meeting */
	Meeting newMeeting(sponspor, participator, stime, etime, title);
	meetings.insert(meetings.end(), newMeeting);

	return true;
}

/* delete a meeting by title */
bool MeetingManage::deleteMeeting(string userName, string title) {
	Meeting * temp;
	list<Meeting>::iterator index;
	temp = queryMeetingByTitle(title);
	if(temp == NULL){
		ErrorInformation::MeetingNotFoundError();
		return false;
	}
	else if(temp->getSponsor() != userName){
		ErrorInformation::MeetingCannotDeleteError();
		return false;
	}
	else{
		for(index = meetings.begin(); index != meetings.end(); index++)
			if(index->getTitle() == title)
				break;
		meetings.erase(index);
		return true;
	}
}

/* Delete all meeting of the user */
bool MeetingManage::deleteAllMeetings(string userName){
	list<Meeting>::iterator index;
	bool temp = false;
	for(index = meetings.begin(); index != meetings.end();){
		if((*index).getSponsor() == userName){
			meetings.erase(index++);
			temp = true;
		}
		else
			++index;
	}
	if(temp == false){
		ErrorInformation::MeetingDeleteAllError();
	}
	return temp;
}

bool MeetingManage::updateMeetingParticipator( string title, string newParticipator ){
	/* To Do Debug ....*/
	list<Meeting>::iterator index;
	for(index = meetings.begin(); index != meetings.end(); index++){
		if((*index).getTitle() == title){
			if(!queryMeetingsByTime(newParticipator,index->getStartDate(),index->getEndDate()).empty()){
				ErrorInformation::MeetingParticipatorNoTimeError();
				return false;
			}
			(*index).setParticipator(newParticipator);
			return true;
		}
	}
	return false;
}

bool MeetingManage::updateMeetingStartDate( string title, Date newStartDate ){
	/* To Do Debug ....*/
	if(!Date::isValid(newStartDate))
		return false;
	list<Meeting>::iterator index;
	Meeting * temp;
	temp = queryMeetingByTitle(title);
	if(temp == NULL){
		ErrorInformation::MeetingNotFoundError();
		return false;
	}
	if(newStartDate > temp->getEndDate()){
		ErrorInformation::StartAndEndTimeError();
		return false;
	}
	list<Meeting> sponsor, participator;
	sponsor = listAllMeetings(temp->getSponsor());
	participator = listAllMeetings(temp->getParticipator());
	for(index = sponsor.begin(); index != sponsor.end(); index++){
		if(index->getTitle() != title){
			if(!(index->getStartDate() > temp->getEndDate() || index->getEndDate() < newStartDate)){
				ErrorInformation::MeetingSponsorHaveNoTimeError();
				return false;
			}
		}
	}
	for(index = participator.begin(); index != participator.end(); index++){
		if(index->getTitle() != title){
			if(!(index->getStartDate() > temp->getEndDate() || index->getEndDate() < newStartDate)){
				ErrorInformation::MeetingParticipatorNoTimeError();
				return false;
			}
		}
	}
	temp->setStartDate(newStartDate);
	return true;
}


bool MeetingManage::updateMeetingEndDate( string title, Date newEndDate ){
	/* To Do Debug ....*/
	if(!Date::isValid(newEndDate))
		return false;
	list<Meeting>::iterator index;
	Meeting * temp;
	temp = queryMeetingByTitle(title);
	if(temp == NULL){
		ErrorInformation::MeetingNotFoundError();
		return false;
	}
	if(newEndDate < temp->getStartDate()){
		ErrorInformation::StartAndEndTimeError();
		return false;
	}
	list<Meeting> sponsor, participator;
	sponsor = listAllMeetings(temp->getSponsor());
	participator = listAllMeetings(temp->getParticipator());
	for(index = sponsor.begin(); index != sponsor.end(); index++){
		if(index->getTitle() != title){
			if(!(index->getStartDate() > newEndDate || index->getEndDate() < temp->getStartDate())){
				ErrorInformation::MeetingSponsorHaveNoTimeError();
				return false;
			}
		}
	}
	for(index = participator.begin(); index != participator.end(); index++){
		if(index->getTitle() != title){
			if(!(index->getStartDate() > newEndDate || index->getEndDate() < temp->getStartDate())){
				ErrorInformation::MeetingParticipatorNoTimeError();
				return false;
			}
		}
	}
	temp->setEndDate(newEndDate);
	return true;
}

/* Find a meeting by title */
Meeting * MeetingManage::queryMeetingByTitle( string title ){
	list<Meeting>::iterator index;

	for(index = meetings.begin(); index != meetings.end(); index++) {
		if((*index).getTitle() == title)
			return &(*index);
	}
	return NULL;
}

/* List the user all meetings during a time */
list<Meeting> MeetingManage::queryMeetingsByTime( string userName, Date stime, Date etime ){
	list<Meeting>::iterator index;
	list<Meeting> temp;
	if(Date::isValid(stime) && Date::isValid(etime) && stime <= etime){
		for(index = meetings.begin(); index != meetings.end(); index++) {
			if(!((*index).getEndDate() < stime || (*index).getStartDate() > etime ) &&
				((*index).getSponsor() == userName || (*index).getParticipator() == userName)){
					temp.insert(temp.end(),*index);
			}
		}
	}
	return temp;
}

/* List all meeting relate to a user */
list<Meeting> MeetingManage::listAllMeetings( string userName ){
	list<Meeting>::iterator index;
	list<Meeting> temp;

	for(index = meetings.begin(); index != meetings.end(); index++){
		if((*index).getSponsor() == userName || (*index).getParticipator() == userName){
			temp.insert(temp.end(), *index);
		}
	}

	return temp;
}

/* list all meeting the user sponsor */
list<Meeting> MeetingManage::listAllSponsorMeetings( string userName ){
	list<Meeting>::iterator index;
	list<Meeting> temp;

	for(index = meetings.begin(); index != meetings.end(); index++){
		if((*index).getSponsor() == userName){
			temp.insert(temp.end(), *index);
		}
	}

	return temp;
}

/* list all meeting the user sponsor */
list<Meeting> MeetingManage::listAllParticipateMeetings( string userName ){
	list<Meeting>::iterator index;
	list<Meeting> temp;

	for(index = meetings.begin(); index != meetings.end(); index++){
		if((*index).getParticipator() == userName){
			temp.insert(temp.end(), *index);
		}
	}
	return temp;
}

