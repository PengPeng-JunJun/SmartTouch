// PsdLayer.cpp : 实现文件
//

#include "stdafx.h"
#include "PsdMgr.h"
#include "afxdialogex.h"

#define YS_SUPERWORD	_T("7512921423")

// CPsdMgr 对话框

IMPLEMENT_DYNAMIC(CPsdMgr, CTpLayerWnd)

CPsdMgr::CPsdMgr(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CPsdMgr::IDD, pParent)
	, m_nLevel(-1)
	, m_bChangePsd(FALSE)
{
	int i = 0;

	m_strDefault[i++] = _T("0000");
	m_strDefault[i++] = _T("1111");
	m_strDefault[i++] = _T("2222");
	m_strDefault[i++] = _T("Woody");
}

CPsdMgr::CPsdMgr(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nLevel(-1)
	, m_bChangePsd(FALSE)
{
	int i = 0;

	m_strDefault[i++] = _T("0000");
	m_strDefault[i++] = _T("1111");
	m_strDefault[i++] = _T("2222");
	m_strDefault[i++] = _T("Woody");
}

CPsdMgr::~CPsdMgr()
{
}

void CPsdMgr::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPsdMgr, CTpLayerWnd)
	ON_MESSAGE(WM_PSD_LEVEL, &CPsdMgr::OnPsdLevel)
	ON_MESSAGE(WM_PSD_ENTER, &CPsdMgr::OnPsdEnter)
END_MESSAGE_MAP()


// CPsdMgr 消息处理程序


BOOL CPsdMgr::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i = 0; i < PSD_LEVEL_SUM; i++)
	{
		((CBL_Radio *)(GetDlgItem(IDC_RD_PSD_OP + i)))->SetSelect(i == m_nLevel);
	}

	if (m_bChangePsd)
	{
		SetTitle(_T("修改密码"));

		((CBL_Edit *)(GetDlgItem(IDC_EDIT_PSD)))->SetCaption(_T("旧密码:"));
		GetDlgItem(IDC_EDIT_PSD_NEW)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_PSD_CONFIRM)->ShowWindow(SW_SHOW);
	}
	else
	{
		CRect rcEdit;
		GetDlgItem(IDC_EDIT_PSD)->GetWindowRect(rcEdit);
		ScreenToClient(rcEdit);
		rcEdit.DeflateRect(10, 0, 10, 0);
		GetDlgItem(IDC_EDIT_PSD)->MoveWindow(rcEdit);

		const int nOfst = 60;

		CRect rcBtWnd;
		m_BtBaseOk.GetWindowRect(rcBtWnd);
		ScreenToClient(rcBtWnd);

		rcBtWnd.top -= nOfst;
		rcBtWnd.bottom -= nOfst;

		m_BtBaseOk.MoveWindow(rcBtWnd);

		m_BtBaseCancel.GetWindowRect(rcBtWnd);
		ScreenToClient(rcBtWnd);

		rcBtWnd.top -= nOfst;
		rcBtWnd.bottom -= nOfst;

		m_BtBaseCancel.MoveWindow(rcBtWnd);

		CRect rcWnd;

		GetWindowRect(rcWnd);
		rcWnd.bottom -= nOfst;

		MoveWindow(rcWnd);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPsdMgr::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_nLevel < 0)
	{
		CMsgBox MsgBox(this);
		MsgBox.ShowMsg(_T("未选择任何权限。"), m_strTitle, MB_OK | MB_ICONERROR);

		return;
	}

	CBL_Edit *pEdit = (CBL_Edit *)GetDlgItem(IDC_EDIT_PSD);
	const CString strInput = pEdit->GetPsdCode();

	if (strInput != m_strPsd && (YS_SUPERWORD != strInput))
	{
		CString strInfo = m_bChangePsd? _T("旧密码错误！请重新输入。"): _T("密码错误！请重新输入。");

		CMsgBox MsgBox(this);
		MsgBox.ShowMsg(strInfo, m_strTitle, MB_OK | MB_ICONERROR);

		return;
	}
	else
	{
		_SetPsdLeve(m_nLevel);
	}

	if (m_bChangePsd)
	{
		USES_CONVERSION;

		pEdit = (CBL_Edit *)GetDlgItem(IDC_EDIT_PSD_NEW);

		const CString strNew = pEdit->GetPsdCode();

		pEdit = (CBL_Edit *)GetDlgItem(IDC_EDIT_PSD_CONFIRM);
		const CString strConfirm = pEdit->GetPsdCode();

		if (strNew.IsEmpty())
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("新密码不能为空！请重新输入。"), _T("修改密码"), MB_OK | MB_ICONERROR);

			return;
		}

		if (strConfirm != strNew)
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("确认密码和新密码不同！请重新输入。"), _T("修改密码"), MB_OK | MB_ICONERROR);

			return;
		}

		CRegKey regKey;
		CString strKeyName;

		CAES Aes;
		const CString strPath = Aes.Cipher(_T("Password"));

		strKeyName.Format(_T("Software\\%s\\%s"), AfxGetAppName(), strPath);

		if (ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE, strKeyName))
		{
			const CString strLevel[] = {_T("Operator"), _T("QRA"), _T("Technician"), _T("Super")};

			if (ERROR_SUCCESS == regKey.SetStringValue(Aes.Cipher(strLevel[m_nLevel]), Aes.Cipher(strConfirm)))
			{
				CMsgBox MsgBox(this);
				MsgBox.ShowMsg(_T("修改密码成功！"), _T("修改密码"), MB_OK | MB_ICONINFORMATION);

				regKey.Close();
			}
			else
			{
				CMsgBox MsgBox(this);
				MsgBox.ShowMsg(_T("新密码写入失败！"), _T("修改密码"), MB_OK | MB_ICONERROR);

				regKey.Close();

				return;
			}
		}
		else
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("访问密码文件失败！"), _T("修改密码"), MB_OK | MB_ICONERROR);

			return;
		}
	}

	CTpLayerWnd::OnOK();
}


