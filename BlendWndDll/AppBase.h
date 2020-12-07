#pragma once

#include <vector>
using namespace std;

#include "resource.h"

#include "UdpSvr.h"
#include "TopBlur.h"
#include "GdiplusText.h"

#include "..\BlActiveXDll\BLCtrls.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// 顶层禁用窗口
typedef struct _tagBaseBlurInfo
{
	CWnd *pWnd;
	CString strInfo;
	int nShowCmd;
}BASE_BLUR_INFO;

// 客户区画线
typedef struct _tagLine
{
	CString strName;
	int nNum;
	CPoint pt1;
	CPoint pt2;
	COLORREF rgbLine;
	int nWidth;
	int nStytle;
}TP_UI_LINE;

// 权限级别
enum
{
	PSD_LEVEL_OP = 0,
	PSD_LEVEL_QC,
	PSD_LEVEL_TE,
	PSD_LEVEL_MGR,
	PSD_LEVEL_SUM
};

#define APP_LOCK_AUTO			-1

#define RGB_TRANS_TOP_KEY		RGB(55, 56, 57)
#define RGB_BT_LAYER_BACK		RGB(45, 50, 55)

#define RGB2ARGB(a, rgb)		(Color(a, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)))
#define GET_WORK_AREA(rcWork)	SystemParametersInfo(SPI_GETWORKAREA, 0, &rcWork, 0)

// 格式化错误消息
#define FORMAT_ERR_INFO(pInfo)	LPVOID lpMsgBuf;\
								const DWORD nErr = GetLastError();\
								FormatMessage(\
									FORMAT_MESSAGE_ALLOCATE_BUFFER |\
									FORMAT_MESSAGE_FROM_SYSTEM |\
									FORMAT_MESSAGE_IGNORE_INSERTS,\
									nullptr,\
									nErr,\
									MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),\
									(LPTSTR) &lpMsgBuf,\
									0,\
									nullptr\
									);\
								if (nullptr != (pInfo))\
								{\
									CString strTmp;\
									strTmp.Format(_T("%s"), lpMsgBuf);\
									strTmp.Delete(strTmp.GetLength() - 1, 1);\
									(pInfo)->Format(_T("Err:%d(%s)。"), nErr, strTmp);\
								}\
								LocalFree(lpMsgBuf)

enum
{
	IDC_BT_BASE_CANCEL = 32762,
	IDC_BT_BASE_OK,
	IDC_SW_BASE_LOCK,
	IDC_BT_BASE_MIN,
	IDC_BT_BASE_SIZE,
	IDC_BT_BASE_CLOSE
};

#ifdef _DEBUG
	#define APP_THREAD_LOCK(var, sta)	if (sta)\
	{\
		var.Lock();\
		TRACE(_T("\n%s.Lock"), var.m_strName);\
	}\
	else\
	{\
		var.Unlock();\
		TRACE(_T("\n%s.Unlock\n"), var.m_strName);\
	}
#else
	#define APP_THREAD_LOCK(var, sta)	if (sta)\
	{\
		var.Lock();\
	}\
	else\
	{\
		var.Unlock();\
	}
#endif // _DEBUG

#define CRECT2RECTF(rect)			RectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height())

static UINT gMsgAppBaseLockUi	= RegisterWindowMessage(_T("gMsgAppBaseLockUi"));
static UINT gMsgAppBaseUnlockUi	= RegisterWindowMessage(_T("gMsgAppBaseUnlockUi"));
static UINT gMsgAppBaseSetFocus	= RegisterWindowMessage(_T("gMsgAppBaseSetFocus"));
static UINT gMsgAppBaseLoadFile	= RegisterWindowMessage(_T("gMsgAppBaseLoadFile"));
static UINT gMsgMinWindow      = RegisterWindowMessage(_T("gMsgMinWindow"));

// CAppBase 对话框

