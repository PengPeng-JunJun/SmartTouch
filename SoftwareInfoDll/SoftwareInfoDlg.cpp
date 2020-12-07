// SoftwareInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SoftwareInfoDlg.h"
#include "afxdialogex.h"


// CSoftwareInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CSoftwareInfoDlg, CTpLayerWnd)

CSoftwareInfoDlg::CSoftwareInfoDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSoftwareInfoDlg::IDD, pParent)
{

}

CSoftwareInfoDlg::CSoftwareInfoDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}


CSoftwareInfoDlg::~CSoftwareInfoDlg()
{
}

void CSoftwareInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_btVersion, m_BL_btVersion);
}


BEGIN_MESSAGE_MAP(CSoftwareInfoDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CSoftwareInfoDlg ��Ϣ�������

void CSoftwareInfoDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}