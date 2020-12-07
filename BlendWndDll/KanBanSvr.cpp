// KanBanSvr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KanBanSvr.h"
#include "afxdialogex.h"

// CKanBanSvr �Ի���

IMPLEMENT_SERIAL(CKanBanSvr, CTpLayerWnd, 1 | VERSIONABLE_SCHEMA);

CKanBanSvr::CKanBanSvr(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CKanBanSvr::IDD, pParent)
	, m_nPort(NET_KANBAN_DEFAULT_PORT)
	, m_nPortBkup(NET_KANBAN_DEFAULT_PORT)
{

}

CKanBanSvr::CKanBanSvr(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nPort(NET_KANBAN_DEFAULT_PORT)
	, m_nPortBkup(NET_KANBAN_DEFAULT_PORT)
{
}

CKanBanSvr::~CKanBanSvr()
{
}

void CKanBanSvr::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CKanBanSvr, CTpLayerWnd)
END_MESSAGE_MAP()


// CKanBanSvr ��Ϣ�������


BOOL CKanBanSvr::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_strIp.IsEmpty())
	{
		LoadDefaultIpPortFix();
	}

	m_strIpBkup = m_strIp;
	m_nPortBkup = m_nPort;
	m_strStartFixBkup = m_strStartFix;
	m_strEndFixBkup = m_strEndFix;

	_UpdateUi();
	LockCtrls(APP_LOCK_AUTO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CKanBanSvr::Serialize(CArchive& ar)
{
	ar.SerializeClass(RUNTIME_CLASS(CKanBanSvr));

	if (ar.IsStoring())
	{	// storing code
		ar << m_strIp;
		ar << m_nPort;
		ar << m_strStartFix;
		ar << m_strEndFix;
	}
	else
	{	// loading code
		const UINT nSchema = ar.GetObjectSchema();

		switch (nSchema)
		{
		case 1:
			ar >> m_strIp;
			ar >> m_nPort;
			ar >> m_strStartFix;
			ar >> m_strEndFix;
			break;

		default:
			break;
		}
	}
}


void CKanBanSvr::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_strIp			= ((CBL_IpAdd *)(GetDlgItem(IDC_IP_KANBAN_SVR)))->GetIpAdd();
	m_nPort			= ((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_PORT)))->GetIntValue();
	m_strStartFix	= ((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_START)))->GetValueText();
	m_strEndFix		= ((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_END)))->GetValueText();

	if (m_strIpBkup		!= m_strIp ||
		m_nPortBkup		!= m_nPort ||
		m_strStartFix	!= m_strStartFix ||
		m_strEndFix		!= m_strEndFix)
	{
		_FileDirty(TRUE);
	}

	SaveDefaultIpPortFix();

	CTpLayerWnd::OnOK();
}


void CKanBanSvr::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_strIp			= m_strIpBkup;
	m_nPort			= m_nPortBkup;
	m_strStartFix	= m_strStartFixBkup;
	m_strEndFix		= m_strEndFixBkup;

	CTpLayerWnd::OnCancel();
}


void CKanBanSvr::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_TE);
	const BOOL bEnable = !bLocked;

	((CBL_IpAdd *)(GetDlgItem(IDC_IP_KANBAN_SVR)))->SetReadOnly(bLocked);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_PORT)))->SetReadOnly(bLocked);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_START)))->SetReadOnly(bLocked);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_END)))->SetReadOnly(bLocked);

	m_BtBaseOk.EnableWindow(bEnable);
}


void CKanBanSvr::LoadDefaultIpPortFix(void)
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 
	strPath.Replace(_T(".exe"), _T(".ini"));

	const CString strItem = _T("Kanban Default IpAdd");

	GetPrivateProfileString(strItem, _T("IpAdd"), _T(""),
		m_strIp.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);

	m_strIp.ReleaseBuffer();
	m_strIpBkup = m_strIp;

	m_nPort = GetPrivateProfileInt(strItem, _T("Port"), NET_KANBAN_DEFAULT_PORT, strPath);
	m_nPortBkup = m_nPort;

	GetPrivateProfileString(strItem, _T("StartFix"), _T(""),
		m_strStartFix.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);

	m_strStartFix.ReleaseBuffer();
	m_strStartFixBkup = m_strStartFix;

	GetPrivateProfileString(strItem, _T("EndFix"), _T(""),
		m_strEndFix.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);

	m_strEndFix.ReleaseBuffer();
	m_strEndFixBkup = m_strEndFix;
}


void CKanBanSvr::SaveDefaultIpPortFix(void)
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 
	strPath.Replace(_T(".exe"), _T(".ini"));

	const CString strItem = _T("Kanban Default IpAdd");

	WritePrivateProfileString(strItem, _T("IpAdd"), m_strIp, strPath);

	CString strValue;
	strValue.Format(_T("%d"), m_nPort);
	WritePrivateProfileString(strItem, _T("Port"), strValue, strPath);

	WritePrivateProfileString(strItem, _T("StartFix"), m_strStartFix, strPath);
	WritePrivateProfileString(strItem, _T("EndFix"), m_strEndFix, strPath);
}


void CKanBanSvr::_UpdateUi(void)
{
	((CBL_IpAdd *)(GetDlgItem(IDC_IP_KANBAN_SVR)))->SetIpAdd(m_strIp);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_PORT)))->SetValue(m_nPort);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_START)))->SetValueText(m_strStartFix);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_KANBAN_END)))->SetValueText(m_strEndFix);
}
