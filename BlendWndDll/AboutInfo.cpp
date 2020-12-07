// AboutInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AboutInfo.h"
#include "afxdialogex.h"


// CAboutInfo 对话框

IMPLEMENT_DYNAMIC(CAboutInfo, CTpLayerWnd)

CAboutInfo::CAboutInfo(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CAboutInfo::IDD, pParent)
{

}

CAboutInfo::CAboutInfo(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CAboutInfo::~CAboutInfo()
{
}

void CAboutInfo::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutInfo, CTpLayerWnd)
END_MESSAGE_MAP()

// CAboutInfo 消息处理程序


BOOL CAboutInfo::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BtBaseCancel.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
