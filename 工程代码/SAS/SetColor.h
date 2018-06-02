#if !defined(AFX_SETCOLOR_H__439EFE38_4430_45C8_A626_0A4E20A32AED__INCLUDED_)
#define AFX_SETCOLOR_H__439EFE38_4430_45C8_A626_0A4E20A32AED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SConfig.h"
// SetColor.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// SetColor dialog

class SetColor : public CDialog
{

private:

	SConfig config;//定义配置信息类

// Construction
public:
	SetColor(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetColor)
	enum { IDD = IDD_COLORSET };

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    //CPoint start;//开始坐标
	//CPoint end;//结束坐标
	// Generated message map functions
	//{{AFX_MSG(SetColor)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNflow();
	afx_msg void OnNspo2();
	afx_msg void OnNpulse();
	afx_msg void OnNpleth();
	afx_msg void OnApneab();
	afx_msg void OnHypopneab();
	afx_msg void OnDescendb();
	afx_msg void OnBackc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCOLOR_H__439EFE38_4430_45C8_A626_0A4E20A32AED__INCLUDED_)
