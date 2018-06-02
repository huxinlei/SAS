// SASView.h : interface of the CSASView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SASVIEW_H__C8A894BA_D912_4671_B38E_C7E8CB7A808E__INCLUDED_)
#define AFX_SASVIEW_H__C8A894BA_D912_4671_B38E_C7E8CB7A808E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SCaseData.h"
#include "SCaseFile.h"
#include "SEventData.h"

class CSASView : public CFormView
{
protected: // create from serialization only
	CSASView();
	DECLARE_DYNCREATE(CSASView)

public:
	//{{AFX_DATA(CSASView)
	enum { IDD = IDD_SAS_FORM };
	CStatic	m_Picture;
	CListCtrl	m_ScaseList;
	int		m_Sid;
	CString	m_Sname1;
	CString	m_Sname2;
	int		m_Ssex;
	int		m_Shigh;
	int		m_Sweight;
	int		m_Stotaltime;
	CTime	m_Sstartdate1;
	CTime	m_Sstartdate2;
	CTime	m_Senddate1;
	CTime	m_Senddate2;
	CTime	m_Sbirthday;
	CString	m_Scomment;
	CString	m_Sdiagnosis;
	CString	m_Srecord;
	int		m_Sage;
	CString	m_Pad;
	//}}AFX_DATA

// Attributes
public:
	CSASDoc* GetDocument();

	void RefreshList();

	SCase GetScaseBySid(int sid);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSASView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSASView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    SCaseData dataOper;//病例信息列表

    SCaseFile dataFile;//病例文件操作类

	SEventData eventOper;//病例事件文件操作类

// Generated message map functions
protected:
	//{{AFX_MSG(CSASView)
	afx_msg void OnOpen();
	afx_msg void OnCancel();
	afx_msg void OnSave();
	afx_msg void OnNewscase();
	afx_msg void OnClickPlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnColorset();
	afx_msg void OnWordandspeed();
	afx_msg void OnItemchangedPlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPadw();
	afx_msg void OnPadr();
	afx_msg void OnConsult();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SASView.cpp
inline CSASDoc* CSASView::GetDocument()
   { return (CSASDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SASVIEW_H__C8A894BA_D912_4671_B38E_C7E8CB7A808E__INCLUDED_)
