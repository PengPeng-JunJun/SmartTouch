// SmartLEDListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "SmartLEDListDlg.h"
#include "afxdialogex.h"


// CSmartLEDListDlg 对话框

IMPLEMENT_DYNAMIC(CSmartLEDListDlg, CTpLayerWnd)

CSmartLEDListDlg::CSmartLEDListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSmartLEDListDlg::IDD, pParent)
	, m_nSmartLEDCode(0)
{

}

CSmartLEDListDlg::CSmartLEDListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nSmartLEDCode(0)
{

}

CSmartLEDListDlg::~CSmartLEDListDlg()
{
}

void CSmartLEDListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_SmartLEDList, m_BL_SmartLEDList);
	DDX_Control(pDX, IDC_BL_edSmartLEDCode, m_BL_edSmartLEDCode);
	DDX_Control(pDX, IDC_BL_btLoadSmartLED, m_BL_btLoadSmartLED);
	DDX_Control(pDX, IDC_BL_btSaveSmartLED, m_BL_btSaveSmartLED);
}


BEGIN_MESSAGE_MAP(CSmartLEDListDlg, CTpLayerWnd)
	ON_MESSAGE(WM_SMARTLED_CODE, &CSmartLEDListDlg::OntReceiveSmartledCode)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CSmartLEDListDlg 消息处理程序


BOOL CSmartLEDListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BL_SmartLEDList.ResetRows(m_BL_SmartLEDList.GetRows(), TRUE);
	m_BL_SmartLEDList.AppendColumn(_T("啟動碼"),DT_CENTER,80,FALSE);
	m_BL_SmartLEDList.AppendColumn(_T("LED檢測軟件名稱"),DT_CENTER,300,FALSE);
	m_BL_SmartLEDList.AppendColumn(_T("結果緩存器"),DT_CENTER,70,FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSmartLEDListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edSmartLEDCode.GetValueText();
		ar << m_BL_SmartLEDList.GetRows();
		for (int i = 0; i < m_BL_SmartLEDList.GetRows(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ar << m_BL_SmartLEDList.GetItemText(i, j);
			}
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edSmartLEDCode.SetValueText(strTem);
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_SmartLEDList.AppendRow(TRUE);
			for (int j = 0; j < 3; j++)
			{
				ar >> strTem;
				m_BL_SmartLEDList.SetItemText(i, j, strTem);
			}
		}

	}
}
BEGIN_EVENTSINK_MAP(CSmartLEDListDlg, CTpLayerWnd)
	ON_EVENT(CSmartLEDListDlg, IDC_BL_edSmartLEDCode, 1, CSmartLEDListDlg::ValueChangedBledsmartledcode, VTS_BSTR)
	ON_EVENT(CSmartLEDListDlg, IDC_BL_SmartLEDList, 2, CSmartLEDListDlg::ItemChangedBlSmartledlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CSmartLEDListDlg, IDC_BL_SmartLEDList, 5, CSmartLEDListDlg::LBtDbClickBlSmartledlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CSmartLEDListDlg, IDC_BL_btSaveSmartLED, 1, CSmartLEDListDlg::LBtClickedBlbtsavesmartled, VTS_I4)
	ON_EVENT(CSmartLEDListDlg, IDC_BL_btLoadSmartLED, 1, CSmartLEDListDlg::LBtClickedBlbtloadsmartled, VTS_I4)
END_EVENTSINK_MAP()


void CSmartLEDListDlg::ValueChangedBledsmartledcode(LPCTSTR strNew)
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
		m_BL_edSmartLEDCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartLEDCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartLEDCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edSmartLEDCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartLEDCode.SetValueText(strInfoOld);
			}
		}
	}
}


void CSmartLEDListDlg::ItemChangedBlSmartledlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
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
			m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("啟動碼只能為數字"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}

	if (nCol == 2)
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
			m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoOld);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoOld);
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_SmartLEDList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
		}
	}
}


void CSmartLEDListDlg::LBtDbClickBlSmartledlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	
}


