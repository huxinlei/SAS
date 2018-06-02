// SCase.cpp: implementation of the SCase class.
// 日期：2012年3月17号
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAS.h"
#include "SCase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SCase::SCase()
{
  this->sid = -1;//默认为-1
}

//带参构造函数
SCase::SCase(int sid,CString sname,CTime sbirthday,int ssex,int shigh,int sweight,
			 CTime sstartdate,CString scomment,CString sdiagnosis,CString srecord)
{
	this->sid = sid;

	this->sname = sname;

	this->sbirthday = sbirthday;

	this->ssex = ssex;

	this->shigh = shigh;

	this->sweight = sweight;

	this->sstartdate = sstartdate;

	this->scomment = scomment;

	this->sdiagnosis = sdiagnosis;

	this->srecord = srecord;
}

//sid
int SCase::GetSid()
{
	return sid;
}

void SCase::SetSid(int sid)
{
	this->sid = sid;
}

//sname
CString SCase::GetSName()
{
	return sname;
}

void SCase::SetSName(CString sname)
{
	this->sname = sname;
}

//ssex
int SCase::GetSsex()
{
	return ssex;
}

void SCase::SetSsex(int ssex)
{
	this->ssex = ssex;
}

//shigh
int SCase::GetShigh()
{
	return shigh;
}

void SCase::SetShigh(int shigh)
{
	this->shigh = shigh;
}

//sweight
int SCase::GetSweight()
{
	return sweight;
}

void SCase::SetSweight(int sweight)
{
	this->sweight = sweight;
}
//sstartdate
CTime SCase::GetSstartdate()
{
	return sstartdate;
}

void SCase::SetSstartdate(CTime sstartdate)
{
	this->sstartdate = sstartdate;
}

//sbirthday
CTime SCase::GetSbirthday()
{
	return sbirthday;
}

void SCase::SetSbirthday(CTime sbirthday)
{
	this->sbirthday = sbirthday;
}

//scomment
CString SCase::GetScomment()
{
	return scomment;
}

void SCase::SetScomment(CString scomment)
{
	this->scomment = scomment;
}

//sdiagnosis
CString SCase::GetSdiagnosis()
{
	return sdiagnosis;
}

void SCase::SetSdiagnosis(CString sdiagnosis)
{
	this->sdiagnosis = sdiagnosis;
}

//srecord
CString SCase::GetSrecord()
{
	return srecord;
}

void SCase::SetSrecord(CString srecord)
{
	this->srecord = srecord;
}

//sage
int SCase::GetSage()
{
	CTime now = CTime::GetCurrentTime();//获得当前日期

    return now.GetYear() - this->sbirthday.GetYear();//获得年龄
}

//senddate 依赖于InitSenddate()函数，在调用它之前返回的结果无效
CTime SCase::GetSenddate()
{

	return this->senddate;//返回结束时间
}

//senddate数据的初始化
void SCase::InitSenddate()
{
	int byteCount = 0;//数据大小

    int day = 0;//天
	int hour = 0;
	int minute = 0;
	int second = 0;

    if(this->sid >= 0)
	{
   	  CFile fileOper;

	  fileOper.Open(GetFilePath(sid),CFile::modeReadWrite);//打开文件

	  byteCount = fileOper.GetLength();//获得文件长度

	  fileOper.Close();//关闭文件
	}

	if(byteCount > 0)
	{
		int totalSec = byteCount/(4*2*50);//获得总秒数

	    day = ((totalSec/60)/60)/24;
        hour = ((totalSec/60)/60)%24;
		minute = (totalSec/60)%60;
		second = totalSec%60;

		//如果时间超过二十八天就按零处理
		if(day>28)
		{
			day = 0;
			hour = 0;
			minute = 0;
			second = 0;
		}
	}

	CTime enddate(
		          this->sstartdate.GetYear(),
				  this->sstartdate.GetMonth(),
		          this->sstartdate.GetDay() + day,
		          this->sstartdate.GetHour() + hour,
		          this->sstartdate.GetMinute() + minute,
				  this->sstartdate.GetSecond() + second);//实例化

	this->senddate = enddate;//返回结束日期

	
}

//stotaltime  依赖于senddate变量的初始化
int SCase::GetStotaltime()
{
  CTimeSpan total = this->senddate - this->sstartdate;

  return total.GetTotalSeconds();//返回总时间，按秒计算
}


//获得病例数据
CString SCase::GetFilePath(int sid)
{
	char path[MAX_PATH] = {0};

	GetModuleFileName(NULL,path,MAX_PATH);//获得数据的路径

	int index;

	for(index = MAX_PATH - 1; index >= 0; index--)
	{
		if(path[index] == '\\')
		{
			break;
		}	
	}

	char realpath[MAX_PATH];

	for(int cindex = 0; cindex <= index; cindex++)
	{
		realpath[cindex] = path[cindex];
	}

	realpath[cindex] = '\0';

    CString pathS = realpath;//获得路径

	CString temp;

	temp.Format("scases_%d",sid);

	pathS += "SCases\\" + temp + ".dt";

	return pathS;//获得实际路径

}


SCase::~SCase()
{

}

//重载operator==

