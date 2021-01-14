// ControllerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ControllerDlg.h"
#include "afxdialogex.h"


// CControllerDlg 对话框

IMPLEMENT_DYNAMIC(CControllerDlg, CTpLayerWnd)

CControllerDlg::CControllerDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CControllerDlg::IDD, pParent)
	, m_nControllerDlgCounter(0)
	, m_nReportColCounter(0)
	, m_strInput(_T(""))
	, m_strControllerName(_T(""))
	, m_bUninterrupted(FALSE)
	, m_strRegistersStart(_T("")) //R起始地址
	, m_strRegistersEnd(_T(""))   //R結束地址
	, m_strRegistersStart1(_T(""))//D起始地址
	, m_strRegistersEnd1(_T(""))//D結束地址
	, m_strRegisters(_T(""))//R的switch狀態
	, m_strRegisters1(_T(""))//D的switch狀態
	, m_strRegistersPos(_T(""))//R的起始位
	, m_strRegistersPos1(_T(""))//D的起始位
	, m_strCoil(_T(""))//M的switch狀態
	, m_strCoilStart(_T("")) //M起始地址
	, m_strCoilEnd(_T(""))   //M結束地址
	, m_strCoilPos(_T(""))//M的起始位
	, m_bCollecting(FALSE)
	, m_bRelayBtStarStatus(FALSE)
	, m_bRelayBtStopStatus(FALSE)
	, m_bRelayBtResetStatus(FALSE)
	, m_bRelayBtErrorStatus(FALSE)
	, m_bRelayBtPauseStatus(FALSE)
	, m_bRelaySwAutoStatus(FALSE)
	, m_bRelaySwUnAutoStatus(FALSE)
	, m_bLocked(TRUE)
	, m_nAutoLockTime(30000)
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

CControllerDlg::CControllerDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nControllerDlgCounter(0)
	, m_nReportColCounter(0)
	, m_strInput(_T(""))
	, m_strControllerName(_T(""))
	, m_bUninterrupted(FALSE)
	, m_strRegistersStart(_T("")) //R起始地址
	, m_strRegistersEnd(_T(""))   //R結束地址
	, m_strRegistersStart1(_T(""))//D起始地址
	, m_strRegistersEnd1(_T(""))//D結束地址
	, m_strRegisters(_T(""))//R的switch狀態
	, m_strRegisters1(_T(""))//D的switch狀態
	, m_strRegistersPos(_T(""))//R的起始位
	, m_strRegistersPos1(_T(""))//D的起始位
	, m_strCoil(_T(""))//M的switch狀態
	, m_strCoilStart(_T("")) //M起始地址
	, m_strCoilEnd(_T(""))   //M結束地址
	, m_strCoilPos(_T(""))//M的起始位
	, m_bCollecting(FALSE)
	, m_bRelayBtStarStatus(FALSE)
	, m_bRelayBtStopStatus(FALSE)
	, m_bRelayBtResetStatus(FALSE)
	, m_bRelayBtErrorStatus(FALSE)
	, m_bRelayBtPauseStatus(FALSE)
	, m_bRelaySwAutoStatus(FALSE)
	, m_bRelaySwUnAutoStatus(FALSE)
	, m_bLocked(TRUE)
	, m_nAutoLockTime(30000)
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

CControllerDlg::~CControllerDlg()
{
	m_Excel.CloseExcelFile();
	m_Excel.ReleaseExcel();
}

void CControllerDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BL_ReportCollectList, m_BL_ReportCollectList);
	DDX_Control(pDX, IDC_BL_ControllerMenu, m_BL_ControllerMenu);
	for (int i = 0; i < BT_RELAY_SUM; i++)
	{
		DDX_Control(pDX, IDC_BL_btRelay_0 + i, m_BL_btRelay[i]);
	}
	for (int i = 0; i < CK_RELAY_SUM; i++)
	{
		DDX_Control(pDX, IDC_BL_ckRelay_0 + i, m_BL_ckRelay[i]);
	}
	for (int i = 0; i < DP_RELAY_SUM; i++)
	{
		DDX_Control(pDX, IDC_BL_DropRelay_0 + i, m_BL_dpRelay[i]);
	}

	DDX_Control(pDX, IDC_BL_AddCtrl, m_BL_btAddCtrl);
	DDX_Control(pDX, IDC_BL_ChangeCtrl, m_BL_btChangeCtrl);

	DDX_Control(pDX, IDC_BL_btRelayStar, m_BL_btRelayStar);
	DDX_Control(pDX, IDC_BL_btRelayStop, m_BL_btRelayStop);
	DDX_Control(pDX, IDC_BL_btRelayReset, m_BL_btRelayReset);
	DDX_Control(pDX, IDC_BL_btRelayError, m_BL_btRelayError);
	DDX_Control(pDX, IDC_BL_btRelayPause, m_BL_btRelayPause);
	DDX_Control(pDX, IDC_BL_swRelayAuto, m_BL_swRelayAuto);
	DDX_Control(pDX, IDC_BL_swRelayUnAuto, m_BL_swRelayUnAuto);
	DDX_Control(pDX, IDC_BL_swConnect, m_BL_swConnect);
	
}


BEGIN_MESSAGE_MAP(CControllerDlg, CTpLayerWnd)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_STARTCOLLECT, &CControllerDlg::OnStartCollect)
	ON_MESSAGE(WM_STOPCOLLECT, &CControllerDlg::OnStopCollect)
//	ON_WM_UNICHAR()
ON_WM_TIMER()
ON_MESSAGE(WM_COLLECTFINISH, &CControllerDlg::OnCollectFinish)
ON_MESSAGE(WM_COLLECTLOSE, &CControllerDlg::OnCollectLose)
ON_MESSAGE(WM_BT_REALY, &CControllerDlg::OnBtRealyMessage)
ON_MESSAGE(WM_CK_REALY, &CControllerDlg::OnCkRealy)
ON_MESSAGE(WM_WRITE_FINISH, &CControllerDlg::OnWriteFinish)
ON_MESSAGE(WM_DP_REALY, &CControllerDlg::OnDpRealy)
ON_MESSAGE(WM_PARAM_FINISH, &CControllerDlg::OnParamFinish)
ON_MESSAGE(WM_SMARTDOTS_FINISH, &CControllerDlg::OnSmartdotsFinish)
ON_MESSAGE(WM_UDEVISION_FINISH, &CControllerDlg::OnUdevisionFinish)
ON_MESSAGE(WM_SMARTROBOT_FINISH, &CControllerDlg::OnSmartrobotFinish)
ON_MESSAGE(WM_SMARTROBOT_STAR_UDEVISION, &CControllerDlg::OnSmartrobotStarUdevision)
ON_MESSAGE(WM_UDEVISION_FINISH_ROBOT, &CControllerDlg::OnUdevisionFinishRobot)
ON_MESSAGE(WM_SMARTLED_FINISH, &CControllerDlg::OnSmartledFinish)
ON_MESSAGE(WM_UDEOUTLOOK_FINISH_ROBOT, &CControllerDlg::OnUdeoutlookFinishRobot)
ON_MESSAGE(WM_UDEOUTLOOK_FINISH, &CControllerDlg::OnUdeoutlookFinish)
ON_MESSAGE(WM_SMARTROBOT_STAR_UDEOUTLOOK, &CControllerDlg::OnSmartrobotStarUdeoutlook)
ON_MESSAGE(WM_LOCK_STATE, &CControllerDlg::OnGetLockState)
ON_MESSAGE(WM_NEWSMARTDOTS_FINISH, &CControllerDlg::OnNewsSmartDotsFinish)
END_MESSAGE_MAP()


// CControllerDlg 消息处理程序
BOOL CControllerDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化

// 	m_BL_ReportCollectList.ResetRows(m_BL_ReportCollectList.GetRows(), TRUE);
// 
// 	m_BL_ReportCollectList.AppendColumn(_T("寄存器名"),DT_CENTER,120,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("數據地址"),DT_CENTER,100,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("數據位數"),DT_CENTER,100,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("數據名"),DT_CENTER,280,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("單位"),DT_CENTER,90,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("實時值"),DT_CENTER,100,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("是否重置"),DT_CENTER,100,FALSE);
// 	m_BL_ReportCollectList.AppendColumn(_T("重置值"),DT_CENTER,100,FALSE);
// 
// 
// 	for (int nCounter = 0; nCounter < m_BL_ReportCollectList.GetColumns(); nCounter++)//修改表头文字格式
// 	{
// 		m_BL_ReportCollectList.SetHeaderFont(nCounter, _T("Tahoma"), 150);
// 	}
// 
// 	m_BL_ReportCollectList.SetColumnReadOnly(1, TRUE);
// 	m_BL_ReportCollectList.SetColumnReadOnly(5, TRUE);
// 	m_BL_ReportCollectList.SetColumnReadOnly(6, TRUE);

	//m_Excel.Create(IDD_EXCEL, this);

	SetMainMenu();

	Invalidate(FALSE);

	m_CtrlSet.CreateBlendWnd(IDD_CTRLSET, this);

	m_MsgListDlg.CreateBlendWnd(IDD_MSGLISTDLG, this);
	m_MsgListDlg.CreateTopWnd(FALSE, FALSE);

	m_ParameterListDlg.CreateBlendWnd(IDD_PARAMETERLISTDLG, this);
	m_ParameterListDlg.CreateTopWnd(FALSE, FALSE);

	m_DataCollectionDlg.CreateBlendWnd(IDD_DATACOLLECTIONDLG, this);
	m_DataCollectionDlg.CreateTopWnd(FALSE, FALSE);

	m_ErrorListDlg.CreateBlendWnd(IDD_ERRORLISTDLG, this);
	m_ErrorListDlg.CreateTopWnd(FALSE, FALSE);

	m_SmartDotsListDlg.CreateBlendWnd(IDD_SMARTDOTSLISTDLG, this);
	m_SmartDotsListDlg.CreateTopWnd(FALSE, FALSE);
	
	m_SmartRobotListDlg.CreateBlendWnd(IDD_SMARTROBOTLISTDLG, this);
	m_SmartRobotListDlg.CreateTopWnd(FALSE, FALSE);
	
	m_AngleTestListDlg.CreateBlendWnd(IDD_ANGLETESTLISTDLG, this);
	m_AngleTestListDlg.CreateTopWnd(FALSE, FALSE);
	
	m_DiameterTestListDlg.CreateBlendWnd(IDD_DIAMETERTESTDLG, this);
	m_DiameterTestListDlg.CreateTopWnd(FALSE, FALSE);

	m_UDEOutlookListDlg.CreateBlendWnd(IDD_UDEOUTLOOKLISTDLG, this);
	m_UDEOutlookListDlg.CreateTopWnd(FALSE, FALSE);

	m_UDEVisionListDlg.CreateBlendWnd(IDD_UDEVISION, this);
	m_UDEVisionListDlg.CreateTopWnd(FALSE, FALSE);

	m_SmartLEDListDlg.CreateBlendWnd(IDD_SMARTLEDLISTDLG, this);
	m_SmartLEDListDlg.CreateTopWnd(FALSE, FALSE);

	m_NewSmartDotsDlg.CreateBlendWnd(IDD_NEWSMARTDOTS, this);
	m_NewSmartDotsDlg.CreateTopWnd(FALSE, FALSE);

	m_AutoLockTimeDlg.CreateBlendWnd(IDD_NEWSMARTDOTS, this);


	m_ParameterListDlg->m_pParameterListDlg = this;
	m_ErrorListDlg->m_pErrorListDlg = this;
	m_SmartDotsListDlg->m_pSmartDotsListDlg = this;
	m_UDEVisionListDlg->m_pUDEVisionListDlg = this;
	m_UDEOutlookListDlg->m_pUDEOutlookListDlg = this;
	m_SmartRobotListDlg->m_pSmartRobotListDlg = this;
	m_SmartLEDListDlg->m_pSmartLEDListDlg = this;
	m_AngleTestListDlg->m_pAngleTestListDlg = this;
	m_DiameterTestListDlg->m_pDiameterTestListDlg = this;
	m_NewSmartDotsDlg->m_pNewSmartDotsDlg = this;
	
	/*m_CtrlSet.CreateTopWnd(FALSE, FALSE);*/
	SetTimer(1, 1, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CControllerDlg::DrawTitle(CDC * pDC, CRect rcDraw)
{
	return;
}


void CControllerDlg::DrawElement(CDC * pDC, CRect rcDraw)
{
	CRect rcClient;
	GetClientRect(rcClient);
	CString strPart = GetTitle();
	CRect rcText;

	HDC hdc;
	CFont fontGrade;
	hdc = ::GetDC(this->m_hWnd);
	SetBkMode(hdc, TRANSPARENT);//寫入的字體為透明背景
	fontGrade.CreatePointFont(150, L"Tahoma");

	pDC->SelectObject(fontGrade);
	pDC->SetTextColor(RGB(0,255,255));
	rcText.TopLeft().x = rcClient.TopLeft().x + 15;
	rcText.TopLeft().y = rcClient.TopLeft().y + 10;
	rcText.BottomRight().x = rcClient.TopLeft().x + 200;
	rcText.BottomRight().y = rcClient.TopLeft().y + 200;
	pDC->DrawTextW(strPart, &rcText, DT_EDITCONTROL|DT_LEFT|DT_NOPREFIX);

	CPoint pt[4];
	pt[0].x = 200;
	pt[0].y = 0;
	pt[1].x = 240;
	pt[1].y = 40;
	pt[2].x = 800;
	pt[2].y = 40;
	pt[3].x = 840;
	pt[3].y = 0;
	CPen pen(PS_SOLID,1, RGB(0,255,255));
	pDC->SelectObject(pen);
	pDC->MoveTo(pt[0]);
	pDC->LineTo(pt[1]);
	pDC->LineTo(pt[2]);
	pDC->LineTo(pt[3]);

	CBrush br(RGB(64,64,64));

	
	pDC->SelectObject(br);

	pDC->BeginPath();

	pDC->MoveTo(pt[0].x + 1, pt[0].y);
	pDC->LineTo(pt[1].x, pt[1].y);
	pDC->LineTo(pt[2].x, pt[2].y);
	pDC->LineTo(pt[3].x, pt[3].y);

	pDC->EndPath();
	pDC->FillPath();

}

void CControllerDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}

void CControllerDlg::SetMainMenu()
{
	m_BL_ControllerMenu.AddPopByPosPosPos(0, 0, 0, 0, _T("參數管理"), _T("參數設置...;數據統計..."));

	m_BL_ControllerMenu.AddPopByPosPosPos(0, 1, 0, 0, _T("消息配置"), _T("報警消息...;焊點檢測消息...;機械手消息...;直徑檢測消息...;角度檢測消息...;外觀檢測消息...;視覺檢測...;LED試燈檢測...;新焊點檢測..."));

	m_BL_ControllerMenu.AddPopByPosPosPos(0, 2, 0, 0, _T("幫助"), _T("報警查看...;消息列表...;設置鎖定延時..."));

	
// 	m_BL_MainMenu.CheckItemByPos(_T("設置"), 3, m_bAutoRun);
// 	m_BL_MainMenu.CheckItemByPos(_T("設置"), 4, m_bMin2Tray);
// 	m_BL_MainMenu.CheckItemByPos(_T("設置"), 5, m_bAutoFindFile);
}

