// SCaseShow.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SCaseShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SCaseShow

IMPLEMENT_DYNCREATE(SCaseShow, CFrameWnd)

SCaseShow::SCaseShow()
{
	Create(NULL,"������Ϣ��ʾ");
}

SCaseShow::~SCaseShow()
{
}


BEGIN_MESSAGE_MAP(SCaseShow, CFrameWnd)
	//{{AFX_MSG_MAP(SCaseShow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SCaseShow message handlers
