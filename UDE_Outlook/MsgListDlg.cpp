// MsgListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "MsgListDlg.h"
#include "afxdialogex.h"


// CMsgListDlg 对话框

IMPLEMENT_DYNAMIC(CMsgListDlg, CTpLayerWnd)

CMsgListDlg::CMsgListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CMsgListDlg::IDD, pParent)
{

}

CMsgListDlg::CMsgListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)

{
	
}


CMsgListDlg::~CMsgListDlg()
{
}

void CMsgListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_MsgList, m_BL_MsgList);
}

void CMsgListDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);

}

BEGIN_MESSAGE_MAP(CMsgListDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CMsgListDlg 消息处理程序


BOOL CMsgListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetTitle(_T("消息列表"));
	m_BL_MsgList.ResetRows(m_BL_MsgList.GetRows(), TRUE);
	m_BL_MsgList.AppendColumn(_T("編號"),DT_CENTER,50,FALSE);
	m_BL_MsgList.AppendColumn(_T("寄存器名"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("數據地址"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("數據位數"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("數據名稱"),DT_CENTER,150,FALSE);
	m_BL_MsgList.AppendColumn(_T("實時值"),DT_CENTER,110,FALSE);
	m_BL_MsgList.AppendColumn(_T("顯示狀態"),DT_CENTER,90,FALSE);
	m_BL_MsgList.AppendColumn(_T("是否鎖定"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("繼電器類型"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("是否重置"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("重置值"),DT_CENTER,100,FALSE);

// 	m_BL_MsgList.AppendColumn(_T(""),DT_CENTER,100,FALSE);
	 
	 
	for (int nCounter = 0; nCounter < m_BL_MsgList.GetColumns(); nCounter++)//修改表头文字格式
	{
	 	m_BL_MsgList.SetHeaderFont(nCounter, _T("Tahoma"), 150);
	}
	 
	m_BL_MsgList.SetReadOnly(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
BEGIN_EVENTSINK_MAP(CMsgListDlg, CTpLayerWnd)
	ON_EVENT(CMsgListDlg, IDC_BL_MsgList, 1, CMsgListDlg::RowsChangedBlMsglist, VTS_I4 VTS_I4 VTS_BOOL)
END_EVENTSINK_MAP()


void CMsgListDlg::RowsChangedBlMsglist(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: 在此处添加消息处理程序代码
	for (int i = 0; i < nNewRows; i++)
	{
		m_BL_MsgList.SetItemText(i, 9, _T("0"));
	}
	
}
