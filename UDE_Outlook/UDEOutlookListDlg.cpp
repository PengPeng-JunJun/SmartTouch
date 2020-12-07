// UDEOutlookListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "UDEOutlookListDlg.h"
#include "afxdialogex.h"


// CUDEOutlookListDlg 对话框

IMPLEMENT_DYNAMIC(CUDEOutlookListDlg, CTpLayerWnd)

CUDEOutlookListDlg::CUDEOutlookListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CUDEOutlookListDlg::IDD, pParent)
	, m_nUDEOutlookCode(0)
	, m_nUDEOutlookNO(0)
	, m_nUDEOutlookCodeRobot(0)
	, m_bAutoRestarUDEOutlook(FALSE)
{
	m_vstrUDEOutlookInfo.resize(10);
	m_vstrUDEOutlookRes.resize(10);
	for (int i = 0; i < 10; i++)
	{
		CString strTem;
		strTem.Format(_T("Res%d"), i);
		m_vstrUDEOutlookRes[i] = strTem;
	}
}

CUDEOutlookListDlg::CUDEOutlookListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nUDEOutlookCode(0)
	, m_nUDEOutlookNO(0)
	, m_nUDEOutlookCodeRobot(0)
	, m_bAutoRestarUDEOutlook(FALSE)
{
	m_vstrUDEOutlookInfo.resize(10);
	m_vstrUDEOutlookRes.resize(10);
	for (int i = 0; i < 10; i++)
	{
		CString strTem;
		strTem.Format(_T("Res%d"), i);
		m_vstrUDEOutlookRes[i] = strTem;
	}
}


CUDEOutlookListDlg::~CUDEOutlookListDlg()
{
}

void CUDEOutlookListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_UDEOutlookList, m_BL_UDEOutlookList);
	DDX_Control(pDX, IDC_BL_edUDEOutlookCode, m_BL_edUDEOutlookCode);
	DDX_Control(pDX, IDC_BL_edUDEOutlookResult, m_BL_edUDEOutlookResult);
	DDX_Control(pDX, IDC_BL_btSaveUDEOutlook, m_BL_btSaveUDEOutlook);
	DDX_Control(pDX, IDC_BL_btLoadUDEOutlook, m_BL_btLoadUDEOutlook);
	for (int i = 0; i < 10; i++)
	{
		DDX_Control(pDX, IDC_BL_edUDEOutlookRes_0 + i, m_BL_edUDEOutlookRes[i]);
	}
	DDX_Control(pDX, IDC_BL_btUDEOutlookContinue, m_BL_btUDEOutlookContinue);
	DDX_Control(pDX, IDC_BL_edUDEOutlookInfo, m_BL_edUDEOutlookInfo);
	DDX_Control(pDX, IDC_BL_rdUDEOutlook_PLC, m_BL_rdUDEOutlook_PLC);
	DDX_Control(pDX, IDC_BL_rdUDEOutlook_Robot, m_BL_rdUDEOutlook_Robot);
}


BEGIN_MESSAGE_MAP(CUDEOutlookListDlg, CTpLayerWnd)
	ON_WM_TIMER()
	ON_MESSAGE(WM_ED_UDEOUTLOOK_RES, &CUDEOutlookListDlg::OnEdUdeoutlookRes)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_UDEOUTLOOK_CODE, &CUDEOutlookListDlg::OnReceiveUdeoutlookCode)
	ON_MESSAGE(WM_UDEOUTLOOK_CODE_ROBOT, &CUDEOutlookListDlg::OnReceiveUdeoutlookCodeRobot)
END_MESSAGE_MAP()


// CUDEOutlookListDlg 消息处理程序

