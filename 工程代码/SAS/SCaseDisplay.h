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

	SCase scase;//�������

    CMenu menu;//�����Ҽ��˵�����

	CMenu *menuPop;//�����Ҽ��˵�����ָ��

	SEventData eventOper;//�¼��ļ���������

    CToolBar mToolbar;//���幤����

	SConfig sconfig;//���廭ͼ������Ϣ���ʵ��

	int position;//��ǰ��ʾ���ݵĵ�ǰ����

	int realClientWidth;//ʵ�����ݿɻ�������

	int realClientHight;//ʵ�����ݿɻ�����߶�

	int realDrawCount;//ʵ��һ��Ļ�ɻ�������

	int realX;//ʵ�ʿɻ�x�Ὺʼ����

	int realY;//ʵ�ʿɻ�y�Ὺʼ����

    ANLEVENT curEvent;//��ǰ��ӻ���ѡ�е��¼�

	EventOper eOper;//�¼�window��Ӧ����

	bool IAflag;//��Ӻ�����ͣ�¼����

	bool IHflag;//��ӵ�ͨ���¼����

	bool IDflag;//��������¼����

	bool DEflag;//ɾ���¼����

	bool UPflag;//�����¼����

	int realTrayHight;//��ǰ�θ߶�

	bool eDialogFlag;//�¼��б���±��

	int GetShowPosition(int realPosition,WSpeed wSpeed);//����ʵ�ʴ��������ת������Ļ��ʾ������

	void FindEvent(int position);//��ѡ���¼���λ�¼����ػ�


private:

	LOGFONT CreateFontBySize(int size);//���ݴ���Ĵ�С������Ӧ����

	CString GetSCaseString();//���ɲ�����Ϣ

	int GetModeLength(WSpeed wSpeed);//���ݴ����ģʽ������ݵ���

	int GetRealIndex(int position,WSpeed wSpeed);//���ݴ����ģʽ�͵�ǰ���귵��ʵ��

	CString GetTBHMSString(int position);//����λ�����ɵ�ǰʱ�䴮

	CString GetTBMDString(int position);//����λ���������մ�

	bool CheckEventExist(ANLEVENT event);//�жϵ�ǰ�¼��ǲ��Ǵ���

	bool DeleteEventByPoint(CPoint point);//���ݴ������ĵ�����ɾ���¼�

    ANLEVENT GetEventByPoint(CPoint point);//���ݴ���������������¼�

	bool UpdateEventByNid(ANLEVENT event);//�����¼���Ÿ����¼�����

	void UpdateEventNid();//�����¼���ţ��Է�ֹ��ų�ͻ

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
	afx_msg   void   OnInitMenuPopup(CMenu   *pPopupMenu,   UINT   nIndex,BOOL   bSysMenu); //��Ӧ�˵���״̬����
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
