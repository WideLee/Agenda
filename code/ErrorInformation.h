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
			cout << "[错误] 年份不合理！" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidMonthError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Month is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 月份不合理！" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidDayError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Day is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 日期不合理！" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidHourError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Hour is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 小时不合理！" << endl;
		else cout << "error!" << endl;
	}
	static void DateInvalidMinuteError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Minute is invalid! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 分钟不合理！" << endl;
		else cout << "error!" << endl;
	}
	static void StringFormatError(){
		if(Language::getLanguage() == 0)
			cout << "[error] String format error! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 字符串格式错误！" << endl;
		else cout << "error!" << endl;
	}
	static void UserNotFoundError(){
		if(Language::getLanguage() == 0)
			cout << "[error] User not found! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 用户不存在！" << endl;
		else cout << "error!" << endl;
	}
	static void UserNameConflictError(){
		if(Language::getLanguage() == 0)
			cout << "[error] This user name has been register! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 该用户名已经被注册了！" << endl;
		else cout << "error!" << endl;
	}
	static void UserDeleteError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You have some meetings, so you can't delete your account! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 您还有会议，不能删除您的账号！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingTitleConflictError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting title conflict! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 会议主题重复！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingSameSponsorError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Sponsor and participator is the same person! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 会议发起者与会议参与者不能是同一个人！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingDateError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting date error! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 会议时间有误！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingDateConflictError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting date conflict! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 会议时间有冲突！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingSponsorHaveNoTimeError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You have no time! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 您没有空参加这个会议！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingParticipatorNoTimeError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting participator have no time! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 您邀请的用户没有空参加这个会议！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingNotFoundError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Meeting not found ! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 找不到这个会议！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingCannotDeleteError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You can't delete a meeting sponsor by you! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 您不能删除一个不是您发起的会议！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingDeleteAllError(){
		if(Language::getLanguage() == 0)
			cout << "[error] No meeting has been delete! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 没有会议被删除！" << endl;
		else cout << "error!" << endl;
	}
	static void PasswordError(){
		if(Language::getLanguage() == 0)
			cout << "[error] Password error! ! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 密码错误！" << endl;
		else cout << "error!" << endl;
	}
	static void StartAndEndTimeError(){
		if(Language::getLanguage() == 0)
			cout << "[error] StartTime is later than endTime! " << endl; 
		else if(Language::getLanguage() == 1)
			cout << "[错误] 开始时间比结束时间晚！" << endl;
		else cout << "error!" << endl;
	}
	static void MeetingUpdateError(){
		if(Language::getLanguage() == 0)
			cout << "[error] You can't update property of meeting which is not sponsor by you! " << endl;
		else if(Language::getLanguage() == 1)
			cout << "[错误] 您不能更改不是您发起的会议的属性" << endl;
		else cout << "error!" << endl;
	}
};

#endif