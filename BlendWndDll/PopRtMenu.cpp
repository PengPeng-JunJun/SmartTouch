// PopRtMenu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PopRtMenu.h"
#include "afxdialogex.h"

// CPopRtMenu �Ի���

IMPLEMENT_DYNAMIC(CPopRtMenu, CDialogEx)

CPopRtMenu::CPopRtMenu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPopRtMenu::IDD, pParent)
	, m_pParent(nullptr)
	, m_bHover(FALSE)
	, m_bTrack(TRUE)
	, m_nTransParent(24)
	, m_nBorderWidth(1)
{

}

CPopRtMenu::CPopRtMenu(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CDialogEx(nIDTemplate, pParent)
	, m_pParent(nullptr)
	, m_bHover(FALSE)
	, m_bTrack(TRUE)
	, m_nTransParent(24)
	, m_nBorderWidth(1)
{

}


CPopRtMenu::~CPopRtMenu()
{
	m_MsgHook.StopMsgHook();
}

void CPopRtMenu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopRtMenu, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_KEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPopRtMenu ��Ϣ�������


BOOL CPopRtMenu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyle(WS_CAPTION, 0, 0);
	ModifyStyleEx(WS_EX_DLGMODALFRAME, 0, 0);

	const DWORD dwExStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, dwExStyle ^ WS_EX_LAYERED);

	SetBackgroundColor(m_rgbBk);
	SetLayeredWindowAttributes(m_rgbBk, 255 - m_nTransParent, LWA_ALPHA);

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPopRtMenu::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_MsgHook.StopMsgHook();

	CDialogEx::OnOK();
}


void CPopRtMenu::OnHotKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return;
}


