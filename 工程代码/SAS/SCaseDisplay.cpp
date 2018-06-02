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

  	 this->scase = scase;//��ò�����Ϣ

	 this->scase.InitSenddate();

	 this->sdata.InitDatas(scase.GetSid());//��ʼ��������Ϣ

	 this->eventOper.GetSEventList(scase.GetSid());//�����¼���ʼ��

	 this->position = 0;//Ĭ�ϳ�ʼֵΪ0


	 this->curEvent.nID = -1;//���ø�һ��־��ǰû��Ҫ��������ѡ����

	 //�¼���ǲ���Ĭ��Ϊfalse
	 this->IAflag = false;

	 this->IHflag = false;

	 this->IDflag = false;

	 this->DEflag = false;

	 this->UPflag = false;

	 //�¼���ǲ���Ĭ��Ϊfalse

	 //�¼���������Ĭ��Ϊû�в���
	 this->eOper = NOOPER;//û�в���

	 this->realTrayHight = 0;//��ǰ�θ߶ȳ�ʼʱĬ��Ϊ0
}


void SCaseDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(SCaseDisplay, CDialog)
	//{{AFX_MSG_MAP(SCaseDisplay)
	ON_WM_INITMENUPOPUP()//��Ӧ�˵���������
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
  ////��ͼ������ʽ1.0/////////////////////////////////////////
   CPaintDC dcOrigin(this);

   dcOrigin.SetBkColor(sconfig.backC);//���ñ���ɫ

   CRect clientRect;

   GetClientRect(&clientRect);//ʵ�ʿɻ������С

   
   CRect toolRect;//������������ռ�������С

   this->mToolbar.GetClientRect(&toolRect);

 //  CString tempShow;

 //  tempShow.Format("%d",toolRect.bottom);

//   AfxMessageBox(tempShow);

   int rClientHight = clientRect.bottom - toolRect.bottom;//ʵ�ʿɻ��ĸ߶�

   int rStartPosX = toolRect.left;

   int rStartPosY = toolRect.bottom;

   int rClientWidth = clientRect.right;//ʵ�ʿɻ��Ŀ��

   this->realX = sconfig.verticalHintWidth;//������ݻ�ͼ��x������

   this->realY = sconfig.scaseHight + sconfig.horizontalHintHight;//������ݻ�ͼ��y������

   this->realClientHight = rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight;//ʵ��������ʾ�߶�

   this->realClientWidth = rClientWidth - 2 * sconfig.verticalHintWidth;//���ʵ��������ʾ���

   this->realDrawCount = (this->GetModeLength(sconfig.wSpeed) - position) > this->realClientWidth ? this->realClientWidth:this->GetModeLength(sconfig.wSpeed) - position;//��û��������


   
   //��ʼ��������
   //////��ʼ��������///////////////////////////////

   if(this->GetModeLength(sconfig.wSpeed) > this->realClientWidth)
   {
   	SCROLLINFO siScroll;

	siScroll.fMask = SIF_RANGE;

	siScroll.nMin = 0;

	int nMaxPos = this->GetModeLength(sconfig.wSpeed) - this->realClientWidth;

	siScroll.nMax = nMaxPos;//�������

    siScroll.nPage = 1;

	siScroll.nPos = this->position;

	SetScrollInfo(SB_HORZ,&siScroll,TRUE);

    //������ͼ�����С
	GetClientRect(&clientRect);//ʵ�ʿɻ������С

	rClientHight = clientRect.bottom - toolRect.bottom;//ʵ�ʿɻ��ĸ߶�

	rClientWidth = clientRect.right;//ʵ�ʿɻ��Ŀ��

    this->realClientHight = rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight;//ʵ��������ʾ�߶�

    this->realClientWidth = rClientWidth - 2 * sconfig.verticalHintWidth;//���ʵ��������ʾ���

	this->realDrawCount = (this->GetModeLength(sconfig.wSpeed) - position) > this->realClientWidth ? this->realClientWidth:this->GetModeLength(sconfig.wSpeed) - position;//��û��������

	//������ͼ�����С
   }
   else
   {
   	SCROLLINFO siNull;

	siNull.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	siNull.nMin = 0;

	siNull.nMax = 0;//�������

    siNull.nPage = 1;

	siNull.nPos = this->position;

	SetScrollInfo(SB_HORZ,&siNull,TRUE);
   }
 
   //��ʼ��������

 ////˫���弼������////////////////////////////////////////

//����һ���ڴ��豸��������󣨼��󱸻�������
 CDC dc; 

