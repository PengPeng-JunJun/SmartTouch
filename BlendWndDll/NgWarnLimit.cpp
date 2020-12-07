// NgWarnLimit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NgWarnLimit.h"
#include "afxdialogex.h"


// CNgWarnLimit �Ի���

IMPLEMENT_DYNAMIC(CNgWarnLimit, CTpLayerWnd)

CNgWarnLimit::CNgWarnLimit(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CNgWarnLimit::IDD, pParent)
	, m_bUseNum(FALSE)
	, m_bUseRate(TRUE)
	, m_nNgLimit(0)
	, m_dNgRateLimit(5)
{

}

CNgWarnLimit::CNgWarnLimit(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_bUseNum(FALSE)
	, m_bUseRate(TRUE)
	, m_nNgLimit(0)
	, m_dNgRateLimit(5)
{
}


CNgWarnLimit::~CNgWarnLimit()
{
}

void CNgWarnLimit::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNgWarnLimit, CTpLayerWnd)
END_MESSAGE_MAP()


// CNgWarnLimit ��Ϣ�������


BOOL CNgWarnLimit::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	_UpdateUi();
	LockCtrls(APP_LOCK_AUTO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CNgWarnLimit::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_bUseNum = ((CBL_CheckBox *)(GetDlgItem(IDC_CHECK_STATISTIC_NUM)))->GetStatus();
	m_bUseRate = ((CBL_CheckBox *)(GetDlgItem(IDC_CHECK_STATISTIC_RATE)))->GetStatus();

	m_nNgLimit = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_NG_WARN_NUM)))->GetIntValue();
	m_dNgRateLimit = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_NG_WARN_RATE)))->GetDoubleValue();

	CTpLayerWnd::OnOK();
}


void CNgWarnLimit::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_QC);
	const BOOL bEnable = !bLocked;

	GetDlgItem(IDC_CHECK_STATISTIC_NUM)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_STATISTIC_RATE)->EnableWindow(bEnable);

	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NG_WARN_NUM)))->SetReadOnly(bLocked);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NG_WARN_RATE)))->SetReadOnly(bLocked);

	m_BtBaseOk.EnableWindow(bEnable);
}


void CNgWarnLimit::_UpdateUi(void)
{
	((CBL_CheckBox *)(GetDlgItem(IDC_CHECK_STATISTIC_NUM)))->SetStatus(m_bUseNum);
	((CBL_CheckBox *)(GetDlgItem(IDC_CHECK_STATISTIC_RATE)))->SetStatus(m_bUseRate);

	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NG_WARN_NUM)))->SetValue(m_nNgLimit);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_NG_WARN_RATE)))->SetValue(m_dNgRateLimit);
}
