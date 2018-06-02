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
   
	//获得病例数据显示
	m_ScaseList.InsertColumn(0,"病例编号");
	m_ScaseList.InsertColumn(1,"病患名称");
	m_ScaseList.InsertColumn(2,"病患出生日期");
	m_ScaseList.InsertColumn(3,"年龄");
	m_ScaseList.InsertColumn(4,"性别");
	m_ScaseList.InsertColumn(5,"身高(cm)");
	m_ScaseList.InsertColumn(6,"体重(kg)");
	m_ScaseList.InsertColumn(7,"开始记录日期时间");
	m_ScaseList.InsertColumn(8,"备注");
	m_ScaseList.InsertColumn(9,"诊断医生");
	m_ScaseList.InsertColumn(10,"记录医生");
	m_ScaseList.InsertColumn(11,"记录结束日期时间");
	m_ScaseList.InsertColumn(12,"记录总时间(s)");

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

	m_ScaseList.SetExtendedStyle(m_ScaseList.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT|LVS_EX_GRIDLINES);//设置选中全行

	this->RefreshList();//刷新列表视图

	//显示三块石头工作室标志


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


//打开选中项的病例信息
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
		AfxMessageBox("请选择病例后再进行此操作!");
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

//病例信息修改后保存
void CSASView::OnSave() 
{
   if(m_Sid > 0)
   {
	UpdateData(1);//将视图中的数据写入变量


	//检测病患姓名是否输入
	if(m_Sname1.IsEmpty()||m_Sname2.IsEmpty())
	{
		MessageBox("患者名称不能为空，请检查！","输入提示");
		
		return;
	}
    
	SCase scase;//定义病例信息

	scase.SetSid(m_Sid);//设置sid

	scase.SetSName(m_Sname1 + m_Sname2);//设置sname

	scase.SetSsex(m_Ssex);//设置性别

	scase.SetSbirthday(m_Sbirthday);//设置生日

	scase.SetShigh(m_Shigh);//设置身高

	scase.SetSweight(m_Sweight);//设置体重

	CTime startdate(m_Sstartdate1.GetYear(),m_Sstartdate1.GetMonth(),m_Sstartdate1.GetDay(),
		       m_Sstartdate2.GetHour(),m_Sstartdate2.GetMinute(),m_Sstartdate2.GetSecond());

	scase.SetSstartdate(startdate);//设置开始日期

	scase.SetSdiagnosis(m_Sdiagnosis);//设置诊断医生

	scase.SetSrecord(m_Srecord);//设置记录医生

	scase.SetScomment(m_Scomment);//设置备注信息

	dataOper.SaveSCaseBySid(scase);//将修改提交给数据库

	//更新年龄和结束日期的显示

    this->m_Sage = scase.GetSage();//获得年龄

	scase.InitSenddate();//初始化结束日期

	this->m_Senddate1 = scase.GetSenddate();

	this->m_Senddate2 = scase.GetSenddate();

    this->m_Stotaltime = scase.GetStotaltime();//获得总时间

	UpdateData(0);


    AfxMessageBox("病例信息已经更新成功!");

	this->RefreshList();//更新病患信息列表
   }
   else
   {
	 AfxMessageBox("请选择病例后再进行此操作!");
   }
}

//打开新建病例窗体
void CSASView::OnNewscase() 
{
	
	SCaseNew newDialog;//事例新建窗体

	if(newDialog.DoModal())//打开添加窗体
	{
		this->RefreshList();//刷新列表视图控件
	}

}

void CSASView::OnClickPlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	*pResult = 0;

	if(this->m_ScaseList.GetSelectedCount() > 0)
	{
	
	 int itemIndex = this->m_ScaseList.GetSelectionMark();//获得选中的下标

	 int sid  = atoi(this->m_ScaseList.GetItemText(itemIndex,0));//获得病例编号

	 //SCaseData dataOper;

	 SCase scase = GetScaseBySid(sid);//获得病例信息

	 this->m_Sid = scase.GetSid();

	 //留待改进如何判断编码
	 CString sname1 = scase.GetSName().Left(2);

	 CString sname2 = scase.GetSName().Right(scase.GetSName().GetLength() - 2);

	 this->m_Sname1 = sname1;

	 this->m_Sname2 = sname2;

	 this->m_Sage = scase.GetSage();//获得年龄

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

     this->m_Stotaltime = scase.GetStotaltime();//获得总时间

	 UpdateData(0);

	 
	}
		 
}

