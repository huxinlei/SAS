// SCase.h: interface for the SCase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCASE_H__D31A9ED7_2951_41C4_A3C3_855FC6419BCB__INCLUDED_)
#define AFX_SCASE_H__D31A9ED7_2951_41C4_A3C3_855FC6419BCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SCase
{
public:
	SCase();

	SCase(int sid,CString sname,CTime sbirthday,int ssex,int shigh,
		int sweight,CTime sstartdate,CString scomment,CString sdiagnosis,CString srecord);//带参构造函数
    

	//sid
	int GetSid();

	void SetSid(int sid);


	//sname
	CString GetSName();

	void SetSName(CString sname);
    
	//ssex 0为未填，1为男，2为女
	int GetSsex();

	void SetSsex(int ssex);

	//shigh
	int GetShigh();

	void SetShigh(int shigh);

	//sweight
	int GetSweight();

	void SetSweight(int sweight);

	//sstardate
	CTime GetSstartdate();

	void SetSstartdate(CTime sstartdate);

	//scomment
	CString GetScomment();

	void SetScomment(CString scomment);

	//获得年龄方法
    int GetSage();

	//获得结束日期时间
	CTime GetSenddate();

	//获得记录总时间，依赖GetSenddate方法
	int GetStotaltime();

	//诊断医生
	CString GetSdiagnosis();

	void SetSdiagnosis(CString sdiagnosis);

	//记录医生
	CString GetSrecord();

	void SetSrecord(CString srecord);

	//出生日期
    CTime GetSbirthday();

	void SetSbirthday(CTime ctime);

    CString GetFilePath(int sid);//获取文件路径

	//senddate数据的初始化
    void InitSenddate();
    
    //析构
	virtual ~SCase();

	//重载operator==
	operator== (SCase scase) const
	{
		return sid == scase.sid;//返回病例编号
	}

private:
	
	int sid;//病例编号

	CString sname;//病例名称

    CTime sbirthday;//病例出生日期

	int ssex;//性别，0代表未填，1表示男，2表示女

	int shigh;//身高cm

	int sweight;//体重kg

	int sage;//年龄，程序计算得出

	CTime sstartdate;//开始记录日期时间

	CTime senddate;//记录结束日期时间

	CString stotaltime;//记录总时间

	CString scomment;//备注

	CString sdiagnosis;//诊断医生

	CString srecord;//记录医生

};

#endif // !defined(AFX_SCASE_H__D31A9ED7_2951_41C4_A3C3_855FC6419BCB__INCLUDED_)
