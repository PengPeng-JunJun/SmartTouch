// AngleTestListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "AngleTestListDlg.h"
#include "afxdialogex.h"


// CAngleTestListDlg �Ի���

IMPLEMENT_DYNAMIC(CAngleTestListDlg, CTpLayerWnd)

CAngleTestListDlg::CAngleTestListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CAngleTestListDlg::IDD, pParent)
{

}

CAngleTestListDlg::CAngleTestListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CAngleTestListDlg::~CAngleTestListDlg()
{
}

void CAngleTestListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAngleTestListDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CAngleTestListDlg ��Ϣ�������


BOOL CAngleTestListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAngleTestListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
	}
	else
	{	// loading code
	}
}
