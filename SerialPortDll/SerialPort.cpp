// SerialPort.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialPort.h"
#include "afxdialogex.h"

#define m_nPortNumber		m_nSetData[0]
#define m_nBaudRate			m_nSetData[1]
#define m_nDataBits			m_nSetData[2]
#define m_nStopBits			m_nSetData[3]
#define m_nCheckMode		m_nSetData[4]

#define COM_OPEN_FAIL		m_editStatus.SetValueColor(RGB(230, 55, 55));\
							m_editStatus.SetValueText(_T("打开失败"))

#define WM_DN_PORT_SET		WM_USER + 1
#define WM_RD_REV_MODE		WM_USER + 2
#define WM_RD_SEND_MODE		WM_USER + 3


#define COM_REV_DATA_SHOW_MODE		3
#define COM_SEND_DATA_MODE			3

// CSerialPort 对话框

IMPLEMENT_SERIAL(CSerialPort, CTpLayerWnd, 1 | VERSIONABLE_SCHEMA);

CSerialPort::CSerialPort(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSerialPort::IDD, pParent)
	, m_bOpen(FALSE)
	, m_nRevMode(COM_DATA_HEX_MODE)
	, m_nSendMode(COM_DATA_HEX_MODE)
	, m_hSerialPort(nullptr)
	, m_pThread(nullptr)
	, m_bThreadAlive(FALSE)
	, m_bSendFinish(TRUE)
	, m_hWriteEvent(nullptr)
	, m_hShutdownEvent(nullptr)
	, m_pszWriteBuffer(nullptr)
	, m_dwWriteSize(1)
{
	for (int i = 0; i < COM_PORT_DATA_SUM; i++)
	{
		m_nSetDataBkup[i] = 0;
	}

	m_nPortNumber	= 0;
	m_nBaudRate		= 9600;
	m_nDataBits		= 8;
	m_nStopBits		= 1;
	m_nCheckMode	= 0;

	m_OverLapped.Offset = 0;
	m_OverLapped.OffsetHigh = 0;
	m_OverLapped.hEvent = nullptr;
}

CSerialPort::CSerialPort(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_bOpen(FALSE)
	, m_nRevMode(COM_DATA_HEX_MODE)
	, m_nSendMode(COM_DATA_HEX_MODE)
	, m_hSerialPort(nullptr)
	, m_pThread(nullptr)
	, m_bThreadAlive(FALSE)
	, m_bSendFinish(TRUE)
	, m_hWriteEvent(nullptr)
	, m_hShutdownEvent(nullptr)
	, m_pszWriteBuffer(nullptr)
	, m_dwWriteSize(1)
{
	for (int i = 0; i < COM_PORT_DATA_SUM; i++)
	{
		m_nSetDataBkup[i] = 0;
	}

	m_nPortNumber	= 0;
	m_nBaudRate		= 9600;
	m_nDataBits		= 8;
	m_nStopBits		= 1;
	m_nCheckMode	= 0;

	m_OverLapped.Offset = 0;
	m_OverLapped.OffsetHigh = 0;
	m_OverLapped.hEvent = nullptr;
}

CSerialPort::~CSerialPort()
{
	ClosePort();

	if (nullptr != m_pszWriteBuffer)
	{
		delete []m_pszWriteBuffer;
		m_pszWriteBuffer = nullptr;
	}
}

void CSerialPort::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_COM_STATUS, m_editStatus);
}


BEGIN_MESSAGE_MAP(CSerialPort, CTpLayerWnd)
	ON_REGISTERED_MESSAGE(gMsgSerialReceiveChar, &CSerialPort::OnGmsgserialreceivechar)
	ON_MESSAGE(WM_DN_PORT_SET, &CSerialPort::OnDnPortSet)
	ON_MESSAGE(WM_RD_REV_MODE, &CSerialPort::OnRadRevMode)
	ON_MESSAGE(WM_RD_SEND_MODE, &CSerialPort::OnRadSendMode)	
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CSerialPort, CTpLayerWnd)
	ON_EVENT(CSerialPort, IDC_BT_CLEAR_RECEIVE, 1, CSerialPort::LBtClickedBtClearReceive, VTS_I4)
	ON_EVENT(CSerialPort, IDC_BT_SEND_DATA, 1, CSerialPort::LBtClickedBtSendData, VTS_I4)
	ON_EVENT(CSerialPort, IDC_DN_SEND_DATA, 1, CSerialPort::TextChangedDnSendData, VTS_BSTR)
	ON_EVENT(CSerialPort, IDC_DN_SEND_DATA, 3, CSerialPort::SelectChangedDnSendData, VTS_BSTR VTS_BSTR VTS_I2)
	ON_EVENT(CSerialPort, IDC_BT_COM_OK, 1, CSerialPort::LBtClickedBtComOk, VTS_I4)
	ON_EVENT(CSerialPort, IDC_BT_COM_CANCEL, 1, CSerialPort::LBtClickedBtComCancel, VTS_I4)	
END_EVENTSINK_MAP()

// CSerialPort 消息处理程序