void CSmartLEDListDlg::LBtClickedBlbtsavesmartled(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.LED"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("LED Files(*.LED)|*.LED|All File(*.*)|*.*||"),this);
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


void CSmartLEDListDlg::LBtClickedBlbtloadsmartled(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CFileDialog dlgFile(TRUE, _T("*.LED"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.LED)|*.LED|All Files(*.*)|*.*||"), this);

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

	for (int i = m_BL_SmartLEDList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_SmartLEDList.DeleteRow(i, FALSE);
	}
	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}


afx_msg LRESULT CSmartLEDListDlg::OntReceiveSmartledCode(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_SmartLEDList.GetRows(); i++)
	{
		//if ((_ttoi(m_BL_SmartLEDList.GetItemText(i, 0)) == m_nSmartLEDCode) || (_ttoi(m_BL_SmartLEDList.GetItemText(i, 0)) == m_nSmartLEDCode - 1))
		//{
		//	CString  strFindWindow;//目标窗口名称
		//	strFindWindow = m_BL_SmartLEDList.GetItemText(i, 1);
		//	HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
		//	if(hWnd == NULL)
		//	{
		//		MsgBox.ShowMsg(_T("未找到目標LED檢測窗口"), _T("查找失敗"), MB_OK);
		//		return 0;
		//	}
		//	TEST_RESULT_INFO Info;
		//	Info.nID = 100;
		//	if (_ttoi(m_BL_SmartLEDList.GetItemText(i, 0)) == m_nSmartLEDCode)//該啟動碼的第一次啟動
		//	{
		//		Info.nParam1 = 0;
		//	}
		//	if (_ttoi(m_BL_SmartLEDList.GetItemText(i, 0)) == m_nSmartLEDCode - 1)//該啟動碼的除第一次以外啟動
		//	{
		//		Info.nParam1 = 1;
		//	}
		//	CString  szInfo;
		//	szInfo = GetTitle();//发送消息的窗口名称
		//	USES_CONVERSION;
		//	memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);

		//	COPYDATASTRUCT Cds;
		//	Cds.dwData = Info.nID;
		//	Cds.cbData = sizeof(TEST_RESULT_INFO);
		//	Cds.lpData = (LPVOID)&Info;
		//	::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		//}

		if (_ttoi(m_BL_SmartLEDList.GetItemText(i, 0)) == m_nSmartLEDCode)
		{
			CString  strFindWindow;//目标窗口名称
			strFindWindow = m_BL_SmartLEDList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//查找目标窗口
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("未找到目標正位度檢測窗口"), _T("查找失敗"), MB_OK);
				return 0;
			}
			TEST_RESULT_INFO Info;
			Info.nID = 100;
			if (_ttoi(m_BL_SmartLEDList.GetItemText(i, 0)) == m_nSmartLEDCode)//該啟動碼的第一次啟動
			{
				Info.nParam1 = 1;
			}

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


BOOL CSmartLEDListDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nInfoID = 0;
	nInfoID = pCopyDataStruct->dwData;

	TEST_RESULT_INFO tagSmartLEDResult;

	memset(tagSmartLEDResult.szInfo , '\0' , TEST_INFO_ARRAY_LEN);
	memset(tagSmartLEDResult.szSrcWnd ,'\0' , TEST_INFO_ARRAY_LEN);
	memcpy(&tagSmartLEDResult, pCopyDataStruct->lpData, pCopyDataStruct->cbData);


	TRACE(_T("\n"));
	TRACE(tagSmartLEDResult.szSrcWnd);
	TRACE(_T("\n"));

	USES_CONVERSION;
	CString strInfo = A2W(tagSmartLEDResult.szSrcWnd);
	//if (tagSmartLEDResult.nID == 9)//收到LED來的消息
	//{
	//	BOOL bIsFind = FALSE;
	//	int nTestRowCounter = 0;
	//	for (int i = 0; i < m_BL_SmartLEDList.GetRows(); i++)
	//	{
	//		if (m_BL_SmartLEDList.GetItemText(i, 1) == strInfo)//窗口名稱相同
	//		{
	//			bIsFind = TRUE;
	//			nTestRowCounter = i;
	//			break;
	//		}
	//		if (bIsFind)
	//		{
	//			break;
	//		}
	//	}
	//	if (tagSmartLEDResult.nParam1 >= 0)//LED測試完成
	//	{
	//		//if (tagSmartLEDResult.nParam4 > 0)
	//		//{
	//			m_pSmartLEDListDlg->PostMessage(WM_SMARTLED_FINISH, nTestRowCounter, tagSmartLEDResult.nParam2);
	//	//	}
	//	}
	//	else//LED多次測試，中途完成
	//	{
	//		//if (tagSmartLEDResult.nParam4 > 0)
	//		//{
	//			m_pSmartLEDListDlg->PostMessage(WM_SMARTLED_FINISH, nTestRowCounter, 32767);
	//		//}
	//	}
	//}

	if (tagSmartLEDResult.nID == 4)//收到正位度來的消息
	{
		BOOL bIsFind = FALSE;
		int nTestRowCounter = 0;
		for (int i = 0; i < m_BL_SmartLEDList.GetRows(); i++)
		{
			if (m_BL_SmartLEDList.GetItemText(i, 1) == strInfo)//窗口名稱相同
			{
				bIsFind = TRUE;
				nTestRowCounter = i;
				break;
			}
			if (bIsFind)
			{
				break;
			}
		}
		if (tagSmartLEDResult.nParam1 == 4)//正位度測試完成
		{
			m_pSmartLEDListDlg->PostMessage(WM_SMARTLED_FINISH, nTestRowCounter, tagSmartLEDResult.nParam2);
		}
		if (tagSmartLEDResult.nParam1 == 3)//正位度拍照完成
		{
			m_pSmartLEDListDlg->PostMessage(WM_SMARTLED_FINISH, nTestRowCounter, 9999);
		}
	}
	return CTpLayerWnd::OnCopyData(pWnd, pCopyDataStruct);

}

