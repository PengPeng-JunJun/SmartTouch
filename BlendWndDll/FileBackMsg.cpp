// RemoteFileMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileBackMsg.h"
#include "afxdialogex.h"


// CFileBackMsg 对话框

IMPLEMENT_SERIAL(CFileBackMsg, CTpLayerWnd, 1 | VERSIONABLE_SCHEMA);

CFileBackMsg::CFileBackMsg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CFileBackMsg::IDD, pParent)
	, m_strOk(_T("OK"))
	, m_strNg(_T("NG"))
{

}

CFileBackMsg::CFileBackMsg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_strOk(_T("OK"))
	, m_strNg(_T("NG"))
{
}


CFileBackMsg::~CFileBackMsg()
{
}

void CFileBackMsg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileBackMsg, CTpLayerWnd)
END_MESSAGE_MAP()

// CFileBackMsg 消息处理程序


BOOL CFileBackMsg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_strOkBkup = m_strOk;
	m_strNgBkup = m_strNg;

	_UpdateUi();
	LockCtrls(APP_LOCK_AUTO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CFileBackMsg::Serialize(CArchive& ar)
{
	ar.SerializeClass(RUNTIME_CLASS(CFileBackMsg));

	if (ar.IsStoring())
	{	// storing code
		ar << m_strOk;
		ar << m_strNg;
	}
	else
	{	// loading code
		const UINT nSchema = ar.GetObjectSchema();

		CString strWnd;

		switch (nSchema)
		{
		case 1:
			ar >> m_strOk;
			ar >> m_strNg;
			break;

		default:
			break;
		}
	}
}


void CFileBackMsg::OnOK()
{
	if (m_strOk != m_strOkBkup ||
		m_strNg != m_strNgBkup)
	{
		_FileDirty(TRUE);
	}

	CTpLayerWnd::OnOK();
}


void CFileBackMsg::OnCancel()
{
	m_strOk = m_strOkBkup;
	m_strNg = m_strNgBkup;

	CTpLayerWnd::OnCancel();
}


void CFileBackMsg::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_TE);
	const BOOL bEnable = !bLocked;

	((CBL_Edit *)(GetDlgItem(IDC_EDIT_FILE_BACK_OK_MSG)))->SetReadOnly(bLocked);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_FILE_BACK_NG_MSG)))->SetReadOnly(bLocked);

	m_BtBaseOk.EnableWindow(bEnable);
}


void CFileBackMsg::_UpdateUi(void)
{
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_FILE_BACK_OK_MSG)))->SetValueText(m_strOk);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_FILE_BACK_NG_MSG)))->SetValueText(m_strNg);
}
