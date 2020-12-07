// SmartDotsListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "SmartDotsListDlg.h"
#include "afxdialogex.h"


// CSmartDotsListDlg �Ի���

IMPLEMENT_DYNAMIC(CSmartDotsListDlg, CTpLayerWnd)

CSmartDotsListDlg::CSmartDotsListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CSmartDotsListDlg::IDD, pParent)
	, m_nSmartDotsCode(0)
{

}

CSmartDotsListDlg::CSmartDotsListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nSmartDotsCode(0)
{

}

CSmartDotsListDlg::~CSmartDotsListDlg()
{
}

void CSmartDotsListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_SmartDotsList, m_BL_SmartDotsList);
	DDX_Control(pDX, IDC_BL_edSmartDotsCode, m_BL_edSmartDotsCode);
	DDX_Control(pDX, IDC_BL_edSmartDotsResult, m_BL_edSmartDotsResult);
	DDX_Control(pDX, IDC_BL_btLoadSmartDots, m_BL_btLoadSmartDots);
	DDX_Control(pDX, IDC_BL_btSaveSmartDots, m_BL_btSaveSmartDots);
	
}


BEGIN_MESSAGE_MAP(CSmartDotsListDlg, CTpLayerWnd)
	ON_MESSAGE(WM_SMARTDOTS_CODE, &CSmartDotsListDlg::OnReceiveSmartdotsCode)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CSmartDotsListDlg ��Ϣ�������


BOOL CSmartDotsListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BL_SmartDotsList.ResetRows(m_BL_SmartDotsList.GetRows(), TRUE);
	m_BL_SmartDotsList.AppendColumn(_T("���Ӵa"),DT_CENTER,60,FALSE);
	m_BL_SmartDotsList.AppendColumn(_T("���c�z�yܛ�����Q"),DT_CENTER,200,FALSE);
	m_BL_SmartDotsList.AppendColumn(_T("���Ͼ�̖"),DT_CENTER,80,FALSE);
	m_BL_SmartDotsList.AppendColumn(_T("ģ��1"),DT_CENTER,70,FALSE);
	m_BL_SmartDotsList.AppendColumn(_T("ģ��2"),DT_CENTER,70,FALSE);
	m_BL_SmartDotsList.AppendColumn(_T("ģ��3"),DT_CENTER,70,FALSE);
	m_BL_SmartDotsList.AppendColumn(_T("�Y��������"),DT_CENTER,70,FALSE);
	

	m_BL_SmartDotsList.SetColumnReadOnly(3, TRUE);
	m_BL_SmartDotsList.SetColumnReadOnly(4, TRUE);
	m_BL_SmartDotsList.SetColumnReadOnly(5, TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CSmartDotsListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edSmartDotsCode.GetValueText();
		ar << m_BL_SmartDotsList.GetRows();
		for (int i = 0; i < m_BL_SmartDotsList.GetRows(); i++)
		{
			for (int j = 0; j < 7; j++)
			{
				ar << m_BL_SmartDotsList.GetItemText(i, j);
			}
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edSmartDotsCode.SetValueText(strTem);
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_SmartDotsList.AppendRow(TRUE);
			for (int j = 0; j < 7; j++)
			{
				ar >> strTem;
				m_BL_SmartDotsList.SetItemText(i, j, strTem);
			}
		}
	}
}
BEGIN_EVENTSINK_MAP(CSmartDotsListDlg, CTpLayerWnd)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_edSmartDotsCode, 1, CSmartDotsListDlg::ValueChangedBledsmartdotscode, VTS_BSTR)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_SmartDotsList, 2, CSmartDotsListDlg::ItemChangedBlSmartdotslist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_SmartDotsList, 5, CSmartDotsListDlg::LBtDbClickBlSmartdotslist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_SmartDotsList, 6, CSmartDotsListDlg::ItemEditFinishBlSmartdotslist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_edSmartDotsResult, 1, CSmartDotsListDlg::ValueChangedBledsmartdotsresult, VTS_BSTR)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_btSaveSmartDots, 1, CSmartDotsListDlg::LBtClickedBlbtsavesmartdots, VTS_I4)
	ON_EVENT(CSmartDotsListDlg, IDC_BL_btLoadSmartDots, 1, CSmartDotsListDlg::LBtClickedBlbtloadsmartdots, VTS_I4)
