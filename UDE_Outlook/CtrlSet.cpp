// CtrlSet.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "CtrlSet.h"
#include "afxdialogex.h"

// CCtrlSet 对话框

IMPLEMENT_DYNAMIC(CCtrlSet, CTpLayerWnd)

CCtrlSet::CCtrlSet(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CCtrlSet::IDD, pParent)
	, m_nRelayBtFocus(-1)
	, m_nRelayCkFocus(-1)
	, m_nRelayDpFocus(-1)
	, m_bRelayBtStarStatus(FALSE)
	, m_bRelayBtStopStatus(FALSE)
	, m_bRelayBtResetStatus(FALSE)
	, m_bRelayBtErrorStatus(FALSE)
	, m_nBasicFocus(0)
	, m_bRelayBtPauseStatus(FALSE)
	, m_bRelaySwAutoStatus(FALSE)
	, m_bRelaySwUnAutoStatus(FALSE)
{
	m_vbRelayBtStatus.resize(BT_RELAY_SUM);
	m_vstrRelayBt.resize(BT_RELAY_SUM);
	m_vstrRelayBtName.resize(BT_RELAY_SUM);
	m_vnRelayBtMode.resize(BT_RELAY_SUM);
	m_vbIsRelayBtClickAuto.resize(BT_RELAY_SUM);
	for (size_t i = 0; i < BT_RELAY_SUM; i++)
	{
		m_vbRelayBtStatus[i] = FALSE;
		m_vstrRelayBt[i] = _T("");
		m_vstrRelayBtName[i] = _T("");
		m_vnRelayBtMode[i] = 0;
		m_vbIsRelayBtClickAuto[i] = FALSE;
	}

	m_vbRelayCkStatus.resize(CK_RELAY_SUM);
	m_vstrRelayCk.resize(CK_RELAY_SUM);
	m_vstrRelayCkName.resize(CK_RELAY_SUM);
	for (size_t i = 0; i < CK_RELAY_SUM; i++)
	{
		m_vbRelayCkStatus[i] = FALSE;
		m_vstrRelayCk[i] = _T("");
		m_vstrRelayCkName[i] = _T("");
	}

	m_vbRelayDpStatus.resize(DP_RELAY_SUM);
	m_vstrRelayDp.resize(DP_RELAY_SUM);
	m_vstrRelayDpName.resize(DP_RELAY_SUM);
	m_vstrRelayDpCaption.resize(DP_RELAY_SUM);
	for (size_t i = 0; i < DP_RELAY_SUM; i++)
	{
		m_vbRelayDpStatus[i] = FALSE;
		m_vstrRelayDp[i] = _T("");
		m_vstrRelayDpName[i] = _T("");
		m_vstrRelayDpCaption[i] = _T("");
	}
}

CCtrlSet::CCtrlSet(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nRelayBtFocus(-1)
	, m_nRelayCkFocus(-1)
	, m_nRelayDpFocus(-1)
	, m_bRelayBtStarStatus(FALSE)
	, m_bRelayBtStopStatus(FALSE)
	, m_bRelayBtResetStatus(FALSE)
	, m_bRelayBtErrorStatus(FALSE)
	, m_nBasicFocus(0)
	, m_bRelayBtPauseStatus(FALSE)
	, m_bRelaySwAutoStatus(FALSE)
	, m_bRelaySwUnAutoStatus(FALSE)
{
	m_vbRelayBtStatus.resize(BT_RELAY_SUM);
	m_vstrRelayBt.resize(BT_RELAY_SUM);
	m_vstrRelayBtName.resize(BT_RELAY_SUM);
	m_vnRelayBtMode.resize(BT_RELAY_SUM);
	m_vbIsRelayBtClickAuto.resize(BT_RELAY_SUM);
	for (size_t i = 0; i < BT_RELAY_SUM; i++)
	{
		m_vbRelayBtStatus[i] = FALSE;
		m_vstrRelayBt[i] = _T("");
		m_vstrRelayBtName[i] = _T("");
		m_vnRelayBtMode[i] = 0;
		m_vbIsRelayBtClickAuto[i] = FALSE;
	}

	m_vbRelayCkStatus.resize(CK_RELAY_SUM);
	m_vstrRelayCk.resize(CK_RELAY_SUM);
	m_vstrRelayCkName.resize(CK_RELAY_SUM);
	for (size_t i = 0; i < CK_RELAY_SUM; i++)
	{
		m_vbRelayCkStatus[i] = FALSE;
		m_vstrRelayCk[i] = _T("");
		m_vstrRelayCkName[i] = _T("");
	}

	m_vbRelayDpStatus.resize(DP_RELAY_SUM);
	m_vstrRelayDp.resize(DP_RELAY_SUM);
	m_vstrRelayDpName.resize(DP_RELAY_SUM);
	m_vstrRelayDpCaption.resize(DP_RELAY_SUM);
	for (size_t i = 0; i < DP_RELAY_SUM; i++)
	{
		m_vbRelayDpStatus[i] = FALSE;
		m_vstrRelayDp[i] = _T("");
		m_vstrRelayDpName[i] = _T("");
		m_vstrRelayDpCaption[i] = _T("");
	}
}



CCtrlSet::~CCtrlSet()
{
}

void CCtrlSet::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);


	for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
	{
		DDX_Control(pDX, IDC_BL_RelayBtMode_0 + i, m_BL_rdRelayBtMode[i]);
	}

	DDX_Control(pDX, IDC_BL_ckRelayClickAuto, m_BL_ckRelayBtClickAuto);

	DDX_Control(pDX, IDC_BL_RelayBt, m_BL_edRelayBt);
	DDX_Control(pDX, IDC_BL_RelayBtName, m_BL_edRelayBtName);

	DDX_Control(pDX, IDC_BL_RelayCk, m_BL_edRelayCk);
	DDX_Control(pDX, IDC_BL_RelayCkName, m_BL_edRelayCkName);

	DDX_Control(pDX, IDC_BL_RelayDrop, m_BL_edRelayDp);
	DDX_Control(pDX, IDC_BL_RelayDropName, m_BL_edRelayDpName);
	DDX_Control(pDX, IDC_BL_RelayDropCaption, m_BL_edRelayDpCaption);
	
	for (int i = 0; i < BT_RELAY_SUM; i++)
	{
		DDX_Control(pDX, IDC_BL_RelayBtStatus_0 + i, m_BL_btRelayBtStatus[i]);
	}
	for (int i = 0; i < CK_RELAY_SUM; i++)
	{
		DDX_Control(pDX, IDC_BL_RelayCkStatus_0 + i, m_BL_btRelayCkStatus[i]);
	}

	for (int i = 0; i < DP_RELAY_SUM; i++)
	{
		DDX_Control(pDX, IDC_BL_RelayDropStatus_0 + i, m_BL_btRelayDpStatus[i]);
	}

	DDX_Control(pDX, IDC_BL_RelayBtOK, m_BL_btRelayBtOK);
	DDX_Control(pDX, IDC_BL_RelayCkOK, m_BL_btRelayCkOK);
	DDX_Control(pDX, IDC_BL_RelayDpOK, m_BL_btRelayDpOK);

	DDX_Control(pDX, IDC_BL_RelayStarStatus, m_BL_btRelayStarStatus);
	DDX_Control(pDX, IDC_BL_RelayStopStatus, m_BL_btRelayStopStatus);
	DDX_Control(pDX, IDC_BL_RelayResetStatus, m_BL_btRelayResetStatus);
	DDX_Control(pDX, IDC_BL_RelayErrorStatus, m_BL_btRelayErrorStatus);
	DDX_Control(pDX, IDC_BL_RelayPauseStatus, m_BL_btRelayPauseStatus);
	DDX_Control(pDX, IDC_BL_RelayAutoStatus, m_BL_btRelayAutoStatus);
	DDX_Control(pDX, IDC_BL_RelayUnAutoStatus, m_BL_btRelayUnAutoStatus);

	DDX_Control(pDX, IDC_BL_btSaveCtrl, m_BL_btSaveCtrl);
	DDX_Control(pDX, IDC_BL_btLoadCtrl, m_BL_btLoadCtrl);
}