BEGIN_EVENTSINK_MAP(CControllerDlg, CTpLayerWnd)
	ON_EVENT(CControllerDlg, IDC_BL_ReportCollectList, 1, CControllerDlg::RowsChangedBlReportcollectlist, VTS_I4 VTS_I4 VTS_BOOL)
	ON_EVENT(CControllerDlg, IDC_BL_ReportCollectList, 5, CControllerDlg::LBtDbClickBlReportcollectlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CControllerDlg, IDC_BL_ReportCollectList, 2, CControllerDlg::ItemChangedBlReportcollectlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CControllerDlg, IDC_BL_ReportCollectList, 6, CControllerDlg::ItemEditFinishBlReportcollectlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CControllerDlg, IDC_BL_AddCtrl, 1, CControllerDlg::LBtClickedBlAddctrl, VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_ChangeCtrl, 1, CControllerDlg::LBtClickedBlChangectrl, VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_ControllerMenu, 2, CControllerDlg::ItemClickBlControllermenu, VTS_BSTR VTS_BSTR VTS_I2 VTS_BOOL VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_swConnect, 1, CControllerDlg::StatusChangedBlswconnect, VTS_BOOL)
	ON_EVENT(CControllerDlg, IDC_BL_swRelayAuto, 1, CControllerDlg::StatusChangedBlswrelayauto, VTS_BOOL)
	ON_EVENT(CControllerDlg, IDC_BL_swRelayUnAuto, 1, CControllerDlg::StatusChangedBlswrelayunauto, VTS_BOOL)
	ON_EVENT(CControllerDlg, IDC_BL_btRelayStar, 1, CControllerDlg::LBtClickedBlbtrelaystar, VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_btRelayStop, 1, CControllerDlg::LBtClickedBlbtrelaystop, VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_btRelayReset, 1, CControllerDlg::LBtClickedBlbtrelayreset, VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_btRelayPause, 1, CControllerDlg::LBtClickedBlbtrelaypause, VTS_I4)
	ON_EVENT(CControllerDlg, IDC_BL_btRelayError, 1, CControllerDlg::LBtClickedBlbtrelayerror, VTS_I4)
END_EVENTSINK_MAP()


void CControllerDlg::RowsChangedBlReportcollectlist(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: 在此处添加消息处理程序代码
	if (nOldRows < nNewRows)//如果是添加行
	{
		if (m_BL_ReportCollectList.GetCurRow() >= 0)
		{
			m_BL_ReportCollectList.SetItemNumberOnly(m_BL_ReportCollectList.GetCurRow(), 1, TRUE);
			m_BL_ReportCollectList.SetItemNumberOnly(m_BL_ReportCollectList.GetCurRow(), 2, TRUE);
			m_BL_ReportCollectList.SetItemText(m_BL_ReportCollectList.GetCurRow(), 2, _T("16"));
			m_BL_ReportCollectList.SetItemText(m_BL_ReportCollectList.GetCurRow(), 6, _T("●"));
			m_BL_ReportCollectList.SetItemText(m_BL_ReportCollectList.GetCurRow(), 7, _T("0"));
			m_BL_ReportCollectList.SetItemNumberOnly(m_BL_ReportCollectList.GetCurRow(), 7, TRUE);
		}
	}
}


void CControllerDlg::LBtDbClickBlReportcollectlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_ReportCollectList.SetDropDownData(_T("16;32"));
	}
	if (nCol == 6)
	{
		if (!m_bCollecting)
		{
			if (m_BL_ReportCollectList.GetItemText(nRow, nCol) == _T(""))
			{
				m_BL_ReportCollectList.SetItemText(nRow, nCol, _T("●"));
			}
			else
			{
				m_BL_ReportCollectList.SetItemText(nRow, nCol, _T(""));
			}
		}
	}
}


void CControllerDlg::ItemChangedBlReportcollectlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	CString strInfoOld;
	CString strInfoNew;
	strInfoOld = strOld;
	strInfoNew = strNew;
	strInfoNew.MakeUpper();
	strInfoOld.MakeUpper();
	if (nCol == 0)
	{
		if (strInfoNew.GetLength() == 1)
		{
			if (strInfoNew == _T("R"))
			{
				if (_ttoi(m_strRegisters) <= 0)
				{
					MsgBox.ShowMsg(_T("該設備未設置 R 類型緩存器數據讀取"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			if (strInfoNew == _T("D"))
			{
				if (_ttoi(m_strRegisters1) <= 0)
				{
					MsgBox.ShowMsg(_T("該設備未設置 D 類型緩存器數據讀取"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			if (strInfoNew == _T("M"))
			{
				if (_ttoi(m_strCoil) <= 0)
				{
					MsgBox.ShowMsg(_T("該設備未設置 M 類型線圈數據讀取"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			if((strInfoNew != _T("D")) && (strInfoNew != _T("R"))  && (strInfoNew != _T("M")))
			{
				CString strErrInfo;
				strErrInfo.Format(_T("該設備不支持 %s 類型緩存器數據讀取"), strInfoNew);
				MsgBox.ShowMsg(strErrInfo, _T("無法獲取"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			m_BL_ReportCollectList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_ReportCollectList.SetItemText(nRow, nCol, strInfoOld);
				}
				else
				{
					strAddress.Format(_T("%d"), _ttoi(strInfoNew) + _ttoi(m_strRegistersStart) - _ttoi(m_strRegistersPos));
					m_BL_ReportCollectList.SetItemText(nRow, nCol + 1, strAddress);
					m_BL_ReportCollectList.SetItemReadOnly(nRow, 2, FALSE);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_ReportCollectList.SetItemText(nRow, nCol, strInfoOld);
				}
				else
				{
					strAddress.Format(_T("%d"), _ttoi(strInfoNew) + _ttoi(m_strRegistersStart1) - _ttoi(m_strRegistersPos1));
					m_BL_ReportCollectList.SetItemText(nRow, nCol + 1, strAddress);
					m_BL_ReportCollectList.SetItemReadOnly(nRow, 2, FALSE);
				}
			}
			if (strInfoNew[0] == 'M')
			{
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strCoilEnd) - _ttoi(m_strCoilStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strCoilPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 M 線圈超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_ReportCollectList.SetItemText(nRow, nCol, strInfoOld);
				}
				else
				{
					strAddress.Format(_T("%d"), _ttoi(strInfoNew) + _ttoi(m_strCoilStart) - _ttoi(m_strCoilPos));
					m_BL_ReportCollectList.SetItemText(nRow, nCol + 1, strAddress);
					m_BL_ReportCollectList.SetItemReadOnly(nRow, 2, TRUE);
				}
			}
		}
	}
}


void CControllerDlg::LBtClickedBlGetreport(long nFlags)
{

}



void CControllerDlg::AutoDeletData()
{
	//m_pController->SendMessage(WM_COLLECTRUN, m_nControllerDlgCounter, WRITE_DATA);
}


void CControllerDlg::CollectData()
{
	SetTimer(0, 1 * TIME_RATIO, NULL);
}


CString CControllerDlg::GetExePath(void)  
{  
	CString strExePath;  
	GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);  
	strExePath.ReleaseBuffer();  
	strExePath = strExePath.Left(strExePath.ReverseFind(_T('\\')));  
	return strExePath;  
} 

void CControllerDlg::LoadFileData()
{
	CString strFileName;
	strFileName = GetExePath() + _T("\\Controller\\") + m_strControllerName + _T(".ini");

	GetPrivateProfileString(m_strControllerName,_T("strRegistersStart"),_T(""),m_strRegistersStart.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegistersEnd"),_T(""),m_strRegistersEnd.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegistersStart1"),_T(""),m_strRegistersStart1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegistersEnd1"),_T(""),m_strRegistersEnd1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegisters"),_T(""),m_strRegisters.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegisters1"),_T(""),m_strRegisters1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegistersPos"),_T(""),m_strRegistersPos.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strRegistersPos1"),_T(""),m_strRegistersPos1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strCoil"),_T(""),m_strCoil.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strCoilStart"),_T(""),m_strCoilStart.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strCoilEnd"),_T(""),m_strCoilEnd.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	GetPrivateProfileString(m_strControllerName,_T("strCoilPos"),_T(""),m_strCoilPos.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
	

	m_CtrlSet->m_strCoilStart = m_strCoilStart; //M起始地址
	m_CtrlSet->m_strCoilEnd = m_strCoilEnd;   //M結束地址
	m_CtrlSet->m_strCoilPos = m_strCoilPos;//M的起始位

	m_ParameterListDlg->m_strRegistersStart = m_strRegistersStart;
	m_ParameterListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_ParameterListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_ParameterListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_ParameterListDlg->m_strRegisters = m_strRegisters;
	m_ParameterListDlg->m_strRegisters1 = m_strRegisters1;
	m_ParameterListDlg->m_strRegistersPos = m_strRegistersPos;
	m_ParameterListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_DataCollectionDlg->m_strRegistersStart = m_strRegistersStart; 
	m_DataCollectionDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_DataCollectionDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_DataCollectionDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_DataCollectionDlg->m_strRegisters = m_strRegisters;
	m_DataCollectionDlg->m_strRegisters1 = m_strRegisters1;
	m_DataCollectionDlg->m_strRegistersPos = m_strRegistersPos;
	m_DataCollectionDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_ErrorListDlg->m_strRegistersStart = m_strRegistersStart;
	m_ErrorListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_ErrorListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_ErrorListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_ErrorListDlg->m_strRegisters = m_strRegisters;
	m_ErrorListDlg->m_strRegisters1 = m_strRegisters1;
	m_ErrorListDlg->m_strRegistersPos = m_strRegistersPos;
	m_ErrorListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_SmartDotsListDlg->m_strRegistersStart = m_strRegistersStart;
	m_SmartDotsListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_SmartDotsListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_SmartDotsListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_SmartDotsListDlg->m_strRegisters = m_strRegisters;
	m_SmartDotsListDlg->m_strRegisters1 = m_strRegisters1;
	m_SmartDotsListDlg->m_strRegistersPos = m_strRegistersPos;
	m_SmartDotsListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_UDEVisionListDlg->m_strRegistersStart = m_strRegistersStart;
	m_UDEVisionListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_UDEVisionListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_UDEVisionListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_UDEVisionListDlg->m_strRegisters = m_strRegisters;
	m_UDEVisionListDlg->m_strRegisters1 = m_strRegisters1;
	m_UDEVisionListDlg->m_strRegistersPos = m_strRegistersPos;
	m_UDEVisionListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_UDEOutlookListDlg->m_strRegistersStart = m_strRegistersStart;
	m_UDEOutlookListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_UDEOutlookListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_UDEOutlookListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_UDEOutlookListDlg->m_strRegisters = m_strRegisters;
	m_UDEOutlookListDlg->m_strRegisters1 = m_strRegisters1;
	m_UDEOutlookListDlg->m_strRegistersPos = m_strRegistersPos;
	m_UDEOutlookListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_SmartRobotListDlg->m_strRegistersStart = m_strRegistersStart;
	m_SmartRobotListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_SmartRobotListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_SmartRobotListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_SmartRobotListDlg->m_strRegisters = m_strRegisters;
	m_SmartRobotListDlg->m_strRegisters1 = m_strRegisters1;
	m_SmartRobotListDlg->m_strRegistersPos = m_strRegistersPos;
	m_SmartRobotListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_SmartLEDListDlg->m_strRegistersStart = m_strRegistersStart;
	m_SmartLEDListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_SmartLEDListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_SmartLEDListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_SmartLEDListDlg->m_strRegisters = m_strRegisters;
	m_SmartLEDListDlg->m_strRegisters1 = m_strRegisters1;
	m_SmartLEDListDlg->m_strRegistersPos = m_strRegistersPos;
	m_SmartLEDListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_AngleTestListDlg->m_strRegistersStart = m_strRegistersStart;
	m_AngleTestListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_AngleTestListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_AngleTestListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_AngleTestListDlg->m_strRegisters = m_strRegisters;
	m_AngleTestListDlg->m_strRegisters1 = m_strRegisters1;
	m_AngleTestListDlg->m_strRegistersPos = m_strRegistersPos;
	m_AngleTestListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_DiameterTestListDlg->m_strRegistersStart = m_strRegistersStart;
	m_DiameterTestListDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_DiameterTestListDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_DiameterTestListDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_DiameterTestListDlg->m_strRegisters = m_strRegisters;
	m_DiameterTestListDlg->m_strRegisters1 = m_strRegisters1;
	m_DiameterTestListDlg->m_strRegistersPos = m_strRegistersPos;
	m_DiameterTestListDlg->m_strRegistersPos1 = m_strRegistersPos1;

	m_NewSmartDotsDlg->m_strRegistersStart = m_strRegistersStart;
	m_NewSmartDotsDlg->m_strRegistersEnd = m_strRegistersEnd;
	m_NewSmartDotsDlg->m_strRegistersStart1 = m_strRegistersStart1;
	m_NewSmartDotsDlg->m_strRegistersEnd1 = m_strRegistersEnd1;
	m_NewSmartDotsDlg->m_strRegisters = m_strRegisters;
	m_NewSmartDotsDlg->m_strRegisters1 = m_strRegisters1;
	m_NewSmartDotsDlg->m_strRegistersPos = m_strRegistersPos;
	m_NewSmartDotsDlg->m_strRegistersPos1 = m_strRegistersPos1;
}


CString CControllerDlg::DateCalculate_GetSpan(COleDateTime TimeBegin, COleDateTime TimeEnd)
{
	COleDateTimeSpan ts = TimeEnd - TimeBegin;
	CString strTimeSpan;
	strTimeSpan.Format(_T("%f"),ts.m_span);
	return strTimeSpan;
}


CString CControllerDlg::DateCalculate_GetDate(CTime Time, int nTimeSpan, int nOffset)
{
	CString strTime;
	int nYear,nMonth,nDay;
	if (nOffset == DATE_BEFORE)
	{
		Time -= CTimeSpan( nTimeSpan, 0, 0, 0 );    //该函数第一个参数为相差的天数 
	}
	if (nOffset == DATE_AFTER)
	{
		Time += CTimeSpan( nTimeSpan, 0, 0, 0 );    //该函数第一个参数为相差的天数 
	}
	 
	nYear = Time.GetYear();
	nMonth = Time.GetMonth();
	nDay = Time.GetDay();

	CString strPart_1;
	CString strPart_2;
	CString strPart_3;
	strPart_1.Format(_T("%d"), nYear);
	if (strPart_1.GetLength() == 1)
	{
		strPart_1.Insert(0, '0');
	}
	strPart_2.Format(_T("%d"), nMonth);
	if (strPart_2.GetLength() == 1)
	{
		strPart_2.Insert(0, '0');
	}
	strPart_3.Format(_T("%d"), nDay);
	if (strPart_3.GetLength() == 1)
	{
		strPart_3.Insert(0, '0');
	}
	strTime = strPart_1 + strPart_2 + strPart_3;

	return strTime;

}

void CControllerDlg::GetSystemTime(int & nYear, int & nMouth, int & nDay, int & nHour, int & nMinute, int & nSeconds)
{
	CTime time = CTime::GetCurrentTime(); ///构造CTime对象  
	nYear = time.GetYear(); ///年  
	nMouth = time.GetMonth(); ///月  
	nDay = time.GetDay(); ///日 
	nHour = time.GetHour();
	nMinute = time.GetMinute();
	nSeconds = time.GetSecond();
}

void CControllerDlg::GetSystemTime(CString & strYear, CString & strMouth, CString & strDay, CString & strHour, CString & strMinute, CString & strSeconds)
{
	int nYear = 0;
	int nMonth = 0;
	int nDay = 0;
	int nHour = 0;
	int nMinute = 0;
	int nSeconds = 0;

	GetSystemTime(nYear, nMonth, nDay, nHour, nMinute, nSeconds);

	strYear.Format(_T("%d"), nYear);
	strMouth.Format(_T("%d"), nMonth);
	strDay.Format(_T("%d"), nDay);
	strHour.Format(_T("%d"), nHour);
	strMinute.Format(_T("%d"), nMinute);
	strSeconds.Format(_T("%d"), nSeconds);

	while (strMouth.GetLength() < 2)
	{
		strMouth.Insert(0, '0');
	}

	while (strDay.GetLength() < 2)
	{
		strDay.Insert(0, '0');
	}
	while (strHour.GetLength() < 2)
	{
		strHour.Insert(0, '0');
	}
	while (strMinute.GetLength() < 2)
	{
		strMinute.Insert(0, '0');
	}
	while (strMinute.GetLength() < 2)
	{
		strMinute.Insert(0, '0');
	}
	while (strSeconds.GetLength() < 2)
	{
		strSeconds.Insert(0, '0');
	}

}

void CControllerDlg::UpdateMsgList()
{
	CString strShowStatus;//顯示狀態
	CString strData;//數據繼電器或緩存器
	CString strDataName;//數據名稱
	CString strAddress;//數據地址
	CString strLockStatus;//是否鎖定
	CString strDataByte;// 數據位數
	CString strRelayMode;//繼電器類型（用於DropDowm）
	m_MsgListDlg->m_BL_MsgList.ResetRows(0, FALSE);//清除消息列表中的內容
	int nRowsCounter = -1;//行計數
	for (int i = 0; i < 7; i++)
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		nRowsCounter++;
		switch (i)
		{
		case 0:
			strData = m_strRelayAuto;
			strAddress = UpdateMsgListAddress(m_strRelayAuto);
			strDataName = _T("自動");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelaySwAutoStatus);
			strLockStatus = _T("Lock");
			break;
		case 1:
			strData = m_strRelayUnAuto;
			strAddress = UpdateMsgListAddress(m_strRelayUnAuto);
			strDataName = _T("手動");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelaySwUnAutoStatus);
			strLockStatus = _T("Lock");
			break;
		case 2:
			strData = m_strRelayStar;
			strAddress = UpdateMsgListAddress(m_strRelayStar);
			strDataName = _T("啟動");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelayBtStarStatus);
			strLockStatus = _T("UnLock");
			break;
		case 3:
			strData = m_strRelayStop;
			strAddress = UpdateMsgListAddress(m_strRelayStop);
			strDataName = _T("停止");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelayBtStopStatus);
			strLockStatus = _T("UnLock");
			break;
		case 4:
			strData = m_strRelayReset;
			strAddress = UpdateMsgListAddress(m_strRelayReset);
			strDataName = _T("復位");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelayBtResetStatus);
			strLockStatus = _T("UnLock");
			break;
		case 5:
			strData = m_strRelayError;
			strAddress = UpdateMsgListAddress(m_strRelayError);
			strDataName = _T("故障");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelayBtErrorStatus);
			strLockStatus = _T("Lock");
			break;
		case 6:
			strData = m_strRelayPause;
			strAddress = UpdateMsgListAddress(m_strRelayPause);
			strDataName = _T("暫停");
			strDataByte = _T("16");
			strShowStatus.Format(_T("%d"), m_bRelayBtPauseStatus);
			strLockStatus = _T("Lock");
			break;
		default:
			break;
		}
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 1, strData);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 4, strDataName);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 7, strLockStatus);
	}
	for (int i = 0; i < BT_RELAY_SUM; i++)
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		nRowsCounter++;
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 1, m_vstrRelayBt[i]);
		strAddress = UpdateMsgListAddress(m_vstrRelayBt[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 4, m_vstrRelayBtName[i]);
		strShowStatus.Format(_T("%d"), m_vbRelayBtStatus[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 6, strShowStatus);
		if (m_vnRelayBtMode[i] == 1)
		{
			strLockStatus = _T("Lock");
		}
		if (m_vnRelayBtMode[i] == 2)
		{
			strLockStatus = _T("Unlock");
		}
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 7, strLockStatus);
		if (m_vbIsRelayBtClickAuto[i])
		{
			m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 8, _T("Auto"));//自動狀態下仍可以使用按鈕
		}
	}
	for (int i = 0; i < CK_RELAY_SUM; i++)
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		nRowsCounter++;
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 1, m_vstrRelayCk[i]);
		strAddress = UpdateMsgListAddress(m_vstrRelayCk[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 4, m_vstrRelayCkName[i]);
		strShowStatus.Format(_T("%d"), m_vbRelayCkStatus[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 6, strShowStatus);
		strLockStatus = _T("Lock");
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 7, strLockStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 8, _T("Check"));
	}
	for (int i = 0; i < DP_RELAY_SUM; i++)
	{
		vector<CString> vstrTemRelayDp;
		vector<CString> vstrTemRelayDpName;

		vstrTemRelayDp.clear();
		vstrTemRelayDpName.clear();

		CString strTemRelayDp;
		CString strTemRelayName;
		CString strTem;
		strTemRelayDp = m_vstrRelayDp[i];
		strTemRelayName = m_vstrRelayDpName[i];
		if (!strTemRelayDp.IsEmpty())
		{
			strTemRelayDp.Append(_T(";"));
			strTemRelayName.Append(_T(";"));
			vstrTemRelayDp = m_ValueCalculate.CutString(strTemRelayDp, ';');
			vstrTemRelayDpName = m_ValueCalculate.CutString(strTemRelayName, ';');
			for (size_t j = 0; j < vstrTemRelayDp.size(); j++)
			{
				m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
				nRowsCounter++;
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 1, vstrTemRelayDp[j]);
				strAddress = UpdateMsgListAddress(vstrTemRelayDp[j]);
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 2, strAddress);
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 3, _T("16"));
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 4, vstrTemRelayDpName[j]);
				strShowStatus.Format(_T("%d"), m_vbRelayDpStatus[i]);
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 6, strShowStatus);
				strLockStatus = _T("Lock");
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 7, strLockStatus);
				strTem.Format(_T("Drop%d"), i);
				m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 8, strTem);
			}
		}
	}
}