//����һ��λͼ����
 CBitmap MemBitmap;
 //��������Ļ�豸������ǰ�˻����������ݵ��ڴ��豸�����������󱸻�������
 dc.CreateCompatibleDC(NULL);
 //��ʱ�����ܻ�ͼ����Ϊû��λͼ���豸�������ǲ��ܻ�ͼ��
 //���潨��һ������Ļ�豸�����������ڴ��豸���������ݵ�λͼ
 MemBitmap.CreateCompatibleBitmap(&dcOrigin,rClientWidth,rClientHight);
 //��λͼѡ�뵽�ڴ��豸������
 //ֻ��ѡ����λͼ���豸��������еط���ͼ������ָ����λͼ��
 CBitmap *pOldBit=dc.SelectObject(&MemBitmap);
 //���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
 //��Ҳ�������Լ�Ӧ���õ���ɫ
 dc.FillSolidRect(0,0,rClientWidth,rClientHight,sconfig.backC);

 CPen pen(PS_DOT,1,RGB(255,0,0));

 CPen *oldPen = dc.SelectObject(&pen);//�޸Ļ���
 

   ////˫���弼������/////////////////////////////////////////

   dc.SetMapMode(MM_TEXT);//������ʾģʽΪ����

   dc.SetBkMode(TRANSPARENT);//͸��

   Gdiplus::Graphics g(dc.GetSafeHdc());


   //��ӡ������Ϣ
   LOGFONT scaseLog = CreateFontBySize(sconfig.scaseWordSize);

   CFont scaseFont;

   scaseFont.CreateFontIndirect(&scaseLog);

   dc.SelectObject(&scaseFont);//ѡ���豸����

  // dc.SetTextAlign(TA_CENTER);

   dc.SetBkMode(TRANSPARENT);//���ģʽ

   CRect scaseRect(0,sconfig.scaseSpaceTop,rClientWidth,sconfig.scaseHight - sconfig.scaseSpaceTop);//���岡����Ϣ��ʾ����


   dc.DrawText(GetSCaseString(),scaseRect,DT_CENTER);//������������Ϣ��ʾ


   int rStartX = rClientWidth - sconfig.verticalHintWidth;//����ұ߹���������ʼx������

   int trayHight = 100;//tray����Ϊ���̣����̸߶�

   int traySegHight = 100/11;

   trayHight = traySegHight * 11;

   if(sconfig.hGain == 0)//��������Ӧģʽ
   {
     trayHight = this->realClientHight / 4;//��ʼ���ĸ����̸߶�

	 traySegHight = trayHight / 11;

	 trayHight = traySegHight * 11;//ͨ�������������������ʾ����
   }

   this->realTrayHight = trayHight;//��ǰ�θ߶�

   int nFlowCX = 0;//����x��Ŀ�ʼ����

   int nFlowCY = sconfig.horizontalHintHight + sconfig.scaseHight;//����y�����꿪ʼ

   int nSpO2CX = 0;
   
   int nSpO2CY = sconfig.horizontalHintHight + sconfig.scaseHight + 1 + trayHight;//Ѫ�����Ͷ�y�����꿪ʼ

   int nPulseCX = 0;

   int nPulseCY = sconfig.horizontalHintHight + sconfig.scaseHight + 2 + 2 * trayHight;//����y�����꿪ʼ

   int nPlethCX = 0;

   int nPlethCY = sconfig.horizontalHintHight + sconfig.scaseHight + 3 + 3 * trayHight;//Ѫ���ݻ�y�����꿪ʼ
   
   //��������ʾ������

   CPen zeroPen(PS_SOLID,1,sconfig.zeroShaftC);

   dc.SelectObject(zeroPen);

   LOGFONT lrtoolLog = CreateFontBySize(sconfig.rlWordSize);

   CFont lrtoolFont;

   lrtoolFont.CreateFontIndirect(&lrtoolLog);//�����ʼ�����ٴε���CreateFontIndirect()��������

   dc.SelectObject(&lrtoolFont);//ѡ���豸����

   //����
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
		  dc.TextOut(nFlowCX + sconfig.verticalHintWidth,nFlowCY - traySegHight + 1,"����");
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

	  dc.LineTo(sconfig.verticalHintWidth,nFlowCY);//���

	  dc.MoveTo(rStartX,nFlowCY);

	  dc.LineTo(rClientWidth,nFlowCY);//�ұ�

      nFlowCY += traySegHight; 
   }

   //Ѫ�����Ͷ�
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

		  dc.TextOut(nSpO2CX + sconfig.verticalHintWidth,nSpO2CY - traySegHight + 1,"Ѫ�����Ͷ�");
		  break;

	  }
      dc.MoveTo(nSpO2CX,nSpO2CY);

	  dc.LineTo(sconfig.verticalHintWidth,nSpO2CY);//���

	  dc.MoveTo(rStartX,nSpO2CY);

	  dc.LineTo(rClientWidth,nSpO2CY);//�ұ�

      nSpO2CY += traySegHight; 
   }

   //����
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

		  dc.TextOut(nPulseCX + sconfig.verticalHintWidth,nPulseCY - traySegHight + 1,"����");
		  break;

	  }

      dc.MoveTo(nPulseCX,nPulseCY);

	  dc.LineTo(sconfig.verticalHintWidth,nPulseCY);//���

	  dc.MoveTo(rStartX,nPulseCY);

	  dc.LineTo(rClientWidth,nPulseCY);//�ұ�

      nPulseCY += traySegHight; 
   }

   //Ѫ���ݻ�
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

		  dc.TextOut(nPlethCX + sconfig.verticalHintWidth,nPlethCY - traySegHight + 1,"Ѫ���ݻ���");
		  break;
	  }

      dc.MoveTo(nPlethCX,nPlethCY);

	  dc.LineTo(sconfig.verticalHintWidth,nPlethCY);//���

	  dc.MoveTo(rStartX,nPlethCY);

	  dc.LineTo(rClientWidth,nPlethCY);//�ұ�

      nPlethCY += traySegHight; 
   }

   //�������

   CPen intervalPen(PS_DOT,1,sconfig.intervalC);//���û�����ɫ

   dc.SelectObject(&intervalPen);//���û�����ɫ



   int intervalCount = this->realClientWidth / sconfig.hInterval - 1;//��ÿɻ�����߸���

   for(int intervali = 1; intervali <= intervalCount;intervali++)
   {
      int intervalX = this->realX + intervali * sconfig.hInterval;//���x����

	  int intervalY1 = this->realY;//������y����

	  int intervalY2 = this->realY + this->realClientHight;//����յ�y����

	  dc.MoveTo(intervalX,intervalY1);//�ƶ����

	  dc.LineTo(intervalX,intervalY2);//���ߵ��յ�
   }

   //�������
   
   
   //��������ʾ������


   //////����������ʾ/////////////////////////////////////////////

  //�����Ӧģʽ�����ݵ����0������ʾ����������
  if(this->GetModeLength(sconfig.wSpeed) > 0)
  {
   //������������
   int realPosition = 0;//���ʵ���±�ֵ

   int changePos = this->position;//������ݵ�ǰ�±�

   //����
   nFlowCX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);
 
   nFlowCY = this->realY + 5 * traySegHight + (((-sdata.datas[realPosition].nFlow) * traySegHight*5) / 500);

   CPen nFlowPen(PS_SOLID,1,sconfig.nFlowC);

   oldPen = dc.SelectObject(&nFlowPen);//���û�����ɫ

   dc.MoveTo(nFlowCX,nFlowCY);

   for(int fi = 1; fi < this->realDrawCount;fi++)
   {
	 changePos++;

	 nFlowCX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

     nFlowCY = this->realY + 5 * traySegHight + (((-sdata.datas[realPosition].nFlow) * traySegHight*5) / 500);

	 dc.LineTo(nFlowCX,nFlowCY);

   }

    //Ѫ�����Ͷ�

   changePos = this->position;

   nSpO2CX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

   nSpO2CY = this->realY + 2 * trayHight - traySegHight - (sdata.datas[realPosition].nSpO2 * 10 * traySegHight  / 100);

   CPen nSpO2Pen(PS_SOLID,1,sconfig.nSpO2C);

   oldPen = dc.SelectObject(&nSpO2Pen);//���û�����ɫ

   dc.MoveTo(nSpO2CX,nSpO2CY);

   for(int si = 1; si < this->realDrawCount;si++)
   {
	 changePos++;

	 nSpO2CX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

     nSpO2CY = this->realY + 2 * trayHight - traySegHight - (sdata.datas[realPosition].nSpO2 * 10 * traySegHight  / 100);

	 dc.LineTo(nSpO2CX,nSpO2CY);

   }


   //����

   changePos = this->position;

   nPulseCX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

   nPulseCY = this->realY + 3 * trayHight - traySegHight - (sdata.datas[realPosition].nPulse * 10 * traySegHight  / 100);

   CPen nPulsePen(PS_SOLID,1,sconfig.nPulseC);

   oldPen = dc.SelectObject(&nPulsePen);//���û�����ɫ

   dc.MoveTo(nPulseCX,nPulseCY);

   for(int pi = 1; pi < this->realDrawCount;pi++)
   {
	 changePos++;

	 nPulseCX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

     nPulseCY = this->realY + 3 * trayHight - traySegHight - (sdata.datas[realPosition].nPulse * 10 * traySegHight / 100);

	 dc.LineTo(nPulseCX,nPulseCY);
   }

   //Ѫ���ݻ�

   changePos = this->position;

   nPlethCX = this->realX;

   realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

   nPlethCY = this->realY + 4 * trayHight - traySegHight - (sdata.datas[realPosition].nPleth * 10 * traySegHight / 100);

   CPen nPlethPen(PS_SOLID,1,sconfig.nPlethC);

   oldPen = dc.SelectObject(&nPlethPen);//���û�����ɫ

   dc.MoveTo(nPlethCX,nPlethCY);

   for(int pli = 1; pli < this->realDrawCount;pli++)
   {
	 changePos++;

	 nPlethCX++;

     int realPosition = this->GetRealIndex(changePos,sconfig.wSpeed);//���ʵ���±�ֵ

     nPlethCY = this->realY + 4 * trayHight - traySegHight - (sdata.datas[realPosition].nPleth * 10 * traySegHight / 100);

	 dc.LineTo(nPlethCX,nPlethCY);
   }

   //������������

   //������ʱ��̶���ʾ��
    int TopX = sconfig.verticalHintWidth;//top��x��Ŀ�ʼ����

    int TopY = sconfig.scaseHight;//top��y�����꿪ʼ

    int BottomX = sconfig.verticalHintWidth;//bottom��x�Ὺʼ����

	int BottomY = sconfig.scaseHight + sconfig.horizontalHintHight + this->realClientHight;//bottom��y�Ὺʼ���� 

    LOGFONT tbtoolLog = CreateFontBySize(sconfig.tbWordSize);

    CFont tbtoolFont;

    tbtoolFont.CreateFontIndirect(&tbtoolLog);//�����ʼ�����ٴε���CreateFontIndirect()��������

    dc.SelectObject(&tbtoolFont);//ѡ���豸����

	int strCount = this->realDrawCount/sconfig.hInterval;//��ʱ��ĸ���

   for(int stri = 1; stri <= strCount;stri++)
   {
	   CString drawStr1 = GetTBMDString(this->position + stri * sconfig.hInterval);//��õ�ǰ������մ�
	   CString drawStr2 = GetTBHMSString(this->position + stri * sconfig.hInterval);//��õ�ǰ���ʱ���ַ���

	   TopX = sconfig.verticalHintWidth + ((2*stri - 1) * sconfig.hInterval)/2; //(stri-1)*sconfig.hInterval + 

	   BottomX = TopX;

	   dc.TextOut(TopX,TopY,drawStr1);//���մ���Ϣ

	   dc.TextOut(BottomX,BottomY,drawStr1);//���մ���Ϣ
       
       dc.TextOut(TopX,TopY + sconfig.tbWordHighSpace,drawStr2);//����������ʱ����Ϣ��ʾ
 
       dc.TextOut(BottomX,BottomY + sconfig.tbWordHighSpace,drawStr2);//����������ʱ����Ϣ��ʾ
   }

   
   //������ʱ��̶���ʾ��
 }

   //////����������ʾ/////////////////////////////////////////////

   ////////////////�¼���ʾ////////////////////////////////////////

    POSITION pos = eventOper.sEventList.GetHeadPosition();//��õ�һ������

	ANLEVENT event;//�¼��������ձ���������

	int eventSX = this->realX;//��ʼx������

	int eventSY = this->realY;//��ʼy������

    Gdiplus::Color colorE(192, 0, 0, 128);//�¼�Ĭ�ϵ���ɫ

	Gdiplus::SolidBrush eventBrush(colorE);

	//��ʼ��������ͣ�¼���ɫ
	BYTE AR = GetRValue(sconfig.apneaB);
	
	BYTE AG = GetGValue(sconfig.apneaB);

	BYTE AB = GetBValue(sconfig.apneaB);

	Gdiplus::Color colorA(192, AR, AG, AB);//�¼�Ĭ�ϵ���ɫ



	//��ʼ����ͨ���¼���ɫ

    BYTE HR = GetRValue(sconfig.hypopneaB);
	
	BYTE HG = GetGValue(sconfig.hypopneaB);

	BYTE HB = GetBValue(sconfig.hypopneaB);

	Gdiplus::Color colorH(192, HR, HG, HB);//�¼�Ĭ�ϵ���ɫ



	//��ʼ�������¼���ɫ
	BYTE DR = GetRValue(sconfig.descendB);
	
	BYTE DG = GetGValue(sconfig.descendB);

	BYTE DB = GetBValue(sconfig.descendB);

	Gdiplus::Color colorD(192, DR, DG, DB);//�¼�Ĭ�ϵ���ɫ



	//��ǰ�¼�id��Ϊ-1ʱ����ǰ�¼�
	if(curEvent.nID != -1 && this->eOper != UPDATEE)
	{
		   int beginCurModeP = this->GetShowPosition(curEvent.nBeginTime,sconfig.wSpeed);//��õ�ǰģʽ�µĿ�ʼ����

	       int endCurModeP = this->GetShowPosition(curEvent.nEndTime,sconfig.wSpeed);//��õ�ǰģʽ�µĽ�������

		   switch(curEvent.nParam)
		   {
		   case 1:
			   eventSY = this->realY + 1;//���y������

               eventBrush.SetColor(colorA);//���ú�����ͣ�¼�

			   break;

		   case 2:
			   eventSY = this->realY + 1;//���y������


               eventBrush.SetColor(colorH);//���ú�����ͣ�¼�

			   break;

		   case 3:
			   eventSY = this->realY + trayHight + 1;//���y������


               eventBrush.SetColor(colorD);//���ú�����ͣ�¼�

			   break;
		   }
	      
     
		   Gdiplus::Rect eventCurRect(eventSX + (beginCurModeP - this->position),eventSY,endCurModeP - beginCurModeP,trayHight - sconfig.eventHightSpace);//���¼�

           g.FillRectangle(&eventBrush,eventCurRect);

	}


	//�¼���ͼ
	while(pos != NULL)
	{
       event = eventOper.sEventList.GetNext(pos);//���������

	   int beginModeP = this->GetShowPosition(event.nBeginTime,sconfig.wSpeed);//��õ�ǰģʽ�µĿ�ʼ����

	   int endModeP = this->GetShowPosition(event.nEndTime,sconfig.wSpeed);//��õ�ǰģʽ�µĽ�������

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
			   eventSY = this->realY + 1;//���y������

               eventBrush.SetColor(colorA);//���ú�����ͣ�¼�

			   break;

		   case 2:
			   eventSY = this->realY + 1;//���y������


               eventBrush.SetColor(colorH);//���ú�����ͣ�¼�

			   break;

		   case 3:
			   eventSY = this->realY + trayHight + 1;//���y������


               eventBrush.SetColor(colorD);//���ú�����ͣ�¼�

			   break;
		   }
	      
     
		   Gdiplus::Rect eventRect(eventSX + (beginModeP - this->position),eventSY,endModeP - beginModeP,trayHight - sconfig.eventHightSpace);//���¼�


		   g.FillRectangle(&eventBrush,eventRect);

	   }

	  
	}
	
   ////////////////�¼���ʾ////////////////////////////////////////

 

   Gdiplus::SolidBrush sBrush(sconfig.sColor);
 
   Gdiplus::Rect horizontalHintSCaseTop(0,0,rClientWidth,sconfig.scaseHight);
		
   g.FillRectangle(&sBrush,horizontalHintSCaseTop);//����Ϣ��ʾ������ʾ������Ϣ


 

   Gdiplus::SolidBrush hBrush(sconfig.hColor);


   Gdiplus::Rect horizontalHintTop(0,sconfig.scaseHight,rClientWidth,sconfig.horizontalHintHight);
		
   g.FillRectangle(&hBrush,horizontalHintTop);//��������Ϣ��ʾ��,��ʾʱ����ʾ��Ϣ


   Gdiplus::Rect horizontalHintBottom(0,rClientHight - sconfig.horizontalHintHight,rClientWidth,sconfig.horizontalHintHight);

   g.FillRectangle(&hBrush,horizontalHintBottom);//���ײ���Ϣ��ʾ������ʾʱ����ʾ��Ϣ


   Gdiplus::SolidBrush vBrush(sconfig.vColor);

   Gdiplus::Rect verticalHintLeft(0,sconfig.horizontalHintHight + sconfig.scaseHight,
	   sconfig.verticalHintWidth,rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight);

   g.FillRectangle(&vBrush,verticalHintLeft);//�������Ϣ��ʾ������ʾ������Ϣ


   Gdiplus::Rect verticalHintRight(rClientWidth - sconfig.verticalHintWidth,sconfig.horizontalHintHight + sconfig.scaseHight,
	   sconfig.verticalHintWidth,rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight);

   g.FillRectangle(&vBrush,verticalHintRight);//���ұ���Ϣ��ʾ������ʾ������Ϣ




   int drawX = sconfig.horizontalHintHight + 1;//��������Ϣ��ʼx������

   int drawY = sconfig.scaseHight + sconfig.horizontalHintHight + 1;//��������Ϣ��ʼy������

   int drawHight = rClientHight - 2 * sconfig.horizontalHintHight - sconfig.scaseHight;//��ò�����Ϣ��ͼ���ܿ��

   int drawWidth = rClientWidth - 2 * sconfig.verticalHintWidth;//��ò�����Ϣ��ͼ���ܳ���



   //dcOrigin.Rectangle(rStartPosX,rStartPosY,200,200);
   //dcOrigin.SetMapMode(MM_TEXT);//������ʾģʽΪ����

   ////////////�¼���ʾ����////////////////////////////////////////////////////////	
  //���󱸻������е�ͼ�ο�����ǰ�˻�����
  dcOrigin.BitBlt(rStartPosX,rStartPosY,rClientWidth,rClientHight,&dc,0,0,SRCCOPY);
  //��ͼ��ɺ������
  MemBitmap.DeleteObject();

  dc.DeleteDC();


}


