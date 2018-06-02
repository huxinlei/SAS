// SEventList.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SEventList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SEventList dialog


SEventList::SEventList(SCaseDisplay* parent,CWnd* pParent)
	: CDialog(SEventList::IDD, pParent)
{
	this->parent = parent;//获得父窗体的引用


	//{{AFX_DATA_INIT(SEventList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SEventList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SEventList)
	DDX_Control(pDX, IDC_EVENTLIST, m_EventList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SEventList, CDialog)
	//{{AFX_MSG_MAP(SEventList)
	ON_NOTIFY(NM_CLICK, IDC_EVENTLIST, OnClickEventlist)
	ON_NOTIFY(TVN_SELCHANGED, IDC_EVENTTREE, OnSelchangedEventtree)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SEventList message handlers
//设置事件列表
BOOL SEventList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//初始化事件树
	m_ImageList.Create(16,16,0,8,8);

	hIcon = ::AfxGetApp()->LoadIcon(IDI_ICONE);//加载图标

	m_ImageList.Add(hIcon);//添加到图像列表中

	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_EVENTTREE);//加载事件树

	pTree->SetImageList(&m_ImageList,TVSIL_NORMAL);

	this->tvInsert.hParent = NULL;

	this->tvInsert.hInsertAfter = TVI_LAST;

	this->tvInsert.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;

	this->tvInsert.item.hItem = NULL;

	this->tvInsert.item.state = 0;

	this->tvInsert.item.stateMask = 0;

	this->tvInsert.item.cchTextMax = 6;

	this->tvInsert.item.iSelectedImage = 1;

	this->tvInsert.item.cChildren = 0;

	this->tvInsert.item.lParam = 0;

	//显示第一层

	this->tvInsert.item.pszText = "事件类型";

	this->tvInsert.item.iImage = 0;

	this->tvInsert.item.iSelectedImage = 0;

	hDad = pTree->InsertItem(&this->tvInsert);

	//添加子项

	this->tvInsert.hParent = hDad;//设置父项

	this->tvInsert.item.iImage = 0;

	this->tvInsert.item.iSelectedImage = 0;

	this->tvInsert.item.pszText = "呼吸暂停事件";

	pTree->InsertItem(&this->tvInsert);//添加项


	this->tvInsert.item.pszText = "低通气事件";

	pTree->InsertItem(&this->tvInsert);//添加项


	this->tvInsert.item.pszText = "氧减事件";

	pTree->InsertItem(&this->tvInsert);//添加项



    //初试化事件树

	//初始化事件列表
	//获得病例数据显示
	m_EventList.InsertColumn(0,"事件编号");
	m_EventList.InsertColumn(1,"事件类型");
	m_EventList.InsertColumn(2,"开始时间");
	m_EventList.InsertColumn(3,"结束时间");
	m_EventList.InsertColumn(4,"标记方式");


	m_EventList.SetColumnWidth(0,80);
	m_EventList.SetColumnWidth(1,80);
	m_EventList.SetColumnWidth(2,150);
	m_EventList.SetColumnWidth(3,150);
	m_EventList.SetColumnWidth(4,80);


	m_EventList.SetExtendedStyle(LVS_EX_FULLROWSELECT);//设置选中全行
	//初始化事件列表

	this->RefreshEventList(0);//默认显示所有事件列表
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//销毁窗口

BOOL SEventList::DestroyWindow() 
{
	
	return CDialog::DestroyWindow();
}

