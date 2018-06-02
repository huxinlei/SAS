#if !defined(AFX_SCOLORSET2_H__00C8593D_9751_4113_BC49_4D07330B0928__INCLUDED_)
#define AFX_SCOLORSET2_H__00C8593D_9751_4113_BC49_4D07330B0928__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SColorSet2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SColorSet2 dialog

class SColorSet2 : public CDialog
{
// Construction
public:
	SColorSet2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SColorSet2)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SColorSet2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SColorSet2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCOLORSET2_H__00C8593D_9751_4113_BC49_4D07330B0928__INCLUDED_)
