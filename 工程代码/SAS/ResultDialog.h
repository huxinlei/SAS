#if !defined(AFX_RESULTDIALOG_H__442C4AC1_E329_4C01_BF4A_CF709E7EA44C__INCLUDED_)
#define AFX_RESULTDIALOG_H__442C4AC1_E329_4C01_BF4A_CF709E7EA44C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResultDialog.h : header file
//
#include "SCaseDisplay.h"
/////////////////////////////////////////////////////////////////////////////
// ResultDialog dialog

class ResultDialog : public CDialog
{
// Construction
public:
	ResultDialog(SCaseDisplay *parent,CWnd* pParent = NULL);   // standard constructor

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
	//{{AFX_VIRTUAL(ResultDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESULTDIALOG_H__442C4AC1_E329_4C01_BF4A_CF709E7EA44C__INCLUDED_)
