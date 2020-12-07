#include "stdafx.h"
#include "RS232.h"


CRS232::CRS232(void)
{
}


CRS232::~CRS232(void)
{
}


void CRS232::CreateBlendWnd(CWnd * pParent)
{
	m_Port.CreateBlendWnd(IDD_SERIALPORT, pParent);
}


INT_PTR CRS232::CreateTopWnd(BOOL bModal, BOOL bShowNow/* = TRUE*/)
{
	return m_Port.CreateTopWnd(bModal, bShowNow);
}


void CRS232::ShowParamWnd(int nShow)
{
	m_Port->ShowWindow(nShow);
}


BOOL CRS232::Init(int nPort)
{
	return m_Port->Init(nPort);
}


BOOL CRS232::IsOpen(void)
{
	return m_Port->IsOpen();
}


BOOL CRS232::ClosePort(void)
{
	return m_Port->ClosePort();
}


int CRS232::GetPortNum(void)
{
	return m_Port->GetPortNumber();
}


void CRS232::LockStatus(BOOL bLock)
{
	m_Port->LockStatus(bLock);
}


CTpLayerWnd * CRS232::GetTpLayer(void)
{
	return m_Port.m_pTopWnd;
}


BOOL CRS232::Write2Port(const BYTE byData)
{
	return m_Port->Write2Port(byData);
}


BOOL CRS232::Write2Port(const CString & strData, int nSendMode)
{
	return m_Port->Write2Port(strData, nSendMode);
}


BOOL CRS232::Write2Port(const BYTE *pData, int nLength)
{
	return m_Port->Write2Port(pData, nLength);
}


BOOL CRS232::Write2Port(const vector<BYTE> * pvSend)
{
	size_t nSize = pvSend->size();

	BYTE *pData = new BYTE[nSize];

	for (size_t i = 0; i < nSize; i++)
	{
		pData[i] = pvSend->at(i);
	}

	return m_Port->Write2Port(pData, nSize);
}


void CRS232::Serialize(CArchive& ar)
{
	return m_Port->Serialize(ar);
}