BOOL CUDEOutlookListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BL_UDEOutlookList.ResetRows(m_BL_UDEOutlookList.GetRows(), TRUE);
	m_BL_UDEOutlookList.AppendColumn(_T("啟動碼"),DT_CENTER,70,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("視覺檢測軟件名稱"),DT_CENTER,300,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("0"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("1"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("2"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("3"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("4"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("5"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("6"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("7"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("8"),DT_CENTER,32,FALSE);
	m_BL_UDEOutlookList.AppendColumn(_T("9"),DT_CENTER,32,FALSE);

	for (int i = 2; i < 12; i++)
	{
		m_BL_UDEOutlookList.SetColumnReadOnly(i, TRUE);
	}
	SetTimer(0, 1, nullptr);
	SetTimer(1, 1, nullptr);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



void CUDEOutlookListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edUDEOutlookCode.GetValueText();

		for (int i = 0; i < 10; i++)
		{
			ar << m_BL_edUDEOutlookRes[i].GetValueText();
		}

		ar << m_BL_UDEOutlookList.GetRows();
		for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
		{
			for (int j = 0; j < UDEOUTLOOK_COLS_COUNTER; j++)
			{
				ar << m_BL_UDEOutlookList.GetItemText(i, j);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			ar << m_vstrUDEOutlookInfo[i];
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edUDEOutlookCode.SetValueText(strTem);
		for (int i = 0; i < 10; i++)
		{
			ar >> strTem;
			m_BL_edUDEOutlookRes[i].SetValueText(strTem);
		}
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_UDEOutlookList.AppendRow(FALSE);
			for (int j = 0; j < UDEOUTLOOK_COLS_COUNTER; j++)
			{
				ar >> strTem;
				m_BL_UDEOutlookList.SetItemText(i, j, strTem);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			ar >> m_vstrUDEOutlookInfo[i];
		}
	}
}



void CUDEOutlookListDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		if (!m_BL_UDEOutlookList.GetReadOnly())
		{
			for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
			{
				for (int j = 2; j < UDEOUTLOOK_COLS_COUNTER; j++)
				{
					m_BL_UDEOutlookList.SetItemTextColor(i, j, RGB(0,255,230));
				}
			}
		}
		SetTimer(0, 1, nullptr);
		break;
	case 1:
		KillTimer(1);
		if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL)) 
		{
			for (int i = 0; i < 10; i++)
			{
				m_BL_edUDEOutlookRes[i].SetCaption(m_vstrUDEOutlookRes[i]);
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				m_BL_edUDEOutlookRes[i].SetCaption(m_vstrUDEOutlookRes[i]);
			}
		}
		SetTimer(1, 1, nullptr);
		break;
	case 2:
		KillTimer(2);
		_KillProcess(PROCESS_NAME);
		SetTimer(3, RESET_DELAY, nullptr);
// 		Sleep(RESET_DELAY);
// 		_OpenProcess(PROCESS_PATH);
//  		Sleep(RESTAR_DELAY);
// 
// 		for (int i = 0; i < 4; i++)
// 		{
// 			m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, i, 1);
// 			Sleep(1);
// 		}
		break;
	case 3:
		KillTimer(3);
		_OpenProcess(PROCESS_PATH);
		SetTimer(4, RESTAR_DELAY, nullptr);
		break;
	case 4:
		KillTimer(4);
		for (int i = 0; i < 4; i++)
		{
			m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, i, 1);
			Sleep(1);
		}
		break;
	default:
		break;
	}
	CTpLayerWnd::OnTimer(nIDEvent);
}

afx_msg LRESULT CUDEOutlookListDlg::OnEdUdeoutlookRes(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_BL_edUDEOutlookRes[i].IsMsgSrc())
			{
				m_nUDEOutlookNO = i;
				m_BL_edUDEOutlookInfo.SetValueText(m_vstrUDEOutlookInfo[i]);
				CMsgBox MsgBox(this);
				CString strInfoOld;
				CString strInfoNew;
				strInfoNew = m_BL_edUDEOutlookRes[i].GetValueText();
				strInfoOld = m_BL_edUDEOutlookRes[i].GetValueText();
				strInfoOld.Delete(strInfoNew.GetLength() - 1, 1);

				strInfoNew.MakeUpper();
				strInfoOld.MakeUpper();

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
					if((strInfoNew != _T("D")) && (strInfoNew != _T("R")))
					{
						CString strErrInfo;
						strErrInfo.Format(_T("該設備不支持 %s 類型緩存器數據讀取"), strInfoNew);
						MsgBox.ShowMsg(strErrInfo, _T("無法獲取"), MB_ICONSTOP | MB_OK);
						strInfoNew = _T("");
					}
					m_BL_edUDEOutlookRes[i].SetValueText(strInfoNew);
				}
				else
				{
					CString strAddress;
					if (strInfoNew[0] == 'R')
					{
						if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
						{
							MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
							m_BL_edUDEOutlookRes[i].SetValueText(strInfoOld);
						}
						strInfoNew.Delete(0, 1);
						int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
						if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
						{
							MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
							m_BL_edUDEOutlookRes[i].SetValueText(strInfoOld);
						}
					}
					if (strInfoNew[0] == 'D')
					{
						if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
						{
							m_BL_edUDEOutlookRes[i].SetValueText(strInfoOld);
							MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
						}
						strInfoNew.Delete(0, 1);
						int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
						if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
						{
							MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
							m_BL_edUDEOutlookRes[i].SetValueText(strInfoOld);
						}
					}
				}
			}
		}
	}
	return 0;
}

