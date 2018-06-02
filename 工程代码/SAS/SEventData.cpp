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

//根据病例编号删除病例信息
bool SEventData::DeleteEvents(int sid)
{
	bool flag = false;//默认删除失败
  
	CString path;//原始路径


	path = GetFilePath(sid);//获得存放路径

   
	if(DeleteFile(path))//删除病例文件
	{

		 flag = true;

	}

   return flag;//返回删除结果
}


//获得病例数据
CString SEventData::GetFilePath(int sid)
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

	temp.Format("event_%d",sid);

	pathS += "SEvents\\" + temp + ".dat";

	return pathS;//获得实际路径

}

//获得病例事件列表
int SEventData::GetSEventList(int sid)
{
  CFile fileOper;//初始化文件操作类

  if(fileOper.Open(GetFilePath(sid),CFile::modeRead))
  {
 
	   int eCount = 0;//默认事件个数为零

	   fileOper.Read(&eCount,sizeof(int));//读取事件个数

	   DWORD pos = 0;//记录文件读取的位置，默认为零

	   for(int i = 0; i < eCount; i++)
	   {
         pos = fileOper.GetPosition();//获得文件当前指针

		 ANLEVENT sevent;//新建一个事件变量

		 fileOper.Seek(pos,CFile::begin);//设置读取指针
		 
		 fileOper.Read(&sevent,sizeof(ANLEVENT));//读取事件信息

		 this->sEventList.AddTail(sevent);//添加到事件链表的队尾
	   }
	  
      fileOper.Close();//关闭文件

	  return this->sEventList.GetCount();//返回事件个数

  }
  else
  {
	  return -1;//打开文件失败
  }
}

//将事件列表保存到文件中
int SEventData::SaveSEventList(int sid)
{
  CFile fileOper;//文件对象定义

  if(fileOper.Open(GetFilePath(sid),CFile::modeCreate|CFile::modeReadWrite))
  {
 
	   int eCount = this->sEventList.GetCount();//获得事件个数

	   fileOper.Write(&eCount,sizeof(int));//读取事件个数

	   int cSize = sizeof(ANLEVENT);//获得事件结构体的大小 
	   
	   POSITION pos = this->sEventList.GetHeadPosition();//获得第一个指针

	   while(pos != NULL)
	   {

	     fileOper.SeekToEnd();//移到文件的最后

		 ANLEVENT event = this->sEventList.GetNext(pos);//获得事件结构体
		 
		 fileOper.Write(&event,cSize);//写入文件

	   }
	  
      fileOper.Close();//关闭文件

	  return this->sEventList.GetCount();//返回事件个数

  }
  else
  {
	  return -1;//打开文件失败
  }
}