void CCtrlSet::_DefaultFocus(void)
{
	//m_BtBaseOk.ShowWindow(SW_HIDE);
	//m_BtBaseCancel.ShowWindow(SW_HIDE);

}

BOOL CCtrlSet::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateCtrlInfo();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CCtrlSet::UpdateCtrlInfo()
{
	m_BL_edRelayBt.SetEnabled(FALSE);
	m_BL_edRelayBtName.SetEnabled(FALSE);
	for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
	{
		m_BL_rdRelayBtMode[i].SetEnabled(FALSE);
	}
	m_BL_ckRelayBtClickAuto.SetEnabled(FALSE);
	m_BL_btRelayBtOK.SetEnabled(FALSE);

	m_BL_edRelayCk.SetEnabled(FALSE);
	m_BL_edRelayCkName.SetEnabled(FALSE);
	m_BL_btRelayCkOK.SetEnabled(FALSE);

	m_BL_edRelayDp.SetEnabled(FALSE);
	m_BL_edRelayDpName.SetEnabled(FALSE);
	m_BL_edRelayDpCaption.SetEnabled(FALSE);
	m_BL_btRelayDpOK.SetEnabled(FALSE);


	for (int i = 0; i < CK_RELAY_SUM; i++)
	{
		if (m_vbRelayCkStatus[i])//按键继电器被使用
		{
			m_BL_btRelayCkStatus[i].SetBorderColor(RGB(0, 255, 230));
			m_BL_btRelayCkStatus[i].SetCtrlCaption(m_vstrRelayCk[i]);
		}
		else
		{
			m_BL_btRelayCkStatus[i].SetBorderColor(RGB(128, 128, 128));
		}
		m_BL_btRelayCkStatus[i].SetFocusColor(RGB(128,128,128));
	}

	for (int i = 0; i < DP_RELAY_SUM; i++)
	{
		if (m_vbRelayDpStatus[i])//按键继电器被使用
		{
			m_BL_btRelayDpStatus[i].SetBorderColor(RGB(0, 255, 230));
			m_BL_btRelayDpStatus[i].SetCtrlCaption(m_vstrRelayDp[i]);
		}
		else
		{
			m_BL_btRelayDpStatus[i].SetBorderColor(RGB(128, 128, 128));
		}
		m_BL_btRelayDpStatus[i].SetFocusColor(RGB(128,128,128));
	}

	for (int i = 0; i < BT_RELAY_SUM; i++)
	{
		if (m_vbRelayBtStatus[i])//按键继电器被使用
		{
			m_BL_btRelayBtStatus[i].SetBorderColor(RGB(0, 255, 230));
			m_BL_btRelayBtStatus[i].SetCtrlCaption(m_vstrRelayBt[i]);
		}
		else
		{
			m_BL_btRelayBtStatus[i].SetBorderColor(RGB(128, 128, 128));
		}
		switch (m_vnRelayBtMode[i])
		{
		case RELAY_BT_MODE_LOCK:
			m_BL_btRelayBtStatus[i].SetInterruptMode(TRUE);
			break;
		case RELAY_BT_MODE_UNLOCK:
			m_BL_btRelayBtStatus[i].SetInterruptMode(FALSE);
			break;
		default:
			break;
		}
		m_BL_btRelayBtStatus[i].SetFocusColor(RGB(128,128,128));
	}

	SetBasicRelayColor();
}

void CCtrlSet::SetBasicRelayColor()
{
	if (m_bRelayBtStarStatus)
	{
		m_BL_btRelayStarStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayStarStatus.SetCtrlCaption(m_strRelayStar);
	}
	else
	{
		m_BL_btRelayStarStatus.SetBorderColor(RGB(128, 128, 128));
	}

	if (m_bRelayBtStopStatus)
	{
		m_BL_btRelayStopStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayStopStatus.SetCtrlCaption(m_strRelayStop);
	}
	else
	{
		m_BL_btRelayStopStatus.SetBorderColor(RGB(128, 128, 128));
	}

	if (m_bRelayBtResetStatus)
	{
		m_BL_btRelayResetStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayResetStatus.SetCtrlCaption(m_strRelayReset);
	}
	else
	{
		m_BL_btRelayResetStatus.SetBorderColor(RGB(128, 128, 128));
	}

	if (m_bRelayBtErrorStatus)
	{
		m_BL_btRelayErrorStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayErrorStatus.SetCtrlCaption(m_strRelayError);
	}
	else
	{
		m_BL_btRelayErrorStatus.SetBorderColor(RGB(128, 128, 128));
	}

	if (m_bRelayBtPauseStatus)
	{
		m_BL_btRelayPauseStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayPauseStatus.SetCtrlCaption(m_strRelayPause);
	}
	else
	{
		m_BL_btRelayPauseStatus.SetBorderColor(RGB(128, 128, 128));
	}

	if (m_bRelaySwAutoStatus)
	{
		m_BL_btRelayAutoStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayAutoStatus.SetCtrlCaption(m_strRelayAuto);
	}
	else
	{
		m_BL_btRelayAutoStatus.SetBorderColor(RGB(128, 128, 128));
	}

	if (m_bRelaySwUnAutoStatus)
	{
		m_BL_btRelayUnAutoStatus.SetBorderColor(RGB(0, 255, 230));
		m_BL_btRelayUnAutoStatus.SetCtrlCaption(m_strRelayUnAuto);
	}
	else
	{
		m_BL_btRelayUnAutoStatus.SetBorderColor(RGB(128, 128, 128));
	}
}

