// SASView.cpp : implementation of the CSASView class
//

#include "stdafx.h"
#include "SAS.h"

#include "SASDoc.h"
#include "SASView.h"

#include "SCase.h"
#include "SCaseDisplay.h"
#include "SEventData.h"
#include "SCaseNew.h"
#include "stdlib.h"
#include "SCaseShow.h"
#include "SetColor.h"
#include "SetConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSASView

IMPLEMENT_DYNCREATE(CSASView, CFormView)

BEGIN_MESSAGE_MAP(CSASView, CFormView)
	//{{AFX_MSG_MAP(CSASView)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_COMMAND(ID_NEWSCASE, OnNewscase)
	ON_NOTIFY(NM_CLICK, IDC_PLIST, OnClickPlist)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_COMMAND(ID_COLORSET, OnColorset)
	ON_COMMAND(ID_WORDANDSPEED, OnWordandspeed)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PLIST, OnItemchangedPlist)
	ON_BN_CLICKED(IDC_PADW, OnPadw)
	ON_BN_CLICKED(IDC_PADR, OnPadr)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_CONSULT, OnConsult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSASView construction/destruction

CSASView::CSASView()
	: CFormView(CSASView::IDD)
{
	//{{AFX_DATA_INIT(CSASView)
	m_Sid = 0;
	m_Sname1 = _T("");
	m_Sname2 = _T("");
	m_Ssex = -1;
	m_Shigh = 0;
	m_Sweight = 0;
	m_Stotaltime = 0;
	m_Sstartdate1 = 0;
	m_Sstartdate2 = 0;
	m_Senddate1 = 0;
	m_Senddate2 = 0;
	m_Sbirthday = 0;
	m_Scomment = _T("");
	m_Sdiagnosis = _T("");
	m_Srecord = _T("");
	m_Sage = 0;
	m_Pad = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSASView::~CSASView()
{
}

void CSASView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSASView)
	DDX_Control(pDX, IDC_Picture, m_Picture);
	DDX_Control(pDX, IDC_PLIST, m_ScaseList);
	DDX_Text(pDX, IDC_SID, m_Sid);
	DDX_Text(pDX, IDC_SNAME1, m_Sname1);
	DDX_Text(pDX, IDC_SNAME2, m_Sname2);
	DDX_CBIndex(pDX, IDC_SSEX, m_Ssex);
	DDX_Text(pDX, IDC_SHIGH, m_Shigh);
	DDX_Text(pDX, IDC_SWEIGHT, m_Sweight);
	DDX_Text(pDX, IDC_TOTALTIME, m_Stotaltime);
	DDX_DateTimeCtrl(pDX, IDC_STARTDATE1, m_Sstartdate1);
	DDX_DateTimeCtrl(pDX, IDC_STARTDATE2, m_Sstartdate2);
	DDX_DateTimeCtrl(pDX, IDC_SENDDATE1, m_Senddate1);
	DDX_DateTimeCtrl(pDX, IDC_SENDDATE2, m_Senddate2);
	DDX_DateTimeCtrl(pDX, IDC_SBIRTHDAY, m_Sbirthday);
	DDX_Text(pDX, IDC_COMMENT, m_Scomment);
	DDX_Text(pDX, IDC_DIAGNOSIS, m_Sdiagnosis);
	DDX_Text(pDX, IDC_RECORD, m_Srecord);
	DDX_Text(pDX, IDC_SAGE, m_Sage);
	DDX_Text(pDX, IDC_PAD, m_Pad);
	//}}AFX_DATA_MAP
}

BOOL CSASView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	

	return CFormView::PreCreateWindow(cs);
}

