// SCaseFile.h: interface for the SCaseFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCASEFILE_H__C2D27F3F_535E_4FA6_B6D1_32E4F5D4D0E2__INCLUDED_)
#define AFX_SCASEFILE_H__C2D27F3F_535E_4FA6_B6D1_32E4F5D4D0E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//�������ݽṹ��
typedef struct DATA_BLOCK {
	                short	nFlow;	//��������
	                short   nSpO2;  //Ѫ������
	                short   nPulse; //��������
	                short   nPleth; //Ѫ���ݻ���
             } DATA_BLOCK;


class SCaseFile  
{
public:
	SCaseFile();

	DATA_BLOCK *GetDatas();//�������ָ��

	int GetLength();

	bool InitDatas(int sid);//���ݲ����ų�ʼ����������

	bool CopyDatas(int sid,CString originpath);//�������ļ����Ƶ�SCases�ļ�����

	bool DeleteDatas(int sid);//�������Ĵ�SCases�ļ�����ɾ��

	virtual ~SCaseFile();

public:

	DATA_BLOCK *datas;//��������ָ��

	int length;//����

private:
	CString GetFilePath(int sid);

};


#endif // !defined(AFX_SCASEFILE_H__C2D27F3F_535E_4FA6_B6D1_32E4F5D4D0E2__INCLUDED_)
