// MsgInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "MsgInfoDlg.h"
#include "afxdialogex.h"


// CMsgInfoDlg 对话框

IMPLEMENT_DYNAMIC(CMsgInfoDlg, CTpLayerWnd)

CMsgInfoDlg::CMsgInfoDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CMsgInfoDlg::IDD, pParent)
{

}


CMsgInfoDlg::CMsgInfoDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{
}


CMsgInfoDlg::~CMsgInfoDlg()
{
}

void CMsgInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_BT_ErrorInfo, m_BL_btErrorInfo);
	DDX_Control(pDX, IDC_BL_BT_ErrorReason_0, m_BL_btErrorReason[0]);
	DDX_Control(pDX, IDC_BL_BT_ErrorReason_1, m_BL_btErrorReason[1]);
	DDX_Control(pDX, IDC_BL_BT_ErrorReason_2, m_BL_btErrorReason[2]);
}


BEGIN_MESSAGE_MAP(CMsgInfoDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CMsgInfoDlg 消息处理程序
void CMsgInfoDlg::_DefaultFocus(void)
{
	//m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);

}