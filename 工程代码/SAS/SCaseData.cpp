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

  CString temp = this->GetFilePath();//临时记录数据库的路径

  this->connString = this->connHead + temp;//初始化数据库的连接路径 
}

SCaseData::~SCaseData()
{

}

//根据姓名查询病例数据
SCase SCaseData::SelectSCaseBySname(CString sname)
{
    CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//数据库连接字符串

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //标准SQL语句
   CString cmda = "";

   cmda = "select * from sleepdata where sname = '" + sname + "'";//查询所有的数据
  
   comd->CommandText = _bstr_t(cmda);//得到SQL语句

   record=comd->Execute(NULL,NULL,adCmdText);//执行SQL语句

   SCase scase;//定义病例变量

   if(!record->end)
   {

		  int sid = record->GetCollect("sid").intVal;
		  
		  scase.SetSid(sid);//获得病例编号

		  CString sname = (char*)(_bstr_t)record->GetCollect("sname");

		  scase.SetSName(sname);//获得病例名称

		  //CTime birthtime(record->GetCollect("sbirthday"));
		  COleDateTime btemp1(record->GetCollect("sbirthday"));

		  CTime birthtime(btemp1.GetYear(),btemp1.GetMonth(),btemp1.GetDay(),btemp1.GetHour(),btemp1.GetMinute(),btemp1.GetSecond());
         // CTime birthtime = vrecord->GetCollect("sbirthday").date;

		  scase.SetSbirthday(birthtime);//获得病例生日


		  scase.SetSbirthday(birthtime);//获得病例生日

		  int ssex = record->GetCollect("ssex").intVal;

		  scase.SetSsex(ssex);//获得性别

		  int shigh = record->GetCollect("shigh").intVal;

		  scase.SetShigh(shigh);//获得高度

		  int sweight = record->GetCollect("sweight").intVal;

		  scase.SetSweight(sweight);//获得重量

		  //CTime starttime(record->GetCollect("startdate"));//获得开始时间
		  //scase.SetSstartdate(starttime);
		  COleDateTime btemp2(record->GetCollect("startdate"));

		  CTime starttime(btemp2.GetYear(),btemp2.GetMonth(),btemp2.GetDay(),btemp2.GetHour(),btemp2.GetMinute(),btemp2.GetSecond());

		  scase.SetSstartdate(starttime);


		  CString scomment = (char*)(_bstr_t)record->GetCollect("scomment");

		  scase.SetScomment(scomment);//获得病例备注

		  CString sdiagnosis = (char*)(_bstr_t)record->GetCollect("sdiagnosis");

		  scase.SetSdiagnosis(sdiagnosis);//获得诊断医生名称

		  CString srecord = (char*)(_bstr_t)record->GetCollect("srecord");

		  scase.SetSrecord(srecord);//获得记录医生名称

   }
 
   record->Close();//关闭数据集

   pconnect->Close();//关闭数据库连接

   comd.Release();//释放数据库操作对象的内存空间

   record.Release();//释放数据记录集的内存空间

   pconnect.Release();//释放数据库连接对象的内存空间

   CoUninitialize();//释放ado资源

   return scase;//返回查询的病例信息
}