void CControllerDlg::UpdateParameterList()
{
	CString strShowStatus;//顯示狀態
	CString strData;//數據繼電器或緩存器
	CString strDataName;//數據名稱
	CString strAddress;//數據地址
	CString strLockStatus;//是否鎖定
	CString strDataByte;// 數據位數
	CString strRelayMode;//繼電器類型（用於DropDowm）

	m_vstrParameter.clear();
	m_vstrParameterName.clear();
	m_vstrParameterByte.clear();
	m_vstrParameterPt.clear();
	m_vstrParameterUnit.clear();

	for (int i = m_ParameterListDlg->m_BL_ParameterList.GetRows() - 1; i >= 0 ; i--)
	{
		if ((m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 1) == _T("")) || (m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 2) == _T("")))
		{
			m_ParameterListDlg->m_BL_ParameterList.DeleteRow(i, FALSE);
		}
		else
		{
			if (m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 1).GetLength() <= 1)
			{
				m_ParameterListDlg->m_BL_ParameterList.DeleteRow(i, FALSE);
			}
		}
	}

	for (int i = 0; i < m_ParameterListDlg->m_BL_ParameterList.GetRows(); i++)
	{
		m_vstrParameter.push_back(m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 1));
		m_vstrParameterByte.push_back(m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 2));
		m_vstrParameterName.push_back(m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 3));
		m_vstrParameterPt.push_back(m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 4));
		m_vstrParameterUnit.push_back(m_ParameterListDlg->m_BL_ParameterList.GetItemText(i, 5));
	}

	for (size_t i = 0; i < m_vstrParameter.size(); i++)
	{
		int nRowsCounter = m_MsgListDlg->m_BL_MsgList.GetRows() - 1;
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		nRowsCounter++;
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 1, m_vstrParameter[i]);
		strAddress = UpdateMsgListAddress(m_vstrParameter[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 3, m_vstrParameterByte[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 4, m_vstrParameterName[i]);
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 6, strShowStatus);
	}
	
}

void CControllerDlg::UpdateDataCollectionList()
{
	CString strShowStatus;//顯示狀態
	CString strData;//數據繼電器或緩存器
	CString strDataName;//數據名稱
	CString strAddress;//數據地址
	CString strLockStatus;//是否鎖定
	CString strDataByte;// 數據位數
	CString strRelayMode;//繼電器類型（用於DropDowm）

	m_vstrDataCollection.clear();
	m_vstrDataCollectionName.clear();
	m_vstrDataCollectionByte.clear();
	m_vstrDataCollectionPt.clear();
	m_vstrDataCollectionUnit.clear();

	for (int i = m_DataCollectionDlg->m_BL_DataCollectionList.GetRows() - 1; i >= 0 ; i--)
	{
		if ((m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 1) == _T("")) || (m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 2) == _T("")))
		{
			m_DataCollectionDlg->m_BL_DataCollectionList.DeleteRow(i, FALSE);
		}
		else
		{
			if (m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 1).GetLength() <= 1)
			{
				m_DataCollectionDlg->m_BL_DataCollectionList.DeleteRow(i, FALSE);
			}
		}
	}

	for (int i = 0; i < m_DataCollectionDlg->m_BL_DataCollectionList.GetRows(); i++)
	{
		m_vstrDataCollection.push_back(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 1));
		m_vstrDataCollectionByte.push_back(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 2));
		m_vstrDataCollectionName.push_back(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 3));
		m_vstrDataCollectionPt.push_back(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 4));
		m_vstrDataCollectionUnit.push_back(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(i, 5));
	}

	for (size_t i = 0; i < m_vstrDataCollection.size(); i++)
	{
		int nRowsCounter = m_MsgListDlg->m_BL_MsgList.GetRows() - 1;
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		nRowsCounter++;
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 1, m_vstrDataCollection[i]);
		strAddress = UpdateMsgListAddress(m_vstrDataCollection[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 3, m_vstrDataCollectionByte[i]);
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 4, m_vstrDataCollectionName[i]);
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(nRowsCounter, 6, strShowStatus);
	}
}

void CControllerDlg::UpdateErrorList()
{
	CString strAddress;//數據地址
	CString strShowStatus;//顯示狀態
	for (int i = m_ErrorListDlg->m_BL_ErrorList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_ErrorListDlg->m_BL_ErrorList.GetItemText(i, 0) == _T("")) || (m_ErrorListDlg->m_BL_ErrorList.GetItemText(i, 1) == _T("")))
		{
			m_ErrorListDlg->m_BL_ErrorList.DeleteRow(i, FALSE);
		}
	}
	if ((m_ErrorListDlg->m_BL_edErrorCode.GetValueText().GetLength() > 1) && (m_ErrorListDlg->m_BL_ErrorList.GetRows() > 0))
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_ErrorListDlg->m_BL_edErrorCode.GetValueText());
		strAddress = UpdateMsgListAddress(m_ErrorListDlg->m_BL_edErrorCode.GetValueText());
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("報警緩存器"));
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));
	}
}


void CControllerDlg::UpdateSmartDotsList()
{
	CString strAddress;//數據地址
	CString strShowStatus;//顯示狀態
	for (int i = m_SmartDotsListDlg->m_BL_SmartDotsList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 0) != _T("")) && (m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 1) != _T("")) &&
			(m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 2) != _T("")) && (m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 6) != _T("")))
		{
			BOOL bIsInpu = FALSE;//有選擇模板
			for (int j = 3; j < 6; j++)
			{
				if (m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, j) != _T(""))
				{
					bIsInpu = TRUE;
					break;
				}
			}
			if (!bIsInpu)
			{
				m_SmartDotsListDlg->m_BL_SmartDotsList.DeleteRow(i, FALSE);
			}
			if (m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 6).GetLength() <= 1)
			{
				m_SmartDotsListDlg->m_BL_SmartDotsList.DeleteRow(i, FALSE);
			}
		}
		else
		{
			m_SmartDotsListDlg->m_BL_SmartDotsList.DeleteRow(i, FALSE);
		}
	}
	if ((m_SmartDotsListDlg->m_BL_edSmartDotsCode.GetValueText().GetLength() > 1) && (m_SmartDotsListDlg->m_BL_SmartDotsList.GetRows() > 0))
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_SmartDotsListDlg->m_BL_edSmartDotsCode.GetValueText());
		strAddress = UpdateMsgListAddress(m_SmartDotsListDlg->m_BL_edSmartDotsCode.GetValueText());
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("焊點檢測緩存器"));
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));

		for (int i = 0; i < m_SmartDotsListDlg->m_BL_SmartDotsList.GetRows(); i++)
		{
			m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 6));
			strAddress = UpdateMsgListAddress(m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(i, 6));
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("焊點結果緩存器"));
			strShowStatus = _T("0");
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		}
	}	
}

void CControllerDlg::UpdateNewSmartDots()
{
	CString strAddress;//數據地址
	CString strShowStatus;//顯示狀態
	for (int i = m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 0) != _T("")) && (m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 1) != _T("")) &&
			(m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 2) != _T("")) && (m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 7) != _T("")))
		{
			BOOL bIsInpu = FALSE;//有選擇模板
			for (int j = 3; j < 7; j++)
			{
				if (m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, j) != _T(""))
				{
					bIsInpu = TRUE;
					break;
				}
			}
			if (!bIsInpu)
			{
				m_NewSmartDotsDlg->m_BL_NewSmartDotsList.DeleteRow(i, FALSE);
			}
			if (m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 7).GetLength() <= 1)
			{
				m_NewSmartDotsDlg->m_BL_NewSmartDotsList.DeleteRow(i, FALSE);
			}
		}
		else
		{
			m_NewSmartDotsDlg->m_BL_NewSmartDotsList.DeleteRow(i, FALSE);
		}
	}
	if ((m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.GetValueText().GetLength() > 1) && (m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetRows() > 0))
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.GetValueText());
		strAddress = UpdateMsgListAddress(m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.GetValueText());
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("新焊點檢測緩存器"));
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));

		for (int i = 0; i < m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetRows(); i++)
		{
			m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 7));
			strAddress = UpdateMsgListAddress(m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(i, 7));
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("新焊點結果緩存器"));
			strShowStatus = _T("0");
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		}
	}
}

void CControllerDlg::UpdateUDEVisionList()
{
 	CString strAddress;//數據地址
 	CString strShowStatus;//顯示狀態
 	for (int i = m_UDEVisionListDlg->m_BL_UDEVisionList.GetRows() - 1; i >= 0; i--)
 	{
 		if ((m_UDEVisionListDlg->m_BL_UDEVisionList.GetItemText(i, 0) == _T("")) || (m_UDEVisionListDlg->m_BL_UDEVisionList.GetItemText(i, 1) == _T("")))
 		{
			m_UDEVisionListDlg->m_BL_UDEVisionList.DeleteRow(i, FALSE);
 		}
		else
		{
			BOOL bIsInput = FALSE;
			for (int j = 2; j < 23; j++)
			{
				if (m_UDEVisionListDlg->m_BL_UDEVisionList.GetItemText(i, j) != _T(""))
				{
					bIsInput = TRUE;
					break;
				}
			}
			if (!bIsInput)
			{
				m_UDEVisionListDlg->m_BL_UDEVisionList.DeleteRow(i, FALSE);
			}
		}
 	}
 	if ((m_UDEVisionListDlg->m_BL_edUDEVisionCode.GetValueText().GetLength() > 1) && (m_UDEVisionListDlg->m_BL_UDEVisionList.GetRows() > 0))
 	{
 		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
 		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_UDEVisionListDlg->m_BL_edUDEVisionCode.GetValueText());
 		strAddress = UpdateMsgListAddress(m_UDEVisionListDlg->m_BL_edUDEVisionCode.GetValueText());
 		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
 		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
 		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("外觀檢測緩存器"));
 		strShowStatus = _T("1");
 		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));

		for (int i = 0; i < 21; i++)
		{
			if (m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].GetValueText().GetLength() > 1)
			{
				m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].GetValueText());
				strAddress = UpdateMsgListAddress(m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].GetValueText());
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("外觀結果緩存器"));
				strShowStatus = _T("0");
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);

				CString strTem;
				strTem = m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].GetValueText();
				strTem.Delete(0, 1);
				strTem.Format(_T("%d"), _ttoi(strTem) + 1);
				strTem.Insert(0, m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].GetValueText()[0]);
				m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, strTem);
				strAddress = UpdateMsgListAddress(strTem);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("外觀完成緩存器"));
				strShowStatus = _T("0");
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
			}
		}
 	}
 	
}

void CControllerDlg::UpdateSmartRobotList()
{
	CString strAddress;//數據地址
	CString strShowStatus;//顯示狀態
	for (int i = m_SmartRobotListDlg->m_BL_SendSmartRobotList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_SmartRobotListDlg->m_BL_SendSmartRobotList.GetItemText(i, 0) == _T("")) || (m_SmartRobotListDlg->m_BL_SendSmartRobotList.GetItemText(i, 1) == _T(""))
			|| (m_SmartRobotListDlg->m_BL_SendSmartRobotList.GetItemText(i, 2) == _T("")))
		{
			m_SmartRobotListDlg->m_BL_SendSmartRobotList.DeleteRow(i, FALSE);
		}
	}
	if ((m_SmartRobotListDlg->m_BL_edSmartRobotCode.GetValueText().GetLength() > 1) && (m_SmartRobotListDlg->m_BL_SendSmartRobotList.GetRows() > 0))
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_SmartRobotListDlg->m_BL_edSmartRobotCode.GetValueText());
		strAddress = UpdateMsgListAddress(m_SmartRobotListDlg->m_BL_edSmartRobotCode.GetValueText());
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("機械手緩存器"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
	}
	else
	{
		//return;
	}

	for (int i = m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 0) == _T("")) || (m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 1) == _T(""))
			|| (m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 2) == _T("")) || (m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 4) == _T("")))
		{
			m_SmartRobotListDlg->m_BL_GetSmartRobotList.DeleteRow(i, FALSE);
		}
		else
		{
			if (m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 2) == _T("0"))
			{
				if (m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 5).GetLength() <= 1)
				{
					m_SmartRobotListDlg->m_BL_GetSmartRobotList.DeleteRow(i, FALSE);
				}
				else
				{
					m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
					m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 5));
					strAddress = UpdateMsgListAddress(m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(i, 5));
					m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
					m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
					m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("機械手返回緩存器"));
					strShowStatus = _T("0");
					m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
				}
			}
		}
	}
}


