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
	this->parent = parent;//��ø����������


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
//�����¼��б�
BOOL SEventList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//��ʼ���¼���
	m_ImageList.Create(16,16,0,8,8);

	hIcon = ::AfxGetApp()->LoadIcon(IDI_ICONE);//����ͼ��

	m_ImageList.Add(hIcon);//��ӵ�ͼ���б���

	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_EVENTTREE);//�����¼���

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

	//��ʾ��һ��

	this->tvInsert.item.pszText = "�¼�����";

	this->tvInsert.item.iImage = 0;

	this->tvInsert.item.iSelectedImage = 0;

	hDad = pTree->InsertItem(&this->tvInsert);

	//�������

	this->tvInsert.hParent = hDad;//���ø���

	this->tvInsert.item.iImage = 0;

	this->tvInsert.item.iSelectedImage = 0;

	this->tvInsert.item.pszText = "������ͣ�¼�";

	pTree->InsertItem(&this->tvInsert);//�����


	this->tvInsert.item.pszText = "��ͨ���¼�";

	pTree->InsertItem(&this->tvInsert);//�����


	this->tvInsert.item.pszText = "�����¼�";

	pTree->InsertItem(&this->tvInsert);//�����



    //���Ի��¼���

	//��ʼ���¼��б�
	//��ò���������ʾ
	m_EventList.InsertColumn(0,"�¼����");
	m_EventList.InsertColumn(1,"�¼�����");
	m_EventList.InsertColumn(2,"��ʼʱ��");
	m_EventList.InsertColumn(3,"����ʱ��");
	m_EventList.InsertColumn(4,"��Ƿ�ʽ");


	m_EventList.SetColumnWidth(0,80);
	m_EventList.SetColumnWidth(1,80);
	m_EventList.SetColumnWidth(2,150);
	m_EventList.SetColumnWidth(3,150);
	m_EventList.SetColumnWidth(4,80);


	m_EventList.SetExtendedStyle(LVS_EX_FULLROWSELECT);//����ѡ��ȫ��
	//��ʼ���¼��б�

	this->RefreshEventList(0);//Ĭ����ʾ�����¼��б�
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//���ٴ���

BOOL SEventList::DestroyWindow() 
{
	
	return CDialog::DestroyWindow();
}