void SCaseDisplay::OnMouseMove(UINT nFlags, CPoint point) 
{

	if(!this->IAflag)
		return ;
	ANLEVENT event;//�����¼�

    event = this->curEvent;//��õ�ǰ�¼�

    int beginX = 0;

    int beginY = 0;

	int endX = 0;

	int endY = 0;

	int posBeginX = this->realX;//��ʼλ��

	int curPos = 0;//��ǰλ���±�Ϊ0

	HCURSOR myCursor;//�������ͼ�����

    switch(eOper)
	{
	case INSERTAE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

		  this->curEvent = event;//�¼����

	      Invalidate();//������ʾ

		}

		break;

	case INSERTHE://��ͨ���¼�
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

		  this->curEvent = event;//�¼����


	      Invalidate();//������ʾ

		}

		break;
	case INSERTDE:

		beginX = this->realX;

		beginY = this->realY + this->realTrayHight;//y����Ŀ�ʼλ��

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;//y����Ľ���λ��

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

		  this->curEvent = event;//�¼����

	      Invalidate();//������ʾ
		}

		break;
	case DELETEE:



		if((point.x > this->realX) && (point.x < (this->realX + this->realClientWidth))&&(point.y >this->realY)&&(point.y < (this->realY + this->realClientHight)))
		{
  		    myCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);
	
	        this->SetCapture();

	        SetCursor(myCursor);//�������

		}
		else
		{
            ReleaseCapture();//�ͷ���꣬��ԭ����״̬
		}
		break;
	case UPDATEE:
	    beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;

		//�жϸ����¼��Ƿ��Ѿ���ʼ
		if(!this->IHflag)
		{

			 if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
			 {
		          this->curEvent = GetEventByPoint(point);//��õ�ǰ�ǲ��Ǵ����޸��¼�
		
			   if(this->curEvent.nID != -1)
			   {
		          myCursor = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE);
	
	              this->SetCapture();

	              SetCursor(myCursor);//�������

				  this->IDflag = true;//��ǿ��Կ�ʼ�޸��¼�
			   }
			   else
			   {
			      ReleaseCapture();//�ͷ���꣬��ԭ����״̬

				  this->IDflag = false;//��ǲ����Կ�ʼ�޸��¼�
			   }
			 }
		}
		else
		{
			
			if(this->curEvent.nParam != 3)
			{
				//������ͣ����ͨ���¼��޸Ĵ������
		        beginX = this->realX;

				beginY = this->realY;
		
				endX = this->realX + this->realClientWidth;

				endY = this->realY + this->realTrayHight;

				if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
				{
				  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

				  if(this->curEvent.bAuto)
				  {
					  //�޸��¼���β
					  this->curEvent.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

					  this->UpdateEventByNid(this->curEvent);//���µ�ǰ�޸��¼�
				  }
				  else
				  {
					  //�޸�ʱ��
					  this->curEvent.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

					  this->UpdateEventByNid(this->curEvent);//���µ�ǰ�޸��¼�
				  }
		
				}


			    Invalidate();//������ʾ

			}
			else
			{
			   //�����¼��޸Ĵ������
		        beginX = this->realX;

				beginY = this->realY + this->realTrayHight;
		
				endX = this->realX + this->realClientWidth;

				endY = this->realY + 2 * this->realTrayHight;

				if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
				{
				  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

				  if(this->curEvent.bAuto)
				  {
					  //�޸��¼���β
					  this->curEvent.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

					  this->UpdateEventByNid(this->curEvent);//���µ�ǰ�޸��¼�
				  }
				  else
				  {
					  //�޸�ʱ��
					  this->curEvent.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�

					  this->UpdateEventByNid(this->curEvent);//���µ�ǰ�޸��¼�
				  }
		
				}


			    Invalidate();//������ʾ


			}

		}

		break;

	case NOOPER:
		break;
	}

	CDialog::OnMouseMove(nFlags, point);
}