void CPopRtMenu::DrawElement(CDC * pDC, CRect rcDraw)
{
	const size_t nItems = m_vbEnable.size();

	const int nSpace = 4;
	const int nItemHeight = (int)((double)(rcDraw.Height() - (nSpace << 1)) / nItems + 0.5);

	CFont ft;
	ft.CreatePointFont(100, _T("Tahoma"));
	pDC->SelectObject(ft);

	pDC->FillSolidRect(rcDraw, m_rgbBk);

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SetBkMode(TRANSPARENT);
	//////////////////////////////////////////////////////////////////////////

	if (nItems)
	{
		m_vrcItem[0] = rcDraw;
		m_vrcItem[0].DeflateRect(nSpace, nSpace, nSpace, nSpace);
		m_vrcItem[0].bottom = m_vrcItem[0].top + nItemHeight;

		for (size_t i = 0; i < nItems; i++)
		{
			if (i)
			{
				m_vrcItem[i] = m_vrcItem[i - 1];
				m_vrcItem[i].OffsetRect(0, nItemHeight);
			}

			if (m_vbEnable[i])
			{
				if (i == m_nCurSel)
				{
					pDC->FillSolidRect(m_vrcItem[i], m_rgbHover);
					pDC->SetTextColor(m_rgbBk);
				}
				else
				{
					pDC->SetTextColor(m_rgbText);
				}
			}
			else
			{
				pDC->SetTextColor(m_rgbDisable);
			}

			CRect rcTemp = m_vrcItem[i];
			rcTemp.left += (nSpace << 1);
			pDC->DrawText(m_vstrItem[i], rcTemp, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	CPen penBorder1(PS_SOLID, 1,
		RGB(GetRValue(m_rgbBorder) >> 1, GetGValue(m_rgbBorder) >> 1, GetBValue(m_rgbBorder) >> 1));
	pDC->SelectObject(penBorder1);

	pDC->Rectangle(rcDraw);

	CPen penBorder2(PS_SOLID, m_nBorderWidth, m_rgbBorder);
	pDC->SelectObject(penBorder2);

	CRect rcTmp = rcDraw;
	rcTmp.DeflateRect(nSpace, nSpace, nSpace, nSpace);
	pDC->Rectangle(rcTmp);
}


void CPopRtMenu::_SendRtMenuMsg(BOOL bEnable, int nMsg, BOOL bMenuKey)
{
	if (bEnable)
	{
		m_pParent->SendMessage(gMsgPopRtMenu, nMsg, bMenuKey);

		m_nCurSel = RT_MENU_UNSELECT;

		m_ptCursor.x = -1;
		m_ptCursor.y = -1;

		Invalidate(FALSE);

		OnOK();
	}
}


BOOL CPopRtMenu::_LoadImageFromResource(ATL::CImage *pImage, UINT nResID, LPCTSTR lpTyp)
{
	if (nullptr == pImage)
	{
		return FALSE;
	}

	pImage->Destroy();

	const HINSTANCE hInst = AfxGetResourceHandle();

	// ������Դ
	const HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nResID), lpTyp);

	if (nullptr == hRsrc)
	{
		return FALSE;
	}

	// ������Դ
	HGLOBAL hImgData = ::LoadResource(hInst, hRsrc);

	if (nullptr == hImgData)
	{
		::FreeResource(hImgData);

		return FALSE;
	}

	// �����ڴ��е�ָ����Դ
	LPVOID lpVoid = ::LockResource(hImgData);

	LPSTREAM pStream = nullptr;

	const DWORD dwSize = ::SizeofResource(hInst, hRsrc);

	HGLOBAL hNew = ::GlobalAlloc(GHND, dwSize);

	LPBYTE lpByte = (LPBYTE)::GlobalLock(hNew);

	::memcpy(lpByte, lpVoid, dwSize);

	// ����ڴ��е�ָ����Դ
	::GlobalUnlock(hNew);

	// ��ָ���ڴ洴��������
	const HRESULT hResult = ::CreateStreamOnHGlobal(hNew, TRUE, &pStream);

	if (S_OK != hResult)
	{
		GlobalFree(hNew);
	}
	else
	{
		// ����ͼƬ
		pImage->Load(pStream);
		GlobalFree(hNew);
	}

	// �ͷ���Դ
	::FreeResource(hImgData);

	return TRUE;
}


BOOL CPopRtMenu::_DrawIcon(ATL::CImage * pImage, CDC * pDC, CRect rcDraw, BOOL bEnable)
{
	ASSERT(nullptr != pImage);

	if (!pImage->IsNull())
	{
		const int nWidth = pImage->GetWidth();
		const int nHeight = pImage->GetHeight();

		if (!bEnable)
		{
			if (32 == pImage->GetBPP()) // ȷ�ϸ�ͼ�����Alphaͨ��
			{
				const BYTE R = GetRValue(m_rgbDisable);
				const BYTE G = GetGValue(m_rgbDisable);
				const BYTE B = GetBValue(m_rgbDisable);

				for (int nW = 0; nW < nWidth; nW++)
				{
					for (int nH = 0; nH < nHeight; nH++)
					{
						BYTE *pData = (BYTE *)pImage->GetPixelAddress(nW, nH);

						pData[0] = B;
						pData[1] = G;
						pData[2] = R;
					}
				}
			}
		}

		const BOOL bResult = pImage->Draw(pDC->GetSafeHdc(), rcDraw, CRect(0, 0, nWidth, nHeight));

		return bResult;
	}

	return FALSE;
}


void CPopRtMenu::_SelectFont(const CString & strFont, LOGFONT &LgFt, CFont * pFt)
{
	if (FALSE == strFont.IsEmpty())
	{
		const int nFind = strFont.Find(',');

		if (nFind > 0)
		{
			CString strTmp = strFont;
			const CString strName = strTmp.Left(nFind);
			swprintf_s(LgFt.lfFaceName, strName);

			strTmp.Delete(0, nFind + 1);
			const double dpt = _ttof(strTmp);

			if (dpt > 0)
			{
				LgFt.lfHeight = (LONG)(dpt * 7.5 + 0.5);
				pFt->CreatePointFontIndirect(&LgFt);

				return;
			}
		}
	}

	LgFt.lfHeight = (LONG)(LgFt.lfHeight * 7.5 + 0.5);
	pFt->CreatePointFontIndirect(&LgFt);
}


void CPopRtMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rcWnd;
	GetWindowRect(rcWnd);

	CPoint pt;
	GetCursorPos(&pt);

	if (!rcWnd.PtInRect(pt))
	{
		OnOK();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CPopRtMenu::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ptCursor = point;

	const size_t nItems = m_vbEnable.size();

	for (size_t i = 0; i < nItems; i++)
	{
		if (m_vbEnable[i] && m_vrcItem[i].PtInRect(point))
		{
			_SendRtMenuMsg(m_vbEnable[i], i, FALSE);

			break;
		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CPopRtMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_ptCursor == point)
	{
		return;
	}

	m_ptCursor = point;

	CRect rcClient;
	GetClientRect(rcClient);

	int nSelect = m_nCurSel;

	const size_t nItems = m_vbEnable.size();

	for (size_t i = 0; i < nItems; i++)
	{
		if (m_vrcItem[i].PtInRect(m_ptCursor) && m_bHover)
		{
			m_nCurSel = i;
			break;
		}
	}

	if (m_bTrack)
	{
		TRACKMOUSEEVENT TrackEvent;

		TrackEvent.cbSize		= sizeof(TrackEvent);
		TrackEvent.dwFlags		= TME_HOVER | TME_LEAVE;
		TrackEvent.hwndTrack	= GetSafeHwnd();
		TrackEvent.dwHoverTime	= 10;

		m_bTrack = !_TrackMouseEvent(&TrackEvent);
	}

	if (nSelect != m_nCurSel)
	{
		Invalidate(FALSE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CPopRtMenu::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bHover = TRUE;
	Invalidate(FALSE);

	CDialogEx::OnMouseHover(nFlags, point);
}


void CPopRtMenu::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bTrack = TRUE;
	m_bHover = FALSE;
	m_nCurSel = RT_MENU_UNSELECT;

	Invalidate(FALSE);

	CDialogEx::OnMouseLeave();
}


void CPopRtMenu::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnHotKeyDown(nChar, nRepCnt, nFlags);

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CPopRtMenu::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������
	m_bTrack = TRUE;
	m_nCurSel = RT_MENU_UNSELECT;

	if (bShow)
	{
		m_MsgHook.StartMsgHook(this);
	}
	else
	{
		m_MsgHook.StopMsgHook();
	}
}


void CPopRtMenu::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rcClient;
	GetClientRect(rcClient);

	CBitmap bmp;
	CDC dcMem;

	dcMem.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());

	dcMem.SelectObject(&bmp);

	DrawElement(&dcMem, rcClient);

	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(),
		&dcMem,
		0, 0,
		SRCCOPY);

	bmp.DeleteObject();
	dcMem.DeleteDC();
}
