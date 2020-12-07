// NewSmartDots.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "NewSmartDots.h"
#include "afxdialogex.h"


// CNewSmartDots 对话框

IMPLEMENT_DYNAMIC(CNewSmartDots, CTpLayerWnd)

CNewSmartDots::CNewSmartDots(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CNewSmartDots::IDD, pParent)
	, m_nNewSmartDotsCode(0)
{

}

CNewSmartDots::CNewSmartDots(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nNewSmartDotsCode(0)
{

}

CNewSmartDots::~CNewSmartDots()
{

}

void CNewSmartDots::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_NewSmartDotsList, m_BL_NewSmartDotsList);
	DDX_Control(pDX, IDC_BL_edNewSmartDotsCode, m_BL_edNewSmartDotsCode);
}


BEGIN_MESSAGE_MAP(CNewSmartDots, CTpLayerWnd)
	ON_MESSAGE(WM_NEWSMARTDOTS_CODE, &CNewSmartDots::OnNewSmartDotsCode)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CNewSmartDots 消息处理程序


BOOL CNewSmartDots::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_BL_NewSmartDotsList.ResetRows(m_BL_NewSmartDotsList.GetRows(), TRUE);
	m_BL_NewSmartDotsList.AppendColumn(_T("啟動碼"),DT_CENTER,60,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("新焊點檢測軟件名稱"),DT_CENTER,200,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("材料編號"),DT_CENTER,80,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("相機1"),DT_CENTER,70,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("相機2"),DT_CENTER,70,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("相機3"),DT_CENTER,70,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("相機4"),DT_CENTER,70,FALSE);
	m_BL_NewSmartDotsList.AppendColumn(_T("結果緩存器"),DT_CENTER,70,FALSE);

	m_BL_NewSmartDotsList.SetColumnReadOnly(3, TRUE);
	m_BL_NewSmartDotsList.SetColumnReadOnly(4, TRUE);
	m_BL_NewSmartDotsList.SetColumnReadOnly(5, TRUE);
	m_BL_NewSmartDotsList.SetColumnReadOnly(6, TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CNewSmartDots::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edNewSmartDotsCode.GetValueText();
		ar << m_BL_NewSmartDotsList.GetRows();
		for (int i = 0; i < m_BL_NewSmartDotsList.GetRows(); i++)
		{
			for (int j = 0; j < 8; j++)
			{
				ar << m_BL_NewSmartDotsList.GetItemText(i, j);
			}
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edNewSmartDotsCode.SetValueText(strTem);
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_NewSmartDotsList.AppendRow(TRUE);
			for (int j = 0; j < 8; j++)
			{
				ar >> strTem;
				m_BL_NewSmartDotsList.SetItemText(i, j, strTem);
			}
		}
	}
}
BEGIN_EVENTSINK_MAP(CNewSmartDots, CTpLayerWnd)
	ON_EVENT(CNewSmartDots, IDC_BL_edNewSmartDotsCode, 1, CNewSmartDots::ValueChangedBlednewsmartdotscode, VTS_BSTR)
	ON_EVENT(CNewSmartDots, IDC_BL_NewSmartDotsList, 2, CNewSmartDots::ItemChangedBlNewsmartdotslist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CNewSmartDots, IDC_BL_NewSmartDotsList, 5, CNewSmartDots::LBtDbClickBlNewsmartdotslist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
END_EVENTSINK_MAP()


void CNewSmartDots::ValueChangedBlednewsmartdotscode(LPCTSTR strNew)
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
		m_BL_edNewSmartDotsCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edNewSmartDotsCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edNewSmartDotsCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edNewSmartDotsCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edNewSmartDotsCode.SetValueText(strInfoOld);
			}
		}
	}
}


void CNewSmartDots::ItemChangedBlNewsmartdotslist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
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
			m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("啟動碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}

	if (nCol == 7)
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
			m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoOld);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoOld);
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_NewSmartDotsList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
		}
	}
}


