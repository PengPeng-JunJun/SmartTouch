// AngleTestListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "AngleTestListDlg.h"
#include "afxdialogex.h"


// CAngleTestListDlg 对话框

IMPLEMENT_DYNAMIC(CAngleTestListDlg, CTpLayerWnd)

CAngleTestListDlg::CAngleTestListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CAngleTestListDlg::IDD, pParent)
{

}

CAngleTestListDlg::CAngleTestListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CAngleTestListDlg::~CAngleTestListDlg()
{
}

void CAngleTestListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAngleTestListDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CAngleTestListDlg 消息处理程序


BOOL CAngleTestListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAngleTestListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
