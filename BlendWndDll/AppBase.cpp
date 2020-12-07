// AppBase.cpp : 实现文件
//

#include "stdafx.h"
#include "AppBase.h"
#include "afxdialogex.h"

#include "Blender.h"
#include "PsdMgr.h"

vector<BASE_BLUR_INFO> g_vBaseInfo;
CSemaphore g_seBaseInfo;

#ifdef _DEBUG
	BOOL g_bUiLocked = FALSE;
	int g_nPsdLevel = PSD_LEVEL_MGR;
#else
	BOOL g_bUiLocked = TRUE;
	int g_nPsdLevel = -1;
#endif // _DEBUG

BOOL g_bFileDirty = FALSE;

// CAppBase 对话框

IMPLEMENT_DYNAMIC(CAppBase, CDialogEx)

CAppBase::CAppBase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppBase::IDD, pParent)
	, m_bClickShow(FALSE)
	, m_pOwner(nullptr)
	, m_bUiLocked(FALSE)
	, m_bStatusLock(FALSE)
	, m_bRegistered(FALSE)
	, m_bChildWnd(FALSE)
	, m_nMenuStart(0)
	, m_fTitleFontSize(13)
	, m_strTitleFont(_T("微软雅黑"))
	, m_rgbTitle(RGB(0, 255, 230))
	, m_rgbKey(RGB_TRANS_TOP_KEY)
	, m_nBlurCount(0)
	, m_nRevBuffSize(2048)
	, m_bNetAnswered(FALSE)
	, m_pNetBuffer(nullptr)
	, m_pNetThread(nullptr)
	, m_bSaveOK(FALSE)
	, m_bSaveNG(FALSE)
{

}

CAppBase::CAppBase(UINT nIDTemplate, CWnd * pParent/* = NULL*/)
	: CDialogEx(nIDTemplate, pParent)
	, m_bClickShow(FALSE)
	, m_pOwner(nullptr)
	, m_bUiLocked(FALSE)
	, m_bStatusLock(FALSE)
	, m_bRegistered(FALSE)
	, m_bChildWnd(FALSE)
	, m_nMenuStart(0)
	, m_fTitleFontSize(13)
	, m_strTitleFont(_T("微软雅黑"))
	, m_rgbTitle(RGB(0, 255, 230))
	, m_rgbKey(RGB_TRANS_TOP_KEY)
	, m_nBlurCount(0)
	, m_nRevBuffSize(2048)
	, m_bNetAnswered(FALSE)
	, m_pNetBuffer(nullptr)
	, m_pNetThread(nullptr)
	, m_bSaveOK(FALSE)
	, m_bSaveNG(FALSE)
{

}

CAppBase::~CAppBase()
{
	if (nullptr != m_pNetBuffer)
	{
		delete []m_pNetBuffer;
		m_pNetBuffer = nullptr;
	}

	_RemoveBlurInfo(this);
}

void CAppBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAppBase, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_REGISTERED_MESSAGE(gMsgSemiTransBlur, &CAppBase::OnGmsgsemitransblur)
	ON_REGISTERED_MESSAGE(gMsgAppBaseLockUi, &CAppBase::OnGmsgappbaselockui)
	ON_REGISTERED_MESSAGE(gMsgAppBaseUnlockUi, &CAppBase::OnGmsgappbaseunlockui)
	ON_REGISTERED_MESSAGE(gMsgAppBaseSetFocus, &CAppBase::OnGmsgappbasesetfocus)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CAppBase, CDialogEx)
	ON_EVENT(CAppBase, IDC_BT_BASE_CLOSE, 1, CAppBase::LBtClickedBtClose, VTS_I4)
	ON_EVENT(CAppBase, IDC_BT_BASE_SIZE, 1, CAppBase::LBtClickedBtSize, VTS_I4)
	ON_EVENT(CAppBase, IDC_BT_BASE_MIN, 1, CAppBase::LBtClickedBtMin, VTS_I4)
	ON_EVENT(CAppBase, IDC_SW_BASE_LOCK, 1, CAppBase::StatusChangedSwAppLock, VTS_BOOL)
	ON_EVENT(CAppBase, IDC_BT_BASE_OK, 1, CAppBase::LBtClickedBtOk, VTS_I4)
	ON_EVENT(CAppBase, IDC_BT_BASE_CANCEL, 1, CAppBase::LBtClickedBtCancel, VTS_I4)
END_EVENTSINK_MAP()

