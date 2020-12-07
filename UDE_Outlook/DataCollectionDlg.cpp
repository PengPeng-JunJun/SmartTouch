// DataCollectionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "DataCollectionDlg.h"
#include "afxdialogex.h"


// CDataCollectionDlg 对话框

IMPLEMENT_DYNAMIC(CDataCollectionDlg, CTpLayerWnd)

CDataCollectionDlg::CDataCollectionDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	
{
}




CDataCollectionDlg::CDataCollectionDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CDataCollectionDlg::IDD, pParent)
{

}

CDataCollectionDlg::~CDataCollectionDlg()
{
}

void CDataCollectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_DataCollectionList, m_BL_DataCollectionList);
	DDX_Control(pDX, IDC_BL_btSaveData, m_BL_btSaveData);
	DDX_Control(pDX, IDC_BL_btLoadData, m_BL_btLoadData);
	DDX_Control(pDX, IDC_BL_btAddData, m_BL_btAddData);
}


BEGIN_MESSAGE_MAP(CDataCollectionDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CDataCollectionDlg 消息处理程序

void CDataCollectionDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}

BOOL CDataCollectionDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();
	m_BL_DataCollectionList.ResetRows(m_BL_DataCollectionList.GetRows(), TRUE);
	m_BL_DataCollectionList.AppendColumn(_T("編號"),DT_CENTER,70,FALSE);
	m_BL_DataCollectionList.AppendColumn(_T("寄存器名"),DT_CENTER,100,FALSE);
	m_BL_DataCollectionList.AppendColumn(_T("數據位數"),DT_CENTER,100,FALSE);
	m_BL_DataCollectionList.AppendColumn(_T("數據名稱"),DT_CENTER,270,FALSE);
	m_BL_DataCollectionList.AppendColumn(_T("小數位數"),DT_CENTER,105,FALSE);
	m_BL_DataCollectionList.AppendColumn(_T("單位"),DT_CENTER,100,FALSE);
	m_BL_DataCollectionList.AppendColumn(_T("值"),DT_CENTER,110,FALSE);

	m_BL_DataCollectionList.SetColumnReadOnly(6, TRUE);

	m_ParameterAdd.CreateBlendWnd(IDD_PARAMETER, this);

	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}
BEGIN_EVENTSINK_MAP(CDataCollectionDlg, CTpLayerWnd)
	ON_EVENT(CDataCollectionDlg, IDC_BL_DataCollectionList, 2, CDataCollectionDlg::ItemChangedBlDatacollectionlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CDataCollectionDlg, IDC_BL_DataCollectionList, 5, CDataCollectionDlg::LBtDbClickBlDatacollectionlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CDataCollectionDlg, IDC_BL_DataCollectionList, 6, CDataCollectionDlg::ItemEditFinishBlDatacollectionlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CDataCollectionDlg, IDC_BL_btSaveData, 1, CDataCollectionDlg::LBtClickedBlbtsavedata, VTS_I4)
	ON_EVENT(CDataCollectionDlg, IDC_BL_btLoadData, 1, CDataCollectionDlg::LBtClickedBlbtloaddata, VTS_I4)
	ON_EVENT(CDataCollectionDlg, IDC_BL_btAddData, 1, CDataCollectionDlg::LBtClickedBlbtadddata, VTS_I4)
END_EVENTSINK_MAP()


void CDataCollectionDlg::ItemChangedBlDatacollectionlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	CString strInfoOld;
	CString strInfoNew;
	strInfoOld = strOld;
	strInfoNew = strNew;
	strInfoNew.MakeUpper();
	strInfoOld.MakeUpper();
	if (nCol == 1)
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
			if((strInfoNew != _T("D")) && (strInfoNew != _T("R")))
			{
				CString strErrInfo;
				strErrInfo.Format(_T("該設備不支持 %s 類型緩存器數據讀取"), strInfoNew);
				MsgBox.ShowMsg(strErrInfo, _T("無法獲取"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			m_BL_DataCollectionList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_DataCollectionList.SetItemText(nRow, nCol, strInfoOld);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_DataCollectionList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					m_BL_DataCollectionList.SetItemText(nRow, nCol, strInfoOld);
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_DataCollectionList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
		}
	}

}


