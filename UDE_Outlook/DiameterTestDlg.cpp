// DiameterTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "DiameterTestDlg.h"
#include "afxdialogex.h"


// CDiameterTestDlg 对话框

IMPLEMENT_DYNAMIC(CDiameterTestDlg, CTpLayerWnd)

CDiameterTestDlg::CDiameterTestDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CDiameterTestDlg::IDD, pParent)
{

}

CDiameterTestDlg::CDiameterTestDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CDiameterTestDlg::~CDiameterTestDlg()
{
}

void CDiameterTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDiameterTestDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CDiameterTestDlg 消息处理程序


BOOL CDiameterTestDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDiameterTestDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
