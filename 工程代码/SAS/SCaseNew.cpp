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

//病例导入
void SCaseNew::OnImport() 
{
	UpdateData(1);//写回变量


	if(m_Sname1.IsEmpty()||m_Sname2.IsEmpty())
	{
		MessageBox("患者名称不能为空，请检查！","输入提示");

		return;
	}

	if(m_Sfilepath.IsEmpty())
	{
		MessageBox("患者病例文件不存在，请检查！","输入提示");
		
		return;
	}
		

	CString name = m_Sname1 + m_Sname2;//获得姓名

	CTime Sstartdate(m_Sstartdate1.GetYear(),m_Sstartdate1.GetMonth(),m_Sstartdate1.GetDay(),
		m_Sstartdate2.GetHour(),m_Sstartdate2.GetMinute(),m_Sstartdate2.GetSecond());//获得开始时间

    SCase scase;

	scase.SetSName(name);//设置姓名
	scase.SetSbirthday(m_Sbirthday);//设置生日
	scase.SetSsex(m_Ssex);//设置性别
	scase.SetShigh(m_Shigh);//设置身高
	scase.SetSweight(m_Sweight);//设置体重
	scase.SetSstartdate(Sstartdate);//设置开始时间
    scase.SetScomment(m_Scomment);//设置备注
	scase.SetSdiagnosis(m_Sdiagnosis);//设置诊断医生
	scase.SetSrecord(m_Srecord);//设置记录医生

    SCaseData dataOper;//实例数据库操作类

	SCaseFile fileOper;//实例文件操作类

	int sid = -1;
	if((sid=dataOper.InsertSCase(scase)) > -1)//插入病例
    {
		if(fileOper.CopyDatas(sid,m_Sfilepath))
		{
           AfxMessageBox("病人数据导入成功!");
		}
		else
		{
			dataOper.DeleteSCaseBySid(sid);//删除数据库中的病例信息
			AfxMessageBox("由于文件的原因病例数据导入失败!");
		}
		
	}
	else
	{
		AfxMessageBox("由于数据库的原因病人数据导入失败!");
	}

	CDialog::OnOK();//关闭当前窗体
	UpdateData(0);//写回试图
}

//打开文件对话框
void SCaseNew::OnFilescan() 
{
	UpdateData(1);//写回控件变量

	char sfile[] = "病例文件(*.dt)|*.dt";//文件过滤器

	CFileDialog dlg(TRUE,"dt","",OFN_ALLOWMULTISELECT,sfile);//对话框对象

	if(dlg.DoModal())
	{
		m_Sfilepath = dlg.GetPathName();//获得文件完整路径

		UpdateData(0);//写回控件
	}

}