void CCtrlSet::DrawElement(CDC * pDC, CRect rcDraw)
{
	CPen pen(PS_SOLID, 1, RGB(0, 255, 230));

	pDC->SelectObject(pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->MoveTo(600, 53);
	pDC->LineTo(470, 53);
	pDC->LineTo(470, 482);
	pDC->LineTo(1115, 482);
	pDC->LineTo(1115, 53);
	pDC->LineTo(600, 53);

}

void CCtrlSet::StatusChangedBlckrelayclickauto(short nNewStatus)
{
	// TODO: 在此处添加消息处理程序代码
}

BEGIN_MESSAGE_MAP(CCtrlSet, CTpLayerWnd)
	ON_MESSAGE(WM_RD_RELAY_BT_MODE, &CCtrlSet::OnRdRelayBtModeChange)
	ON_MESSAGE(WM_BT_RELAY_BT_STATUS, &CCtrlSet::OnBtRelayBtStatus)
	ON_MESSAGE(WM_BT_RELAY_CK_STATUS, &CCtrlSet::OnBtRelayCkStatus)
	ON_MESSAGE(WM_BT_RELAY_DP_STATUS, &CCtrlSet::OnBtRelayDpStatus)
	ON_MESSAGE(WM_BG_RELAY_BASIC, &CCtrlSet::OnBgRelayBasic)
END_MESSAGE_MAP()


// CCtrlSet 消息处理程序


afx_msg LRESULT CCtrlSet::OnRdRelayBtModeChange(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
	{
		m_BL_rdRelayBtMode[i].SetSelect(FALSE);
		if (m_BL_rdRelayBtMode[i].IsMsgSrc())
		{
			m_BL_rdRelayBtMode[i].SetSelect(TRUE);
		}
	}
	return 0;
}



afx_msg LRESULT CCtrlSet::OnBtRelayBtStatus(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 4)//鼠標命中
	{
		return 0;
	}
	if (wParam == 0)//單擊鼠標左鍵
	{
		m_BL_edRelayBt.SetEnabled(TRUE);
		m_BL_edRelayBtName.SetEnabled(TRUE);
		for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
		{
			m_BL_rdRelayBtMode[i].SetEnabled(TRUE);
		}
		m_BL_btRelayBtOK.SetEnabled(TRUE);
		m_BL_ckRelayBtClickAuto.SetEnabled(TRUE);

		m_BL_edRelayCk.SetEnabled(FALSE);
		m_BL_edRelayCkName.SetEnabled(FALSE);
		m_BL_btRelayCkOK.SetEnabled(FALSE);

		m_BL_edRelayDp.SetEnabled(FALSE);
		m_BL_edRelayDpName.SetEnabled(FALSE);
		m_BL_edRelayDpCaption.SetEnabled(FALSE);
		m_BL_btRelayDpOK.SetEnabled(FALSE);

		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			if (m_vbRelayCkStatus[i])//按键继电器被使用
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayCkStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			if (m_vbRelayDpStatus[i])//按键继电器被使用
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayDpStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if (m_vbRelayBtStatus[i])//按键继电器被使用
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayBtStatus[i].SetFocusColor(RGB(128,128,128));
			m_BL_btRelayBtStatus[i].SetStatus(FALSE);
			if (m_BL_btRelayBtStatus[i].IsMsgSrc())
			{
				m_nRelayBtFocus = i;
				m_BL_edRelayBt.SetValueText(m_vstrRelayBt[i]);
				m_BL_edRelayBtName.SetValueText(m_vstrRelayBtName[i]);
				m_BL_rdRelayBtMode[0].SetSelect(FALSE);
				m_BL_rdRelayBtMode[1].SetSelect(FALSE);
				switch (m_vnRelayBtMode[i])
				{
				case RELAY_BT_MODE_LOCK:
					m_BL_rdRelayBtMode[0].SetSelect(TRUE);
					m_BL_rdRelayBtMode[1].SetSelect(FALSE);
					break;
				case RELAY_BT_MODE_UNLOCK:
					m_BL_rdRelayBtMode[0].SetSelect(FALSE);
					m_BL_rdRelayBtMode[1].SetSelect(TRUE);
					break;
				default:
					break;
				}
				m_BL_ckRelayBtClickAuto.SetStatus(m_vbIsRelayBtClickAuto[i]);

				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(255, 0, 0));
				m_BL_btRelayBtStatus[i].SetFocusColor(RGB(255, 0, 0));
				m_BL_btRelayBtStatus[i].SetForeColor(RGB(0, 255, 230));
			}
		}

		SetBasicRelayColor();
	}
	if (wParam == 1)//雙擊鼠標左鍵
	{

	}
	if (wParam == 2)//雙擊鼠標右鍵
	{
		
	}
	if (wParam == 3)//按鍵狀態改變
	{

	}
	return 0;
}



afx_msg LRESULT CCtrlSet::OnBtRelayCkStatus(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 4)//鼠標命中
	{
		return 0;
	}
	if (wParam == 0)//單擊鼠標左鍵
	{
		m_BL_edRelayBt.SetEnabled(FALSE);
		m_BL_edRelayBtName.SetEnabled(FALSE);
		for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
		{
			m_BL_rdRelayBtMode[i].SetEnabled(FALSE);
		}
		m_BL_btRelayBtOK.SetEnabled(FALSE);
		m_BL_ckRelayBtClickAuto.SetEnabled(FALSE);

		m_BL_edRelayCk.SetEnabled(TRUE);
		m_BL_edRelayCkName.SetEnabled(TRUE);
		m_BL_btRelayCkOK.SetEnabled(TRUE);

		m_BL_edRelayDp.SetEnabled(FALSE);
		m_BL_edRelayDpName.SetEnabled(FALSE);
		m_BL_btRelayDpOK.SetEnabled(FALSE);
		m_BL_edRelayDpCaption.SetEnabled(FALSE);

		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if (m_vbRelayBtStatus[i])//按键继电器被使用
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayBtStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			if (m_vbRelayDpStatus[i])//按键继电器被使用
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayDpStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			if (m_vbRelayCkStatus[i])//按键继电器被使用
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayCkStatus[i].SetFocusColor(RGB(128,128,128));
			m_BL_btRelayCkStatus[i].SetStatus(FALSE);
			if (m_BL_btRelayCkStatus[i].IsMsgSrc())
			{
				m_nRelayCkFocus = i;
				m_BL_edRelayCk.SetValueText(m_vstrRelayCk[i]);
				m_BL_edRelayCkName.SetValueText(m_vstrRelayCkName[i]);
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(255, 0, 0));
				m_BL_btRelayCkStatus[i].SetFocusColor(RGB(255, 0, 0));
				m_BL_btRelayCkStatus[i].SetForeColor(RGB(0, 255, 230));
			}
		}

		SetBasicRelayColor();
	}
	if (wParam == 1)//雙擊鼠標左鍵
	{

	}
	if (wParam == 2)//雙擊鼠標右鍵
	{

	}
	if (wParam == 3)//按鍵狀態改變
	{

	}
	return 0;
}


