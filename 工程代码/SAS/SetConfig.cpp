// SetConfig.cpp : implementation file
//

#include "stdafx.h"
#include "SAS.h"
#include "SetConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetConfig dialog


SetConfig::SetConfig(CWnd* pParent /*=NULL*/)
	: CDialog(SetConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetConfig)
	m_ModeV = -1;
	//}}AFX_DATA_INIT
}


void SetConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetConfig)
	DDX_Control(pDX, IDC_TBWORD, m_tbWord);
	DDX_Control(pDX, IDC_RLWORD, m_rlWord);
	DDX_Control(pDX, IDC_MODESHOW, m_Mode);
	DDX_CBIndex(pDX, IDC_MODESHOW, m_ModeV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetConfig, CDialog)
	//{{AFX_MSG_MAP(SetConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetConfig message handlers
//��ӳ�ʼ������
BOOL SetConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
    
	m_ModeV = config.wSpeed;//WSPEED002,WSPEED02,WSPEED1,WSPEED2,WSPEED1M

	m_rlWord.SetRange(12,16);//���ÿ������õķ�Χ

	m_tbWord.SetRange(12,16);//

	m_rlWord.SetPos(config.rlWordSize);//��ʼֵ�������

	m_tbWord.SetPos(config.tbWordSize);//����ֵ�������

	UpdateData(0);
	
	return TRUE; 
}

void SetConfig::OnOK() 
{

	UpdateData(1);//��������

	config.rlWordSize = m_rlWord.GetPos();//��õ�ǰֵ

	config.tbWordSize = m_tbWord.GetPos();//��õ�ǰֵ

	config.wSpeed = (WSpeed)m_ModeV;//�����������

	if(config.SaveConfig())//�����ļ�
	{
		AfxMessageBox("������Ϣ����ɹ�!");
	}
	else
	{
		AfxMessageBox("�����ļ�ԭ��������Ϣ����ʧ��!");
	}

	CDialog::OnOK();
}