void CControllerDlg::UpdateSmartLEDList()
{
	CString strAddress;//數據地址
	CString strShowStatus;//顯示狀態
	for (int i = m_SmartLEDListDlg->m_BL_SmartLEDList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 0) != _T("")) && (m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 1) != _T("")) &&
			(m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 2) != _T("")))
		{
			if (m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 2).GetLength() <= 1)
			{
				m_SmartLEDListDlg->m_BL_SmartLEDList.DeleteRow(i, FALSE);
			}
			else
			{
				CString strTem;
				//strTem.Format(_T("(%d)"), _ttoi(m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 0)) + 1);
				//m_SmartLEDListDlg->m_BL_SmartLEDList.SetItemText(i, 0, m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 0) + strTem);
			}
		}
		else
		{
			m_SmartLEDListDlg->m_BL_SmartLEDList.DeleteRow(i, FALSE);
		}
	}
	if ((m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText().GetLength() > 1) && (m_SmartLEDListDlg->m_BL_SmartLEDList.GetRows() > 0))
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText());
		strAddress = UpdateMsgListAddress(m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText());
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("LED檢測緩存器"));
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));


		CString strTem;
		strTem = m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText();
		strTem.Delete(0, 1);
		strTem.Format(_T("%d"), _ttoi(strTem) + 1);
		strTem.Insert(0, m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText()[0]);
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, strTem);
		strAddress = UpdateMsgListAddress(strTem);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("LED完成緩存器"));
		strShowStatus = _T("0");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);


		for (int i = 0; i < m_SmartLEDListDlg->m_BL_SmartLEDList.GetRows(); i++)
		{
			m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 2));
			strAddress = UpdateMsgListAddress(m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(i, 2));
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("LED結果緩存器"));
			strShowStatus = _T("0");
			m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		}
	}
}

void CControllerDlg::UpdateUDEOutlookList()
{
	CString strAddress;//數據地址
	CString strShowStatus;//顯示狀態
	for (int i = m_UDEOutlookListDlg->m_BL_UDEOutlookList.GetRows() - 1; i >= 0; i--)
	{
		if ((m_UDEOutlookListDlg->m_BL_UDEOutlookList.GetItemText(i, 0) == _T("")) || (m_UDEOutlookListDlg->m_BL_UDEOutlookList.GetItemText(i, 1) == _T("")))
		{
			m_UDEOutlookListDlg->m_BL_UDEOutlookList.DeleteRow(i, FALSE);
		}
		else
		{
			BOOL bIsInput = FALSE;
			for (int j = 2; j < 12; j++)
			{
				if (m_UDEOutlookListDlg->m_BL_UDEOutlookList.GetItemText(i, j) != _T(""))
				{
					bIsInput = TRUE;
					break;
				}
			}
			if (!bIsInput)
			{
				m_UDEOutlookListDlg->m_BL_UDEOutlookList.DeleteRow(i, FALSE);
			}
		}
	}
	if ((m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText().GetLength() > 1) && (m_UDEOutlookListDlg->m_BL_UDEOutlookList.GetRows() > 0))
	{
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText());
		strAddress = UpdateMsgListAddress(m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText());
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("視覺檢測緩存器"));
		strShowStatus = _T("1");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 8, _T("消息轉換"));

		CString strTem;
		strTem = m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText();
		strTem.Delete(0, 1);
		strTem.Format(_T("%d"), _ttoi(strTem) + 1);
		strTem.Insert(0, m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText()[0]);
		m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, strTem);
		strAddress = UpdateMsgListAddress(strTem);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("16"));
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("視覺完成緩存器"));
		strShowStatus = _T("0");
		m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);

		for (int i = 0; i < 10; i++)
		{
			if (m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].GetValueText().GetLength() > 1)
			{
				m_MsgListDlg->m_BL_MsgList.AppendRow(FALSE);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 1, m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].GetValueText());
				strAddress = UpdateMsgListAddress(m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].GetValueText());
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 2, strAddress);
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 3, _T("32"));
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 4, _T("視覺結果緩存器"));
				strShowStatus = _T("0");
				m_MsgListDlg->m_BL_MsgList.SetItemText(m_MsgListDlg->m_BL_MsgList.GetCurRow(), 6, strShowStatus);
			}
		}
	}
}


void CControllerDlg::UpdateAngleTestList()
{

}


void CControllerDlg::UpdateDiameterTestList()
{

}


CString CControllerDlg::UpdateMsgListAddress(CString strRelayMode)
{
	CString strAddress;
	if (strRelayMode[0] == 'R')
	{
		strRelayMode.Delete(0, 1);
		int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
		strAddress.Format(_T("%d"), _ttoi(strRelayMode) + _ttoi(m_strRegistersStart) - _ttoi(m_strRegistersPos));	
	}
	if (strRelayMode[0] == 'D')
	{
		strRelayMode.Delete(0, 1);
		int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
		strAddress.Format(_T("%d"), _ttoi(strRelayMode) + _ttoi(m_strRegistersStart1) - _ttoi(m_strRegistersPos1));
	}
	if (strRelayMode[0] == 'M')
	{
		strRelayMode.Delete(0, 1);
		int nSub = _ttoi(m_strCoilEnd) - _ttoi(m_strCoilStart);
		strAddress.Format(_T("%d"), _ttoi(strRelayMode) + _ttoi(m_strCoilStart) - _ttoi(m_strCoilPos));
	}
	return strAddress;
}

void CControllerDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code	
// 		ar << m_BL_ReportCollectList.GetRows();
// 		for (int nRowcounter = 0; nRowcounter < m_BL_ReportCollectList.GetRows(); nRowcounter++)
// 		{
// 			for (int nColcounter = 0; nColcounter < 8; nColcounter++)
// 			{
// 				ar << m_BL_ReportCollectList.GetItemText(nRowcounter, nColcounter);
// 			}
// 		}
		ar << m_bCollecting;
		for (size_t i = 0;i < BT_RELAY_SUM; i++)
		{
			ar << m_vbRelayBtStatus[i];
			ar << m_vstrRelayBt[i];
			ar << m_vstrRelayBtName[i];
			ar << m_vnRelayBtMode[i];
			ar << m_vbIsRelayBtClickAuto[i];
		}
		for (size_t i = 0;i < CK_RELAY_SUM; i++)
		{
			ar << m_vbRelayCkStatus[i];
			ar << m_vstrRelayCk[i];
			ar << m_vstrRelayCkName[i];
		}
		for (size_t i = 0;i < DP_RELAY_SUM; i++)
		{
			ar << m_vbRelayDpStatus[i];
			ar << m_vstrRelayDp[i];
			ar << m_vstrRelayDpName[i];
			ar << m_vstrRelayDpCaption[i];
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

		ar << m_vstrParameter.size();
		for (size_t i = 0;i < m_vstrParameter.size(); i++)
		{
			ar << m_vstrParameter[i];
			ar << m_vstrParameterByte[i];
			ar << m_vstrParameterName[i];
			ar << m_vstrParameterPt[i];
			ar << m_vstrParameterUnit[i];
		}
		ar << m_nAutoLockTime;
		m_ErrorListDlg->Serialize(ar);
		m_SmartDotsListDlg->Serialize(ar);
		m_UDEVisionListDlg->Serialize(ar);
		m_SmartRobotListDlg->Serialize(ar);
		m_SmartLEDListDlg->Serialize(ar);
		m_UDEOutlookListDlg->Serialize(ar);
		m_DataCollectionDlg->Serialize(ar);
		m_NewSmartDotsDlg->Serialize(ar);
		//m_AngleTestListDlg->Serialize(ar);
		//m_DiameterTestListDlg->Serialize(ar);
	}
	else
	{	// loading code
		m_strSoftwareVersion.Append(_T("."));
		vector<CString> vstrTem;
		vstrTem = m_ValueCalculate.CutString(m_strSoftwareVersion, '.');
		int nAr = 0;

		CString strAr;
		ar >> m_bCollecting;
		for (size_t i = 0;i < BT_RELAY_SUM; i++)
		{
			ar >> m_vbRelayBtStatus[i];
			ar >> m_vstrRelayBt[i];
			ar >> m_vstrRelayBtName[i];
			ar >> m_vnRelayBtMode[i];
			if (_ttoi(vstrTem[0]) >= 9)
			{
				ar >> m_vbIsRelayBtClickAuto[i];
			}
		}
		for (size_t i = 0;i < CK_RELAY_SUM; i++)
		{
			ar >> m_vbRelayCkStatus[i];
			ar >> m_vstrRelayCk[i];
			ar >> m_vstrRelayCkName[i];
		}
		for (size_t i = 0;i < DP_RELAY_SUM; i++)
		{
			ar >> m_vbRelayDpStatus[i];
			ar >> m_vstrRelayDp[i];
			ar >> m_vstrRelayDpName[i];
			ar >> m_vstrRelayDpCaption[i];
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

		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if (m_vbRelayBtStatus[i])
			{
				m_BL_btRelay[i].ShowWindow(SW_SHOW);
				m_BL_btRelay[i].SetCaption(m_vstrRelayBtName[i]);
				m_BL_btRelay[i].SetCtrlCaption(m_vstrRelayBt[i]);
				switch (m_vnRelayBtMode[i])
				{
				case RELAY_BT_MODE_LOCK:
					m_BL_btRelay[i].SetInterruptMode(TRUE);
					m_BL_btRelay[i].SetPushLike(TRUE);
					break;
				case RELAY_BT_MODE_UNLOCK:
					m_BL_btRelay[i].SetInterruptMode(FALSE);
					m_BL_btRelay[i].SetPushLike(FALSE);
					break;
				default:
					break;
				}
			}
			else
			{
				m_BL_btRelay[i].ShowWindow(SW_HIDE);
			}
		}
		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			if (m_vbRelayCkStatus[i])
			{
				m_BL_ckRelay[i].ShowWindow(SW_SHOW);
				m_BL_ckRelay[i].SetCaption(m_vstrRelayCkName[i]);
			}
			else
			{
				m_BL_ckRelay[i].ShowWindow(SW_HIDE);
			}
		}
		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			if (m_vbRelayDpStatus[i])
			{
				m_BL_dpRelay[i].ShowWindow(SW_SHOW);
				m_BL_dpRelay[i].SetCaption(m_vstrRelayDpCaption[i]);
				m_BL_dpRelay[i].SetDropDownData(m_vstrRelayDpName[i]);
			}
			else
			{
				m_BL_dpRelay[i].ShowWindow(SW_HIDE);
			}
		}

		if (m_bRelayBtStarStatus)
		{
			m_BL_btRelayStar.ShowWindow(SW_SHOW);
			m_BL_btRelayStar.SetCtrlCaption(m_strRelayStar);
		}
		else
		{
			m_BL_btRelayStar.ShowWindow(SW_HIDE);
		}
		if (m_bRelayBtStopStatus)
		{
			m_BL_btRelayStop.ShowWindow(SW_SHOW);
			m_BL_btRelayStop.SetCtrlCaption(m_strRelayStop);
		}
		else
		{
			m_BL_btRelayStop.ShowWindow(SW_HIDE);
		}
		if (m_bRelayBtResetStatus)
		{
			m_BL_btRelayReset.ShowWindow(SW_SHOW);
			m_BL_btRelayReset.SetCtrlCaption(m_strRelayReset);
		}
		else
		{
			m_BL_btRelayReset.ShowWindow(SW_HIDE);
		}
		if (m_bRelayBtErrorStatus)
		{
			m_BL_btRelayError.ShowWindow(SW_SHOW);
			m_BL_btRelayError.SetCtrlCaption(m_strRelayError);
		}
		else
		{
			m_BL_btRelayError.ShowWindow(SW_HIDE);
		}
		if (m_bRelayBtPauseStatus)
		{
			m_BL_btRelayPause.ShowWindow(SW_SHOW);
			m_BL_btRelayPause.SetCtrlCaption(m_strRelayPause);
		}
		else
		{
			m_BL_btRelayPause.ShowWindow(SW_HIDE);
		}
		if (m_bRelaySwAutoStatus)
		{
			m_BL_swRelayAuto.ShowWindow(SW_SHOW);
		}
		else
		{
			m_BL_swRelayAuto.ShowWindow(SW_HIDE);
		}
		if (m_bRelaySwUnAutoStatus)
		{
			m_BL_swRelayUnAuto.ShowWindow(SW_SHOW);
		}
		else
		{
			m_BL_swRelayUnAuto.ShowWindow(SW_HIDE);
		}

		ar >> nAr;
		m_vstrParameter.clear();
		m_vstrParameterByte.clear();
		m_vstrParameterName.clear();
		m_vstrParameterPt.clear();
		if (_ttoi(vstrTem[0]) >= 6)
		{
			m_vstrParameterUnit.clear();
		}

		m_vstrParameter.resize(nAr);
		m_vstrParameterByte.resize(nAr);
		m_vstrParameterName.resize(nAr);
		m_vstrParameterPt.resize(nAr);
		if (_ttoi(vstrTem[0]) >= 6)
		{
			m_vstrParameterUnit.resize(nAr);
		}

		for (size_t i = 0;i < m_vstrParameter.size(); i++)
		{
			ar >> m_vstrParameter[i];
			ar >> m_vstrParameterByte[i];
			ar >> m_vstrParameterName[i];
			ar >> m_vstrParameterPt[i];
			if (_ttoi(vstrTem[0]) >= 6)
			{
				ar >> m_vstrParameterUnit[i];
			}
			m_ParameterListDlg->m_BL_ParameterList.AppendRow(FALSE);
			m_ParameterListDlg->m_BL_ParameterList.SetItemText(i, 1, m_vstrParameter[i]);
			m_ParameterListDlg->m_BL_ParameterList.SetItemText(i, 2, m_vstrParameterByte[i]);
			m_ParameterListDlg->m_BL_ParameterList.SetItemText(i, 3, m_vstrParameterName[i]);
			m_ParameterListDlg->m_BL_ParameterList.SetItemText(i, 4, m_vstrParameterPt[i]);
			if (_ttoi(vstrTem[0]) >= 6)
			{
				m_ParameterListDlg->m_BL_ParameterList.SetItemText(i, 5, m_vstrParameterUnit[i]);
			}
		}
		LoadFileData();

		if (_ttoi(vstrTem[0]) >= 11)
		{
			ar >> m_nAutoLockTime;
		}
		m_ErrorListDlg->Serialize(ar);
		if (_ttoi(vstrTem[0]) >= 2)
		{
			m_SmartDotsListDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 3)
		{
			m_UDEVisionListDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 4)
		{
			m_SmartRobotListDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 5)
		{
			m_SmartLEDListDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 7)
		{
			m_UDEOutlookListDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 8)
		{
			m_DataCollectionDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 10)
		{
			m_NewSmartDotsDlg->Serialize(ar);
		}
		if (_ttoi(vstrTem[0]) >= 100)
		{
			m_AngleTestListDlg->Serialize(ar);
			m_DiameterTestListDlg->Serialize(ar);
		}
		UpdateMsgList();
		UpdateParameterList();
		UpdateErrorList();
		if (_ttoi(vstrTem[0]) >= 2)
		{
			UpdateSmartDotsList();
		}
		if (_ttoi(vstrTem[0]) >= 3)
		{
			UpdateUDEVisionList();
		}
		if (_ttoi(vstrTem[0]) >= 4)
		{
			UpdateSmartRobotList();
		}
		if (_ttoi(vstrTem[0]) >= 5)
		{
			UpdateSmartLEDList();
		}
		if (_ttoi(vstrTem[0]) >= 7)
		{
			UpdateUDEOutlookList();
		}
		if (_ttoi(vstrTem[0]) >= 8)
		{
			UpdateDataCollectionList();
		}
		if (_ttoi(vstrTem[0]) >= 9)
		{
			UpdateNewSmartDots();
		}
		if (_ttoi(vstrTem[0]) >= 100)
		{
			UpdateAngleTestList();
			UpdateDiameterTestList();
		}
		
		const CString strTitle = GetTitle();
		m_SmartDotsListDlg->SetTitle(GetTitle() + _T("焊點檢測"));
		m_SmartRobotListDlg->SetTitle(GetTitle() + _T("機械手臂"));
		m_AngleTestListDlg->SetTitle(GetTitle() + _T("角度檢測"));
		m_DiameterTestListDlg->SetTitle(GetTitle() + _T("直徑檢測"));
		m_UDEOutlookListDlg->SetTitle(GetTitle() + _T("視覺檢測"));
		m_UDEVisionListDlg->SetTitle(GetTitle() + _T("_UDEVision"));
		m_SmartLEDListDlg->SetTitle(GetTitle() + _T("LED檢測"));
		m_DataCollectionDlg->SetTitle(GetTitle() + _T("數據統計"));
		m_NewSmartDotsDlg->SetTitle(GetTitle() + _T("新焊點檢測"));
	}
}

