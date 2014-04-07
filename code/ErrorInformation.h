/*********************************************************************
* ErrorInformation.h  Version 1.00  <Mon Aug 02 16:43:36 2012>
* 
* Copyright(C) 2011-2012 LiMingkuan(11331173)  All rights reserved.
* LiMingkuan is a student majoring in Software Engineering,
* from the School of Software, 
* SUN YAT-SEN UNIVERSITY, GZ 510006, P. R. China
********************************************************************/

#ifndef _ERRORINFORMATION_H_INCLUDE_
#define _ERRORINFORMATION_H_INCLUDE_

#include <string>
#include <iostream>
#include "Language.h"

using namespace std;
/* This errorInformation contain all kind of error 
 * and it also output the error message 
 */
class ErrorInformation{
public:
	static void DateInvalidYearError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Year is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ��ݲ�����" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidMonthError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Month is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �·ݲ�����" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidDayError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Day is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ���ڲ�����" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidHourError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Hour is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] Сʱ������" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidMinuteError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Minute is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ���Ӳ�����" << endl;
		else cout << "error!" << endl;
	}
	static void StringFormatError(){
		if(Language::getLanguage() == 0)
			cout << "[error] String format error! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �ַ�����ʽ����" << endl;
		else cout << "error!" << endl;
	}
	static void UserNotFoundError(){
		if(Language::getLanguage() == 0)
			cout << "[error] User not found! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �û������ڣ�" << endl;
		else cout << "error!" << endl;
	}
	static void UserNameConflictError(){
		if(Language::getLanguage() == 0)
			cout << "[error] This user name has been register! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ���û����Ѿ���ע���ˣ�" << endl;
		else cout << "error!" << endl;
	}
	static void UserDeleteError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You have some meetings, so you can't delete your account! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �����л��飬����ɾ�������˺ţ�" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingTitleConflictError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting title conflict! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ���������ظ���" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingSameSponsorError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Sponsor and participator is the same person! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ���鷢�������������߲�����ͬһ���ˣ�" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingDateError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting date error! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ����ʱ������" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingDateConflictError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting date conflict! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ����ʱ���г�ͻ��" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingSponsorHaveNoTimeError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You have no time! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ��û�пղμ�������飡" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingParticipatorNoTimeError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting participator have no time! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ��������û�û�пղμ�������飡" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingNotFoundError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting not found ! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �Ҳ���������飡" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingCannotDeleteError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You can't delete a meeting sponsor by you! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] ������ɾ��һ������������Ļ��飡" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingDeleteAllError(){
		if(Language::getLanguage() == 0)
			cout << "[error] No meeting has been delete! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] û�л��鱻ɾ����" << endl;
		else cout << "error!" << endl;
	}
	static void PasswordError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Password error! ! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �������" << endl;
		else cout << "error!" << endl;
	}
	static void StartAndEndTimeError(){
		if(Language::getLanguage() == 0)
			cout << "[error] StartTime is later than endTime! " << endl; 
		else if(Language::getLanguage() == 1)
			cout << "[����] ��ʼʱ��Ƚ���ʱ����" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingUpdateError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You can't update property of meeting which is not sponsor by you! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[����] �����ܸ��Ĳ���������Ļ��������" << endl;
		else cout << "error!" << endl;
	}
};

#endif