//��ˢ�±����¼�
BOOL SCaseDisplay::OnEraseBkgnd(CDC* pDC)
{
 // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
 //return CDialog::OnEraseBkgnd(pDC);
 return FALSE;
}


//���Ի��˵�
BOOL SCaseDisplay::OnInitDialog() 
{
	CDialog::OnInitDialog();

    menu.LoadMenu(IDR_MENUPOP);//���ز˵���Դ

	////���ô������////////////////////////////////////////////////////
     SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),0); 

    ////���ô������////////////////////////////////////////////////////
//CBRS_SIZE_DYNAMIC

	 //������ʾ������

  	if (!mToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY|CBRS_SIZE_DYNAMIC) ||
		!mToolbar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	EnableToolTips(TRUE);//��ʾ��ʾ��Ϣ

	mToolbar.SetSizes(CSize(68,42),CSize(60,17));

	mToolbar.SetButtonText(0,_T("������ͣ"));

	mToolbar.SetButtonText(1,_T("����"));

	mToolbar.SetButtonText(2,_T("��ͨ��"));

	mToolbar.SetButtonText(3,_T("�¼�ɾ��"));

	mToolbar.SetButtonText(4,_T("�¼��޸�"));

	mToolbar.SetButtonText(5,_T("�¼�ͳ��"));

	mToolbar.SetButtonText(6,_T("�¼��б�"));

	mToolbar.EnableToolTips(TRUE);

	mToolbar.ShowWindow(SW_SHOW);

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_FIRST,0);//AFX_IDW_CONTROLBAR_LAST,0);

	//������ʾ������
	
	return TRUE;  

}


