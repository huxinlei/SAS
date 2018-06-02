#if !defined(AFX_SEVENTLIST_H__D02F0ECC_2DEB_4A4F_8761_E157B24D2E0C__INCLUDED_)
#define AFX_SEVENTLIST_H__D02F0ECC_2DEB_4A4F_8761_E157B24D2E0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SEventList.h : header file
//
#include "SCaseDisplay.h"
/////////////////////////////////////////////////////////////////////////////
// SEventList dialog

class SEventList : public CDialog
{
private:
	CImageList m_ImageList;//图像

	TV_INSERTSTRUCT tvInsert;//插入结构

	HTREEITEM hDad;//树项

	HICON hIcon;//图标

	SCaseDisplay* parent;//调用此窗体的父窗体

// Construction
public:
	SEventList(SCaseDisplay *parent,CWnd* pParent = NULL);   // standard constructor

	void RefreshEventList(int nParam);//根据事件类型刷新事件列表

	CString GetTimeString(int position);//获得事件时间

// Dialog Data
	//{{AFX_DATA(SEventList)
	enum { IDD = IDD_EVENTDIALOG };
	CListCtrl	m_EventList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SEventList)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SEventList)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickEventlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedEventtree(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEVENTLIST_H__D02F0ECC_2DEB_4A4F_8761_E157B24D2E0C__INCLUDED_)
