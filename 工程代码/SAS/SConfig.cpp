// SConfig.cpp: implementation of the SConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAS.h"
#include "SConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SConfig::SConfig()
{
   hGain = 0;//设置画图托盘高度像素数，默认零为启用屏幕自适应
   
   wSpeed = WSPEED002;

   COLORREF selEventColor(RGB(139,0,0));//8B0000

   selEventC = selEventColor;//设置选中事件颜色

   COLORREF color(RGB(125,255,0));//设置数据线条颜色

   nFlowC = color;

   nPlethC = color;

   nPulseC = color;

   nSpO2C = color;

   apneaB = color;

   hypopneaB = color;

   descendB = color; 

   COLORREF backColor(RGB(255,255,255));//设置背景颜色

   backC = backColor;//设置背景色

   COLORREF zeroColor(RGB(0,0,0));//设置0轴颜色

   zeroShaftC = zeroColor;//设置0轴线条色

   COLORREF  intervalColor(RGB(255,211,255));//设置竖直间隔线颜色

   intervalC = intervalColor;//设置竖直间隔线颜色

   horizontalHintHight = 30;//水平提示条的高度为30像素

   verticalHintWidth = 30;//竖直提示条初始宽度为30像素

   scaseHight = 40;//设置病例信息提示条初始化宽度为40像素


   Gdiplus::Color sColor1(192, 255, 211, 155);

   sColor = sColor1;//病例信息条颜色初始化


   Gdiplus::Color hColor1(192, 255, 0, 0);

   hColor = hColor1;//水平信息条颜色初始化


   Gdiplus::Color vColor1(192,255,255,0);

   vColor = vColor1;//竖直信息条颜色初始化


   rlWordSize = 16;//左右提示字体大小默认值

   tbWordSize = 16;//上下提示字体大小默认值

   scaseWordSize = 24;//病例字体提示信息字体默认值

   scaseSpaceTop = 7;//默认初值为7

   hInterval = 60;//默认四十个点画一条竖线

   tbWordHighSpace = 15;//默认大小为15

   eventHightSpace = 15;//事件高度减去的值


   if(!LoadConfig())
   {
	   SaveConfig();//将配置信息保存到文件中
   }
   
}

SConfig::~SConfig()
{

}

bool SConfig::LoadConfig()
{

	  CFile fileOper;//初始化文件操作类

  if(fileOper.Open(GetFilePath(),CFile::modeRead))
  {
	   DWORD pos = 0;//记录文件读取的位置，默认为零

	   fileOper.Read(&apneaB,sizeof(COLORREF));//


       pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针
		
	   fileOper.Read(&hypopneaB,sizeof(COLORREF));//




	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针
		
	   fileOper.Read(&descendB,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针
		
	   fileOper.Read(&backC,sizeof(COLORREF));//



	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针
		
	   fileOper.Read(&nFlowC,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针
		
	   fileOper.Read(&nPlethC,sizeof(COLORREF));//


	   
	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针

	   fileOper.Read(&nPulseC,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针

	   fileOper.Read(&nSpO2C,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针

	   fileOper.Read(&hGain,sizeof(int));//


	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针

	   fileOper.Read(&wSpeed,sizeof(WSpeed));//


	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针

	   fileOper.Read(&tbWordSize,sizeof(int));//

	   	
	   pos = fileOper.GetPosition();//获得文件当前指针

	   fileOper.Seek(pos,CFile::begin);//设置读取指针

	   fileOper.Read(&rlWordSize,sizeof(int));//

	
       fileOper.Close();//关闭文件

	   return true;//返回事件个数

  }
  else
  {
	  return false;//打开文件失败
  }
}

//将事件列表保存到文件中
bool SConfig::SaveConfig()
{
  CFile fileOper;//文件对象定义

  if(fileOper.Open(GetFilePath(),CFile::modeCreate|CFile::modeReadWrite))
  {
 
	   fileOper.Write(&apneaB,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&hypopneaB,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后

	   fileOper.Write(&descendB,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&backC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&nFlowC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后

	   
	   fileOper.Write(&nPlethC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&nPulseC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后

	   
	   fileOper.Write(&nSpO2C,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&hGain,sizeof(int));//

	   fileOper.SeekToEnd();//移到文件的最后

	   
	   fileOper.Write(&wSpeed,sizeof(WSpeed));//显示模式

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&tbWordSize,sizeof(int));//上下字体大小

	   fileOper.SeekToEnd();//移到文件的最后


	   fileOper.Write(&rlWordSize,sizeof(int));//左右字体大小

	   


	  
      fileOper.Close();//关闭文件

	  return true;//返操作成功

  }
  else
  {
	  return false;//打开文件失败
  }
}

//获得配置信息文件路径
CString SConfig::GetFilePath()
{
	char path[MAX_PATH] = {0};

	GetModuleFileName(NULL,path,MAX_PATH);//获得数据的路径

	int index;

	for(index = MAX_PATH - 1; index >= 0; index--)
	{
		if(path[index] == '\\')
		{
			break;
		}	
	}

	char realpath[MAX_PATH];

	for(int cindex = 0; cindex <= index; cindex++)
	{
		realpath[cindex] = path[cindex];
	}

	realpath[cindex] = '\0';

    CString pathS = realpath;//获得路径

	CString temp;

	temp = "config";//设置文件配置名称

	pathS += "SDatas\\" + temp + ".set";

	return pathS;//获得实际路径

}