afx_msg LRESULT CControllerDlg::OnStartCollect(WPARAM wParam, LPARAM lParam)
{
	SetTimer(0, 1 * TIME_RATIO, NULL);
	
	return 0;
}


afx_msg LRESULT CControllerDlg::OnStopCollect(WPARAM wParam, LPARAM lParam)
{
	KillTimer(0);
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	m_bCollecting = FALSE;
	return 0;
}


UINT CControllerDlg:: _CollectDataThread(LPVOID pParam)
{
	CControllerDlg *pApp = (CControllerDlg *)pParam;
	UINT nRetVul = pApp->_CollectDataThreadKernal();

	return nRetVul;
}

UINT CControllerDlg::_CollectDataThreadKernal(void)
{
	CollectData();
	return 0;
}

void CControllerDlg::CollectStar()
{
	if (m_bCollecting)
	{
		if (m_bUninterrupted)
		{
			CollectData();
		}
		else
		{
			m_pController->PostMessage(WM_COLLECTRUN, m_nControllerDlgCounter, READ_DATA);
			QueryPerformanceFrequency(&m_nFreq);
			QueryPerformanceCounter(&m_nBeginTime); 
		}
	}
}

void CControllerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		//AfxBeginThread(_CollectDataThread, this);//啟動採集數據線程
		CollectStar();
		break;
	case 1:
		KillTimer(1);
		if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL)) 
		{
			for (int i = 0; i < CK_RELAY_SUM; i++)
			{
				if (m_vbRelayCkStatus[i])
				{
					m_BL_ckRelay[i].SetCaption(m_vstrRelayCk[i]);
				}
			}
			for (int i = 0; i < DP_RELAY_SUM; i++)
			{
				if (m_vbRelayDpStatus[i])
				{
					m_BL_dpRelay[i].SetDropDownData(m_vstrRelayDp[i]);
				}
			}
			m_BL_swRelayAuto.SetCaption(m_strRelayAuto);
			m_BL_swRelayUnAuto.SetCaption(m_strRelayUnAuto);
		}
		else
		{
			for (int i = 0; i < CK_RELAY_SUM; i++)
			{
				if (m_vbRelayCkStatus[i])
				{
					m_BL_ckRelay[i].ShowWindow(SW_SHOW);
					m_BL_ckRelay[i].SetCaption(m_vstrRelayCkName[i]);
				}
			}
			for (int i = 0; i < DP_RELAY_SUM; i++)
			{
				if (m_vbRelayDpStatus[i])
				{
					m_BL_dpRelay[i].SetDropDownData(m_vstrRelayDpName[i]);
				}
			}
			m_BL_swRelayAuto.SetCaption(_T("自动模式"));
			m_BL_swRelayUnAuto.SetCaption(_T("手动模式"));
		}
		SetTimer(1, 1, NULL);
		break;
	case 6:
		{
			KillTimer(6);
			if (m_ParameterListDlg->m_bParamInputting)
			{
				SetTimer(6, m_nAutoLockTime, NULL);
				break;
			}
			const BOOL bLock = TRUE;
// 			for (int i = 0; i < CK_RELAY_SUM; i++)
// 			{
// 				m_BL_ckRelay[i].SetEnabled(FALSE);
// 			}
			for (int i = 0; i < DP_RELAY_SUM; i++)
			{
				m_BL_dpRelay[i].SetEnabled(FALSE);
			}
			m_ParameterListDlg->m_BL_ParameterList.SetReadOnly(bLock);
			m_ParameterListDlg->m_BL_btAddParam.SetEnabled(!bLock);
			m_ParameterListDlg->m_BL_btSaveParam.SetEnabled(!bLock);
			m_ParameterListDlg->m_BL_btLoadParam.SetEnabled(!bLock);
			m_ParameterListDlg->m_BL_ckUpdateData.SetEnabled(!bLock);

			m_DataCollectionDlg->m_BL_DataCollectionList.SetReadOnly(bLock);
			m_DataCollectionDlg->m_BL_btAddData.SetEnabled(!bLock);
			m_DataCollectionDlg->m_BL_btSaveData.SetEnabled(!bLock);
			m_DataCollectionDlg->m_BL_btLoadData.SetEnabled(!bLock);

			m_ErrorListDlg->m_BL_ErrorList.SetReadOnly(bLock);
			m_ErrorListDlg->m_BL_edErrorCode.SetEnabled(!bLock);
			m_ErrorListDlg->m_BL_btSaveError.SetEnabled(!bLock);
			m_ErrorListDlg->m_BL_btLoadError.SetEnabled(!bLock);

			m_SmartDotsListDlg->m_BL_SmartDotsList.SetReadOnly(bLock);
			m_SmartDotsListDlg->m_BL_btLoadSmartDots.SetEnabled(!bLock);
			m_SmartDotsListDlg->m_BL_btSaveSmartDots.SetEnabled(!bLock);
			m_SmartDotsListDlg->m_BL_edSmartDotsCode.SetEnabled(!bLock);
			m_SmartDotsListDlg->m_BL_edSmartDotsResult.SetEnabled(!bLock);

			m_NewSmartDotsDlg->m_BL_NewSmartDotsList.SetReadOnly(bLock);
			m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.SetEnabled(!bLock);

			m_UDEVisionListDlg->m_BL_UDEVisionList.SetReadOnly(bLock);
			m_UDEVisionListDlg->m_BL_btSaveUDEVision.SetEnabled(!bLock);
			m_UDEVisionListDlg->m_BL_btLoadUDEVision.SetEnabled(!bLock);
			m_UDEVisionListDlg->m_BL_edUDEVisionCode.SetEnabled(!bLock);
			m_UDEVisionListDlg->m_BL_edUDEVisionResult.SetEnabled(!bLock);
			m_UDEVisionListDlg->m_BL_btUDEVisionContinue.SetEnabled(!bLock);
			for (int i = 0; i < 21; i++)
			{
				m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].SetReadOnly(bLock);
			}

			m_SmartLEDListDlg->m_BL_SmartLEDList.SetReadOnly(bLock);
			m_SmartLEDListDlg->m_BL_btSaveSmartLED.SetEnabled(!bLock);
			m_SmartLEDListDlg->m_BL_btLoadSmartLED.SetEnabled(!bLock);
			m_SmartLEDListDlg->m_BL_edSmartLEDCode.SetEnabled(!bLock);

			m_SmartRobotListDlg->m_BL_SendSmartRobotList.SetReadOnly(bLock);
			m_SmartRobotListDlg->m_BL_GetSmartRobotList.SetReadOnly(bLock);
			m_SmartRobotListDlg->m_BL_edSmartRobotCode.SetEnabled(!bLock);
			m_SmartRobotListDlg->m_BL_btSaveSmartRobot.SetEnabled(!bLock);
			m_SmartRobotListDlg->m_BL_btLoadSmartRobot.SetEnabled(!bLock);

			m_UDEOutlookListDlg->m_BL_UDEOutlookList.SetReadOnly(bLock);
			for (int i = 0; i < 10; i++)
			{
				m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].SetReadOnly(bLock);
			}
			m_UDEOutlookListDlg->m_BL_btSaveUDEOutlook.SetEnabled(!bLock);
			m_UDEOutlookListDlg->m_BL_btLoadUDEOutlook.SetEnabled(!bLock);
			m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.SetEnabled(!bLock);
			m_UDEOutlookListDlg->m_BL_edUDEOutlookResult.SetEnabled(!bLock);
			m_UDEOutlookListDlg->m_BL_btUDEOutlookContinue.SetEnabled(!bLock);
			m_ParameterListDlg->m_bParamInpiutLocked = bLock;
		}
		break;
	default:
		break;
	}
	
	CTpLayerWnd::OnTimer(nIDEvent);
}


void CControllerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTpLayerWnd::OnClose();
}


void CControllerDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CTpLayerWnd::OnCancel();
}



void CControllerDlg::ItemEditFinishBlReportcollectlist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 0)
	{
		CString strInfo;
		strInfo = m_BL_ReportCollectList.GetItemText(nRow, 1);
		if (_ttoi(strInfo) < 0)
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("緩存名錯誤，數據地址不能為負數，請檢查設備配置文件"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
			m_BL_ReportCollectList.SetItemText(nRow, nCol, _T(""));
			m_BL_ReportCollectList.SetItemText(nRow, 1, _T(""));
		}
	}
	if (nCol == 7)
	{
		if (m_BL_ReportCollectList.GetItemText(nRow, nCol) == _T(""))
		{
			m_BL_ReportCollectList.SetItemText(nRow, nCol, _T("0"));
		}
	}
}


afx_msg LRESULT CControllerDlg::OnCollectFinish(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < 7 + BT_RELAY_SUM + CK_RELAY_SUM; i++)
	{
		int nRelayStatus = 0;
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 6) == _T("1"))//有顯示
		{
			nRelayStatus = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));
			if (i < 7)
			{
				switch (i)
				{
				case 0:
					m_BL_swRelayAuto.SetStatus(nRelayStatus);
					break;
				case 1:
					m_BL_swRelayUnAuto.SetStatus(nRelayStatus);
					break;
				case 2:
					m_BL_btRelayStar.SetStatus(nRelayStatus);
					break;
				case 3:
					m_BL_btRelayStop.SetStatus(nRelayStatus);
					break;
				case 4:
					m_BL_btRelayReset.SetStatus(nRelayStatus);
					break;
				case 5:
					m_BL_btRelayError.SetStatus(nRelayStatus);
					break;
				case 6:
					m_BL_btRelayPause.SetStatus(nRelayStatus);
					break;
				default:
					break;
				}
			}
			else if((i >=7) && (i <= 106))
			{
				m_BL_btRelay[i - 7].SetStatus(nRelayStatus);
			}
			else
			{
				m_BL_ckRelay[i - 107].SetStatus(nRelayStatus);
			}
		}
	}

	/*dropdown控件處理部分*/
	size_t nMsgListRowCounter = 123;
	for (int i = 0; i < DP_RELAY_SUM; i++)
	{
		if (m_vbRelayDpStatus[i])
		{
			CString strTem;
			CString strPart;
			vector<CString> vstrDpTem;
			vstrDpTem.clear();
			strTem = m_vstrRelayDp[i];
			strTem.Append(_T(";"));
			vstrDpTem = m_ValueCalculate.CutString(strTem, ';');

			vector<CString> vstrDpNameTem;
			vstrDpNameTem.clear();
			strTem = m_vstrRelayDpName[i];
			strTem.Append(_T(";"));
			vstrDpNameTem = m_ValueCalculate.CutString(strTem, ';');


			for (size_t j = nMsgListRowCounter; j < nMsgListRowCounter + vstrDpTem.size(); j++)
			{
				if (_ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(j, 5)) > 0)
				{
					int n = j - 123;
					m_BL_dpRelay[i].SetValueText(vstrDpNameTem[j - nMsgListRowCounter]);
				}
			}
			nMsgListRowCounter = nMsgListRowCounter + vstrDpTem.size();
		}
	}
	
	for (size_t j = nMsgListRowCounter; j < nMsgListRowCounter + m_vstrParameter.size(); j++)
	{
		CString strTem;
		strTem = m_MsgListDlg->m_BL_MsgList.GetItemText(j, 5);
		double dTem = _ttoi(strTem) * (1 / pow(10, _ttoi(m_ParameterListDlg->m_BL_ParameterList.GetItemText(j - nMsgListRowCounter, 4))));
		strTem.Format(_T("%f"), dTem);
		while ((strTem.GetLength() - strTem.Find('.') - 1) > _ttoi(m_ParameterListDlg->m_BL_ParameterList.GetItemText(j - nMsgListRowCounter, 4)))
		{
			strTem.Delete(strTem.GetLength() - 1, 1);
		}
		if (_ttoi(m_ParameterListDlg->m_BL_ParameterList.GetItemText(j - nMsgListRowCounter, 4)) == 0)//没有小数点
		{
			strTem.Delete(strTem.GetLength() - 1, 1);
		}
		m_ParameterListDlg->m_BL_ParameterList.SetItemText(j - nMsgListRowCounter, 6, strTem);
	}
	nMsgListRowCounter = nMsgListRowCounter + m_vstrParameter.size();

	for (size_t j = nMsgListRowCounter; j < nMsgListRowCounter + m_vstrDataCollection.size(); j++)
	{
		CString strTem;
		strTem = m_MsgListDlg->m_BL_MsgList.GetItemText(j, 5);
		double dTem = _ttoi(strTem) * (1 / pow(10, _ttoi(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(j - nMsgListRowCounter, 4))));
		strTem.Format(_T("%f"), dTem);
		while ((strTem.GetLength() - strTem.Find('.') - 1) > _ttoi(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(j - nMsgListRowCounter, 4)))
		{
			strTem.Delete(strTem.GetLength() - 1, 1);
		}
		if (_ttoi(m_DataCollectionDlg->m_BL_DataCollectionList.GetItemText(j - nMsgListRowCounter, 4)) == 0)//没有小数点
		{
			strTem.Delete(strTem.GetLength() - 1, 1);
		}
		m_DataCollectionDlg->m_BL_DataCollectionList.SetItemText(j - nMsgListRowCounter, 6, strTem);
	}
	nMsgListRowCounter = nMsgListRowCounter + m_vstrDataCollection.size();


	vector<CString> vstrTem;
	vector<int> vnTem;
	vstrTem.clear();
	vnTem.clear();
	for (int i = nMsgListRowCounter; i < m_MsgListDlg->m_BL_MsgList.GetRows(); i++)
	{
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("報警緩存器"))
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
			{
				m_ErrorListDlg->m_nErrorCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
				m_ErrorListDlg->PostMessage(WM_ERROR_CODE);
				vstrTem.push_back(m_ErrorListDlg->m_BL_edErrorCode.GetValueText());
				vnTem.push_back(0);
			}
		}
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("焊點檢測緩存器"))
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
			{
				m_SmartDotsListDlg->m_nSmartDotsCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
				m_SmartDotsListDlg->PostMessage(WM_SMARTDOTS_CODE);
				vstrTem.push_back(m_SmartDotsListDlg->m_BL_edSmartDotsCode.GetValueText());
				vnTem.push_back(0);
			}
		}
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("新焊點檢測緩存器"))
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
			{
				m_NewSmartDotsDlg->m_nNewSmartDotsCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
				m_NewSmartDotsDlg->PostMessage(WM_NEWSMARTDOTS_CODE);
				vstrTem.push_back(m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.GetValueText());
				vnTem.push_back(0);
			}
		}
 		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("外觀檢測緩存器"))
 		{
 			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
 			{
  				m_UDEVisionListDlg->m_nUDEVisionCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
  				m_UDEVisionListDlg->PostMessage(WM_UDEVISION_CODE, PLC2UDEVISION);
 				vstrTem.push_back(m_UDEVisionListDlg->m_BL_edUDEVisionCode.GetValueText());
 				vnTem.push_back(0);
 			}
 		}
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("視覺檢測緩存器"))
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
			{
				m_UDEOutlookListDlg->m_nUDEOutlookCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
				m_UDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_CODE, PLC2UDEOUTLOOK);
				vstrTem.push_back(m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText());
				vnTem.push_back(0);
			}
		}
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("機械手緩存器"))
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
			{
				m_SmartRobotListDlg->m_nSmartRobotCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
				m_SmartRobotListDlg->PostMessage(WM_SMARTROBOT_CODE);
				vstrTem.push_back(m_SmartRobotListDlg->m_BL_edSmartRobotCode.GetValueText());
				vnTem.push_back(0);
			}
		}
		if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 4) == _T("LED檢測緩存器"))
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5) != _T("0"))//收到錯誤碼
			{
				m_SmartLEDListDlg->m_nSmartLEDCode = _ttoi(m_MsgListDlg->m_BL_MsgList.GetItemText(i, 5));//傳遞錯誤碼，並發送消息
				m_SmartLEDListDlg->PostMessage(WM_SMARTLED_CODE);
				vstrTem.push_back(m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText());
				vnTem.push_back(0);
			}
		}
		m_MsgListDlg->m_BL_MsgList.SetItemText(i, 5, _T("0"));
	}
	if (vstrTem.size() > 0)
	{
		for (size_t i = 0; i < vstrTem.size(); i++)
		{
			SearchSendData(vstrTem[i], vnTem[i]);
		}
	}
	else
	{
		QueryPerformanceCounter(&m_nEndTime);
		m_strTime.Format(_T("%.2f"), (((double)(m_nEndTime.QuadPart - m_nBeginTime.QuadPart) / (double)m_nFreq.QuadPart)) * 1000);
		((CBL_Button *)(GetDlgItem(IDC_BL_btRunTime)))->SetCaption(m_strTime);
		CollectData();
	}
	return 0;
}


