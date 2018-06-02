// SCaseData.cpp: implementation of the SCaseData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SAS.h"
#include "SCaseData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CONNSTRING "Provider=MSDASQL.1;Persist Security Info=False;Data Source=MS Access Database;Initial Catalog="
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SCaseData::SCaseData()
{
  this->connHead = CONNSTRING;

  CString temp = this->GetFilePath();//��ʱ��¼���ݿ��·��

  this->connString = this->connHead + temp;//��ʼ�����ݿ������·�� 
}

SCaseData::~SCaseData()
{

}

//����������ѯ��������
SCase SCaseData::SelectSCaseBySname(CString sname)
{
    CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//���ݿ������ַ���

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //��׼SQL���
   CString cmda = "";

   cmda = "select * from sleepdata where sname = '" + sname + "'";//��ѯ���е�����
  
   comd->CommandText = _bstr_t(cmda);//�õ�SQL���

   record=comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���

   SCase scase;//���岡������

   if(!record->end)
   {

		  int sid = record->GetCollect("sid").intVal;
		  
		  scase.SetSid(sid);//��ò������

		  CString sname = (char*)(_bstr_t)record->GetCollect("sname");

		  scase.SetSName(sname);//��ò�������

		  //CTime birthtime(record->GetCollect("sbirthday"));
		  COleDateTime btemp1(record->GetCollect("sbirthday"));

		  CTime birthtime(btemp1.GetYear(),btemp1.GetMonth(),btemp1.GetDay(),btemp1.GetHour(),btemp1.GetMinute(),btemp1.GetSecond());
         // CTime birthtime = vrecord->GetCollect("sbirthday").date;

		  scase.SetSbirthday(birthtime);//��ò�������


		  scase.SetSbirthday(birthtime);//��ò�������

		  int ssex = record->GetCollect("ssex").intVal;

		  scase.SetSsex(ssex);//����Ա�

		  int shigh = record->GetCollect("shigh").intVal;

		  scase.SetShigh(shigh);//��ø߶�

		  int sweight = record->GetCollect("sweight").intVal;

		  scase.SetSweight(sweight);//�������

		  //CTime starttime(record->GetCollect("startdate"));//��ÿ�ʼʱ��
		  //scase.SetSstartdate(starttime);
		  COleDateTime btemp2(record->GetCollect("startdate"));

		  CTime starttime(btemp2.GetYear(),btemp2.GetMonth(),btemp2.GetDay(),btemp2.GetHour(),btemp2.GetMinute(),btemp2.GetSecond());

		  scase.SetSstartdate(starttime);


		  CString scomment = (char*)(_bstr_t)record->GetCollect("scomment");

		  scase.SetScomment(scomment);//��ò�����ע

		  CString sdiagnosis = (char*)(_bstr_t)record->GetCollect("sdiagnosis");

		  scase.SetSdiagnosis(sdiagnosis);//������ҽ������

		  CString srecord = (char*)(_bstr_t)record->GetCollect("srecord");

		  scase.SetSrecord(srecord);//��ü�¼ҽ������

   }
 
   record->Close();//�ر����ݼ�

   pconnect->Close();//�ر����ݿ�����

   comd.Release();//�ͷ����ݿ����������ڴ�ռ�

   record.Release();//�ͷ����ݼ�¼�����ڴ�ռ�

   pconnect.Release();//�ͷ����ݿ����Ӷ�����ڴ�ռ�

   CoUninitialize();//�ͷ�ado��Դ

   return scase;//���ز�ѯ�Ĳ�����Ϣ
}

