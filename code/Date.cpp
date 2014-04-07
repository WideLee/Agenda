//====================================================================
// Date.cpp  Version 1.00  <Mon Jul 30 14:11:54 2012>
// 
// Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
// LiMingkuan is a student majoring in Software Engineering,
// from the School of Software, 
// SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
//====================================================================

#include <iostream>
#include <stdlib.h>
#include "Date.h"

/* The Default Constructor */
Date::Date() {
	setYear( -1 );
	setMonth( -1 );
	setDay( -1 );
	setHour( -1 );
	setMinute( -1 );
}

Date::Date( int year, int month, int day, int hour, int minute ) {
    this -> year = year;
    this -> month = month;
    this -> day = day;
    this -> hour = hour;
    this -> minute = minute;
}

int Date::getYear() const {
    return year;
}

void Date::setYear( int year ){
    this -> year = year;
}

int Date::getMonth( ) const{
    return month;
}

void Date::setMonth( int month) {
    this -> month = month;
}

int Date::getDay( ) const{
    return day;
}

void Date::setDay( int day ){
    this -> day = day;
}

int Date::getHour( ) const{
	return hour;
}

void Date::setHour( int hour ){
	this -> hour = hour;
}

int Date::getMinute( ) const{
    return minute;
}

void Date::setMinute( int minute ){
    this -> minute = minute;
}

/* Judge whether the Date is Valid */
bool Date::isValid(Date date) {
    bool isLeapYear = false;
    int maxDay = -1;

	/* Judge whether is a leap year */
    if((date.year%4==0&&date.year%100!=0)||(date.year%400==0))
        isLeapYear = true;
    if(date.year < 1000 || date.year > 9999){
		ErrorInformation::DateInvalidYearError();
        return false;
	}
    if(date.month < 1 || date.month > 12){
		ErrorInformation::DateInvalidMonthError();
        return false;
	}

    if(date.month == 1 || date.month == 3 || date.month == 5 ||
        date.month == 7 || date.month == 8 || date.month == 10 ||
        date.month == 12)
        maxDay = 31;
    else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
        maxDay = 30;
    else if (date.month == 2 && isLeapYear)
        maxDay = 29;
    else if (date.month == 2 && !isLeapYear)
        maxDay = 28;
    if(date.day > maxDay || date.day < 1){
		ErrorInformation::DateInvalidDayError();
        return false;
	}

    if(date.hour < 0 || date.hour > 23){
		ErrorInformation::DateInvalidHourError();
        return false;
	}
    if(date.minute < 0 || date.minute > 59){
		ErrorInformation::DateInvalidMinuteError();
        return false;
	}
    return true;
}

bool isNumber(char c){
	if (c >= '0' && c <= '9'){
		return true;
	}
	else return false;
}

Date Date::convertStringToDate(string ds){
    /* To do: Judge if the format of the string is valid */

    Date d;

	/* Judge whether the format of the string is valid */
	if(ds.size() == 16 && isNumber(ds[0]) && isNumber(ds[1]) && isNumber(ds[2]) 
		&& isNumber(ds[3]) && ds[4] == '-' && isNumber(ds[5]) && isNumber(ds[6]) 
		&& ds[7] == '-' && isNumber(ds[8]) && isNumber(ds[9]) && ds[10] == '/' 
		&& isNumber(ds[11]) && isNumber(ds[12]) && ds[13] == ':' && isNumber(ds[14]) 
		&& isNumber(ds[15]) ){
			d.year = (ds[0] - '0') * 1000 + (ds[1] - '0') * 100 + (ds[2] - '0') * 10 + ds[3] -'0';
			d.month = (ds[5] - '0') * 10 + ds[6] - '0';
			d.day = (ds[8] - '0') * 10 + ds[9] - '0';
			d.hour = (ds[11] - '0') * 10 + ds[12] - '0';
			d.minute = (ds[14] - '0') * 10 + ds[15] - '0';
	}
	else ErrorInformation::StringFormatError();
    return d;
}

string Date::convertDateToString(Date date){
    string temp;
    temp += date.year / 1000 + '0';
    temp += date.year / 100 - date.year / 1000 *10 + '0';
    temp += date.year / 10 - date.year / 100 * 10 + '0';
    temp += date.year % 10 + '0';
    temp += '-';
    temp += date.month / 10 + '0';
    temp += date.month % 10 + '0';
    temp += '-';
    temp += date.day / 10 + '0';
    temp += date.day % 10 + '0';
    temp += '/';
    temp += date.hour / 10 + '0';
    temp += date.hour % 10 + '0';
    temp += ':';
    temp += date.minute / 10 + '0';
    temp += date.minute % 10 + '0';
    return temp;
}

/* Overload the operation = */
Date& Date::operator=( const Date& t ){
	setYear( t.getYear() );
	setMonth( t.getMonth() );
	setDay( t.getDay() );
	setHour( t.getHour() );
	setMinute( t.getMinute() );

	return *this;
}

/* Overload the operation == */
bool Date::operator==( const Date& t ) const{
	if ( year   == t.getYear()  &&
		 month  == t.getMonth() &&
		 day    == t.getDay()   &&
		 hour   == t.getHour()  &&
		 minute == t.getMinute() )
		 return true;
	return false;
}

/* Overload the operation > */
bool Date::operator>( const Date& t ) const{
    if(this -> year > t.year)
        return true;
    else if(this -> year < t.year)
        return  false;
    else {
        if(this -> month > t.month)
            return true;
        else if(this -> month < t.month)
            return false;
        else {
            if(this -> day > t.day)
                return true;
            else if(this -> day < t.day)
                return false;
            else {
                if(this -> hour > t.hour)
                    return true;
                else if(this -> hour < t.hour)
                    return false;
                else {
                    if(this -> minute > t.minute)
                        return true;
                    else return false;
                }
            }
        }
    }
}

/* Overload the operation < */
bool Date::operator<( const Date& t ) const{
    if( (*this) > t || *this == t )
        return false;
    else return true;
}

/* Overload the operation >= */
bool Date::operator>=( const Date& t ) const{
	if( (*this) > t  || (*this) == t)
		return true;
	else
		return false;
}

/* Overload the operation <= */
bool Date::operator<=( const Date& t ) const{
	if( (*this) < t  || (*this) == t)
		return true;
	else
		return false;
}

