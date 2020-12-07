// TpLayerWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "TpLayerWnd.h"
#include "afxdialogex.h"

#include "BtLayerWnd.h"

// CTpLayerWnd 对话框

IMPLEMENT_DYNAMIC(CTpLayerWnd, CAppBase)

CTpLayerWnd::CTpLayerWnd(CWnd* pParent /*=NULL*/)
	: CAppBase(CTpLayerWnd::IDD, pParent)
	, m_bModal(TRUE)
	, m_pBtLayer(pParent)
{

}


CTpLayerWnd::CTpLayerWnd(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CAppBase(nIDTemplate, pParent)
	, m_bModal(TRUE)
	, m_pBtLayer(pParent)
{

}


CTpLayerWnd::~CTpLayerWnd()
{
}

void CTpLayerWnd::DoDataExchange(CDataExchange* pDX)
{
	CAppBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTpLayerWnd, CAppBase)
	ON_WM_NCHITTEST()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CTpLayerWnd 消息处理程序


BOOL CTpLayerWnd::OnInitDialog()
{
	CAppBase::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BtBaseClose.SetShowTip(FALSE);
	m_BtBaseMin.ShowWindow(SW_HIDE);
	m_swBaseLock.ShowWindow(SW_HIDE);

//	m_TopBlur.m_bUseLayerWnd = TRUE;

	SetBackgroundColor(m_rgbKey);

	CRect rcClient;
	GetClientRect(rcClient);

	MoveWindow(rcClient);
	CenterWindow(m_pOwner);

	const DWORD dwExStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, dwExStyle ^ WS_EX_LAYERED);

	SetLayeredWindowAttributes(m_rgbKey, 0, LWA_COLORKEY);

	if (m_bModal)
	{
		_SendBlurMsg(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CTpLayerWnd::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	_CloseWnd();

	CAppBase::OnOK();
}


void CTpLayerWnd::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类

	_CloseWnd();

	CAppBase::OnCancel();
}


void CTpLayerWnd::DrawTitle(CDC * pDC, CRect rcDraw)
{
	CString strWnd;

	if (m_strTitle.IsEmpty())
	{
		GetWindowText(strWnd);
	}
	else
	{
		strWnd = m_strTitle;
	}

	CRect rcTitle = rcDraw;
	rcTitle.DeflateRect(0, 0, 80, 0);
	rcTitle.bottom = rcTitle.top + 30;

	pDC->FillSolidRect(rcTitle, m_rgbKey);

	CGdiplusText GdiText;
	GdiText.DrawText(pDC, CPoint(12, 8), strWnd, m_strTitleFont, m_fTitleFontSize, RGB2ARGB(255, m_rgbTitle));
}


INT_PTR CTpLayerWnd::CreateTopWnd(BOOL bModal, CWnd * pOwner)
{
	m_bModal = bModal;
	m_pOwner = pOwner;

	if (bModal)
	{
		return DoModal();
	}
	else
	{
		Create(m_lpszTemplateName, m_pBtLayer);
	}

	return IDCANCEL;
}


void CTpLayerWnd::MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint/* = TRUE*/)
{
	CAppBase::MoveWindow(x, y, nWidth, nHeight, bRepaint);

	CRect rcWnd;
	GetWindowRect(rcWnd);
	m_pBtLayer->MoveWindow(rcWnd, bRepaint);
}


void CTpLayerWnd::MoveWindow(LPCRECT lpRect, BOOL bRepaint /* = TRUE */)
{
	CAppBase::MoveWindow(lpRect, bRepaint);

	CRect rcWnd;
	GetWindowRect(rcWnd);
	m_pBtLayer->MoveWindow(rcWnd, bRepaint);
}


BOOL CTpLayerWnd::SetWindowPos(const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags)
{
	BOOL bSwp = CAppBase::SetWindowPos(pWndInsertAfter, x, y, cx, cy, nFlags);

	CRect rcWnd;
	GetWindowRect(rcWnd);
	m_pBtLayer->MoveWindow(rcWnd, FALSE);

	return bSwp;
}


void CTpLayerWnd::_PreShowWnd(void)
{
	return;
}


void CTpLayerWnd::_CloseWnd(void)
{
	_SendBlurMsg(FALSE);

	m_pBtLayer->SendMessage(gMsgTplayerWndClose);	
}


LRESULT CTpLayerWnd::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rcClient;
	GetClientRect(rcClient);
	ClientToScreen(rcClient);

	if (rcClient.PtInRect(point))
	{
		return HTCAPTION;
	}

	return CAppBase::OnNcHitTest(point);
}


void CTpLayerWnd::OnMove(int x, int y)
{
	CAppBase::OnMove(x, y);

	// TODO:  在此处添加消息处理程序代码
	CRect rcWnd;
	GetWindowRect(rcWnd);
	m_pBtLayer->MoveWindow(rcWnd, FALSE);
}


void CTpLayerWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CAppBase::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	if (bShow)
	{
		CRect rcWnd;
		GetWindowRect(rcWnd);
		m_pBtLayer->MoveWindow(rcWnd, FALSE);

		_PreShowWnd();
	}

	((CBtLayerWnd *)m_pBtLayer)->ShowWindow(bShow);
}