void CSASView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
   
	//��ò���������ʾ
	m_ScaseList.InsertColumn(0,"�������");
	m_ScaseList.InsertColumn(1,"��������");
	m_ScaseList.InsertColumn(2,"������������");
	m_ScaseList.InsertColumn(3,"����");
	m_ScaseList.InsertColumn(4,"�Ա�");
	m_ScaseList.InsertColumn(5,"���(cm)");
	m_ScaseList.InsertColumn(6,"����(kg)");
	m_ScaseList.InsertColumn(7,"��ʼ��¼����ʱ��");
	m_ScaseList.InsertColumn(8,"��ע");
	m_ScaseList.InsertColumn(9,"���ҽ��");
	m_ScaseList.InsertColumn(10,"��¼ҽ��");
	m_ScaseList.InsertColumn(11,"��¼��������ʱ��");
	m_ScaseList.InsertColumn(12,"��¼��ʱ��(s)");

	m_ScaseList.SetColumnWidth(0,60);
	m_ScaseList.SetColumnWidth(1,60);
	m_ScaseList.SetColumnWidth(2,90);
	m_ScaseList.SetColumnWidth(3,60);
	m_ScaseList.SetColumnWidth(4,60);
	m_ScaseList.SetColumnWidth(5,60);
	m_ScaseList.SetColumnWidth(6,60);
	m_ScaseList.SetColumnWidth(7,120);
	m_ScaseList.SetColumnWidth(8,60);
	m_ScaseList.SetColumnWidth(9,60);
	m_ScaseList.SetColumnWidth(10,70);
	m_ScaseList.SetColumnWidth(11,120);
	m_ScaseList.SetColumnWidth(12,90);

	m_ScaseList.SetExtendedStyle(m_ScaseList.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT|LVS_EX_GRIDLINES);//����ѡ��ȫ��

	this->RefreshList();//ˢ���б���ͼ

	//��ʾ����ʯͷ�����ұ�־


	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CSASView diagnostics