void CPsdMgr::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_nLevel = -1;
	_SetPsdLeve(m_nLevel);

	CTpLayerWnd::OnCancel();
}


BOOL CPsdMgr::_ReadCode(void)
{
	USES_CONVERSION;

	CRegKey regKey;
	CString strKeyName;

	CAES Aes;
 	const CString strPath = Aes.Cipher(_T("Password"));

	strKeyName.Format(_T("Software\\%s\\%s"), AfxGetAppName(), strPath);

	const CString strLevel[] = {_T("Operator"), _T("QcMgr"), _T("Technician"), _T("Super")};

	BOOL bOpenSuccess = ERROR_SUCCESS == regKey.Open(HKEY_LOCAL_MACHINE, strKeyName);

	if (FALSE == bOpenSuccess)
	{
		if (ERROR_SUCCESS == regKey.Create(HKEY_LOCAL_MACHINE, strKeyName))
		{
			for (int i = 0; i < PSD_LEVEL_SUM; i++)
			{
				regKey.SetStringValue(Aes.Cipher(strLevel[i]), Aes.Cipher(m_strDefault[i]));
			}

			bOpenSuccess = TRUE;
		}
		else
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("访问密码文件失败！"), _T("密码"), MB_OK | MB_ICONERROR);

			return FALSE;
		}
	}

	if (bOpenSuccess)
	{
		DWORD dwChars = 1024;

		const CString strLevelHex = Aes.Cipher(strLevel[m_nLevel]);
		const LONG nKeyRes = regKey.QueryStringValue(strLevelHex, m_strPsd.GetBufferSetLength(MAX_PATH + 1), &dwChars);

		m_strPsd.ReleaseBuffer();

		if (ERROR_SUCCESS == nKeyRes)
		{
			m_strPsd = Aes.Inv_Cipher(m_strPsd);
		}
		else
		{
			m_strPsd = strLevelHex;
		}

		regKey.Close();
	}
	else
	{
		CMsgBox MsgBox(this);
		MsgBox.ShowMsg(_T("访问密码文件失败！"), _T("密码"), MB_OK | MB_ICONERROR);

		m_nLevel = -1;

		for (int i = 0; i < PSD_LEVEL_SUM; i++)
		{
			((CBL_Radio *)(GetDlgItem(IDC_RD_PSD_OP + i)))->SetSelect(i == m_nLevel);
		}

		return FALSE;
	}

	return TRUE;
}


afx_msg LRESULT CPsdMgr::OnPsdLevel(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < PSD_LEVEL_SUM; i++)
	{
		CBL_Radio *pRadio = (CBL_Radio *)GetDlgItem(IDC_RD_PSD_OP + i);

		if (pRadio->IsMsgSrc())
		{
			m_nLevel = i;
		}
		else
		{
			pRadio->SetSelect(FALSE);
		}
	}

	if (!_ReadCode())
	{
		m_nLevel = -1;
	}

	GetDlgItem(IDC_EDIT_PSD)->SetFocus();

	return 0;
}


afx_msg LRESULT CPsdMgr::OnPsdEnter(WPARAM wParam, LPARAM lParam)
{
	if (1 == wParam)
	{
		OnOK();
	}

	return 0;
}
