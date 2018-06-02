// SCaseDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SCaseDisplay.h"
#include "TCHAR.H"
#include "SEventList.h"
#include "SResultDialog.h"

#include "gdiplus.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define LINESIZE 20
#define LINESIZE1 40
/////////////////////////////////////////////////////////////////////////////
// SCaseDisplay dialog


SCaseDisplay::SCaseDisplay(SCase scase,CWnd* pParent /*=NULL*/)
	: CDialog(SCaseDisplay::IDD, pParent)
{

  	 this->scase = scase;//获得病例信息

	 this->scase.InitSenddate();

	 this->sdata.InitDatas(scase.GetSid());//初始化病例信息

	 this->eventOper.GetSEventList(scase.GetSid());//病例事件初始化

	 this->position = 0;//默认初始值为0


	 this->curEvent.nID = -1;//设置负一标志当前没有要添加项或者选中项

	 //事件标记操作默认为false
	 this->IAflag = false;

	 this->IHflag = false;

	 this->IDflag = false;

	 this->DEflag = false;

	 this->UPflag = false;

	 //事件标记操作默认为false

	 //事件操作类型默认为没有操作
	 this->eOper = NOOPER;//没有操作

	 this->realTrayHight = 0;//当前段高度初始时默认为0
}


void SCaseDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(SCaseDisplay, CDialog)
	//{{AFX_MSG_MAP(SCaseDisplay)
	ON_WM_INITMENUPOPUP()//相应菜单更新命令
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_WSPEED002, OnWspeed002)
	ON_COMMAND(ID_WSPEED02, OnWspeed02)
	ON_COMMAND(ID_WSPEED1, OnWspeed1)
	ON_COMMAND(ID_WSPEED1M, OnWspeed1m)
	ON_COMMAND(ID_WSPEED2, OnWspeed2)
	ON_UPDATE_COMMAND_UI(ID_WSPEED002, OnUpdateWspeed002)
	ON_UPDATE_COMMAND_UI(ID_WSPEED02, OnUpdateWspeed02)
	ON_UPDATE_COMMAND_UI(ID_WSPEED1, OnUpdateWspeed1)
	ON_UPDATE_COMMAND_UI(ID_WSPEED1M, OnUpdateWspeed1m)
	ON_UPDATE_COMMAND_UI(ID_WSPEED2, OnUpdateWspeed2)
	ON_WM_HSCROLL()
	ON_COMMAND(INSERT_A, OnA)
	ON_COMMAND(DELETE_E, OnE)
	ON_COMMAND(UPDATE_EE, OnUPDATEEE)
	ON_COMMAND(INSERT_D, OnD)
	ON_COMMAND(INSERT_H, OnH)
	ON_COMMAND(EVENT_SHOW, OnShow)
	ON_COMMAND(RESULT_SHOW, OnShowR)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SCaseDisplay message handlers