END_EVENTSINK_MAP()


void CSmartDotsListDlg::ValueChangedBledsmartdotscode(LPCTSTR strNew)
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
		m_BL_edSmartDotsCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartDotsCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartDotsCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edSmartDotsCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartDotsCode.SetValueText(strInfoOld);
			}
		}
	}
}

void CSmartDotsListDlg::ValueChangedBledsmartdotsresult(LPCTSTR strNew)
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
		m_BL_edSmartDotsResult.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartDotsResult.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartDotsResult.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edSmartDotsResult.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edSmartDotsResult.SetValueText(strInfoOld);
			}
		}
	}
}


void CSmartDotsListDlg::ItemChangedBlSmartdotslist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	
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
				MsgBox.ShowMsg(_T("���Ӵaֻ�ܞ锵��"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				strInfoNew = _T("");
			}
			else
			{
				if (strInfoNew == _T("0"))
				{
					MsgBox.ShowMsg(_T("���Ӵa������0�_�^"), _T("ERROR"), MB_ICONSTOP | MB_OK);
					strInfoNew = _T("");
				}
			}
			m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("���Ӵaֻ�ܞ锵��"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}

	if (nCol == 6)
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
			m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			CString strAddress;
			if (strInfoNew[0] == 'R')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
					m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoOld);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
					m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
			if (strInfoNew[0] == 'D')
			{
				if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
				{
					m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoOld);
					MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				}
				strInfoNew.Delete(0, 1);
				int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
				if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
				{
					MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
					m_BL_SmartDotsList.SetItemText(nRow, nCol, strInfoOld);
				}
			}
		}
	}
}


void CSmartDotsListDlg::LBtDbClickBlSmartdotslist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	if (nCol == 0)
	{
		if (m_BL_SmartDotsList.GetReadOnly())
		{
			CString  strFindWindow;//Ŀ�괰������
			strFindWindow = m_BL_SmartDotsList.GetItemText(nRow, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�˺��c�z�y����"), _T("����ʧ��"), MB_OK);
				return;
			}
			TEST_START_INFO Info;
			Info.nID = 100;
			Info.nParam4 = 1;
			Info.nParam2 = _ttoi(m_BL_SmartDotsList.GetItemText(nRow, 2));    //�����ԵĲ��ϱ��
			for (int j = 3; j <= 5; j++)//��ʼ��ѯ���ģ��
			{
				if (m_BL_SmartDotsList.GetItemText(nRow, j) == _T("��"))
				{
					Info.nParam1 = j - 2; //�����ԵĲ���ģ��
					break;
				}
			}
			CString  szInfo;
			szInfo = GetTitle();//������Ϣ�Ĵ�������
			USES_CONVERSION;
			memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);

			COPYDATASTRUCT Cds;
			Cds.dwData = Info.nID;
			Cds.cbData = sizeof(TEST_START_INFO);
			Cds.lpData = (LPVOID)&Info;
			::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		}
	}
	if (nCol == 2)
	{
		* pnParam = 2;
		m_BL_SmartDotsList.SetDropDownData(_T("1;2;3;4;5;6;7;8;9;10;11;12"));
	}
	if ((nCol >= 3) && (nCol <= 5))
	{
		if (!m_BL_SmartDotsList.GetReadOnly())
		{
			if (m_BL_SmartDotsList.GetItemText(nRow, nCol) == _T("��"))
			{
				m_BL_SmartDotsList.SetItemText(nRow, nCol, _T(""));
			}
			else
			{
				for (int i = 3; i < 6; i++)
				{
					m_BL_SmartDotsList.SetItemText(nRow, i, _T(""));
				}
				m_BL_SmartDotsList.SetItemText(nRow, nCol, _T("��"));
			}
		}
	}
}


void CSmartDotsListDlg::ItemEditFinishBlSmartdotslist(long nRow, long nCol, LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	CString strTem = strNew;
	if (nCol == 0)
	{
		if(strTem == _T("0"))
		{
			MsgBox.ShowMsg(_T("�e�`�a����Ǵ��0�Ĕ���"), _T("ERROR"), MB_ICONSTOP | MB_OK);
			m_BL_SmartDotsList.SetItemText(nRow, nCol, _T(""));
		}
	}
	if (nCol == 6)
	{
// 		for (int i = 0; i < nRow; i++)
// 		{
// 			if ((m_BL_SmartDotsList.GetItemText(i, 6) == strTem) && (strTem.GetLength() != 0))
// 			{
// 				MsgBox.ShowMsg(_T("���c�Y��������������"), _T("WARNING"), MB_OK | MB_ICONWARNING);
// 				return;
// 			}
// 		}
	}
}