afx_msg LRESULT CCtrlSet::OnBtRelayDpStatus(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 4)//鼠標命中
	{
		return 0;
	}
	if (wParam == 0)//單擊鼠標左鍵
	{
		m_BL_edRelayBt.SetEnabled(FALSE);
		m_BL_edRelayBtName.SetEnabled(FALSE);
		for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
		{
			m_BL_rdRelayBtMode[i].SetEnabled(FALSE);
		}
		m_BL_btRelayBtOK.SetEnabled(FALSE);
		m_BL_ckRelayBtClickAuto.SetEnabled(FALSE);

		m_BL_edRelayCk.SetEnabled(FALSE);
		m_BL_edRelayCkName.SetEnabled(FALSE);
		m_BL_btRelayCkOK.SetEnabled(FALSE);

		m_BL_edRelayDp.SetEnabled(TRUE);
		m_BL_edRelayDpName.SetEnabled(TRUE);
		m_BL_edRelayDpCaption.SetEnabled(TRUE);
		m_BL_btRelayDpOK.SetEnabled(TRUE);

		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if (m_vbRelayBtStatus[i])//按键继电器被使用
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayBtStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			if (m_vbRelayCkStatus[i])//按键继电器被使用
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayCkStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			if (m_vbRelayDpStatus[i])//按键继电器被使用
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayDpStatus[i].SetFocusColor(RGB(128,128,128));
			m_BL_btRelayDpStatus[i].SetStatus(FALSE);
			if (m_BL_btRelayDpStatus[i].IsMsgSrc())
			{
				m_nRelayDpFocus = i;
				m_BL_edRelayDp.SetValueText(m_vstrRelayDp[i]);
				m_BL_edRelayDpName.SetValueText(m_vstrRelayDpName[i]);
				m_BL_edRelayDpCaption.SetValueText(m_vstrRelayDpCaption[i]);
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(255, 0, 0));
				m_BL_btRelayDpStatus[i].SetFocusColor(RGB(255, 0, 0));
				m_BL_btRelayDpStatus[i].SetForeColor(RGB(0, 255, 230));
			}
		}

	SetBasicRelayColor();
	}
	if (wParam == 1)//雙擊鼠標左鍵
	{

	}
	if (wParam == 2)//雙擊鼠標右鍵
	{

	}
	if (wParam == 3)//按鍵狀態改變
	{

	}
	return 0;
}