void SCaseDisplay::OnPaint() 
{
  ////画图程序正式1.0/////////////////////////////////////////
   CPaintDC dcOrigin(this);

   dcOrigin.SetBkColor(sconfig.backC);//设置背景色

   CRect clientRect;

   GetClientRect(&clientRect);//实际可画区域大小

   
   CRect toolRect;//工具条区域所占的区域大小

   this->mToolbar.GetClientRect(&toolRect);

 //  CString tempShow;

 //  tempShow.Format("%d",toolRect.bottom);

//   AfxMessageBox(tempShow);

   int rClientHight = clientRect.bottom - toolRect.bottom;//实际可画的高度

   int rStartPosX = toolRect.left;

   int rStartPosY = toolRect.bottom;

   int rClientWidth = clientRect.right;//实际可画的宽度

   this->realX = sconfig.verticalHintWidth;//获得数据画图的x轴坐标

   this->realY = sconfig.scaseHight + sconfig.horizontalHintHight;//获得数据画图的y轴坐标

   this->realClientHight = rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight;//实际数据显示高度

   this->realClientWidth = rClientWidth - 2 * sconfig.verticalHintWidth;//获得实际数据显示宽度

   this->realDrawCount = (this->GetModeLength(sconfig.wSpeed) - position) > this->realClientWidth ? this->realClientWidth:this->GetModeLength(sconfig.wSpeed) - position;//获得画点的总数


   
   //初始化滚动条
   //////初始化滚动条///////////////////////////////

   if(this->GetModeLength(sconfig.wSpeed) > this->realClientWidth)
   {
   	SCROLLINFO siScroll;

	siScroll.fMask = SIF_RANGE;

	siScroll.nMin = 0;

	int nMaxPos = this->GetModeLength(sconfig.wSpeed) - this->realClientWidth;

	siScroll.nMax = nMaxPos;//数据项长度

    siScroll.nPage = 1;

	siScroll.nPos = this->position;

	SetScrollInfo(SB_HORZ,&siScroll,TRUE);

    //修正画图区域大小
	GetClientRect(&clientRect);//实际可画区域大小

	rClientHight = clientRect.bottom - toolRect.bottom;//实际可画的高度

	rClientWidth = clientRect.right;//实际可画的宽度

    this->realClientHight = rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight;//实际数据显示高度

    this->realClientWidth = rClientWidth - 2 * sconfig.verticalHintWidth;//获得实际数据显示宽度

	this->realDrawCount = (this->GetModeLength(sconfig.wSpeed) - position) > this->realClientWidth ? this->realClientWidth:this->GetModeLength(sconfig.wSpeed) - position;//获得画点的总数

	//修正画图区域大小
   }
   else
   {
   	SCROLLINFO siNull;

	siNull.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	siNull.nMin = 0;

	siNull.nMax = 0;//数据项长度

    siNull.nPage = 1;

	siNull.nPos = this->position;

	SetScrollInfo(SB_HORZ,&siNull,TRUE);
   }
 
   //初始化滚动条

 ////双缓冲技术代码////////////////////////////////////////

//定义一个内存设备描述表对象（即后备缓冲区）
 CDC dc; 

//定义一个位图对象
 CBitmap MemBitmap;
 //建立与屏幕设备描述表（前端缓冲区）兼容的内存设备描述表句柄（后备缓冲区）
 dc.CreateCompatibleDC(NULL);
 //这时还不能绘图，因为没有位图的设备描述表是不能绘图的
 //下面建立一个与屏幕设备描述表（或者内存设备描述表）兼容的位图
 MemBitmap.CreateCompatibleBitmap(&dcOrigin,rClientWidth,rClientHight);
 //将位图选入到内存设备描述表
 //只有选入了位图的设备描述表才有地方绘图，画到指定的位图上
 CBitmap *pOldBit=dc.SelectObject(&MemBitmap);
 //先用背景色将位图清除干净，这里我用的是白色作为背景
 //你也可以用自己应该用的颜色
 dc.FillSolidRect(0,0,rClientWidth,rClientHight,sconfig.backC);

 CPen pen(PS_DOT,1,RGB(255,0,0));

 CPen *oldPen = dc.SelectObject(&pen);//修改画笔
 

   ////双缓冲技术代码/////////////////////////////////////////

   dc.SetMapMode(MM_TEXT);//设置显示模式为像素

   dc.SetBkMode(TRANSPARENT);//透明

   Gdiplus::Graphics g(dc.GetSafeHdc());


   //打印病例信息
   LOGFONT scaseLog = CreateFontBySize(sconfig.scaseWordSize);

   CFont scaseFont;

   scaseFont.CreateFontIndirect(&scaseLog);

   dc.SelectObject(&scaseFont);//选入设备环境

  // dc.SetTextAlign(TA_CENTER);

   dc.SetBkMode(TRANSPARENT);//输出模式

   CRect scaseRect(0,sconfig.scaseSpaceTop,rClientWidth,sconfig.scaseHight - sconfig.scaseSpaceTop);//定义病例信息显示矩形


   dc.DrawText(GetSCaseString(),scaseRect,DT_CENTER);//画病例基本信息提示


   int rStartX = rClientWidth - sconfig.verticalHintWidth;//获得右边工具条的起始x轴坐标

   int trayHight = 100;//tray译文为托盘，托盘高度

   int traySegHight = 100/11;

   trayHight = traySegHight * 11;

   if(sconfig.hGain == 0)//才用自适应模式
   {
     trayHight = this->realClientHight / 4;//初始化四个托盘高度

	 traySegHight = trayHight / 11;

	 trayHight = traySegHight * 11;//通过这两步消除误差，提高显示精度
   }

   this->realTrayHight = trayHight;//当前段高度

   int nFlowCX = 0;//气流x轴的开始坐标

   int nFlowCY = sconfig.horizontalHintHight + sconfig.scaseHight;//气流y轴坐标开始

   int nSpO2CX = 0;
   
   int nSpO2CY = sconfig.horizontalHintHight + sconfig.scaseHight + 1 + trayHight;//血氧饱和度y轴坐标开始

   int nPulseCX = 0;

   int nPulseCY = sconfig.horizontalHintHight + sconfig.scaseHight + 2 + 2 * trayHight;//脉搏y轴坐标开始

   int nPlethCX = 0;

   int nPlethCY = sconfig.horizontalHintHight + sconfig.scaseHight + 3 + 3 * trayHight;//血氧容积y轴坐标开始
   
   //画左右提示工具条

   CPen zeroPen(PS_SOLID,1,sconfig.zeroShaftC);

   dc.SelectObject(zeroPen);

   LOGFONT lrtoolLog = CreateFontBySize(sconfig.rlWordSize);

   CFont lrtoolFont;

   lrtoolFont.CreateFontIndirect(&lrtoolLog);//字体初始化后再次调用CreateFontIndirect()函数出错

   dc.SelectObject(&lrtoolFont);//选入设备环境

   //气流
   for(int nFlowCi = 0; nFlowCi < 11; nFlowCi++)
   {

	  switch(nFlowCi)
	  {
	  case 0:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"500");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"500");
		  break;

	  case 1:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"400");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"400");
		  break;
		  
	  case 2:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"300");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"300");
		  break;

	  case 3:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"200");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"200");
		  break;
	  case 4:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"100");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"100");
		  break;
	  case 5:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"0");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"0");
		  dc.MoveTo(nFlowCX + sconfig.verticalHintWidth,nFlowCY);
		  dc.LineTo(rStartX,nFlowCY);
		  dc.TextOut(nFlowCX + sconfig.verticalHintWidth,nFlowCY - traySegHight + 1,"气流");
		  break;
	  case 6:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"-100");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"-100");
		  break;
	  case 7:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"-200");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"-200");
		  break;
	  case 8:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"-300");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"-300");
		  break;
	  case 9:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"-400");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"-400");
		  break;
	  case 10:
		  dc.TextOut(nFlowCX,nFlowCY - traySegHight + 1,"-500");
		  dc.TextOut(rStartX,nFlowCY - traySegHight + 1,"-500");
		  break;

	  }
      dc.MoveTo(nFlowCX,nFlowCY);

	  dc.LineTo(sconfig.verticalHintWidth,nFlowCY);//左边

	  dc.MoveTo(rStartX,nFlowCY);

	  dc.LineTo(rClientWidth,nFlowCY);//右边

      nFlowCY += traySegHight; 
   }

   //血氧饱和度
   for(int nSpO2Ci = 0;nSpO2Ci < 11; nSpO2Ci++)
   {

	  switch(nSpO2Ci)
	  {
	  case 0:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"100");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"100");
		  break;

	  case 1:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"90");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"90");
		  break;
		  
	  case 2:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"80");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"80");
		  break;

	  case 3:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"70");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"70");
		  break;
	  case 4:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"60");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"60");
		  break;
	  case 5:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"50");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"50");

		  break;
	  case 6:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"40");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"40");
		  break;
	  case 7:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"30");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"30");
		  break;
	  case 8:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"20");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"20");
		  break;
	  case 9:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"10");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"10");
		  break;
	  case 10:
		  dc.TextOut(nSpO2CX,nSpO2CY - traySegHight + 1,"0");
		  dc.TextOut(rStartX,nSpO2CY - traySegHight + 1,"0");

		  dc.MoveTo(nSpO2CX + sconfig.verticalHintWidth,nSpO2CY);
		  dc.LineTo(rStartX,nSpO2CY);

		  dc.TextOut(nSpO2CX + sconfig.verticalHintWidth,nSpO2CY - traySegHight + 1,"血氧饱和度");
		  break;

	  }
      dc.MoveTo(nSpO2CX,nSpO2CY);

	  dc.LineTo(sconfig.verticalHintWidth,nSpO2CY);//左边

	  dc.MoveTo(rStartX,nSpO2CY);

	  dc.LineTo(rClientWidth,nSpO2CY);//右边

      nSpO2CY += traySegHight; 
   }

   //脉搏
   for(int nPulseCi = 0;nPulseCi < 11; nPulseCi++)
   {

	  switch(nPulseCi)
	  {
	  case 0:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"100");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"100");
		  break;

	  case 1:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"90");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"90");
		  break;
		  
	  case 2:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"80");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"80");
		  break;

	  case 3:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"70");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"70");
		  break;
	  case 4:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"60");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"60");
		  break;
	  case 5:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"50");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"50");

		  break;
	  case 6:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"40");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"40");
		  break;
	  case 7:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"30");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"30");
		  break;
	  case 8:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"20");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"20");
		  break;
	  case 9:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"10");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"10");
		  break;
	  case 10:
		  dc.TextOut(nPulseCX,nPulseCY - traySegHight + 1,"0");
		  dc.TextOut(rStartX,nPulseCY - traySegHight + 1,"0");

		  dc.MoveTo(nPulseCX + sconfig.verticalHintWidth,nPulseCY);
		  dc.LineTo(rStartX,nPulseCY);

		  dc.TextOut(nPulseCX + sconfig.verticalHintWidth,nPulseCY - traySegHight + 1,"脉率");
		  break;

	  }

      dc.MoveTo(nPulseCX,nPulseCY);

	  dc.LineTo(sconfig.verticalHintWidth,nPulseCY);//左边

	  dc.MoveTo(rStartX,nPulseCY);

	  dc.LineTo(rClientWidth,nPulseCY);//右边

      nPulseCY += traySegHight; 
   }

   //血氧容积
   for(int nPlethCi = 0;nPlethCi < 11; nPlethCi++)
   {

	  switch(nPlethCi)
	  {
	  case 0:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"100");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"100");
		  break;

	  case 1:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"90");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"90");
		  break;
		  
	  case 2:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"80");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"80");
		  break;

	  case 3:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"70");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"70");
		  break;
	  case 4:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"60");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"60");
		  break;
	  case 5:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"50");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"50");

		  break;
	  case 6:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"40");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"40");
		  break;
	  case 7:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"30");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"30");
		  break;
	  case 8:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"20");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"20");
		  break;
	  case 9:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"10");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"10");
		  break;
	  case 10:
		  dc.TextOut(nPlethCX,nPlethCY - traySegHight + 1,"0");
		  dc.TextOut(rStartX,nPlethCY - traySegHight + 1,"0");

		  dc.MoveTo(nPlethCX + sconfig.verticalHintWidth,nPlethCY);
		  dc.LineTo(rStartX,nPlethCY);

		  dc.TextOut(nPlethCX + sconfig.verticalHintWidth,nPlethCY - traySegHight + 1,"血氧容积波");
		  break;
	  }

      dc.MoveTo(nPlethCX,nPlethCY);

	  dc.LineTo(sconfig.verticalHintWidth,nPlethCY);//左边

	  dc.MoveTo(rStartX,nPlethCY);

	  dc.LineTo(rClientWidth,nPlethCY);//右边

      nPlethCY += traySegHight; 
   }

   //画间隔线

   CPen intervalPen(PS_DOT,1,sconfig.intervalC);//设置画笔颜色

   dc.SelectObject(&intervalPen);//设置画笔颜色



   int intervalCount = this->realClientWidth / sconfig.hInterval - 1;//获得可画间隔线个数

   for(int intervali = 1; intervali <= intervalCount;intervali++)
   {
      int intervalX = this->realX + intervali * sconfig.hInterval;//获得x坐标

	  int intervalY1 = this->realY;//获得起点y坐标

	  int intervalY2 = this->realY + this->realClientHight;//获得终点y坐标

	  dc.MoveTo(intervalX,intervalY1);//移动起点

	  dc.LineTo(intervalX,intervalY2);//画线到终点
   }

   //画间隔线
   
   
   //画左右提示工具条


   //////病例数据显示/////////////////////////////////////////////

  //如果相应模式的数据点等于0则不再显示病例数据线
  if(this->GetModeLength(sconfig.wSpeed) > 0)
  {
   //画病例数据线
   int realPosition = 0;//获得实际下标值

   int changePos = this->position;//获得数据当前下标

   //气流
   nFlowCX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);
 
   nFlowCY = this->realY + 5 * traySegHight + (((-sdata.datas[realPosition].nFlow) * traySegHight*5) / 500);

   CPen nFlowPen(PS_SOLID,1,sconfig.nFlowC);

   oldPen = dc.SelectObject(&nFlowPen);//设置画笔颜色

   dc.MoveTo(nFlowCX,nFlowCY);

   for(int fi = 1; fi < this->realDrawCount;fi++)
   {
	 changePos++;

	 nFlowCX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

     nFlowCY = this->realY + 5 * traySegHight + (((-sdata.datas[realPosition].nFlow) * traySegHight*5) / 500);

	 dc.LineTo(nFlowCX,nFlowCY);

   }

    //血氧饱和度

   changePos = this->position;

   nSpO2CX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

   nSpO2CY = this->realY + 2 * trayHight - traySegHight - (sdata.datas[realPosition].nSpO2 * 10 * traySegHight  / 100);

   CPen nSpO2Pen(PS_SOLID,1,sconfig.nSpO2C);

   oldPen = dc.SelectObject(&nSpO2Pen);//设置画笔颜色

   dc.MoveTo(nSpO2CX,nSpO2CY);

   for(int si = 1; si < this->realDrawCount;si++)
   {
	 changePos++;

	 nSpO2CX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

     nSpO2CY = this->realY + 2 * trayHight - traySegHight - (sdata.datas[realPosition].nSpO2 * 10 * traySegHight  / 100);

	 dc.LineTo(nSpO2CX,nSpO2CY);

   }


   //脉搏

   changePos = this->position;

   nPulseCX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

   nPulseCY = this->realY + 3 * trayHight - traySegHight - (sdata.datas[realPosition].nPulse * 10 * traySegHight  / 100);

   CPen nPulsePen(PS_SOLID,1,sconfig.nPulseC);

   oldPen = dc.SelectObject(&nPulsePen);//设置画笔颜色

   dc.MoveTo(nPulseCX,nPulseCY);

   for(int pi = 1; pi < this->realDrawCount;pi++)
   {
	 changePos++;

	 nPulseCX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

     nPulseCY = this->realY + 3 * trayHight - traySegHight - (sdata.datas[realPosition].nPulse * 10 * traySegHight / 100);

	 dc.LineTo(nPulseCX,nPulseCY);
   }

   //血氧容积

   changePos = this->position;

   nPlethCX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

   nPlethCY = this->realY + 4 * trayHight - traySegHight - (sdata.datas[realPosition].nPleth * 10 * traySegHight / 100);

   CPen nPlethPen(PS_SOLID,1,sconfig.nPlethC);

   oldPen = dc.SelectObject(&nPlethPen);//设置画笔颜色

   dc.MoveTo(nPlethCX,nPlethCY);

   for(int pli = 1; pli < this->realDrawCount;pli++)
   {
	 changePos++;

	 nPlethCX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//获得实际下标值

     nPlethCY = this->realY + 4 * trayHight - traySegHight - (sdata.datas[realPosition].nPleth * 10 * traySegHight / 100);

	 dc.LineTo(nPlethCX,nPlethCY);
   }

   //画病例数据线

   //画上下时间刻度提示符
    int TopX = sconfig.verticalHintWidth;//top条x轴的开始坐标

    int TopY = sconfig.scaseHight;//top条y轴坐标开始

    int BottomX = sconfig.verticalHintWidth;//bottom条x轴开始坐标

	int BottomY = sconfig.scaseHight + sconfig.horizontalHintHight + this->realClientHight;//bottom条y轴开始坐标 

    LOGFONT tbtoolLog = CreateFontBySize(sconfig.tbWordSize);

    CFont tbtoolFont;

    tbtoolFont.CreateFontIndirect(&tbtoolLog);//字体初始化后再次调用CreateFontIndirect()函数出错

    dc.SelectObject(&tbtoolFont);//选入设备环境

	int strCount = this->realDrawCount/sconfig.hInterval;//画时间的个数

   for(int stri = 1; stri <= strCount;stri++)
   {
	   CString drawStr1 = GetTBMDString(this->position + stri * sconfig.hInterval);//获得当前点的月日串
	   CString drawStr2 = GetTBHMSString(this->position + stri * sconfig.hInterval);//获得当前点的时间字符串

	   TopX = sconfig.verticalHintWidth + ((2*stri - 1) * sconfig.hInterval)/2; //(stri-1)*sconfig.hInterval + 

	   BottomX = TopX;

	   dc.TextOut(TopX,TopY,drawStr1);//月日串信息

	   dc.TextOut(BottomX,BottomY,drawStr1);//月日串信息
       
       dc.TextOut(TopX,TopY + sconfig.tbWordHighSpace,drawStr2);//画病例基本时间信息提示
 
       dc.TextOut(BottomX,BottomY + sconfig.tbWordHighSpace,drawStr2);//画病例基本时间信息提示
   }

   
   //画上下时间刻度提示符
 }

   //////病例数据显示/////////////////////////////////////////////

   ////////////////事件显示////////////////////////////////////////

    POSITION pos = eventOper.sEventList.GetHeadPosition();//获得第一条数据

	ANLEVENT event;//事件用来接收遍历的数据

	int eventSX = this->realX;//开始x轴坐标

	int eventSY = this->realY;//开始y轴坐标

    Gdiplus::Color colorE(192, 0, 0, 128);//事件默认的颜色

	Gdiplus::SolidBrush eventBrush(colorE);

	//初始化呼吸暂停事件颜色
	BYTE AR = GetRValue(sconfig.apneaB);
	
	BYTE AG = GetGValue(sconfig.apneaB);

	BYTE AB = GetBValue(sconfig.apneaB);

	Gdiplus::Color colorA(192, AR, AG, AB);//事件默认的颜色



	//初始化低通气事件颜色

    BYTE HR = GetRValue(sconfig.hypopneaB);
	
	BYTE HG = GetGValue(sconfig.hypopneaB);

	BYTE HB = GetBValue(sconfig.hypopneaB);

	Gdiplus::Color colorH(192, HR, HG, HB);//事件默认的颜色



	//初始化氧减事件颜色
	BYTE DR = GetRValue(sconfig.descendB);
	
	BYTE DG = GetGValue(sconfig.descendB);

	BYTE DB = GetBValue(sconfig.descendB);

	Gdiplus::Color colorD(192, DR, DG, DB);//事件默认的颜色



	//当前事件id不为-1时画当前事件
	if(curEvent.nID != -1 && this->eOper != UPDATEE)
	{
		   int beginCurModeP = this->GetShowPosition(curEvent.nBeginTime,sconfig.wSpeed);//获得当前模式下的开始坐标

	       int endCurModeP = this->GetShowPosition(curEvent.nEndTime,sconfig.wSpeed);//获得当前模式下的结束坐标

		   switch(curEvent.nParam)
		   {
		   case 1:
			   eventSY = this->realY + 1;//获得y轴坐标

               eventBrush.SetColor(colorA);//设置呼吸暂停事件

			   break;

		   case 2:
			   eventSY = this->realY + 1;//获得y轴坐标


               eventBrush.SetColor(colorH);//设置呼吸暂停事件

			   break;

		   case 3:
			   eventSY = this->realY + trayHight + 1;//获得y轴坐标


               eventBrush.SetColor(colorD);//设置呼吸暂停事件

			   break;
		   }
	      
     
		   Gdiplus::Rect eventCurRect(eventSX + (beginCurModeP - this->position),eventSY,endCurModeP - beginCurModeP,trayHight - sconfig.eventHightSpace);//画事件

           g.FillRectangle(&eventBrush,eventCurRect);

	}


	//事件画图
	while(pos != NULL)
	{
       event = eventOper.sEventList.GetNext(pos);//获得数据项

	   int beginModeP = this->GetShowPosition(event.nBeginTime,sconfig.wSpeed);//获得当前模式下的开始坐标

	   int endModeP = this->GetShowPosition(event.nEndTime,sconfig.wSpeed);//获得当前模式下的结束坐标

	   if(beginModeP < this->position)
	   {
		   beginModeP = this->position;
	   }

	   if(beginModeP > (this->position + this->realDrawCount))
	   {
           beginModeP = this->position + this->realDrawCount;
	   }

	   if(endModeP < this->position)
	   {
		   endModeP = this->position;
	   }

	   if(endModeP > (this->position + this->realDrawCount))
	   {
           endModeP = this->position + this->realDrawCount;
	   }
	   
	   if((beginModeP >= this->position) && (beginModeP != endModeP) && (endModeP <= (this->position + this->realDrawCount)))
	   {
      
		   switch(event.nParam)
		   {
		   case 1:
			   eventSY = this->realY + 1;//获得y轴坐标

               eventBrush.SetColor(colorA);//设置呼吸暂停事件

			   break;

		   case 2:
			   eventSY = this->realY + 1;//获得y轴坐标


               eventBrush.SetColor(colorH);//设置呼吸暂停事件

			   break;

		   case 3:
			   eventSY = this->realY + trayHight + 1;//获得y轴坐标


               eventBrush.SetColor(colorD);//设置呼吸暂停事件

			   break;
		   }
	      
     
		   Gdiplus::Rect eventRect(eventSX + (beginModeP - this->position),eventSY,endModeP - beginModeP,trayHight - sconfig.eventHightSpace);//画事件


		   g.FillRectangle(&eventBrush,eventRect);

	   }

	  
	}
	
   ////////////////事件显示////////////////////////////////////////

 

   Gdiplus::SolidBrush sBrush(sconfig.sColor);
 
   Gdiplus::Rect horizontalHintSCaseTop(0,0,rClientWidth,sconfig.scaseHight);
		
   g.FillRectangle(&sBrush,horizontalHintSCaseTop);//画信息提示条，显示病例信息


 

   Gdiplus::SolidBrush hBrush(sconfig.hColor);


   Gdiplus::Rect horizontalHintTop(0,sconfig.scaseHight,rClientWidth,sconfig.horizontalHintHight);
		
   g.FillRectangle(&hBrush,horizontalHintTop);//画顶层信息提示条,显示时间提示信息


   Gdiplus::Rect horizontalHintBottom(0,rClientHight - sconfig.horizontalHintHight,rClientWidth,sconfig.horizontalHintHight);

   g.FillRectangle(&hBrush,horizontalHintBottom);//画底层信息提示条，显示时间提示信息


   Gdiplus::SolidBrush vBrush(sconfig.vColor);

   Gdiplus::Rect verticalHintLeft(0,sconfig.horizontalHintHight + sconfig.scaseHight,
	   sconfig.verticalHintWidth,rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight);

   g.FillRectangle(&vBrush,verticalHintLeft);//画左边信息提示条，显示幅度信息


   Gdiplus::Rect verticalHintRight(rClientWidth - sconfig.verticalHintWidth,sconfig.horizontalHintHight + sconfig.scaseHight,
	   sconfig.verticalHintWidth,rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight);

   g.FillRectangle(&vBrush,verticalHintRight);//画右边信息提示条，显示幅度信息




   int drawX = sconfig.horizontalHintHight + 1;//画病例信息起始x轴坐标

   int drawY = sconfig.scaseHight + sconfig.horizontalHintHight + 1;//画病例信息起始y轴坐标

   int drawHight = rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight;//获得病例信息画图的总宽度

   int drawWidth = rClientWidth - 2 * sconfig.verticalHintWidth;//获得病例信息画图的总长度



   //dcOrigin.Rectangle(rStartPosX,rStartPosY,200,200);
   //dcOrigin.SetMapMode(MM_TEXT);//设置显示模式为像素

   ////////////事件显示代码////////////////////////////////////////////////////////	
  //将后备缓冲区中的图形拷贝到前端缓冲区
  dcOrigin.BitBlt(rStartPosX,rStartPosY,rClientWidth,rClientHight,&dc,0,0,SRCCOPY);
  //绘图完成后的清理
  MemBitmap.DeleteObject();

  dc.DeleteDC();


}


