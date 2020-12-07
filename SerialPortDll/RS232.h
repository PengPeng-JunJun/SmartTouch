#pragma once

#include "SerialPort.h"

class AFX_EXT_CLASS CRS232
{
public:
	CRS232(void);
	~CRS232(void);

	void CreateBlendWnd(CWnd * pParent);
	INT_PTR CreateTopWnd(BOOL bModal, BOOL bShowNow = TRUE);
	void ShowParamWnd(int nShow);

	BOOL Init(int nPort);
	BOOL IsOpen(void);
	BOOL ClosePort(void);
	int GetPortNum(void);

	void LockStatus(BOOL bLock);
	CTpLayerWnd * GetTpLayer(void);

	BOOL Write2Port(const BYTE byData);
	BOOL Write2Port(const CString & strData, int nSendMode);
	BOOL Write2Port(const BYTE *pData, int nLength);
	BOOL Write2Port(const vector<BYTE> * pvSend);

	void Serialize(CArchive& ar);
protected:
	CBlender<CSerialPort> m_Port;
};