BOOL CAppBase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ModifyStyle(WS_CAPTION, 0, 0);
	ModifyStyleEx(WS_EX_DLGMODALFRAME, 0, 0);

	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	CString strWndText = m_strTitle;

	if (m_strTitle.IsEmpty())
	{
		GetWindowText(strWndText);
		m_strTitle = strWndText;
	}

	BASE_BLUR_INFO Bi;

	Bi.pWnd = this;
	Bi.strInfo = strWndText;
	g_vBaseInfo.push_back(Bi);

	//////////////////////////////////////////////////////////////////////////
	CRect rcBox;
	GetClientRect(rcBox);

	rcBox.left = rcBox.right - 62;
	rcBox.right -= 12;
	rcBox.top += 8;
	rcBox.bottom = rcBox.top + 24;

	m_BtBaseClose.Create(_T("关闭"), WS_CHILD | WS_VISIBLE, rcBox, this, IDC_BT_BASE_CLOSE);
	m_BtBaseClose.SetShowBorder(FALSE);
	m_BtBaseClose.SetBackColor(m_rgbKey);
	m_BtBaseClose.SetBlendColor(m_rgbKey);
	m_BtBaseClose.SetForeColor(RGB(0, 255, 230));
	m_BtBaseClose.SetTipBackColor(RGB(64, 64, 64));
	m_BtBaseClose.SetShowTip(TRUE);
	m_BtBaseClose.SetPngName(_T("Close_"));
	m_BtBaseClose.SetPngImage(TRUE);

	m_BtBaseMin.Create(_T("最小化"), WS_CHILD | WS_VISIBLE, rcBox, this, IDC_BT_BASE_MIN);
	m_BtBaseMin.SetShowBorder(FALSE);
	m_BtBaseMin.SetBackColor(m_rgbKey);
	m_BtBaseMin.SetBlendColor(m_rgbKey);
	m_BtBaseMin.SetForeColor(RGB(0, 255, 230));
	m_BtBaseMin.SetTipBackColor(RGB(64, 64, 64));
	m_BtBaseMin.SetShowTip(TRUE);
	m_BtBaseMin.SetPngName(_T("Min_"));
	m_BtBaseMin.SetPngImage(TRUE);

	m_swBaseLock.Create(_T("锁定"), WS_CHILD | WS_VISIBLE, rcBox, this, IDC_SW_BASE_LOCK);
	m_swBaseLock.SetBackColor(RGB(45, 50, 55));
	m_swBaseLock.SetForeColor(RGB(0, 255, 230));
	m_swBaseLock.SetStatus(g_bUiLocked);

	COleFont ftTmp = m_swBaseLock.GetFont();
	CY sz = ftTmp.GetSize();
	sz.int64 = (LONGLONG)(sz.int64 * 1.1);
	sz.Lo = (unsigned long)(sz.Lo * 1.1);
	ftTmp.SetSize(sz);
	m_swBaseLock.SetFont(ftTmp);

	GetDlgItem(IDOK)->GetWindowRect(rcBox);
	ScreenToClient(rcBox);

	m_BtBaseOk.Create(_T("确定"), WS_CHILD | WS_VISIBLE, rcBox, this, IDC_BT_BASE_OK);
	m_BtBaseOk.SetShowBorder(TRUE);
	m_BtBaseOk.SetBackColor(m_rgbKey);
	m_BtBaseOk.SetBlendColor(m_rgbKey);
	m_BtBaseOk.SetForeColor(RGB(0, 255, 230));
	m_BtBaseOk.SetBorderColor(RGB(0, 255, 230));
	m_BtBaseOk.SetHoverBkColor(RGB(70, 70, 70));
	m_BtBaseOk.SetTipBackColor(RGB(64, 64, 64));
	m_BtBaseOk.SetShowTip(FALSE);
	m_BtBaseOk.SetPngImage(FALSE);
	
	ftTmp = m_BtBaseOk.GetFont();
	ftTmp.SetName(_T("微软雅黑"));
	sz = ftTmp.GetSize();
	sz.int64 = (LONGLONG)(sz.int64 * 1.15);
	sz.Lo = (unsigned long)(sz.Lo * 1.15);
	ftTmp.SetSize(sz);
	m_BtBaseOk.SetFont(ftTmp);

	GetDlgItem(IDCANCEL)->GetWindowRect(rcBox);
	ScreenToClient(rcBox);

	m_BtBaseCancel.Create(_T("取消"), WS_CHILD | WS_VISIBLE, rcBox, this, IDC_BT_BASE_CANCEL);
	m_BtBaseCancel.SetShowBorder(TRUE);
	m_BtBaseCancel.SetBackColor(m_rgbKey);
	m_BtBaseCancel.SetBlendColor(m_rgbKey);
	m_BtBaseCancel.SetForeColor(RGB(0, 255, 230));
	m_BtBaseCancel.SetBorderColor(RGB(0, 255, 230));
	m_BtBaseCancel.SetHoverBkColor(RGB(70, 70, 70));
	m_BtBaseCancel.SetTipBackColor(RGB(64, 64, 64));
	m_BtBaseCancel.SetShowTip(FALSE);
	m_BtBaseCancel.SetPngImage(FALSE);
	m_BtBaseCancel.SetFont(ftTmp);

	m_BtBaseCancel.SetFocus();

	if (m_bChildWnd)
	{
		m_BtBaseClose.ShowWindow(SW_HIDE);
		m_BtBaseMin.ShowWindow(SW_HIDE);
		m_swBaseLock.ShowWindow(SW_HIDE);
		m_BtBaseOk.ShowWindow(SW_HIDE);
		m_BtBaseCancel.ShowWindow(SW_HIDE);
	}
	else
	{
		if (nullptr == m_TopBlur.GetSafeHwnd())
		{
			_AddBlurInfo(this, strWndText);

			m_TopBlur.m_strCaption = strWndText;
			m_TopBlur.m_strCaption.Insert(0, _T("TopBlur-"));
			m_TopBlur.Create(IDD_TOPBLUR, this);
		}

		PostMessage(gMsgAppBaseSetFocus);
	}	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAppBase::DrawTitle(CDC * pDC, CRect rcDraw)
{
	if (m_bChildWnd)
	{
		return;
	}

	Graphics graph(pDC->GetSafeHdc());
	graph.SetCompositingQuality(CompositingQualityHighQuality);
	graph.SetSmoothingMode(SmoothingModeAntiAlias);

	Pen pen(Color(255, 0, 255, 230), 1);
	SolidBrush brush(RGB2ARGB(255, RGB_BT_LAYER_BACK));

	CString strWnd;

	if (m_strTitle.IsEmpty())
	{
		GetWindowText(strWnd);
	}
	else
	{
		strWnd = m_strTitle;
	}

	// 绘图路径
	GraphicsPath path;

	CGdiplusText GdiText;
	RectF rcText = GdiText.MeasureString(pDC, strWnd, m_strTitleFont, m_fTitleFontSize);

	if (rcText.Width < 164)
	{
		rcText.Width = 164;
	}

	// 保存绘图路径

	const int nLeftSpace = 32;
	const int nRightSpace = 140;
	const int nHeight = 35;
	const int nTop = 3;

	m_nMenuStart = nLeftSpace + nHeight;

	path.AddLine((int)rcText.Width + nLeftSpace, nTop, (int)rcText.Width + nLeftSpace + nHeight, nHeight + nTop);
	path.AddLine((int)rcText.Width + nLeftSpace + nHeight, nHeight + nTop, rcDraw.right - nRightSpace - nHeight, nHeight + nTop);
	path.AddLine(rcDraw.right - nRightSpace - nHeight, nHeight + nTop, rcDraw.right - nRightSpace, nTop);

	DrawTarget(&graph, &pen, &brush, &path);

	GdiText.DrawText(pDC, CPoint(12, 9), strWnd, m_strTitleFont, m_fTitleFontSize, RGB2ARGB(255, m_rgbTitle));
}