#ifdef _DEBUG
void CSASView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSASView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSASDoc* CSASView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSASDoc)));
	return (CSASDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSASView message handlers


//��ѡ����Ĳ�����Ϣ
void CSASView::OnOpen() 
{

    if(m_Sid > 0)
	{
	  SCase scase = GetScaseBySid(m_Sid);
		
      SCaseDisplay databoard(scase);

      databoard.DoModal();
	}
	else
	{
		AfxMessageBox("��ѡ�������ٽ��д˲���!");
	}

}

void CSASView::OnCancel() 
{
	m_Sid = 0;
	m_Sname1 = _T("");
	m_Sname2 = _T("");
	m_Ssex = -1;
	m_Shigh = 0;
	m_Sweight = 0;
	m_Stotaltime = 0;
	m_Sstartdate1 = 0;
	m_Sstartdate2 = 0;
	m_Senddate1 = 0;
	m_Senddate2 = 0;
	m_Sbirthday = 0;
	m_Scomment = _T("");
	m_Sdiagnosis = _T("");
	m_Srecord = _T("");
	m_Sage = 0;
	
	UpdateData(0);
}

//������Ϣ�޸ĺ󱣴�
void CSASView::OnSave() 
{
   if(m_Sid > 0)
   {
	UpdateData(1);//����ͼ�е�����д�����


	//��ⲡ�������Ƿ�����
	if(m_Sname1.IsEmpty()||m_Sname2.IsEmpty())
	{
		MessageBox("�������Ʋ���Ϊ�գ����飡","������ʾ");
		
		return;
	}
    
	SCase scase;//���岡����Ϣ

	scase.SetSid(m_Sid);//����sid

	scase.SetSName(m_Sname1 + m_Sname2);//����sname

	scase.SetSsex(m_Ssex);//�����Ա�

	scase.SetSbirthday(m_Sbirthday);//��������

	scase.SetShigh(m_Shigh);//�������

	scase.SetSweight(m_Sweight);//��������

	CTime startdate(m_Sstartdate1.GetYear(),m_Sstartdate1.GetMonth(),m_Sstartdate1.GetDay(),
		       m_Sstartdate2.GetHour(),m_Sstartdate2.GetMinute(),m_Sstartdate2.GetSecond());

	scase.SetSstartdate(startdate);//���ÿ�ʼ����

	scase.SetSdiagnosis(m_Sdiagnosis);//�������ҽ��

	scase.SetSrecord(m_Srecord);//���ü�¼ҽ��

	scase.SetScomment(m_Scomment);//���ñ�ע��Ϣ

	dataOper.SaveSCaseBySid(scase);//���޸��ύ�����ݿ�

	//��������ͽ������ڵ���ʾ

    this->m_Sage = scase.GetSage();//�������

	scase.InitSenddate();//��ʼ����������

	this->m_Senddate1 = scase.GetSenddate();

	this->m_Senddate2 = scase.GetSenddate();

    this->m_Stotaltime = scase.GetStotaltime();//�����ʱ��

	UpdateData(0);


    AfxMessageBox("������Ϣ�Ѿ����³ɹ�!");

	this->RefreshList();//���²�����Ϣ�б�
   }
   else
   {
	 AfxMessageBox("��ѡ�������ٽ��д˲���!");
   }
}

//���½���������
void CSASView::OnNewscase() 
{
	
	SCaseNew newDialog;//�����½�����

	if(newDialog.DoModal())//����Ӵ���
	{
		this->RefreshList();//ˢ���б���ͼ�ؼ�
	}

}

void CSASView::OnClickPlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;

	if(this->m_ScaseList.GetSelectedCount() > 0)
	{
	
	 int itemIndex = this->m_ScaseList.GetSelectionMark();//���ѡ�е��±�

	 int sid  = atoi(this->m_ScaseList.GetItemText(itemIndex,0));//��ò������

	 //SCaseData dataOper;

	 SCase scase = GetScaseBySid(sid);//��ò�����Ϣ

	 this->m_Sid = scase.GetSid();

	 //�����Ľ�����жϱ���
	 CString sname1 = scase.GetSName().Left(2);

	 CString sname2 = scase.GetSName().Right(scase.GetSName().GetLength() - 2);

	 this->m_Sname1 = sname1;

	 this->m_Sname2 = sname2;

	 this->m_Sage = scase.GetSage();//�������

	 this->m_Ssex = scase.GetSsex();

	 this->m_Shigh = scase.GetShigh();

	 this->m_Sweight = scase.GetSweight();

	 this->m_Sbirthday = scase.GetSbirthday();

	 this->m_Scomment = scase.GetScomment();

	 this->m_Sdiagnosis = scase.GetSdiagnosis();

	 this->m_Srecord = scase.GetSrecord();

	 this->m_Sstartdate1 = scase.GetSstartdate();

	 this->m_Sstartdate2 = scase.GetSstartdate();

	 scase.InitSenddate();

	 this->m_Senddate1 = scase.GetSenddate();

	 this->m_Senddate2 = scase.GetSenddate();

     this->m_Stotaltime = scase.GetStotaltime();//�����ʱ��

	 UpdateData(0);

	 
	}
		 
}

