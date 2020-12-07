#pragma once

#include "resource.h"

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#endif

class AFX_EXT_CLASS CComRevData
{
public:
	CComRevData(void)
	{
		m_nCount = 0;
	}

	~CComRevData(void)
	{
	}

	BYTE m_szData[4096];
	int m_nCount;
};

static UINT gMsgSerialReceiveChar = RegisterWindowMessage(_T("gMsgSerialReceiveChar"));
static UINT gMsgSerialHardwardInfo = RegisterWindowMessage(_T("gMsgSerialHardwardInfo"));
static UINT gMsgSerialParamChanged = RegisterWindowMessage(_T("gMsgSerialParamChanged"));

#define WM_COMM_BREAK_DETECTED		0	// A break was detected on input.
#define WM_COMM_CTS_DETECTED		1	// The CTS (clear-to-send) signal changed state. 
#define WM_COMM_DSR_DETECTED		2	// The DSR (data-set-ready) signal changed state. 
#define WM_COMM_ERR_DETECTED		3	// A line-status error occurred. Line-status errors are CE_FRAME, CE_OVERRUN, and CE_RXPARITY. 
#define WM_COMM_RING_DETECTED		4	// A ring indicator was detected. 
#define WM_COMM_RLSD_DETECTED		5	// The RLSD (receive-line-signal-detect) signal changed state. 
#define WM_COMM_RXFLAG_DETECTED		6	// The event character was received and placed in the input buffer.  
#define WM_COMM_TXEMPTY_DETECTED	7	// The last character in the output buffer was sent.  

#define COM_PORT_DATA_SUM			5

enum 
{
	COM_DATA_ASCII_MODE = 0,
	COM_DATA_DEC_MODE,
	COM_DATA_HEX_MODE
};

// CSerialPort 对话框

class CSerialPort : public CTpLayerWnd
{
	DECLARE_SERIAL(CSerialPort)

public:
	CSerialPort(CWnd* pParent = NULL);   // 标准构造函数
	CSerialPort(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CSerialPort();

// 对话框数据
	enum { IDD = IDD_SERIALPORT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	CBL_Edit m_editStatus;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);
	virtual void _DefaultFocus(void);

	BOOL Init(int nPort);
	BOOL ClosePort(void);
	BOOL IsOpen(void);

	int GetPortNumber(void);
	void SetPortNumber(int nPort);

	BOOL Write2Port(const BYTE byData);
	BOOL Write2Port(const CString & strData, int nSendMode);
	BOOL Write2Port(const BYTE *pData, int nLength);
	BOOL Write2Port(const vector<BYTE> byData);

	void SaveSetData(CString *pstrPath = nullptr);
	void LoadSetData(CString *pstrPath = nullptr);
protected:
	BOOL m_bOpen;
	int m_nRevMode;
	int m_nSendMode;
	int m_nSetData[COM_PORT_DATA_SUM];	

	std::vector<int> m_vRevShow;
	CString m_strRevData;
	CString m_strSendData;
	
	int m_nSetDataBkup[COM_PORT_DATA_SUM];

	virtual void _PreShowWnd(void);
	void _UpdateUi(void);

	BOOL _StartMonitoring(void);
	BOOL _StopMonitoring(void);
	static UINT	_CommThread(LPVOID pParam);
	UINT _ThreadFuncKernal(void);

	void _WriteChar(void);
	void _ReceiveChar(COMSTAT Comstat);
protected:
	HANDLE m_hSerialPort;
	CWinThread *m_pThread;
	BOOL m_bThreadAlive;

	CCriticalSection m_csSync;
	BOOL m_bSendFinish;

	HANDLE m_hWriteEvent;
	HANDLE m_hShutdownEvent;
	HANDLE m_hEventArray[3];

	OVERLAPPED m_OverLapped;
	COMMTIMEOUTS m_CommTimeouts;
	DCB m_DCB;

	BYTE *m_pszWriteBuffer;
	DWORD m_dwCommEvents;
	COMSTAT m_Comstat;
	DWORD m_dwWriteSize;
protected:
	afx_msg LRESULT OnGmsgserialreceivechar(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDnPortSet(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRadRevMode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRadSendMode(WPARAM wParam, LPARAM lParam);	
public:
	void LBtClickedBtClearReceive(long nFlags);
	void LBtClickedBtSendData(long nFlags);
	void TextChangedDnSendData(LPCTSTR strNew);
	void SelectChangedDnSendData(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void LBtClickedBtComOk(long nFlags);
	void LBtClickedBtComCancel(long nFlags);
};
