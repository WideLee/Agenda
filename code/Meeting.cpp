//====================================================================
// Meeting.cpp  Version 1.00  <Mon Jul 30 13:47:37 2012>
// 
// Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
// LiMingkuan is a student majoring in Software Engineering,
// from the School of Software, 
// SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
//====================================================================

#include<iostream>
#include <string>
#include "Date.h"
#include "Meeting.h"

using namespace std;

Meeting::Meeting(string sponsor, string participator, Date startDate, Date endDate, string title) {
    this -> sponsor = sponsor;
    this -> participator = participator;
    this -> startDate = startDate;
    this -> endDate = endDate;
    this -> title = title;
}

string Meeting::getSponsor() const {
    return sponsor;
}
void Meeting::setSponsor(string sponsor) {
    this -> sponsor = sponsor;
}

string Meeting::getParticipator() const {
    return participator;
}
void Meeting::setParticipator(string participator) {
    this -> participator = participator;
}

Date Meeting::getStartDate() const {
    return startDate;
}
void Meeting::setStartDate(Date startDate) {
    this -> startDate = startDate;
}

Date Meeting::getEndDate() const {
    return endDate;
}
void Meeting::setEndDate(Date endDate) {
    this -> endDate = endDate;
}

string Meeting::getTitle() const {
    return title;
}
void Meeting::setTitle(string participator) {
    this -> participator = participator;
}