void CAppBase::DrawElement(CDC * pDC, CRect rcDraw)
{
	return;
}


void CAppBase::DrawLine(CDC * pDC, CRect rcDraw)
{
	const size_t nLines = m_vUiLines.size();

	if (nLines)
	{
		Graphics graph(pDC->GetSafeHdc());
		graph.SetCompositingQuality(CompositingQualityHighQuality);
		graph.SetSmoothingMode(SmoothingModeAntiAlias);

		for (size_t i = 0; i < nLines; i++)
		{
			const Pen p(RGB2ARGB(255, m_vUiLines[i].rgbLine), (REAL)m_vUiLines[i].nWidth);

			graph.DrawLine(&p,
				Point(m_vUiLines[i].pt1.x, m_vUiLines[i].pt1.y),
				Point(m_vUiLines[i].pt2.x, m_vUiLines[i].pt2.y));
		}
	}
}


void CAppBase::LockCtrls(int nLock)
{
	return;
}


void CAppBase::PreWndDestroy(void)
{
	return;
}


BOOL CAppBase::ShowWindow(int nCmdShow)
{
	if (nCmdShow)
	{
		m_bClickShow = TRUE;
	}

	const BOOL bRetVal = CDialogEx::ShowWindow(nCmdShow);

	if (nCmdShow)
	{
		BringWindowToTop();
	}

	return bRetVal;
}


CWnd * CAppBase::GetOwner(void)
{
	return m_pOwner;
}


void CAppBase::SetOwner(CWnd * pOwner)
{
	m_pOwner = pOwner;
}


CString CAppBase::GetTitle(void)
{
	return m_strTitle;
}


void CAppBase::SetTitle(const CString & strTitle)
{
	m_strTitle = strTitle;

	if (m_bChildWnd)
	{
		return;
	}

	if (nullptr != GetSafeHwnd())
	{
		SetWindowText(strTitle);

		CRect rcClient;
		GetClientRect(rcClient);

		CClientDC dc(this);

		CGdiplusText GdiText;
		RectF rcText = GdiText.MeasureString(&dc, m_strTitle, m_strTitleFont, m_fTitleFontSize);

		rcText.Width = (REAL)(rcClient.Width() - 80);

		if (rcText.Width < 164)
		{
			rcText.Width = 164;
		}

		if (rcText.Height < 30)
		{
			rcText.Height = 30;
		}

		InvalidateRect(CRect(0, 0, (LONG)rcText.Width + 16, (LONG)rcText.Height + 16), FALSE);
	}
}


COLORREF CAppBase::GetTitleColor(void)
{
	return m_rgbTitle;
}


void CAppBase::SetTitleColor(COLORREF rgbTitle)
{
	m_rgbTitle = rgbTitle;
}


void CAppBase::SetTitleFont(CString strFont, REAL fSize)
{
	m_strTitleFont = strFont;
	m_fTitleFontSize = fSize;
}


CString CAppBase::GetTitleFont(void)
{
	return m_strTitleFont;
}


REAL CAppBase::GetTitleFontSize(void)
{
	return m_fTitleFontSize;
}


void CAppBase::LockStatus(BOOL bLock)
{
#ifdef _DEBUG
	m_bStatusLock = FALSE;
#else
	m_bStatusLock = bLock;
#endif // _DEBUG

	if (nullptr != GetSafeHwnd())
	{
		PostMessage(gMsgAppBaseLockUi, APP_LOCK_AUTO);
	}
}


void CAppBase::AdjustMenuPos(CBL_Menu * pMenu)
{
	CString strWnd;
	GetWindowText(strWnd);

	CRect rcWnd;
	GetClientRect(rcWnd);

	CClientDC dc(this);
	CGdiplusText GdiText;
	const RectF rcText = GdiText.MeasureString(&dc, strWnd, GetTitleFont(), GetTitleFontSize());

	const int nStart = max(164, (int)rcText.Width) + 80;
	pMenu->MoveWindow(nStart, 4, rcWnd.Width() - nStart - 400, 30, TRUE);

	InvalidateRect(CRect(0, 0, nStart + 240, 48), TRUE);
}


void CAppBase::DrawTarget(Graphics * pGraph, Pen * pen, Brush * pBrush, GraphicsPath * pPath)
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


BOOL CAppBase::AddLine(const CString & strName, int nIndex, CPoint pt1, CPoint pt2, COLORREF rgbLine, int nWidth, int nStyle)
{
	if (strName.IsEmpty())
	{
		return FALSE;
	}

	TP_UI_LINE line;
	line.strName = strName;
	line.nNum = nIndex;
	line.nStytle = nStyle;
	line.pt1 = pt1;
	line.pt2 = pt2;
	line.nWidth = nWidth;
	line.rgbLine = rgbLine;

	const size_t nLines = m_vUiLines.size();

	for (int i = nLines - 1; i >= 0; i--)
	{
		if (m_vUiLines[i].strName == strName)
		{
			return FALSE;
		}

		if (m_vUiLines[i].nNum == nIndex)
		{
			return FALSE;
		}
	}

	m_vUiLines.push_back(line);

	return TRUE;
}


BOOL CAppBase::DeleteLine(const CString & strName)
{
	const size_t nLines = m_vUiLines.size();

	for (int i = nLines - 1; i >= 0; i--)
	{
		if (m_vUiLines[i].strName == strName)
		{
			m_vUiLines.erase(m_vUiLines.begin() + i);
			return TRUE;
		}
	}

	return FALSE;
}


BOOL CAppBase::DeleteLine(int nLine)
{
	const size_t nLines = m_vUiLines.size();

	for (int i = nLines - 1; i >= 0; i--)
	{
		if (m_vUiLines[i].nNum == nLine)
		{
			m_vUiLines.erase(m_vUiLines.begin() + i);

			return TRUE;
		}
	}

	return FALSE;
}