afx_msg LRESULT CCtrlSet::OnBgRelayBasic(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 4)//鼠標命中
	{
		return 0;
	}
	if (wParam == 0)//單擊鼠標左鍵
	{
		m_BL_edRelayBt.SetEnabled(TRUE);
		m_BL_edRelayBtName.SetEnabled(FALSE);
		for (int i = 0; i < RELAY_BT_MODE_COUNTER; i++)
		{
			m_BL_rdRelayBtMode[i].SetEnabled(FALSE);
		}
		m_BL_ckRelayBtClickAuto.SetEnabled(FALSE);
		m_BL_btRelayBtOK.SetEnabled(TRUE);

		m_BL_edRelayCk.SetEnabled(FALSE);
		m_BL_edRelayCkName.SetEnabled(FALSE);
		m_BL_btRelayCkOK.SetEnabled(FALSE);

		m_BL_edRelayDp.SetEnabled(FALSE);
		m_BL_edRelayDpName.SetEnabled(FALSE);
		m_BL_edRelayDpCaption.SetEnabled(FALSE);
		m_BL_btRelayDpOK.SetEnabled(FALSE);

		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			if (m_vbRelayCkStatus[i])//按键继电器被使用
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayCkStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayCkStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			if (m_vbRelayDpStatus[i])//按键继电器被使用
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayDpStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayDpStatus[i].SetFocusColor(RGB(128,128,128));
		}

		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if (m_vbRelayBtStatus[i])//按键继电器被使用
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(0, 255, 230));
			}
			else
			{
				m_BL_btRelayBtStatus[i].SetBorderColor(RGB(128, 128, 128));
			}
			m_BL_btRelayBtStatus[i].SetFocusColor(RGB(128,128,128));
		}

		if (m_bRelayBtStarStatus)//启动继电器被使用
		{
			m_BL_btRelayStarStatus.SetBorderColor(RGB(0, 255, 230));
		}
		else
		{
			m_BL_btRelayStarStatus.SetBorderColor(RGB(128, 128, 128));
		}
		m_BL_btRelayStarStatus.SetFocusColor(RGB(128,128,128));

		if (m_bRelayBtStopStatus)//停止继电器被使用
		{
			m_BL_btRelayStopStatus.SetBorderColor(RGB(0, 255, 230));
		}
		else
		{
			m_BL_btRelayStopStatus.SetBorderColor(RGB(128, 128, 128));
		}
		m_BL_btRelayStopStatus.SetFocusColor(RGB(128,128,128));

		if (m_bRelayBtResetStatus)//复位继电器被使用
		{
			m_BL_btRelayResetStatus.SetBorderColor(RGB(0, 255, 230));
		}
		else
		{
			m_BL_btRelayResetStatus.SetBorderColor(RGB(128, 128, 128));
		}
		m_BL_btRelayResetStatus.SetFocusColor(RGB(128,128,128));

		if (m_bRelayBtErrorStatus)//故障继电器被使用
		{
			m_BL_btRelayErrorStatus.SetBorderColor(RGB(0, 255, 230));
		}
		else
		{
			m_BL_btRelayErrorStatus.SetBorderColor(RGB(128, 128, 128));
		}
		m_BL_btRelayErrorStatus.SetFocusColor(RGB(128,128,128));


		if (m_bRelayBtPauseStatus)
		{
			m_BL_btRelayPauseStatus.SetBorderColor(RGB(0, 255, 230));
			m_BL_btRelayPauseStatus.SetCtrlCaption(m_strRelayPause);
		}
		else
		{
			m_BL_btRelayPauseStatus.SetBorderColor(RGB(128, 128, 128));
		}

		if (m_bRelaySwAutoStatus)
		{
			m_BL_btRelayAutoStatus.SetBorderColor(RGB(0, 255, 230));
			m_BL_btRelayAutoStatus.SetCtrlCaption(m_strRelayAuto);
		}
		else
		{
			m_BL_btRelayAutoStatus.SetBorderColor(RGB(128, 128, 128));
		}

		if (m_bRelaySwUnAutoStatus)
		{
			m_BL_btRelayUnAutoStatus.SetBorderColor(RGB(0, 255, 230));
			m_BL_btRelayUnAutoStatus.SetCtrlCaption(m_strRelayUnAuto);
		}
		else
		{
			m_BL_btRelayUnAutoStatus.SetBorderColor(RGB(128, 128, 128));
		}


		if (m_BL_btRelayStarStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayStar);
			m_BL_btRelayStarStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayStarStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayStarStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayStarStatus.SetStatus(FALSE);
			m_nBasicFocus = 1;
		}
		if (m_BL_btRelayStopStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayStop);
			m_BL_btRelayStopStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayStopStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayStopStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayStopStatus.SetStatus(FALSE);
			m_nBasicFocus = 2;
		}
		if (m_BL_btRelayResetStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayReset);
			m_BL_btRelayResetStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayResetStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayResetStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayResetStatus.SetStatus(FALSE);
			m_nBasicFocus = 3;
		}
		if (m_BL_btRelayErrorStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayError);
			m_BL_btRelayErrorStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayErrorStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayErrorStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayErrorStatus.SetStatus(FALSE);
			m_nBasicFocus = 4;
		}
		if (m_BL_btRelayPauseStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayPause);
			m_BL_btRelayPauseStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayPauseStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayPauseStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayPauseStatus.SetStatus(FALSE);
			m_nBasicFocus = 5;
		}
		if (m_BL_btRelayAutoStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayAuto);
			m_BL_btRelayAutoStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayAutoStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayAutoStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayAutoStatus.SetStatus(FALSE);
			m_nBasicFocus = 6;
		}
		if (m_BL_btRelayUnAutoStatus.IsMsgSrc())
		{
			m_BL_edRelayBt.SetValueText(m_strRelayUnAuto);
			m_BL_btRelayUnAutoStatus.SetBorderColor(RGB(255, 0, 0));
			m_BL_btRelayUnAutoStatus.SetFocusColor(RGB(255, 0, 0));
			m_BL_btRelayUnAutoStatus.SetForeColor(RGB(0, 255, 230));
			m_BL_btRelayUnAutoStatus.SetStatus(FALSE);
			m_nBasicFocus = 7;
		}
	}
	if (wParam == 1)//雙擊鼠標左鍵
	{

	}
	if (wParam == 2)//雙擊鼠標右鍵
	{

	}
	if (wParam == 3)//按鍵狀態改變
	{

	}
	return 0;
}


BEGIN_EVENTSINK_MAP(CCtrlSet, CTpLayerWnd)
	ON_EVENT(CCtrlSet, IDC_BL_RelayBtOK, 1, CCtrlSet::LBtClickedBlRelaybtok, VTS_I4)
	ON_EVENT(CCtrlSet, IDC_BL_RelayBt, 1, CCtrlSet::ValueChangedBlRelaybt, VTS_BSTR)
	ON_EVENT(CCtrlSet, IDC_BL_RelayCkOK, 1, CCtrlSet::LBtClickedBlRelayckok, VTS_I4)
	ON_EVENT(CCtrlSet, IDC_BL_RelayCk, 1, CCtrlSet::ValueChangedBlRelayck, VTS_BSTR)
	ON_EVENT(CCtrlSet, IDC_BL_RelayDpOK, 1, CCtrlSet::LBtClickedBlRelaydpok, VTS_I4)
	ON_EVENT(CCtrlSet, IDC_BL_RelayDrop, 1, CCtrlSet::ValueChangedBlRelaydrop, VTS_BSTR)
	ON_EVENT(CCtrlSet, IDC_BL_btSaveCtrl, 1, CCtrlSet::LBtClickedBlbtsavectrl, VTS_I4)
	ON_EVENT(CCtrlSet, IDC_BL_btLoadCtrl, 1, CCtrlSet::LBtClickedBlbtloadctrl, VTS_I4)
	ON_EVENT(CCtrlSet, IDC_BL_ckRelayClickAuto, 1, CCtrlSet::StatusChangedBlckrelayclickauto, VTS_I2)
END_EVENTSINK_MAP()


