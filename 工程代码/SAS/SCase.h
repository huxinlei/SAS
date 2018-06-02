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
		int sweight,CTime sstartdate,CString scomment,CString sdiagnosis,CString srecord);//���ι��캯��
    

	//sid
	int GetSid();

	void SetSid(int sid);


	//sname
	CString GetSName();

	void SetSName(CString sname);
    
	//ssex 0Ϊδ�1Ϊ�У�2ΪŮ
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

	//������䷽��
    int GetSage();

	//��ý�������ʱ��
	CTime GetSenddate();

	//��ü�¼��ʱ�䣬����GetSenddate����
	int GetStotaltime();

	//���ҽ��
	CString GetSdiagnosis();

	void SetSdiagnosis(CString sdiagnosis);

	//��¼ҽ��
	CString GetSrecord();

	void SetSrecord(CString srecord);

	//��������
    CTime GetSbirthday();

	void SetSbirthday(CTime ctime);

    CString GetFilePath(int sid);//��ȡ�ļ�·��

	//senddate���ݵĳ�ʼ��
    void InitSenddate();
    
    //����
	virtual ~SCase();

	//����operator==
	operator== (SCase scase) const
	{
		return sid == scase.sid;//���ز������
	}

private:
	
	int sid;//�������

	CString sname;//��������

    CTime sbirthday;//������������

	int ssex;//�Ա�0����δ�1��ʾ�У�2��ʾŮ

	int shigh;//���cm

	int sweight;//����kg

	int sage;//���䣬�������ó�

	CTime sstartdate;//��ʼ��¼����ʱ��

	CTime senddate;//��¼��������ʱ��

	CString stotaltime;//��¼��ʱ��

	CString scomment;//��ע

	CString sdiagnosis;//���ҽ��

	CString srecord;//��¼ҽ��

};

#endif // !defined(AFX_SCASE_H__D31A9ED7_2951_41C4_A3C3_855FC6419BCB__INCLUDED_)
