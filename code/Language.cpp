//====================================================================
// Language.cpp  Version 1.00  <Mon Aug 03 11:22:30 2012>
// 
// Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
// LiMingkuan is a student majoring in Software Engineering,
// from the School of Software, 
// SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
//====================================================================

#include <iostream>
#include "Language.h"

using namespace std;

int Language::language = 0;

int Language::getLanguage(){
	return language;
}

void Language::setLanguage(int newLanguage){
	language = newLanguage;
}