BOOL CSerialPort::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
// 	CRect rcWnd;
// 	GetDlgItem(IDC_DN_SEND_DATA)->GetWindowRect(rcWnd);
// 	ScreenToClient(rcWnd);
// 
// 	rcWnd.right--;
// 	GetDlgItem(IDC_DN_SEND_DATA)->MoveWindow(rcWnd);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSerialPort:: _DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}
void CSerialPort::Serialize(CArchive& ar)
{
	ar.SerializeClass(RUNTIME_CLASS(CSerialPort));

	if (ar.IsStoring())
	{	// storing code
		for (int i = 0; i < COM_PORT_DATA_SUM; i++)
		{
			ar << m_nSetData[i];
		}
	}
	else
	{	// loading code
		const UINT nSchema = ar.GetObjectSchema();

		switch (nSchema)
		{
		case 1:
			for (int i = 0; i < COM_PORT_DATA_SUM; i++)
			{
				ar >> m_nSetData[i];
			}
			break;

		default:
			break;
		}

		if (nullptr != GetSafeHwnd())
		{
			Init(m_nPortNumber);

			_UpdateUi();
			LockCtrls(-1);
		}
	}

 	_FileDirty(FALSE);
}


void CSerialPort::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	for (int i = 0; i < COM_PORT_DATA_SUM; i++)
	{
		m_nSetData[i] = m_nSetDataBkup[i];
	}

	m_vRevShow.clear();
	m_strRevData.Empty();

	CTpLayerWnd::OnCancel();
}


void CSerialPort::LockCtrls(int nLock)
{
	if (nLock < 0)
	{
		m_bUiLocked = _IsUiLocked() || (_GetPsdLeve() < PSD_LEVEL_TE);
	}
	else
	{
		m_bUiLocked = (nLock > 0) || (_GetPsdLeve() < PSD_LEVEL_TE);
	}

	const BOOL bEnable = !m_bUiLocked;

	CBL_DropDown *pDropDown = (CBL_DropDown *)GetDlgItem(IDC_DN_COM_PORT);
	pDropDown->SetReadOnly(m_bUiLocked);

	for (int i = 1; i < COM_PORT_DATA_SUM; i++)
	{
		CBL_DropDown *pDropDown = (CBL_DropDown *)GetDlgItem(IDC_DN_COM_PORT + i);
		pDropDown->SetReadOnly(m_bUiLocked);
	}

	for (int i = 0; i < COM_REV_DATA_SHOW_MODE; i++)
	{
		CBL_Radio *pRadio = (CBL_Radio *)GetDlgItem(IDC_RD_RECEIVE_ASCII + i);
		pRadio->EnableWindow(bEnable);
	}

	const CString strData = ((CBL_DropDown *)(GetDlgItem(IDC_DN_SEND_DATA)))->GetValueText();

	GetDlgItem(IDC_BT_SEND_DATA)->EnableWindow(bEnable && !strData.IsEmpty() && m_bOpen);
	GetDlgItem(IDC_BT_COM_OK)->EnableWindow(bEnable);
}