class AFX_EXT_CLASS CAppBase : public CDialogEx
{
	DECLARE_DYNAMIC(CAppBase)

public:
	CAppBase(CWnd* pParent = NULL);   // 标准构造函数
	CAppBase(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAppBase();

	// 对话框数据
	enum { IDD = IDD_APPBASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	BOOL m_bClickShow;

	CString m_strLastFile;		// 上一次调用档案
	CString m_strFilePath;		// 档案保存路径

	virtual BOOL OnInitDialog();
	virtual void DrawTitle(CDC * pDC, CRect rcDraw);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);
	virtual void DrawLine(CDC * pDC, CRect rcDraw);
	virtual void LockCtrls(int nLock);
	virtual void PreWndDestroy(void);

	BOOL ShowWindow(int nCmdShow);

	CWnd * GetOwner(void);
	void SetOwner(CWnd * pOwner);

	CString GetTitle(void);
	void SetTitle(const CString & strTitle);

	COLORREF GetTitleColor(void);
	void SetTitleColor(COLORREF rgbTitle);

	void SetTitleFont(CString strFont, REAL fSize);
	CString GetTitleFont(void);
	REAL GetTitleFontSize(void);

	void LockStatus(BOOL bLock);
	void AdjustMenuPos(CBL_Menu * pMenu);

	void DrawTarget(Graphics * pGraph, Pen * pen, Brush * pBrush, GraphicsPath * pPath);
	BOOL AddLine(const CString & strName, int nIndex, CPoint pt1, CPoint pt2, COLORREF rgbLine, int nWidth, int nStyle);
	BOOL DeleteLine(const CString & strName);
	BOOL DeleteLine(int nLine);

	BOOL SendNetMsg(const CString & strIp, USHORT nPort, const CString & strMsg,
		int nBuffSize = 1024, CString * pstrBack = nullptr);
protected:
	CWnd *m_pOwner;					// 父窗口
	BOOL m_bUiLocked;				// UI锁定
	BOOL m_bStatusLock;				// 状态锁定
	BOOL m_bRegistered;				// 注册状态
	BOOL m_bChildWnd;				// 子窗口标记

	int m_nMenuStart;				// 菜单开始坐标
	REAL m_fTitleFontSize;			// 标题字体大小
	CString m_strTitle;				// 窗口标题
	CString m_strTitleFont;			// 标题字体
	COLORREF m_rgbTitle;			// 标题字符颜色
	COLORREF m_rgbKey;				// 透明颜色

	int m_nBlurCount;				// 顶层禁用窗口引用计数
	CTopBlur m_TopBlur;				// 顶怪禁用窗口
	vector<TP_UI_LINE> m_vUiLines;	// UI线条

	CBL_Button m_BtBaseClose;		// 关闭按钮
	CBL_Button m_BtBaseSize;		// 还原按钮
	CBL_Button m_BtBaseMin;			// 最小化按钮
	CBL_Switch m_swBaseLock;		// 锁定按钮
	CBL_Button m_BtBaseOk;			// 确定按钮
	CBL_Button m_BtBaseCancel;		// 取消按钮

	int m_nRevBuffSize;				// 接收缓冲区大小
	BOOL m_bNetAnswered;			// 网络消息是否被回复
	SOCKET m_SockClient;			// 客户Socket
	char *m_pNetBuffer;				// 接收缓冲区指针
	CWinThread *m_pNetThread;		// 接收线程

	BOOL m_bSaveOK;					// 保存OK图像
	BOOL m_bSaveNG;					// 保存NG图像
	CString m_strPathOK;			// OK图像保存路径
	CString m_strPathNG;			// NG图像保存路径

	virtual BOOL _LoadFileEx(void);
	virtual void _DefaultFocus(void);

	int _Rand(int nMin, int nMax);
	void _DelayMs(int nTime);

	BOOL _GetLockState(int nLock, int nLevel);
	BOOL _IsUiLocked(void);
	void _LockAllUis(BOOL bLock);

	int _GetPsdLeve(void);
	void _SetPsdLeve(int nLevel);
	BOOL _IsPsdLevel(int nLevel);

	void _SendBlurMsg(BOOL bShow);
	void _AddBlurInfo(CWnd * pDstWnd, const CString & strWnd);
	void _RemoveBlurInfo(CWnd * pDstWnd);

	void _DeleteSpace(CString & strData);
	vector<CString> _GetSegInfo(const CString & strInfo, char nMark);

	BOOL _SaveOkNgPath(void);
	BOOL _LoadOkNgPath(void);

	BOOL _SaveFile(CBL_Menu * pMenu, const CString & strType, const CString & strExt, BOOL bSaveAs);
	BOOL _LoadFile(CBL_Menu * pMenu, const CString & strType, const CString & strExt, BOOL bRecent);
	BOOL _LoadFile(CBL_Menu * pMenu, const CString & strType, const CString & strExt, const CString & strFile);

	BOOL _IsFileDirty(void);
	void _FileDirty(BOOL bDirty);
	void _SetTitleFromPath(CBL_Menu * pMenu);
	void _SetNoTitle(CBL_Menu * pMenu);

	CString _GetCurPath(void);
	CString _GetSysFontPath(void);

	BOOL _InstallFont(CString strFile);
	BOOL _RemoveFont(CString strFont);

	BOOL _RegisterActivex(BOOL bRegister);

	static UINT _ReceiveNetMsgThread(LPVOID pParam);
	UINT _ReceiveNetMsgThreadKernal(void);
protected:
	afx_msg LRESULT OnGmsgsemitransblur(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgappbaselockui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgappbaseunlockui(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgappbasesetfocus(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
public:
	void LBtClickedBtClose(long nFlags);
	void LBtClickedBtSize(long nFlags);
	void LBtClickedBtMin(long nFlags);
	void StatusChangedSwAppLock(BOOL bStatus);
	void LBtClickedBtOk(long nFlags);
	void LBtClickedBtCancel(long nFlags);
};
