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

   this->length = 0;//���ݳ�ʼ��
}

SCaseFile::~SCaseFile()
{
   if(length > 0)
   {
	   delete datas;//�ͷ��ڴ�ռ�
   }
}

//�������ָ������ã�δʹ��
DATA_BLOCK * SCaseFile::GetDatas()
{
  return datas;
}

//������ݵĳ���
int SCaseFile::GetLength()
{
	return length;
}

//���ݲ����ų�ʼ��������Ϣ
bool SCaseFile::InitDatas(int sid)
{
   	CFile fileOper;

	//AfxMessageBox(GetFilePath(sid));//��ӡ��·����

	if(fileOper.Open(GetFilePath(sid),CFile::modeReadWrite))//���ļ�
	{

	    this->length = fileOper.GetLength();//����ļ�����

		int totalLength = this->length;//����ļ��ܳ���

	    char *data = new char[this->length];//��ʼ���ַ����ռ�

	    fileOper.Read(data,this->length);//��ȡ���ݷ����ַ���������

	    int countLeap = this->length / sizeof(DATA_BLOCK);//ȷ��ѭ������

	    this->length = countLeap;//ȷ����������

	    //datas = new DATA_BLOCK[countLeap];//ʵ�������ݿռ�

		datas = (DATA_BLOCK*)data;//���DATA_BLOCKָ������,���ݶ�ȡ����

	    int dindex = 0;

	    for(dindex = 0; dindex < countLeap; dindex++)
		{

          //datas[dindex].nFlow = *((short*)&data[i]);//((short)data[i + 1] << 8) | data[i];//�����������

		  if(datas[dindex].nFlow > 500)
		  {
             datas[dindex].nFlow = 500;
		  }
		  else if(datas[dindex].nFlow < -500)
		  {
			  datas[dindex].nFlow = -500;
		  }
			    

	      //datas[dindex].nSpO2 = (unsigned)data[i+2];//���Ѫ������

		  if(datas[dindex].nSpO2 > 100)
		  {
			  datas[dindex].nSpO2 = 100;
		  }
		  else if(datas[dindex].nSpO2 < 0)
		  {
              datas[dindex].nSpO2 = 0;
		  }

	      //datas[dindex].nPulse = (unsigned)data[i+4];//�����������


		  if(datas[dindex].nPulse > 100)
		  {
			  datas[dindex].nPulse = 100;
		  }
		  else if(datas[dindex].nPulse < 0)
		  {
              datas[dindex].nPulse = 0;
		  }

	      //datas[dindex].nPleth = (unsigned)data[i+6];//���Ѫ�ݻ�����

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

      return true;//ȡ�����ݷ�����
	}
	else
	{
	  return false;//δȡ�����ݷ��ؼ�
	}
}
//��ò�������
CString SCaseFile::GetFilePath(int sid)
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

	temp.Format("scases_%d",sid);

	pathS += "SCases\\" + temp + ".dt";

	return pathS;//���ʵ��·��

}

//originpathԭ�����ݵ�·��
bool SCaseFile::CopyDatas(int sid,CString originpath)
{
	bool flag = false;
    CString npath;//���·��

	CString opath;//ԭʼ·��

	opath = originpath;

	npath = GetFilePath(sid);//��ô��·��

	CFile nfile;//�������ļ�

	CFile ofile;//�������ļ�

	if(ofile.Open(opath,CFile::modeReadWrite))//��ԭʼ�ļ�
	{


	  if(nfile.Open(npath,CFile::modeCreate | CFile::modeReadWrite))//�����ļ�
      {
	     char *temp;

	     temp = new char[ofile.GetLength()];

	     ofile.Read(temp,ofile.GetLength());

	     nfile.Write(temp,ofile.GetLength());//д�����ļ���ʵ�ָ���

	     delete temp;//�ͷ��ڴ�ռ�

	     ofile.Close();

	     nfile.Close();

		 flag = true;
	  }

	}

   return flag;
}

//���ݲ������ɾ��������Ϣ
bool SCaseFile::DeleteDatas(int sid)
{
	bool flag = false;//Ĭ��ɾ��ʧ��
  
	CString path;//ԭʼ·��


	path = GetFilePath(sid);//��ô��·��

   
	if(DeleteFile(path))//��ԭʼ�ļ�
	{

		 flag = true;

	}

   return flag;//����ɾ�����
}


