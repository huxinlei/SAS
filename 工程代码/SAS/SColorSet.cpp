// SColorSet.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SColorSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SColorSet dialog


SColorSet::SColorSet(CWnd* pParent /*=NULL*/)
	: CDialog(SColorSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(SColorSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SColorSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SColorSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SColorSet, CDialog)
	//{{AFX_MSG_MAP(SColorSet)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SColorSet message handlers
