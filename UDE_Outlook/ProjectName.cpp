// ProjectName.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ProjectName.h"
#include "afxdialogex.h"


// CProjectName 对话框

IMPLEMENT_DYNAMIC(CProjectName, CTpLayerWnd)

	CProjectName::CProjectName(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CProjectName::IDD, pParent)
	, m_strProjectName(_T(""))
{

}

CProjectName::CProjectName(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(CProjectName::IDD, pParent)
	, m_strProjectName(_T(""))
{
}

CProjectName::~CProjectName()
{
}

void CProjectName::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ProjectName, m_BL_ProjectName);
}


BEGIN_MESSAGE_MAP(CProjectName, CTpLayerWnd)
END_MESSAGE_MAP()


// CProjectName 消息处理程序


void CProjectName::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_strProjectName = m_BL_ProjectName.GetValueText();
	CTpLayerWnd::OnOK();
}


BOOL CProjectName::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	m_BL_ProjectName.SetValueText(m_strProjectName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