BEGIN_EVENTSINK_MAP(CUDEOutlookListDlg, CTpLayerWnd)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_rdUDEOutlook_PLC, 1, CUDEOutlookListDlg::StatusChangedBlrdudeoutlookPlc, VTS_BOOL)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_rdUDEOutlook_Robot, 1, CUDEOutlookListDlg::StatusChangedBlrdudeoutlookRobot, VTS_BOOL)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_edUDEOutlookCode, 1, CUDEOutlookListDlg::ValueChangedBledudeoutlookcode, VTS_BSTR)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_btSaveUDEOutlook, 1, CUDEOutlookListDlg::LBtClickedBlbtsaveudeoutlook, VTS_I4)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_btLoadUDEOutlook, 1, CUDEOutlookListDlg::LBtClickedBlbtloadudeoutlook, VTS_I4)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_UDEOutlookList, 2, CUDEOutlookListDlg::ItemChangedBlUdeoutlooklist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_UDEOutlookList, 5, CUDEOutlookListDlg::LBtDbClickBlUdeoutlooklist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_UDEOutlookList, 6, CUDEOutlookListDlg::ItemEditFinishBlUdeoutlooklist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CUDEOutlookListDlg, IDC_BL_btUDEOutlookContinue, 1, CUDEOutlookListDlg::LBtClickedBlbtudeoutlookcontinue, VTS_I4)
END_EVENTSINK_MAP()


void CUDEOutlookListDlg::StatusChangedBlrdudeoutlookPlc(BOOL bNewStatus)
{
	// TODO: 在此处添加消息处理程序代码
	m_BL_rdUDEOutlook_Robot.SetSelect(!bNewStatus);
}


void CUDEOutlookListDlg::StatusChangedBlrdudeoutlookRobot(BOOL bNewStatus)
{
	// TODO: 在此处添加消息处理程序代码
	m_BL_rdUDEOutlook_PLC.SetSelect(!bNewStatus);
}



void CUDEOutlookListDlg::ValueChangedBledudeoutlookcode(LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	CString strInfoOld;
	CString strInfoNew;
	strInfoNew = strNew;
	strInfoOld = strNew;
	strInfoOld.Delete(strInfoNew.GetLength() - 1, 1);

	strInfoNew.MakeUpper();
	strInfoOld.MakeUpper();

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
		if((strInfoNew != _T("D")) && (strInfoNew != _T("R")))
		{
			CString strErrInfo;
			strErrInfo.Format(_T("該設備不支持 %s 類型緩存器數據讀取"), strInfoNew);
			MsgBox.ShowMsg(strErrInfo, _T("無法獲取"), MB_ICONSTOP | MB_OK);
			strInfoNew = _T("");
		}
		m_BL_edUDEOutlookCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edUDEOutlookCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edUDEOutlookCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edUDEOutlookCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edUDEOutlookCode.SetValueText(strInfoOld);
			}
		}
	}
}


void CUDEOutlookListDlg::LBtClickedBlbtsaveudeoutlook(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Out"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Out Files(*.Out)|*.Out|All File(*.*)|*.*||"),this);
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
	if (!file.Open(strPath,CFile::modeWrite| CFile::modeCreate,&FileEX))
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


