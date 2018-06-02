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
   hGain = 0;//���û�ͼ���̸߶���������Ĭ����Ϊ������Ļ����Ӧ
   
   wSpeed = WSPEED002;

   COLORREF selEventColor(RGB(139,0,0));//8B0000

   selEventC = selEventColor;//����ѡ���¼���ɫ

   COLORREF color(RGB(125,255,0));//��������������ɫ

   nFlowC = color;

   nPlethC = color;

   nPulseC = color;

   nSpO2C = color;

   apneaB = color;

   hypopneaB = color;

   descendB = color; 

   COLORREF backColor(RGB(255,255,255));//���ñ�����ɫ

   backC = backColor;//���ñ���ɫ

   COLORREF zeroColor(RGB(0,0,0));//����0����ɫ

   zeroShaftC = zeroColor;//����0������ɫ

   COLORREF  intervalColor(RGB(255,211,255));//������ֱ�������ɫ

   intervalC = intervalColor;//������ֱ�������ɫ

   horizontalHintHight = 30;//ˮƽ��ʾ���ĸ߶�Ϊ30����

   verticalHintWidth = 30;//��ֱ��ʾ����ʼ���Ϊ30����

   scaseHight = 40;//���ò�����Ϣ��ʾ����ʼ�����Ϊ40����


   Gdiplus::Color sColor1(192, 255, 211, 155);

   sColor = sColor1;//������Ϣ����ɫ��ʼ��


   Gdiplus::Color hColor1(192, 255, 0, 0);

   hColor = hColor1;//ˮƽ��Ϣ����ɫ��ʼ��


   Gdiplus::Color vColor1(192,255,255,0);

   vColor = vColor1;//��ֱ��Ϣ����ɫ��ʼ��


   rlWordSize = 16;//������ʾ�����СĬ��ֵ

   tbWordSize = 16;//������ʾ�����СĬ��ֵ

   scaseWordSize = 24;//����������ʾ��Ϣ����Ĭ��ֵ

   scaseSpaceTop = 7;//Ĭ�ϳ�ֵΪ7

   hInterval = 60;//Ĭ����ʮ���㻭һ������

   tbWordHighSpace = 15;//Ĭ�ϴ�СΪ15

   eventHightSpace = 15;//�¼��߶ȼ�ȥ��ֵ


   if(!LoadConfig())
   {
	   SaveConfig();//��������Ϣ���浽�ļ���
   }
   
}

SConfig::~SConfig()
{

}

bool SConfig::LoadConfig()
{

	  CFile fileOper;//��ʼ���ļ�������

  if(fileOper.Open(GetFilePath(),CFile::modeRead))
  {
	   DWORD pos = 0;//��¼�ļ���ȡ��λ�ã�Ĭ��Ϊ��

	   fileOper.Read(&apneaB,sizeof(COLORREF));//


       pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��
		
	   fileOper.Read(&hypopneaB,sizeof(COLORREF));//




	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��
		
	   fileOper.Read(&descendB,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��
		
	   fileOper.Read(&backC,sizeof(COLORREF));//



	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��
		
	   fileOper.Read(&nFlowC,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��
		
	   fileOper.Read(&nPlethC,sizeof(COLORREF));//


	   
	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��

	   fileOper.Read(&nPulseC,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��

	   fileOper.Read(&nSpO2C,sizeof(COLORREF));//


	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��

	   fileOper.Read(&hGain,sizeof(int));//


	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��

	   fileOper.Read(&wSpeed,sizeof(WSpeed));//


	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��

	   fileOper.Read(&tbWordSize,sizeof(int));//

	   	
	   pos = fileOper.GetPosition();//����ļ���ǰָ��

	   fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��

	   fileOper.Read(&rlWordSize,sizeof(int));//

	
       fileOper.Close();//�ر��ļ�

	   return true;//�����¼�����

  }
  else
  {
	  return false;//���ļ�ʧ��
  }
}

//���¼��б��浽�ļ���
bool SConfig::SaveConfig()
{
  CFile fileOper;//�ļ�������

  if(fileOper.Open(GetFilePath(),CFile::modeCreate|CFile::modeReadWrite))
  {
 
	   fileOper.Write(&apneaB,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&hypopneaB,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������

	   fileOper.Write(&descendB,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&backC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&nFlowC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������

	   
	   fileOper.Write(&nPlethC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&nPulseC,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������

	   
	   fileOper.Write(&nSpO2C,sizeof(COLORREF));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&hGain,sizeof(int));//

	   fileOper.SeekToEnd();//�Ƶ��ļ������

	   
	   fileOper.Write(&wSpeed,sizeof(WSpeed));//��ʾģʽ

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&tbWordSize,sizeof(int));//���������С

	   fileOper.SeekToEnd();//�Ƶ��ļ������


	   fileOper.Write(&rlWordSize,sizeof(int));//���������С

	   


	  
      fileOper.Close();//�ر��ļ�

	  return true;//�������ɹ�

  }
  else
  {
	  return false;//���ļ�ʧ��
  }
}

//���������Ϣ�ļ�·��
CString SConfig::GetFilePath()
{
	char path[MAX_PATH] = {0};

	GetModuleFileName(NULL,path,MAX_PATH);//������ݵ�·��

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

    CString pathS = realpath;//���·��

	CString temp;

	temp = "config";//�����ļ���������

	pathS += "SDatas\\" + temp + ".set";

	return pathS;//���ʵ��·��

}