void CSmartDotsListDlg::LBtClickedBlbtsavesmartdots(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Dots"),_T("�o���}"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Dots Files(*.Dots)|*.Dots|All File(*.*)|*.*||"),this);
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


void CSmartDotsListDlg::LBtClickedBlbtloadsmartdots(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CFileDialog dlgFile(TRUE, _T("*.Dots"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Dots)|*.Dots|All Files(*.*)|*.*||"), this);

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

	for (int i = m_BL_SmartDotsList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_SmartDotsList.DeleteRow(i, FALSE);
	}
	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}


afx_msg LRESULT CSmartDotsListDlg::OnReceiveSmartdotsCode(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_SmartDotsList.GetRows(); i++)
	{
		if (_ttoi(m_BL_SmartDotsList.GetItemText(i, 0)) == m_nSmartDotsCode)
		{
			CString  strFindWindow;//Ŀ�괰������
			strFindWindow = m_BL_SmartDotsList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�˺��c�z�y����"), _T("����ʧ��"), MB_OK);
				return 0;
			}
			TEST_START_INFO Info;
			Info.nID = 100;
			Info.nParam4 = 1;
			Info.nParam2 = _ttoi(m_BL_SmartDotsList.GetItemText(i, 2));    //�����ԵĲ��ϱ��
			for (int j = 3; j <= 5; j++)//��ʼ��ѯ���ģ��
			{
				if (m_BL_SmartDotsList.GetItemText(i, j) == _T("��"))
				{
					Info.nParam1 = j - 2; //�����ԵĲ���ģ��
					break;
				}
			}
			CString  szInfo;
			szInfo = GetTitle();//������Ϣ�Ĵ�������
			USES_CONVERSION;
			memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);

			COPYDATASTRUCT Cds;
			Cds.dwData = Info.nID;
			Cds.cbData = sizeof(TEST_START_INFO);
			Cds.lpData = (LPVOID)&Info;
			::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
		}
	}
	return 0;
}


BOOL CSmartDotsListDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nInfoID = 0;
	nInfoID = pCopyDataStruct->dwData;

	TEST_RESULT_INFO tagSmartDotsResult;

	memset(tagSmartDotsResult.szInfo , '\0' , TEST_INFO_ARRAY_LEN);
	memset(tagSmartDotsResult.szSrcWnd ,'\0' , TEST_INFO_ARRAY_LEN);
	memcpy(&tagSmartDotsResult, pCopyDataStruct->lpData, pCopyDataStruct->cbData);


	TRACE(_T("\n"));
	TRACE(tagSmartDotsResult.szSrcWnd);
	TRACE(_T("\n"));

	USES_CONVERSION;
	CString strInfo = A2W(tagSmartDotsResult.szSrcWnd);
	if (tagSmartDotsResult.nID == 1)//�յ������������������Ϣ
	{
		BOOL bIsFind = FALSE;
		int nTestRowCounter = 0;
		for (int i = 0; i < m_BL_SmartDotsList.GetRows(); i++)
		{
			if (m_BL_SmartDotsList.GetItemText(i, 1) == strInfo)//�������Q��ͬ
			{
				if (_ttoi(m_BL_SmartDotsList.GetItemText(i, 2)) == tagSmartDotsResult.nParam2)//���Ͼ�̖��ͬ
				{
					for (int j = 3; j < 6; j++)
					{
						if (m_BL_SmartDotsList.GetItemText(i, j) == _T("��"))
						{
							if ((j - 2) == tagSmartDotsResult.nParam1)//�yԇģ����ͬ
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
		m_pSmartDotsListDlg->PostMessage(WM_SMARTDOTS_FINISH, nTestRowCounter, tagSmartDotsResult.nResult);//���Ͳ��Խ��������������źţ�
	}
	return CTpLayerWnd::OnCopyData(pWnd, pCopyDataStruct);
}