//���ݱ�Ų�ѯ��������
SCase SCaseData::SelectSCaseBySid(int sid)
{
    CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//���ݿ������ַ���

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //��׼SQL���
   CString cmda = "";

   cmda = "select * from sleepdata where sid = ";//��ѯ���е�����

   CString temp;

   temp.Format("%d",sid);//��ò������

   cmda += temp;
  
   comd->CommandText = _bstr_t(cmda);//�õ�SQL���

   record=comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���

   SCase scase;//���岡������

   if(!record->end)
   {

		  int sid = record->GetCollect("sid").intVal;
		  
		  scase.SetSid(sid);//��ò������

		  CString sname = (char*)(_bstr_t)record->GetCollect("sname");

		  scase.SetSName(sname);//��ò�������

		  //CTime birthtime(record->GetCollect("sbirthday"));
		  COleDateTime btemp1(record->GetCollect("sbirthday"));

		  CTime birthtime(btemp1.GetYear(),btemp1.GetMonth(),btemp1.GetDay(),btemp1.GetHour(),btemp1.GetMinute(),btemp1.GetSecond());
         // CTime birthtime = vrecord->GetCollect("sbirthday").date;

		  scase.SetSbirthday(birthtime);//��ò�������


		  scase.SetSbirthday(birthtime);//��ò�������

		  int ssex = record->GetCollect("ssex").intVal;

		  scase.SetSsex(ssex);//����Ա�

		  int shigh = record->GetCollect("shigh").intVal;

		  scase.SetShigh(shigh);//��ø߶�

		  int sweight = record->GetCollect("sweight").intVal;

		  scase.SetSweight(sweight);//�������

		  //CTime starttime(record->GetCollect("startdate"));//��ÿ�ʼʱ��
		  //scase.SetSstartdate(starttime);
		  COleDateTime btemp2(record->GetCollect("startdate"));

		  CTime starttime(btemp2.GetYear(),btemp2.GetMonth(),btemp2.GetDay(),btemp2.GetHour(),btemp2.GetMinute(),btemp2.GetSecond());

		  scase.SetSstartdate(starttime);


		  CString scomment = (char*)(_bstr_t)record->GetCollect("scomment");

		  scase.SetScomment(scomment);//��ò�����ע

		  CString sdiagnosis = (char*)(_bstr_t)record->GetCollect("sdiagnosis");

		  scase.SetSdiagnosis(sdiagnosis);//������ҽ������

		  CString srecord = (char*)(_bstr_t)record->GetCollect("srecord");

		  scase.SetSrecord(srecord);//��ü�¼ҽ������

   }
 
   record->Close();//�ر����ݼ�

   pconnect->Close();//�ر����ݿ�����

   comd.Release();//�ͷ����ݿ����������ڴ�ռ�

   record.Release();//�ͷ����ݼ�¼�����ڴ�ռ�

   pconnect.Release();//�ͷ����ݿ����Ӷ�����ڴ�ռ�

   CoUninitialize();//�ͷ�ado��Դ

   return scase;//���ز�ѯ�Ĳ�����Ϣ
}

//���ݱ��ɾ����������
int SCaseData::DeleteSCaseBySid(int sid)
{
   CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

  // _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//���ݿ������ַ���

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //��׼SQL���
   CString cmda = "";

   cmda = "DELETE * FROM sleepdata WHERE sid = ";//��ѯ���е�����

   CString temp;

   temp.Format("%d",sid);//�������

   cmda += temp;

   comd->CommandText = _bstr_t(cmda);//�õ�SQL���

   comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���
  
   pconnect->Close();//�ر����ݿ�����

   comd.Release();//�ͷ����ݿ����������ڴ�ռ�

   //record.Release();//�ͷ����ݼ�¼�����ڴ�ռ�

   pconnect.Release();//�ͷ����ݿ����Ӷ�����ڴ�ռ�

   CoUninitialize();//�ͷ�ado��Դ

   return sid;//����ɾ���������

}