//��갴��ʱ����¼���ʼ
void SCaseDisplay::OnLButtonDown(UINT nFlags, CPoint point) 
{
    ANLEVENT event;//�����¼�

	event.nID = -1;

	event.nBeginTime = 0;

	event.nEndTime = 0;

    int beginX = 0;

    int beginY = 0;

	int endX = 0;

	int endY = 0;

	int posBeginX = this->realX;//��ʼλ��

	int curPos = 0;//��ǰλ���±�Ϊ0

	
	switch(eOper)
	{
	case INSERTAE://������ͣ�¼�

        beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
          event.bAuto = false;//������ֶ�����¼�

		  event.nParam = 1;//���Ϊ������ͣ�¼�

		  event.nID = eventOper.sEventList.GetCount() + 1;//�¼����

		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//���ʱ���������е��±�

		  event.nEndTime = event.nBeginTime;//�¼��Ľ�������Ĭ�ϺͿ�ʼ����һ��

		}
        
		this->IAflag = true;

		this->curEvent = event;//��õ�ǰ��ӵ��¼�

		break;
	case INSERTHE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
          event.bAuto = false;//������ֶ�����¼�

		  event.nParam = 2;//���Ϊ������ͣ�¼�

		  event.nID = eventOper.sEventList.GetCount() + 1;//�¼����

		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//���ʱ���������е��±�

		  event.nEndTime = event.nBeginTime;//�¼��Ľ�������Ĭ�ϺͿ�ʼ����һ��

		}
        
		this->IAflag = true;

		this->curEvent = event;//��õ�ǰ��ӵ��¼�

		break;
	case INSERTDE://�����¼�

		beginX = this->realX;

		beginY = this->realY + this->realTrayHight;//y����Ŀ�ʼλ��

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;//y����Ľ���λ��

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
          event.bAuto = false;//������ֶ�����¼�

		  event.nParam = 3;//���Ϊ������ͣ�¼�

		  event.nID = eventOper.sEventList.GetCount() + 1;//�¼����

		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nBeginTime = GetRealIndex(curPos,sconfig.wSpeed);//���ʱ���������е��±�

		  event.nEndTime = event.nBeginTime;//�¼��Ľ�������Ĭ�ϺͿ�ʼ����һ��

		}
        
		this->IAflag = true;

		this->curEvent = event;//��õ�ǰ��ӵ��¼�

		break;
	case DELETEE:
		this->IAflag = true;//����up��Ӧɾ���¼�
		break;
	case UPDATEE:
        if(this->curEvent.nID != -1)//�����ǰ�¼���nID��Ϊ��һ
		{
			this->IHflag = true;//�����¼��޸ı��
		}
		else
		{
			this->IHflag = false;//�����¼��޸ı��
		}
		break;
	case NOOPER:
		break;
	}



	CDialog::OnLButtonDown(nFlags, point);
}