void SCaseDisplay::OnMouseMove(UINT nFlags, CPoint point) 
{

	if(!this->IAflag)
		return ;
	ANLEVENT event;//定义事件

    event = this->curEvent;//获得当前事件

    int beginX = 0;

    int beginY = 0;

	int endX = 0;

	int endY = 0;

	int posBeginX = this->realX;//起始位置

	int curPos = 0;//当前位置下标为0

	HCURSOR myCursor;//定义鼠标图标对象

    switch(eOper)
	{
	case INSERTAE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

		  this->curEvent = event;//事件标记

	      Invalidate();//更新显示

		}

		break;

	case INSERTHE://低通气事件
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

		  this->curEvent = event;//事件标记


	      Invalidate();//更新显示

		}

		break;
	case INSERTDE:

		beginX = this->realX;

		beginY = this->realY + this->realTrayHight;//y坐标的开始位置

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;//y坐标的结束位置

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

		  this->curEvent = event;//事件标记

	      Invalidate();//更新显示
		}

		break;
	case DELETEE:



		if((point.x > this->realX) && (point.x < (this->realX + this->realClientWidth))&&(point.y >this->realY)&&(point.y < (this->realY + this->realClientHight)))
		{
  		    myCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	
	        this->SetCapture();

	        SetCursor(myCursor);//设置鼠标

		}
		else
		{
            ReleaseCapture();//释放鼠标，还原初试状态
		}
		break;
	case UPDATEE:
	    beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;

		//判断更改事件是否已经开始
		if(!this->IHflag)
		{

			 if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
			 {
		          this->curEvent = GetEventByPoint(point);//获得当前是不是存在修改事件
		
			   if(this->curEvent.nID != -1)
			   {
		          myCursor = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	
	              this->SetCapture();

	              SetCursor(myCursor);//设置鼠标

				  this->IDflag = true;//标记可以开始修改事件
			   }
			   else
			   {
			      ReleaseCapture();//释放鼠标，还原初试状态

				  this->IDflag = false;//标记不可以开始修改事件
			   }
			 }
		}
		else
		{
			
			if(this->curEvent.nParam != 3)
			{
				//呼吸暂停、低通气事件修改处理代码
		        beginX = this->realX;

				beginY = this->realY;
		
				endX = this->realX + this->realClientWidth;

				endY = this->realY + this->realTrayHight;

				if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
				{
				  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

				  if(this->curEvent.bAuto)
				  {
					  //修改事件结尾
					  this->curEvent.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

					  this->UpdateEventByNid(this->curEvent);//更新当前修改事件
				  }
				  else
				  {
					  //修改时间
					  this->curEvent.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

					  this->UpdateEventByNid(this->curEvent);//更新当前修改事件
				  }
		
				}


			    Invalidate();//更新显示

			}
			else
			{
			   //氧减事件修改处理代码
		        beginX = this->realX;

				beginY = this->realY + this->realTrayHight;
		
				endX = this->realX + this->realClientWidth;

				endY = this->realY + 2 * this->realTrayHight;

				if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
				{
				  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

				  if(this->curEvent.bAuto)
				  {
					  //修改事件结尾
					  this->curEvent.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

					  this->UpdateEventByNid(this->curEvent);//更新当前修改事件
				  }
				  else
				  {
					  //修改时间
					  this->curEvent.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标

					  this->UpdateEventByNid(this->curEvent);//更新当前修改事件
				  }
		
				}


			    Invalidate();//更新显示


			}

		}

		break;

	case NOOPER:
		break;
	}

	CDialog::OnMouseMove(nFlags, point);
}