BOOL CAppBase::SendNetMsg(const CString & strIp, USHORT nPort, const CString & strMsg,
						 int nBufSize/* = 1024*/, CString * pstrBack/* = nullptr*/)
{
	USES_CONVERSION;

	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 0);
	WSAStartup(wVersionRequested, &wsaData);

	//////////////////////////////////////////////////////////////////////////
	m_SockClient = socket(AF_INET, SOCK_DGRAM, 0);
	//////////////////////////////////////////////////////////////////////////

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(W2A(strIp));
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(nPort);

	int nRes = sendto(m_SockClient, W2A(strMsg), strlen(W2A(strMsg)) + 1, 0, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	if (SOCKET_ERROR == nRes)
	{
#ifdef _DEBUG
		CString strInfo;
		FORMAT_ERR_INFO(&strInfo);
#endif // _DEBUG

		closesocket(m_SockClient);
		WSACleanup();

		return FALSE;
	}

	if (nullptr != pstrBack)
	{
		if (nullptr != m_pNetBuffer)
		{
			delete []m_pNetBuffer;
			m_pNetBuffer = nullptr;
		}

		m_nRevBuffSize = nBufSize;
		m_pNetBuffer = new char[nBufSize];
		memset(m_pNetBuffer, 0, nBufSize);

		m_bNetAnswered = FALSE;
		m_pNetThread = AfxBeginThread(_ReceiveNetMsgThread, this);

		int i = 0;

		while (!m_bNetAnswered)
		{
			if (i > 300)
			{
				TerminateThread(m_pNetThread->m_hThread, 0);

				closesocket(m_SockClient);
				WSACleanup();

				return FALSE;
			}

			Sleep(10);

			i++;
		}

		*pstrBack = m_pNetBuffer;
	}

	closesocket(m_SockClient);
	WSACleanup();

	return TRUE;
}


BOOL CAppBase::_LoadFileEx(void)
{
	return TRUE;
}


void CAppBase::_DefaultFocus(void)
{
	if ((FALSE == m_bChildWnd) && IsKindOf(RUNTIME_CLASS(CTpLayerWnd)))
	{
		m_BtBaseOk.SetFocus();
	}
}


int CAppBase::_Rand(int nMin, int nMax)
{
	srand((unsigned)time(nullptr) + rand());
	const int nRand = rand() % (nMax - nMin + 1) + nMin;

	return nRand;
}


void CAppBase::_DelayMs(int nTime)
{
	LARGE_INTEGER lTemp;

	LONGLONG QStart = 0;
	LONGLONG QEnd = 0;
	double dFreq = 0;
	double dTime = 0;

	QueryPerformanceFrequency(&lTemp);
	dFreq = (double)lTemp.QuadPart;

	QueryPerformanceCounter(&lTemp);
	QStart = lTemp.QuadPart;

	do
	{
		QueryPerformanceCounter(&lTemp);
		QEnd	= lTemp.QuadPart;
		dTime	= (double)(QEnd - QStart) / dFreq;
		dTime	*= 1000;
	} while (dTime < nTime);
}


BOOL CAppBase::_GetLockState(int nLock, int nLevel)
{
	BOOL bUiLocked = FALSE;

	if (nLock < 0)
	{
		bUiLocked = _IsUiLocked() || (_GetPsdLeve() < nLevel);
	}
	else
	{
		bUiLocked = (nLock > 0) || (_GetPsdLeve() < nLevel);
	}

	return bUiLocked;
}


BOOL CAppBase::_IsUiLocked(void)
{
#ifdef _DEBUG
	return FALSE;
#else
	return g_bUiLocked || m_bStatusLock;
#endif // _DEBUG	
}


void CAppBase::_LockAllUis(BOOL bLock)
{
	if (bLock)
	{
		g_nPsdLevel = -1;
	}

	g_bUiLocked = bLock;

	const size_t nSize = g_vBaseInfo.size();

	for (size_t i = 0; i < nSize; i++)
	{
		const BASE_BLUR_INFO *pInfo = &g_vBaseInfo[i];
		CWnd *pWnd = pInfo->pWnd;

		if ((nullptr != pWnd) && (nullptr != pWnd->GetSafeHwnd()))
		{
			pWnd->PostMessage(gMsgAppBaseLockUi, bLock, (LPARAM)this);
		}
	}
}


int CAppBase::_GetPsdLeve(void)
{
#ifdef _DEBUG
	return PSD_LEVEL_MGR;
#else
	return g_nPsdLevel;
#endif // _DEBUG	
}


void CAppBase::_SetPsdLeve(int nLevel)
{
	g_nPsdLevel = nLevel;
}


BOOL CAppBase::_IsPsdLevel(int nLevel)
{
	return (g_nPsdLevel >= nLevel);
}


void CAppBase::_SendBlurMsg(BOOL bShow)
{
	g_seBaseInfo.Lock();

	const size_t nSize = g_vBaseInfo.size();

	for (size_t i = 0; i < nSize; i++)
	{
		const BASE_BLUR_INFO *pInfo = &g_vBaseInfo[i];
		CWnd *pWnd = pInfo->pWnd;

		if (pWnd == this)
		{
			continue;
		}
		
		if ((nullptr != pWnd) && (nullptr != pWnd->GetSafeHwnd()))
		{
			pWnd->PostMessage(gMsgSemiTransBlur, bShow, (LPARAM)this);
		}
	}

	g_seBaseInfo.Unlock();
}


void CAppBase::_AddBlurInfo(CWnd * pDstWnd, const CString & strWnd)
{
	g_seBaseInfo.Lock();

	BOOL bFind = FALSE;

	const size_t nSize = g_vBaseInfo.size();

	for (size_t i = 0; i < nSize; i++)
	{
		const BASE_BLUR_INFO *pInfo = &g_vBaseInfo[i];

		if (pInfo->pWnd == this)
		{
			bFind = TRUE;
			break;
		}
	}

	if (!bFind)
	{
		BASE_BLUR_INFO Bi;

		Bi.pWnd = this;
		Bi.strInfo = strWnd;
		Bi.nShowCmd = SW_SHOWNORMAL;

		g_vBaseInfo.push_back(Bi);
	}

	g_seBaseInfo.Unlock();
}


void CAppBase::_RemoveBlurInfo(CWnd * pDstWnd)
{
	g_seBaseInfo.Lock();

	const size_t nSize = g_vBaseInfo.size();

	for (size_t i = 0; i < nSize; i++)
	{
		const BASE_BLUR_INFO *pInfo = &g_vBaseInfo[i];

		if (pInfo->pWnd == this)
		{
			g_vBaseInfo.erase(g_vBaseInfo.begin() + i);

			break;
		}
	}

	g_seBaseInfo.Unlock();
}