//刷新列表控件
void CSASView::RefreshList()
{
	

	m_ScaseList.DeleteAllItems();

	if(dataOper.GetSCaseList()>0)
	{
		POSITION pos = dataOper.sCaseList.GetHeadPosition();//获得第一条数据

		int index = 0;

		while(pos != NULL)
		{
			SCase scase = dataOper.sCaseList.GetNext(pos);//获得数据项
          
			CString str;//转换为字符

			str.Format("%d_%d",index,scase.GetSid());

			m_ScaseList.InsertItem(index,str);//添加项

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

			str = scase.GetSsex() == 2?"未填":(scase.GetSsex() == 0?"男":"女");

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

			scase.InitSenddate();//初始化结束日期

			str.Format("%d-%d-%d %d:%d:%d",scase.GetSenddate().GetYear(),
				        scase.GetSenddate().GetMonth(),
						scase.GetSenddate().GetDay(),
						scase.GetSenddate().GetHour(),
						scase.GetSenddate().GetMinute(),
						scase.GetSenddate().GetSecond());

			m_ScaseList.SetItemText(index,11,str);

			str.Format("%d",scase.GetStotaltime());

			m_ScaseList.SetItemText(index,12,str);

            index++;//下标加1
		}
	}

}

//从dataOper.sCaseList中查出所要的病例
SCase CSASView::GetScaseBySid(int sid)
{
	SCase scase;//病例信息实例

	scase.SetSid(-1);//默认sid为负1，标志未查到相应信息

	POSITION pos = dataOper.sCaseList.GetHeadPosition();//获得第一条数据

	while(pos != NULL)
	{
       scase = dataOper.sCaseList.GetNext(pos);//获得数据项

	   if(scase.GetSid() == sid)
	   {
          break;//如果相等跳出循环
	   }
	}

	return scase;
}

//删除当前病例信息
void CSASView::OnDelete() 
{

  if(m_Sid > 0)
	{
	   dataOper.DeleteSCaseBySid(m_Sid);//删除数据库中病患的基本信息

       dataFile.DeleteDatas(m_Sid);//删除当前选中项中的病例文件

	   eventOper.DeleteEvents(m_Sid);//删除当前选中项中的事件文件

	   this->RefreshList();//更新病患信息列表


	   //更新数据显示
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

	   UpdateData(0);//更新当前选中病例信息

	   AfxMessageBox("病例信息已经成功删除!");
 
	}
	else
	{
		AfxMessageBox("请选择病例后再进行此操作!");
	}
 
}

//图形颜色设置
void CSASView::OnColorset() 
{
   SetColor SetDialog;
   
   SetDialog.DoModal();
  
}


//增益文字设置
void CSASView::OnWordandspeed() 
{
  SetConfig config;
 	
  config.DoModal();//显示配置窗体
}

void CSASView::OnItemchangedPlist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	*pResult = 0;

	if(this->m_ScaseList.GetSelectedCount() > 0)
	{
		
		int itemIndex = this->m_ScaseList.GetSelectionMark();//获得选中的下标
		
		int sid  = atoi(this->m_ScaseList.GetItemText(itemIndex,0));//获得病例编号
		
		//SCaseData dataOper;
		
		SCase scase = GetScaseBySid(sid);//获得病例信息
		
		this->m_Sid = scase.GetSid();
		
		//留待改进如何判断编码
		CString sname1 = scase.GetSName().Left(2);
		
		CString sname2 = scase.GetSName().Right(scase.GetSName().GetLength() - 2);
		
		this->m_Sname1 = sname1;
		
		this->m_Sname2 = sname2;
		
		this->m_Sage = scase.GetSage();//获得年龄
		
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
		
		this->m_Stotaltime = scase.GetStotaltime();//获得总时间
		
		UpdateData(0);
		
		
	}
		 
}

void CSASView::OnPadw() 
{
	UpdateData(1);

	CString str;

	this->GetDlgItemText(IDC_PADW,str);//获得当前按钮提示

	if(str == "便笺锁定")
	{

		this->GetDlgItem(IDC_PADR)->EnableWindow(FALSE);
		
		this->GetDlgItem(IDC_PAD)->EnableWindow(FALSE);

		this->SetDlgItemText(IDC_PADW,"便笺解锁");

	}
	else
	{

		this->GetDlgItem(IDC_PADR)->EnableWindow(TRUE);
		
		this->GetDlgItem(IDC_PAD)->EnableWindow(TRUE);

		this->SetDlgItemText(IDC_PADW,"便笺锁定");

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
       MessageBox("姓名输入不能为空，请检查！","输入提示");

	   return;
	}
	SCase scase = dataOper.SelectSCaseBySname(m_Sname1 + m_Sname2);//获得病例信息

	if(scase.GetSid() != -1)
	{
	
	this->m_Sid = scase.GetSid();
	
	//留待改进如何判断编码
	CString sname1 = scase.GetSName().Left(2);
	
	CString sname2 = scase.GetSName().Right(scase.GetSName().GetLength() - 2);
	
	this->m_Sname1 = sname1;
	
	this->m_Sname2 = sname2;
	
	this->m_Sage = scase.GetSage();//获得年龄
	
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
	
	this->m_Stotaltime = scase.GetStotaltime();//获得总时间
	
	UpdateData(0);
	}
	else
	{
		MessageBox("此病例不存在！","操作提示");
	}
		
}
