// SCase.cpp: implementation of the SCase class.
// ���ڣ�2012��3��17��
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
  this->sid = -1;//Ĭ��Ϊ-1
}

//���ι��캯��
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
	CTime now = CTime::GetCurrentTime();//��õ�ǰ����

    return now.GetYear() - this->sbirthday.GetYear();//�������
}

//senddate ������InitSenddate()�������ڵ�����֮ǰ���صĽ����Ч
CTime SCase::GetSenddate()
{

	return this->senddate;//���ؽ���ʱ��
}

//senddate���ݵĳ�ʼ��
void SCase::InitSenddate()
{
	int byteCount = 0;//���ݴ�С

    int day = 0;//��
	int hour = 0;
	int minute = 0;
	int second = 0;

    if(this->sid >= 0)
	{
   	  CFile fileOper;

	  fileOper.Open(GetFilePath(sid),CFile::modeReadWrite);//���ļ�

	  byteCount = fileOper.GetLength();//����ļ�����

	  fileOper.Close();//�ر��ļ�
	}

	if(byteCount > 0)
	{
		int totalSec = byteCount/(4*2*50);//���������

	    day = ((totalSec/60)/60)/24;
        hour = ((totalSec/60)/60)%24;
		minute = (totalSec/60)%60;
		second = totalSec%60;

		//���ʱ�䳬����ʮ����Ͱ��㴦��
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
				  this->sstartdate.GetSecond() + second);//ʵ����

	this->senddate = enddate;//���ؽ�������

	
}

//stotaltime  ������senddate�����ĳ�ʼ��
int SCase::GetStotaltime()
{
  CTimeSpan total = this->senddate - this->sstartdate;

  return total.GetTotalSeconds();//������ʱ�䣬�������
}


//��ò�������
CString SCase::GetFilePath(int sid)
{
	char path[MAX_PATH] = {0};

	GetModuleFileName(NULL,path,MAX_PATH);//������ݵ�·��

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

    CString pathS = realpath;//���·��

	CString temp;

	temp.Format("scases_%d",sid);

	pathS += "SCases\\" + temp + ".dt";

	return pathS;//���ʵ��·��

}


SCase::~SCase()
{

}

//����operator==