void CCtrlSet::LBtClickedBlRelaybtok(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	if (m_BL_edRelayBt.GetValueText() != _T(""))
	{
		CString strTem;
		strTem = m_BL_edRelayBt.GetValueText();
		if (strTem[0] != 'M')
		{
			MsgBox.ShowMsg(_T("继电器输入错误"), _T("ERROR"), MB_ICONERROR | MB_OK);
			m_BL_edRelayBt.SetValueText(_T(""));
			if (m_BL_rdRelayBtMode[0].GetEnabled())
			{
				m_vbRelayBtStatus[m_nRelayBtFocus] = FALSE;
			}
			else
			{
				switch (m_nBasicFocus)
				{
				case 1:
					m_bRelayBtStarStatus = FALSE;
					break;
				case 2:
					m_bRelayBtStopStatus = FALSE;
					break;
				case 3:
					m_bRelayBtResetStatus = FALSE;
					break;
				case 4:
					m_bRelayBtErrorStatus = FALSE;
					break;
				case 5:
					m_bRelayBtPauseStatus = FALSE;
					break;
				case 6:
					m_bRelaySwAutoStatus = FALSE;
					break;
				case 7:
					m_bRelaySwUnAutoStatus = FALSE;
					break;
				default:
					break;
				}
			}
		}
		else
		{
			for (int i = 1; i < strTem.GetLength(); i++)
			{
				if ((strTem[i] < '0') || (strTem[i] > '9'))
				{
					MsgBox.ShowMsg(_T("继电器输入错误"), _T("ERROR"), MB_ICONERROR | MB_OK);
					m_BL_edRelayBt.SetValueText(_T(""));
					if (m_BL_rdRelayBtMode[0].GetEnabled())
					{
						m_vbRelayBtStatus[m_nRelayBtFocus] = FALSE;
					}
					else
					{
						switch (m_nBasicFocus)
						{
						case 1:
							m_bRelayBtStarStatus = FALSE;
							break;
						case 2:
							m_bRelayBtStopStatus = FALSE;
							break;
						case 3:
							m_bRelayBtResetStatus = FALSE;

							break;
						case 4:
							m_bRelayBtErrorStatus = FALSE;
							break;
						case 5:
							m_bRelayBtPauseStatus = FALSE;
							break;
						case 6:
							m_bRelaySwAutoStatus = FALSE;
							break;
						case 7:
							m_bRelaySwUnAutoStatus = FALSE;
							break;
						default:
							break;
						}
					}
					return;
				}
			}

			strTem.Delete(0, 1);
			int nSub = _ttoi(m_strCoilEnd) - _ttoi(m_strCoilStart);
			if ((_ttoi(strTem) - _ttoi(m_strCoilPos)) > nSub)
			{
				MsgBox.ShowMsg(_T(" M 線圈超出設置範圍"), _T("ERROR"), MB_ICONERROR | MB_OK);
				if (m_BL_rdRelayBtMode[0].GetEnabled())
				{
					m_vbRelayBtStatus[m_nRelayBtFocus] = FALSE;
				}
				else
				{
					switch (m_nBasicFocus)
					{
					case 1:
						m_bRelayBtStarStatus = FALSE;
						break;
					case 2:
						m_bRelayBtStopStatus = FALSE;
						break;
					case 3:
						m_bRelayBtResetStatus = FALSE;

						break;
					case 4:
						m_bRelayBtErrorStatus = FALSE;
						break;
					case 5:
						m_bRelayBtPauseStatus = FALSE;
						break;
					case 6:
						m_bRelaySwAutoStatus = FALSE;
						break;
					case 7:
						m_bRelaySwUnAutoStatus = FALSE;
						break;
					default:
						break;
					}
				}
				m_BL_edRelayBt.SetValueText(_T(""));
				return;
			}
			if (m_BL_rdRelayBtMode[0].GetEnabled())//按键继电器
			{
				if (m_BL_rdRelayBtMode[0].GetSelect() || m_BL_rdRelayBtMode[1].GetSelect())
				{
					if (m_BL_edRelayBtName.GetValueText() != _T(""))
					{
						m_vbRelayBtStatus[m_nRelayBtFocus] = TRUE;
						m_vstrRelayBt[m_nRelayBtFocus] = m_BL_edRelayBt.GetValueText();
						m_vstrRelayBtName[m_nRelayBtFocus] = m_BL_edRelayBtName.GetValueText();
						m_BL_btRelayBtStatus[m_nRelayBtFocus].SetCtrlCaption(m_vstrRelayBt[m_nRelayBtFocus]);
						if (m_BL_rdRelayBtMode[0].GetSelect())
						{
							m_vnRelayBtMode[m_nRelayBtFocus] = RELAY_BT_MODE_LOCK;
							m_BL_btRelayBtStatus[m_nRelayBtFocus].SetInterruptMode(TRUE);
						}
						if (m_BL_rdRelayBtMode[1].GetSelect())
						{
							m_vnRelayBtMode[m_nRelayBtFocus] = RELAY_BT_MODE_UNLOCK;
							m_BL_btRelayBtStatus[m_nRelayBtFocus].SetInterruptMode(FALSE);
						}
						m_vbIsRelayBtClickAuto[m_nRelayBtFocus] = m_BL_ckRelayBtClickAuto.GetStatus();
					}
					else
					{
						m_vbRelayBtStatus[m_nRelayBtFocus] = FALSE;
						MsgBox.ShowMsg(_T("未输入按键名称"), _T("ERROR"), MB_ICONERROR | MB_OK);
					}
				}
				else
				{
					MsgBox.ShowMsg(_T("未选择继电器类型"), _T("ERROR"), MB_ICONERROR | MB_OK);
					m_vbRelayBtStatus[m_nRelayBtFocus] = FALSE;
				}
			}
			else//启动，停止，复位，故障继电器
			{
				switch (m_nBasicFocus)
				{
				case 1:
					m_bRelayBtStarStatus = TRUE;
					m_strRelayStar = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayStarStatus.SetCtrlCaption(m_strRelayStar);
					break;
				case 2:
					m_bRelayBtStopStatus = TRUE;
					m_strRelayStop = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayStopStatus.SetCtrlCaption(m_strRelayStop);
					break;
				case 3:
					m_bRelayBtResetStatus = TRUE;
					m_strRelayReset = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayResetStatus.SetCtrlCaption(m_strRelayReset);
					break;
				case 4:
					m_bRelayBtErrorStatus = TRUE;
					m_strRelayError = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayErrorStatus.SetCtrlCaption(m_strRelayError);
					break;
				case 5:
					m_bRelayBtPauseStatus = TRUE;
					m_strRelayPause = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayPauseStatus.SetCtrlCaption(m_strRelayPause);
					break;
				case 6:
					m_bRelaySwAutoStatus = TRUE;
					m_strRelayAuto = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayAutoStatus.SetCtrlCaption(m_strRelayAuto);
					break;
				case 7:
					m_bRelaySwUnAutoStatus = TRUE;
					m_strRelayUnAuto = m_BL_edRelayBt.GetValueText();
					m_BL_btRelayUnAutoStatus.SetCtrlCaption(m_strRelayUnAuto);
					break;
				default:
					break;
				}
				
			}
		}
	}
	else
	{
		if (m_BL_rdRelayBtMode[0].GetEnabled())
		{
			m_vstrRelayBt[m_nRelayBtFocus] = _T("");
			m_vstrRelayBtName[m_nRelayBtFocus] = _T("");
			m_vnRelayBtMode[m_nRelayBtFocus] = -1;
			m_vbRelayBtStatus[m_nRelayBtFocus] = FALSE;
			m_BL_btRelayBtStatus[m_nRelayBtFocus].SetCtrlCaption(_T("未使用"));
			m_BL_btRelayBtStatus[m_nRelayBtFocus].SetInterruptMode(FALSE);
		}
		else
		{
			switch (m_nBasicFocus)
			{
			case 1:
				m_bRelayBtStarStatus = FALSE;
				m_strRelayStar = _T("");
				m_BL_btRelayStarStatus.SetCtrlCaption(_T("启动"));
				break;
			case 2:
				m_bRelayBtStopStatus = FALSE;
				m_strRelayStop = _T("");
				m_BL_btRelayStopStatus.SetCtrlCaption(_T("停止"));
				break;
			case 3:
				m_bRelayBtResetStatus = FALSE;
				m_strRelayReset = _T("");
				m_BL_btRelayResetStatus.SetCtrlCaption(_T("复位"));
				break;
			case 4:
				m_bRelayBtErrorStatus = FALSE;
				m_strRelayError = _T("");
				m_BL_btRelayErrorStatus.SetCtrlCaption(_T("故障重置"));
				break;
			case 5:
				m_bRelayBtPauseStatus = FALSE;
				m_strRelayPause = _T("");
				m_BL_btRelayPauseStatus.SetCtrlCaption(_T("暂停"));
				break;
			case 6:
				m_bRelaySwAutoStatus = FALSE;
				m_strRelayAuto = _T("");
				m_BL_btRelayAutoStatus.SetCtrlCaption(_T("自动"));
				break;
			case 7:
				m_bRelaySwUnAutoStatus = FALSE;
				m_strRelayUnAuto = _T("");
				m_BL_btRelayUnAutoStatus.SetCtrlCaption(_T("手动"));
				break;
			default:
				break;
			}
		}
		
	}
}


