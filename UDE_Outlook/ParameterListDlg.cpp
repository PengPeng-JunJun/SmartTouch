// ParameterListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ParameterListDlg.h"
#include "afxdialogex.h"


// CParameterListDlg 对话框

IMPLEMENT_DYNAMIC(CParameterListDlg, CTpLayerWnd)

CParameterListDlg::CParameterListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CParameterListDlg::IDD, pParent)
	, m_bParamInpiutLocked(TRUE)
	, m_bLocked(TRUE)
	, m_bParamInputting(FALSE)
{

}


CParameterListDlg::CParameterListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_bParamInpiutLocked(TRUE)
	, m_bLocked(TRUE)
	, m_bParamInputting(FALSE)
{
}


CParameterListDlg::~CParameterListDlg()
{
}

void CParameterListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_BL_ParameterList, m_BL_ParameterList);
	DDX_Control(pDX, IDC_BL_btSaveParam, m_BL_btSaveParam);
	DDX_Control(pDX, IDC_BL_btLoadParam, m_BL_btLoadParam);
	DDX_Control(pDX, IDC_BL_btAddParam, m_BL_btAddParam);
	DDX_Control(pDX, IDC_BL_ckUpdateData, m_BL_ckUpdateData);
	
}


BEGIN_MESSAGE_MAP(CParameterListDlg, CTpLayerWnd)
	ON_MESSAGE(WM_PARAM_UPDATE, &CParameterListDlg::OnParamUpdate)
END_MESSAGE_MAP()


// CParameterListDlg 消息处理程序


BOOL CParameterListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BL_ParameterList.ResetRows(m_BL_ParameterList.GetRows(), TRUE);
	m_BL_ParameterList.AppendColumn(_T("編號"),DT_CENTER,70,FALSE);
	m_BL_ParameterList.AppendColumn(_T("寄存器名"),DT_CENTER,100,FALSE);
	m_BL_ParameterList.AppendColumn(_T("數據位數"),DT_CENTER,100,FALSE);
	m_BL_ParameterList.AppendColumn(_T("數據名稱"),DT_CENTER,270,FALSE);
	m_BL_ParameterList.AppendColumn(_T("小數位數"),DT_CENTER,105,FALSE);
	m_BL_ParameterList.AppendColumn(_T("單位"),DT_CENTER,100,FALSE);
	m_BL_ParameterList.AppendColumn(_T("值"),DT_CENTER,110,FALSE);

	m_BL_ParameterList.SetColumnReadOnly(6, TRUE);

	m_NumberInput.CreateBlendWnd(IDD_NUMBERINPUT, this);
	m_ParameterAdd.CreateBlendWnd(IDD_PARAMETER, this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CParameterListDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}
BEGIN_EVENTSINK_MAP(CParameterListDlg, CTpLayerWnd)
	ON_EVENT(CParameterListDlg, IDC_BL_ParameterList, 2, CParameterListDlg::ItemChangedBlParameterlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CParameterListDlg, IDC_BL_ParameterList, 5, CParameterListDlg::LBtDbClickBlParameterlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CParameterListDlg, IDC_BL_ParameterList, 1, CParameterListDlg::RowsChangedBlParameterlist, VTS_I4 VTS_I4 VTS_BOOL)
	ON_EVENT(CParameterListDlg, IDC_BL_btSaveParam, 1, CParameterListDlg::LBtClickedBlbtsaveparam, VTS_I4)
	ON_EVENT(CParameterListDlg, IDC_BL_btLoadParam, 1, CParameterListDlg::LBtClickedBlbtloadparam, VTS_I4)
	ON_EVENT(CParameterListDlg, IDC_BL_ParameterList, 6, CParameterListDlg::ItemEditFinishBlParameterlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CParameterListDlg, IDC_BL_btAddParam, 1, CParameterListDlg::LBtClickedBlbtaddparam, VTS_I4)
	ON_EVENT(CParameterListDlg, IDC_BL_ckUpdateData, 1, CParameterListDlg::StatusChangedBlckupdatedata, VTS_I2)
	END_EVENTSINK_MAP()


void CParameterListDlg::ItemChangedBlParameterlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
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
			m_BL_ParameterList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_ParameterList.SetItemText(nRow, nCol, strInfoOld);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 R 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_ParameterList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					m_BL_ParameterList.SetItemText(nRow, nCol, strInfoOld);
					MsgBox.ShowMsg(_T("緩存器編號只能為數字"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("待採集數據的 D 緩存器超出設置範圍"), _T("無法獲取"), MB_ICONSTOP | MB_OK);
					m_BL_ParameterList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
		}
	}
}