void CUDEOutlookListDlg::LBtClickedBlbtloadudeoutlook(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CFileDialog dlgFile(TRUE, _T("*.Out"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Out)|*.Out|All Files(*.*)|*.*||"), this);

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

	for (int i = m_BL_UDEOutlookList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_UDEOutlookList.DeleteRow(i, FALSE);
	}
	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}


void CUDEOutlookListDlg::ItemChangedBlUdeoutlooklist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 0)
	{
		CMsgBox MsgBox(this);
		CString strInfoOld;
		CString strInfoNew;
		strInfoOld = strOld;
		strInfoNew = strNew;
		if (strInfoNew.GetLength() == 1)
		{
			if ((strInfoNew[0] < '0') || (strInfoNew[0] > '9'))
			{
				MsgBox.ShowMsg(_T("啟動碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			else
			{
				if (strInfoNew == _T("0"))
				{
					MsgBox.ShowMsg(_T("啟動碼不能是0開頭"), _T("ERROR"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			m_BL_UDEOutlookList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("啟動碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_UDEOutlookList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}
}


void CUDEOutlookListDlg::LBtDbClickBlUdeoutlooklist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	if (nCol == 0)
	{
		if (m_BL_UDEOutlookList.GetReadOnly())//雙擊測試碼，進行測試
		{
			m_nUDEOutlookCode = _ttoi(m_BL_UDEOutlookList.GetItemText(nRow, 0));
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_UDEOutlookList.GetItemText(nRow, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標視覺檢測窗口"), _T("查找失敗"), MB_OK);
				return;
			}
			TEST_INFO Info;
			Info.nID = 100;
			int nStarCounter = 0;
			for (int j = 2; j < 12; j++)
			{
				if (m_BL_UDEOutlookList.GetItemText(nRow, j) != _T(""))
				{
					nStarCounter++;
					Info.byStarGroup[nStarCounter - 1] = j - 2;
				}
			}
			if (nStarCounter > 0)
			{
				Info.nParam2 = nStarCounter;    //待测试的群組编号
				CString  szInfo;
				szInfo = GetTitle();//发送消息的窗口名称
				USES_CONVERSION;
				memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
				COPYDATASTRUCT Cds;
				Cds.dwData = Info.nID;
				Cds.cbData = sizeof(TEST_INFO);
				Cds.lpData = (LPVOID)&Info;
				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
				if (m_bAutoRestarUDEOutlook)
				{
					SetTimer(2, WAIT_DELAY, nullptr);
				}
			}
		}
	}
	if (nCol > 1)
	{
		if (!m_BL_UDEOutlookList.GetReadOnly())
		{
			if (m_BL_edUDEOutlookRes[nCol - 2].GetValueText().GetLength() > 1)
			{
				if (m_BL_UDEOutlookList.GetItemText(nRow, nCol) == _T(""))
				{
					m_BL_UDEOutlookList.SetItemText(nRow, nCol, _T("●"));
				}
				else
				{
					m_BL_UDEOutlookList.SetItemText(nRow, nCol, _T(""));
				}
			}
			else
			{
				MsgBox.ShowMsg(_T("未輸入該群組結果緩存器"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				return;
			}
		}
		else
		{
			if (nFlags & MK_CONTROL)
			{
				if (m_BL_rdUDEOutlook_PLC.GetSelect())
				{
					if (m_BL_edUDEOutlookRes[nCol - 2].GetValueText().GetLength() > 1)
					{
						m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, nCol - 2, 1);
						return;
					}
				}
				if (m_BL_rdUDEOutlook_Robot.GetSelect())
				{
					m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH_ROBOT, nCol - 2, 1);
					return;
				}
			}
			if (nFlags & MK_SHIFT)
			{
				if (m_BL_rdUDEOutlook_PLC.GetSelect())
				{
					if (m_BL_edUDEOutlookRes[nCol - 2].GetValueText().GetLength() > 1)
					{
						m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, nCol - 2, 0);
						return;
					}
				}
				if (m_BL_rdUDEOutlook_Robot.GetSelect())
				{
					m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH_ROBOT, nCol - 2, 0);
					return;
				}
			}
		}
	}
}


void CUDEOutlookListDlg::ItemEditFinishBlUdeoutlooklist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	CString strTem = strNew;
	if (nCol == 0)
	{
		if(strTem == _T("0"))
		{
			MsgBox.ShowMsg(_T("錯誤碼必須是大於0的數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
			m_BL_UDEOutlookList.SetItemText(nRow, nCol, _T(""));
		}
	}
}


void CUDEOutlookListDlg::LBtClickedBlbtudeoutlookcontinue(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
// 	SetTimer(2, WAIT_DELAY, nullptr);
 	//m_nUDEOutlookCode = _ttoi(m_BL_UDEOutlookList.GetItemText(0, 0));

	//_KillProcess(_T("UDE_Outlook.exe"));
	_OpenProcess(PROCESS_PATH);
 	return;
	CMsgBox MsgBox(this);
	if (m_BL_rdUDEOutlook_PLC.GetSelect())
	{
		if (m_nUDEOutlookCode != 0)
		{
			for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
			{
				if (_ttoi(m_BL_UDEOutlookList.GetItemText(i, 0)) == m_nUDEOutlookCode)
				{
					CString  strFindWindow;//目标窗口名称
					strFindWindow = m_BL_UDEOutlookList.GetItemText(i, 1);
					HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
					if(hWnd == NULL)
					{
						MsgBox.ShowMsg(_T("未找到目標視覺測窗口"), _T("查找失敗"), MB_OK);
						return ;
					}
					TEST_INFO Info;
					Info.nID = 100;
					int nStarCounter = 0;
					for (int j = 2; j < 12; j++)
					{
						if (m_BL_UDEOutlookList.GetItemText(i, j) != _T(""))
						{
							nStarCounter++;
							Info.byStarGroup[nStarCounter - 1] = j - 2;
						}
					}
					if (nStarCounter > 0)
					{
						Info.nParam2 = nStarCounter;    //待测试的群組编号
						CString  szInfo;
						szInfo = GetTitle();//发送消息的窗口名称
						USES_CONVERSION;
						memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
						COPYDATASTRUCT Cds;
						Cds.dwData = Info.nID;
						Cds.cbData = sizeof(TEST_INFO);
						Cds.lpData = (LPVOID)&Info;
						::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
						if (m_bAutoRestarUDEOutlook)
						{
							SetTimer(2, WAIT_DELAY, nullptr);
						}
					}
				}
			}
		}
	}
	if (m_BL_rdUDEOutlook_Robot.GetSelect())
	{
		if (m_nUDEOutlookCodeRobot != 0)
		{
			for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
			{
				if (_ttoi(m_BL_UDEOutlookList.GetItemText(i, 0)) == m_nUDEOutlookCodeRobot)
				{
					CString  strFindWindow;//目标窗口名称
					strFindWindow = m_BL_UDEOutlookList.GetItemText(i, 1);
					HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
					if(hWnd == NULL)
					{
						MsgBox.ShowMsg(_T("未找到目標視覺檢測窗口"), _T("查找失敗"), MB_OK);
						return ;
					}
					TEST_INFO Info;
					Info.nID = 100;
					int nStarCounter = 0;
					for (int j = 2; j < 12; j++)
					{
						if (m_BL_UDEOutlookList.GetItemText(i, j) != _T(""))
						{
							nStarCounter++;
							Info.byStarGroup[nStarCounter - 1] = j - 2;
						}
					}
					if (nStarCounter > 0)
					{
						Info.nParam2 = nStarCounter;    //待测试的群組编号
						m_vbyRobotStarUDEOutlookGroup.clear();
						for (int i = 0; i < nStarCounter; i++)
						{
							m_vbyRobotStarUDEOutlookGroup.push_back(Info.byStarGroup[i]);
						}
						CString  szInfo;
						szInfo = GetTitle();//发送消息的窗口名称
						USES_CONVERSION;
						memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
						COPYDATASTRUCT Cds;
						Cds.dwData = Info.nID;
						Cds.cbData = sizeof(TEST_INFO);
						Cds.lpData = (LPVOID)&Info;
						::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
						if (m_bAutoRestarUDEOutlook)
						{
							SetTimer(2, WAIT_DELAY, nullptr);
						}
					}
				}
			}
		}
	}
}


BOOL CUDEOutlookListDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nInfoID = 0;
	nInfoID = pCopyDataStruct->dwData;

	TEST_INFO tagUDEOutlookResult;

	memset(tagUDEOutlookResult.szInfo , '\0' , TEST_INFO_ARRAY_LEN);
	memset(tagUDEOutlookResult.szSrcWnd ,'\0' , TEST_INFO_ARRAY_LEN);
	memcpy(&tagUDEOutlookResult, pCopyDataStruct->lpData, pCopyDataStruct->cbData);


	TRACE(_T("\n"));
	TRACE(tagUDEOutlookResult.szSrcWnd);
	TRACE(_T("\n"));

	USES_CONVERSION;
	CString strInfo = A2W(tagUDEOutlookResult.szSrcWnd);
	if (tagUDEOutlookResult.nID == 20)
	{
		for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
		{
			if (m_BL_UDEOutlookList.GetItemText(i, tagUDEOutlookResult.nParam2 + 2) != _T(""))
			{
				if (tagUDEOutlookResult.nParam1 == 6666)
				{
// 					switch (tagUDEOutlookResult.nParam1)
// 					{
// 					case 0://NG
// 						m_BL_UDEOutlookList.SetItemTextColor(i, tagUDEOutlookResult.nParam2 + 2, RGB(255,0,0));
// 						break;
// 					case 1://PASS
// 						m_BL_UDEOutlookList.SetItemTextColor(i, tagUDEOutlookResult.nParam2 + 2, RGB(0,255,0));
// 						break;
// 					default:
//						break;
// 					}
					m_BL_UDEOutlookList.SetItemTextColor(i, tagUDEOutlookResult.nParam2 + 2, RGB(0,0,255));
				}
				else if (tagUDEOutlookResult.nParam1 == 9999)//拍照完成
				{
					m_BL_UDEOutlookList.SetItemTextColor(i, tagUDEOutlookResult.nParam2 + 2, RGB(0,0,255));
				}
				else
				{
					m_BL_UDEOutlookList.SetItemTextColor(i, tagUDEOutlookResult.nParam2 + 2, RGB(255, 155, 32));
				}
			}
		}
		BOOL bResDispose = FALSE;//結果被處理
		for (size_t i = 0; i < m_vbyRobotStarUDEOutlookGroup.size(); i++)
		{
			if (tagUDEOutlookResult.nParam2 == m_vbyRobotStarUDEOutlookGroup[i])
			{
				bResDispose = TRUE;
// 				m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH_ROBOT, tagUDEOutlookResult.nParam2, tagUDEOutlookResult.nParam1);
// 				if ((tagUDEOutlookResult.nParam1 == 0) || (tagUDEOutlookResult.nParam1 == 1))//收到測試結果
// 				{
// 					m_vbyRobotStarUDEOutlookGroup.erase(m_vbyRobotStarUDEOutlookGroup.begin() + i);
// 				}
				break;
			}
		}
		if (!bResDispose)
		{
			//m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, tagUDEOutlookResult.nParam2, tagUDEOutlookResult.nParam1);

			if (tagUDEOutlookResult.nParam1 == 9999)
			{
				m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, 9999);
			}
			else if (tagUDEOutlookResult.nParam1 == 6666)
			{
				KillTimer(2);
				const int nResCounter = tagUDEOutlookResult.nResCounter;
				for (int i = 0; i < nResCounter; i++)
				{
					m_pUDEOutlookListDlg->PostMessage(WM_UDEOUTLOOK_FINISH, i, tagUDEOutlookResult.Result[i]);
					Sleep(1);
				}
			}
		}		
	}
	return CTpLayerWnd::OnCopyData(pWnd, pCopyDataStruct);
}


afx_msg LRESULT CUDEOutlookListDlg::OnReceiveUdeoutlookCode(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
	{
		if (_ttoi(m_BL_UDEOutlookList.GetItemText(i, 0)) == m_nUDEOutlookCode)
		{
			for (int j = 2; j < 12; j++)
			{
				m_BL_UDEOutlookList.SetItemTextColor(i, j, RGB(128,128,128));
			}
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_UDEOutlookList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標視覺檢測窗口"), _T("查找失敗"), MB_OK);
				return 0;
			}
			TEST_INFO Info;
			Info.nID = 100;
			int nStarCounter = 0;
			for (int j = 2; j < 12; j++)
			{
				if (m_BL_UDEOutlookList.GetItemText(i, j) != _T(""))
				{
					nStarCounter++;
					Info.byStarGroup[nStarCounter - 1] = j - 2;
				}
			}
			if (nStarCounter > 0)
			{
				Info.nParam2 = nStarCounter;    //待测试的群組编号
				CString  szInfo;
				szInfo = GetTitle();//发送消息的窗口名称
				USES_CONVERSION;
				memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
				COPYDATASTRUCT Cds;
				Cds.dwData = Info.nID;
				Cds.cbData = sizeof(TEST_INFO);
				Cds.lpData = (LPVOID)&Info;
				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
				if (m_bAutoRestarUDEOutlook)
				{
					SetTimer(2, WAIT_DELAY, nullptr);
				}
			}
			break;
		}
	}
	return 0;
}


afx_msg LRESULT CUDEOutlookListDlg::OnReceiveUdeoutlookCodeRobot(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_UDEOutlookList.GetRows(); i++)
	{
		if (_ttoi(m_BL_UDEOutlookList.GetItemText(i, 0)) == m_nUDEOutlookCodeRobot)
		{
			for (int j = 2; j < 12; j++)
			{
				m_BL_UDEOutlookList.SetItemTextColor(i, j, RGB(128,128,128));
			}
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_UDEOutlookList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標視覺檢測窗口"), _T("查找失敗"), MB_OK);
				return 0;
			}
			TEST_INFO Info;
			Info.nID = 100;
			int nStarCounter = 0;
			for (int j = 2; j < 12; j++)
			{
				if (m_BL_UDEOutlookList.GetItemText(i, j) != _T(""))
				{
					nStarCounter++;
					Info.byStarGroup[nStarCounter - 1] = j - 2;
				}
			}
			if (nStarCounter > 0)
			{
				Info.nParam2 = nStarCounter;    //待测试的群組编号
				m_vbyRobotStarUDEOutlookGroup.clear();
				for (int i = 0; i < nStarCounter; i++)
				{
					m_vbyRobotStarUDEOutlookGroup.push_back(Info.byStarGroup[i]);
				}
				CString  szInfo;
				szInfo = GetTitle();//发送消息的窗口名称
				USES_CONVERSION;
				memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
				COPYDATASTRUCT Cds;
				Cds.dwData = Info.nID;
				Cds.cbData = sizeof(TEST_INFO);
				Cds.lpData = (LPVOID)&Info;
				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));

				if (m_bAutoRestarUDEOutlook)
				{
					SetTimer(2, WAIT_DELAY, nullptr);
				}
			}
			break;
		}
	}
	return 0;
}


