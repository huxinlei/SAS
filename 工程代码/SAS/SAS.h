// SAS.h : main header file for the SAS application
//

#if !defined(AFX_SAS_H__B653A0C5_E478_44F1_B568_4B3D46A89844__INCLUDED_)
#define AFX_SAS_H__B653A0C5_E478_44F1_B568_4B3D46A89844__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSASApp:
// See SAS.cpp for the implementation of this class
//

class CSASApp : public CWinApp
{
public:
	CSASApp();
	ULONG_PTR gdiplusToken;
	GdiplusStartupInput gdiplusStartupInput;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSASApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSASApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAS_H__B653A0C5_E478_44F1_B568_4B3D46A89844__INCLUDED_)