void CParameterListDlg::LBtDbClickBlParameterlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_ParameterList.SetDropDownData(_T("16;32"));
	}
	if (nCol == 6)
	{
		if (!m_bParamInpiutLocked)
		{
			m_bParamInputting = TRUE;
			m_NumberInput->m_strCurrentValue = m_BL_ParameterList.GetItemText(nRow, 6);
			m_NumberInput->m_strPtByte = m_BL_ParameterList.GetItemText(nRow, 4);
			if (m_NumberInput.CreateTopWnd(TRUE) == IDOK)//數據修改完成
			{
				m_pParameterListDlg->PostMessage(WM_PARAM_FINISH, nRow, m_NumberInput->m_nSendValue);
			}
			m_bParamInputting = FALSE;
		}
	}
}


void CParameterListDlg::RowsChangedBlParameterlist(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: 在此处添加消息处理程序代码

}

void CParameterListDlg::ItemEditFinishBlParameterlist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 2)
	{
		m_BL_ParameterList.SetItemText(m_BL_ParameterList.GetCurRow(), 4, _T("0"));
	}
}


void CParameterListDlg::LBtClickedBlbtsaveparam(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Par"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Par Files(*.Par)|*.Par|All File(*.*)|*.*||"),this);
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
	// TODO: 在此添加命令处理程序代码
}


void CParameterListDlg::LBtClickedBlbtloadparam(long nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CFileDialog dlgFile(TRUE, _T("*.Par"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Par)|*.Par|All Files(*.*)|*.*||"), this);

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

	m_BL_ckUpdateData.SetStatus(FALSE);
	m_BL_ckUpdateData.SetEnabled(TRUE);
	ar.Flush();
	ar.Close();
	file.Close();
}


void CParameterListDlg::LBtClickedBlbtaddparam(long nFlags)
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
			m_BL_ParameterList.AppendRow(TRUE);
			CString strTem;
			strTem.Format(_T("%d"), (m_ParameterAdd->m_nDataStar + i * m_ParameterAdd->m_nDataInterval));
			strTem.Insert(0, m_ParameterAdd->m_strDataStar[0]);
			m_BL_ParameterList.SetItemText(m_BL_ParameterList.GetCurRow(), 1, strTem);
			strTem.Format(_T("%d"), m_ParameterAdd->m_nDataBits);
			m_BL_ParameterList.SetItemText(m_BL_ParameterList.GetCurRow(), 2, strTem);
			m_BL_ParameterList.SetItemText(m_BL_ParameterList.GetCurRow(), 4, _T("0"));
		}
	}
	
}


void CParameterListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		 ar << m_BL_ParameterList.GetRows();
		 for (int i = 0; i < m_BL_ParameterList.GetRows(); i++)
		 {
			 for (int j = 0; j < 7; j++)
			 {
				 ar << m_BL_ParameterList.GetItemText(i, j);
			 }
		 }
	}
	else
	{	// loading code
		for (int i = m_BL_ParameterList.GetRows() - 1; i >= 0 ; i--)
		{
			m_BL_ParameterList.DeleteRow(i, TRUE);
		}
		int nAr = 0;
		CString strAr;
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_ParameterList.AppendRow(TRUE);
			for (int j = 0; j < 7; j++)
			{
				ar >> strAr;
				m_BL_ParameterList.SetItemText(i, j, strAr);
			}
		}
	}
}


afx_msg LRESULT CParameterListDlg::OnParamUpdate(WPARAM wParam, LPARAM lParam)
{
	if (m_BL_ckUpdateData.GetStatus())
	{
		if (m_vnUpdateData.size() > 0)
		{
			for (size_t i = 0; i < m_vnUpdateData.size(); i++)
			{
				m_pParameterListDlg->SendMessage(WM_PARAM_FINISH, i, m_vnUpdateData[i]);
			}
		}
	}
	m_BL_ckUpdateData.SetStatus(FALSE);
	m_BL_ckUpdateData.SetEnabled(FALSE);
	return 0;
}


void CParameterListDlg::StatusChangedBlckupdatedata(short nNewStatus)
{
	// TODO: 在此处添加消息处理程序代码
	m_vnUpdateData.clear();
	if (m_BL_ParameterList.GetRows() > 0)
	{
		for (int i = 0; i < m_BL_ParameterList.GetRows(); i++)
		{
			m_vnUpdateData.push_back(_ttoi(m_BL_ParameterList.GetItemText(i, 6)));
		}
	}
}
