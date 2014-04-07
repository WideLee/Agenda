/*********************************************************************
 * Language.h  Version 1.00  <Mon Aug 03 11:17:08 2012>
 * 
 * Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
 * LiMingkuan is a student majoring in Software Engineering,
 * from the School of Software, 
 * SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
 ********************************************************************/

#ifndef _LANGUAGE_H_INCLUDE_
#define _LANGUAGE_H_INCLUDE_
/* A class to manage system language */
class Language{
private:	
	static int language;
public:
	Language(){};
	static int getLanguage();
	static void setLanguage(int newLanguage);
};

#endif