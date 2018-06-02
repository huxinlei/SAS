#if !defined(AFX_SCASEDISPLAY_H__F195CBB9_92EB_425D_B7CD_4F41B576DFFC__INCLUDED_)
#define AFX_SCASEDISPLAY_H__F195CBB9_92EB_425D_B7CD_4F41B576DFFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SCaseDisplay.h : header file
//
#include "SCase.h"
#include "SEventData.h"
#include "SCaseFile.h"
#include "SConfig.h"

/////////////////////////////////////////////////////////////////////////////
// SCaseDisplay dialog

enum EventOper{INSERTAE,INSERTHE,INSERTDE,DELETEE,UPDATEE,NOOPER};
class SCaseDisplay : public CDialog
{

public:

	SCaseFile sdata;//

	SCase scase;//病例编号

    CMenu menu;//定义右键菜单对象

	CMenu *menuPop;//定义右键菜单对象指针

	SEventData eventOper;//事件文件操作对象

    CToolBar mToolbar;//定义工具条

	SConfig sconfig;//定义画图配置信息类的实例

	int position;//当前显示数据的当前坐标

	int realClientWidth;//实际数据可画区域宽度

	int realClientHight;//实际数据可画区域高度

	int realDrawCount;//实际一屏幕可画点总数

	int realX;//实际可画x轴开始坐标

	int realY;//实际可画y轴开始坐标

    ANLEVENT curEvent;//当前添加或者选中的事件

	EventOper eOper;//事件window相应类型

	bool IAflag;//添加呼吸暂停事件标记

	bool IHflag;//添加低通气事件标记

	bool IDflag;//添加氧减事件标记

	bool DEflag;//删除事件标记

	bool UPflag;//更新事件标记

	int realTrayHight;//当前段高度

	bool eDialogFlag;//事件列表更新标记

	int GetShowPosition(int realPosition,WSpeed wSpeed);//根据实际传入的坐标转换成屏幕显示的坐标

	void FindEvent(int position);//当选择事件定位事件并重绘


private:

	LOGFONT CreateFontBySize(int size);//根据传入的大小生成相应字体

	CString GetSCaseString();//生成病例信息

	int GetModeLength(WSpeed wSpeed);//根据传入的模式获得数据点数

	int GetRealIndex(int position,WSpeed wSpeed);//根据传入的模式和当前坐标返回实际

	CString GetTBHMSString(int position);//根据位置生成当前时间串

	CString GetTBMDString(int position);//根据位置生成月日串

	bool CheckEventExist(ANLEVENT event);//判断当前事件是不是存在

	bool DeleteEventByPoint(CPoint point);//根据传过来的单击点删除事件

    ANLEVENT GetEventByPoint(CPoint point);//根据传过来的坐标查找事件

	bool UpdateEventByNid(ANLEVENT event);//根据事件编号更新事件数据

	void UpdateEventNid();//更新事件编号，以防止编号冲突

// Construction
public:

	SCaseDisplay(SCase scase,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SCaseDisplay)
	enum { IDD = IDD_SCASEDISPLAY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SCaseDisplay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	//}}AFX_VIRTUAL

// Implementation


protected:


	// Generated message map functions
	//{{AFX_MSG(SCaseDisplay)
	afx_msg   void   OnInitMenuPopup(CMenu   *pPopupMenu,   UINT   nIndex,BOOL   bSysMenu); //相应菜单更状态更新
	afx_msg void OnPaint();	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd( CDC* pDC );
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWspeed002();
	afx_msg void OnWspeed02();
	afx_msg void OnWspeed1();
	afx_msg void OnWspeed1m();
	afx_msg void OnWspeed2();
	afx_msg void OnUpdateWspeed002(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWspeed02(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWspeed1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWspeed1m(CCmdUI* pCmdUI);
	afx_msg void OnUpdateWspeed2(CCmdUI* pCmdUI);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnA();
	afx_msg void OnE();
	afx_msg void OnUPDATEEE();
	afx_msg void OnD();
	afx_msg void OnH();
	afx_msg void OnShow();
	afx_msg void OnShowR();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCASEDISPLAY_H__F195CBB9_92EB_425D_B7CD_4F41B576DFFC__INCLUDED_)
