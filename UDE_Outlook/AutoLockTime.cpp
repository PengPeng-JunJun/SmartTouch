// AutoLockTime.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "AutoLockTime.h"
#include "afxdialogex.h"


// CAutoLockTime �Ի���

IMPLEMENT_DYNAMIC(CAutoLockTime, CTpLayerWnd)

CAutoLockTime::CAutoLockTime(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CAutoLockTime::IDD, pParent)
	, m_nAutoLockTime(30000)
{

}

CAutoLockTime::CAutoLockTime(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(CAutoLockTime::IDD, pParent)
	, m_nAutoLockTime(30000)
{

}

CAutoLockTime::~CAutoLockTime()
{
}

void CAutoLockTime::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_edAutoLockTime, m_BL_edAutoLockTime);
}


BEGIN_MESSAGE_MAP(CAutoLockTime, CTpLayerWnd)
END_MESSAGE_MAP()


// CAutoLockTime ��Ϣ�������


void CAutoLockTime::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_nAutoLockTime = m_BL_edAutoLockTime.GetIntValue() * 1000;
	CTpLayerWnd::OnOK();
}


BOOL CAutoLockTime::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	CString strTemp;

	strTemp.Format(_T("%d"), (int)(m_nAutoLockTime / 1000.0));

	m_BL_edAutoLockTime.SetValueText(strTemp);
	return TRUE;  // return TRUE unless you set the focus to a control

	// �쳣: OCX ����ҳӦ���� FALSE
}