BOOL CSerialPort::Init(int nPort)
{
	if (nPort < 1)
	{
		if (m_bOpen)
		{
			ClosePort();
		}

		return TRUE;
	}

	ClosePort();

	m_nPortNumber = nPort;

	while (m_bThreadAlive)
	{
		SetEvent(m_hShutdownEvent);
	}

	// Create events
	if (nullptr != m_OverLapped.hEvent)
	{
		ResetEvent(m_OverLapped.hEvent);
	}
	else
	{
		// 重叠访问事件
		// 手工复位为无信号状态
		// 初始状态为有无信号状态
		// 无名事件对象
		// 默认安全属性, 
		m_OverLapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);		
	}

	if (nullptr != m_hWriteEvent)
	{
		ResetEvent(m_hWriteEvent);
	}
	else
	{
		m_hWriteEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	}

	if (nullptr != m_hShutdownEvent)
	{
		ResetEvent(m_hShutdownEvent);
	}
	else
	{
		m_hShutdownEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
	}

	m_hEventArray[0] = m_hShutdownEvent;	// 最高优先级
	m_hEventArray[1] = m_OverLapped.hEvent;
	m_hEventArray[2] = m_hWriteEvent;

	m_dwCommEvents = EV_RXFLAG | EV_RXCHAR;

	m_csSync.Lock();

	if (nullptr != m_hSerialPort)
	{
		CloseHandle(m_hSerialPort);
		m_hSerialPort = nullptr;
	}

	BOOL bResult = FALSE;
	CString strPort;
	CString strProperty;

	strPort.Format(_T("COM%d"), m_nPortNumber);

	TCHAR tCheck = 'N';

	switch (m_nCheckMode)
	{
	case 0:
		tCheck = 'N';
		break;

	case 1:
		tCheck = 'O';
		break;

	case 2:
		tCheck = 'E';
		break;

	case 3:
		tCheck = 'M';
		break;

	case 4:
		tCheck = 'S';
		break;

	default:
		tCheck = 'N';
		break;
	}

	strProperty.Format(_T("baud=%d parity=%c data=%d stop=%d"),
		m_nBaudRate,
		tCheck,
		m_nDataBits,
		m_nStopBits);

	m_hSerialPort = CreateFile(strPort,
		GENERIC_READ | GENERIC_WRITE,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		0);

	if (INVALID_HANDLE_VALUE == m_hSerialPort)
	{
		m_bOpen = FALSE;

		m_editStatus.SetValueColor(RGB(230, 55, 55));
		m_editStatus.SetValueText(_T("打开失败！串口不在在或被占用。"));

		goto LABEL_END;
	}

	m_CommTimeouts.ReadIntervalTimeout			= 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier	= 1000;
	m_CommTimeouts.ReadTotalTimeoutConstant		= 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier	= 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant	= 1000;

	if (SetCommTimeouts(m_hSerialPort, &m_CommTimeouts))
	{						   
		if (SetCommMask(m_hSerialPort, m_dwCommEvents))
		{
			if (GetCommState(m_hSerialPort, &m_DCB))
				// DCB结构包含了诸如波特率、每个字符的数据位数、奇偶校验和停止位数等信息。
				// 在查询或配置置串行口的属性时，都要用DCB结构来作为缓冲区。
			{
				m_DCB.EvtChar = 'Q';
				m_DCB.fRtsControl = RTS_CONTROL_ENABLE;	// Set RTS bit high!

				if (BuildCommDCB(strProperty, &m_DCB))
				{
					if (!SetCommState(m_hSerialPort, &m_DCB))
					{
						CMsgBox MsgBox(this);
						MsgBox.ShowMsg(_T("SetCommState()"), _T("SerialPort"), MB_OK | MB_ICONERROR);

						CBL_Edit *pEdit = (CBL_Edit *)GetDlgItem(IDC_EDIT_COM_STATUS);

						m_editStatus.SetCaption(_T("端口初始化函数SetCommState()错误！"));

						m_bOpen = FALSE;

						COM_OPEN_FAIL;

						goto LABEL_END;
					}
				}
				else
				{
					CMsgBox MsgBox(this);
					MsgBox.ShowMsg(_T("BuildCommDCB()"), _T("SerialPort"), MB_OK | MB_ICONERROR);
					m_editStatus.SetCaption(_T("端口初始化函数BuildCommDCB()错误！"));

					m_bOpen = FALSE;

					COM_OPEN_FAIL;

					goto LABEL_END;
				}
			}
			else
			{
				CMsgBox MsgBox(this);
				MsgBox.ShowMsg(_T("GetCommState()"), _T("SerialPort"), MB_OK | MB_ICONERROR);
				m_editStatus.SetCaption(_T("端口初始化函数GetCommState()错误！"));

				m_bOpen = FALSE;

				COM_OPEN_FAIL;

				goto LABEL_END;
			}
		}
		else
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("SetCommMask()"), _T("SerialPort"), MB_OK | MB_ICONERROR);
			m_editStatus.SetCaption(_T("端口初始化函数SetCommMask()错误！"));

			m_bOpen = FALSE;

			COM_OPEN_FAIL;

			goto LABEL_END;
		}
	}
	else
	{
		CMsgBox MsgBox(this);
		MsgBox.ShowMsg(_T("SetCommTimeouts()"), _T("SerialPort"), MB_OK | MB_ICONERROR);
		m_editStatus.SetCaption(_T("端口初始化函数SetCommTimeouts()错误！"));

		m_bOpen = FALSE;

		COM_OPEN_FAIL;

		goto LABEL_END;
	}

	// flush the port
	PurgeComm(m_hSerialPort, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	m_bOpen = TRUE;

	m_editStatus.SetValueColor(RGB(0, 255, 255));
	m_editStatus.SetValueText(_T("打开成功"));

	_StartMonitoring();

LABEL_END:

	m_csSync.Unlock();

// 	if (nullptr != GetSafeHwnd() && IsWindowVisible())
// 	{
// 		_UpdateUi();
// 	}

	return m_bOpen;
}


BOOL CSerialPort::ClosePort(void)
{
	while (m_bThreadAlive)
	{
		SetEvent(m_hShutdownEvent);
	}

	// If the port is still opened: close it 
	if (nullptr != m_hSerialPort)
	{
		CloseHandle(m_hSerialPort);
		m_hSerialPort = nullptr;
	}

	// Close Handles
	if(nullptr != m_hShutdownEvent)
	{
		CloseHandle(m_hShutdownEvent);
		m_hShutdownEvent = nullptr;
	}

	if(nullptr != m_OverLapped.hEvent)
	{
		CloseHandle(m_OverLapped.hEvent);
		m_OverLapped.hEvent = nullptr;
	}

	if(nullptr != m_hWriteEvent)
	{
		CloseHandle(m_hWriteEvent);
		m_hWriteEvent = nullptr;
	}

	delete [] m_pszWriteBuffer;
	m_pszWriteBuffer = nullptr;

	m_pThread = nullptr;

	m_bOpen = FALSE;

	return TRUE;
}


BOOL CSerialPort::IsOpen(void)
{
	return m_bOpen;
}


int CSerialPort::GetPortNumber(void)
{
	return m_nPortNumber;
}


void CSerialPort::SetPortNumber(int nPort)
{
	m_nPortNumber = nPort;
}


BOOL CSerialPort::Write2Port(const BYTE byData)
{
	if (!m_bOpen)
	{
		return FALSE;
	}

//	int nWarnTime = 0;

	while (!m_bSendFinish)
	{
// 		LARGE_INTEGER lTemp;
// 
// 		LONGLONG QStart = 0;
// 		LONGLONG QEnd = 0;
// 		double dFreq = 0;
// 		double dTime = 0;
// 
// 		QueryPerformanceFrequency(&lTemp);
// 		dFreq = (double)lTemp.QuadPart;
// 
// 		QueryPerformanceCounter(&lTemp);
// 		QStart = lTemp.QuadPart;
// 
// 		do
// 		{
// 			QueryPerformanceCounter(&lTemp);
// 			QEnd	= lTemp.QuadPart;
// 			dTime	= (double)(QEnd - QStart) / dFreq;
// 			dTime	*= 1000;
// 		} while (dTime < 1);
// 
// 		nWarnTime++;
// 
// 		if (nWarnTime > 5000)
// 		{
// 			return FALSE;
// 		}
		;
	}

	m_bSendFinish = FALSE;

	m_dwWriteSize = 1;	

	delete []m_pszWriteBuffer;
	m_pszWriteBuffer = nullptr;
	m_pszWriteBuffer = new BYTE[2];

	if (nullptr == m_pszWriteBuffer)
	{
		m_bSendFinish = TRUE;
		return FALSE;
	}

	m_pszWriteBuffer[0] = byData;
	m_pszWriteBuffer[1] = 0;

	SetEvent(m_hWriteEvent);

	return TRUE;
}