//ˢ���б�ؼ�
void CSASView::RefreshList()
{
	

	m_ScaseList.DeleteAllItems();

	if(dataOper.GetSCaseList()>0)
	{
		POSITION pos = dataOper.sCaseList.GetHeadPosition();//��õ�һ������

		int index = 0;

		while(pos != NULL)
		{
			SCase scase = dataOper.sCaseList.GetNext(pos);//���������
          
			CString str;//ת��Ϊ�ַ�

			str.Format("%d_%d",index,scase.GetSid());

			m_ScaseList.InsertItem(index,str);//�����

			str.Format("%d",scase.GetSid());

			m_ScaseList.SetItemText(index,0,str);

		    m_ScaseList.SetItemText(index,1,scase.GetSName());

			str.Format("%d-%d-%d %d:%d:%d",scase.GetSbirthday().GetYear(),
				        scase.GetSbirthday().GetMonth(),
						scase.GetSbirthday().GetDay(),
						scase.GetSbirthday().GetHour(),
						scase.GetSbirthday().GetMinute(),
						scase.GetSbirthday().GetSecond());

            m_ScaseList.SetItemText(index,2,str);

			str.Format("%d",scase.GetSage());

			m_ScaseList.SetItemText(index,3,str);

			str = scase.GetSsex() == 2?"δ��":(scase.GetSsex() == 0?"��":"Ů");

            m_ScaseList.SetItemText(index,4,str);

			str.Format("%d",scase.GetShigh());

			m_ScaseList.SetItemText(index,5,str);

			str.Format("%d",scase.GetSweight());

			m_ScaseList.SetItemText(index,6,str);

			str.Format("%d-%d-%d %d:%d:%d",scase.GetSstartdate().GetYear(),
				        scase.GetSstartdate().GetMonth(),
						scase.GetSstartdate().GetDay(),
						scase.GetSstartdate().GetHour(),
						scase.GetSstartdate().GetMinute(),
						scase.GetSstartdate().GetSecond());
			
			m_ScaseList.SetItemText(index,7,str);

			m_ScaseList.SetItemText(index,8,scase.GetScomment());

			m_ScaseList.SetItemText(index,9,scase.GetSdiagnosis());

			m_ScaseList.SetItemText(index,10,scase.GetSrecord());

			scase.InitSenddate();//��ʼ����������

			str.Format("%d-%d-%d %d:%d:%d",scase.GetSenddate().GetYear(),
				        scase.GetSenddate().GetMonth(),
						scase.GetSenddate().GetDay(),
						scase.GetSenddate().GetHour(),
						scase.GetSenddate().GetMinute(),
						scase.GetSenddate().GetSecond());

			m_ScaseList.SetItemText(index,11,str);

			str.Format("%d",scase.GetStotaltime());

			m_ScaseList.SetItemText(index,12,str);

            index++;//�±��1
		}
	}

}

//��dataOper.sCaseList�в����Ҫ�Ĳ���
SCase CSASView::GetScaseBySid(int sid)
{
	SCase scase;//������Ϣʵ��

	scase.SetSid(-1);//Ĭ��sidΪ��1����־δ�鵽��Ӧ��Ϣ

	POSITION pos = dataOper.sCaseList.GetHeadPosition();//��õ�һ������

	while(pos != NULL)
	{
       scase = dataOper.sCaseList.GetNext(pos);//���������

	   if(scase.GetSid() == sid)
	   {
          break;//����������ѭ��
	   }
	}

	return scase;
}

//ɾ����ǰ������Ϣ
void CSASView::OnDelete() 
{

  if(m_Sid > 0)
	{
	   dataOper.DeleteSCaseBySid(m_Sid);//ɾ�����ݿ��в����Ļ�����Ϣ

       dataFile.DeleteDatas(m_Sid);//ɾ����ǰѡ�����еĲ����ļ�

	   eventOper.DeleteEvents(m_Sid);//ɾ����ǰѡ�����е��¼��ļ�

	   this->RefreshList();//���²�����Ϣ�б�


	   //����������ʾ
	   m_Sid = 0;
	   m_Sname1 = _T("");
	   m_Sname2 = _T("");
	   m_Ssex = -1;
	   m_Shigh = 0;
	   m_Sweight = 0;
	   m_Stotaltime = 0;
	   m_Sstartdate1 = 0;
	   m_Sstartdate2 = 0;
	   m_Senddate1 = 0;
 	   m_Senddate2 = 0;
	   m_Sbirthday = 0;
	   m_Scomment = _T("");
	   m_Sdiagnosis = _T("");
	   m_Srecord = _T("");
	   m_Sage = 0;

	   UpdateData(0);//���µ�ǰѡ�в�����Ϣ

	   AfxMessageBox("������Ϣ�Ѿ��ɹ�ɾ��!");
 
	}
	else
	{
		AfxMessageBox("��ѡ�������ٽ��д˲���!");
	}
 
}

//ͼ����ɫ����
void CSASView::OnColorset() 
{
   SetColor SetDialog;
   
   SetDialog.DoModal();
  
}


//������������
void CSASView::OnWordandspeed() 
{
  SetConfig config;
 	
  config.DoModal();//��ʾ���ô���
}