//不刷新背景事件
BOOL SCaseDisplay::OnEraseBkgnd(CDC* pDC)
{
 // TODO: 在此添加消息处理程序代码和/或调用默认值
 //return CDialog::OnEraseBkgnd(pDC);
 return FALSE;
}


//初试化菜单
BOOL SCaseDisplay::OnInitDialog() 
{
	CDialog::OnInitDialog();

    menu.LoadMenu(IDR_MENUPOP);//加载菜单资源

	////设置窗口最大化////////////////////////////////////////////////////
     SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),0); 

    ////设置窗口最大化////////////////////////////////////////////////////
//CBRS_SIZE_DYNAMIC

	 //设置显示工具条

  	if (!mToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_SIZE_DYNAMIC) ||
		!mToolbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	EnableToolTips(TRUE);//显示提示信息

	mToolbar.SetSizes(CSize(68,42),CSize(60,17));

	mToolbar.SetButtonText(0,_T("呼吸暂停"));

	mToolbar.SetButtonText(1,_T("氧减"));

	mToolbar.SetButtonText(2,_T("低通气"));

	mToolbar.SetButtonText(3,_T("事件删除"));

	mToolbar.SetButtonText(4,_T("事件修改"));

	mToolbar.SetButtonText(5,_T("事件统计"));

	mToolbar.SetButtonText(6,_T("事件列表"));

	mToolbar.EnableToolTips(TRUE);

	mToolbar.ShowWindow(SW_SHOW);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_FIRST,0);//AFX_IDW_CONTROLBAR_LAST,0);

	//设置显示工具条
	
	return TRUE;  

}