//根据编号查询病例数据
SCase SCaseData::SelectSCaseBySid(int sid)
{
    CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//数据库连接字符串

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //标准SQL语句
   CString cmda = "";

   cmda = "select * from sleepdata where sid = ";//查询所有的数据

   CString temp;

   temp.Format("%d",sid);//获得病例编号

   cmda += temp;
  
   comd->CommandText = _bstr_t(cmda);//得到SQL语句

   record=comd->Execute(NULL,NULL,adCmdText);//执行SQL语句

   SCase scase;//定义病例变量

   if(!record->end)
   {

		  int sid = record->GetCollect("sid").intVal;
		  
		  scase.SetSid(sid);//获得病例编号

		  CString sname = (char*)(_bstr_t)record->GetCollect("sname");

		  scase.SetSName(sname);//获得病例名称

		  //CTime birthtime(record->GetCollect("sbirthday"));
		  COleDateTime btemp1(record->GetCollect("sbirthday"));

		  CTime birthtime(btemp1.GetYear(),btemp1.GetMonth(),btemp1.GetDay(),btemp1.GetHour(),btemp1.GetMinute(),btemp1.GetSecond());
         // CTime birthtime = vrecord->GetCollect("sbirthday").date;

		  scase.SetSbirthday(birthtime);//获得病例生日


		  scase.SetSbirthday(birthtime);//获得病例生日

		  int ssex = record->GetCollect("ssex").intVal;

		  scase.SetSsex(ssex);//获得性别

		  int shigh = record->GetCollect("shigh").intVal;

		  scase.SetShigh(shigh);//获得高度

		  int sweight = record->GetCollect("sweight").intVal;

		  scase.SetSweight(sweight);//获得重量

		  //CTime starttime(record->GetCollect("startdate"));//获得开始时间
		  //scase.SetSstartdate(starttime);
		  COleDateTime btemp2(record->GetCollect("startdate"));

		  CTime starttime(btemp2.GetYear(),btemp2.GetMonth(),btemp2.GetDay(),btemp2.GetHour(),btemp2.GetMinute(),btemp2.GetSecond());

		  scase.SetSstartdate(starttime);


		  CString scomment = (char*)(_bstr_t)record->GetCollect("scomment");

		  scase.SetScomment(scomment);//获得病例备注

		  CString sdiagnosis = (char*)(_bstr_t)record->GetCollect("sdiagnosis");

		  scase.SetSdiagnosis(sdiagnosis);//获得诊断医生名称

		  CString srecord = (char*)(_bstr_t)record->GetCollect("srecord");

		  scase.SetSrecord(srecord);//获得记录医生名称

   }
 
   record->Close();//关闭数据集

   pconnect->Close();//关闭数据库连接

   comd.Release();//释放数据库操作对象的内存空间

   record.Release();//释放数据记录集的内存空间

   pconnect.Release();//释放数据库连接对象的内存空间

   CoUninitialize();//释放ado资源

   return scase;//返回查询的病例信息
}

//根据编号删除病例数据
int SCaseData::DeleteSCaseBySid(int sid)
{
   CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

  // _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//数据库连接字符串

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //标准SQL语句
   CString cmda = "";

   cmda = "DELETE * FROM sleepdata WHERE sid = ";//查询所有的数据

   CString temp;

   temp.Format("%d",sid);//病例编号

   cmda += temp;

   comd->CommandText = _bstr_t(cmda);//得到SQL语句

   comd->Execute(NULL,NULL,adCmdText);//执行SQL语句
  
   pconnect->Close();//关闭数据库连接

   comd.Release();//释放数据库操作对象的内存空间

   //record.Release();//释放数据记录集的内存空间

   pconnect.Release();//释放数据库连接对象的内存空间

   CoUninitialize();//释放ado资源

   return sid;//返回删除病例编号

}

//保存病例修改数据
int SCaseData::SaveSCaseBySid(SCase scase)
{
	int result = -1;//默认-1是插入失败

   CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

  // _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//数据库连接字符串

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //标准SQL语句
   CString cmda = "";

   cmda = "UPDATE sleepdata SET sname = '";//查询所有的数据

   cmda += scase.GetSName();

   cmda += "',";

   CString temp;//临时变量

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

   comd->CommandText = _bstr_t(cmda);//得到SQL语句

   comd->Execute(NULL,NULL,adCmdText);//执行SQL语句
   /////////////////////////////////////////////////////////////处理代码//////////////////////////

  result = scase.GetSid();//获得改变病例的id号

   /////////////////////////////////////////////////////

   pconnect->Close();//关闭数据库连接

   comd.Release();//释放数据库操作对象的内存空间

   //record.Release();//释放数据记录集的内存空间

   pconnect.Release();//释放数据库连接对象的内存空间

   CoUninitialize();//释放ado资源

   return result;
}

//插入新的病例数据
int SCaseData::InsertSCase(SCase scase)
{
	int result = -1;//默认-1是插入失败

   CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString =  _bstr_t(this->connString);//数据库连接字符串

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //标准SQL语句
   CString cmda = "";

   cmda = "INSERT INTO sleepdata ( sname, sbirthday, ssex, shigh, sweight, startdate, scomment, sdiagnosis, srecord ) values('";//查询所有的数据

   cmda += scase.GetSName();

   cmda += "',";

   CString temp;//临时变量

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

   comd->CommandText = _bstr_t(cmda);//得到SQL语句

   comd->Execute(NULL,NULL,adCmdText);//执行SQL语句
   /////////////////////////////////////////////////////////////处理代码//////////////////////////

  cmda = "select max(sid) as msid from sleepdata";

  comd->CommandText = _bstr_t(cmda);//得到SQL语句

  record = comd->Execute(NULL,NULL,adCmdText);//执行SQL语句

  if(!record->end)
  {
     result = record->GetCollect("msid").intVal;
  }

   /////////////////////////////////////////////////////
   record->Close();//关闭数据集

   pconnect->Close();//关闭数据库连接

   comd.Release();//释放数据库操作对象的内存空间

   record.Release();//释放数据记录集的内存空间

   pconnect.Release();//释放数据库连接对象的内存空间

   CoUninitialize();//释放ado资源

   return result;

}