//���没���޸�����
int SCaseData::SaveSCaseBySid(SCase scase)
{
	int result = -1;//Ĭ��-1�ǲ���ʧ��

   CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

  // _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//���ݿ������ַ���

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //��׼SQL���
   CString cmda = "";

   cmda = "UPDATE sleepdata SET sname = '";//��ѯ���е�����

   cmda += scase.GetSName();

   cmda += "',";

   CString temp;//��ʱ����

   //CString ttt = scase.GetSage() + scase.GetSage();
   temp.Format("%d",scase.GetSbirthday().GetYear());

   CString temp1 = temp;

   temp.Format("%d",scase.GetSbirthday().GetMonth());

   CString temp2 = temp;

   temp.Format("%d",scase.GetSbirthday().GetDay());

   CString temp3 = temp;

   temp.Format("%d",scase.GetSbirthday().GetHour());

   CString temp4 = temp;

   temp.Format("%d",scase.GetSbirthday().GetMinute());

   CString temp5 = temp;

   temp.Format("%d",scase.GetSbirthday().GetSecond());

   CString temp6 = temp;

   CString birthS = temp1 + "-" +
	                temp2  + "-" +
					temp3 + " " + 
					temp4 + ":" + 
					temp5 + ":" + temp6;

   cmda += "sbirthday=";

   cmda += "'";

   cmda += birthS;

   cmda += "',";

   temp.Format("%d",scase.GetSsex());

   cmda += "ssex = ";

   cmda += temp;

   cmda += ",";

   cmda += "shigh = ";

   temp.Format("%d",scase.GetShigh());

   cmda += temp;

   cmda += ",";

   cmda += "sweight = ";

   temp.Format("%d",scase.GetSweight());

   cmda += temp;

   cmda += ",";


   temp.Format("%d",scase.GetSstartdate().GetYear());

   temp1 = temp;

   temp.Format("%d",scase.GetSstartdate().GetMonth());

   temp2 = temp;

   temp.Format("%d",scase.GetSstartdate().GetDay());

   temp3 = temp;

   temp.Format("%d",scase.GetSstartdate().GetHour());

   temp4 = temp;

   temp.Format("%d",scase.GetSstartdate().GetMinute());

   temp5 = temp;

   temp.Format("%d",scase.GetSstartdate().GetSecond());

   temp6 = temp;

   CString startS = temp1 + "-" +
	                temp2 + "-" +
					temp3 + " " + 
					temp4 + ":" + 
					temp5 + ":" +
					temp6;

   cmda += "startdate = ";

   cmda += "'";

   cmda += startS;

   cmda += "',";

   cmda += "scomment = ";

   cmda += "'";

   cmda += scase.GetScomment();

   cmda += "',";

   cmda += "sdiagnosis = ";

   cmda += "'";

   cmda += scase.GetSdiagnosis();

   cmda += "',";

   cmda += "srecord = ";

   cmda += "'";

   cmda += scase.GetSrecord();

   cmda += "' where sid = ";

   temp.Format("%d",scase.GetSid());

   cmda += temp;

   comd->CommandText = _bstr_t(cmda);//�õ�SQL���

   comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���
   /////////////////////////////////////////////////////////////�������//////////////////////////

  result = scase.GetSid();//��øı䲡����id��

   /////////////////////////////////////////////////////

   pconnect->Close();//�ر����ݿ�����

   comd.Release();//�ͷ����ݿ����������ڴ�ռ�

   //record.Release();//�ͷ����ݼ�¼�����ڴ�ռ�

   pconnect.Release();//�ͷ����ݿ����Ӷ�����ڴ�ռ�

   CoUninitialize();//�ͷ�ado��Դ

   return result;
}

//�����µĲ�������
int SCaseData::InsertSCase(SCase scase)
{
	int result = -1;//Ĭ��-1�ǲ���ʧ��

   CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//���ݿ������ַ���

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //��׼SQL���
   CString cmda = "";

   cmda = "INSERT INTO sleepdata ( sname, sbirthday, ssex, shigh, sweight, startdate, scomment, sdiagnosis, srecord ) values('";//��ѯ���е�����

   cmda += scase.GetSName();

   cmda += "',";

   CString temp;//��ʱ����

   //CString ttt = scase.GetSage() + scase.GetSage();
   temp.Format("%d",scase.GetSbirthday().GetYear());

   CString temp1 = temp;

   temp.Format("%d",scase.GetSbirthday().GetMonth());

   CString temp2 = temp;

   temp.Format("%d",scase.GetSbirthday().GetDay());

   CString temp3 = temp;

   temp.Format("%d",scase.GetSbirthday().GetHour());

   CString temp4 = temp;

   temp.Format("%d",scase.GetSbirthday().GetMinute());

   CString temp5 = temp;

   temp.Format("%d",scase.GetSbirthday().GetSecond());

   CString temp6 = temp;

   CString birthS = temp1 + "-" +
	                temp2  + "-" +
					temp3 + " " + 
					temp4 + ":" + 
					temp5 + ":" + temp6;

   cmda += "'";

   cmda += birthS;

   cmda += "',";

   temp.Format("%d",scase.GetSsex());

   cmda += temp;

   cmda += ",";

   temp.Format("%d",scase.GetShigh());

   cmda += temp;

   cmda += ",";

   temp.Format("%d",scase.GetSweight());

   cmda += temp;

   cmda += ",";

   temp.Format("%d",scase.GetSstartdate().GetYear());

   temp1 = temp;

   temp.Format("%d",scase.GetSstartdate().GetMonth());

   temp2 = temp;

   temp.Format("%d",scase.GetSstartdate().GetDay());

   temp3 = temp;

   temp.Format("%d",scase.GetSstartdate().GetHour());

   temp4 = temp;

   temp.Format("%d",scase.GetSstartdate().GetMinute());

   temp5 = temp;

   temp.Format("%d",scase.GetSstartdate().GetSecond());

   temp6 = temp;

   CString startS = temp1 + "-" +
	                temp2 + "-" +
					temp3 + " " + 
					temp4 + ":" + 
					temp5 + ":" +
					temp6;

   cmda += "'";

   cmda += startS;

   cmda += "',";

    cmda += "'";

   cmda += scase.GetScomment();

   cmda += "',";


   cmda += "'";

   cmda += scase.GetSdiagnosis();

   cmda += "',";

    cmda += "'";

   cmda += scase.GetSrecord();

   cmda += "')";

   comd->CommandText = _bstr_t(cmda);//�õ�SQL���

   comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���
   /////////////////////////////////////////////////////////////�������//////////////////////////

  cmda = "select max(sid) as msid from sleepdata";

  comd->CommandText = _bstr_t(cmda);//�õ�SQL���

  record = comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���

  if(!record->end)
  {
     result = record->GetCollect("msid").intVal;
  }

   /////////////////////////////////////////////////////
   record->Close();//�ر����ݼ�

   pconnect->Close();//�ر����ݿ�����

   comd.Release();//�ͷ����ݿ����������ڴ�ռ�

   record.Release();//�ͷ����ݼ�¼�����ڴ�ռ�

   pconnect.Release();//�ͷ����ݿ����Ӷ�����ڴ�ռ�

   CoUninitialize();//�ͷ�ado��Դ

   return result;

}