void CCtrlSet::ValueChangedBlRelaybt(LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CString strTem;
	strTem = m_BL_edRelayBt.GetValueText();
	strTem.MakeUpper();
	m_BL_edRelayBt.SetValueText(strTem);
}


void CCtrlSet::LBtClickedBlRelayckok(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	if (m_BL_edRelayCk.GetValueText() != _T(""))
	{
		CString strTem;
		strTem = m_BL_edRelayCk.GetValueText();
		if (strTem[0] != 'M')
		{
			MsgBox.ShowMsg(_T("继电器输入错误"), _T("ERROR"), MB_ICONERROR | MB_OK);
			m_BL_edRelayCk.SetValueText(_T(""));
			m_vbRelayCkStatus[m_nRelayCkFocus] = FALSE;
		}
		else
		{
			for (int i = 1; i < strTem.GetLength(); i++)
			{
				if ((strTem[i] < '0') || (strTem[i] > '9'))
				{
					MsgBox.ShowMsg(_T("继电器输入错误"), _T("ERROR"), MB_ICONERROR | MB_OK);
					m_BL_edRelayCk.SetValueText(_T(""));
					m_vbRelayCkStatus[m_nRelayCkFocus] = FALSE;
					return;
				}
			}

			strTem.Delete(0, 1);
			int nSub = _ttoi(m_strCoilEnd) - _ttoi(m_strCoilStart);
			if ((_ttoi(strTem) - _ttoi(m_strCoilPos)) > nSub)
			{
				MsgBox.ShowMsg(_T(" M 線圈超出設置範圍"), _T("ERROR"), MB_ICONERROR | MB_OK);
				m_vbRelayCkStatus[m_nRelayCkFocus] = FALSE;
				m_BL_edRelayCk.SetValueText(_T(""));
				return;
			}

			if (m_BL_edRelayCkName.GetValueText() != _T(""))
			{
				m_vbRelayCkStatus[m_nRelayCkFocus] = TRUE;
				m_vstrRelayCk[m_nRelayCkFocus] = m_BL_edRelayCk.GetValueText();
				m_vstrRelayCkName[m_nRelayCkFocus] = m_BL_edRelayCkName.GetValueText();
				m_BL_btRelayCkStatus[m_nRelayCkFocus].SetCtrlCaption(m_vstrRelayCk[m_nRelayCkFocus]);
			}
			else
			{
				m_vbRelayCkStatus[m_nRelayCkFocus] = FALSE;
				MsgBox.ShowMsg(_T("未输入勾选名称"), _T("ERROR"), MB_ICONERROR | MB_OK);
			}
		}
	}
	else
	{
		m_vstrRelayCk[m_nRelayCkFocus] = _T("");
		m_vstrRelayCkName[m_nRelayCkFocus] = _T("");
		m_vbRelayCkStatus[m_nRelayCkFocus] = FALSE;
	}
}


void CCtrlSet::ValueChangedBlRelayck(LPCTSTR strNew)
{
	CString strTem;
	strTem = m_BL_edRelayCk.GetValueText();
	strTem.MakeUpper();
	m_BL_edRelayCk.SetValueText(strTem);
	// TODO: 在此处添加消息处理程序代码
}


void CCtrlSet::LBtClickedBlRelaydpok(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	if (m_BL_edRelayDp.GetValueText() != _T(""))
	{
		CString strTem;
		CString strTemName;

		strTem = m_BL_edRelayDp.GetValueText();
		strTemName = m_BL_edRelayDpName.GetValueText();

		strTem.Append(_T(";"));
		strTemName.Append(_T(";"));

		vector<CString> vstrTem;
		vector<CString> vstrTemName;

		vstrTem = m_ValueCalculate.CutString(strTem, ';');
		vstrTemName = m_ValueCalculate.CutString(strTemName, ';');

		if (vstrTem.size() != vstrTemName.size())
		{
			MsgBox.ShowMsg(_T("继电器输入数量和继电器标志数量不等"), _T("ERROR"), MB_ICONERROR | MB_OK);
			m_vbRelayDpStatus[m_nRelayDpFocus] = FALSE;
			return;
		}

		for (size_t i = 0; i < vstrTem.size(); i++)
		{
			if (vstrTem[i][0] != 'M')
			{
				MsgBox.ShowMsg(_T("继电器输入错误"), _T("ERROR"), MB_ICONERROR | MB_OK);
				m_vbRelayDpStatus[m_nRelayDpFocus] = FALSE;
				return;
			}
			for (int j = 1; j < vstrTem[i].GetLength(); j++)
			{
				if ((vstrTem[i][j] < '0') || (vstrTem[i][j] > '9'))
				{
					MsgBox.ShowMsg(_T("继电器输入错误"), _T("ERROR"), MB_ICONERROR | MB_OK);
					m_vbRelayDpStatus[m_nRelayDpFocus] = FALSE;
					return;
				}
			}
			vstrTem[i].Delete(0, 1);
			int nSub = _ttoi(m_strCoilEnd) - _ttoi(m_strCoilStart);
			if ((_ttoi(vstrTem[i]) - _ttoi(m_strCoilPos)) > nSub)
			{
				MsgBox.ShowMsg(_T(" M 線圈超出設置範圍"), _T("ERROR"), MB_ICONERROR | MB_OK);
				m_vbRelayDpStatus[m_nRelayDpFocus] = FALSE;
				return;
			}
		}

		if (m_BL_edRelayDpCaption.GetValueText() != _T(""))
		{
			m_vbRelayDpStatus[m_nRelayDpFocus] = TRUE;
			m_vstrRelayDp[m_nRelayDpFocus] = m_BL_edRelayDp.GetValueText();
			m_vstrRelayDpName[m_nRelayDpFocus] = m_BL_edRelayDpName.GetValueText();
			m_vstrRelayDpCaption[m_nRelayDpFocus] = m_BL_edRelayDpCaption.GetValueText();
			m_BL_btRelayDpStatus[m_nRelayDpFocus].SetCtrlCaption(m_vstrRelayDpCaption[m_nRelayDpFocus]);
		}
		else
		{
			m_vbRelayDpStatus[m_nRelayDpFocus] = FALSE;
			MsgBox.ShowMsg(_T("未输入勾选名称"), _T("ERROR"), MB_ICONERROR | MB_OK);
		}
	}
	else
	{
		m_vstrRelayDp[m_nRelayDpFocus] = _T("");
		m_vstrRelayDpName[m_nRelayDpFocus] = _T("");
		m_vstrRelayDpCaption[m_nRelayDpFocus] = _T("");
		m_vbRelayDpStatus[m_nRelayDpFocus] = FALSE;
	}
}