void CAppBase::_DeleteSpace(CString & strData)
{
	const int nLength = strData.GetLength();

	for (int i = nLength - 1; i >= 0; i--)
	{
		if (' ' == strData[i])
		{
			strData.Delete(i);
		}
	}
}


vector<CString> CAppBase::_GetSegInfo(const CString & strInfo, char nMark)
{
	CString strSrc = strInfo;

	vector<CString> vRetVal;
	int nPos = -1;

LABEL_RESTART:
	nPos = strSrc.Find(nMark);

	if (nPos >= 0)
	{
		const CString strTmp = strSrc.Left(nPos);
		vRetVal.push_back(strTmp);

		strSrc.Delete(0, nPos + 1);

		goto LABEL_RESTART;
	}
	else if (!strSrc.IsEmpty())
	{
		vRetVal.push_back(strSrc);
	}

	return vRetVal;
}


BOOL CAppBase::_SaveOkNgPath(void)
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 
	strPath.Replace(_T(".exe"), _T(".ini"));

	CString strItem = _T("ImgSave");

	WritePrivateProfileString(strItem, _T("Path_OK"), m_strPathOK, strPath);
	WritePrivateProfileString(strItem, _T("Path_NG"), m_strPathNG, strPath);

	WritePrivateProfileString(strItem, _T("Save_OK"), m_bSaveOK? _T("1"): _T("0"), strPath);
	WritePrivateProfileString(strItem, _T("Save_NG"), m_bSaveNG? _T("1"): _T("0"), strPath);

	return TRUE;
}


BOOL CAppBase::_LoadOkNgPath(void)
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 
	strPath.Replace(_T(".exe"), _T(".ini"));

	CString strItem = _T("ImgSave");

	GetPrivateProfileString(strItem, _T("Path_OK"), _T(""),
		m_strPathOK.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);
	m_strPathOK.ReleaseBuffer();

	GetPrivateProfileString(strItem, _T("Path_NG"), _T(""),
		m_strPathNG.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);
	m_strPathNG.ReleaseBuffer();

	m_bSaveOK = GetPrivateProfileInt(strItem, _T("Save_OK"), 0, strPath);
	m_bSaveNG = GetPrivateProfileInt(strItem, _T("Save_NG"), 0, strPath);

	return TRUE;
}


BOOL CAppBase::_SaveFile(CBL_Menu * pMenu, const CString & strType, const CString & strExt, BOOL bSaveAs)
{
	if (bSaveAs || m_strFilePath.IsEmpty())
	{
		CString strDefault = strExt;
		strDefault.Insert(0, _T("*."));

		CString strFilter;
		strFilter.Format(_T("%s Files(*.%s)|*.%s|All Files(*.*)|*.*||"), strType, strExt, strExt);

		CFileDialog dlgFile(FALSE, strDefault, _T("无标题"), OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, strFilter, this);

		dlgFile.m_pOFN->lpstrTitle = _T("文件另存为");

		if (IDOK == dlgFile.DoModal())
		{
			m_strFilePath = dlgFile.GetPathName();
		}
		else
		{
			return TRUE;
		}
	}

	CFile file;
	CFileException FileEx;

	if (!file.Open(m_strFilePath, CFile::modeWrite | CFile::modeCreate, &FileEx))
	{
		FileEx.ReportError();
		return FALSE;
	}

	CArchive ar(&file, CArchive::store);

	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();

	_SetTitleFromPath(pMenu);

	pMenu->AddRecentFile(m_strFilePath);
	pMenu->SaveRecentFile();

	_FileDirty(FALSE);

	CMsgBox MsgWnd(this);
	MsgWnd.ShowMsg(_T("保存成功!"), _T("保存"), MB_OK | MB_ICONINFORMATION);

	return TRUE;
}


BOOL CAppBase::_LoadFile(CBL_Menu * pMenu, const CString & strType, const CString & strExt, BOOL bRecent)
{
	if (_IsFileDirty())
	{
		CMsgBox MsgBox(this);

		if (IDYES == MsgBox.ShowMsg(_T("是否保存当前文档?"), _T("打开"), MB_YESNO | MB_ICONQUESTION))
		{
			if (!_SaveFile(pMenu, strType, strExt, FALSE))
			{
				return FALSE;
			}
		}
	}

	if (!bRecent)
	{
		CString strDefault = strExt;
		strDefault.Insert(0, _T("*."));

		CString strFilter;
		strFilter.Format(_T("%s Files(*.%s)|*.%s|All Files(*.*)|*.*||"), strType, strExt, strExt);

		CFileDialog dlgFile(TRUE, strDefault, nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY, strFilter, this);

		dlgFile.m_pOFN->lpstrTitle = _T("打开文件");

		if (IDOK == dlgFile.DoModal())
		{
			CString strPath = dlgFile.GetPathName();

			if (m_strFilePath == strPath)
			{
				return TRUE;
			}
			else
			{
				m_strFilePath = strPath;
			}
		}
		else
		{
			return TRUE;
		}
	}

	if (m_strLastFile == m_strFilePath)
	{
		return TRUE;
	}

	m_strLastFile = m_strFilePath;

	CFile file;
	CFileException FileEx;

	if (!file.Open(m_strFilePath, CFile::modeRead, &FileEx))
	{
		FileEx.ReportError();

		pMenu->RemoveRecentFile(m_strFilePath);
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);

	BeginWaitCursor();

	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();

	EndWaitCursor();

	_SetTitleFromPath(pMenu);

	pMenu->AddRecentFile(m_strFilePath);
	pMenu->SaveRecentFile();

	_FileDirty(FALSE);

#ifdef _DEBUG
	_LockAllUis(FALSE);
	m_swBaseLock.SetStatus(FALSE);
#else
	_LockAllUis(TRUE);
	m_swBaseLock.SetStatus(TRUE);
#endif // _DEBUG

	return TRUE;
}