//获得病例列表
int SCaseData::GetSCaseList()
{
    CoInitialize(NULL);

   _ConnectionPtr pconnect(__uuidof(Connection));

   _RecordsetPtr record(__uuidof(Recordset));

   _CommandPtr comd(__uuidof(Command));

   pconnect->ConnectionString = _bstr_t(this->connString);//数据库连接字符串

   pconnect->Open("","","",NULL);

   comd->put_ActiveConnection(_variant_t((IDispatch *)pconnect));

   //标准SQL语句
   CString cmda = "";

   cmda = "select * from sleepdata";//查询所有的数据
  
   comd->CommandText = _bstr_t(cmda);//得到SQL语句

   record=comd->Execute(NULL,NULL,adCmdText);//执行SQL语句

   int result = 0;//结果默认0,既没有查出数据

   sCaseList.RemoveAll();//查询之前清空列表项

   if(!record->end)
   { 
     
	   while(!record->end)
	   {

          SCase scase;//定义病例变量

		 // scase = new SCase();//实例病例变量

		  int sid = record->GetCollect("sid").intVal;
		  
		  scase.SetSid(sid);//获得病例编号

		  CString sname = (char*)(_bstr_t)record->GetCollect("sname");

		  scase.SetSName(sname);//获得病例名称

		 // CTime birthtime(record->GetCollect("sbirthday"));
		  COleDateTime btemp1(record->GetCollect("sbirthday"));

		  CTime birthtime(btemp1.GetYear(),btemp1.GetMonth(),btemp1.GetDay(),btemp1.GetHour(),btemp1.GetMinute(),btemp1.GetSecond());
         // CTime birthtime = vrecord->GetCollect("sbirthday").date;

		  scase.SetSbirthday(birthtime);//获得病例生日

		  int ssex = record->GetCollect("ssex").intVal;

		  scase.SetSsex(ssex);//获得性别

		  int shigh = record->GetCollect("shigh").intVal;

		  scase.SetShigh(shigh);//获得高度

		  int sweight = record->GetCollect("sweight").intVal;

		  scase.SetSweight(sweight);//获得重量

		  //CTime starttime(record->GetCollect("startdate"));//获得开始时间
		  COleDateTime btemp2(record->GetCollect("startdate"));

		  CTime starttime(btemp2.GetYear(),btemp2.GetMonth(),btemp2.GetDay(),btemp2.GetHour(),btemp2.GetMinute(),btemp2.GetSecond());

		  scase.SetSstartdate(starttime);

		  CString scomment = (char*)(_bstr_t)record->GetCollect("scomment");

		  scase.SetScomment(scomment);//获得病例备注

		  CString sdiagnosis = (char*)(_bstr_t)record->GetCollect("sdiagnosis");

		  scase.SetSdiagnosis(sdiagnosis);//获得诊断医生名称

		  CString srecord = (char*)(_bstr_t)record->GetCollect("srecord");

		  scase.SetSrecord(srecord);//获得记录医生名称

		  sCaseList.AddTail(scase);//添加到病例链表中

		  record->MoveNext();//移动到下一条

	   }
	    

	   result = this->sCaseList.GetCount();
	   //m_id = (char *)(_bstr_t)record->GetCollect("id");//得到编号

	   //m_name = (char *)(_bstr_t)record->GetCollect("name");//得到学生姓名

	   //UpdateData(false);
   }
 
   record->Close();//关闭数据集

   pconnect->Close();//关闭数据库连接

   comd.Release();//释放数据库操作对象的内存空间

   record.Release();//释放数据记录集的内存空间

   pconnect.Release();//释放数据库连接对象的内存空间

   CoUninitialize();//释放ado资源

   return result;
}

//获得病例数据
CString SCaseData::GetFilePath()
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

	temp = "SAS";

	pathS += "SDatas\\" + temp + ".mdb";

	return pathS;//获得实际路径

}

