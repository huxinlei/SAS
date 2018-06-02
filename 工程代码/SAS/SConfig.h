// SConfig.h: interface for the SConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCONFIG_H__152F1DC6_BD91_473E_AC9B_42050E1F538C__INCLUDED_)
#define AFX_SCONFIG_H__152F1DC6_BD91_473E_AC9B_42050E1F538C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum WSpeed{WSPEED002,WSPEED02,WSPEED1,WSPEED2,WSPEED1M};

class SConfig  
{
public:

	SConfig();

	virtual ~SConfig();

    CString GetFilePath();//����ļ�·��

	bool SaveConfig();//����������Ϣ

	bool LoadConfig();//����������Ϣ

public:

	COLORREF selEventC;//����ѡ���¼�����ɫ

	COLORREF nFlowC;//����������ɫ

	COLORREF nPlethC;//�����ݻ�����ɫ

	COLORREF nPulseC;//����������ɫ

	COLORREF nSpO2C;//����Ѫ�����Ͷ���ɫ

	COLORREF apneaB;//���ú�����ͣ�¼���ɫ

	COLORREF hypopneaB;//���õ�ͨ���¼���ɫ

	COLORREF descendB;//���������¼���ɫ

	COLORREF backC;//������ɫ

	COLORREF zeroShaftC;//0��������ɫ

	COLORREF intervalC;//��ֱ����ɫ

	WSpeed wSpeed;//��������

	int hGain;//��ֵ��������

	int horizontalHintHight;//ˮƽ��ʾ���ĸ߶�

	int verticalHintWidth;//��ֱ��ʾ���Ŀ��

	int scaseHight;//������Ϣ��ʾ���߶�


	Gdiplus::Color sColor;//������Ϣ��ʾ����ɫ

	Gdiplus::Color hColor;//ˮƽ��Ϣ��ʾ����ɫ

    Gdiplus::Color vColor;//��ֱ��Ϣ��ʾ����ɫ

	int rlWordSize;//������ʾ�������С

	int scaseWordSize;//������Ϣ�����С

	int scaseSpaceTop;//������ʾ��Ϣ�����ϱ߿�Ŀհ�����

	int tbWordSize;//������ʾ�����С

	int hInterval;//�����ٸ��㻭һ������

	int tbWordHighSpace;//ʱ�������֮��ļ��

	int eventHightSpace;//��ͼʱ�¼��ĸ߶�


};

#endif // !defined(AFX_SCONFIG_H__152F1DC6_BD91_473E_AC9B_42050E1F538C__INCLUDED_)