//鼠标按下时添加事件开始
void SCaseDisplay::OnLButtonDown(UINT nFlags, CPoint point) 
{
    ANLEVENT event;//定义事件

	event.nID = -1;

	event.nBeginTime = 0;

	event.nEndTime = 0;

    int beginX = 0;

    int beginY = 0;

	int endX = 0;

	int endY = 0;

	int posBeginX = this->realX;//起始位置

	int curPos = 0;//当前位置下标为0

	
	switch(eOper)
	{
	case INSERTAE://呼吸暂停事件

        beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
          event.bAuto = false;//标记是手动标记事件

		  event.nParam = 1;//标记为呼吸暂停事件

		  event.nID = eventOper.sEventList.GetCount() + 1;//事件标记

		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//获得时间在数组中的下标

		  event.nEndTime = event.nBeginTime;//事件的结束坐标默认和开始坐标一致

		}
        
		this->IAflag = true;

		this->curEvent = event;//获得当前添加的事件

		break;
	case INSERTHE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
          event.bAuto = false;//标记是手动标记事件

		  event.nParam = 2;//标记为呼吸暂停事件

		  event.nID = eventOper.sEventList.GetCount() + 1;//事件标记

		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//获得时间在数组中的下标

		  event.nEndTime = event.nBeginTime;//事件的结束坐标默认和开始坐标一致

		}
        
		this->IAflag = true;

		this->curEvent = event;//获得当前添加的事件

		break;
	case INSERTDE://氧减事件

		beginX = this->realX;

		beginY = this->realY + this->realTrayHight;//y坐标的开始位置

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;//y坐标的结束位置

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
          event.bAuto = false;//标记是手动标记事件

		  event.nParam = 3;//标记为呼吸暂停事件

		  event.nID = eventOper.sEventList.GetCount() + 1;//事件标记

		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//获得时间在数组中的下标

		  event.nEndTime = event.nBeginTime;//事件的结束坐标默认和开始坐标一致

		}
        
		this->IAflag = true;

		this->curEvent = event;//获得当前添加的事件

		break;
	case DELETEE:
		this->IAflag = true;//启动up相应删除事件
		break;
	case UPDATEE:
        if(this->curEvent.nID != -1)//如果当前事件的nID不为负一
		{
			this->IHflag = true;//启动事件修改标记
		}
		else
		{
			this->IHflag = false;//启动事件修改标记
		}
		break;
	case NOOPER:
		break;
	}



	CDialog::OnLButtonDown(nFlags, point);
}

