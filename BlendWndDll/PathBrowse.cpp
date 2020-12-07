// PathBrowse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PathBrowse.h"
#include "afxdialogex.h"


// CPathBrowse �Ի���

IMPLEMENT_DYNAMIC(CPathBrowse, CTpLayerWnd)

CPathBrowse::CPathBrowse(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CPathBrowse::IDD, pParent)
{

}

CPathBrowse::CPathBrowse(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{
}

CPathBrowse::~CPathBrowse()
{
}

void CPathBrowse::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPathBrowse, CTpLayerWnd)
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CPathBrowse, CTpLayerWnd)
	ON_EVENT(CPathBrowse, IDC_BT_PATH_BROSE_GO, 1, CPathBrowse::LBtClickedBtPathBroseGo, VTS_I4)
END_EVENTSINK_MAP()

// CPathBrowse ��Ϣ�������


BOOL CPathBrowse::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_strPathBkup = m_strFilePath;
	
	_UpdateUi();
	LockCtrls(APP_LOCK_AUTO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPathBrowse::OnOK()
{
	m_strFilePath = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_PATH_BROSE)))->GetValueText();

	if (m_strFilePath.IsEmpty())
	{
		CMsgBox MsgBox(this);
		MsgBox.ShowMsg(_T("·������Ϊ�գ����������á�"), _T("·������"), MB_OK | MB_ICONASTERISK);

		return;
	}

	if (m_strPathBkup != m_strFilePath)
	{
		_FileDirty(TRUE);
	}

	CTpLayerWnd::OnOK();
}


void CPathBrowse::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_strFilePath = m_strPathBkup;

	CTpLayerWnd::OnCancel();
}


void CPathBrowse::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_TE);
	const BOOL bEnable = !bLocked;

	((CBL_Edit *)(GetDlgItem(IDC_EDIT_PATH_BROSE)))->SetReadOnly(bLocked);
	GetDlgItem(IDC_BT_PATH_BROSE_GO)->EnableWindow(bEnable);
	
	m_BtBaseOk.EnableWindow(bEnable);
}


void CPathBrowse::_UpdateUi(void)
{
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_PATH_BROSE)))->SetValueText(m_strFilePath);
}


void CPathBrowse::LBtClickedBtPathBroseGo(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CFolderPickerDialog Dlg;

	if (IDOK == Dlg.DoModal())
	{
		m_strFilePath = Dlg.GetFolderPath();

		_UpdateUi();
	}
}
