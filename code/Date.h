/*********************************************************************
 * Date.h  Version 1.00  <Mon Jul 30 14:11:54 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _Date_H_INCLUDE_
#define _Date_H_INCLUDE_

#include <string>
#include <iostream>
#include "ErrorInformation.h"
using namespace std;
/* This class is manage all operation relate to date */
class Date{
private:
	int year;
	int month;
	int day;
	int hour;
	int minute;
public:
	Date();
	Date( int year, int month, int day, int hour, int minute);

	int getYear( ) const;
	void setYear( int year );

	int getMonth( ) const;
	void setMonth( int month );

	int getDay( ) const;
	void setDay( int day );

	int getHour( ) const;
	void setHour( int hour );

	int getMinute( ) const;
	void setMinute( int minute );

	static bool isValid( Date date );
	static Date convertStringToDate(string dateString);
	static string convertDateToString(Date date);	

	Date& operator=( const Date& t );
	bool operator==( const Date& t ) const;
	bool operator>( const Date& t) const;
	bool operator<( const Date& t ) const;
	bool operator>=( const Date& t) const;
	bool operator<=( const Date& t ) const;
	
};

#endif