BOOL CAppBase::_LoadFile(CBL_Menu * pMenu, const CString & strType, const CString & strExt, const CString & strFile)
{
	if (_IsFileDirty())
	{
		CMsgBox MsgBox(this);

		if (IDYES == MsgBox.ShowMsg(_T("是否保存当前文档?"), _T("打开"), MB_YESNO | MB_ICONQUESTION))
		{
			if (!_SaveFile(pMenu, strType, strExt, FALSE))
			{
				return FALSE;
			}
		}
	}

	CFile file;
	CFileException FileEx;

	CString strFullPath = strFile;
	strFullPath.Insert(0, _T("\\"));
	strFullPath.Append(_T(".") + strExt);

	m_strFilePath = pMenu->m_strDefaultPath + strFile;

	if (m_strLastFile == m_strFilePath)
	{
		return TRUE;
	}

	m_strLastFile = m_strFilePath;

	if (!file.Open(m_strFilePath, CFile::modeRead, &FileEx))
	{
		FileEx.ReportError();

		pMenu->RemoveRecentFile(m_strFilePath);
		return FALSE;
	}

	CArchive ar(&file, CArchive::load);

	BeginWaitCursor();

	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();

	EndWaitCursor();

	_SetTitleFromPath(pMenu);

	pMenu->AddRecentFile(pMenu->m_strDefaultPath + strFile);
	pMenu->SaveRecentFile();

	_FileDirty(FALSE);

#ifdef _DEBUG
	_LockAllUis(FALSE);
	m_swBaseLock.SetStatus(FALSE);
#else
	_LockAllUis(TRUE);
	m_swBaseLock.SetStatus(TRUE);
#endif // _DEBUG

	_LoadFileEx();

	return TRUE;
}


BOOL CAppBase::_IsFileDirty(void)
{
#ifdef _DEBUG
	return FALSE;
#endif // _DEBUG

	return g_bFileDirty;
}


void CAppBase::_FileDirty(BOOL bDirty)
{
	g_bFileDirty = bDirty;
}


void CAppBase::_SetTitleFromPath(CBL_Menu * pMenu)
{
	int nFind = m_strFilePath.ReverseFind('\\');

	CString strTitle = m_strFilePath;
	strTitle.Delete(0, nFind + 1);

	nFind = strTitle.ReverseFind('.');
	strTitle = strTitle.Left(nFind);

	strTitle.Append(_T(" - "));
	strTitle.Append(AfxGetAppName());
	SetWindowText(strTitle);

	AdjustMenuPos(pMenu);
}


void CAppBase::_SetNoTitle(CBL_Menu * pMenu)
{
	CString strTitle = _T("无标题 - ");
	strTitle.Append(AfxGetAppName());
	SetWindowText(strTitle);

	AdjustMenuPos(pMenu);
}


CString CAppBase::_GetCurPath(void)
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 
	
	const int nPos = strPath.ReverseFind('\\');

	return strPath.Left(nPos);
}


CString CAppBase::_GetSysFontPath(void)
{
	TCHAR sWinDir[MAX_PATH];

	GetWindowsDirectory(sWinDir,MAX_PATH);

	CString sFontDir(sWinDir);
	sFontDir += _T("\\Fonts");

	return sFontDir;
}


BOOL CAppBase::_InstallFont(CString strFile)
{
#ifdef _DEBUG
	return TRUE;
#else
	//安装字体
	const CString strSysPath = _GetSysFontPath() + _T("\\");
	const CString strSysFile = strSysPath + strFile;

    if (PathFileExists(strSysFile))
    {
        return TRUE;
    }

	CString strCurPath = _GetCurPath();
	strCurPath.AppendChar('\\');
	strCurPath.Append(strFile);

	if (!CopyFile(strCurPath, strSysFile, FALSE))
	{
		return FALSE;
	}

	//添加字体到系统字体表
	const int nFontNum = AddFontResource(strSysFile);

	if (nFontNum <= 0)
	{
		return FALSE;
	}

	CRegKey FontKey;

	const CString strKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");

	LONG nRes = FontKey.Open(HKEY_LOCAL_MACHINE, strKey);

	if (ERROR_SUCCESS != nRes)
	{
		nRes = FontKey.Create(HKEY_LOCAL_MACHINE, strKey);

		if (ERROR_SUCCESS != nRes)
		{
			return FALSE;
		}
	}

	CString strFont = strFile;

	const int nDot = strFont.ReverseFind('.');
	strFont = strFont.Left(nDot);
	strFont.Append(_T(" (TrueType)"));

	USES_CONVERSION;
	nRes = FontKey.SetStringValue(strFont, strFile);

	if (ERROR_SUCCESS != nRes)
	{
		return FALSE;
	}

	nRes = FontKey.Close();

	if (ERROR_SUCCESS != nRes)
	{
		return FALSE;
	}

	::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

#endif

	return TRUE;
}


BOOL CAppBase::_RemoveFont(CString strFont)
{
 #ifdef _DEBUG
 	return TRUE;
 #else
	//卸载字体
	const CString strSysPath = _GetSysFontPath() + _T("\\");
	const CString strSysFile = strSysPath + strFont;

	if (!PathFileExists(strSysFile))
	{
		return TRUE;
	}

	//删除注册表
	CRegKey FontKey;

	const CString strKey = _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Fonts");

	LONG nRes = FontKey.Open(HKEY_LOCAL_MACHINE, strKey);

	if (ERROR_SUCCESS != nRes)
	{
		return FALSE;
	}

	const int nDot = strFont.ReverseFind('.');
	strFont = strFont.Left(nDot);
	strFont.Append(_T(" (TrueType)"));

	nRes = FontKey.DeleteValue(strFont);

	if (ERROR_SUCCESS != nRes)
	{
		return FALSE;
	}

	nRes = FontKey.Close();
	
	if (ERROR_SUCCESS != nRes)
	{
		return FALSE;
	}

	//从系统字体表移除字体
	if (!RemoveFontResource(strSysFile))
	{
		return FALSE;
	}

	if (!DeleteFile(strSysFile))
	{
		return FALSE;
	}

	::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

#endif

	return TRUE;
}