//��ò����б�
int SCaseData::GetSCaseList()
{
    CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString = _bstr_t(this->connString);//���ݿ������ַ���

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //��׼SQL���
   CString cmda = "";

   cmda = "select * from sleepdata";//��ѯ���е�����
  
   comd->CommandText = _bstr_t(cmda);//�õ�SQL���

   record=comd->Execute(NULL,NULL,adCmdText);//ִ��SQL���

   int result = 0;//���Ĭ��0,��û�в������

   sCaseList.RemoveAll();//��ѯ֮ǰ����б���

   if(!record->end)
   { 
     
	   while(!record->end)
	   {

          SCase scase;//���岡������

		 // scase = new SCase();//ʵ����������

		  int sid = record->GetCollect("sid").intVal;
		  
		  scase.SetSid(sid);//��ò������

		  CString sname = (char*)(_bstr_t)record->GetCollect("sname");

		  scase.SetSName(sname);//��ò�������

		 // CTime birthtime(record->GetCollect("sbirthday"));
		  COleDateTime btemp1(record->GetCollect("sbirthday"));

		  CTime birthtime(btemp1.GetYear(),btemp1.GetMonth(),btemp1.GetDay(),btemp1.GetHour(),btemp1.GetMinute(),btemp1.GetSecond());
         // CTime birthtime = vrecord->GetCollect("sbirthday").date;

		  scase.SetSbirthday(birthtime);//��ò�������

		  int ssex = record->GetCollect("ssex").intVal;

		  scase.SetSsex(ssex);//����Ա�

		  int shigh = record->GetCollect("shigh").intVal;

		  scase.SetShigh(shigh);//��ø߶�

		  int sweight = record->GetCollect("sweight").intVal;

		  scase.SetSweight(sweight);//�������

		  //CTime starttime(record->GetCollect("startdate"));//��ÿ�ʼʱ��
		  COleDateTime btemp2(record->GetCollect("startdate"));

		  CTime starttime(btemp2.GetYear(),btemp2.GetMonth(),btemp2.GetDay(),btemp2.GetHour(),btemp2.GetMinute(),btemp2.GetSecond());

		  scase.SetSstartdate(starttime);

		  CString scomment = (char*)(_bstr_t)record->GetCollect("scomment");

		  scase.SetScomment(scomment);//��ò�����ע

		  CString sdiagnosis = (char*)(_bstr_t)record->GetCollect("sdiagnosis");

		  scase.SetSdiagnosis(sdiagnosis);//������ҽ������

		  CString srecord = (char*)(_bstr_t)record->GetCollect("srecord");

		  scase.SetSrecord(srecord);//��ü�¼ҽ������

		  sCaseList.AddTail(scase);//��ӵ�����������

		  record->MoveNext();//�ƶ�����һ��

	   }
	    

	   result = this->sCaseList.GetCount();
	   //m_id = (char *)(_bstr_t)record->GetCollect("id");//�õ����

	   //m_name = (char *)(_bstr_t)record->GetCollect("name");//�õ�ѧ������

	   //UpdateData(false);
   }
 
   record->Close();//�ر����ݼ�

   pconnect->Close();//�ر����ݿ�����

   comd.Release();//�ͷ����ݿ����������ڴ�ռ�

   record.Release();//�ͷ����ݼ�¼�����ڴ�ռ�

   pconnect.Release();//�ͷ����ݿ����Ӷ�����ڴ�ռ�

   CoUninitialize();//�ͷ�ado��Դ

   return result;
}

//��ò�������
CString SCaseData::GetFilePath()
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

	temp = "SAS";

	pathS += "SDatas\\" + temp + ".mdb";

	return pathS;//���ʵ��·��

}