void CCtrlSet::ValueChangedBlRelaydrop(LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CString strTem;
	strTem = m_BL_edRelayDp.GetValueText();
	strTem.MakeUpper();
	m_BL_edRelayDp.SetValueText(strTem);
	// TODO: 在此处添加消息处理程序代码
}





void CCtrlSet::LBtClickedBlbtsavectrl(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Ctr"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Ctr Files(*.Par)|*.Ctr|All File(*.*)|*.*||"),this);
	dlgFile.m_pOFN->lpstrTitle = _T("文件保存");
	if (IDOK == dlgFile.DoModal())
	{
		strPath = dlgFile.GetPathName();
	}
	else
	{
		return;
	}
	CFile file;
	CFileException FileEX;
	if (!file.Open(strPath, CFile::modeWrite| CFile::modeCreate,&FileEX))
	{
		FileEX.ReportError();
		return;
	}	
	CArchive ar(&file,CArchive::store);
	Serialize(ar);
	ar.Flush();
	ar.Close();
	file.Close();
}


void CCtrlSet::LBtClickedBlbtloadctrl(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CFileDialog dlgFile(TRUE, _T("*.Ctr"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Ctr)|*.Ctr|All Files(*.*)|*.*||"), this);

	dlgFile.m_pOFN->lpstrTitle = _T("文件打開");

	if (IDCANCEL == dlgFile.DoModal())
	{
		return ;
	}
	CString strPath = dlgFile.GetPathName();
	CFile file;
	CFileException FileEx;

	if (!file.Open(strPath, CFile::modeRead, &FileEx))
	{
		FileEx.ReportError();
		return ;
	}
	CArchive ar(&file, CArchive::load);

	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}


void CCtrlSet::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		for (size_t i = 0; i < BT_RELAY_SUM; i++)
		{
			ar << m_vbRelayBtStatus[i];
			ar << m_vstrRelayBt[i];//按键中间继电器（Mxx）
			ar << m_vstrRelayBtName[i];//按键中间继电器名称
			ar << m_vnRelayBtMode[i];//按键中间继电器类型
			ar << m_vbIsRelayBtClickAuto[i];//按键中间继电器类型
		}

		for (size_t i = 0; i < CK_RELAY_SUM; i++)
		{
			ar << m_vbRelayCkStatus[i];
			ar << m_vstrRelayCk[i];//按键中间继电器（Mxx）
			ar << m_vstrRelayCkName[i];//按键中间继电器名称
		}

		for (size_t i = 0; i < DP_RELAY_SUM; i++)
		{
			ar << m_vbRelayDpStatus[i];
			ar << m_vstrRelayDp[i];//按键中间继电器（Mxx）
			ar << m_vstrRelayDpName[i];//按键中间继电器名称
			ar << m_vstrRelayDpCaption[i];//按键中间继电器名称
		}

		ar << m_bRelayBtStarStatus;
		ar << m_bRelayBtStopStatus;
		ar << m_bRelayBtResetStatus;
		ar << m_bRelayBtErrorStatus;
		ar << m_bRelayBtPauseStatus;
		ar << m_bRelaySwAutoStatus;
		ar << m_bRelaySwUnAutoStatus;

		ar << m_strRelayStar;
		ar << m_strRelayStop;
		ar << m_strRelayReset;
		ar << m_strRelayError;
		ar << m_strRelayPause;
		ar << m_strRelayAuto;
		ar << m_strRelayUnAuto;
	}
	else
	{	// loading code
		for (size_t i = 0; i < BT_RELAY_SUM; i++)
		{
			ar >> m_vbRelayBtStatus[i];
			ar >> m_vstrRelayBt[i];//按键中间继电器（Mxx）
			ar >> m_vstrRelayBtName[i];//按键中间继电器名称
			ar >> m_vnRelayBtMode[i];//按键中间继电器类型
			ar >> m_vbIsRelayBtClickAuto[i];//按键中间继电器类型
		}

		for (size_t i = 0; i < CK_RELAY_SUM; i++)
		{
			ar >> m_vbRelayCkStatus[i];
			ar >> m_vstrRelayCk[i];//按键中间继电器（Mxx）
			ar >> m_vstrRelayCkName[i];//按键中间继电器名称
		}

		for (size_t i = 0; i < DP_RELAY_SUM; i++)
		{
			ar >> m_vbRelayDpStatus[i];
			ar >> m_vstrRelayDp[i];//按键中间继电器（Mxx）
			ar >> m_vstrRelayDpName[i];//按键中间继电器名称
			ar >> m_vstrRelayDpCaption[i];//按键中间继电器名称
		}

		ar >> m_bRelayBtStarStatus;
		ar >> m_bRelayBtStopStatus;
		ar >> m_bRelayBtResetStatus;
		ar >> m_bRelayBtErrorStatus;
		ar >> m_bRelayBtPauseStatus;
		ar >> m_bRelaySwAutoStatus;
		ar >> m_bRelaySwUnAutoStatus;

		ar >> m_strRelayStar;
		ar >> m_strRelayStop;
		ar >> m_strRelayReset;
		ar >> m_strRelayError;
		ar >> m_strRelayPause;
		ar >> m_strRelayAuto;
		ar >> m_strRelayUnAuto;

		UpdateCtrlInfo();
	}
}