//����¼�����
void SCaseDisplay::OnLButtonUp(UINT nFlags, CPoint point) 
{ 
	
	if(!this->IAflag)
		return ;
	ANLEVENT event;//�����¼�

    event = this->curEvent;//��õ�ǰ�¼�

    int beginX = 0;

    int beginY = 0;

	int endX = 0;

	int endY = 0;

	int posBeginX = this->realX;//��ʼλ��

	int curPos = 0;//��ǰλ���±�Ϊ0


	switch(eOper)
	{
	case INSERTAE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�
          
		  if(!CheckEventExist(event))
		  {
		    eventOper.sEventList.AddTail(event);//�����¼��б���

		    eventOper.SaveSEventList(scase.GetSid());//����һ���б��ļ�
		  }
		  else
		  {
			  MessageBox("�¼�����������ص���Ƕ��!");
		  }

		  Invalidate();//ˢ��

		}

		break;
	case INSERTHE:
		beginX = this->realX;

		beginY = this->realY;

		endX = this->realX + this->realClientWidth;

		endY = this->realY + this->realTrayHight;

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�
          
		  if(!CheckEventExist(event))
		  {
		    eventOper.sEventList.AddTail(event);//�����¼��б���

		    eventOper.SaveSEventList(scase.GetSid());//����һ���б��ļ�
		  }
		  else
		  {
			  MessageBox("�¼�����������ص���Ƕ��!");
		  }

		  Invalidate();//ˢ��

		}
		break;
	case INSERTDE:
		beginX = this->realX;

		beginY = this->realY + this->realTrayHight;//y����Ŀ�ʼλ��

		endX = this->realX + this->realClientWidth;

		endY = this->realY + 2 * this->realTrayHight;//y����Ľ���λ��

		if((point.x >= beginX) && (point.x <= endX) && (point.y >= beginY) &&(point.y <= endY))
		{
		  curPos = this->position + point.x - posBeginX;//����ڵ�ǰ��ʾ�µ������

		  event.nEndTime = GetRealIndex(curPos,sconfig.wSpeed);//��ý����±�
          
		  if(!CheckEventExist(event))
		  {

		    eventOper.sEventList.AddTail(event);//�����¼��б���

		    eventOper.SaveSEventList(scase.GetSid());//����һ���б��ļ�
		  }
		  else
		  {
			  MessageBox("�¼�����������ص���Ƕ��!");
		  }

		  Invalidate();//ˢ��

		}

		break;
	case DELETEE:
		if((point.x > this->realX) && (point.x < (this->realX + this->realClientWidth)))
		{
           DeleteEventByPoint(point);//����ɾ���¼�����

		   Invalidate();//ˢ��

		}

		ReleaseCapture();//�ͷ���꣬��ԭ����״̬
		break;
	case UPDATEE:

		if(this->IHflag)//����¼���ʼ�޸�
		{
			this->curEvent.bAuto = false;//ʹ�¼�������¹�Ϊ�ֶ�

            this->UpdateEventByNid(this->curEvent);//���µ�ǰ�޸��¼�

		    eventOper.SaveSEventList(this->scase.GetSid());//�����ļ�

			ReleaseCapture();//�ͷ���꣬��ԭ����״̬

		    this->IDflag = false;//��ǲ����Կ�ʼ�޸��¼�

			Invalidate();//ˢ��
		}

		break;
	case NOOPER:
		break;
	}

	this->curEvent.nID = -1;//��ǰ�¼�������һ

	eOper = NOOPER;//����Ϊû�в���

	this->IAflag = false;//�¼������������

	this->IHflag = false;



   CDialog::OnLButtonUp(nFlags, point);
}

//��������ʱ�˵�����
void SCaseDisplay::OnDestroy() 
{
	menu.DestroyMenu();//���ٲ˵�

	CDialog::OnDestroy();	
}


//�Ҽ��˵�����
void SCaseDisplay::OnRButtonDown(UINT nFlags, CPoint point) 
{
   menuPop = menu.GetSubMenu(0);//�õ��Ӳ˵�

   ClientToScreen(&point);//�ͻ�����ת������Ļ����

   menuPop->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);//�����˵�

   CDialog::OnRButtonDown(nFlags, point);
}

//���ݴ�������Ĵ�С������Ӧ����
LOGFONT SCaseDisplay::CreateFontBySize(int size)
{
   LOGFONT log;//�ṹ�����

   //��������
   log.lfCharSet = ANSI_CHARSET;

   log.lfClipPrecision = 23;//����Ĳü�����

   log.lfEscapement = 0;//���������x�����б��Ϊ0

   log.lfHeight = size;//����ĸ߶�Ϊ50

   strcpy(log.lfFaceName,"�½�����");//��������

   log.lfItalic = 0;//0��ʾ��б��

   log.lfOrientation = 900;//�����׼����x��֮��ļн�

   log.lfOutPrecision = 90;//������������

   log.lfPitchAndFamily = 0;//�ַ����

   log.lfQuality = 90;//������������

   log.lfUnderline = 0;//���»���

   log.lfStrikeOut = 0;//��ɾ����

   return log;//�����½�������

}

//��ò�����ʾ��Ϣ�ַ���
CString SCaseDisplay::GetSCaseString()
{

   CString scaseText = "��ʼ��¼ʱ��:" + scase.GetSstartdate().Format("%y-%m-%d %H:%M:%S");

   scaseText += "         ";

   CString temp;//��ʱ����������ʾ

   temp = "��������:" + scase.GetSName();

   scaseText += temp;

   temp = scase.GetSsex() == 2?"δ��":(scase.GetSsex() == 0?"��":"Ů");

   scaseText += "  ";

   temp = "�Ա�:" + temp;

   scaseText +=  temp;

   scaseText += "  ";

   temp.Format("%d",scase.GetSage());

   scaseText += "����:" + temp + "��";

   scaseText += "         ";

   temp =  "������¼ʱ��:" + scase.GetSenddate().Format("%y-%m-%d %H:%M:%S");

   scaseText += temp;

   return scaseText;
}

//����ģʽ���û��ʵ�ʿ�����ʾ��������
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

	return result;//����ʵ�ʿ�����ʾ��������
}

