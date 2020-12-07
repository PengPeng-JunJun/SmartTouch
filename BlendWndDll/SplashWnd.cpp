// SplashWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplashWnd.h"
#include "afxdialogex.h"


// CSplashWnd �Ի���

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


// CSplashWnd ��Ϣ�������


BOOL CSplashWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
#ifdef _DEBUG
	SetTimer(1, 1, nullptr);
#else
	SetTimer(1, 2000, nullptr);
#endif // _DEBUG	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(nIDEvent);
	ShowWindow(SW_HIDE);

	CDialogEx::OnTimer(nIDEvent);
}
