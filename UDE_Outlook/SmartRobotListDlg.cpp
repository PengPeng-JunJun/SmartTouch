// SmartRobotListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "SmartRobotListDlg.h"
#include "afxdialogex.h"


// CSmartRobotListDlg 对话框

IMPLEMENT_DYNAMIC(CSmartRobotListDlg, CTpLayerWnd)

CSmartRobotListDlg::CSmartRobotListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSmartRobotListDlg::IDD, pParent)
	, m_nSmartRobotCode(0)
{

}


CSmartRobotListDlg::CSmartRobotListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nSmartRobotCode(0)
{

}

CSmartRobotListDlg::~CSmartRobotListDlg()
{
}

void CSmartRobotListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_SendSmartRobotList, m_BL_SendSmartRobotList);
	DDX_Control(pDX, IDC_BL_GetSmartRobotList, m_BL_GetSmartRobotList);
	DDX_Control(pDX, IDC_BL_edSmartRobotCode, m_BL_edSmartRobotCode);
	DDX_Control(pDX, IDC_BL_btLoadSmartRobot, m_BL_btLoadSmartRobot);
	DDX_Control(pDX, IDC_BL_btSaveSmartRobot, m_BL_btSaveSmartRobot);
	
}


BEGIN_MESSAGE_MAP(CSmartRobotListDlg, CTpLayerWnd)
	ON_MESSAGE(WM_SMARTROBOT_CODE, &CSmartRobotListDlg::OnReceiveSmartrobotCode)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_SMARTROBOT_FINISH_UDEVISION, &CSmartRobotListDlg::OnReceiveSmartrobotFinishUdevision)
	ON_MESSAGE(WM_SMARTROBOT_FINISH_UDEOUTLOOK, &CSmartRobotListDlg::OnReceiveSmartrobotFinishUdeoutlook)
END_MESSAGE_MAP()


// CSmartRobotListDlg 消息处理程序


BOOL CSmartRobotListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BL_SendSmartRobotList.ResetRows(m_BL_SendSmartRobotList.GetRows(), TRUE);
	m_BL_SendSmartRobotList.AppendColumn(_T("消息碼"),DT_CENTER,65,FALSE);
	m_BL_SendSmartRobotList.AppendColumn(_T("手臂進程名"),DT_CENTER,200,FALSE);
	m_BL_SendSmartRobotList.AppendColumn(_T("手臂消息碼"),DT_CENTER,100,FALSE);
	m_BL_SendSmartRobotList.AppendColumn(_T("手臂消息註解"),DT_CENTER,32,FALSE);


	m_BL_GetSmartRobotList.AppendColumn(_T("消息碼"),DT_CENTER,60,FALSE);
	m_BL_GetSmartRobotList.AppendColumn(_T("手臂進程名"),DT_CENTER,210,FALSE);
	m_BL_GetSmartRobotList.AppendColumn(_T("目標代碼"),DT_CENTER,90,FALSE);
	m_BL_GetSmartRobotList.AppendColumn(_T("目標名稱"),DT_CENTER,130,FALSE);
	m_BL_GetSmartRobotList.AppendColumn(_T("目標消息碼"),DT_CENTER,110,FALSE);
	m_BL_GetSmartRobotList.AppendColumn(_T("存放位置"),DT_CENTER,32,FALSE);
	m_BL_GetSmartRobotList.SetColumnReadOnly(3, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSmartRobotListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edSmartRobotCode.GetValueText();

		ar << m_BL_SendSmartRobotList.GetRows();
		for (int i = 0; i < m_BL_SendSmartRobotList.GetRows(); i++)
		{
			for (int j = 0; j < 4; j++)
			{
				ar << m_BL_SendSmartRobotList.GetItemText(i, j);
			}
		}
		ar << m_BL_GetSmartRobotList.GetRows();
		for (int i = 0; i < m_BL_GetSmartRobotList.GetRows(); i++)
		{
			for (int j = 0; j < 6; j++)
			{
				ar << m_BL_GetSmartRobotList.GetItemText(i, j);
			}
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edSmartRobotCode.SetValueText(strTem);
		
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_SendSmartRobotList.AppendRow(FALSE);
			for (int j = 0; j < 4; j++)
			{
				ar >> strTem;
				m_BL_SendSmartRobotList.SetItemText(i, j, strTem);
			}
		}
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_GetSmartRobotList.AppendRow(FALSE);
			for (int j = 0; j < 6; j++)
			{
				ar >> strTem;
				m_BL_GetSmartRobotList.SetItemText(i, j, strTem);
				if (j == 5)
				{
					if (m_BL_GetSmartRobotList.GetItemText(i, 2) == _T("0"))
					{
						m_BL_GetSmartRobotList.SetItemReadOnly(i, j, FALSE);
					}
					else
					{
						m_BL_GetSmartRobotList.SetItemReadOnly(i, j, TRUE);
					}
				}
			}
		}
	}
}
BEGIN_EVENTSINK_MAP(CSmartRobotListDlg, CTpLayerWnd)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_edSmartRobotCode, 1, CSmartRobotListDlg::ValueChangedBledsmartrobotcode, VTS_BSTR)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_SendSmartRobotList, 2, CSmartRobotListDlg::ItemChangedBlSendsmartrobotlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_SendSmartRobotList, 5, CSmartRobotListDlg::LBtDbClickBlSendsmartrobotlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_GetSmartRobotList, 2, CSmartRobotListDlg::ItemChangedBlGetsmartrobotlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_GetSmartRobotList, 5, CSmartRobotListDlg::LBtDbClickBlGetsmartrobotlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_GetSmartRobotList, 6, CSmartRobotListDlg::ItemEditFinishBlGetsmartrobotlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_btSaveSmartRobot, 1, CSmartRobotListDlg::LBtClickedBlbtsavesmartrobot, VTS_I4)
	ON_EVENT(CSmartRobotListDlg, IDC_BL_btLoadSmartRobot, 1, CSmartRobotListDlg::LBtClickedBlbtloadsmartrobot, VTS_I4)
