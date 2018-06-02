// SASDoc.cpp : implementation of the CSASDoc class
//

#include "stdafx.h"
#include "SAS.h"

#include "SASDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSASDoc

IMPLEMENT_DYNCREATE(CSASDoc, CDocument)

BEGIN_MESSAGE_MAP(CSASDoc, CDocument)
	//{{AFX_MSG_MAP(CSASDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSASDoc construction/destruction

CSASDoc::CSASDoc()
{
	// TODO: add one-time construction code here

}

CSASDoc::~CSASDoc()
{
}

BOOL CSASDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSASDoc serialization

void CSASDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSASDoc diagnostics

#ifdef _DEBUG
void CSASDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSASDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSASDoc commands