//���ݵ�ǰ�±�λ�ú�ģʽ���ʵ���±�
int SCaseDisplay::GetRealIndex(int position,WSpeed wSpeed)
{
   int realPosition = -1;//Ĭ�ϸ�һ

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
//���ݵ�ǰʵ������ת������Ӧģʽ�µ���ʾ�±�
int SCaseDisplay::GetShowPosition(int realPosition,WSpeed wSpeed)
{
   int position = -1;//Ĭ�ϸ�һ

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

//���ݵ�ǰλ������ʱ���ַ���
CString SCaseDisplay::GetTBHMSString(int position)
{
	CString tbShowString = "";//Ĭ��Ϊ��

    int realPosition = this->GetRealIndex(position,sconfig.wSpeed);

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
		          this->scase.GetSstartdate().GetYear(),
				  this->scase.GetSstartdate().GetMonth(),
		          this->scase.GetSstartdate().GetDay() + day,
		          this->scase.GetSstartdate().GetHour() + hour,
		          this->scase.GetSstartdate().GetMinute() + minute,
				  this->scase.GetSstartdate().GetSecond() + second);//ʵ����


    tbShowString.Format("  %d:%d:%d",enddate.GetHour(),enddate.GetMinute(),enddate.GetSecond());
		       
	return tbShowString;//����ʱ���ַ���
}


//��������������ʾ�ַ���
CString SCaseDisplay::GetTBMDString(int position)
{
	CString tbShowString = "";//Ĭ��Ϊ��

    int realPosition = this->GetRealIndex(position,sconfig.wSpeed);

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
		          this->scase.GetSstartdate().GetYear(),
				  this->scase.GetSstartdate().GetMonth(),
		          this->scase.GetSstartdate().GetDay() + day,
		          this->scase.GetSstartdate().GetHour() + hour,
		          this->scase.GetSstartdate().GetMinute() + minute,
				  this->scase.GetSstartdate().GetSecond() + second);//ʵ����


    tbShowString.Format("    %d-%d  ",enddate.GetMonth(),enddate.GetDay());
		       
	return tbShowString;//����ʱ���ַ���
}

bool SCaseDisplay::CheckEventExist(ANLEVENT preEvent)
{
	bool rFlag = false;//Ĭ�Ͻ��������

	POSITION pos = eventOper.sEventList.GetHeadPosition();//��õ�һ������

	ANLEVENT event;//�¼��������ձ���������

    while(pos != NULL)
	{
       event = eventOper.sEventList.GetNext(pos);//���������

	   if(event.nParam == preEvent.nParam)//����һ��ʱ�ٽ��м��
	   {
		   if((event.nBeginTime <= preEvent.nBeginTime && preEvent.nBeginTime <= event.nEndTime) || 
			   (event.nBeginTime <= preEvent.nEndTime && preEvent.nEndTime <= event.nEndTime))
		   {
			   rFlag = true;//�¼������ص���Ƕ��

			   break;
		   }
	   }

	}

	return rFlag;//�¼����ڱ��
}

bool SCaseDisplay::DeleteEventByPoint(CPoint point)
{
	bool rFlag = false;//Ĭ������Ϊ��

	POSITION pos = eventOper.sEventList.GetHeadPosition();//��õ�һ������

	ANLEVENT event;//�¼��������ձ���������

	int ahBeginY = this->realY + 1;//���ú�����ͣ�͵�ͨ��y�Ὺʼ����

	int ahEndY = this->realY + 1 + this->realTrayHight - sconfig.eventHightSpace;//���ú�����ͣ�͵�ͨ��y���������

	int dBeginY = this->realY + this->realTrayHight + 1;//���������¼�y��Ŀ�ʼ����

	int dEndY = this->realY + 2* this->realTrayHight + 1 - sconfig.eventHightSpace;//���������¼�y��Ľ�������

	int changePos = (point.x - this->realX) + this->position;

	int curIndex = this->GetRealIndex(changePos,sconfig.wSpeed);//��õ�ǰ���positionֵ

    while(pos != NULL)
	{

	   POSITION  curPos = pos;//��õ�ǰָ��λ��

       event = eventOper.sEventList.GetNext(pos);//���������

	   if(event.nParam == 3)
	   {

		   if((event.nBeginTime <= curIndex && curIndex <= event.nEndTime) &&
			   (dBeginY <= point.y && point.y <= dEndY))
		   {
			   eventOper.sEventList.RemoveAt(curPos);//ɾ����ǰ�¼�

		       eventOper.SaveSEventList(scase.GetSid());//����һ���б��ļ�

			   rFlag = true;//���ɾ���ɹ�

			   break;
		   }
	   }
	   else
	   {
		   if((event.nBeginTime <= curIndex && curIndex <= event.nEndTime) &&
			   (ahBeginY <= point.y && point.y <= ahEndY))
		   {
			   eventOper.sEventList.RemoveAt(curPos);//ɾ����ǰ�¼�

		       eventOper.SaveSEventList(scase.GetSid());//����һ���б��ļ�

			   rFlag = true;//���ɾ���ɹ�

			   break;
		   }
	   }

	}

	
    UpdateEventNid();//�������ݱ��

	return rFlag;//��ʾû��ɾ���κ���
}

//�����¼�
bool SCaseDisplay::UpdateEventByNid(ANLEVENT event)
{
	bool rFlag = false;//Ĭ�ϸ���ʧ��


	POSITION pos = eventOper.sEventList.GetHeadPosition();//��õ�һ������


    while(pos != NULL)
	{
      POSITION curPos = pos;//��õ�ǰΪλ��

      ANLEVENT selEvent = eventOper.sEventList.GetNext(pos);//�¼�

      if(event.nID == selEvent.nID)//�жϵ�ǰ�ǲ���Ҫ���µ���
	  {
		if(event.nBeginTime == selEvent.nBeginTime && event.nEndTime <= selEvent.nBeginTime)
		{
			rFlag = false;//����ʧ��

			break;
		}
		 
		if(event.nEndTime == selEvent.nEndTime && event.nBeginTime >= selEvent.nEndTime)
		{
		   rFlag = false;//����ʧ��

			break;
		}

         eventOper.sEventList.GetAt(curPos).nBeginTime = event.nBeginTime;

		 eventOper.sEventList.GetAt(curPos).nEndTime = event.nEndTime;

		 eventOper.sEventList.GetAt(curPos).bAuto = event.bAuto;

		 eventOper.sEventList.GetAt(curPos).nParam = event.nParam;

		 eventOper.sEventList.GetAt(curPos).nID = event.nID;

		 rFlag = true;//�¼����³ɹ�

		 break;//����ѭ��
	  }

	}

	return rFlag;//���ظ��½��

}

