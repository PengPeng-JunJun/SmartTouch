// SplashWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "SplashWnd.h"
#include "afxdialogex.h"


// CSplashWnd 对话框

IMPLEMENT_DYNAMIC(CSplashWnd, CDialogEx)

CSplashWnd::CSplashWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSplashWnd::IDD, pParent)
{

}

CSplashWnd::~CSplashWnd()
{
}

void CSplashWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSplashWnd, CDialogEx)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSplashWnd 消息处理程序


BOOL CSplashWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
#ifdef _DEBUG
	SetTimer(1, 1, nullptr);
#else
	SetTimer(1, 2000, nullptr);
#endif // _DEBUG	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	KillTimer(nIDEvent);
	ShowWindow(SW_HIDE);

	CDialogEx::OnTimer(nIDEvent);
}
