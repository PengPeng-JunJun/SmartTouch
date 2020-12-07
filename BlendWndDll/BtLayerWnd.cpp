// BtLayerWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BtLayerWnd.h"
#include "afxdialogex.h"

int g_nGdiplusInit = 0;
ULONG_PTR g_GdiplusToken;
Gdiplus::GdiplusStartupInput g_GdiStIpt;

// CBtLayerWnd �Ի���

IMPLEMENT_DYNAMIC(CBtLayerWnd, CDialogEx)


CBtLayerWnd::CBtLayerWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBtLayerWnd::IDD, pParent)
	, m_pTopWnd(nullptr)
	, m_nTrans(230)
	, m_rgbBack(RGB_BT_LAYER_BACK)
{
	if (!g_nGdiplusInit)
	{
		GdiplusStartup(&g_GdiplusToken, &g_GdiStIpt, nullptr);
	}

	g_nGdiplusInit++;
}

CBtLayerWnd::CBtLayerWnd(UINT nIDTemplate, CWnd* pParent /*= nullptr*/)
	: CDialogEx(nIDTemplate, pParent)
	, m_pTopWnd(nullptr)
	, m_nTrans(230)
	, m_rgbBack(RGB_BT_LAYER_BACK)
{
	if (!g_nGdiplusInit)
	{
		Gdiplus::GdiplusStartup(&g_GdiplusToken, &g_GdiStIpt, nullptr);
	}

	g_nGdiplusInit++;
}


CBtLayerWnd::~CBtLayerWnd()
{
	g_nGdiplusInit--;

	if (!g_nGdiplusInit)
	{
		Gdiplus::GdiplusShutdown(g_GdiplusToken);
	}
}


void CBtLayerWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBtLayerWnd, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_REGISTERED_MESSAGE(gMsgTplayerWndClose, &CBtLayerWnd::OnGmsgtplayerwndclose)	
END_MESSAGE_MAP()


// CBtLayerWnd ��Ϣ�������



BOOL CBtLayerWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDOK)->ShowWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	GetDlgItem(IDCANCEL)->ShowWindow(FALSE);
	GetDlgItem(IDCANCEL)->EnableWindow(FALSE);

	ModifyStyle(WS_CAPTION, 0, 0);
	ModifyStyleEx(WS_EX_DLGMODALFRAME, 0, 0);

// 	m_Blend.BlendOp = AC_SRC_OVER;
// 	m_Blend.BlendFlags = 0;
// 	m_Blend.AlphaFormat = AC_SRC_ALPHA;
// 	m_Blend.SourceConstantAlpha = 255;

	const DWORD dwExStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, dwExStyle ^ WS_EX_LAYERED);

	SetBackgroundColor(m_rgbBack);
	SetLayeredWindowAttributes(RGB(0, 0, 0), m_nTrans, LWA_ALPHA);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CBtLayerWnd::__DrawBorder(Graphics * pGraph, Pen * pen, Brush * pBrush, RectF rect, REAL fOfst)
{
	// ��ͼ·��
	GraphicsPath path;

	// �����ͼ·��
	path.AddLine(fOfst - 1.0f, 0.0f, rect.Width - fOfst, 0.0f);
	path.AddLine(rect.Width - fOfst, 0.0f, rect.Width - 1.0f, fOfst - 1.0f);
	path.AddLine(rect.Width - 1.0f, fOfst - 1.0f, rect.Width - 1.0f, rect.Height - fOfst);
	path.AddLine(rect.Width - 1.0f, rect.Height - fOfst, rect.Width - fOfst, rect.Height - 1.0f);
	path.AddLine(rect.Width - fOfst, rect.Height - 1.0f, fOfst - 1.0f, rect.Height - 1.0f);
	path.AddLine(fOfst - 1.0f, rect.Height - 1.0f, 0.0f, rect.Height - fOfst);
	path.AddLine(0.0f, rect.Height - fOfst, 0.0f, fOfst - 1.0f);
	path.AddLine(0.0f, fOfst - 1.0f, fOfst - 1.0f, 0.0f);

	__DrawTarget(pGraph, pen, pBrush, &path);
}


void CBtLayerWnd::__DrawTarget(Graphics * pGraph, Pen * pen, Brush * pBrush, GraphicsPath * pPath)
{
	if (nullptr != pen)
	{
		pGraph->DrawPath(pen, pPath);
	}

	if (nullptr != pBrush)
	{
		pGraph->FillPath(pBrush, pPath);
	}
}


void CBtLayerWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

// 	using namespace Gdiplus;
// 
// 	CRect rcClient;
// 	GetClientRect(rcClient);
// 
// 	CDC dcMem;
// 	dcMem.CreateCompatibleDC(&dc);
// 
// 	CBitmap bmp;
// 	bmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
// 	dcMem.SelectObject(bmp);
// 
// 	Graphics graph(dcMem.GetSafeHdc());
// 	graph.SetCompositingQuality(CompositingQualityHighQuality);
// 	graph.SetSmoothingMode(SmoothingModeAntiAlias);
// 
// 	SolidBrush brush(Color(m_nTrans, GetRValue(m_rgbBack), GetGValue(m_rgbBack), GetBValue(m_rgbBack)));
// 
// 	__DrawBorder(&graph, nullptr, &brush, CRECT2RECTF(rcClient), 11);
// 
// 	RECT rcWnd;
// 	GetWindowRect(&rcWnd);
// 	POINT ptWnd = {rcWnd.left, rcWnd.top };
// 
// 	SIZE szWnd = {rcClient.Width(), rcClient.Height()};
// 	POINT ptSrc = {0, 0};
// 
// 	const DWORD dwExStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
// 	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, dwExStyle ^ WS_EX_LAYERED);
// 
// 	BOOL bRetVal = ::UpdateLayeredWindow(GetSafeHwnd(), dcMem.GetSafeHdc(), &ptWnd,
// 		&szWnd, dcMem.GetSafeHdc(), &ptSrc, 0, &m_Blend, LWA_ALPHA);
}


void CBtLayerWnd::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	const int nOfst = 12;

	CRgn rgnWnd;

	CPoint pts[] = {
		CPoint(nOfst, 0), CPoint(0, nOfst), CPoint(0, cy - nOfst - 1),
		CPoint(nOfst, cy - 1), CPoint(cx - nOfst - 1, cy - 1), CPoint(cx - 1, cy - nOfst - 1),
		CPoint(cx - 1, nOfst), CPoint(cx - nOfst, 0), CPoint(nOfst, 0)};

	rgnWnd.CreatePolygonRgn(pts, 9, ALTERNATE);

	SetWindowRgn(rgnWnd, TRUE);
}


void CBtLayerWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	if (bShow)
	{
		if ((nullptr != m_pTopWnd) && (nullptr != m_pTopWnd->GetSafeHwnd()))
		{
			CTpLayerWnd *pTopWnd = (CTpLayerWnd *)m_pTopWnd;

			if (FALSE == pTopWnd->m_bClickShow)
			{
				pTopWnd->ShowWindow(SW_SHOW);
			}

			pTopWnd->m_bClickShow = FALSE;
		}
	}
}


afx_msg LRESULT CBtLayerWnd::OnGmsgtplayerwndclose(WPARAM wParam, LPARAM lParam)
{
	OnCancel();

	return 0;
}