//添加事件结束
void SCaseDisplay::OnLButtonUp(UINT nFlags, CPoint point) 
{ 
	
	if(!this->IAflag)
		return ;
	ANLEVENT event;//定义事件

    event = this->curEvent;//获得当前事件

    int beginX = 0;

    int beginY = 0;

	int endX = 0;

	int endY = 0;

	int posBeginX = this->realX;//起始位置

	int curPos = 0;//当前位置下标为0


	switch(eOper)
	{
	case INSERTAE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标
          
		  if(!CheckEventExist(event))
		  {
		    eventOper.sEventList.AddTail(event);//加入事件列表中

		    eventOper.SaveSEventList(scase.GetSid());//保存一下列表到文件
		  }
		  else
		  {
			  MessageBox("事件不允许存在重叠和嵌套!");
		  }

		  Invalidate();//刷新

		}

		break;
	case INSERTHE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标
          
		  if(!CheckEventExist(event))
		  {
		    eventOper.sEventList.AddTail(event);//加入事件列表中

		    eventOper.SaveSEventList(scase.GetSid());//保存一下列表到文件
		  }
		  else
		  {
			  MessageBox("事件不允许存在重叠和嵌套!");
		  }

		  Invalidate();//刷新

		}
		break;
	case INSERTDE:
		beginX = this->realX;

		beginY = this->realY + this->realTrayHight;//y坐标的开始位置

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;//y坐标的结束位置

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//获得在当前显示下的坐标点

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//获得结束下标
          
		  if(!CheckEventExist(event))
		  {

		    eventOper.sEventList.AddTail(event);//加入事件列表中

		    eventOper.SaveSEventList(scase.GetSid());//保存一下列表到文件
		  }
		  else
		  {
			  MessageBox("事件不允许存在重叠和嵌套!");
		  }

		  Invalidate();//刷新

		}

		break;
	case DELETEE:
		if((point.x > this->realX) && (point.x < (this->realX + this->realClientWidth)))
		{
           DeleteEventByPoint(point);//调用删除事件程序

		   Invalidate();//刷新

		}

		ReleaseCapture();//释放鼠标，还原初试状态
		break;
	case UPDATEE:

		if(this->IHflag)//标记事件开始修改
		{
			this->curEvent.bAuto = false;//使事件标记重新归为手动

            this->UpdateEventByNid(this->curEvent);//更新当前修改事件

		    eventOper.SaveSEventList(this->scase.GetSid());//保存文件

			ReleaseCapture();//释放鼠标，还原初试状态

		    this->IDflag = false;//标记不可以开始修改事件

			Invalidate();//刷新
		}

		break;
	case NOOPER:
		break;
	}

	this->curEvent.nID = -1;//当前事件项标号置一

	eOper = NOOPER;//重置为没有操作

	this->IAflag = false;//事件操作结束标记

	this->IHflag = false;



   CDialog::OnLButtonUp(nFlags, point);
}

//窗体销毁时菜单处理
void SCaseDisplay::OnDestroy() 
{
	menu.DestroyMenu();//销毁菜单

	CDialog::OnDestroy();	
}


//右键菜单命令
void SCaseDisplay::OnRButtonDown(UINT nFlags, CPoint point) 
{
   menuPop = menu.GetSubMenu(0);//得到子菜单

   ClientToScreen(&point);//客户坐标转换成屏幕坐标

   menuPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);//弹出菜单

   CDialog::OnRButtonDown(nFlags, point);
}

//根据传入字体的大小创建相应字体
LOGFONT SCaseDisplay::CreateFontBySize(int size)
{
   LOGFONT log;//结构体变量

   //属性设置
   log.lfCharSet = ANSI_CHARSET;

   log.lfClipPrecision = 23;//字体的裁剪精度

   log.lfEscapement = 0;//字体相对于x轴的倾斜度为0

   log.lfHeight = size;//字体的高度为50

   strcpy(log.lfFaceName,"新建字体");//字体名称

   log.lfItalic = 0;//0表示非斜体

   log.lfOrientation = 900;//字体基准线与x轴之间的夹角

   log.lfOutPrecision = 90;//字体的输出精度

   log.lfPitchAndFamily = 0;//字符间距

   log.lfQuality = 90;//字体的输出质量

   log.lfUnderline = 0;//无下划线

   log.lfStrikeOut = 0;//无删除线

   return log;//返回新建的字体

}

//获得病例提示信息字符串
CString SCaseDisplay::GetSCaseString()
{

   CString scaseText = "开始记录时间:" + scase.GetSstartdate().Format("%y-%m-%d %H:%M:%S");

   scaseText += "         ";

   CString temp;//临时处理数据显示

   temp = "病患姓名:" + scase.GetSName();

   scaseText += temp;

   temp = scase.GetSsex() == 2?"未填":(scase.GetSsex() == 0?"男":"女");

   scaseText += "  ";

   temp = "性别:" + temp;

   scaseText +=  temp;

   scaseText += "  ";

   temp.Format("%d",scase.GetSage());

   scaseText += "年龄:" + temp + "岁";

   scaseText += "         ";

   temp =  "结束记录时间:" + scase.GetSenddate().Format("%y-%m-%d %H:%M:%S");

   scaseText += temp;

   return scaseText;
}

//根据模式设置获得实际可以显示的数据量
int SCaseDisplay::GetModeLength(WSpeed wSpeed)
{
	int result = -1;
//WSPEED002,WSPEED02,WSPEED1,WSPEED2,WSPEED1M
	switch(wSpeed)
	{
	   case WSPEED002:
		   result = sdata.length;//0.02s
		   break;
	   case WSPEED02:
		   result = sdata.length / 10;//0.2s
		   break;
	   case WSPEED1:
		   result = sdata.length / 50;//1s
		   break;
	   case WSPEED2:
		   result = sdata.length / 100;//2s
		   break;
	   case WSPEED1M:
		   result = sdata.length / 3000;//1m
		   break;

	}

	return result;//返回实际可以显示的数据量
}

//根据当前下标位置和模式获得实际下标
int SCaseDisplay::GetRealIndex(int position,WSpeed wSpeed)
{
   int realPosition = -1;//默认负一

   switch(wSpeed)
   {
   case WSPEED002:
	   realPosition = position;//0.02s
	   break;
   case WSPEED02:
	   realPosition = position * 10;//0.2s
	   break;
   case WSPEED1:
	   realPosition = position * 50;//1s
	   break;
   case WSPEED2:
	   realPosition = position * 100;//2s
	   break;
   case WSPEED1M:
	   realPosition = position * 3000;//1m
   }
   return realPosition;
}
//根据当前实际坐标转换成相应模式下的显示下标
int SCaseDisplay::GetShowPosition(int realPosition,WSpeed wSpeed)
{
   int position = -1;//默认负一

   switch(wSpeed)
   {
   case WSPEED002:
	   position = realPosition;//0.02s
	   break;
   case WSPEED02:
	   position = realPosition / 10;//0.2s
	   break;
   case WSPEED1:
	   position = realPosition / 50;//1s
	   break;
   case WSPEED2:
	   position = realPosition / 100;//2s
	   break;
   case WSPEED1M:
	   position = realPosition / 3000;//1m
   }
   return position;
}

//根据当前位置生成时间字符串
CString SCaseDisplay::GetTBHMSString(int position)
{
	CString tbShowString = "";//默认为空

    int realPosition = this->GetRealIndex(position,sconfig.wSpeed);

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
		          this->scase.GetSstartdate().GetYear(),
				  this->scase.GetSstartdate().GetMonth(),
		          this->scase.GetSstartdate().GetDay() + day,
		          this->scase.GetSstartdate().GetHour() + hour,
		          this->scase.GetSstartdate().GetMinute() + minute,
				  this->scase.GetSstartdate().GetSecond() + second);//实例化


    tbShowString.Format("  %d:%d:%d",enddate.GetHour(),enddate.GetMinute(),enddate.GetSecond());
		       
	return tbShowString;//返回时间字符串
}


//根据生成月日显示字符串
CString SCaseDisplay::GetTBMDString(int position)
{
	CString tbShowString = "";//默认为空

    int realPosition = this->GetRealIndex(position,sconfig.wSpeed);

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
		          this->scase.GetSstartdate().GetYear(),
				  this->scase.GetSstartdate().GetMonth(),
		          this->scase.GetSstartdate().GetDay() + day,
		          this->scase.GetSstartdate().GetHour() + hour,
		          this->scase.GetSstartdate().GetMinute() + minute,
				  this->scase.GetSstartdate().GetSecond() + second);//实例化


    tbShowString.Format("    %d-%d  ",enddate.GetMonth(),enddate.GetDay());
		       
	return tbShowString;//返回时间字符串
}

