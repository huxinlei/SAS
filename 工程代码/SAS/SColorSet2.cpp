// SColorSet2.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SColorSet2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SColorSet2 dialog


SColorSet2::SColorSet2(CWnd* pParent /*=NULL*/)
	: CDialog(SColorSet2::IDD, pParent)
{
	//{{AFX_DATA_INIT(SColorSet2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SColorSet2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SColorSet2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SColorSet2, CDialog)
	//{{AFX_MSG_MAP(SColorSet2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SColorSet2 message handlers
