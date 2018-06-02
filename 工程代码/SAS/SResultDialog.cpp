// SResultDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SResultDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SResultDialog dialog


SResultDialog::SResultDialog(SCaseDisplay* parent,CWnd* pParent /*=NULL*/)
	: CDialog(SResultDialog::IDD, pParent)
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


void SResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SResultDialog)
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


BEGIN_MESSAGE_MAP(SResultDialog, CDialog)
	//{{AFX_MSG_MAP(SResultDialog)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SResultDialog message handlers

BOOL SResultDialog::OnInitDialog() 
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

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SResultDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
		
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
 
    int realWidth = clientRect.right - 2 * leftWidth - 1;//��ÿ��ʵ�ʿ��õ����ص�

	int realHight = clientRect.bottom - bottomWidth - 5;//��ø߶�ʵ�ʿ��õ����ص�

	//��ʾ��ֱ��ʾ��Ϣ
	CFont myFont;//�����������
	myFont.CreateFont(10,15,2700,0,5,FALSE,FALSE,FALSE,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH,"newFont");

	CFont *pOldFont = pDC->SelectObject(&myFont);

	pDC->TextOut(0,0,"Ѫ���ֲ�ͼ");

	pDC->SelectObject(pOldFont);

	myFont.DeleteObject();//ɾ���������



	//��ʾ��ֱ��ʾ��Ϣ


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
	realX = 2 * leftWidth + 1 + 5;//��ͼ��ʼ����x

    realY = realY + drawHight;//���ˮƽyֵ

    pDC->MoveTo(realX,realY);//�Ƶ���ʼ��

	pDC->LineTo(realX + drawWidth - 5,realY);


	//pDC->TextOut(realX,realY,"100%");

	for(int ix = 1; ix <= 10; ix++)
	{
      pDC->MoveTo(realX + ix * segWidth - 5,realY - 5);

	  pDC->LineTo(realX + ix * segWidth - 5,realY);

	  switch(ix)
	  {
	  case 1:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"95");
		  break;
	  case 2:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"90");
		  break;
	  case 3:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"85");
		  break;
	  case 4:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"80");
		  break;
	  case 5:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"75");
		  break;
	  case 6:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"70");
		  break;
	  case 7:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"65");
		  break;
	  case 8:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"60");
		  break;
	  case 9:
		  pDC->TextOut(realX + ix * segWidth - 11,realY,"55");
		  break;
	  case 10:
		  pDC->TextOut(realX + ix * segWidth - 30,realY,"55��");
		  break;
	  }
	}

	int seg95 = 0;

	int seg90 = 0;

	int seg85 = 0;

	int seg80 = 0;

	int seg75 = 0;

	int seg70 = 0;

	int seg65 = 0;

	int seg60 = 0;

	int seg55 = 0;

	int seg50 = 0;//��¼55���µ���������

	for(int i = 0; i < this->parent->sdata.length; i++)
	{
		if(this->parent->sdata.datas[i].nSpO2 >= 95)
		{
			seg95++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 90)
		{
			seg90++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 85)
		{
			seg85++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 80)
		{
			seg80++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 75)
		{
			seg75++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 70)
		{
			seg70++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 65)
		{
			seg65++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 60)
		{
			seg60++;
		}
		else if(this->parent->sdata.datas[i].nSpO2 >= 55)
		{
			seg55++;
		}
		else
		{
			seg50++;
		}
	}
    
	//��Ѫ����һ��ͼ
    int drawY = drawHight - seg95 * drawHight / this->parent->sdata.length;

	CRect r95(realX,drawY + 5,realX + segWidth,realY);

	pDC->Rectangle(r95);

	//90����95����

	drawY = drawHight - seg90 * drawHight /  this->parent->sdata.length;

	CRect r90(realX + segWidth,drawY + 5,realX + 2 * segWidth,realY);

	pDC->Rectangle(r90);

	//85

	drawY = drawHight - seg85 * drawHight /  this->parent->sdata.length;

	CRect r85(realX + 2 * segWidth,drawY + 5,realX + 3 * segWidth,realY);

	pDC->Rectangle(r85);

	//80
	drawY = drawHight - seg80 * drawHight /  this->parent->sdata.length;

	CRect r80(realX + 3 * segWidth,drawY + 5,realX + 4 * segWidth,realY);

	pDC->Rectangle(r80);


    //75

	drawY = drawHight - seg75 * drawHight /  this->parent->sdata.length;

	CRect r75(realX + 4 * segWidth,drawY + 5,realX + 5 * segWidth,realY);

	pDC->Rectangle(r75);

	//70

	drawY = drawHight - seg70 * drawHight /  this->parent->sdata.length;

	CRect r70(realX + 5 * segWidth,drawY + 5,realX + 6 * segWidth,realY);

	pDC->Rectangle(r70);

	//65
	drawY = drawHight - seg65 * drawHight /  this->parent->sdata.length;

	CRect r65(realX + 6 * segWidth,drawY + 5,realX + 7 * segWidth,realY);

	pDC->Rectangle(r65);

	//60
	drawY = drawHight - seg60 * drawHight /  this->parent->sdata.length;

	CRect r60(realX + 7 * segWidth,drawY + 5,realX + 8 * segWidth,realY);

	pDC->Rectangle(r60);

	//55
	drawY = drawHight - seg55 * drawHight /  this->parent->sdata.length;

	CRect r55(realX + 8 * segWidth,drawY  + 5,realX + 9 * segWidth,realY);

	pDC->Rectangle(r55);

	//50

	drawY = drawHight - seg50 * drawHight /  this->parent->sdata.length;

	CRect r50(realX + 9 * segWidth,drawY + 5,realX + 10 * segWidth,realY);

	pDC->Rectangle(r50);	


	m_Spo2.ReleaseDC(pDC);
}
