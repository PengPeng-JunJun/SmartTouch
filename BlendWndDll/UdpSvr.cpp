// UdpSvr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UdpSvr.h"
#include "AppNetSeriver.h"

// CUdpSvr

CUdpSvr::CUdpSvr()
	: m_pOwner(nullptr)
{
}

CUdpSvr::~CUdpSvr()
{
	if (nullptr != m_pOwner)
	{
		((CAppNetSeriver *)m_pOwner)->RemoveClient(this);
	}
}


// CUdpSvr ��Ա����


void CUdpSvr::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CAppNetSeriver *)m_pOwner)->AddClient();

	CSocket::OnAccept(nErrorCode);
}


void CUdpSvr::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CAppNetSeriver *)m_pOwner)->ReceiveData(this);

	CSocket::OnReceive(nErrorCode);
}


void CUdpSvr::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	((CAppNetSeriver *)m_pOwner)->RemoveClient(this);

	CSocket::OnClose(nErrorCode);
}