afx_msg LRESULT CControllerDlg::OnWriteFinish(WPARAM wParam, LPARAM lParam)
{
	CollectData();
	return 0;
}


afx_msg LRESULT CControllerDlg::OnCollectLose(WPARAM wParam, LPARAM lParam)
{
	SetTimer(0, 1 * TIME_RATIO, NULL);
	return 0;
}


afx_msg LRESULT CControllerDlg::OnBtRealyMessage(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 4)//鼠標命中
	{
		return 0;
	}
	if (wParam == 0)//單擊鼠標左鍵
	{
		int nSendBtMsg = 0;
		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if(m_BL_btRelay[i].IsMsgSrc())
			{
				nSendBtMsg = i;
				break;
				
			}
		}
		const BOOL bShowRelayAuto = m_BL_swRelayAuto.IsWindowVisible();
		const BOOL bShowRelayUnAuto = m_BL_swRelayUnAuto.IsWindowVisible();
		BOOL IsSendMessage = FALSE;//點擊按鈕是否發出消息  FALSE-不發送  TRUE-發送
		if (bShowRelayAuto && bShowRelayUnAuto)
		{
			if (!m_BL_swRelayAuto.GetStatus() && m_BL_swRelayUnAuto.GetStatus())
			{
				IsSendMessage = TRUE;
			}
		}
		else if (bShowRelayAuto && !bShowRelayUnAuto)
		{
			if (!m_BL_swRelayAuto.GetStatus())
			{
				IsSendMessage = TRUE;
			}
		}
		else if(!bShowRelayAuto && bShowRelayUnAuto)
		{
			if (m_BL_swRelayUnAuto.GetStatus())
			{
				IsSendMessage = TRUE;
			}
		}
		else if(!bShowRelayAuto && !bShowRelayUnAuto)
		{
			IsSendMessage = TRUE;
		}
		
		if (m_BL_swRelayAuto.GetStatus() && m_BL_dpRelay[0].GetEnabled())
		{
			if (m_vbIsRelayBtClickAuto[nSendBtMsg])
			{
				IsSendMessage = TRUE;
			}
		}
		else if(m_BL_swRelayAuto.GetStatus() && !m_BL_dpRelay[0].GetEnabled())
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("自動模式使用按鈕需解除鎖定！！！"), _T("非法使用"), MB_ICONSTOP | MB_OK);
			return 0;
		}
		if (IsSendMessage)
		{
			if (m_BL_btRelay[nSendBtMsg].GetPushLike())//交替式按鈕
			{
				SearchSendData(m_vstrRelayBt[nSendBtMsg], m_BL_btRelay[nSendBtMsg].GetStatus());
			}
			else
			{
				SearchSendData(m_vstrRelayBt[nSendBtMsg], 3);
			}
		}
		else
		{
			CMsgBox MsgBox(this);
			MsgBox.ShowMsg(_T("該模式下禁止使用按鍵！！！"), _T("非法使用"), MB_ICONSTOP | MB_OK);
		}
		
	}
	if (wParam == 1)//雙擊鼠標左鍵
	{
		for (int i = 0; i < BT_RELAY_SUM; i++)
		{
			if(m_BL_btRelay[i].IsMsgSrc())
			{
				
			}
		}
	}
	if (wParam == 2)//雙擊鼠標右鍵
	{
		if (lParam & MK_CONTROL)//按住CTRL
		{

		}
		else
		{
			//m_CtrlSet.CreateTopWnd(TRUE);
		}
	}
	if (wParam == 3)//按鍵狀態改變
	{

	}
	
	return 0;
}

afx_msg LRESULT CControllerDlg::OnCkRealy(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < CK_RELAY_SUM; i++)
	{
		if(m_BL_ckRelay[i].IsMsgSrc())
		{
			SearchSendData(m_vstrRelayCk[i], wParam);
			if (m_BL_swConnect.GetStatus())
			{
				KillTimer(6);
				SetTimer(6, m_nAutoLockTime, NULL);
			}
			break;
		}
	}
	return 0;
}


afx_msg LRESULT CControllerDlg::OnDpRealy(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < DP_RELAY_SUM; i++)
	{
		if(m_BL_dpRelay[i].IsMsgSrc())
		{
			if (wParam == 2)//修改了选择项目消息
			{
				vector<CString> vstrTem;
				vector<int> vnTem;
				vnTem.clear();
				vstrTem.clear();
				CString strTem;
				strTem = m_vstrRelayDp[i];
				strTem.Append(_T(";"));
				vstrTem = m_ValueCalculate.CutString(strTem, ';');
				vnTem.resize(vstrTem.size());
				for (size_t j = 0; j < vstrTem.size(); j++)
				{
					if (j == m_BL_dpRelay[i].GetCurSelect())
					{
						SearchSendData(vstrTem[j], 1);
					}
					else
					{
						SearchSendData(vstrTem[j], 0);
					}
				}
				if (m_BL_swConnect.GetStatus())
				{
					KillTimer(6);
					SetTimer(6, m_nAutoLockTime, NULL);
				}
				break;
			}
		}
	}
	return 0;
}

afx_msg LRESULT CControllerDlg::OnParamFinish(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_swConnect.GetStatus())
	{
		SearchSendData(m_ParameterListDlg->m_BL_ParameterList.GetItemText(wParam, 1), lParam);
	}
	return 0;
}

afx_msg LRESULT CControllerDlg::OnSmartdotsFinish(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_swConnect.GetStatus())
	{
		SearchSendData(m_SmartDotsListDlg->m_BL_SmartDotsList.GetItemText(wParam, 6), lParam);
	}
	return 0;
}

afx_msg LRESULT CControllerDlg::OnNewsSmartDotsFinish(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_swConnect.GetStatus())
	{
		SearchSendData(m_NewSmartDotsDlg->m_BL_NewSmartDotsList.GetItemText(wParam, 7), lParam);
	}
	return 0;
}

afx_msg LRESULT CControllerDlg::OnUdevisionFinish(WPARAM wParam, LPARAM lParam)
{
	//收到结果信号和完成信号，数据放置在PLC的缓存器的位置是不同的
	if (m_BL_swConnect.GetStatus())
	{
		if (lParam <= 1)//收到的是结果信号
		{
			SearchSendData(m_UDEVisionListDlg->m_BL_edUDEVisionRes[wParam].GetValueText(), lParam);
		}
		else//收到的是完成信号
 		{
			CString strTem;
			strTem = m_UDEVisionListDlg->m_BL_edUDEVisionRes[wParam].GetValueText();
			strTem.Delete(0, 1);
			strTem.Format(_T("%d"), _ttoi(strTem) + 1);
			strTem.Insert(0, m_UDEVisionListDlg->m_BL_edUDEVisionRes[wParam].GetValueText()[0]);
			SearchSendData(strTem, lParam);
		}
	}
	return 0;
}


afx_msg LRESULT CControllerDlg::OnUdeoutlookFinish(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_swConnect.GetStatus())
	{
		if (wParam == 9999)
		{
			CString strTem;
			strTem = m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText();
			strTem.Delete(0, 1);
			strTem.Format(_T("%d"), _ttoi(strTem) + 1);
			strTem.Insert(0, m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.GetValueText()[0]);
			SearchSendData(strTem, 2);
		}
		else
		{
			if (lParam != -1)
			{
				SearchSendData(m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[wParam].GetValueText(), lParam);
			}
		}
	}
	return 0;
}


afx_msg LRESULT CControllerDlg::OnSmartrobotFinish(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_swConnect.GetStatus())
	{
		SearchSendData(m_SmartRobotListDlg->m_BL_GetSmartRobotList.GetItemText(wParam, 5), lParam);
	}
	return 0;
}

afx_msg LRESULT CControllerDlg::OnSmartrobotStarUdevision(WPARAM wParam, LPARAM lParam)
{
	m_UDEVisionListDlg->m_nUDEVisionCodeRobot = wParam;
	m_UDEVisionListDlg->PostMessage(WM_UDEVISION_CODE_ROBOT, ROBOT2UDEVISION);
	return 0;
}

afx_msg LRESULT CControllerDlg::OnUdevisionFinishRobot(WPARAM wParam, LPARAM lParam)
{
	m_SmartRobotListDlg->PostMessage(WM_SMARTROBOT_FINISH_UDEVISION, wParam, lParam);
	return 0;
}

afx_msg LRESULT CControllerDlg::OnSmartrobotStarUdeoutlook(WPARAM wParam, LPARAM lParam)
{
	m_UDEOutlookListDlg->m_nUDEOutlookCodeRobot = wParam;//傳遞錯誤碼，並發送消息
	m_UDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_CODE_ROBOT, ROBOT2UDEOUTLOOK);
	return 0;
}

afx_msg LRESULT CControllerDlg::OnUdeoutlookFinishRobot(WPARAM wParam, LPARAM lParam)
{
	m_SmartRobotListDlg->PostMessage(WM_SMARTROBOT_FINISH_UDEOUTLOOK, wParam, lParam);
	return 0;
}

afx_msg LRESULT CControllerDlg::OnSmartledFinish(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_swConnect.GetStatus())
	{
		if (lParam == 9999)
		{
			CString strTem;
			strTem = m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText();
			strTem.Delete(0, 1);
			strTem.Format(_T("%d"), _ttoi(strTem) + 1);
			strTem.Insert(0, m_SmartLEDListDlg->m_BL_edSmartLEDCode.GetValueText()[0]);
			SearchSendData(strTem, 2);
		}
		else
		{
			SearchSendData(m_SmartLEDListDlg->m_BL_SmartLEDList.GetItemText(wParam, 2), lParam);
		}	
	}
	
	return 0;
}

