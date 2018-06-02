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

	this->parent = parent;//获得父类的引用

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
	
    POSITION pos = parent->eventOper.sEventList.GetHeadPosition();//获得第一条数据

    ANLEVENT event;//事件用来接收遍历的数据

	CString str = "";//临时处理数据的变量

	int apneaC = 0;//呼吸暂停事件个数

	int descendC = 0;//氧减事件个数

	int hypopC = 0;//低通气事件个数

	int maxAID = -1;//最长呼吸暂停事件编号

	int maxHID = -1;//最长低通气事件编号

	int maxAT = 0;//默认呼吸暂停最长时间为0

	int maxHT = 0;//默认低通气最长时间为0


	while(pos != NULL)
	{
	   event = parent->eventOper.sEventList.GetNext(pos);//获得数据项

	   if(event.nParam == 1)
	   {
		   apneaC ++;//呼吸暂停事件加1

		   if((event.nEndTime - event.nBeginTime) > maxAT)
		   {
			   maxAT = event.nEndTime - event.nBeginTime;

			   maxAID = event.nID;//获得时间最长的呼吸暂停事件编号
		   }
	   }

	   if(event.nParam == 2)
	   {
		   hypopC ++;//低通气事件加1

		   if((event.nEndTime - event.nBeginTime) > maxHT)
		   {
			   maxHT = event.nEndTime - event.nBeginTime;

			   maxHID = event.nID;//获得时间最长的低通气事件编号
		   }
	   }

	   if(event.nParam == 3)
	   {
		   descendC++;//氧减事件加一
	   }

	}

	str.Format("%d",apneaC);//获得呼吸暂停的个数

	m_ApneaC = "呼吸暂停总个数:" + str;

	str.Format("%d",hypopC);//获得低通气总个数

	m_HypopC = "低通气总个数:" + str;

	str.Format("%d",descendC);//获得氧减总个数

	m_DescendC = "氧减总个数:" + str;


	double apneaI = apneaC * 60.0 / this->parent->scase.GetStotaltime();//获得呼吸暂停的指数

	str.Format("%0.4f",apneaI);

	m_ApneaI = "呼吸暂停指数:" + str;

	double hypopI = hypopC * 60.0 / this->parent->scase.GetStotaltime();//获得低通气的指数
	
	str.Format("%0.4f",hypopI);

	m_HypopI = "低通气指数:" + str;

	double descendI = descendC * 60.0 / this->parent->scase.GetStotaltime();//获得氧减指数

	str.Format("%0.4f",descendI);

	m_DescendI = "氧减指数:" + str;


    if(maxAID == -1)
	{
      str = "无";
	}
	else
	{
	  str.Format("%d",maxAID);//呼吸暂停最长编号
	}

	m_MaxA = "呼吸暂停最长的事件编号为:" + str;

    if(maxHID == -1)
	{
      str = "无";
	}
	else
	{
	  str.Format("%d",maxHID);//呼吸暂停最长编号
	}

	m_MaxH = "低通气最长的事件编号为:" + str;



	UpdateData(0);//写回屏幕*/

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SResultDialog::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
		
    CDC * pDC = m_Spo2.GetDC();

    CRect clientRect;

    m_Spo2.GetClientRect(&clientRect);//实际可画区域大小


	pDC->SetMapMode(MM_TEXT);//设置显示模式为像素

    pDC->SetBkMode(TRANSPARENT);//透明

    CPen pen;

	pen.CreatePen(PS_SOLID,1,RGB(255,0,0));

    CPen *oldPen = pDC->SelectObject(&pen);//修改画笔

//	pDC->MoveTo(clientRect.top,clientRect.left);

//	pDC->LineTo(clientRect.right,clientRect.bottom);
 
    int realWidth = clientRect.right - 2 * leftWidth - 1;//获得宽度实际可用的像素点

	int realHight = clientRect.bottom - bottomWidth - 5;//获得高度实际可用的像素点

	//显示竖直提示信息
	CFont myFont;//创建字体对象
	myFont.CreateFont(10,15,2700,0,5,FALSE,FALSE,FALSE,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY,DEFAULT_PITCH,"newFont");

	CFont *pOldFont = pDC->SelectObject(&myFont);

	pDC->TextOut(0,0,"血氧分布图");

	pDC->SelectObject(pOldFont);

	myFont.DeleteObject();//删除字体对象



	//显示竖直提示信息


	int realX = 2 * leftWidth + 1;//画图起始坐标x

	int realY = 5;//画图起始坐标y
 
	int segHight = realHight / 5;

	int drawHight = 5 * segHight; 

	int segWidth = realWidth / 10;

	int drawWidth = 10 * segWidth;

	//画竖直标记

	pDC->MoveTo(realX,realY);//移到起始点

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


	//画水平标记
	realX = 2 * leftWidth + 1 + 5;//画图起始坐标x

    realY = realY + drawHight;//获得水平y值

    pDC->MoveTo(realX,realY);//移到起始点

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
		  pDC->TextOut(realX + ix * segWidth - 30,realY,"55下");
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

	int seg50 = 0;//记录55以下的数据总数

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
    
	//画血氧第一个图
    int drawY = drawHight - seg95 * drawHight / this->parent->sdata.length;

	CRect r95(realX,drawY + 5,realX + segWidth,realY);

	pDC->Rectangle(r95);

	//90以上95以下

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
