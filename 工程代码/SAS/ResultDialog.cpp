// ResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "ResultDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ResultDialog dialog


ResultDialog::ResultDialog(SCaseDisplay *parent,CWnd* pParent /*=NULL*/)
	: CDialog(ResultDialog::IDD, pParent)
{
	this->parent = parent;//��ø��������

	this->leftWidth = 30;

	this->bottomWidth = 30;
	//{{AFX_DATA_INIT(ResultDialog)
	m_ApneaC = _T("");
	m_ApneaI = _T("");
	m_DescendC = _T("");
	m_DescendI = _T("");
	m_HypopC = _T("");
	m_HypopI = _T("");
	m_MaxA = _T("");
	m_MaxH = _T("");
	//}}AFX_DATA_INIT
}


void ResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ResultDialog)
	DDX_Control(pDX, IDC_SPO2SHOW, m_Spo2);
	DDX_Text(pDX, IDC_APNEAC, m_ApneaC);
	DDX_Text(pDX, IDC_APNEAI, m_ApneaI);
	DDX_Text(pDX, IDC_DESCENDC, m_DescendC);
	DDX_Text(pDX, IDC_DESCENDI, m_DescendI);
	DDX_Text(pDX, IDC_HYPOPC, m_HypopC);
	DDX_Text(pDX, IDC_HYPOPI, m_HypopI);
	DDX_Text(pDX, IDC_MAXA, m_MaxA);
	DDX_Text(pDX, IDC_MAXH, m_MaxH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ResultDialog, CDialog)
	//{{AFX_MSG_MAP(ResultDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ResultDialog message handlers

//��ʼ����ʾ�¼�ͳ����Ϣ
BOOL ResultDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    POSITION pos = parent->eventOper.sEventList.GetHeadPosition();//��õ�һ������

    ANLEVENT event;//�¼��������ձ���������

	CString str = "";//��ʱ�������ݵı���

	int apneaC = 0;//������ͣ�¼�����

	int descendC = 0;//�����¼�����

	int hypopC = 0;//��ͨ���¼�����

	int maxAID = -1;//�������ͣ�¼����

	int maxHID = -1;//���ͨ���¼����

	int maxAT = 0;//Ĭ�Ϻ�����ͣ�ʱ��Ϊ0

	int maxHT = 0;//Ĭ�ϵ�ͨ���ʱ��Ϊ0


	while(pos != NULL)
	{
	   event = parent->eventOper.sEventList.GetNext(pos);//���������

	   if(event.nParam == 1)
	   {
		   apneaC ++;//������ͣ�¼���1

		   if((event.nEndTime - event.nBeginTime) > maxAT)
		   {
			   maxAT = event.nEndTime - event.nBeginTime;

			   maxAID = event.nID;//���ʱ����ĺ�����ͣ�¼����
		   }
	   }

	   if(event.nParam == 2)
	   {
		   hypopC ++;//��ͨ���¼���1

		   if((event.nEndTime - event.nBeginTime) > maxHT)
		   {
			   maxHT = event.nEndTime - event.nBeginTime;

			   maxHID = event.nID;//���ʱ����ĵ�ͨ���¼����
		   }
	   }

	   if(event.nParam == 3)
	   {
		   descendC++;//�����¼���һ
	   }

	}

	str.Format("%d",apneaC);//��ú�����ͣ�ĸ���

	m_ApneaC = "������ͣ�ܸ���:" + str;

	str.Format("%d",hypopC);//��õ�ͨ���ܸ���

	m_HypopC = "��ͨ���ܸ���:" + str;

	str.Format("%d",descendC);//��������ܸ���

	m_DescendC = "�����ܸ���:" + str;


	double apneaI = apneaC * 60.0 / this->parent->scase.GetStotaltime();//��ú�����ͣ��ָ��

	str.Format("%0.4f",apneaI);

	m_ApneaI = "������ָͣ��:" + str;

	double hypopI = hypopC * 60.0 / this->parent->scase.GetStotaltime();//��õ�ͨ����ָ��
	
	str.Format("%0.4f",hypopI);

	m_HypopI = "��ͨ��ָ��:" + str;

	double descendI = descendC * 60.0 / this->parent->scase.GetStotaltime();//�������ָ��

	str.Format("%0.4f",descendI);

	m_DescendI = "����ָ��:" + str;


    if(maxAID == -1)
	{
      str = "��";
	}
	else
	{
	  str.Format("%d",maxAID);//������ͣ����
	}

	m_MaxA = "������ͣ����¼����Ϊ:" + str;

    if(maxHID == -1)
	{
      str = "��";
	}
	else
	{
	  str.Format("%d",maxHID);//������ͣ����
	}

	m_MaxH = "��ͨ������¼����Ϊ:" + str;



	UpdateData(0);//д����Ļ*/

	return TRUE; 
}

void ResultDialog::OnPaint() 
{

    CDC * pDC = m_Spo2.GetDC();

    CRect clientRect;

    m_Spo2.GetClientRect(&clientRect);//ʵ�ʿɻ������С


	pDC->SetMapMode(MM_TEXT);//������ʾģʽΪ����

    pDC->SetBkMode(TRANSPARENT);//͸��

    CPen pen;

	pen.CreatePen(PS_SOLID,1,RGB(255,0,0));

    CPen *oldPen = pDC->SelectObject(&pen);//�޸Ļ���

//	pDC->MoveTo(clientRect.top,clientRect.left);

//	pDC->LineTo(clientRect.right,clientRect.bottom);
 
    int realWidth = clientRect.left - 2 * leftWidth - 1;//��ÿ��ʵ�ʿ��õ����ص�

	int realHight = clientRect.bottom - bottomWidth - 5;//��ø߶�ʵ�ʿ��õ����ص�

	int realX = 2 * leftWidth + 1;//��ͼ��ʼ����x

	int realY = 5;//��ͼ��ʼ����y
 
	int segHight = realHight / 5;

	int drawHight = 5 * segHight; 

	int segWidth = realWidth / 10;

	int drawWidth = 10 * segWidth;

	//����ֱ���

	pDC->MoveTo(realX,realY);//�Ƶ���ʼ��

	pDC->LineTo(realX + 5,realY);

	pDC->TextOut(this->leftWidth,realY - 5,"100%");

	for(int iy = 1; iy <= 5; iy++)
	{

      pDC->MoveTo(realX,realY + iy * segHight);

	  pDC->LineTo(realX + 5,realY + iy * segHight);

      switch(iy)
	  {
	  case 1:
		  pDC->TextOut(this->leftWidth,realY + iy * segHight - 5,"80%");
		  break;
	  case 2:
		  pDC->TextOut(this->leftWidth,realY + iy * segHight - 5,"60%");
		  break;
	  case 3:
		  pDC->TextOut(this->leftWidth,realY + iy * segHight - 5,"40%");
		  break;
	  case 4:
		  pDC->TextOut(this->leftWidth,realY + iy * segHight - 5,"20%");
		  break;
	  case 5:
		  pDC->TextOut(this->leftWidth,realY + iy * segHight - 5,"0%");
		  break;
	  }
	}

	pDC->MoveTo(realX + 5,realY);

	pDC->LineTo(realX + 5,realY + drawHight);


	//��ˮƽ���
    realY = realY + drawHight;//���ˮƽyֵ

    pDC->MoveTo(realX,realY);//�Ƶ���ʼ��

	pDC->LineTo(realX,realY - 5);


	pDC->TextOut(realX,realY,"100%");


	m_Spo2.ReleaseDC(pDC);
	
}
