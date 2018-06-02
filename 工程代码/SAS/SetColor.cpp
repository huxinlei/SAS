// SetColor.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SetColor.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetColor dialog


SetColor::SetColor(CWnd* pParent /*=NULL*/)
	: CDialog(SetColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetColor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SetColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetColor)

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetColor, CDialog)
	//{{AFX_MSG_MAP(SetColor)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
    ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_NFLOW, OnNflow)
	ON_BN_CLICKED(IDC_NSPO2, OnNspo2)
	ON_BN_CLICKED(IDC_NPULSE, OnNpulse)
	ON_BN_CLICKED(IDC_NPLETH, OnNpleth)
	ON_BN_CLICKED(IDC_APNEAB, OnApneab)
	ON_BN_CLICKED(IDC_HYPOPNEAB, OnHypopneab)
	ON_BN_CLICKED(IDC_DESCENDB, OnDescendb)
	ON_BN_CLICKED(IDC_BACKC, OnBackc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetColor message handlers

void SetColor::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
//	CDialog::OnLButtonDown(nFlags, point);

//	start = point;//������λ��
}

void SetColor::OnLButtonUp(UINT nFlags, CPoint point) 
{

/*	CDialog::OnLButtonUp(nFlags, point);

	end = point;//������λ��

	Gdiplus::Graphics g(this->GetDC()->GetSafeHdc());

    Gdiplus::Color color(192, 255, 0, 0 );

    Gdiplus::Rect eventRect(this->start.x,this->start.y,this->end.x,this->start.y + 100);
          
	Gdiplus::SolidBrush eventBrush(color);

	g.FillRectangle(&eventBrush,eventRect);*/
}

void SetColor::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	CDialog::OnMouseMove(nFlags, point);
}

BOOL SetColor::OnInitDialog() 
{
	

	

	/*CDialog::OnInitDialog();
	
	Gdiplus::Graphics g(this->GetDC()->GetSafeHdc());
	Gdiplus::Color color( 192, 255, 0, 0 );

	Gdiplus::Rect rectangle( 0, 0, 200, 200 );
	Gdiplus::SolidBrush solidBrush( color );
	g.FillRectangle( &solidBrush, rectangle );

	/////

	Gdiplus::Color color1(100,255,0,0);

	Gdiplus::Rect rectangle1(100,100,400,400);

	Gdiplus::SolidBrush solidBrush1(color1);

	g.FillRectangle(&solidBrush1,rectangle1);	
	  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
				  */
	return TRUE;
}

void SetColor::OnOK() 
{

	if(config.SaveConfig())//�����ļ�
	{
		AfxMessageBox("������Ϣ����ɹ�!");
	}
	else
	{
		AfxMessageBox("�����ļ�ԭ��������Ϣ����ʧ��!");
	}
	
	CDialog::OnOK();
}

void SetColor::OnCancel() 
{	
	CDialog::OnCancel();
}

HBRUSH SetColor::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);


	CBrush br;//��ˢ����      
    
	CRect rect;//�����ζ���          
	
	 switch (pWnd->GetDlgCtrlID())
	 {
	 case IDC_NFLOW:
	    
		  pDC->SetBkColor(config.nFlowC);
		  break;

	 case IDC_NSPO2:
		 pDC->SetBkColor(config.nSpO2C);
		 break;

	 case IDC_NPULSE:
		 pDC->SetBkColor(config.nPulseC);
		 break;

	 case IDC_NPLETH:
		 pDC->SetBkColor(config.nPlethC);
		 break;
		 
	case IDC_APNEAB:
		 pDC->SetBkColor(config.apneaB);
		 break;
	 case IDC_HYPOPNEAB:
		 pDC->SetBkColor(config.hypopneaB);
		 break;
	 case IDC_DESCENDB:
		 pDC->SetBkColor(config.descendB);
		 break;
	 case IDC_BACKC:
		 pDC->SetBkColor(config.backC);
		 break;

	 }
    
	return hbr;
}

//��������
void SetColor::OnNflow() 
{
   	COLORREF init = config.nFlowC;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.nFlowC = dlg.GetColor();

		Invalidate();
	}
}

//����Ѫ��
void SetColor::OnNspo2() 
{
	COLORREF init = config.nSpO2C;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.nSpO2C = dlg.GetColor();

		Invalidate();
	}
}


//��������
void SetColor::OnNpulse() 
{
	COLORREF init = config.nPulseC;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.nPulseC = dlg.GetColor();

		Invalidate();
	}	
}

//����Ѫ���ݻ�
void SetColor::OnNpleth() 
{
	COLORREF init = config.nPlethC;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.nPlethC = dlg.GetColor();

		Invalidate();
	}		
}

//���ú�����ͣ
void SetColor::OnApneab() 
{
	COLORREF init = config.apneaB;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.apneaB = dlg.GetColor();

		Invalidate();
	}		
}

//���õ�ͨ��
void SetColor::OnHypopneab() 
{
	COLORREF init = config.hypopneaB;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.hypopneaB = dlg.GetColor();

		Invalidate();
	}			
}

//��������
void SetColor::OnDescendb() 
{
	COLORREF init = config.descendB;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.descendB = dlg.GetColor();

		Invalidate();
	}			
}

//���ñ���
void SetColor::OnBackc() 
{
	COLORREF init = config.backC;

	CColorDialog dlg(init);//ѡ�񱳾�ɫ����

	if(IDOK == dlg.DoModal())
	{
		config.backC = dlg.GetColor();

		Invalidate();
	}			
}
