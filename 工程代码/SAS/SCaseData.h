// SCaseData.h: interface for the SCaseData class.
//���ڣ�2012��3��17��
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

	//int GetSCaseCount();//��ò���

	int GetSCaseList();//������ݿ������в�����Ϣ,���ز�����Ϣ����

	SCase SelectSCaseBySid(int sid);//���ݲ�����Ų�ѯ������Ϣ

	SCase SelectSCaseBySname(CString sname);//���ݲ���������ѯ������Ϣ

	int DeleteSCaseBySid(int sid);//���ݲ������ɾ��������Ϣ

	int SaveSCaseBySid(SCase scase);//���ݲ�����ű��没����Ϣ

	int InsertSCase(SCase scase);//���벡����Ϣ

	CString GetFilePath();//������ݿ�Ĵ洢·��

	virtual ~SCaseData();

public:

	CList<SCase,SCase&> sCaseList;//�����б�

private:
	CString connString;//�����ַ���

	CString connHead;


//private:

    //CString connString;//�����ַ���
	//CList<SCase,SCase&> SCaseList;//�����б�
   // int SCaseCount;//��������

};

#endif // !defined(AFX_SCASEDATA_H__74438D8F_9D49_44AD_9157_54DE54B9A16A__INCLUDED_)