//�����¼�����ˢ��������ʾ
void SEventList::RefreshEventList(int nParam)
{
    m_EventList.DeleteAllItems();//����¼��б�����������

    POSITION pos = parent->eventOper.sEventList.GetHeadPosition();//��õ�һ������

    ANLEVENT event;//�¼��������ձ���������

	CString str = "";//��ʱ�������ݵı���

	int index = 0;

	switch(nParam)
	{
	case 0:
			while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//���������

			  str.Format("%d_%d",index,event.nID);

			  m_EventList.InsertItem(index,str);//�����

			  str.Format("%d",event.nID);

			  m_EventList.SetItemText(index,0,str);//��ӱ��

			  if(event.nParam == 1)
			  {
                str = "������ͣ";
			  }
			  else if(event.nParam == 2)
			  {
                str = "��ͨ��";
			  }
			  else if(event.nParam == 3)
			  {
				 str = "����";
			  }
			  else
			  {
				  str = "�����¼�";
			  }

		      m_EventList.SetItemText(index,1,str);//����¼�����

			  str = GetTimeString(event.nBeginTime);//��ÿ�ʼʱ��

              m_EventList.SetItemText(index,2,str);

			  str = GetTimeString(event.nEndTime);//��ý���ʱ��

			  m_EventList.SetItemText(index,3,str);

			  str = event.bAuto?"�Զ�":"�ֶ�";

			  m_EventList.SetItemText(index,4,str);//��ʾ��Ƿ�ʽ

			  index++;

			}

		break;
	case 1:
		
		    while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//���������


			  if(event.nParam == 1)
			  {

				  str.Format("%d_%d",index,event.nID);
	
				  m_EventList.InsertItem(index,str);//�����

				  str.Format("%d",event.nID);

				  m_EventList.SetItemText(index,0,str);//��ӱ��

	              str = "������ͣ";
				
			      m_EventList.SetItemText(index,1,str);//����¼�����
	
				  str = GetTimeString(event.nBeginTime);//��ÿ�ʼʱ��

	              m_EventList.SetItemText(index,2,str);
	
	 			  str = GetTimeString(event.nEndTime);//��ý���ʱ��

				  m_EventList.SetItemText(index,3,str);
	
				  str = event.bAuto?"�Զ�":"�ֶ�";

				  m_EventList.SetItemText(index,4,str);//��ʾ��Ƿ�ʽ

				  index++;
			  }

			}

		break;
	case 2:

		    while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//���������


			  if(event.nParam == 2)
			  {

				  str.Format("%d_%d",index,event.nID);
	
				  m_EventList.InsertItem(index,str);//�����

				  str.Format("%d",event.nID);

				  m_EventList.SetItemText(index,0,str);//��ӱ��

	              str = "��ͨ��";
				
			      m_EventList.SetItemText(index,1,str);//����¼�����
	
				  str = GetTimeString(event.nBeginTime);//��ÿ�ʼʱ��

	              m_EventList.SetItemText(index,2,str);
	
	 			  str = GetTimeString(event.nEndTime);//��ý���ʱ��

				  m_EventList.SetItemText(index,3,str);
	
				  str = event.bAuto?"�Զ�":"�ֶ�";

				  m_EventList.SetItemText(index,4,str);//��ʾ��Ƿ�ʽ

				  index++;
			  }

			}
		break;
	case 3:

		    while(pos != NULL)
			{
		      event = parent->eventOper.sEventList.GetNext(pos);//���������


			  if(event.nParam == 3)
			  {

				  str.Format("%d_%d",index,event.nID);
	
				  m_EventList.InsertItem(index,str);//�����

				  str.Format("%d",event.nID);

				  m_EventList.SetItemText(index,0,str);//��ӱ��

	              str = "����";
				
			      m_EventList.SetItemText(index,1,str);//����¼�����
	
				  str = GetTimeString(event.nBeginTime);//��ÿ�ʼʱ��

	              m_EventList.SetItemText(index,2,str);
	
	 			  str = GetTimeString(event.nEndTime);//��ý���ʱ��

				  m_EventList.SetItemText(index,3,str);
	
				  str = event.bAuto?"�Զ�":"�ֶ�";

				  m_EventList.SetItemText(index,4,str);//��ʾ��Ƿ�ʽ

				  index++;
			  }

			}
		break;
	}
	return;
}
//�����ʾѡ�е��¼�
void SEventList::OnClickEventlist(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;

	 POSITION pos = parent->eventOper.sEventList.GetHeadPosition();//��õ�һ������

     ANLEVENT event;//�¼��������ձ���������


	if(this->m_EventList.GetSelectedCount() > 0)
	{
	
		int itemIndex = this->m_EventList.GetSelectionMark();//���ѡ�е��±�

		int nID = atoi(this->m_EventList.GetItemText(itemIndex,0));//��ò������

	 	while(pos != NULL)
		{
		   event = parent->eventOper.sEventList.GetNext(pos);//���������

		   if(event.nID == nID)
		   {
               int position = this->parent->GetShowPosition(event.nBeginTime,this->parent->sconfig.wSpeed);//�����ʾ����
               
			   this->parent->FindEvent(position);//��ʾѡ���¼�

			   break;//������ִ�г�������
		   }
		}

	 
	}
}

CString SEventList::GetTimeString(int position)
{
	CString tbShowString = "";//Ĭ��Ϊ��

    int realPosition = position;//����¼���ʼ�±�

	int dataCount = realPosition + 1;//��¼��ʼ����ǰ��������

    int day = 0;

	int hour = 0;

	int minute = 0;

	int second = 0;

	if(dataCount > 0)
	{
		int totalSec = dataCount/50;//���������

	    day = ((totalSec/60)/60)/24;
        hour = ((totalSec/60)/60)%24;
		minute = (totalSec/60)%60;
		second = totalSec%60;

		//���ʱ�䳬����ʮ����Ͱ��㴦��
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
				  parent->scase.GetSstartdate().GetSecond() + second);//ʵ����



    tbShowString.Format("%d-%d-%d  %d:%d:%d",enddate.GetYear(),enddate.GetMonth(),
		enddate.GetDay(),enddate.GetHour(),enddate.GetMinute(),enddate.GetSecond());
		       
	return tbShowString;//����ʱ���ַ���
}

//ѡ���¼���ʾ
void SEventList::OnSelchangedEventtree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CTreeCtrl* pTree = (CTreeCtrl*)GetDlgItem(IDC_EVENTTREE);//�����¼���

	CString str = pTree->GetItemText(pNMTreeView->itemNew.hItem);
	
	*pResult = 0;

	if(str == "�¼�����")
	{
	  this->RefreshEventList(0);//Ĭ����ʾ�����¼��б�
	}
	else if(str == "������ͣ�¼�")
	{
	  this->RefreshEventList(1);//Ĭ����ʾ�����¼��б�
	}
	else if(str == "��ͨ���¼�")
	{
	  this->RefreshEventList(2);//Ĭ����ʾ�����¼��б�
	}
	else if(str == "�����¼�")
	{
	  this->RefreshEventList(3);//Ĭ����ʾ�����¼��б�
	}

}
