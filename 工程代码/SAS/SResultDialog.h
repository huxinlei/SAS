#if !defined(AFX_SRESULTDIALOG_H__0D3BF951_20EF_4A8A_B361_390BCC2524AF__INCLUDED_)
#define AFX_SRESULTDIALOG_H__0D3BF951_20EF_4A8A_B361_390BCC2524AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SResultDialog.h : header file
//
#include "SCaseDisplay.h"

/////////////////////////////////////////////////////////////////////////////
// SResultDialog dialog

class SResultDialog : public CDialog
{
// Construction
public:
	SResultDialog(SCaseDisplay* parent,CWnd* pParent = NULL);   // standard constructor

public:
	SCaseDisplay* parent;//调用此窗体的父窗体


	int leftWidth;//左边宽度默认三十

	int bottomWidth;//底边宽度默认三十

// Dialog Data
	//{{AFX_DATA(ResultDialog)
	enum { IDD = IDD_RESULT };
	CStatic	m_Spo2;
	CString	m_ApneaC;
	CString	m_ApneaI;
	CString	m_DescendC;
	CString	m_DescendI;
	CString	m_HypopC;
	CString	m_HypopI;
	CString	m_MaxA;
	CString	m_MaxH;
	//}}AFX_DATA



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SResultDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SRESULTDIALOG_H__0D3BF951_20EF_4A8A_B361_390BCC2524AF__INCLUDED_)
