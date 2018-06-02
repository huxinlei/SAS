// SCaseNew.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SCaseNew.h"
#include "SCase.h"
#include "SCaseData.h"
#include "SCaseFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SCaseNew dialog


SCaseNew::SCaseNew(CWnd* pParent /*=NULL*/)
	: CDialog(SCaseNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(SCaseNew)
	m_Scomment = _T("");
	m_Sdiagnosis = _T("");
	m_Sfilepath = _T("");
	m_Srecord = _T("");
	m_Sage = 0;
	m_Sbirthday = 0;
//	m_Senddate1 = _T("");
//	m_Senddate2 = _T("");
	m_Shigh = 0;
	m_Sid = 0;
	m_Sname1 = _T("");
	m_Sname2 = _T("");
	m_Ssex = 2;
	m_Sweight = 0;
//	m_Stotaltime = _T("");
	m_Sstartdate1 = 0;
	m_Sstartdate2 = 0;
	//}}AFX_DATA_INIT
}


void SCaseNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SCaseNew)
	DDX_Text(pDX, IDC_COMMENT, m_Scomment);
	DDX_Text(pDX, IDC_DIAGNOSIS, m_Sdiagnosis);
	DDX_Text(pDX, IDC_FILEPATH, m_Sfilepath);
	DDX_Text(pDX, IDC_RECORD, m_Srecord);
	DDX_Text(pDX, IDC_SAGE, m_Sage);
	DDX_DateTimeCtrl(pDX, IDC_SBIRTHDAY, m_Sbirthday);
	//DDX_Text(pDX, IDC_SENDDATE1, m_Senddate1);
	//DDX_Text(pDX, IDC_SENDDATE2, m_Senddate2);
	DDX_Text(pDX, IDC_SHIGH, m_Shigh);
	DDX_Text(pDX, IDC_SID, m_Sid);
	DDX_Text(pDX, IDC_SNAME1, m_Sname1);
	DDX_Text(pDX, IDC_SNAME2, m_Sname2);
	DDX_CBIndex(pDX, IDC_SSEX, m_Ssex);
	DDX_Text(pDX, IDC_SWEIGHT, m_Sweight);
	//DDX_Text(pDX, IDC_TOTALTIME, m_Stotaltime);
	DDX_DateTimeCtrl(pDX, IDC_SSTARTDATE1, m_Sstartdate1);
	DDX_DateTimeCtrl(pDX, IDC_SSTARTDATE2, m_Sstartdate2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SCaseNew, CDialog)
	//{{AFX_MSG_MAP(SCaseNew)
	ON_BN_CLICKED(IDOK, OnImport)
	ON_BN_CLICKED(IDC_FILESCAN, OnFilescan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SCaseNew message handlers

//��������
void SCaseNew::OnImport() 
{
	UpdateData(1);//д�ر���


	if(m_Sname1.IsEmpty()||m_Sname2.IsEmpty())
	{
		MessageBox("�������Ʋ���Ϊ�գ����飡","������ʾ");

		return;
	}

	if(m_Sfilepath.IsEmpty())
	{
		MessageBox("���߲����ļ������ڣ����飡","������ʾ");
		
		return;
	}
		

	CString name = m_Sname1 + m_Sname2;//�������

	CTime Sstartdate(m_Sstartdate1.GetYear(),m_Sstartdate1.GetMonth(),m_Sstartdate1.GetDay(),
		m_Sstartdate2.GetHour(),m_Sstartdate2.GetMinute(),m_Sstartdate2.GetSecond());//��ÿ�ʼʱ��

    SCase scase;

	scase.SetSName(name);//��������
	scase.SetSbirthday(m_Sbirthday);//��������
	scase.SetSsex(m_Ssex);//�����Ա�
	scase.SetShigh(m_Shigh);//�������
	scase.SetSweight(m_Sweight);//��������
	scase.SetSstartdate(Sstartdate);//���ÿ�ʼʱ��
    scase.SetScomment(m_Scomment);//���ñ�ע
	scase.SetSdiagnosis(m_Sdiagnosis);//�������ҽ��
	scase.SetSrecord(m_Srecord);//���ü�¼ҽ��

    SCaseData dataOper;//ʵ�����ݿ������

	SCaseFile fileOper;//ʵ���ļ�������

	int sid = -1;
	if((sid=dataOper.InsertSCase(scase)) > -1)//���벡��
    {
		if(fileOper.CopyDatas(sid,m_Sfilepath))
		{
           AfxMessageBox("�������ݵ���ɹ�!");
		}
		else
		{
			dataOper.DeleteSCaseBySid(sid);//ɾ�����ݿ��еĲ�����Ϣ
			AfxMessageBox("�����ļ���ԭ�������ݵ���ʧ��!");
		}
		
	}
	else
	{
		AfxMessageBox("�������ݿ��ԭ�������ݵ���ʧ��!");
	}

	CDialog::OnOK();//�رյ�ǰ����
	UpdateData(0);//д����ͼ
}

//���ļ��Ի���
void SCaseNew::OnFilescan() 
{
	UpdateData(1);//д�ؿؼ�����

	char sfile[] = "�����ļ�(*.dt)|*.dt";//�ļ�������

	CFileDialog dlg(TRUE,"dt","",OFN_ALLOWMULTISELECT,sfile);//�Ի������

	if(dlg.DoModal())
	{
		m_Sfilepath = dlg.GetPathName();//����ļ�����·��

		UpdateData(0);//д�ؿؼ�
	}

}
