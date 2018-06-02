#if !defined(AFX_SCOLORSET_H__BA4EA386_C8B1_4D6A_9E1F_CA11F5A496A9__INCLUDED_)
#define AFX_SCOLORSET_H__BA4EA386_C8B1_4D6A_9E1F_CA11F5A496A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SColorSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SColorSet dialog

class SColorSet : public CDialog
{
// Construction
public:
	SColorSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SColorSet)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SColorSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SColorSet)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOLORSET_H__BA4EA386_C8B1_4D6A_9E1F_CA11F5A496A9__INCLUDED_)