void CSASView::OnItemchangedPlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	*pResult = 0;

	if(this->m_ScaseList.GetSelectedCount() > 0)
	{
		
		int itemIndex = this->m_ScaseList.GetSelectionMark();//���ѡ�е��±�
		
		int sid  = atoi(this->m_ScaseList.GetItemText(itemIndex,0));//��ò������
		
		//SCaseData dataOper;
		
		SCase scase = GetScaseBySid(sid);//��ò�����Ϣ
		
		this->m_Sid = scase.GetSid();
		
		//�����Ľ�����жϱ���
		CString sname1 = scase.GetSName().Left(2);
		
		CString sname2 = scase.GetSName().Right(scase.GetSName().GetLength() - 2);
		
		this->m_Sname1 = sname1;
		
		this->m_Sname2 = sname2;
		
		this->m_Sage = scase.GetSage();//�������
		
		this->m_Ssex = scase.GetSsex();
		
		this->m_Shigh = scase.GetShigh();
		
		this->m_Sweight = scase.GetSweight();
		
		this->m_Sbirthday = scase.GetSbirthday();
		
		this->m_Scomment = scase.GetScomment();
		
		this->m_Sdiagnosis = scase.GetSdiagnosis();
		
		this->m_Srecord = scase.GetSrecord();
		
		this->m_Sstartdate1 = scase.GetSstartdate();
		
		this->m_Sstartdate2 = scase.GetSstartdate();
		
		scase.InitSenddate();
		
		this->m_Senddate1 = scase.GetSenddate();
		
		this->m_Senddate2 = scase.GetSenddate();
		
		this->m_Stotaltime = scase.GetStotaltime();//�����ʱ��
		
		UpdateData(0);
		
		
	}
		 
}

void CSASView::OnPadw() 
{
	UpdateData(1);

	CString str;

	this->GetDlgItemText(IDC_PADW,str);//��õ�ǰ��ť��ʾ

	if(str == "�������")
	{

		this->GetDlgItem(IDC_PADR)->EnableWindow(FALSE);
		
		this->GetDlgItem(IDC_PAD)->EnableWindow(FALSE);

		this->SetDlgItemText(IDC_PADW,"������");

	}
	else
	{

		this->GetDlgItem(IDC_PADR)->EnableWindow(TRUE);
		
		this->GetDlgItem(IDC_PAD)->EnableWindow(TRUE);

		this->SetDlgItemText(IDC_PADW,"�������");

	}

}

void CSASView::OnPadr() 
{
   this->m_Pad = "";

   UpdateData(0);
	
}

void CSASView::OnConsult() 
{

	UpdateData(1);

	if(m_Sname1.IsEmpty()||m_Sname2.IsEmpty())
	{
       MessageBox("�������벻��Ϊ�գ����飡","������ʾ");

	   return;
	}
	SCase scase = dataOper.SelectSCaseBySname(m_Sname1 + m_Sname2);//��ò�����Ϣ

	if(scase.GetSid() != -1)
	{
	
	this->m_Sid = scase.GetSid();
	
	//�����Ľ�����жϱ���
	CString sname1 = scase.GetSName().Left(2);
	
	CString sname2 = scase.GetSName().Right(scase.GetSName().GetLength() - 2);
	
	this->m_Sname1 = sname1;
	
	this->m_Sname2 = sname2;
	
	this->m_Sage = scase.GetSage();//�������
	
	this->m_Ssex = scase.GetSsex();
	
	this->m_Shigh = scase.GetShigh();
	
	this->m_Sweight = scase.GetSweight();
	
	this->m_Sbirthday = scase.GetSbirthday();
	
	this->m_Scomment = scase.GetScomment();
	
	this->m_Sdiagnosis = scase.GetSdiagnosis();
	
	this->m_Srecord = scase.GetSrecord();
	
	this->m_Sstartdate1 = scase.GetSstartdate();
	
	this->m_Sstartdate2 = scase.GetSstartdate();
	
	scase.InitSenddate();
	
	this->m_Senddate1 = scase.GetSenddate();
	
	this->m_Senddate2 = scase.GetSenddate();
	
	this->m_Stotaltime = scase.GetStotaltime();//�����ʱ��
	
	UpdateData(0);
	}
	else
	{
		MessageBox("�˲��������ڣ�","������ʾ");
	}
		
}