void CControllerDlg::LBtClickedBlAddctrl(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码

	if (nFlags & MK_CONTROL)//按下CTRL
	{
		UpdateMsgList();
		UpdateParameterList();
		UpdateDataCollectionList();
		UpdateErrorList();
		UpdateSmartDotsList();
		UpdateUDEVisionList();
		UpdateSmartRobotList();
		UpdateSmartLEDList();
		UpdateUDEOutlookList();
		UpdateNewSmartDots();
	}
	else
	{
		m_BL_btAddCtrl.SetEnabled(TRUE);

		m_CtrlSet->SetTitle(_T("控件設置"));

		m_CtrlSet->m_vbRelayBtStatus = m_vbRelayBtStatus;
		m_CtrlSet->m_vbRelayCkStatus = m_vbRelayCkStatus;
		m_CtrlSet->m_vbRelayDpStatus = m_vbRelayDpStatus;

		m_CtrlSet->m_vstrRelayBt = m_vstrRelayBt;//按键中间继电器（Mxx）
		m_CtrlSet->m_vstrRelayBtName = m_vstrRelayBtName;//按键中间继电器名称
		m_CtrlSet->m_vnRelayBtMode = m_vnRelayBtMode;//按键中间继电器类型
		m_CtrlSet->m_vbIsRelayBtClickAuto = m_vbIsRelayBtClickAuto;//按键中间继电器类型

		m_CtrlSet->m_vstrRelayCk = m_vstrRelayCk;//按键中间继电器（Mxx）
		m_CtrlSet->m_vstrRelayCkName = m_vstrRelayCkName;//按键中间继电器名称

		m_CtrlSet->m_vstrRelayDp = m_vstrRelayDp;//按键中间继电器（Mxx）
		m_CtrlSet->m_vstrRelayDpName = m_vstrRelayDpName;//按键中间继电器名称
		m_CtrlSet->m_vstrRelayDpCaption = m_vstrRelayDpCaption;//按键中间继电器名称

		m_CtrlSet->m_bRelayBtStarStatus = m_bRelayBtStarStatus;
		m_CtrlSet->m_bRelayBtStopStatus = m_bRelayBtStopStatus;
		m_CtrlSet->m_bRelayBtResetStatus = m_bRelayBtResetStatus;
		m_CtrlSet->m_bRelayBtErrorStatus = m_bRelayBtErrorStatus;
		m_CtrlSet->m_bRelayBtPauseStatus = m_bRelayBtPauseStatus;
		m_CtrlSet->m_bRelaySwAutoStatus = m_bRelaySwAutoStatus;
		m_CtrlSet->m_bRelaySwUnAutoStatus = m_bRelaySwUnAutoStatus;

		m_CtrlSet->m_strRelayStar = m_strRelayStar;
		m_CtrlSet->m_strRelayStop = m_strRelayStop;
		m_CtrlSet->m_strRelayReset = m_strRelayReset;
		m_CtrlSet->m_strRelayError = m_strRelayError;
		m_CtrlSet-> m_strRelayPause = m_strRelayPause;
		m_CtrlSet-> m_strRelayAuto = m_strRelayAuto;
		m_CtrlSet-> m_strRelayUnAuto = m_strRelayUnAuto;


		if (m_CtrlSet.CreateTopWnd(TRUE) == IDOK)//點擊確認
		{
			m_vbRelayBtStatus = m_CtrlSet->m_vbRelayBtStatus;
			m_vbRelayCkStatus = m_CtrlSet->m_vbRelayCkStatus;
			m_vbRelayDpStatus = m_CtrlSet->m_vbRelayDpStatus;

			m_vstrRelayBt = m_CtrlSet->m_vstrRelayBt;//按键中间继电器（Mxx）
			m_vstrRelayBtName = m_CtrlSet->m_vstrRelayBtName;//按键中间继电器名称
			m_vnRelayBtMode = m_CtrlSet->m_vnRelayBtMode;//按键中间继电器类型
			m_vbIsRelayBtClickAuto = m_CtrlSet->m_vbIsRelayBtClickAuto;//按键中间继电器类型

			m_vstrRelayCk = m_CtrlSet->m_vstrRelayCk;//按键中间继电器（Mxx）
			m_vstrRelayCkName = m_CtrlSet->m_vstrRelayCkName;//按键中间继电器名称

			m_vstrRelayDp = m_CtrlSet->m_vstrRelayDp;//按键中间继电器（Mxx）
			m_vstrRelayDpName = m_CtrlSet->m_vstrRelayDpName;//按键中间继电器名称
			m_vstrRelayDpCaption = m_CtrlSet->m_vstrRelayDpCaption;//按键中间继电器名称

			m_bRelayBtStarStatus = m_CtrlSet->m_bRelayBtStarStatus;
			m_bRelayBtStopStatus = m_CtrlSet->m_bRelayBtStopStatus;
			m_bRelayBtResetStatus = m_CtrlSet->m_bRelayBtResetStatus;
			m_bRelayBtErrorStatus = m_CtrlSet->m_bRelayBtErrorStatus;
			m_bRelayBtPauseStatus = m_CtrlSet->m_bRelayBtPauseStatus;
			m_bRelaySwAutoStatus = m_CtrlSet->m_bRelaySwAutoStatus;//
			m_bRelaySwUnAutoStatus = m_CtrlSet->m_bRelaySwUnAutoStatus;//

			m_strRelayStar = m_CtrlSet->m_strRelayStar;
			m_strRelayStop = m_CtrlSet->m_strRelayStop;
			m_strRelayReset = m_CtrlSet->m_strRelayReset;
			m_strRelayError = m_CtrlSet->m_strRelayError;
			m_strRelayPause = m_CtrlSet-> m_strRelayPause;
			m_strRelayAuto = m_CtrlSet-> m_strRelayAuto;
			m_strRelayUnAuto = m_CtrlSet-> m_strRelayUnAuto;

			for (int i = 0; i < BT_RELAY_SUM; i++)
			{
				if (m_vbRelayBtStatus[i])
				{
					m_BL_btRelay[i].ShowWindow(SW_SHOW);
					m_BL_btRelay[i].SetCaption(m_vstrRelayBtName[i]);
					m_BL_btRelay[i].SetCtrlCaption(m_vstrRelayBt[i]);
					switch (m_vnRelayBtMode[i])
					{
					case RELAY_BT_MODE_LOCK:
						m_BL_btRelay[i].SetInterruptMode(TRUE);
						m_BL_btRelay[i].SetPushLike(TRUE);
						break;
					case RELAY_BT_MODE_UNLOCK:
						m_BL_btRelay[i].SetInterruptMode(FALSE);
						m_BL_btRelay[i].SetPushLike(FALSE);
						break;
					default:
						break;
					}
				}
				else
				{
					m_BL_btRelay[i].ShowWindow(SW_HIDE);
				}
			}
			for (int i = 0; i < CK_RELAY_SUM; i++)
			{
				if (m_vbRelayCkStatus[i])
				{
					m_BL_ckRelay[i].ShowWindow(SW_SHOW);
					m_BL_ckRelay[i].SetCaption(m_vstrRelayCkName[i]);
				}
				else
				{
					m_BL_ckRelay[i].ShowWindow(SW_HIDE);
				}
			}
			for (int i = 0; i < DP_RELAY_SUM; i++)
			{
				if (m_vbRelayDpStatus[i])
				{
					m_BL_dpRelay[i].ShowWindow(SW_SHOW);
					m_BL_dpRelay[i].SetCaption(m_vstrRelayDpCaption[i]);
					m_BL_dpRelay[i].SetDropDownData(m_vstrRelayDpName[i]);
				}
				else
				{
					m_BL_dpRelay[i].ShowWindow(SW_HIDE);
				}
			}

			if (m_bRelayBtStarStatus)
			{
				m_BL_btRelayStar.ShowWindow(SW_SHOW);
				m_BL_btRelayStar.SetCtrlCaption(m_strRelayStar);
			}
			else
			{
				m_BL_btRelayStar.ShowWindow(SW_HIDE);
			}
			if (m_bRelayBtStopStatus)
			{
				m_BL_btRelayStop.ShowWindow(SW_SHOW);
				m_BL_btRelayStop.SetCtrlCaption(m_strRelayStop);
			}
			else
			{
				m_BL_btRelayStop.ShowWindow(SW_HIDE);
			}
			if (m_bRelayBtResetStatus)
			{
				m_BL_btRelayReset.ShowWindow(SW_SHOW);
				m_BL_btRelayReset.SetCtrlCaption(m_strRelayReset);
			}
			else
			{
				m_BL_btRelayReset.ShowWindow(SW_HIDE);
			}
			if (m_bRelayBtErrorStatus)
			{
				m_BL_btRelayError.ShowWindow(SW_SHOW);
				m_BL_btRelayError.SetCtrlCaption(m_strRelayError);
			}
			else
			{
				m_BL_btRelayError.ShowWindow(SW_HIDE);
			}
			if (m_bRelayBtPauseStatus)
			{
				m_BL_btRelayPause.ShowWindow(SW_SHOW);
				m_BL_btRelayPause.SetCtrlCaption(m_strRelayPause);
			}
			else
			{
				m_BL_btRelayPause.ShowWindow(SW_HIDE);
			}
			if (m_bRelaySwAutoStatus)
			{
				m_BL_swRelayAuto.ShowWindow(SW_SHOW);
			}
			else
			{
				m_BL_swRelayAuto.ShowWindow(SW_HIDE);
			}
			if (m_bRelaySwUnAutoStatus)
			{
				m_BL_swRelayUnAuto.ShowWindow(SW_SHOW);
			}
			else
			{
				m_BL_swRelayUnAuto.ShowWindow(SW_HIDE);
			}
		}
	}
	
}


void CControllerDlg::LBtClickedBlChangectrl(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	m_CtrlSet->SetTitle(_T("控件設置"));
	//m_CtrlSet->ShowWindow(TRUE);
	if (m_CtrlSet.CreateTopWnd(TRUE) == IDOK)//點擊確認
	{
		// 			m_nShowBtRelayCounter++;
		// 			m_BL_btRelay[m_nShowBtRelayCounter - 1].ShowWindow(SW_SHOW);
		// 			if (m_nShowBtRelayCounter >= BT_RELAY_SUM)
		// 			{
		// 				m_BL_btAddCtrl.SetEnabled(FALSE);
		// 			}
	}
}


void CControllerDlg::ItemClickBlControllermenu(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strMenuName = strMenu;
	CString strItemName = strItem;
	CString strPath;
	if (strMenuName == _T("參數管理"))
	{
		switch (nItemPos)
		{
		case 0:   
			if (m_BL_swConnect.GetStatus())
			{
				m_ParameterListDlg->SetTitle(_T("參數修改"));
			}
			else
			{
				m_ParameterListDlg->SetTitle(_T("參數配置"));
			}
			m_ParameterListDlg->ShowWindow(SW_SHOW);
			break;
		case 1:
			m_DataCollectionDlg->ShowWindow(SW_SHOW);
			break;
		case 2:
			
			break;
		default:
			break;
		}
	}
	if (strMenuName == _T("消息配置"))
	{
		switch (nItemPos)
		{
		case 0:
			m_ErrorListDlg->ShowWindow(SW_SHOW);
			break;
		case 1:
			m_SmartDotsListDlg->ShowWindow(SW_SHOW);
			break;
		case 2:
			m_SmartRobotListDlg->ShowWindow(SW_SHOW);
			break;
		case 3:
			m_DiameterTestListDlg->ShowWindow(SW_SHOW);
			break;
		case 4:
			m_AngleTestListDlg->ShowWindow(SW_SHOW);
			break;
		case 5:
			m_UDEVisionListDlg->ShowWindow(SW_SHOW);
			break;
		case 6:
			m_UDEOutlookListDlg->ShowWindow(SW_SHOW);
			break;
		case 7:
			m_SmartLEDListDlg->ShowWindow(SW_SHOW);
			break;
		case 8:
			m_NewSmartDotsDlg->ShowWindow(SW_SHOW);
			break;
		default:
			break;
		}
	}
	if (strMenuName == _T("幫助"))
	{
		switch (nItemPos)
		{
		case 0:
			m_ErrorListDlg->m_MsgInfoDlg->ShowWindow(SW_SHOW);
			break;
		case 1:
			m_MsgListDlg->ShowWindow(SW_SHOW);
			break;
		case 2:
			m_AutoLockTimeDlg->m_nAutoLockTime = m_nAutoLockTime;
			if (IDOK == m_AutoLockTimeDlg.CreateTopWnd(TRUE, TRUE))
			{
				m_nAutoLockTime = m_AutoLockTimeDlg->m_nAutoLockTime;
			}
			break;
		default:
			break;
		}
	}
}


void CControllerDlg::StatusChangedBlswconnect(BOOL bStatus)
{
	// TODO: 在此处添加消息处理程序代码
	if (bStatus)//開始連接
	{
		StartConnect();
		SetTimer(6, m_nAutoLockTime, NULL);
	}
	else
	{
		KillTimer(0);
		m_bCollecting = FALSE;
		m_BL_btAddCtrl.ShowWindow(SW_SHOW);
		m_pController->PostMessage(WM_STOPCOLLECT, m_nControllerDlgCounter);
		
		m_ParameterListDlg->m_BL_ParameterList.SetReadOnly(m_bLocked);
		m_ParameterListDlg->m_BL_btAddParam.SetEnabled(!m_bLocked);
		m_ParameterListDlg->m_BL_btSaveParam.SetEnabled(!m_bLocked);
		m_ParameterListDlg->m_BL_btLoadParam.SetEnabled(!m_bLocked);
		m_ParameterListDlg->m_BL_ckUpdateData.SetEnabled(!m_bLocked);

		m_DataCollectionDlg->m_BL_DataCollectionList.SetReadOnly(m_bLocked);
		m_DataCollectionDlg->m_BL_btAddData.SetEnabled(!m_bLocked);
		m_DataCollectionDlg->m_BL_btSaveData.SetEnabled(!m_bLocked);
		m_DataCollectionDlg->m_BL_btLoadData.SetEnabled(!m_bLocked);
		
		m_ErrorListDlg->m_BL_ErrorList.SetReadOnly(m_bLocked);
		m_ErrorListDlg->m_BL_edErrorCode.SetEnabled(!m_bLocked);
		m_ErrorListDlg->m_BL_btSaveError.SetEnabled(!m_bLocked);
		m_ErrorListDlg->m_BL_btLoadError.SetEnabled(!m_bLocked);

		m_SmartDotsListDlg->m_BL_SmartDotsList.SetReadOnly(m_bLocked);
		m_SmartDotsListDlg->m_BL_btLoadSmartDots.SetEnabled(!m_bLocked);
		m_SmartDotsListDlg->m_BL_btSaveSmartDots.SetEnabled(!m_bLocked);
		m_SmartDotsListDlg->m_BL_edSmartDotsCode.SetEnabled(!m_bLocked);
		m_SmartDotsListDlg->m_BL_edSmartDotsResult.SetEnabled(!m_bLocked);
		
		m_NewSmartDotsDlg->m_BL_NewSmartDotsList.SetReadOnly(m_bLocked);
		m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.SetEnabled(!m_bLocked);

		m_UDEVisionListDlg->m_BL_UDEVisionList.SetReadOnly(m_bLocked);
		m_UDEVisionListDlg->m_BL_btSaveUDEVision.SetEnabled(!m_bLocked);
		m_UDEVisionListDlg->m_BL_btLoadUDEVision.SetEnabled(!m_bLocked);
		m_UDEVisionListDlg->m_BL_edUDEVisionCode.SetEnabled(!m_bLocked);
		m_UDEVisionListDlg->m_BL_edUDEVisionResult.SetEnabled(!m_bLocked);
		m_UDEVisionListDlg->m_BL_btUDEVisionContinue.SetEnabled(!m_bLocked);
		for (int i = 0; i < 21; i++)
		{
			m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].SetReadOnly(m_bLocked);
		}

		m_SmartLEDListDlg->m_BL_SmartLEDList.SetReadOnly(m_bLocked);
		m_SmartLEDListDlg->m_BL_btSaveSmartLED.SetEnabled(!m_bLocked);
		m_SmartLEDListDlg->m_BL_btLoadSmartLED.SetEnabled(!m_bLocked);
		m_SmartLEDListDlg->m_BL_edSmartLEDCode.SetEnabled(!m_bLocked);
		
		m_SmartRobotListDlg->m_BL_SendSmartRobotList.SetReadOnly(m_bLocked);
		m_SmartRobotListDlg->m_BL_GetSmartRobotList.SetReadOnly(m_bLocked);
		m_SmartRobotListDlg->m_BL_edSmartRobotCode.SetEnabled(!m_bLocked);
		m_SmartRobotListDlg->m_BL_btSaveSmartRobot.SetEnabled(!m_bLocked);
		m_SmartRobotListDlg->m_BL_btLoadSmartRobot.SetEnabled(!m_bLocked);
		
		m_UDEOutlookListDlg->m_BL_UDEOutlookList.SetReadOnly(m_bLocked);
		for (int i = 0; i < 10; i++)
		{
			m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].SetReadOnly(m_bLocked);
		}
		m_UDEOutlookListDlg->m_BL_btSaveUDEOutlook.SetEnabled(!m_bLocked);
		m_UDEOutlookListDlg->m_BL_btLoadUDEOutlook.SetEnabled(!m_bLocked);
		m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.SetEnabled(!m_bLocked);
		m_UDEOutlookListDlg->m_BL_edUDEOutlookResult.SetEnabled(!m_bLocked);
		m_UDEOutlookListDlg->m_BL_btUDEOutlookContinue.SetEnabled(!m_bLocked);
	}
}


void CControllerDlg::StartConnect()
{
	UpdateMsgList();
	UpdateParameterList();
	UpdateDataCollectionList();
	UpdateErrorList();
	UpdateSmartDotsList();
	UpdateUDEVisionList();
	UpdateSmartRobotList();
	UpdateSmartLEDList();
	UpdateUDEOutlookList();
	UpdateNewSmartDots();

	m_ParameterListDlg->PostMessage(WM_PARAM_UPDATE);//詢問是否更新數據


	m_bCollecting = TRUE;
	SetTimer(0, 1 * TIME_RATIO, NULL);
#ifdef _DEBUG
	m_BL_btAddCtrl.ShowWindow(SW_SHOW);
	m_ParameterListDlg->m_BL_ParameterList.SetReadOnly(FALSE);
	m_ParameterListDlg->m_BL_btLoadParam.SetEnabled(TRUE);
	m_ParameterListDlg->m_BL_btAddParam.SetEnabled(TRUE);

	m_DataCollectionDlg->m_BL_DataCollectionList.SetReadOnly(FALSE);
	m_DataCollectionDlg->m_BL_btLoadData.SetEnabled(TRUE);
	m_DataCollectionDlg->m_BL_btAddData.SetEnabled(TRUE);

	m_ErrorListDlg->m_BL_btLoadError.SetEnabled(TRUE);
	m_ErrorListDlg->m_BL_edErrorCode.SetEnabled(TRUE);
	m_ErrorListDlg->m_BL_ErrorList.SetReadOnly(FALSE);

	m_SmartDotsListDlg->m_BL_btLoadSmartDots.SetEnabled(TRUE);
	m_SmartDotsListDlg->m_BL_edSmartDotsCode.SetEnabled(TRUE);
	m_SmartDotsListDlg->m_BL_edSmartDotsResult.SetEnabled(TRUE);
	m_SmartDotsListDlg->m_BL_SmartDotsList.SetReadOnly(FALSE);

	m_NewSmartDotsDlg->m_BL_NewSmartDotsList.SetReadOnly(FALSE);
	m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.SetEnabled(TRUE);

	m_UDEVisionListDlg->m_BL_btLoadUDEVision.SetEnabled(TRUE);
	m_UDEVisionListDlg->m_BL_edUDEVisionCode.SetEnabled(TRUE);
	m_UDEVisionListDlg->m_BL_edUDEVisionResult.SetEnabled(TRUE);
	m_UDEVisionListDlg->m_BL_UDEVisionList.SetReadOnly(FALSE);

	for (int i = 0; i < 21; i++)
	{
		m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].SetReadOnly(FALSE);
	}
	m_UDEVisionListDlg->m_BL_btUDEVisionContinue.SetEnabled(TRUE);

	m_UDEOutlookListDlg->m_BL_btLoadUDEOutlook.SetEnabled(TRUE);
	m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.SetEnabled(TRUE);
	m_UDEOutlookListDlg->m_BL_edUDEOutlookResult.SetEnabled(TRUE);
	m_UDEOutlookListDlg->m_BL_UDEOutlookList.SetReadOnly(FALSE);

	for (int i = 0; i < 10; i++)
	{
		m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].SetReadOnly(FALSE);
	}
	m_UDEOutlookListDlg->m_BL_btUDEOutlookContinue.SetEnabled(TRUE);

	m_SmartRobotListDlg->m_BL_edSmartRobotCode.SetEnabled(TRUE);
	m_SmartRobotListDlg->m_BL_SendSmartRobotList.SetReadOnly(FALSE);
	m_SmartRobotListDlg->m_BL_GetSmartRobotList.SetReadOnly(FALSE);
	m_SmartRobotListDlg->m_BL_btLoadSmartRobot.SetEnabled(TRUE);

	m_SmartLEDListDlg->m_BL_btLoadSmartLED.SetEnabled(TRUE);
	m_SmartLEDListDlg->m_BL_edSmartLEDCode.SetEnabled(TRUE);
	m_SmartLEDListDlg->m_BL_SmartLEDList.SetReadOnly(FALSE);

	
