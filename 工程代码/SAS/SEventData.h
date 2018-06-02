// SEventData.h: interface for the SEventData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEVENTDATA_H__B72FD312_6B09_4625_9EC1_0004C0D13F37__INCLUDED_)
#define AFX_SEVENTDATA_H__B72FD312_6B09_4625_9EC1_0004C0D13F37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>//导入头文件

typedef struct ANLEVENT
{
	int nID;//标记ID

	BOOL bAuto;//FALSE,表示手动标记，TRUE表示自动分析标记

	int nBeginTime;//事件起始时间

	int nEndTime;//事件结束时间

	int nParam;//参数 字段为事件类型标记(1:呼吸暂停事件Apnea Event)(2:低通气事件Hypopnea Event)(3:氧减事件OD Event)


}ANLEVENT;//病例事件

class SEventData  
{
public:

	SEventData();

	virtual ~SEventData();

    int GetSEventList(int sid);//获得事件列表，返回-1表示获取失败（文件不存在）

	int SaveSEventList(int sid);//保存事件列表到文件，返回-1表示保存失败（文件不存在）
    
    CString GetFilePath(int sid);

    bool SEventData::DeleteEvents(int sid);//删除事件列表

public:
	CList<ANLEVENT,ANLEVENT&> sEventList;//病例列表

};

#endif // !defined(AFX_SEVENTDATA_H__B72FD312_6B09_4625_9EC1_0004C0D13F37__INCLUDED_)