BOOL CSerialPort::Write2Port(const CString & strData, int nSendMode)
{
	if (!m_bOpen)
	{
		return FALSE;
	}

	if (nSendMode)
	{
		std::vector<int> vSendData;

		CString strTemp = strData;

		while (' ' == strTemp[strTemp.GetLength() - 1])
		{
			strTemp.Delete(strTemp.GetLength() - 1);
		}

		int nFind = 0;
		const int nSize = strTemp.GetLength();

		for (int i = 0; i < nSize; i++)
		{
			if (' ' == strTemp[i])
			{
				const CString strSend = strTemp.Mid(nFind, i - nFind);
				const int nSendLendth = strSend.GetLength();

				if (1 == nSendMode)
				{
					int nDecData = 0;

					for (int nDec = 0; nDec < nSendLendth; nDec++)
					{
						int nTemp = strSend[nDec] - '0';

						if (nTemp < 0 || nTemp > 9)
						{
							return FALSE;
						}

						int nScale = 1;

						for (int nAdd = 0; nAdd < nSendLendth - nDec - 1; nAdd++)
						{
							nScale *= 10;
						}

						nTemp *= nScale;
						nDecData += nTemp;
					}

					vSendData.push_back(nDecData);
				}
				else
				{
					int nHexData = 0;

					for (int nHex = 0; nHex < nSendLendth; nHex++)
					{
						int nTemp = strSend[nHex];

						if (nTemp >= 'A')
						{
							nTemp = nTemp - 'A' + 10;
						}
						else if ('0' <= nTemp && nTemp <= '9')
						{
							nTemp -= '0';
						}
						else
						{
							return FALSE;
						}

						nTemp <<= ((nSendLendth - nHex - 1) << 2);

						nHexData += nTemp;
					}

					vSendData.push_back(nHexData);
				}

				nFind = i + 1;
			}
		}

 		if (nSize - nFind)
 		{
			const CString strSend = strTemp.Mid(nFind, nSize - nFind);
			const int nSendLendth = strSend.GetLength();

			if (1 == nSendMode)
			{
				int nDecData = 0;

				for (int nDec = 0; nDec < nSendLendth; nDec++)
				{
					int nTemp = strSend[nDec] - '0';

					if (nTemp < 0 || nTemp > 9)
					{
						return FALSE;
					}

					int nScale = 1;

					for (int nAdd = 0; nAdd < nSendLendth - nDec - 1; nAdd++)
					{
						nScale *= 10;
					}

					nTemp *= nScale;
					nDecData += nTemp;
				}

				vSendData.push_back(nDecData);
			}
			else
			{
				int nHexData = 0;

				for (int nHex = 0; nHex < nSendLendth; nHex++)
				{
					int nTemp = strSend[nHex];

					if (nTemp >= 'A')
					{
						nTemp = nTemp - 'A' + 10;
					}
					else if ('0' <= nTemp && nTemp <= '9')
					{
						nTemp -= '0';
					}
					else
					{
						return FALSE;
					}

					nTemp <<= ((nSendLendth - nHex - 1) << 2);

					nHexData += nTemp;
				}

				vSendData.push_back(nHexData);
			}
		}

		while (!m_bSendFinish);

		m_bSendFinish = FALSE;

		m_dwWriteSize = vSendData.size();		

		delete []m_pszWriteBuffer;
		m_pszWriteBuffer = nullptr;
		m_pszWriteBuffer = new BYTE[m_dwWriteSize + 1];

		if (nullptr == m_pszWriteBuffer)
		{
			m_bSendFinish = TRUE;

			return FALSE;
		}

		memset(m_pszWriteBuffer, 0, m_dwWriteSize + 1);

		for (DWORD dwCounter = 0; dwCounter < m_dwWriteSize; dwCounter++)
		{
			m_pszWriteBuffer[dwCounter] = vSendData[dwCounter];
		}
	}
	else
	{
		USES_CONVERSION;

		while (!m_bSendFinish);

		m_bSendFinish = FALSE;
		m_dwWriteSize = strlen(W2A(strData));

		delete []m_pszWriteBuffer;
		m_pszWriteBuffer = nullptr;
		m_pszWriteBuffer = new BYTE[m_dwWriteSize + 1];

		if (nullptr == m_pszWriteBuffer)
		{
			m_bSendFinish = TRUE;

			return FALSE;
		}

		memset(m_pszWriteBuffer, 0, m_dwWriteSize + 1);
		memcpy(m_pszWriteBuffer, W2A(strData), m_dwWriteSize);
	}

	// Set event for write
	SetEvent(m_hWriteEvent);

	return TRUE;
}