#else
	m_BL_btAddCtrl.ShowWindow(SW_HIDE);
	m_ParameterListDlg->m_BL_ParameterList.SetReadOnly(TRUE);
	m_ParameterListDlg->m_BL_btLoadParam.SetEnabled(FALSE);
	m_ParameterListDlg->m_BL_btAddParam.SetEnabled(FALSE);
	m_DataCollectionDlg->m_BL_DataCollectionList.SetReadOnly(FALSE);
	m_DataCollectionDlg->m_BL_btLoadData.SetEnabled(TRUE);
	m_DataCollectionDlg->m_BL_btAddData.SetEnabled(TRUE);

	m_ErrorListDlg->m_BL_btLoadError.SetEnabled(FALSE);
	m_ErrorListDlg->m_BL_edErrorCode.SetEnabled(FALSE);
	m_ErrorListDlg->m_BL_ErrorList.SetReadOnly(TRUE);

	m_SmartDotsListDlg->m_BL_btLoadSmartDots.SetEnabled(FALSE);
	m_SmartDotsListDlg->m_BL_edSmartDotsCode.SetEnabled(FALSE);
	m_SmartDotsListDlg->m_BL_edSmartDotsResult.SetEnabled(FALSE);
	m_SmartDotsListDlg->m_BL_SmartDotsList.SetReadOnly(TRUE);

	m_NewSmartDotsDlg->m_BL_NewSmartDotsList.SetReadOnly(TRUE);
	m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.SetEnabled(FALSE);

	m_UDEVisionListDlg->m_BL_btLoadUDEVision.SetEnabled(FALSE);
	m_UDEVisionListDlg->m_BL_edUDEVisionCode.SetEnabled(FALSE);
	m_UDEVisionListDlg->m_BL_edUDEVisionResult.SetEnabled(FALSE);
	m_UDEVisionListDlg->m_BL_UDEVisionList.SetReadOnly(TRUE);
	for (int i = 0; i < 21; i++)
	{
		m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].SetReadOnly(TRUE);
	}
	m_UDEVisionListDlg->m_BL_btUDEVisionContinue.SetEnabled(TRUE);

	m_SmartRobotListDlg->m_BL_edSmartRobotCode.SetEnabled(FALSE);
	m_SmartRobotListDlg->m_BL_SendSmartRobotList.SetReadOnly(TRUE);
	m_SmartRobotListDlg->m_BL_GetSmartRobotList.SetReadOnly(TRUE);
	m_SmartRobotListDlg->m_BL_btLoadSmartRobot.SetEnabled(FALSE);

	m_SmartLEDListDlg->m_BL_btLoadSmartLED.SetEnabled(FALSE);
	m_SmartLEDListDlg->m_BL_edSmartLEDCode.SetEnabled(FALSE);
	m_SmartLEDListDlg->m_BL_SmartLEDList.SetReadOnly(TRUE);

	m_UDEOutlookListDlg->m_BL_btLoadUDEOutlook.SetEnabled(FALSE);
	m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.SetEnabled(FALSE);
	m_UDEOutlookListDlg->m_BL_edUDEOutlookResult.SetEnabled(FALSE);
	m_UDEOutlookListDlg->m_BL_UDEOutlookList.SetReadOnly(TRUE);
	for (int i = 0; i < 10; i++)
	{
		m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].SetReadOnly(TRUE);
	}
	m_UDEOutlookListDlg->m_BL_btUDEOutlookContinue.SetEnabled(TRUE);

	
#endif
}

void CControllerDlg::SearchSendData(CString strDataInfo, int nData)
{
	if (m_BL_swConnect.GetStatus())
	{
		CString strTem;
		int nRowNO = 0;//需要寫入數據的行號
		for (int i = 0; i < m_MsgListDlg->m_BL_MsgList.GetRows(); i++)
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 1) == strDataInfo)
			{
				m_MsgListDlg->m_BL_MsgList.SetItemText(i, 9, _T("1"));
				strTem.Format(_T("%d"), nData);
				m_MsgListDlg->m_BL_MsgList.SetItemText(i, 10, strTem);
				nRowNO = i;
				break;
			}
		}
		m_pController->SendMessage(WM_WRITE_DATA, m_nControllerDlgCounter, nRowNO);
	}
}

void CControllerDlg::SearchSendData_Angle(CString strDataInfo, int nData)
{
	if (m_BL_swConnect.GetStatus())
	{
		CString strTem;
		int nRowNO = 0;//需要寫入數據的行號
		for (int i = 0; i < m_MsgListDlg->m_BL_MsgList.GetRows(); i++)
		{
			if (m_MsgListDlg->m_BL_MsgList.GetItemText(i, 1) == strDataInfo)
			{
				m_MsgListDlg->m_BL_MsgList.SetItemText(i, 9, _T("1"));
				strTem.Format(_T("%d"), nData);
				m_MsgListDlg->m_BL_MsgList.SetItemText(i, 10, strTem);
				nRowNO = i;
				break;
			}
		}
		m_pController->SendMessage(WM_WRITE_DATA, m_nControllerDlgCounter, nRowNO);
	}
}

void CControllerDlg::StatusChangedBlswrelayauto(BOOL bStatus)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayAuto, bStatus);
}


void CControllerDlg::StatusChangedBlswrelayunauto(BOOL bStatus)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayUnAuto, bStatus);
}


void CControllerDlg::LBtClickedBlbtrelaystar(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayStar, 3);
}


void CControllerDlg::LBtClickedBlbtrelaystop(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayStop, 3);
}


void CControllerDlg::LBtClickedBlbtrelayreset(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayReset, 3);
}


void CControllerDlg::LBtClickedBlbtrelaypause(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayPause, m_BL_btRelayPause.GetStatus());
}


void CControllerDlg::LBtClickedBlbtrelayerror(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	SearchSendData(m_strRelayError, m_BL_btRelayError.GetStatus());
}



afx_msg LRESULT CControllerDlg::OnGetLockState(WPARAM wParam, LPARAM lParam)
{
	if (wParam > 0)//锁定
	{
		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			m_BL_ckRelay[i].SetEnabled(FALSE);
		}
		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			m_BL_dpRelay[i].SetEnabled(FALSE);
		}
		m_ParameterListDlg->m_BL_ParameterList.SetReadOnly(wParam);
		m_ParameterListDlg->m_BL_btAddParam.SetEnabled(!wParam);
		m_ParameterListDlg->m_BL_btSaveParam.SetEnabled(!wParam);
		m_ParameterListDlg->m_BL_btLoadParam.SetEnabled(!wParam);
		m_ParameterListDlg->m_BL_ckUpdateData.SetEnabled(!wParam);

		m_DataCollectionDlg->m_BL_DataCollectionList.SetReadOnly(wParam);
		m_DataCollectionDlg->m_BL_btAddData.SetEnabled(!wParam);
		m_DataCollectionDlg->m_BL_btSaveData.SetEnabled(!wParam);
		m_DataCollectionDlg->m_BL_btLoadData.SetEnabled(!wParam);

		m_ErrorListDlg->m_BL_ErrorList.SetReadOnly(wParam);
		m_ErrorListDlg->m_BL_edErrorCode.SetEnabled(!wParam);
		m_ErrorListDlg->m_BL_btSaveError.SetEnabled(!wParam);
		m_ErrorListDlg->m_BL_btLoadError.SetEnabled(!wParam);

		m_SmartDotsListDlg->m_BL_SmartDotsList.SetReadOnly(wParam);
		m_SmartDotsListDlg->m_BL_btLoadSmartDots.SetEnabled(!wParam);
		m_SmartDotsListDlg->m_BL_btSaveSmartDots.SetEnabled(!wParam);
		m_SmartDotsListDlg->m_BL_edSmartDotsCode.SetEnabled(!wParam);
		m_SmartDotsListDlg->m_BL_edSmartDotsResult.SetEnabled(!wParam);

		m_NewSmartDotsDlg->m_BL_NewSmartDotsList.SetReadOnly(wParam);
		m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.SetEnabled(!wParam);

		m_UDEVisionListDlg->m_BL_UDEVisionList.SetReadOnly(wParam);
		m_UDEVisionListDlg->m_BL_btSaveUDEVision.SetEnabled(!wParam);
		m_UDEVisionListDlg->m_BL_btLoadUDEVision.SetEnabled(!wParam);
		m_UDEVisionListDlg->m_BL_edUDEVisionCode.SetEnabled(!wParam);
		m_UDEVisionListDlg->m_BL_edUDEVisionResult.SetEnabled(!wParam);
		m_UDEVisionListDlg->m_BL_btUDEVisionContinue.SetEnabled(!wParam);
 		for (int i = 0; i < 21; i++)
 		{
 			m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].SetReadOnly(wParam);
 		}

		m_SmartLEDListDlg->m_BL_SmartLEDList.SetReadOnly(wParam);
		m_SmartLEDListDlg->m_BL_btSaveSmartLED.SetEnabled(!wParam);
		m_SmartLEDListDlg->m_BL_btLoadSmartLED.SetEnabled(!wParam);
		m_SmartLEDListDlg->m_BL_edSmartLEDCode.SetEnabled(!wParam);

		m_SmartRobotListDlg->m_BL_SendSmartRobotList.SetReadOnly(wParam);
		m_SmartRobotListDlg->m_BL_GetSmartRobotList.SetReadOnly(wParam);
		m_SmartRobotListDlg->m_BL_edSmartRobotCode.SetEnabled(!wParam);
		m_SmartRobotListDlg->m_BL_btSaveSmartRobot.SetEnabled(!wParam);
		m_SmartRobotListDlg->m_BL_btLoadSmartRobot.SetEnabled(!wParam);

 		m_UDEOutlookListDlg->m_BL_UDEOutlookList.SetReadOnly(wParam);
		for (int i = 0; i < 10; i++)
		{
			m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].SetReadOnly(wParam);
		}
		m_UDEOutlookListDlg->m_BL_btSaveUDEOutlook.SetEnabled(!wParam);
		m_UDEOutlookListDlg->m_BL_btLoadUDEOutlook.SetEnabled(!wParam);
		m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.SetEnabled(!wParam);
		m_UDEOutlookListDlg->m_BL_edUDEOutlookResult.SetEnabled(!wParam);
		m_UDEOutlookListDlg->m_BL_btUDEOutlookContinue.SetEnabled(!wParam);

	}
	else
	{
		if (m_BL_swConnect.GetStatus())
		{
			SetTimer(6, m_nAutoLockTime, NULL);
		}
		for (int i = 0; i < CK_RELAY_SUM; i++)
		{
			m_BL_ckRelay[i].SetEnabled(TRUE);
		}
		for (int i = 0; i < DP_RELAY_SUM; i++)
		{
			m_BL_dpRelay[i].SetEnabled(TRUE);
		}
		if (!m_BL_swConnect.GetStatus())//处于非联机状态
		{
			m_ParameterListDlg->m_BL_ParameterList.SetReadOnly(wParam);
			m_ParameterListDlg->m_BL_btAddParam.SetEnabled(!wParam);
			m_ParameterListDlg->m_BL_btSaveParam.SetEnabled(!wParam);
			m_ParameterListDlg->m_BL_btLoadParam.SetEnabled(!wParam);
			m_ParameterListDlg->m_BL_ckUpdateData.SetEnabled(!wParam);

			m_DataCollectionDlg->m_BL_DataCollectionList.SetReadOnly(wParam);
			m_DataCollectionDlg->m_BL_btAddData.SetEnabled(!wParam);
			m_DataCollectionDlg->m_BL_btSaveData.SetEnabled(!wParam);
			m_DataCollectionDlg->m_BL_btLoadData.SetEnabled(!wParam);

			m_ErrorListDlg->m_BL_ErrorList.SetReadOnly(wParam);
			m_ErrorListDlg->m_BL_edErrorCode.SetEnabled(!wParam);
			m_ErrorListDlg->m_BL_btSaveError.SetEnabled(!wParam);
			m_ErrorListDlg->m_BL_btLoadError.SetEnabled(!wParam);

			m_SmartDotsListDlg->m_BL_SmartDotsList.SetReadOnly(wParam);
			m_SmartDotsListDlg->m_BL_btLoadSmartDots.SetEnabled(!wParam);
			m_SmartDotsListDlg->m_BL_btSaveSmartDots.SetEnabled(!wParam);
			m_SmartDotsListDlg->m_BL_edSmartDotsCode.SetEnabled(!wParam);
			m_SmartDotsListDlg->m_BL_edSmartDotsResult.SetEnabled(!wParam);

			m_NewSmartDotsDlg->m_BL_NewSmartDotsList.SetReadOnly(wParam);
			m_NewSmartDotsDlg->m_BL_edNewSmartDotsCode.SetEnabled(!wParam);

			m_UDEVisionListDlg->m_BL_UDEVisionList.SetReadOnly(wParam);
			m_UDEVisionListDlg->m_BL_btSaveUDEVision.SetEnabled(!wParam);
			m_UDEVisionListDlg->m_BL_btLoadUDEVision.SetEnabled(!wParam);
			m_UDEVisionListDlg->m_BL_edUDEVisionCode.SetEnabled(!wParam);
			m_UDEVisionListDlg->m_BL_edUDEVisionResult.SetEnabled(!wParam);
			m_UDEVisionListDlg->m_BL_btUDEVisionContinue.SetEnabled(!wParam);
			for (int i = 0; i < 21; i++)
			{
				m_UDEVisionListDlg->m_BL_edUDEVisionRes[i].SetReadOnly(wParam);
			}

			m_SmartLEDListDlg->m_BL_SmartLEDList.SetReadOnly(wParam);
			m_SmartLEDListDlg->m_BL_btSaveSmartLED.SetEnabled(!wParam);
			m_SmartLEDListDlg->m_BL_btLoadSmartLED.SetEnabled(!wParam);
			m_SmartLEDListDlg->m_BL_edSmartLEDCode.SetEnabled(!wParam);

			m_SmartRobotListDlg->m_BL_SendSmartRobotList.SetReadOnly(wParam);
			m_SmartRobotListDlg->m_BL_GetSmartRobotList.SetReadOnly(wParam);
			m_SmartRobotListDlg->m_BL_edSmartRobotCode.SetEnabled(!wParam);
			m_SmartRobotListDlg->m_BL_btSaveSmartRobot.SetEnabled(!wParam);
			m_SmartRobotListDlg->m_BL_btLoadSmartRobot.SetEnabled(!wParam);

			m_UDEOutlookListDlg->m_BL_UDEOutlookList.SetReadOnly(wParam);
 			for (int i = 0; i < 10; i++)
 			{
 				m_UDEOutlookListDlg->m_BL_edUDEOutlookRes[i].SetReadOnly(wParam);
 			}
			m_UDEOutlookListDlg->m_BL_btSaveUDEOutlook.SetEnabled(!wParam);
			m_UDEOutlookListDlg->m_BL_btLoadUDEOutlook.SetEnabled(!wParam);
			m_UDEOutlookListDlg->m_BL_edUDEOutlookCode.SetEnabled(!wParam);
			m_UDEOutlookListDlg->m_BL_edUDEOutlookResult.SetEnabled(!wParam);
			m_UDEOutlookListDlg->m_BL_btUDEOutlookContinue.SetEnabled(!wParam);
		}
	}
	m_ParameterListDlg->m_bParamInpiutLocked = wParam;
	return 0;
}


