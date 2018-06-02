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

    CString GetFilePath();//获得文件路径

	bool SaveConfig();//保存配置信息

	bool LoadConfig();//加载配置信息

public:

	COLORREF selEventC;//设置选中事件的颜色

	COLORREF nFlowC;//设置气流颜色

	COLORREF nPlethC;//设置容积波颜色

	COLORREF nPulseC;//设置脉搏颜色

	COLORREF nSpO2C;//设置血氧饱和度颜色

	COLORREF apneaB;//设置呼吸暂停事件颜色

	COLORREF hypopneaB;//设置低通气事件颜色

	COLORREF descendB;//设置氧减事件颜色

	COLORREF backC;//背景颜色

	COLORREF zeroShaftC;//0轴线条颜色

	COLORREF intervalC;//竖直线颜色

	WSpeed wSpeed;//走速设置

	int hGain;//数值增益设置

	int horizontalHintHight;//水平提示条的高度

	int verticalHintWidth;//竖直提示条的宽度

	int scaseHight;//病例信息提示条高度


	Gdiplus::Color sColor;//病例信息提示条颜色

	Gdiplus::Color hColor;//水平信息提示条颜色

    Gdiplus::Color vColor;//竖直信息提示条颜色

	int rlWordSize;//左右提示条字体大小

	int scaseWordSize;//病例信息字体大小

	int scaseSpaceTop;//病例提示信息距离上边框的空白区域

	int tbWordSize;//上下提示字体大小

	int hInterval;//隔多少个点画一条竖线

	int tbWordHighSpace;//时间和月日之间的间距

	int eventHightSpace;//画图时事件的高度


};

#endif // !defined(AFX_SCONFIG_H__152F1DC6_BD91_473E_AC9B_42050E1F538C__INCLUDED_)
