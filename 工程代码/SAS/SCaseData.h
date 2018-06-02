// SCaseData.h: interface for the SCaseData class.
//日期：2012年3月17日
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCASEDATA_H__74438D8F_9D49_44AD_9157_54DE54B9A16A__INCLUDED_)
#define AFX_SCASEDATA_H__74438D8F_9D49_44AD_9157_54DE54B9A16A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SCase.h"
#include <afxtempl.h>


class SCaseData  
{
public:
	SCaseData();

	//int GetSCaseCount();//获得病例

	int GetSCaseList();//获得数据库中所有病例信息,返回病例信息总数

	SCase SelectSCaseBySid(int sid);//根据病例编号查询病例信息

	SCase SelectSCaseBySname(CString sname);//根据病例姓名查询病例信息

	int DeleteSCaseBySid(int sid);//根据病例编号删除病例信息

	int SaveSCaseBySid(SCase scase);//根据病例编号保存病例信息

	int InsertSCase(SCase scase);//插入病例信息

	CString GetFilePath();//获得数据库的存储路径

	virtual ~SCaseData();

public:

	CList<SCase,SCase&> sCaseList;//病例列表

private:
	CString connString;//连接字符串

	CString connHead;


//private:

    //CString connString;//连接字符串
	//CList<SCase,SCase&> SCaseList;//病例列表
   // int SCaseCount;//病例总数

};

#endif // !defined(AFX_SCASEDATA_H__74438D8F_9D49_44AD_9157_54DE54B9A16A__INCLUDED_)