BOOL CAppBase::_RegisterActivex(BOOL bRegister)
{
#ifdef _DEBUG
	return TRUE;
#else
	vector<CString> vstrCtrls = _GetSegInfo(g_strBL_Regs, ',');

	const size_t nCtrls = vstrCtrls.size();

	for (size_t i = 0; i < nCtrls; i++)
	{
		const CString &strDll = vstrCtrls[i];

		HINSTANCE hLib = LoadLibrary(strDll);

		if (hLib < (HINSTANCE)HINSTANCE_ERROR)
		{
			CString strInfo = _T("载入") + strDll;
			strInfo += _T(" 失败！\n请检测当前目录是否在在该文件。");

			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(strInfo, nullptr, MB_OK | MB_ICONERROR);

			return FALSE;
		}

		// 获取注册函数DllRegisterServer地址
		FARPROC lpDllEntryPoint;
		lpDllEntryPoint = GetProcAddress(hLib, bRegister? "DllRegisterServer": "DllUnregisterServer");

		// 调用注册函数DllRegisterServer
		if(nullptr != lpDllEntryPoint)
		{ 
			if (FAILED((*lpDllEntryPoint)()))
			{
				CString strInfo = _T("调用") + strDll;

				if (bRegister)
				{
					strInfo += _T(" DllRegisterServer 失败！\n请确认是否为管理员权限。");
				}
				else
				{
					strInfo += _T(" DllUnregisterServer 失败！\n请确认是否为管理员权限。");
				}

				CMsgBox MsgBox(this);
				MsgBox.ShowMsg(strInfo, nullptr, MB_OK | MB_ICONERROR);
				FreeLibrary(hLib);

				return FALSE;
			};
		}
		else
		{
			CString strInfo = _T("调用") + strDll;

			if (bRegister)
			{
				strInfo += _T(" DllRegisterServer 失败！\n请确认是否为管理员权限。");
			}
			else
			{
				strInfo += _T(" DllUnregisterServer 失败！\n请确认是否为管理员权限。");
			}

			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(strInfo, nullptr, MB_OK | MB_ICONERROR);

			FreeLibrary(hLib);

			return FALSE;
		}
	}
#endif // _DEBUG

	return TRUE;
}


UINT CAppBase::_ReceiveNetMsgThread(LPVOID pParam)
{
	CAppBase *pBase = (CAppBase *)pParam;
	UINT nRetVul = pBase->_ReceiveNetMsgThreadKernal();

	return nRetVul;
}


UINT CAppBase::_ReceiveNetMsgThreadKernal(void)
{
	SOCKADDR_IN sockSvr;  
	int nLength = sizeof(SOCKADDR);

	int nRes = recvfrom(m_SockClient, m_pNetBuffer, m_nRevBuffSize, 0, (SOCKADDR*)&sockSvr, &nLength);

	if (SOCKET_ERROR == nRes)
	{
#ifdef _DEBUG
		CString strInfo;
		FORMAT_ERR_INFO(&strInfo);
#endif // _DEBUG
	}
	else
	{
		m_bNetAnswered = TRUE;
	}

	return (UINT)nRes;
}


afx_msg LRESULT CAppBase::OnGmsgsemitransblur(WPARAM wParam, LPARAM lParam)
{
	if (m_bChildWnd)
	{
		return 0;
	}	

	if (IsWindowVisible())
	{
		if (wParam)
		{
			m_nBlurCount++;
		}
		else if (m_nBlurCount)
		{
			m_nBlurCount--;
		}

		if ((1 == m_nBlurCount) && wParam)
		{
			CRect rcWnd;
			GetWindowRect(rcWnd);

			m_TopBlur.MoveWindow(rcWnd);
			m_TopBlur.ShowWindow(wParam);
			m_TopBlur.EnableWindow(FALSE);
		}
		else if ((0 == m_nBlurCount) && (!wParam))
		{
			m_TopBlur.ShowWindow(wParam);
		}
	}

	return 0;
}


afx_msg LRESULT CAppBase::OnGmsgappbaselockui(WPARAM wParam, LPARAM lParam)
{
	LockCtrls((int)wParam);

	return 0;
}


afx_msg LRESULT CAppBase::OnGmsgappbaseunlockui(WPARAM wParam, LPARAM lParam)
{
	CBlender<CPsdMgr> Psd(IDD_PSDMGR, this);
	Psd->m_bChangePsd = FALSE;
	Psd->SetTitle(_T("密码"));

	if (IDOK == Psd.CreateTopWnd(TRUE))
	{
		_LockAllUis(FALSE);
	}
	else
	{
		m_swBaseLock.SetStatus(TRUE);
	}

	return 0;
}


afx_msg LRESULT CAppBase::OnGmsgappbasesetfocus(WPARAM wParam, LPARAM lParam)
{
	_DefaultFocus();

	return 0;
}


