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

// ������ô���
typedef struct _tagBaseBlurInfo
{
	CWnd *pWnd;
	CString strInfo;
	int nShowCmd;
}BASE_BLUR_INFO;

// �ͻ�������
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

// Ȩ�޼���
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

// ��ʽ��������Ϣ
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
									(pInfo)->Format(_T("Err:%d(%s)��"), nErr, strTmp);\
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

// CAppBase �Ի���

class AFX_EXT_CLASS CAppBase : public CDialogEx
{
	DECLARE_DYNAMIC(CAppBase)

public:
	CAppBase(CWnd* pParent = NULL);   // ��׼���캯��
	CAppBase(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAppBase();

	// �Ի�������
	enum { IDD = IDD_APPBASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	BOOL m_bClickShow;

	CString m_strLastFile;		// ��һ�ε��õ���
	CString m_strFilePath;		// ��������·��

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
	CWnd *m_pOwner;					// ������
	BOOL m_bUiLocked;				// UI����
	BOOL m_bStatusLock;				// ״̬����
	BOOL m_bRegistered;				// ע��״̬
	BOOL m_bChildWnd;				// �Ӵ��ڱ��

	int m_nMenuStart;				// �˵���ʼ����
	REAL m_fTitleFontSize;			// ���������С
	CString m_strTitle;				// ���ڱ���
	CString m_strTitleFont;			// ��������
	COLORREF m_rgbTitle;			// �����ַ���ɫ
	COLORREF m_rgbKey;				// ͸����ɫ

	int m_nBlurCount;				// ������ô������ü���
	CTopBlur m_TopBlur;				// ���ֽ��ô���
	vector<TP_UI_LINE> m_vUiLines;	// UI����

	CBL_Button m_BtBaseClose;		// �رհ�ť
	CBL_Button m_BtBaseSize;		// ��ԭ��ť
	CBL_Button m_BtBaseMin;			// ��С����ť
	CBL_Switch m_swBaseLock;		// ������ť
	CBL_Button m_BtBaseOk;			// ȷ����ť
	CBL_Button m_BtBaseCancel;		// ȡ����ť

	int m_nRevBuffSize;				// ���ջ�������С
	BOOL m_bNetAnswered;			// ������Ϣ�Ƿ񱻻ظ�
	SOCKET m_SockClient;			// �ͻ�Socket
	char *m_pNetBuffer;				// ���ջ�����ָ��
	CWinThread *m_pNetThread;		// �����߳�

	BOOL m_bSaveOK;					// ����OKͼ��
	BOOL m_bSaveNG;					// ����NGͼ��
	CString m_strPathOK;			// OKͼ�񱣴�·��
	CString m_strPathNG;			// NGͼ�񱣴�·��

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
