// DiameterTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "DiameterTestDlg.h"
#include "afxdialogex.h"


// CDiameterTestDlg �Ի���

IMPLEMENT_DYNAMIC(CDiameterTestDlg, CTpLayerWnd)

CDiameterTestDlg::CDiameterTestDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CDiameterTestDlg::IDD, pParent)
{

}

CDiameterTestDlg::CDiameterTestDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CDiameterTestDlg::~CDiameterTestDlg()
{
}

void CDiameterTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDiameterTestDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CDiameterTestDlg ��Ϣ�������


BOOL CDiameterTestDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDiameterTestDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
