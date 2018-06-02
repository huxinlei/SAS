// SCaseFile.cpp: implementation of the SCaseFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAS.h"
#include "SCaseFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SCaseFile::SCaseFile()
{
   this->datas = NULL;

   this->length = 0;//数据初始化
}

SCaseFile::~SCaseFile()
{
   if(length > 0)
   {
	   delete datas;//释放内存空间
   }
}

//获得数据指针的引用，未使用
DATA_BLOCK * SCaseFile::GetDatas()
{
  return datas;
}

//获得数据的长度
int SCaseFile::GetLength()
{
	return length;
}

//根据病例号初始化病例信息
bool SCaseFile::InitDatas(int sid)
{
   	CFile fileOper;

	//AfxMessageBox(GetFilePath(sid));//打印出路径来

	if(fileOper.Open(GetFilePath(sid),CFile::modeReadWrite))//打开文件
	{

	    this->length = fileOper.GetLength();//获得文件长度

		int totalLength = this->length;//获得文件总长度

	    char *data = new char[this->length];//初始化字符串空间

	    fileOper.Read(data,this->length);//读取数据放入字符串数组中

	    int countLeap = this->length / sizeof(DATA_BLOCK);//确定循环次数

	    this->length = countLeap;//确定数据总数

	    //datas = new DATA_BLOCK[countLeap];//实例化数据空间

		datas = (DATA_BLOCK*)data;//获得DATA_BLOCK指针引用,数据读取问题

	    int dindex = 0;

	    for(dindex = 0; dindex < countLeap; dindex++)
		{

          //datas[dindex].nFlow = *((short*)&data[i]);//((short)data[i + 1] << 8) | data[i];//获得气流数据

		  if(datas[dindex].nFlow > 500)
		  {
             datas[dindex].nFlow = 500;
		  }
		  else if(datas[dindex].nFlow < -500)
		  {
			  datas[dindex].nFlow = -500;
		  }
			    

	      //datas[dindex].nSpO2 = (unsigned)data[i+2];//获得血氧数据

		  if(datas[dindex].nSpO2 > 100)
		  {
			  datas[dindex].nSpO2 = 100;
		  }
		  else if(datas[dindex].nSpO2 < 0)
		  {
              datas[dindex].nSpO2 = 0;
		  }

	      //datas[dindex].nPulse = (unsigned)data[i+4];//获得脉率数据


		  if(datas[dindex].nPulse > 100)
		  {
			  datas[dindex].nPulse = 100;
		  }
		  else if(datas[dindex].nPulse < 0)
		  {
              datas[dindex].nPulse = 0;
		  }

	      //datas[dindex].nPleth = (unsigned)data[i+6];//获得血容积数据

		  if(datas[dindex].nPleth > 100)
		  {
			  datas[dindex].nPleth = 100;
		  }
		  else if(datas[dindex].nPleth < 0)
		  {
              datas[dindex].nPleth = 0;
		  }

		}


	  fileOper.Close();

      return true;//取得数据返回真
	}
	else
	{
	  return false;//未取得数据返回假
	}
}
//获得病例数据
CString SCaseFile::GetFilePath(int sid)
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

	temp.Format("scases_%d",sid);

	pathS += "SCases\\" + temp + ".dt";

	return pathS;//获得实际路径

}

//originpath原来数据的路径
bool SCaseFile::CopyDatas(int sid,CString originpath)
{
	bool flag = false;
    CString npath;//存放路径

	CString opath;//原始路径

	opath = originpath;

	npath = GetFilePath(sid);//获得存放路径

	CFile nfile;//操作新文件

	CFile ofile;//操作老文件

	if(ofile.Open(opath,CFile::modeReadWrite))//打开原始文件
	{


	  if(nfile.Open(npath,CFile::modeCreate | CFile::modeReadWrite))//打开新文件
      {
	     char *temp;

	     temp = new char[ofile.GetLength()];

	     ofile.Read(temp,ofile.GetLength());

	     nfile.Write(temp,ofile.GetLength());//写入新文件，实现复制

	     delete temp;//释放内存空间

	     ofile.Close();

	     nfile.Close();

		 flag = true;
	  }

	}

   return flag;
}

//根据病例编号删除病例信息
bool SCaseFile::DeleteDatas(int sid)
{
	bool flag = false;//默认删除失败
  
	CString path;//原始路径


	path = GetFilePath(sid);//获得存放路径

   
	if(DeleteFile(path))//打开原始文件
	{

		 flag = true;

	}

   return flag;//返回删除结果
}