void CDataCollectionDlg::LBtDbClickBlDatacollectionlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_DataCollectionList.SetDropDownData(_T("16;32"));
	}
}


void CDataCollectionDlg::ItemEditFinishBlDatacollectionlist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 2)
	{
		m_BL_DataCollectionList.SetItemText(m_BL_DataCollectionList.GetCurRow(), 4, _T("0"));
	}
}


void CDataCollectionDlg::LBtClickedBlbtsavedata(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Dat"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Dat Files(*.Dat)|*.Dat|All File(*.*)|*.*||"),this);
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


void CDataCollectionDlg::LBtClickedBlbtloaddata(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CFileDialog dlgFile(TRUE, _T("*.Dat"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Par)|*.Dat|All Files(*.*)|*.*||"), this);

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


void CDataCollectionDlg::LBtClickedBlbtadddata(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	m_ParameterAdd->m_strRegistersStart = m_strRegistersStart; //R起始地址
	m_ParameterAdd->m_strRegistersEnd = m_strRegistersEnd;   //R結束地址
	m_ParameterAdd->m_strRegistersStart1 = m_strRegistersStart1;//D起始地址
	m_ParameterAdd->m_strRegistersEnd1 = m_strRegistersEnd1;//D結束地址
	m_ParameterAdd->m_strRegisters = m_strRegisters;//R的switch狀態
	m_ParameterAdd->m_strRegisters1 = m_strRegisters1;//D的switch狀態
	m_ParameterAdd->m_strRegistersPos = m_strRegistersPos;//R的起始位
	m_ParameterAdd->m_strRegistersPos1 = m_strRegistersPos1;//D的起始位

	if (m_ParameterAdd.CreateTopWnd(TRUE) == IDOK)
	{
		for (int i = 0; i <= ((m_ParameterAdd->m_nDataEnd - m_ParameterAdd->m_nDataStar) / (m_ParameterAdd->m_nDataInterval)); i++)
		{
			m_BL_DataCollectionList.AppendRow(TRUE);
			CString strTem;
			strTem.Format(_T("%d"), (m_ParameterAdd->m_nDataStar + i * m_ParameterAdd->m_nDataInterval));
			strTem.Insert(0, m_ParameterAdd->m_strDataStar[0]);
			m_BL_DataCollectionList.SetItemText(m_BL_DataCollectionList.GetCurRow(), 1, strTem);

			strTem.Format(_T("%d"), m_ParameterAdd->m_nDataBits);
			m_BL_DataCollectionList.SetItemText(m_BL_DataCollectionList.GetCurRow(), 2, strTem);
			m_BL_DataCollectionList.SetItemText(m_BL_DataCollectionList.GetCurRow(), 4, _T("0"));
		}
	}
}


void CDataCollectionDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_DataCollectionList.GetRows();
		for (int i = 0; i < m_BL_DataCollectionList.GetRows(); i++)
		{
			for (int j = 0; j < 7; j++)
			{
				ar << m_BL_DataCollectionList.GetItemText(i, j);
			}
		}
	}
	else
	{	// loading code
		for (int i = m_BL_DataCollectionList.GetRows() - 1; i >= 0 ; i--)
		{
			m_BL_DataCollectionList.DeleteRow(i, TRUE);
		}
		int nAr = 0;
		CString strAr;
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_DataCollectionList.AppendRow(TRUE);
			for (int j = 0; j < 7; j++)
			{
				ar >> strAr;
				m_BL_DataCollectionList.SetItemText(i, j, strAr);
			}
		}
	}	
}