BOOL CSerialPort::Write2Port(const BYTE *pData, int nLength)
{
	if (!m_bOpen)
	{
		return FALSE;
	}

	while (!m_bSendFinish);

	m_bSendFinish = FALSE;

	m_dwWriteSize = nLength;

	delete []m_pszWriteBuffer;
	m_pszWriteBuffer = nullptr;
	m_pszWriteBuffer = new BYTE[nLength + 1];

	if (nullptr == m_pszWriteBuffer)
	{
		m_bSendFinish = TRUE;
		return FALSE;
	}

	for (int i = 0; i < nLength; i++)
	{
		m_pszWriteBuffer[i] = pData[i];
	}

	m_pszWriteBuffer[nLength] = 0;

	SetEvent(m_hWriteEvent);

	return TRUE;
}


void CSerialPort::SaveSetData(CString *pstrPath/* = nullptr */)
{
	BOOL bNull = TRUE;

	if (nullptr == pstrPath)
	{
		bNull = FALSE;
		pstrPath = new CString;
		GetModuleFileName(nullptr, pstrPath->GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
		pstrPath->ReleaseBuffer(); 
		pstrPath->Replace(_T(".exe"), _T(".ini"));
	}

	CString strKey;
	strKey.Format(_T("COM-%d Config"), m_nPortNumber);

	CString strValue;

	strValue.Format(_T("%d"), m_nPortNumber);
	WritePrivateProfileString(strKey, _T("m_nPortNumber"), strValue, *pstrPath);

	strValue.Format(_T("%d"), m_nBaudRate);
	WritePrivateProfileString(strKey, _T("m_nBaudRate"), strValue, *pstrPath);

	strValue.Format(_T("%d"), m_nDataBits);
	WritePrivateProfileString(strKey, _T("m_nDataBits"), strValue, *pstrPath);

	strValue.Format(_T("%d"), m_nStopBits);
	WritePrivateProfileString(strKey, _T("m_nStopBits"), strValue, *pstrPath);

	strValue.Format(_T("%d"), m_nCheckMode);
	WritePrivateProfileString(strKey, _T("m_nCheckMode"), strValue, *pstrPath);

	if (bNull)
	{
		delete pstrPath;
	}
}


void CSerialPort::LoadSetData(CString *pstrPath/* = nullptr */)
{
	BOOL bNull = TRUE;

	if (nullptr == pstrPath)
	{
		bNull = FALSE;
		pstrPath = new CString;
		GetModuleFileName(nullptr, pstrPath->GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
		pstrPath->ReleaseBuffer(); 
		pstrPath->Replace(_T(".exe"), _T(".ini"));
	}

	CString strKey;
	strKey.Format(_T("COM-%d Config"), m_nPortNumber);

	CString strValue;

	m_nPortNumber	= GetPrivateProfileInt(strKey, _T("m_nPortNumber"), 0, *pstrPath);
	m_nBaudRate		= GetPrivateProfileInt(strKey, _T("m_nBaudRate"), 9600, *pstrPath);
	m_nDataBits		= GetPrivateProfileInt(strKey, _T("m_nDataBits"), 8, *pstrPath);
	m_nStopBits		= GetPrivateProfileInt(strKey, _T("m_nStopBits"), 1, *pstrPath);
	m_nCheckMode	= GetPrivateProfileInt(strKey, _T("m_nCheckMode"), 0, *pstrPath);

	if (bNull)
	{
		delete pstrPath;
	}
}


void CSerialPort::_PreShowWnd(void)
{
	if (!IsWindowVisible())
	{
		for (int i = 0; i < COM_PORT_DATA_SUM; i++)
		{
			m_nSetDataBkup[i] = m_nSetData[i];
		}
	}

	_UpdateUi();
	LockCtrls(-1);
}


void CSerialPort::_UpdateUi(void)
{
	for (int i = 0; i < COM_PORT_DATA_SUM; i++)
	{
		CBL_DropDown *pDropDown = (CBL_DropDown *)GetDlgItem(IDC_DN_COM_PORT + i);

		if ((0 == i) || (COM_PORT_DATA_SUM - 1 == i))
		{
			pDropDown->SetCurSelect(m_nSetData[i]);
		}
		else
		{
			CString strData;
			strData.Format(_T("%d"), m_nSetData[i]);

			pDropDown->SelectItem(strData);
		}
	}

	for (int i = 0; i < COM_REV_DATA_SHOW_MODE; i++)
	{
		CBL_Radio *pRadio = (CBL_Radio *)GetDlgItem(IDC_RD_RECEIVE_ASCII + i);
		pRadio->SetSelect(i == m_nRevMode);
	}

	for (int i = 0; i < COM_SEND_DATA_MODE; i++)
	{
		CBL_Radio *pRadio = (CBL_Radio *)GetDlgItem(IDC_RD_SEND_ASCII + i);
		pRadio->SetSelect(i == m_nRevMode);
	}

	((CBL_DropDown *)(GetDlgItem(IDC_DN_SEND_DATA)))->SetCurSelect(0);
}


BOOL CSerialPort::_StartMonitoring(void)
{
	m_bThreadAlive = TRUE;

	m_pThread = AfxBeginThread(_CommThread, this);
	
	while (!m_bThreadAlive)
	{
		;
	}

	return (nullptr != m_pThread);
}


BOOL CSerialPort::_StopMonitoring(void)
{
	if (nullptr != m_pThread)
	{
		m_pThread->SuspendThread(); 
	}

	return TRUE;
}


UINT CSerialPort::_CommThread(LPVOID pParam)
{
	CSerialPort *pPort = (CSerialPort *)pParam;
	return pPort->_ThreadFuncKernal();
}


UINT CSerialPort::_ThreadFuncKernal(void)
{
	DWORD dwBytesTransfered = 0;
	DWORD dwEvent = 0;
	DWORD dwCommEvent = 0;
	DWORD dwError = 0;	
	BOOL bResult = FALSE;

	if (nullptr != m_hSerialPort)
	{
		PurgeComm(m_hSerialPort, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	}

	while (TRUE)
	{
		// Make a call to WaitCommEvent().  This call will return immediatEly
		// because our port was created as an Asynchronous port (FILE_FLAG_OVERLAPPED
		// and an m_OverlappedStructerlapped structure specified).  This call will cause the 
		// m_OverlappedStructerlapped element m_OverlappedStruct.hEvent, which is part of the m_hEventArray to 
		// be placed in a non-signed state if there are no bytes available to be read,
		// or to a signed state if there are bytes available.  If this event handle 
		// is set to the non-signed state, it will be set to signed when a 
		// character arrives at the port.

		// We do this for each port!

		bResult = WaitCommEvent(m_hSerialPort, &dwEvent, &m_OverLapped);

		if (bResult)
		{
			// If WaitCommEvent() returns TRUE, check to be sure there are
			// actually bytes in the buffer to read.  
			//
			// If you are reading more than one byte at a time from the buffer 
			// (which this program does not do) you will have the situation occur 
			// where the first byte to arrive will cause the WaitForMultipleObjects() 
			// function to stop waiting.  The WaitForMultipleObjects() function 
			// resets the event handle in m_OverlappedStruct.hEvent to the non-signelead state
			// as it returns.  
			//
			// If in the time between the reset of this event and the call to 
			// ReadFile() more bytes arrive, the m_OverlappedStruct.hEvent handle will be set again
			// to the signed state. When the call to ReadFile() occurs, it will 
			// read all of the bytes from the buffer, and the program will
			// loop back around to WaitCommEvent().
			// 
			// At this point you will be in the situation where m_OverlappedStruct.hEvent is set,
			// but there are no bytes available to read.  If you proceed and call
			// ReadFile(), it will return immediately due to the Asynchronous port setup, but
			// GetOverlappedResults() will not return until the next character arrives.
			//
			// It is not desirable for the GetOverlappedResults() function to be in 
			// this state.  The thread shutdown event (event 0) and the WriteFile()
			// event (Event2) will not work if the thread is blocked by GetOverlappedResults().
			//
			// The solution to this is to check the buffer with a call to ClearCommError().
			// This call will reset the event handle, and if there are no bytes to read
			// we can loop back through WaitCommEvent() again, then proceed.
			// If there are really bytes to read, do nothing and proceed.

			bResult = ClearCommError(m_hSerialPort, &dwError, &m_Comstat);

			if (!m_Comstat.cbInQue)
			{
				continue;
			}
		}
		else
		{ 
			// If WaitCommEvent() returns FALSE, process the last error to determine
			// the reason..
			dwError = GetLastError();

			switch (dwError)
			{ 
			case ERROR_IO_PENDING: 	
				// This is a normal return value if there are no bytes
				// to read at the port.
				// Do nothing and continue
				break;

			case 87:
				// Under Windows NT, this value is returned for some reason.
				// I have not investigated why, but it is also a valid reply
				// Also do nothing and continue.
				break;

			default:
				{
					CMsgBox MsgBox(this);
					MsgBox.ShowMsg(_T("WaitCommEvent() Eoror!"), _T("SerialPort"), MB_OK | MB_ICONERROR);
				}

				return 0;
				break;
			}
		}

		// Main wait function.  This function will normally block the thread
		// until one of nine events occur that require action.
		dwEvent = WaitForMultipleObjects(3, m_hEventArray, FALSE, INFINITE);

		switch (dwEvent)
		{
		case 0:
			// Shutdown event.  This is event zero so it will be
			// the highest priority and be serviced first.
			CloseHandle(m_hSerialPort);
			m_hSerialPort = nullptr;
			m_bThreadAlive = FALSE;

			// Kill this thread.  Break is not needed.
			AfxEndThread(100);
			break;

		case 1:	// Read event
			GetCommMask(m_hSerialPort, &dwCommEvent);

			if (dwCommEvent & EV_RXCHAR)	// 接收到字符，并置于输入缓冲区中				
			{
				_ReceiveChar(m_Comstat);
			}

			if (dwCommEvent & EV_CTS)		// CTS信号状态发生变化
			{
				m_pOwner->SendMessage(gMsgSerialHardwardInfo, m_nPortNumber, WM_COMM_CTS_DETECTED);
			}
			if (dwCommEvent & EV_BREAK)		// 输入中发生中断
			{
				m_pOwner->SendMessage(gMsgSerialHardwardInfo, m_nPortNumber, WM_COMM_BREAK_DETECTED);
			}
			if (dwCommEvent & EV_ERR)		// 发生线路状态错误，线路状态错误包括
			{
				m_pOwner->SendMessage(gMsgSerialHardwardInfo, m_nPortNumber, WM_COMM_ERR_DETECTED);
			}
			if (dwCommEvent & EV_RING)		// 检测到振铃指示
			{
				m_pOwner->SendMessage(gMsgSerialHardwardInfo, m_nPortNumber, WM_COMM_RING_DETECTED);
			}
			if (dwCommEvent & EV_RXFLAG)	// 接收到事件字符，并置于输入缓冲区中
			{
				m_pOwner->SendMessage(gMsgSerialHardwardInfo, m_nPortNumber, WM_COMM_RXFLAG_DETECTED);
			}
			break;

		case 2:	// Write envent
			_WriteChar();
			break;

		default:
			break;
		}
	}

	return 0;
}


void CSerialPort::_WriteChar(void)
{
	BOOL bWrite = FALSE;
	BOOL bResult = FALSE;

	DWORD dwBytesSent = 0;

	ResetEvent(m_hWriteEvent);

	m_csSync.Lock();

	m_OverLapped.Offset = 0;
	m_OverLapped.OffsetHigh = 0;

	// Clear buffer
	PurgeComm(m_hSerialPort,
		PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	bResult = WriteFile(m_hSerialPort,	// Handle to COMM Port
		m_pszWriteBuffer,				// Pointer to message buffer in calling finction
		m_dwWriteSize,					// Length of message to send
		&dwBytesSent,					// Where to store the number of bytes sent
		&m_OverLapped);					// Overlapped structure

	if (bResult)
	{
		bWrite = TRUE;
		m_csSync.Unlock();
	}
	else 
	{
		DWORD dwError = GetLastError();

		switch (dwError)
		{
		case ERROR_IO_PENDING:
			dwBytesSent = 0;
			bWrite = FALSE;
			break;

		default:
			{
				CMsgBox MsgBox(this);
				MsgBox.ShowMsg(_T("WriteFile() Eoror!"), _T("SerialPort"), MB_OK | MB_ICONERROR);
			}
			break;
		}
	} 

	if (!bWrite)
	{
		bWrite = TRUE;

		bResult = GetOverlappedResult(m_hSerialPort,
			&m_OverLapped,
			&dwBytesSent,
			TRUE);

		m_csSync.Unlock();

		if (!bResult) // Deal with the error code  
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("GetOverlappedResults() in WriteFile() Eoror!"), _T("SerialPort"), MB_OK | MB_ICONERROR);
		}	
	}

	if (dwBytesSent != m_dwWriteSize)
	{
		TRACE(_T("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n"), 
			dwBytesSent, strlen((char *)m_pszWriteBuffer));
	}

	m_bSendFinish = TRUE;
}


void CSerialPort::_ReceiveChar(COMSTAT Comstat)
{
	BOOL bRead = TRUE; 
	BOOL bResult = TRUE;
	DWORD dwError = 0;
	DWORD dwBytesRead = 0;

#ifdef UNICODE
	unsigned short RXBuff = 0;
#else
	char RXBuff = 0;
#endif // UNICODE

	while (TRUE)
	{
		// 防止死锁
		if(WAIT_OBJECT_0 == WaitForSingleObject(m_hShutdownEvent, 0))
		{
			return;
		}
		
		m_csSync.Lock();

		// ClearCommError() will update the COMSTAT structure and
		// clear any other errors.

		bResult = ClearCommError(m_hSerialPort, &dwError, &Comstat);

		m_csSync.Unlock();

		if (!Comstat.cbInQue)
		{
			// break out when all bytes have been read
			break;
		}

		m_csSync.Lock();

		if (bRead)
		{
			bResult = ReadFile(m_hSerialPort,		// Handle to COM port 
				&RXBuff,							// RX Buffer Pointer
				1,									// Read one byte
				&dwBytesRead,						// Stores number of bytes read
				&m_OverLapped);						// pointer to the m_OverLapped structure

			// Deal with the error code
			if (bResult)
			{
				// ReadFile() returned complete. It is not necessary to call GetOverlappedResults()
				bRead = TRUE;
			}
			else
			{
				dwError = GetLastError();

				switch (dwError) 
				{ 
				case ERROR_IO_PENDING:
					// Asynchronous i/o is still in progress 
					// Proceed on to GetOverlappedResults();
					bRead = FALSE;
					break;

				default:
					// All other error codes
					{
						CMsgBox MsgBox(this);
						MsgBox.ShowMsg(_T("ReadFile() Eoror!"), _T("SerialPort"), MB_OK | MB_ICONERROR);
					}
					break;
				}
			}
		}

		if (!bRead)
		{
			bRead = TRUE;

			bResult = GetOverlappedResult(m_hSerialPort,	    // Handle to COMM port 
				&m_OverLapped,					// Overlapped structure
				&dwBytesRead,					// Stores number of bytes read
				TRUE); 							// Wait flag

			// Deal with the error code 
			if (!bResult)  
			{
				CMsgBox MsgBox(this);
				MsgBox.ShowMsg(_T("GetOverlappedResults() in ReadFile() Eoror!"), _T("SerialPort"), MB_OK | MB_ICONERROR);
			}	
		}  // Close if (!bRead)

		m_csSync.Unlock();

		// Notify parent that a byte was received

		PostMessage(gMsgSerialReceiveChar, m_nPortNumber, (LPARAM)RXBuff);
		m_pOwner->PostMessage(gMsgSerialReceiveChar, m_nPortNumber, (LPARAM)RXBuff);
	}
}


afx_msg LRESULT CSerialPort::OnGmsgserialreceivechar(WPARAM wParam, LPARAM lParam)
{
	if (FALSE == IsWindowVisible())
	{
		return 0;
	}

	const unsigned short cReceive = (unsigned short)lParam;	

	m_strRevData.Insert(m_strRevData.GetLength(), cReceive);
	m_vRevShow.push_back(cReceive);

	CString strShow;
	CString strRev;

	const int nSize = m_vRevShow.size();

	for (int i = 0; i < nSize; i++)
	{
		if (COM_DATA_DEC_MODE == m_nRevMode)
		{
			strRev.Format(_T("%d"), m_vRevShow[i]);
		}
		else
		{
			strRev.Format(_T("%.2x"), m_vRevShow[i]);
		}

		strShow += strRev;
		strShow += _T(" ");
	}

	int nLen = 0;

	switch (m_nRevMode)
	{
	case COM_DATA_ASCII_MODE:
		nLen = m_strRevData.GetLength();

		if (nLen > 110)
		{
			m_strRevData.Delete(0, 10);
		}

		((CBL_Button *)(GetDlgItem(IDC_BT_REV_SHOW)))->SetCaption(m_strRevData);
		break;

	case COM_DATA_DEC_MODE:
	case COM_DATA_HEX_MODE:
		if (nSize > 50)
		{
			m_vRevShow.erase(m_vRevShow.begin());
		}

		strShow.MakeUpper();

		((CBL_Button *)(GetDlgItem(IDC_BT_REV_SHOW)))->SetCaption(strShow);
		break;

	default:
		break;
	}

	return 0;
}


afx_msg LRESULT CSerialPort::OnDnPortSet(WPARAM wParam, LPARAM lParam)
{
	if (2 != wParam)
	{
		return 0;
	}

	int i = 0;
	m_nPortNumber = ((CBL_DropDown *)(GetDlgItem(IDC_DN_COM_PORT + i)))->GetCurSelect();

	i++;
	m_nBaudRate = _ttoi(((CBL_DropDown *)(GetDlgItem(IDC_DN_COM_PORT + i)))->GetValueText());

	i++;
	m_nDataBits = _ttoi(((CBL_DropDown *)(GetDlgItem(IDC_DN_COM_PORT + i)))->GetValueText());

	i++;
	m_nStopBits = _ttoi(((CBL_DropDown *)(GetDlgItem(IDC_DN_COM_PORT + i)))->GetValueText());

	i++;
	m_nCheckMode = ((CBL_DropDown *)(GetDlgItem(IDC_DN_COM_PORT + i)))->GetCurSelect();

	if (m_nPortNumber)
	{
		Init(m_nPortNumber);
	}
	else
	{
		ClosePort();
		m_editStatus.SetValueText(_T("关闭"));
	}

	LockCtrls(FALSE);

	return 0;
}


afx_msg LRESULT CSerialPort::OnRadRevMode(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < COM_REV_DATA_SHOW_MODE; i++)
	{
		CBL_Radio *pRadio = (CBL_Radio *)GetDlgItem(IDC_RD_RECEIVE_ASCII + i);

		if (pRadio->IsMsgSrc())
		{
			m_nRevMode = i;
		}
		else
		{
			pRadio->SetSelect(FALSE);
		}
	}

	if (COM_DATA_ASCII_MODE == m_nRevMode)
	{
		((CBL_Button *)(GetDlgItem(IDC_BT_REV_SHOW)))->SetCaption(m_strRevData);
	}
	else
	{
		CString strShow;
		CString strRev;

		const int nSize = m_vRevShow.size();

		for (int i = 0; i < nSize; i++)
		{
			if (COM_DATA_DEC_MODE == m_nRevMode)
			{
				strRev.Format(_T("%.2d "), m_vRevShow[i]);
			}
			else
			{
				strRev.Format(_T("%.2x "), m_vRevShow[i]);
			}

			strShow.Append(strRev);
		}

		((CBL_Button *)(GetDlgItem(IDC_BT_REV_SHOW)))->SetCaption(strShow);
	}

	return 0;
}


afx_msg LRESULT CSerialPort::OnRadSendMode(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < COM_SEND_DATA_MODE; i++)
	{
		CBL_Radio *pRadio = (CBL_Radio *)GetDlgItem(IDC_RD_SEND_ASCII + i);

		if (pRadio->IsMsgSrc())
		{
			m_nSendMode = i;
		}
		else
		{
			pRadio->SetSelect(FALSE);
		}
	}

	return 0;
}


