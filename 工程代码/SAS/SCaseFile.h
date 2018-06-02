// SCaseFile.h: interface for the SCaseFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCASEFILE_H__C2D27F3F_535E_4FA6_B6D1_32E4F5D4D0E2__INCLUDED_)
#define AFX_SCASEFILE_H__C2D27F3F_535E_4FA6_B6D1_32E4F5D4D0E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//定义数据结构体
typedef struct DATA_BLOCK {
	                short	nFlow;	//气流数据
	                short   nSpO2;  //血氧数据
	                short   nPulse; //脉率数据
	                short   nPleth; //血氧容积波
             } DATA_BLOCK;


class SCaseFile  
{
public:
	SCaseFile();

	DATA_BLOCK *GetDatas();//获得数据指针

	int GetLength();

	bool InitDatas(int sid);//根据病例号初始化病例数据

	bool CopyDatas(int sid,CString originpath);//将病例文件复制到SCases文件夹中

	bool DeleteDatas(int sid);//将病例文从SCases文件夹中删除

	virtual ~SCaseFile();

public:

	DATA_BLOCK *datas;//病例数据指针

	int length;//数据

private:
	CString GetFilePath(int sid);

};


#endif // !defined(AFX_SCASEFILE_H__C2D27F3F_535E_4FA6_B6D1_32E4F5D4D0E2__INCLUDED_)
