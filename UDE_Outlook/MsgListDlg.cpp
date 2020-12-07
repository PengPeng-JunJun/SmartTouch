// MsgListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "MsgListDlg.h"
#include "afxdialogex.h"


// CMsgListDlg �Ի���

IMPLEMENT_DYNAMIC(CMsgListDlg, CTpLayerWnd)

CMsgListDlg::CMsgListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CMsgListDlg::IDD, pParent)
{

}

CMsgListDlg::CMsgListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)

{
	
}


CMsgListDlg::~CMsgListDlg()
{
}

void CMsgListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_MsgList, m_BL_MsgList);
}

void CMsgListDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);

}

BEGIN_MESSAGE_MAP(CMsgListDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CMsgListDlg ��Ϣ�������


BOOL CMsgListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTitle(_T("��Ϣ�б�"));
	m_BL_MsgList.ResetRows(m_BL_MsgList.GetRows(), TRUE);
	m_BL_MsgList.AppendColumn(_T("��̖"),DT_CENTER,50,FALSE);
	m_BL_MsgList.AppendColumn(_T("�Ĵ�����"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("������ַ"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("����λ��"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("�������Q"),DT_CENTER,150,FALSE);
	m_BL_MsgList.AppendColumn(_T("���rֵ"),DT_CENTER,110,FALSE);
	m_BL_MsgList.AppendColumn(_T("�@ʾ��B"),DT_CENTER,90,FALSE);
	m_BL_MsgList.AppendColumn(_T("�Ƿ��i��"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("�^������"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("�Ƿ�����"),DT_CENTER,100,FALSE);
	m_BL_MsgList.AppendColumn(_T("����ֵ"),DT_CENTER,100,FALSE);

// 	m_BL_MsgList.AppendColumn(_T(""),DT_CENTER,100,FALSE);
	 
	 
	for (int nCounter = 0; nCounter < m_BL_MsgList.GetColumns(); nCounter++)//�޸ı�ͷ���ָ�ʽ
	{
	 	m_BL_MsgList.SetHeaderFont(nCounter, _T("Tahoma"), 150);
	}
	 
	m_BL_MsgList.SetReadOnly(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BEGIN_EVENTSINK_MAP(CMsgListDlg, CTpLayerWnd)
	ON_EVENT(CMsgListDlg, IDC_BL_MsgList, 1, CMsgListDlg::RowsChangedBlMsglist, VTS_I4 VTS_I4 VTS_BOOL)
END_EVENTSINK_MAP()


void CMsgListDlg::RowsChangedBlMsglist(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: �ڴ˴������Ϣ����������
	for (int i = 0; i < nNewRows; i++)
	{
		m_BL_MsgList.SetItemText(i, 9, _T("0"));
	}
	
}
