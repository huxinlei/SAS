// SEventData.h: interface for the SEventData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEVENTDATA_H__B72FD312_6B09_4625_9EC1_0004C0D13F37__INCLUDED_)
#define AFX_SEVENTDATA_H__B72FD312_6B09_4625_9EC1_0004C0D13F37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>//����ͷ�ļ�

typedef struct ANLEVENT
{
	int nID;//���ID

	BOOL bAuto;//FALSE,��ʾ�ֶ���ǣ�TRUE��ʾ�Զ��������

	int nBeginTime;//�¼���ʼʱ��

	int nEndTime;//�¼�����ʱ��

	int nParam;//���� �ֶ�Ϊ�¼����ͱ��(1:������ͣ�¼�Apnea Event)(2:��ͨ���¼�Hypopnea Event)(3:�����¼�OD Event)


}ANLEVENT;//�����¼�

class SEventData  
{
public:

	SEventData();

	virtual ~SEventData();

    int GetSEventList(int sid);//����¼��б�����-1��ʾ��ȡʧ�ܣ��ļ������ڣ�

	int SaveSEventList(int sid);//�����¼��б��ļ�������-1��ʾ����ʧ�ܣ��ļ������ڣ�
    
    CString GetFilePath(int sid);

    bool SEventData::DeleteEvents(int sid);//ɾ���¼��б�

public:
	CList<ANLEVENT,ANLEVENT&> sEventList;//�����б�

};

#endif // !defined(AFX_SEVENTDATA_H__B72FD312_6B09_4625_9EC1_0004C0D13F37__INCLUDED_)
