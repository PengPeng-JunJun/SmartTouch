// ErrorListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ErrorListDlg.h"
#include "afxdialogex.h"


// CErrorListDlg �Ի���

IMPLEMENT_DYNAMIC(CErrorListDlg, CTpLayerWnd)

CErrorListDlg::CErrorListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CErrorListDlg::IDD, pParent)
	, m_nErrorCode(0)
{

}

CErrorListDlg::CErrorListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nErrorCode(0)
{
	
}

CErrorListDlg::~CErrorListDlg()
{
}

void CErrorListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ErrorList, m_BL_ErrorList);
	DDX_Control(pDX, IDC_BL_edErrorListInfo, m_BL_edErrorListInfo);
	DDX_Control(pDX, IDC_BL_edErrorCode, m_BL_edErrorCode);
	DDX_Control(pDX, IDC_BL_btLoadError, m_BL_btLoadError);
	DDX_Control(pDX, IDC_BL_btSaveError, m_BL_btSaveError);
	
}


BEGIN_MESSAGE_MAP(CErrorListDlg, CTpLayerWnd)
	ON_MESSAGE(WM_ERROR_CODE, &CErrorListDlg::OnReceiveErrorCode)
END_MESSAGE_MAP()


// CErrorListDlg ��Ϣ�������


