// SEventData.cpp: implementation of the SEventData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAS.h"
#include "SEventData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SEventData::SEventData()
{

}

SEventData::~SEventData()
{

}

//���ݲ������ɾ��������Ϣ
bool SEventData::DeleteEvents(int sid)
{
	bool flag = false;//Ĭ��ɾ��ʧ��
  
	CString path;//ԭʼ·��


	path = GetFilePath(sid);//��ô��·��

   
	if(DeleteFile(path))//ɾ�������ļ�
	{

		 flag = true;

	}

   return flag;//����ɾ�����
}


//��ò�������
CString SEventData::GetFilePath(int sid)
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

	temp.Format("event_%d",sid);

	pathS += "SEvents\\" + temp + ".dat";

	return pathS;//���ʵ��·��

}

//��ò����¼��б�
int SEventData::GetSEventList(int sid)
{
  CFile fileOper;//��ʼ���ļ�������

  if(fileOper.Open(GetFilePath(sid),CFile::modeRead))
  {
 
	   int eCount = 0;//Ĭ���¼�����Ϊ��

	   fileOper.Read(&eCount,sizeof(int));//��ȡ�¼�����

	   DWORD pos = 0;//��¼�ļ���ȡ��λ�ã�Ĭ��Ϊ��

	   for(int i = 0; i < eCount; i++)
	   {
         pos = fileOper.GetPosition();//����ļ���ǰָ��

		 ANLEVENT sevent;//�½�һ���¼�����

		 fileOper.Seek(pos,CFile::begin);//���ö�ȡָ��
		 
		 fileOper.Read(&sevent,sizeof(ANLEVENT));//��ȡ�¼���Ϣ

		 this->sEventList.AddTail(sevent);//��ӵ��¼�����Ķ�β
	   }
	  
      fileOper.Close();//�ر��ļ�

	  return this->sEventList.GetCount();//�����¼�����

  }
  else
  {
	  return -1;//���ļ�ʧ��
  }
}

//���¼��б��浽�ļ���
int SEventData::SaveSEventList(int sid)
{
  CFile fileOper;//�ļ�������

  if(fileOper.Open(GetFilePath(sid),CFile::modeCreate|CFile::modeReadWrite))
  {
 
	   int eCount = this->sEventList.GetCount();//����¼�����

	   fileOper.Write(&eCount,sizeof(int));//��ȡ�¼�����

	   int cSize = sizeof(ANLEVENT);//����¼��ṹ��Ĵ�С 
	   
	   POSITION pos = this->sEventList.GetHeadPosition();//��õ�һ��ָ��

	   while(pos != NULL)
	   {

	     fileOper.SeekToEnd();//�Ƶ��ļ������

		 ANLEVENT event = this->sEventList.GetNext(pos);//����¼��ṹ��
		 
		 fileOper.Write(&event,cSize);//д���ļ�

	   }
	  
      fileOper.Close();//�ر��ļ�

	  return this->sEventList.GetCount();//�����¼�����

  }
  else
  {
	  return -1;//���ļ�ʧ��
  }
}
