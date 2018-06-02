#if !defined(AFX_SETCONFIG_H__6E8EF441_8D72_4595_B636_17B28DE2B553__INCLUDED_)
#define AFX_SETCONFIG_H__6E8EF441_8D72_4595_B636_17B28DE2B553__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetConfig dialog
#include "SConfig.h"

class SetConfig : public CDialog
{
private:
	SConfig config;//定义配置信息类
// Construction
public:
	SetConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetConfig)
	enum { IDD = IDD_CONFIGSET };
	CSliderCtrl	m_tbWord;
	CSliderCtrl	m_rlWord;
	CComboBox	m_Mode;
	int		m_ModeV;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetConfig)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCONFIG_H__6E8EF441_8D72_4595_B636_17B28DE2B553__INCLUDED_)