//���ݴ������ĵ���������¼���δ�ҵ��������¼���nIDΪ-1
ANLEVENT SCaseDisplay::GetEventByPoint(CPoint point)
{
	POSITION pos = eventOper.sEventList.GetHeadPosition();//��õ�һ������

	ANLEVENT event;//�¼��������ձ���������

	ANLEVENT rEvent;//���ؽ���¼�

	rEvent.nID = -1;//Ĭ�����ñ��Ϊ-1

	int ahBeginY = this->realY + 1;//���ú�����ͣ�͵�ͨ��y�Ὺʼ����

	int ahEndY = this->realY + 1 + this->realTrayHight - sconfig.eventHightSpace;//���ú�����ͣ�͵�ͨ��y���������

	int dBeginY = this->realY + this->realTrayHight + 1;//���������¼�y��Ŀ�ʼ����

	int dEndY = this->realY + 2* this->realTrayHight + 1 - sconfig.eventHightSpace;//���������¼�y��Ľ�������

	int changePos = (point.x - this->realX) + this->position;

	int curIndex = this->GetRealIndex(changePos,sconfig.wSpeed);//��õ�ǰ���positionֵ

    while(pos != NULL)
	{

	   POSITION  curPos = pos;//��õ�ǰָ��λ��

       event = eventOper.sEventList.GetNext(pos);//���������

	   if(event.nParam == 3)
	   {

		   if(((event.nBeginTime-2) <= curIndex && curIndex <= (event.nBeginTime + 2)) &&
			   (dBeginY <= point.y && point.y <= dEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = false;//����޸����ݵĿ�ͷ

			   break;
		   }

		   if(((event.nEndTime - 1) <= curIndex && curIndex <= (event.nEndTime + 1)) &&
			   (dBeginY <= point.y && point.y <= dEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = true;//����޸����ݵĽ�β

			   break;
		   }
	   }
	   else
	   {
		   if(((event.nBeginTime-2) <= curIndex && curIndex <= (event.nBeginTime + 2)) &&
			   (ahBeginY <= point.y && point.y <= ahEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = false;//����޸����ݵĿ�ͷ

			   break;
		   }

		   if(((event.nEndTime - 1) <= curIndex && curIndex <= (event.nEndTime + 1)) &&
			   (ahBeginY <= point.y && point.y <= ahEndY))
		   {
			   rEvent = event;

			   rEvent.bAuto = true;//����޸����ݵĽ�β

			   break;
		   }
	   }

	}

	return rEvent;//���ز�ѯ���
}

//ɾ���¼�ʱ�����¼����

void SCaseDisplay::UpdateEventNid()
{
    POSITION pos = eventOper.sEventList.GetHeadPosition();//��õ�һ������

    ANLEVENT event;//�¼��������ձ���������

    int index = 1;//��ʼֵΪ1


	while(pos != NULL)
	{
	   POSITION curPos = pos;//��õ�ǰΪλ��

	   event = eventOper.sEventList.GetNext(pos);//���������

	   event.nID = index;//����±��

	   eventOper.sEventList.GetAt(curPos).nID = event.nID;

	   index ++ ;//����Լ�
	}
}


//ģʽ������

void SCaseDisplay::OnWspeed002() 
{
	this->position = 0;

	sconfig.wSpeed = WSPEED002;

	//������������Ӱ��
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//�������

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //������������Ӱ��


	Invalidate();
}

void SCaseDisplay::OnWspeed02() 
{
    this->position = 0;

	//������������Ӱ��
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//�������

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //������������Ӱ��


    sconfig.wSpeed = WSPEED02;

	Invalidate();
	
}

void SCaseDisplay::OnWspeed1() 
{

	this->position = 0;

    sconfig.wSpeed = WSPEED1;

	//������������Ӱ��
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//�������

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //������������Ӱ��


    Invalidate();
}

void SCaseDisplay::OnWspeed1m() 
{
	this->position = 0;

	//������������Ӱ��
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//�������

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //������������Ӱ��


	sconfig.wSpeed = WSPEED1M;

	Invalidate();
	
}

void SCaseDisplay::OnWspeed2() 
{
	this->position = 0;

	//������������Ӱ��
    SCROLLINFO si;

	si.fMask = SIF_PAGE|SIF_RANGE|SIF_POS;

	si.nMin = 0;

	si.nMax = 0;//�������

    si.nPage = 1;

	si.nPos = this->position;

	SetScrollInfo(SB_HORZ,&si,TRUE);
   //������������Ӱ��


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


//����˵�����״̬�ı���Ϣ
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


//��ӹ������¼�
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
		SCROLLINFO posInfo;//���ù������ṹ

		GetScrollInfo(SB_HORZ,&posInfo,SIF_ALL);

		this->position = posInfo.nTrackPos;//����϶����������λ��

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
    Invalidate();//����������ʾ
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

//��Ӻ�����ͣ�¼�
void SCaseDisplay::OnA() 
{
	curEvent.nParam = 1;//���������Ǻ�����ͣ�¼�


	eOper = INSERTAE;//���ò�������Ϊ��Ӻ�����ͣ
}

//ɾ���������¼�
void SCaseDisplay::OnE() 
{
	eOper = DELETEE;//ɾ���¼����

	this->IAflag = true;//��������ƶ��¼�
}

//�����¼����
void SCaseDisplay::OnUPDATEEE() 
{
    eOper = UPDATEE;//ɾ��ʱ����

	this->IAflag = true;//��������ƶ��¼�
}

//��������¼�
void SCaseDisplay::OnD() 
{
	curEvent.nParam = 3;//���������������¼�


	eOper = INSERTDE;//���ò�������Ϊ��Ӻ�����ͣ
}

//��ӵ�ͨ���¼�
void SCaseDisplay::OnH() 
{
    curEvent.nParam = 2;//���������������¼�


	eOper = INSERTHE;//���ò�������Ϊ��Ӻ�����ͣ
}

//��ʾ�¼��б�
void SCaseDisplay::OnShow() 
{

	SEventList* eventDialog;//�¼����崰��

	eventDialog = new SEventList(this);

	eventDialog->Create(IDD_EVENTDIALOG,this);//������ģ̬�Ի���

	eventDialog->ShowWindow(SW_SHOW);//��ʾ
 

}

//��ʾͳ�ƽ��
void SCaseDisplay::OnShowR()
{
	SResultDialog rDialog(this);

	rDialog.DoModal();
}
//��ʾѡ���¼�
void SCaseDisplay::FindEvent(int position)
{
	this->position = position;//����±�

	Invalidate();//�ػ���ͼ
}


//�������¼�
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

    Invalidate();//����������ʾ
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