void CAppBase::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	using namespace Gdiplus;

	CRect rcClient;
	GetClientRect(rcClient);

	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	dcMem.SelectObject(bmp);

	dcMem.FillSolidRect(rcClient, m_rgbKey);

	DrawElement(&dcMem, rcClient);
	DrawLine(&dcMem, rcClient);
	DrawTitle(&dcMem, rcClient);

	if (!m_bChildWnd)
	{
		Graphics graph(dcMem.GetSafeHdc());
		graph.SetCompositingQuality(CompositingQualityHighQuality);
		graph.SetSmoothingMode(SmoothingModeAntiAlias);

		//////////////////////////////////////////////////////////////////////////
		CString strIniPath;
		GetModuleFileName(nullptr, strIniPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
		strIniPath.ReleaseBuffer();

		CString strOld = AfxGetAppName();
		strIniPath.Replace(strOld + _T(".exe"), _T("TopLeft.png"));

		TCHAR lpImageFile[MAX_PATH];
		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		Image *pImgTopLeft = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImgTopLeft && (Status::Ok == pImgTopLeft->GetLastStatus()))
		{
			graph.DrawImage(pImgTopLeft, RectF((REAL)0, (REAL)0,
				(REAL)pImgTopLeft->GetWidth(), (REAL)pImgTopLeft->GetHeight()));
		}
		//////////////////////////////////////////////////////////////////////////

		strIniPath.Replace(_T("TopLeft"), _T("TopRight"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		Image *pImgTopRight = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImgTopRight && (Status::Ok == pImgTopRight->GetLastStatus()))
		{
			graph.DrawImage(pImgTopRight,
				RectF((REAL)(rcClient.right - pImgTopRight->GetWidth()), (REAL)0,
				(REAL)pImgTopRight->GetWidth(), (REAL)pImgTopRight->GetHeight()));
		}
		//////////////////////////////////////////////////////////////////////////

		strIniPath.Replace(_T("TopRight"), _T("BottomRight"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		Image *pImgBottomRight = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImgBottomRight && (Status::Ok == pImgBottomRight->GetLastStatus()))
		{
			graph.DrawImage(pImgBottomRight,
				RectF((REAL)(rcClient.right - pImgBottomRight->GetWidth()), (REAL)(rcClient.bottom - pImgBottomRight->GetHeight()),
				(REAL)pImgBottomRight->GetWidth(), (REAL)pImgBottomRight->GetHeight()));
		}
		//////////////////////////////////////////////////////////////////////////

		strIniPath.Replace(_T("BottomRight"), _T("BottomLeft"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		Image *pImgBottomLeft = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImgBottomLeft && (Status::Ok == pImgBottomLeft->GetLastStatus()))
		{
			graph.DrawImage(pImgBottomLeft,
				RectF((REAL)0, (REAL)(rcClient.bottom - pImgBottomLeft->GetHeight()),
				(REAL)pImgBottomLeft->GetWidth(), (REAL)pImgBottomLeft->GetHeight()));
		}

		//////////////////////////////////////////////////////////////////////////

		strIniPath.Replace(_T("BottomLeft"), _T("Top"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		Image *pImage = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImage && (Status::Ok == pImage->GetLastStatus()))
		{
			graph.DrawImage(pImage,
				RectF((REAL)pImgTopLeft->GetWidth(), (REAL)0,
				(REAL)(rcClient.right - pImgTopLeft->GetWidth() - pImgTopRight->GetWidth()), (REAL)pImage->GetHeight()));

			delete pImage;
			pImage = nullptr;
		}

		//////////////////////////////////////////////////////////////////////////
		strIniPath.Replace(_T("Top"), _T("Right"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		pImage = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImage && (Status::Ok == pImage->GetLastStatus()))
		{
			graph.DrawImage(pImage,
				RectF((REAL)(rcClient.right - pImage->GetWidth()), (REAL)pImgTopRight->GetHeight(),
				(REAL)pImage->GetWidth(), (REAL)(rcClient.bottom - pImgTopRight->GetHeight() - pImgBottomRight->GetHeight())));

			delete pImage;
			pImage = nullptr;
		}

		//////////////////////////////////////////////////////////////////////////
		strIniPath.Replace(_T("Right"), _T("Bottom"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		pImage = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImage && (Status::Ok == pImage->GetLastStatus()))
		{
			graph.DrawImage(pImage,
				RectF((REAL)pImgBottomLeft->GetWidth(), (REAL)(rcClient.bottom - pImage->GetHeight()),
				(REAL)(rcClient.right - pImgBottomLeft->GetWidth() - pImgBottomRight->GetWidth()), (REAL)pImage->GetHeight()));

			delete pImage;
			pImage = nullptr;
		}

		//////////////////////////////////////////////////////////////////////////
		strIniPath.Replace(_T("Bottom"), _T("Left"));

		memset(lpImageFile, 0, MAX_PATH);
		swprintf_s(lpImageFile, strIniPath);

		pImage = Image::FromFile(lpImageFile, TRUE);
		if (nullptr != pImage && (Status::Ok == pImage->GetLastStatus()))
		{
			graph.DrawImage(pImage,
				RectF((REAL)0, (REAL)pImgTopLeft->GetHeight(),
				(REAL)pImage->GetWidth(), (REAL)(rcClient.bottom - pImgTopLeft->GetHeight() - pImgBottomLeft->GetHeight())));

			delete pImage;
			pImage = nullptr;
		}

		delete pImgTopLeft;
		delete pImgTopRight;
		delete pImgBottomRight;
		delete pImgBottomLeft;
	}

	dc.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dcMem, 0, 0, SRCCOPY);
}


BOOL CAppBase::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CAppBase::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nullptr != m_BtBaseClose.GetSafeHwnd())
	{
		CRect rcClose;
		GetClientRect(rcClose);

		rcClose.left = rcClose.right - 62;
		rcClose.right -= 12;
		rcClose.top += 8;
		rcClose.bottom = rcClose.top + 24;

		m_BtBaseClose.MoveWindow(rcClose);

		rcClose.OffsetRect(-55, 0);
		m_BtBaseMin.MoveWindow(rcClose);

		rcClose.OffsetRect(-128, 0);
		rcClose.InflateRect(50, 0, 0, 0);
		m_swBaseLock.MoveWindow(rcClose);
	}
}


void CAppBase::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	if (WA_ACTIVE == nState)
	{
		g_seBaseInfo.Lock();

		BASE_BLUR_INFO Info;

		BOOL bFind = FALSE;

		const size_t nSize = g_vBaseInfo.size();

		for (size_t i = 0; i < nSize; i++)
		{
			if (g_vBaseInfo[i].pWnd == this)
			{
				bFind = TRUE;
				Info = g_vBaseInfo[i];

				g_vBaseInfo.erase(g_vBaseInfo.begin() + i);
				break;
			}
		}

		if (bFind)
		{
			g_vBaseInfo.push_back(Info);
		}

		g_seBaseInfo.Unlock();
	}
}


void CAppBase::LBtClickedBtClose(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	PostMessage(WM_CLOSE);
}


void CAppBase::LBtClickedBtMin(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码

	//ShowWindow(SW_MINIMIZE);
	PostMessage(gMsgMinWindow);
}


void CAppBase::LBtClickedBtSize(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
// 	CRect rcWork;
// 	GET_WORK_AREA(rcWork);
// 
// 	rcWork.DeflateRect(200, 100, 200, 100);
// 	ShowWindow(SW_MINIMIZE);
}


void CAppBase::StatusChangedSwAppLock(BOOL bStatus)
{
	if (bStatus)
	{
		_LockAllUis(bStatus);
	}
	else
	{
		PostMessage(gMsgAppBaseUnlockUi);
	}
}


void CAppBase::LBtClickedBtOk(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	OnOK();
}


void CAppBase::LBtClickedBtCancel(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	OnCancel();
}