BOOL CErrorListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BL_ErrorList.AppendColumn(_T("�e�`�a"),DT_CENTER,60,FALSE);
	m_BL_ErrorList.AppendColumn(_T("���ϬF��"),DT_CENTER,160,FALSE);
	m_BL_ErrorList.AppendColumn(_T("����ԭ��1"),DT_CENTER,190,FALSE);
	m_BL_ErrorList.AppendColumn(_T("����ԭ��2"),DT_CENTER,190,FALSE);
	m_BL_ErrorList.AppendColumn(_T("����ԭ��3"),DT_CENTER,190,FALSE);

	m_MsgInfoDlg.CreateBlendWnd(IDD_MSGINFODLG, this);
	m_MsgInfoDlg.CreateTopWnd(FALSE, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BEGIN_EVENTSINK_MAP(CErrorListDlg, CTpLayerWnd)
	ON_EVENT(CErrorListDlg, IDC_BL_ErrorList, 5, CErrorListDlg::LBtDbClickBlErrorlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CErrorListDlg, IDC_BL_ErrorList, 2, CErrorListDlg::ItemChangedBlErrorlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CErrorListDlg, IDC_BL_edErrorCode, 1, CErrorListDlg::ValueChangedBlederrorcode, VTS_BSTR)
	ON_EVENT(CErrorListDlg, IDC_BL_btSaveError, 1, CErrorListDlg::LBtClickedBlbtsaveerror, VTS_I4)
	ON_EVENT(CErrorListDlg, IDC_BL_btLoadError, 1, CErrorListDlg::LBtClickedBlbtloaderror, VTS_I4)
	ON_EVENT(CErrorListDlg, IDC_BL_ErrorList, 6, CErrorListDlg::ItemEditFinishBlErrorlist, VTS_I4 VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()


void CErrorListDlg::LBtDbClickBlErrorlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	m_BL_edErrorListInfo.SetValueText(m_BL_ErrorList.GetItemText(nRow, nCol));
}


void CErrorListDlg::ItemChangedBlErrorlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
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
			if ((strInfoNew[0] < '0') || (strInfoNew[0] > '9'))
			{
				MsgBox.ShowMsg(_T("�e�`�aֻ�ܞ锵��"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			else
			{
				if (strInfoNew == _T("0"))
				{
					MsgBox.ShowMsg(_T("�e�`�a������0�_�^"), _T("ERROR"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			m_BL_ErrorList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("�e�`�aֻ�ܞ锵��"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_ErrorList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}
	m_BL_edErrorListInfo.SetValueText(m_BL_ErrorList.GetItemText(nRow, nCol));
	
	
}

void CErrorListDlg::ItemEditFinishBlErrorlist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	CString strTem = strNew;
	if (nCol == 0)
	{
		if(strTem == _T("0"))
		{
			MsgBox.ShowMsg(_T("�e�`�a����Ǵ��0�Ĕ���"), _T("ERROR"), MB_ICONSTOP | MB_OK);
			m_BL_ErrorList.SetItemText(nRow, nCol, _T(""));
		}
	}
}


void CErrorListDlg::ValueChangedBlederrorcode(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
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
				MsgBox.ShowMsg(_T("ԓ�O��δ�O�� R ��;����������xȡ"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
		}
		if (strInfoNew == _T("D"))
		{
			if (_ttoi(m_strRegisters1) <= 0)
			{
				MsgBox.ShowMsg(_T("ԓ�O��δ�O�� D ��;����������xȡ"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
		}
		if((strInfoNew != _T("D")) && (strInfoNew != _T("R")))
		{
			CString strErrInfo;
			strErrInfo.Format(_T("ԓ�O�䲻֧�� %s ��;����������xȡ"), strInfoNew);
			MsgBox.ShowMsg(strErrInfo, _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			strInfoNew = _T("");
		}
		m_BL_edErrorCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edErrorCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edErrorCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edErrorCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edErrorCode.SetValueText(strInfoOld);
			}
		}
	}
}


void CErrorListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edErrorCode.GetValueText();
		ar << m_BL_ErrorList.GetRows();
		for (int i = 0; i < m_BL_ErrorList.GetRows(); i++)
		{
			for (int j = 0; j < 5; j++)
			{
				ar << m_BL_ErrorList.GetItemText(i, j);
			}
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edErrorCode.SetValueText(strTem);
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_ErrorList.AppendRow(TRUE);
			for (int j = 0; j < 5; j++)
			{
				ar >> strTem;
				m_BL_ErrorList.SetItemText(i, j, strTem);
			}
		}
	}
}


void CErrorListDlg::LBtClickedBlbtsaveerror(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Err"),_T("�o���}"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Err Files(*.Err)|*.Err|All File(*.*)|*.*||"),this);
	dlgFile.m_pOFN->lpstrTitle = _T("�ļ�����");
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


void CErrorListDlg::LBtClickedBlbtloaderror(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CFileDialog dlgFile(TRUE, _T("*.Err"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Err)|*.Err|All Files(*.*)|*.*||"), this);

	dlgFile.m_pOFN->lpstrTitle = _T("�ļ����_");

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

	for (int i = m_BL_ErrorList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_ErrorList.DeleteRow(i, FALSE);
	}
	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}



afx_msg LRESULT CErrorListDlg::OnReceiveErrorCode(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < m_BL_ErrorList.GetRows(); i++)
	{
		if (_ttoi(m_BL_ErrorList.GetItemText(i, 0)) == m_nErrorCode)
		{
			m_MsgInfoDlg->m_BL_btErrorInfo.SetCaption(m_BL_ErrorList.GetItemText(i, 1));
			for (int j = 2; j < 5; j++)
			{
				if (m_BL_ErrorList.GetItemText(i, j) != _T(""))
				{
					CString strTem;
					strTem.Format(_T("%d��"), j - 1);
					strTem.Append(m_BL_ErrorList.GetItemText(i, j));	
					m_MsgInfoDlg->m_BL_btErrorReason[j - 2].SetCaption(strTem);
					m_MsgInfoDlg->m_BL_btErrorReason[j - 2].ShowWindow(SW_SHOW);
				}
				else
				{
					m_MsgInfoDlg->m_BL_btErrorReason[j - 2].ShowWindow(SW_HIDE);
				}
			}
			m_MsgInfoDlg->ShowWindow(SW_SHOW);
			break;
		}
	}

	if (m_nErrorCode == 9999)//ATM����
	{
		CMsgBox MsgBox(this);
		HWND hWnd = ::FindWindow(NULL, _T("ATM�Cе�ֱ�"));//����Ŀ�괰��
		if(hWnd == NULL)
		{
			//MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�˴���"), _T("����ʧ��"), MB_OK);
			return 0;
		}
		TEST_RESULT_INFO Info;
		Info.nID = 100;
		Info.nParam1 = 9999;
		CString  szInfo;
		szInfo = GetTitle();//������Ϣ�Ĵ�������
		USES_CONVERSION;
		memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
		COPYDATASTRUCT Cds;
		Cds.dwData = Info.nID;
		Cds.cbData = sizeof(TEST_RESULT_INFO);
		Cds.lpData = (LPVOID)&Info;
		::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		return 0;
	}

	return 0;
}