//根据事件类型刷新数据显示
void SEventList::RefreshEventList(int nParam)
{
    m_EventList.DeleteAllItems();//清空事件列表中所有数据

    POSITION pos = parent->eventOper.sEventList.GetHeadPosition();//获得第一条数据

    ANLEVENT event;//事件用来接收遍历的数据

	CString str = "";//临时处理数据的变量

	int index = 0;

	switch(nParam)
	{
	case 0:
			while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//获得数据项

			  str.Format("%d_%d",index,event.nID);

			  m_EventList.InsertItem(index,str);//添加项

			  str.Format("%d",event.nID);

			  m_EventList.SetItemText(index,0,str);//添加编号

			  if(event.nParam == 1)
			  {
                str = "呼吸暂停";
			  }
			  else if(event.nParam == 2)
			  {
                str = "低通气";
			  }
			  else if(event.nParam == 3)
			  {
				 str = "氧减";
			  }
			  else
			  {
				  str = "其它事件";
			  }

		      m_EventList.SetItemText(index,1,str);//添加事件类型

			  str = GetTimeString(event.nBeginTime);//获得开始时间

              m_EventList.SetItemText(index,2,str);

			  str = GetTimeString(event.nEndTime);//获得结束时间

			  m_EventList.SetItemText(index,3,str);

			  str = event.bAuto?"自动":"手动";

			  m_EventList.SetItemText(index,4,str);//显示标记方式

			  index++;

			}

		break;
	case 1:
		
		    while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//获得数据项


			  if(event.nParam == 1)
			  {

				  str.Format("%d_%d",index,event.nID);
	
				  m_EventList.InsertItem(index,str);//添加项

				  str.Format("%d",event.nID);

				  m_EventList.SetItemText(index,0,str);//添加编号

	              str = "呼吸暂停";
				
			      m_EventList.SetItemText(index,1,str);//添加事件类型
	
				  str = GetTimeString(event.nBeginTime);//获得开始时间

	              m_EventList.SetItemText(index,2,str);
	
	 			  str = GetTimeString(event.nEndTime);//获得结束时间

				  m_EventList.SetItemText(index,3,str);
	
				  str = event.bAuto?"自动":"手动";

				  m_EventList.SetItemText(index,4,str);//显示标记方式

				  index++;
			  }

			}

		break;
	case 2:

		    while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//获得数据项


			  if(event.nParam == 2)
			  {

				  str.Format("%d_%d",index,event.nID);
	
				  m_EventList.InsertItem(index,str);//添加项

				  str.Format("%d",event.nID);

				  m_EventList.SetItemText(index,0,str);//添加编号

	              str = "低通气";
				
			      m_EventList.SetItemText(index,1,str);//添加事件类型
	
				  str = GetTimeString(event.nBeginTime);//获得开始时间

	              m_EventList.SetItemText(index,2,str);
	
	 			  str = GetTimeString(event.nEndTime);//获得结束时间

				  m_EventList.SetItemText(index,3,str);
	
				  str = event.bAuto?"自动":"手动";

				  m_EventList.SetItemText(index,4,str);//显示标记方式

				  index++;
			  }

			}
		break;
	case 3:

		    while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//获得数据项


			  if(event.nParam == 3)
			  {

				  str.Format("%d_%d",index,event.nID);
	
				  m_EventList.InsertItem(index,str);//添加项

				  str.Format("%d",event.nID);

				  m_EventList.SetItemText(index,0,str);//添加编号

	              str = "氧减";
				
			      m_EventList.SetItemText(index,1,str);//添加事件类型
	
				  str = GetTimeString(event.nBeginTime);//获得开始时间

	              m_EventList.SetItemText(index,2,str);
	
	 			  str = GetTimeString(event.nEndTime);//获得结束时间

				  m_EventList.SetItemText(index,3,str);
	
				  str = event.bAuto?"自动":"手动";

				  m_EventList.SetItemText(index,4,str);//显示标记方式

				  index++;
			  }

			}
		break;
	}
	return;
}
//点击显示选中的事件
void SEventList::OnClickEventlist(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;

	 POSITION pos = parent->eventOper.sEventList.GetHeadPosition();//获得第一条数据

     ANLEVENT event;//事件用来接收遍历的数据


	if(this->m_EventList.GetSelectedCount() > 0)
	{
	
		int itemIndex = this->m_EventList.GetSelectionMark();//获得选中的下标

		int nID = atoi(this->m_EventList.GetItemText(itemIndex,0));//获得病例编号

	 	while(pos != NULL)
		{
		   event = parent->eventOper.sEventList.GetNext(pos);//获得数据项

		   if(event.nID == nID)
		   {
               int position = this->parent->GetShowPosition(event.nBeginTime,this->parent->sconfig.wSpeed);//获得显示坐标
               
			   this->parent->FindEvent(position);//显示选中事件

			   break;//如果相等执行程序后结束
		   }
		}

	 
	}
}

CString SEventList::GetTimeString(int position)
{
	CString tbShowString = "";//默认为空

    int realPosition = position;//获得事件开始下标

	int dataCount = realPosition + 1;//记录开始到当前总数据量

    int day = 0;

	int hour = 0;

	int minute = 0;

	int second = 0;

	if(dataCount > 0)
	{
		int totalSec = dataCount/50;//获得总秒数

	    day = ((totalSec/60)/60)/24;
        hour = ((totalSec/60)/60)%24;
		minute = (totalSec/60)%60;
		second = totalSec%60;

		//如果时间超过二十八天就按零处理
		if(day>28)
		{
			day = 0;
			hour = 0;
			minute = 0;
			second = 0;
		}
	}

	CTime enddate(
		          parent->scase.GetSstartdate().GetYear(),
				  parent->scase.GetSstartdate().GetMonth(),
		          parent->scase.GetSstartdate().GetDay() + day,
		          parent->scase.GetSstartdate().GetHour() + hour,
		          parent->scase.GetSstartdate().GetMinute() + minute,
				  parent->scase.GetSstartdate().GetSecond() + second);//实例化



    tbShowString.Format("%d-%d-%d  %d:%d:%d",enddate.GetYear(),enddate.GetMonth(),
		enddate.GetDay(),enddate.GetHour(),enddate.GetMinute(),enddate.GetSecond());
		       
	return tbShowString;//返回时间字符串
}

//选择事件显示
void SEventList::OnSelchangedEventtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_EVENTTREE);//加载事件树

	CString str = pTree->GetItemText(pNMTreeView->itemNew.hItem);
	
	*pResult = 0;

	if(str == "事件类型")
	{
	  this->RefreshEventList(0);//默认显示所有事件列表
	}
	else if(str == "呼吸暂停事件")
	{
	  this->RefreshEventList(1);//默认显示所有事件列表
	}
	else if(str == "低通气事件")
	{
	  this->RefreshEventList(2);//默认显示所有事件列表
	}
	else if(str == "氧减事件")
	{
	  this->RefreshEventList(3);//默认显示所有事件列表
	}

}