bool SCaseDisplay::CheckEventExist(ANLEVENT preEvent)
{
	bool rFlag = false;//默认结果不存在

	POSITION pos = eventOper.sEventList.GetHeadPosition();//获得第一条数据

	ANLEVENT event;//事件用来接收遍历的数据

    while(pos != NULL)
	{
       event = eventOper.sEventList.GetNext(pos);//获得数据项

	   if(event.nParam == preEvent.nParam)//类型一致时再进行检查
	   {
		   if((event.nBeginTime <= preEvent.nBeginTime && preEvent.nBeginTime <= event.nEndTime) || 
			   (event.nBeginTime <= preEvent.nEndTime && preEvent.nEndTime <= event.nEndTime))
		   {
			   rFlag = true;//事件存在重叠和嵌套

			   break;
		   }
	   }

	}

	return rFlag;//事件存在标记
}

bool SCaseDisplay::DeleteEventByPoint(CPoint point)
{
	bool rFlag = false;//默认设置为假

	POSITION pos = eventOper.sEventList.GetHeadPosition();//获得第一条数据

	ANLEVENT event;//事件用来接收遍历的数据

	int ahBeginY = this->realY + 1;//设置呼吸暂停和低通气y轴开始坐标

	int ahEndY = this->realY + 1 + this->realTrayHight - sconfig.eventHightSpace;//设置呼吸暂停和低通气y轴结束坐标

	int dBeginY = this->realY + this->realTrayHight + 1;//设置氧减事件y轴的开始坐标

	int dEndY = this->realY + 2* this->realTrayHight + 1 - sconfig.eventHightSpace;//设置氧减事件y轴的结束坐标

	int changePos = (point.x - this->realX) + this->position;

	int curIndex = this->GetRealIndex(changePos,sconfig.wSpeed);//获得当前点的position值

    while(pos != NULL)
	{

	   POSITION  curPos = pos;//获得当前指针位置

       event = eventOper.sEventList.GetNext(pos);//获得数据项

	   if(event.nParam == 3)
	   {

		   if((event.nBeginTime <= curIndex && curIndex <= event.nEndTime) &&
			   (dBeginY <= point.y && point.y <= dEndY))
		   {
			   eventOper.sEventList.RemoveAt(curPos);//删除当前事件

		       eventOper.SaveSEventList(scase.GetSid());//保存一下列表到文件

			   rFlag = true;//标记删除成功

			   break;
		   }
	   }
	   else
	   {
		   if((event.nBeginTime <= curIndex && curIndex <= event.nEndTime) &&
			   (ahBeginY <= point.y && point.y <= ahEndY))
		   {
			   eventOper.sEventList.RemoveAt(curPos);//删除当前事件

		       eventOper.SaveSEventList(scase.GetSid());//保存一下列表到文件

			   rFlag = true;//标记删除成功

			   break;
		   }
	   }

	}

	
    UpdateEventNid();//更新数据编号

	return rFlag;//表示没有删除任何项
}

//更新事件
bool SCaseDisplay::UpdateEventByNid(ANLEVENT event)
{
	bool rFlag = false;//默认更新失败


	POSITION pos = eventOper.sEventList.GetHeadPosition();//获得第一条数据


    while(pos != NULL)
	{
      POSITION curPos = pos;//获得当前为位置

      ANLEVENT selEvent = eventOper.sEventList.GetNext(pos);//事件

      if(event.nID == selEvent.nID)//判断当前是不是要更新的项
	  {
		if(event.nBeginTime == selEvent.nBeginTime && event.nEndTime <= selEvent.nBeginTime)
		{
			rFlag = false;//更新失败

			break;
		}
		 
		if(event.nEndTime == selEvent.nEndTime && event.nBeginTime >= selEvent.nEndTime)
		{
		   rFlag = false;//更新失败

			break;
		}

         eventOper.sEventList.GetAt(curPos).nBeginTime = event.nBeginTime;

		 eventOper.sEventList.GetAt(curPos).nEndTime = event.nEndTime;

		 eventOper.sEventList.GetAt(curPos).bAuto = event.bAuto;

		 eventOper.sEventList.GetAt(curPos).nParam = event.nParam;

		 eventOper.sEventList.GetAt(curPos).nID = event.nID;

		 rFlag = true;//事件更新成功

		 break;//结束循环
	  }

	}

	return rFlag;//返回更新结果

}

