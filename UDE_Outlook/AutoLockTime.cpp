// AutoLockTime.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "AutoLockTime.h"
#include "afxdialogex.h"


// CAutoLockTime 对话框

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


// CAutoLockTime 消息处理程序


void CAutoLockTime::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
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

	// 异常: OCX 属性页应返回 FALSE
}