END_EVENTSINK_MAP()


void CSmartRobotListDlg::ValueChangedBledsmartrobotcode(LPCTSTR strNew)
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
		m_BL_edSmartRobotCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartRobotCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartRobotCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edSmartRobotCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartRobotCode.SetValueText(strInfoOld);
			}
		}
	}
}


void CSmartRobotListDlg::ItemChangedBlSendsmartrobotlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	if ((nCol == 0) || (nCol == 2))//
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
				MsgBox.ShowMsg(_T("消息碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			else
			{
				if (strInfoNew == _T("0"))
				{
					MsgBox.ShowMsg(_T("消息碼不能是0開頭"), _T("ERROR"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			m_BL_SendSmartRobotList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("消息碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_SendSmartRobotList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}
}


void CSmartRobotListDlg::LBtDbClickBlSendsmartrobotlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 0)
	{
		if (m_BL_SendSmartRobotList.GetReadOnly())
		{

		}
	}
	
}


afx_msg LRESULT CSmartRobotListDlg::OnReceiveSmartrobotCode(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_SendSmartRobotList.GetRows(); i++)
	{
		if (m_nSmartRobotCode == _ttoi(m_BL_SendSmartRobotList.GetItemText(i, 0)))//控制碼相同
		{
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_SendSmartRobotList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標手臂窗口"), _T("查找失敗"), MB_OK);
				return 0;
			}
			TEST_RESULT_INFO Info;
			Info.nID = 100;
			Info.nParam1 = _ttoi(m_BL_SendSmartRobotList.GetItemText(i, 2));
			CString  szInfo;
			szInfo = GetTitle();//发送消息的窗口名称
			USES_CONVERSION;
			memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
			COPYDATASTRUCT Cds;
			Cds.dwData = Info.nID;
			Cds.cbData = sizeof(TEST_RESULT_INFO);
			Cds.lpData = (LPVOID)&Info;
			::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		}
	}
	return 0;
}


afx_msg LRESULT CSmartRobotListDlg::OnReceiveSmartrobotFinishUdevision(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	HWND hWnd = ::FindWindow(NULL, m_strRobotStarUDEVisionWnd);//查找目标窗口
	if(hWnd == NULL)
	{
		MsgBox.ShowMsg(_T("未找到目標手臂窗口"), _T("查找失敗"), MB_OK);
		return 0;
	}
	TEST_RESULT_INFO Info;
	Info.nID = 100;
	Info.nParam1 = lParam;
	CString  szInfo;
	szInfo = GetTitle();//发送消息的窗口名称
	USES_CONVERSION;
	memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
	COPYDATASTRUCT Cds;
	Cds.dwData = Info.nID;
	Cds.cbData = sizeof(TEST_RESULT_INFO);
	Cds.lpData = (LPVOID)&Info;
	::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
	return 0;
}


afx_msg LRESULT CSmartRobotListDlg::OnReceiveSmartrobotFinishUdeoutlook(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	HWND hWnd = ::FindWindow(NULL, m_strRobotStarUDEOutlookWnd);//查找目标窗口
	if(hWnd == NULL)
	{
		MsgBox.ShowMsg(_T("未找到目標手臂窗口"), _T("查找失敗"), MB_OK);
		return 0;
	}
	TEST_RESULT_INFO Info;
	Info.nID = 100;
	Info.nParam1 = lParam;
	CString  szInfo;
	szInfo = GetTitle();//发送消息的窗口名称
	USES_CONVERSION;
	memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
	COPYDATASTRUCT Cds;
	Cds.dwData = Info.nID;
	Cds.cbData = sizeof(TEST_RESULT_INFO);
	Cds.lpData = (LPVOID)&Info;
	::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
	return 0;
}


void CSmartRobotListDlg::ItemChangedBlGetsmartrobotlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{

	// TODO: 在此处添加消息处理程序代码
	if ((nCol == 0) || (nCol == 4))//
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
				MsgBox.ShowMsg(_T("消息碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			else
			{
				if (strInfoNew == _T("0"))
				{
					MsgBox.ShowMsg(_T("消息碼不能是0開頭"), _T("ERROR"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("消息碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}
	if (nCol == 5)
	{
		CMsgBox MsgBox(this);
		CString strInfoOld;
		CString strInfoNew;
		strInfoOld = strOld;
		strInfoNew = strNew;
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
			m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoOld);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoOld);
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_GetSmartRobotList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
		}
	}
}


void CSmartRobotListDlg::LBtDbClickBlGetsmartrobotlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 0)
	{
		if (m_BL_GetSmartRobotList.GetReadOnly())
		{

		}
	}
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_GetSmartRobotList.SetDropDownData(_T("0;1;2"));
	}

}


void CSmartRobotListDlg::ItemEditFinishBlGetsmartrobotlist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CString strTem;
	strTem = strNew;
	if (nCol == 2)
	{
		switch (_ttoi(strTem))
		{
		case 0:
			m_BL_GetSmartRobotList.SetItemText(nRow, 3, _T("PLC"));
			m_BL_GetSmartRobotList.SetItemReadOnly(nRow, 5, FALSE);
			break;
		case 1:
			m_BL_GetSmartRobotList.SetItemText(nRow, 3, _T("外觀檢測"));
			m_BL_GetSmartRobotList.SetItemReadOnly(nRow, 5, TRUE);
			break;
		case 2:
			m_BL_GetSmartRobotList.SetItemText(nRow, 3, _T("視覺檢測"));
			m_BL_GetSmartRobotList.SetItemReadOnly(nRow, 5, TRUE);
			break;
		default:
			break;
		}
	}
}


BOOL CSmartRobotListDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
// 	if (m_BL_SendSmartRobotList.GetReadOnly())
// 	{
		int nInfoID = 0;
		nInfoID = pCopyDataStruct->dwData;

		TEST_RESULT_INFO InfoResult;
		memset(InfoResult.szInfo , '\0' , TEST_INFO_ARRAY_LEN);
		memset(InfoResult.szSrcWnd ,'\0' , TEST_INFO_ARRAY_LEN);
		memcpy(&InfoResult, pCopyDataStruct->lpData, pCopyDataStruct->cbData);

		TRACE(_T("\n"));
		TRACE(InfoResult.szSrcWnd);
		TRACE(_T("\n"));

		USES_CONVERSION;
		CString strSrcWnd;
		strSrcWnd = A2W(InfoResult.szSrcWnd);
		if (InfoResult.nID == 2)//收到机械手软件发出的消息
		{
			for(int i = 0; i < m_BL_GetSmartRobotList.GetRows(); i++)
			{
				if (m_BL_GetSmartRobotList.GetItemText(i, 1) == strSrcWnd)
				{
					if (_ttoi(m_BL_GetSmartRobotList.GetItemText(i, 0)) == InfoResult.nParam2)
					{
						switch (InfoResult.nParam1)
						{
						case 0:
							m_pSmartRobotListDlg->PostMessage(WM_SMARTROBOT_FINISH, i, _ttoi(m_BL_GetSmartRobotList.GetItemText(i, 4)));
							break;
						case 1:
							m_strRobotStarUDEVisionWnd = strSrcWnd;
							m_pSmartRobotListDlg->PostMessage(WM_SMARTROBOT_STAR_UDEVISION, _ttoi(m_BL_GetSmartRobotList.GetItemText(i, 4)));
							break;
						case 2:
							m_strRobotStarUDEOutlookWnd = strSrcWnd;
							m_pSmartRobotListDlg->PostMessage(WM_SMARTROBOT_STAR_UDEOUTLOOK, _ttoi(m_BL_GetSmartRobotList.GetItemText(i, 4)));
							break;
						default:
							break;
						}
					}
				}
			}
		}
	//}
	return CTpLayerWnd::OnCopyData(pWnd, pCopyDataStruct);
}


void CSmartRobotListDlg::LBtClickedBlbtsavesmartrobot(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Rob"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Rob Files(*.Rob)|*.Rob|All File(*.*)|*.*||"),this);
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


void CSmartRobotListDlg::LBtClickedBlbtloadsmartrobot(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CFileDialog dlgFile(TRUE, _T("*.Rob"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Rob)|*.Rob|All Files(*.*)|*.*||"), this);

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

	for (int i = m_BL_SendSmartRobotList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_SendSmartRobotList.DeleteRow(i, FALSE);
	}
	for (int i = m_BL_GetSmartRobotList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_GetSmartRobotList.DeleteRow(i, FALSE);
	}

	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}