void CNewSmartDots::LBtDbClickBlNewsmartdotslist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	if (nCol == 0)
	{
		if (m_BL_NewSmartDotsList.GetReadOnly())
		{
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_NewSmartDotsList.GetItemText(nRow, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標新焊點檢測窗口"), _T("查找失敗"), MB_OK);
				return;
			}
			_tagIpcCopyInfo Info;
			Info.nID = 100;
			for (int j = 3; j <= 6; j++)//相機編號
			{
				if (m_BL_NewSmartDotsList.GetItemText(nRow, j) == _T("●"))
				{
					Info.nParam1 = j - 2;
					break;
				}
			}

			Info.nParam2 = _ttoi(m_BL_NewSmartDotsList.GetItemText(nRow, 2)); //待测试的材料编号
			
			CString  szInfo;
			szInfo = GetTitle();//发送消息的窗口名称
			USES_CONVERSION;
			memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);

			COPYDATASTRUCT Cds;
			Cds.dwData = Info.nID;
			Cds.cbData = sizeof(_tagIpcCopyInfo);
			Cds.lpData = (LPVOID)&Info;
			::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		}
	}
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_NewSmartDotsList.SetDropDownData(_T("1;2;3;4;5;6;7;8;9;10;11;12"));
	}
	if ((nCol >= 3) && (nCol <= 6))
	{
		if (!m_BL_NewSmartDotsList.GetReadOnly())
		{
			if (m_BL_NewSmartDotsList.GetItemText(nRow, nCol) == _T("●"))
			{
				m_BL_NewSmartDotsList.SetItemText(nRow, nCol, _T(""));
			}
			else
			{
				for (int i = 3; i < 7; i++)
				{
					m_BL_NewSmartDotsList.SetItemText(nRow, i, _T(""));
				}
				m_BL_NewSmartDotsList.SetItemText(nRow, nCol, _T("●"));
			}
		}
	}
}


afx_msg LRESULT CNewSmartDots::OnNewSmartDotsCode(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_NewSmartDotsList.GetRows(); i++)
	{
		if (_ttoi(m_BL_NewSmartDotsList.GetItemText(i, 0)) == m_nNewSmartDotsCode)
		{
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_NewSmartDotsList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標焊點檢測窗口"), _T("查找失敗"), MB_OK);
				return 0;
			}
			_tagIpcCopyInfo Info;
			Info.nID = 100;
			for (int j = 3; j <= 6; j++)//相機編號
			{
				if (m_BL_NewSmartDotsList.GetItemText(i, j) == _T("●"))
				{
					Info.nParam1 = j - 2;
					break;
				}
			}

			Info.nParam2 = _ttoi(m_BL_NewSmartDotsList.GetItemText(i, 2)); //待测试的材料编号
			CString  szInfo;
			szInfo = GetTitle();//发送消息的窗口名称
			USES_CONVERSION;
			memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);

			COPYDATASTRUCT Cds;
			Cds.dwData = Info.nID;
			Cds.cbData = sizeof(_tagIpcCopyInfo);
			Cds.lpData = (LPVOID)&Info;
			::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		}
	}
	
	return 0;
}


BOOL CNewSmartDots::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nInfoID = 0;
	nInfoID = pCopyDataStruct->dwData;

	_tagIpcCopyInfo tagInfo;

	memset(tagInfo.szInfo , '\0' , TEST_INFO_ARRAY_LEN);
	memset(tagInfo.szSrcWnd ,'\0' , TEST_INFO_ARRAY_LEN);
	memcpy(&tagInfo, pCopyDataStruct->lpData, pCopyDataStruct->cbData);


	TRACE(_T("\n"));
	TRACE(tagInfo.szSrcWnd);
	TRACE(_T("\n"));

	USES_CONVERSION;
	const CString strWndName = A2W(tagInfo.szSrcWnd);
	if (tagInfo.nID == 1)//收到焊点检测软件发出的消息
	{
		BOOL bIsFind = FALSE;
		int nTestRowCounter = 0;
		for (int i = 0; i < m_BL_NewSmartDotsList.GetRows(); i++)
		{
			if (m_BL_NewSmartDotsList.GetItemText(i, 1) == strWndName)//窗口名稱相同
			{
				if (_ttoi(m_BL_NewSmartDotsList.GetItemText(i, 2)) == tagInfo.nParam2)//材料編號相同
				{
					for (int j = 3; j < 7; j++)
					{
						if (m_BL_NewSmartDotsList.GetItemText(i, j) == _T("●"))
						{
							if ((j - 2) == tagInfo.nParam1)//測試模板相同
							{
								bIsFind = TRUE;
								nTestRowCounter = i;
								break;
							}
						}
					}
				}
			}
			if (bIsFind)
			{
				break;
			}
		}
		if (bIsFind)
		{
			switch (tagInfo.nParam3)
			{
			case -1:
				m_pNewSmartDotsDlg->PostMessage(WM_NEWSMARTDOTS_FINISH, nTestRowCounter, 3);
				break;
			case 0:
				m_pNewSmartDotsDlg->PostMessage(WM_NEWSMARTDOTS_FINISH, nTestRowCounter, 0);
				break;
			case 1:
				m_pNewSmartDotsDlg->PostMessage(WM_NEWSMARTDOTS_FINISH, nTestRowCounter, 1);
				break;
			default:
				break;
			}
		}
		
	}
	return CTpLayerWnd::OnCopyData(pWnd, pCopyDataStruct);
}
