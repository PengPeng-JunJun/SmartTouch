// AboutInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AboutInfo.h"
#include "afxdialogex.h"


// CAboutInfo �Ի���

IMPLEMENT_DYNAMIC(CAboutInfo, CTpLayerWnd)

CAboutInfo::CAboutInfo(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CAboutInfo::IDD, pParent)
{

}

CAboutInfo::CAboutInfo(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CAboutInfo::~CAboutInfo()
{
}

void CAboutInfo::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutInfo, CTpLayerWnd)
END_MESSAGE_MAP()

// CAboutInfo ��Ϣ�������


BOOL CAboutInfo::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BtBaseCancel.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
