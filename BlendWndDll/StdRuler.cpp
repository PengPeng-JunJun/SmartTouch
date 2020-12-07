// StdRadius.cpp : 实现文件
//

#include "stdafx.h"
#include "StdRuler.h"
#include "afxdialogex.h"


// CStdRuler 对话框

IMPLEMENT_SERIAL(CStdRuler, CTpLayerWnd, 1 | VERSIONABLE_SCHEMA);

CStdRuler::CStdRuler(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CStdRuler::IDD, pParent)
	, m_dStdDist(30)
	, m_dStdDiameter(15)
	, m_dStdDistBkup(30)
	, m_dStdDiameterBkup(15)
{

}

CStdRuler::CStdRuler(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_dStdDist(30)
	, m_dStdDiameter(15)
	, m_dStdDistBkup(30)
	, m_dStdDiameterBkup(15)
{
}

CStdRuler::~CStdRuler()
{
}

void CStdRuler::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStdRuler, CTpLayerWnd)
END_MESSAGE_MAP()


// CStdRuler 消息处理程序


BOOL CStdRuler::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_dStdDistBkup = m_dStdDist;
	m_dStdDiameterBkup = m_dStdDiameter;

	_UpdateUi();
	LockCtrls(APP_LOCK_AUTO);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CStdRuler::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_dStdDist = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_STD_DIST)))->GetDoubleValue();
	m_dStdDiameter = ((CBL_Edit *)(GetDlgItem(IDC_EDIT_STD_DIAMETER)))->GetDoubleValue();

	if ((m_dStdDistBkup != m_dStdDist) ||
		(m_dStdDiameterBkup != m_dStdDiameter))
	{
		_FileDirty(TRUE);
	}

	CTpLayerWnd::OnOK();
}


void CStdRuler::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_dStdDist = m_dStdDistBkup;
	m_dStdDiameter = m_dStdDiameterBkup;

	CTpLayerWnd::OnCancel();
}


void CStdRuler::Serialize(CArchive& ar)
{
	ar.SerializeClass(RUNTIME_CLASS(CStdRuler));

	if (ar.IsStoring())
	{	// storing code
		ar << m_dStdDist;
		ar << m_dStdDiameter;
	}
	else
	{	// loading code
		const UINT nSchema = ar.GetObjectSchema();

		switch (nSchema)
		{
		case 1:
			ar >> m_dStdDist;
			ar >> m_dStdDiameter;

			break;

		default:
			break;
		}
	}
}


void CStdRuler::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_TE);
	const BOOL bEanble = !bLocked;

	((CBL_Edit *)(GetDlgItem(IDC_EDIT_STD_DIST)))->SetReadOnly(bLocked);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_STD_DIAMETER)))->SetReadOnly(bLocked);

	m_BtBaseOk.EnableWindow(bEanble);
}


void CStdRuler::_DefaultFocus(void)
{
	GetDlgItem(IDC_EDIT_STD_DIST)->SetFocus();
}


void CStdRuler::_UpdateUi(void)
{
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_STD_DIST)))->SetValue(m_dStdDist);
	((CBL_Edit *)(GetDlgItem(IDC_EDIT_STD_DIAMETER)))->SetValue(m_dStdDiameter);
}