//根据传过来的点坐标查找事件，未找到则设置事件的nID为-1
ANLEVENT SCaseDisplay::GetEventByPoint(CPoint point)
{
	POSITION pos = eventOper.sEventList.GetHeadPosition();//获得第一条数据

	ANLEVENT event;//事件用来接收遍历的数据

	ANLEVENT rEvent;//返回结果事件

	rEvent.nID = -1;//默认设置编号为-1

	int ahBeginY = this->realY + 1;//设置呼吸暂停和低通气y轴开始坐标

	int ahEndY = this->realY + 1 + this->realTrayHight - sconfig.eventHightSpace;//设置呼吸暂停和低通气y轴结束坐标

	int dBeginY = this->realY + this->realTrayHight + 1;//设置氧减事件y轴的开始坐标

	int dEndY = this->realY + 2* this->realTrayHight + 1 - sconfig.eventHightSpace;//设置氧减事件y轴的结束坐标

	int changePos = (point.x - this->realX) + this->position;

	int curIndex = this->GetRealIndex(changePos,sconfig.wSpeed);//获得当前点的position值

    while(pos != NULL)
	{

	   POSITION  curPos = pos;//获得当前指针位置

       event = eventOper.sEventList.GetNext(pos);//获得数据项

	   if(event.nParam == 3)
	   {

		   if(((event.nBeginTime-2) <= curIndex && curIndex <= (event.nBeginTime + 2)) &&
			   (dBeginY <= point.y && point.y <= dEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = false;//标记修改数据的开头

			   break;
		   }

		   if(((event.nEndTime - 1) <= curIndex && curIndex <= (event.nEndTime + 1)) &&
			   (dBeginY <= point.y && point.y <= dEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = true;//标记修改数据的结尾

			   break;
		   }
	   }
	   else
	   {
		   if(((event.nBeginTime-2) <= curIndex && curIndex <= (event.nBeginTime + 2)) &&
			   (ahBeginY <= point.y && point.y <= ahEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = false;//标记修改数据的开头

			   break;
		   }

		   if(((event.nEndTime - 1) <= curIndex && curIndex <= (event.nEndTime + 1)) &&
			   (ahBeginY <= point.y && point.y <= ahEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = true;//标记修改数据的结尾

			   break;
		   }
	   }

	}

	return rEvent;//返回查询结果
}

//删除事件时更新事件编号

void SCaseDisplay::UpdateEventNid()
{
    POSITION pos = eventOper.sEventList.GetHeadPosition();//获得第一条数据

    ANLEVENT event;//事件用来接收遍历的数据

    int index = 1;//起始值为1


	while(pos != NULL)
	{
	   POSITION curPos = pos;//获得当前为位置

	   event = eventOper.sEventList.GetNext(pos);//获得数据项

	   event.nID = index;//获得新编号

	   eventOper.sEventList.GetAt(curPos).nID = event.nID;

	   index ++ ;//编号自加
	}
}


//模式设置区

void SCaseDisplay::OnWspeed002() 
{
	this->position = 0;

	sconfig.wSpeed = WSPEED002;

	//消除滚动条的影响
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//数据项长度

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //消除滚动条的影响


	Invalidate();
}

void SCaseDisplay::OnWspeed02() 
{
    this->position = 0;

	//消除滚动条的影响
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//数据项长度

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //消除滚动条的影响


    sconfig.wSpeed = WSPEED02;

	Invalidate();
	
}

void SCaseDisplay::OnWspeed1() 
{

	this->position = 0;

    sconfig.wSpeed = WSPEED1;

	//消除滚动条的影响
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//数据项长度

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //消除滚动条的影响


    Invalidate();
}

void SCaseDisplay::OnWspeed1m() 
{
	this->position = 0;

	//消除滚动条的影响
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//数据项长度

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //消除滚动条的影响


	sconfig.wSpeed = WSPEED1M;

	Invalidate();
	
}

void SCaseDisplay::OnWspeed2() 
{
	this->position = 0;

	//消除滚动条的影响
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//数据项长度

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //消除滚动条的影响


	sconfig.wSpeed = WSPEED2;

    Invalidate();
	
}

void SCaseDisplay::OnUpdateWspeed002(CCmdUI* pCmdUI) 
{
   if(sconfig.wSpeed == WSPEED002)
   {
	   pCmdUI->SetCheck(true);
   }
   else
   {
	   pCmdUI->SetCheck(false);
   }
	
}

void SCaseDisplay::OnUpdateWspeed02(CCmdUI* pCmdUI) 
{
   if(sconfig.wSpeed == WSPEED02)
   {
	   pCmdUI->SetCheck(true);
   }
   else
   {
	   pCmdUI->SetCheck(false);
   }
	
}

void SCaseDisplay::OnUpdateWspeed1(CCmdUI* pCmdUI) 
{
   if(sconfig.wSpeed == WSPEED1)
   {
	   pCmdUI->SetCheck(true);
   }
   else
   {
	   pCmdUI->SetCheck(false);
   }
	
}

void SCaseDisplay::OnUpdateWspeed1m(CCmdUI* pCmdUI) 
{
   if(sconfig.wSpeed == WSPEED1M)
   {
	   pCmdUI->SetCheck(true);
   }
   else
   {
	   pCmdUI->SetCheck(false);
   }	
}

void SCaseDisplay::OnUpdateWspeed2(CCmdUI* pCmdUI) 
{
   if(sconfig.wSpeed == WSPEED2)
   {
	   pCmdUI->SetCheck(true);
   }
   else
   {
	   pCmdUI->SetCheck(false);
   }
	
}


//处理菜单接收状态改变消息
void SCaseDisplay::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{
    ASSERT(pPopupMenu != NULL);
    // Check the enabled state of various menu items.

    CCmdUI state;
    state.m_pMenu = pPopupMenu;
    ASSERT(state.m_pOther == NULL);
    ASSERT(state.m_pParentMenu == NULL);

    // Determine if menu is popup in top-level menu and set m_pOther to
    // it if so (m_pParentMenu == NULL indicates that it is secondary popup).
    HMENU hParentMenu;
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
        state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
    {
        CWnd* pParent = this;
           // Child windows don't have menus--need to go to the top!
        if (pParent != NULL &&
           (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
        {
           int nIndexMax = ::GetMenuItemCount(hParentMenu);
           for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
           {
            if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
            {
                // When popup is found, m_pParentMenu is containing menu.
                state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
                break;
            }
           }
        }
    }

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
      state.m_nIndex++)
    {
        state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
        if (state.m_nID == 0)
           continue; // Menu separator or invalid cmd - ignore it.

        ASSERT(state.m_pOther == NULL);
        ASSERT(state.m_pMenu != NULL);
        if (state.m_nID == (UINT)-1)
        {
           // Possibly a popup menu, route to first item of that popup.
           state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
           if (state.m_pSubMenu == NULL ||
            (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
            state.m_nID == (UINT)-1)
           {
            continue;       // First item of popup can't be routed to.
           }
           state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
        }
        else
        {
           // Normal menu item.
           // Auto enable/disable if frame window has m_bAutoMenuEnable
           // set and command is _not_ a system command.
           state.m_pSubMenu = NULL;
           state.DoUpdate(this, FALSE);
        }

        // Adjust for menu deletions and additions.
        UINT nCount = pPopupMenu->GetMenuItemCount();
        if (nCount < state.m_nIndexMax)
        {
           state.m_nIndex -= (state.m_nIndexMax - nCount);
           while (state.m_nIndex < nCount &&
            pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
           {
            state.m_nIndex++;
           }
        }
        state.m_nIndexMax = nCount;
    }
}


//添加滚动条事件
void SCaseDisplay::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch(nSBCode)
	{
	case SB_LINELEFT:
		this->position = this->position - LINESIZE;
		break;
	case SB_LINERIGHT:
		this->position = this->position + LINESIZE;
		break;

	case SB_THUMBTRACK:
        
		//this->position = nPos;
		SCROLLINFO posInfo;//设置滚动条结构

		GetScrollInfo(SB_HORZ,&posInfo,SIF_ALL);

		this->position = posInfo.nTrackPos;//获得拖动后滚动条的位置

		break;

	default:
		return;
	}

	if(this->position < 0)
	{
		this->position = 0;
	}

	int maxPos = this->GetModeLength(sconfig.wSpeed) - this->realClientWidth;

	if(this->position > maxPos)
	{
		this->position = this->GetModeLength(sconfig.wSpeed) - this->realClientWidth;
	}

    SetScrollPos(SB_HORZ,this->position,TRUE);
    Invalidate();//更新数据显示
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

//添加呼吸暂停事件
void SCaseDisplay::OnA() 
{
	curEvent.nParam = 1;//设置类型是呼吸暂停事件


	eOper = INSERTAE;//设置操作类型为添加呼吸暂停
}

//删除鼠标点中事件
void SCaseDisplay::OnE() 
{
	eOper = DELETEE;//删除事件标记

	this->IAflag = true;//开启鼠标移动事件
}

//更改事件标记
void SCaseDisplay::OnUPDATEEE() 
{
    eOper = UPDATEE;//删除时间标记

	this->IAflag = true;//开启鼠标移动事件
}

//添加氧减事件
void SCaseDisplay::OnD() 
{
	curEvent.nParam = 3;//设置类型是氧减事件


	eOper = INSERTDE;//设置操作类型为添加呼吸暂停
}

//添加低通气事件
void SCaseDisplay::OnH() 
{
    curEvent.nParam = 2;//设置类型是氧减事件


	eOper = INSERTHE;//设置操作类型为添加呼吸暂停
}

//显示事件列表
void SCaseDisplay::OnShow() 
{

	SEventList* eventDialog;//事件定义窗体

	eventDialog = new SEventList(this);

	eventDialog->Create(IDD_EVENTDIALOG,this);//创建非模态对话框

	eventDialog->ShowWindow(SW_SHOW);//显示
 

}

//显示统计结果
void SCaseDisplay::OnShowR()
{
	SResultDialog rDialog(this);

	rDialog.DoModal();
}
//显示选中事件
void SCaseDisplay::FindEvent(int position)
{
	this->position = position;//获得下标

	Invalidate();//重绘视图
}


//鼠标滚轮事件
BOOL SCaseDisplay::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{

	int maxPos = this->GetModeLength(sconfig.wSpeed) - this->realClientWidth;

    if(maxPos <= 0)
	{
	   return CDialog::OnMouseWheel(nFlags, zDelta, pt);
	}

	if(zDelta > 0)
	{
		this->position = this->position + LINESIZE1;
	}
	else
	{
        this->position = this->position - LINESIZE1;
	}

	if(this->position < 0)
	{
		this->position = 0;
	}
	

	
	if(this->position > maxPos)
	{
		this->position = this->GetModeLength(sconfig.wSpeed) - this->realClientWidth;
	}

    SetScrollPos(SB_HORZ,this->position,TRUE);

    Invalidate();//更新数据显示
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