void CUDEOutlookListDlg::_OpenProcess(CString sExeName)
{
	SHELLEXECUTEINFO sys2_shell = {sizeof(sys2_shell)};
	sys2_shell.fMask = SEE_MASK_FLAG_DDEWAIT;
	sys2_shell.lpVerb = _T("open");
	sys2_shell.lpFile = sExeName;
	sys2_shell.nShow = SW_NORMAL;
	ShellExecuteEx(&sys2_shell);
}


void CUDEOutlookListDlg::_KillProcess(CString sExeName)
{
	HANDLE hSnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapShot == 0)
	{
		return;
	}
	PROCESSENTRY32 thePE;
	thePE.dwSize = sizeof(PROCESSENTRY32);

	bool Status = Process32First(hSnapShot, &thePE);
	bool bHaveFlag = false;
	DWORD ProcessID = 0;

	while (Status)
	{
		Status = Process32Next(hSnapShot, &thePE);

		CString sFindName = thePE.szExeFile;
		CString sTemp = sExeName.Mid(0, sFindName.GetLength());

		if (sFindName == sTemp)
		{
			bHaveFlag = true;
			ProcessID = thePE.th32ProcessID;;

			if (!TerminateProcess(OpenProcess (PROCESS_TERMINATE||PROCESS_QUERY_INFORMATION,false,ProcessID),0))
			{
				MessageBox(_T("无法终止进程"));
			}
			else
			{
				break;
			}
		}
	}
	CloseHandle(hSnapShot);
}


void CUDEOutlookListDlg::_KillProcess(DWORD Pid)
{
	//打开进程得到进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,Pid);
	if(hProcess == NULL)
	{ 		
		printf("OpenProcess error\n");
		return;
	}
	//结束进程
	if (TerminateProcess(hProcess,0))
	{
		printf("结束进程成功\n");
		return ;
	}
	else
	{
		printf("结束进程失败\n");
		return ;
	}	
}