void CSerialPort::LBtClickedBtClearReceive(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	m_vRevShow.clear();
	m_strRevData.Empty();

	((CBL_Button *)(GetDlgItem(IDC_BT_REV_SHOW)))->SetCaption(m_strRevData);
}


void CSerialPort::LBtClickedBtSendData(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CBL_DropDown *pDropDown = (CBL_DropDown *)GetDlgItem(IDC_DN_SEND_DATA);

	const CString &strData = pDropDown->GetValueText();

	Write2Port(strData, m_nSendMode);

	pDropDown->InsertItem(0, strData, strData);

	if (pDropDown->GetItemCount() > 10)
	{
		pDropDown->DeleteByPos(10);
	}
}


void CSerialPort::TextChangedDnSendData(LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	const CString strData = strNew;
	GetDlgItem(IDC_BT_SEND_DATA)->EnableWindow(!strData.IsEmpty() && m_bOpen);
}


void CSerialPort::SelectChangedDnSendData(LPCTSTR strOld, LPCTSTR strNew, short nPos)
{
	// TODO: 在此处添加消息处理程序代码
	GetDlgItem(IDC_BT_SEND_DATA)->EnableWindow(m_bOpen);
}


void CSerialPort::LBtClickedBtComOk(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	for (int i = 0; i < COM_PORT_DATA_SUM; i++)
	{
		if (m_nSetData[i] != m_nSetDataBkup[i])
		{
			_FileDirty(TRUE);
			break;
		}
	}

	m_vRevShow.clear();
	m_strRevData.Empty();

	OnOK();
}


void CSerialPort::LBtClickedBtComCancel(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	OnCancel();
}
