#if !defined(AFX_SCASENEW_H__433D7C5D_D9DF_40A7_81A3_FB7F5ED81CD9__INCLUDED_)
#define AFX_SCASENEW_H__433D7C5D_D9DF_40A7_81A3_FB7F5ED81CD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SCaseNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SCaseNew dialog

class SCaseNew : public CDialog
{
// Construction
public:
	SCaseNew(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SCaseNew)
	enum { IDD = IDD_SCASENEW };
	CString	m_Scomment;
	CString	m_Sdiagnosis;
	CString	m_Sfilepath;
	CString	m_Srecord;
	int		m_Sage;
	CTime	m_Sbirthday;
	//CString	m_Senddate1;
	//CString	m_Senddate2;
	int		m_Shigh;
	int		m_Sid;
	CString	m_Sname1;
	CString	m_Sname2;
	int		m_Ssex;
	int		m_Sweight;
	//CString	m_Stotaltime;
	CTime	m_Sstartdate1;
	CTime	m_Sstartdate2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SCaseNew)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SCaseNew)
	afx_msg void OnImport();
	afx_msg void OnFilescan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCASENEW_H__433D7C5D_D9DF_40A7_81A3_FB7F5ED81CD9__INCLUDED_)
