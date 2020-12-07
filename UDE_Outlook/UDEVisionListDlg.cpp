// UDEVisionListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "UDEVisionListDlg.h"
#include "afxdialogex.h"


// CUDEVisionListDlg �Ի���

IMPLEMENT_DYNAMIC(CUDEVisionListDlg, CTpLayerWnd)

CUDEVisionListDlg::CUDEVisionListDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CUDEVisionListDlg::IDD, pParent)
	, m_nUDEVisionCode(0)
	, m_nUDEVisionNO(0)
	, m_nUDEVisionCodeRobot(0)
{
	m_vstrUDEVisionInfo.resize(21);

	m_vstrUDEVisionRes.resize(21);
	for (int i = 0; i < 21; i++)
	{
		CString strTem;
		strTem.Format(_T("Res%d"), i);
		m_vstrUDEVisionRes[i] = strTem;
	}
}

CUDEVisionListDlg::CUDEVisionListDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nUDEVisionCode(0)
	, m_nUDEVisionNO(0)
	, m_nUDEVisionCodeRobot(0)
{
	m_vstrUDEVisionInfo.resize(21);
	m_vstrUDEVisionRes.resize(21);
	for (int i = 0; i < 21; i++)
	{
		CString strTem;
		strTem.Format(_T("Res%d"), i);
		m_vstrUDEVisionRes[i] = strTem;
	}
}

CUDEVisionListDlg::~CUDEVisionListDlg()
{

}

void CUDEVisionListDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_UDEVisionList, m_BL_UDEVisionList);
	DDX_Control(pDX, IDC_BL_edUDEVisionCode, m_BL_edUDEVisionCode);
	DDX_Control(pDX, IDC_BL_edUDEVisionResult, m_BL_edUDEVisionResult);
	DDX_Control(pDX, IDC_BL_btSaveUDEVision, m_BL_btSaveUDEVision);
	DDX_Control(pDX, IDC_BL_btLoadUDEVision, m_BL_btLoadUDEVision);
	for (int i = 0; i < 21; i++)
	{
		DDX_Control(pDX, IDC_BL_edUDEVisionRes_0 + i, m_BL_edUDEVisionRes[i]);
	}
	DDX_Control(pDX, IDC_BL_btUDEVisionContinue, m_BL_btUDEVisionContinue);
	DDX_Control(pDX, IDC_BL_edUDEVisionInfo, m_BL_edUDEVisionInfo);
	DDX_Control(pDX, IDC_BL_rdUDEVision_PLC, m_BL_rdUDEVision_PLC);
	DDX_Control(pDX, IDC_BL_rdUDEVision_Robot, m_BL_rdUDEVision_Robot);

	
}


BEGIN_MESSAGE_MAP(CUDEVisionListDlg, CTpLayerWnd)
	ON_MESSAGE(WM_UDEVISION_CODE, &CUDEVisionListDlg::OnReceiveUdevisionCode)
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_ED_UDEVISION_RES, &CUDEVisionListDlg::OnEdUdevisionRes)
	ON_WM_TIMER()
	ON_MESSAGE(WM_UDEVISION_CODE_ROBOT, &CUDEVisionListDlg::OnReceiveUdevisionCodeRobot)
END_MESSAGE_MAP()


// CUDEVisionListDlg ��Ϣ�������


BOOL CUDEVisionListDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BL_UDEVisionList.ResetRows(m_BL_UDEVisionList.GetRows(), TRUE);
	m_BL_UDEVisionList.AppendColumn(_T("���Ӵa"),DT_CENTER,70,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("���^�z�yܛ�����Q"),DT_CENTER,200,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("0"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("1"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("2"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("3"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("4"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("5"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("6"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("7"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("8"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("9"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("10"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("11"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("12"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("13"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("14"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("15"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("16"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("17"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("18"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("19"),DT_CENTER,32,FALSE);
	m_BL_UDEVisionList.AppendColumn(_T("20"),DT_CENTER,32,FALSE);

	for (int i = 2; i < 23; i++)
	{
		m_BL_UDEVisionList.SetColumnReadOnly(i, TRUE);
	}
	SetTimer(0, 1, nullptr);//�ڵ����༭״̬�£�ȷ��ѡ�е�Ⱥ��ĵ�����ɫ��
	SetTimer(1, 1, nullptr);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CUDEVisionListDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_BL_edUDEVisionCode.GetValueText();

		for (int i = 0; i < 21; i++)
		{
			ar << m_BL_edUDEVisionRes[i].GetValueText();
		}

		ar << m_BL_UDEVisionList.GetRows();
		for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
		{
			for (int j = 0; j < UDEVISION_COLS_COUNTER; j++)
			{
				ar << m_BL_UDEVisionList.GetItemText(i, j);
			}
		}
		for (int i = 0; i < 21; i++)
		{
			ar << m_vstrUDEVisionInfo[i];
		}
	}
	else
	{	// loading code
		CString strTem;
		int nAr = 0;
		ar >> strTem;
		m_BL_edUDEVisionCode.SetValueText(strTem);
		for (int i = 0; i < 21; i++)
		{
			ar >> strTem;
			m_BL_edUDEVisionRes[i].SetValueText(strTem);
		}
		ar >> nAr;
		for (int i = 0; i < nAr; i++)
		{
			m_BL_UDEVisionList.AppendRow(FALSE);
			for (int j = 0; j < UDEVISION_COLS_COUNTER; j++)
			{
				ar >> strTem;
				m_BL_UDEVisionList.SetItemText(i, j, strTem);
			}
		}
		for (int i = 0; i < 21; i++)
		{
			ar >> m_vstrUDEVisionInfo[i];
		}
	}
}
BEGIN_EVENTSINK_MAP(CUDEVisionListDlg, CTpLayerWnd)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_edUDEVisionCode, 1, CUDEVisionListDlg::ValueChangedBledudevisioncode, VTS_BSTR)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_UDEVisionList, 2, CUDEVisionListDlg::ItemChangedBlUdevisionlist, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_UDEVisionList, 5, CUDEVisionListDlg::LBtDbClickBlUdevisionlist, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_UDEVisionList, 6, CUDEVisionListDlg::ItemEditFinishBlUdevisionlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_btSaveUDEVision, 1, CUDEVisionListDlg::LBtClickedBlbtsaveudevision, VTS_I4)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_btLoadUDEVision, 1, CUDEVisionListDlg::LBtClickedBlbtloadudevision, VTS_I4)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_btUDEVisionContinue, 1, CUDEVisionListDlg::LBtClickedBlbtudevisioncontinue, VTS_I4)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_edUDEVisionInfo, 2, CUDEVisionListDlg::EnterPressedBledudevisioninfo, VTS_BSTR)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_rdUDEVision_PLC, 1, CUDEVisionListDlg::StatusChangedBlrdudevisionPlc, VTS_BOOL)
	ON_EVENT(CUDEVisionListDlg, IDC_BL_rdUDEVision_Robot, 1, CUDEVisionListDlg::StatusChangedBlrdudevisionRobot, VTS_BOOL)
END_EVENTSINK_MAP()


void CUDEVisionListDlg::ValueChangedBledudevisioncode(LPCTSTR strNew)
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
		m_BL_edUDEVisionCode.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edUDEVisionCode.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edUDEVisionCode.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edUDEVisionCode.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edUDEVisionCode.SetValueText(strInfoOld);
			}
		}
	}
}


void CUDEVisionListDlg::ItemChangedBlUdevisionlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
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
			m_BL_UDEVisionList.SetItemText(nRow, nCol, strInfoNew);
		}
		else
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("���Ӵaֻ�ܞ锵��"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				m_BL_UDEVisionList.SetItemText(nRow, nCol, strInfoOld);
			}
		}
	}
}


void CUDEVisionListDlg::LBtDbClickBlUdevisionlist(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	if (nCol == 0)
	{
		if (m_BL_UDEVisionList.GetReadOnly())//�p���yԇ�a���M�Мyԇ
		{
			CString  strFindWindow;//Ŀ�괰������
			strFindWindow = m_BL_UDEVisionList.GetItemText(nRow, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�����^�z�y����"), _T("����ʧ��"), MB_OK);
				return;
			}
			TEST_INFO Info;
			Info.nID = 100;
			int nStarCounter = 0;
			for (int j = 2; j < 23; j++)
			{
				if (m_BL_UDEVisionList.GetItemText(nRow, j) != _T(""))
				{
					nStarCounter++;
					Info.byStarGroup[nStarCounter - 1] = j - 2;
				}
			}
			if (nStarCounter > 0)
			{
				Info.nParam2 = nStarCounter;    //�����Ե�Ⱥ�M���
				CString  szInfo;
				szInfo = GetTitle();//������Ϣ�Ĵ�������
				USES_CONVERSION;
				memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
				COPYDATASTRUCT Cds;
				Cds.dwData = Info.nID;
				Cds.cbData = sizeof(TEST_INFO);
				Cds.lpData = (LPVOID)&Info;
				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
			}
		}
	}
	if (nCol > 1)
	{
		if (!m_BL_UDEVisionList.GetReadOnly())
		{
			if (m_BL_edUDEVisionRes[nCol - 2].GetValueText().GetLength() > 1)
			{
				if (m_BL_UDEVisionList.GetItemText(nRow, nCol) == _T(""))
				{
					m_BL_UDEVisionList.SetItemText(nRow, nCol, _T("��"));
				}
				else
				{
					m_BL_UDEVisionList.SetItemText(nRow, nCol, _T(""));
				}
			}
			else
			{
				MsgBox.ShowMsg(_T("δݔ��ԓȺ�M�Y��������"), _T("ERROR"), MB_ICONSTOP | MB_OK);
				return;
			}
		}
		else
		{
			if (nFlags & MK_CONTROL)
			{
				if (m_BL_rdUDEVision_PLC.GetSelect())
				{
					if (m_BL_edUDEVisionRes[nCol - 2].GetValueText().GetLength() > 1)
					{
						m_pUDEVisionListDlg->PostMessage(WM_UDEVISION_FINISH, nCol - 2, 1);
						return;
					}
				}
				if (m_BL_rdUDEVision_Robot.GetSelect())
				{
					m_pUDEVisionListDlg->PostMessage(WM_UDEVISION_FINISH_ROBOT, nCol - 2, 1);
					return;
				}
			}
			if (nFlags & MK_SHIFT)
			{
				if (m_BL_rdUDEVision_PLC.GetSelect())
				{
					if (m_BL_edUDEVisionRes[nCol - 2].GetValueText().GetLength() > 1)
					{
						m_pUDEVisionListDlg->PostMessage(WM_UDEVISION_FINISH, nCol - 2, 0);
						return;
					}
				}
				if (m_BL_rdUDEVision_Robot.GetSelect())
				{
					m_pUDEVisionListDlg->PostMessage(WM_UDEVISION_FINISH_ROBOT, nCol - 2, 0);
					return;
				}
			}
		}
	}
}


void CUDEVisionListDlg::ItemEditFinishBlUdevisionlist(long nRow, long nCol, LPCTSTR strNew)
{
	CMsgBox MsgBox(this);
	CString strTem = strNew;
	if (nCol == 0)
	{
		if(strTem == _T("0"))
		{
			MsgBox.ShowMsg(_T("�e�`�a����Ǵ��0�Ĕ���"), _T("ERROR"), MB_ICONSTOP | MB_OK);
			m_BL_UDEVisionList.SetItemText(nRow, nCol, _T(""));
		}
	}
// 	if (nCol == 3)
// 	{
// 		for (int i = 0; i < nRow; i++)
// 		{
// 			if ((m_BL_UDEVisionList.GetItemText(i, 6) == strTem) && (strTem.GetLength() != 0))
// 			{
// 				MsgBox.ShowMsg(_T("���c�Y��������������"), _T("WARNING"), MB_OK | MB_ICONWARNING);
// 				return;
// 			}
// 		}
// 	}
	// TODO: �ڴ˴������Ϣ����������
}


void CUDEVisionListDlg::LBtClickedBlbtsaveudevision(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strPath;
	CFileDialog dlgFile(FALSE,_T("*.Vis"),_T("�o���}"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("Vis Files(*.Vis)|*.Vis|All File(*.*)|*.*||"),this);
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


void CUDEVisionListDlg::LBtClickedBlbtloadudevision(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CFileDialog dlgFile(TRUE, _T("*.Vis"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("SmartTouch Files(*.Vis)|*.Vis|All Files(*.*)|*.*||"), this);

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

	for (int i = m_BL_UDEVisionList.GetRows() - 1; i >= 0 ; i--)
	{
		m_BL_UDEVisionList.DeleteRow(i, FALSE);
	}
	Serialize(ar);

	ar.Flush();
	ar.Close();
	file.Close();
}

void CUDEVisionListDlg::LBtClickedBlbtudevisioncontinue(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	if (m_BL_rdUDEVision_PLC.GetSelect())
	{
		if (m_nUDEVisionCode != 0)
		{
			for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
			{
				if (_ttoi(m_BL_UDEVisionList.GetItemText(i, 0)) == m_nUDEVisionCode)
				{
					CString  strFindWindow;//Ŀ�괰������
					strFindWindow = m_BL_UDEVisionList.GetItemText(i, 1);
					HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
					if(hWnd == NULL)
					{
						MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�����^�z�y����"), _T("����ʧ��"), MB_OK);
						return ;
					}
					TEST_INFO Info;
					Info.nID = 100;
					int nStarCounter = 0;
					for (int j = 2; j < 23; j++)
					{
						if (m_BL_UDEVisionList.GetItemText(i, j) != _T(""))
						{
							nStarCounter++;
							Info.byStarGroup[nStarCounter - 1] = j - 2;
						}
					}
					if (nStarCounter > 0)
					{
						Info.nParam2 = nStarCounter;    //�����Ե�Ⱥ�M���
						CString  szInfo;
						szInfo = GetTitle();//������Ϣ�Ĵ�������
						USES_CONVERSION;
						memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
						COPYDATASTRUCT Cds;
						Cds.dwData = Info.nID;
						Cds.cbData = sizeof(TEST_INFO);
						Cds.lpData = (LPVOID)&Info;
						::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
					}
				}
			}
		}
	}
	if (m_BL_rdUDEVision_Robot.GetSelect())
	{
		if (m_nUDEVisionCodeRobot != 0)
		{
			for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
			{
				if (_ttoi(m_BL_UDEVisionList.GetItemText(i, 0)) == m_nUDEVisionCodeRobot)
				{
					CString  strFindWindow;//Ŀ�괰������
					strFindWindow = m_BL_UDEVisionList.GetItemText(i, 1);
					HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
					if(hWnd == NULL)
					{
						MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�����^�z�y����"), _T("����ʧ��"), MB_OK);
						return ;
					}
					TEST_INFO Info;
					Info.nID = 100;
					int nStarCounter = 0;
					for (int j = 2; j < 23; j++)
					{
						if (m_BL_UDEVisionList.GetItemText(i, j) != _T(""))
						{
							nStarCounter++;
							Info.byStarGroup[nStarCounter - 1] = j - 2;
						}
					}
					if (nStarCounter > 0)
					{
						Info.nParam2 = nStarCounter;    //�����Ե�Ⱥ�M���
						m_vbyRobotStarUDEVisionGroup.clear();
						for (int i = 0; i < nStarCounter; i++)
						{
							m_vbyRobotStarUDEVisionGroup.push_back(Info.byStarGroup[i]);
						}
						CString  szInfo;
						szInfo = GetTitle();//������Ϣ�Ĵ�������
						USES_CONVERSION;
						memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
						COPYDATASTRUCT Cds;
						Cds.dwData = Info.nID;
						Cds.cbData = sizeof(TEST_INFO);
						Cds.lpData = (LPVOID)&Info;
						::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
					}
				}
			}
		}
	}
	
}

afx_msg LRESULT CUDEVisionListDlg::OnReceiveUdevisionCode(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
	{
		if (_ttoi(m_BL_UDEVisionList.GetItemText(i, 0)) == m_nUDEVisionCode)
		{
			for (int j = 2; j < 23; j++)
			{
				m_BL_UDEVisionList.SetItemTextColor(i, j, RGB(128,128,128));
			}
			CString  strFindWindow;//Ŀ�괰������
			strFindWindow = m_BL_UDEVisionList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�����^�z�y����"), _T("����ʧ��"), MB_OK);
				return 0;
			}
			TEST_INFO Info;
			Info.nID = 100;
			int nStarCounter = 0;
			for (int j = 2; j < 23; j++)
			{
				if (m_BL_UDEVisionList.GetItemText(i, j) != _T(""))
				{
					nStarCounter++;
					Info.byStarGroup[nStarCounter - 1] = j - 2;
				}
			}
 			if (nStarCounter > 0)
 			{
 				Info.nParam2 = nStarCounter;    //�����Ե�Ⱥ�M���
 				CString  szInfo;
 				szInfo = GetTitle();//������Ϣ�Ĵ�������
 				USES_CONVERSION;
 				memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
 				COPYDATASTRUCT Cds;
 				Cds.dwData = Info.nID;
 				Cds.cbData = sizeof(TEST_INFO);
 				Cds.lpData = (LPVOID)&Info;
 				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
 			}
		}
	}
	return 0;
}

afx_msg LRESULT CUDEVisionListDlg::OnReceiveUdevisionCodeRobot(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
	{
		if (_ttoi(m_BL_UDEVisionList.GetItemText(i, 0)) == m_nUDEVisionCodeRobot)
		{
			for (int j = 2; j < 23; j++)
			{
				m_BL_UDEVisionList.SetItemTextColor(i, j, RGB(128,128,128));
			}
			CString  strFindWindow;//Ŀ�괰������
			strFindWindow = m_BL_UDEVisionList.GetItemText(i, 1);
			HWND hWnd = ::FindWindow(NULL, strFindWindow);//����Ŀ�괰��
			if(hWnd == NULL)
			{
				MsgBox.ShowMsg(_T("δ�ҵ�Ŀ�����^�z�y����"), _T("����ʧ��"), MB_OK);
				return 0;
			}
			TEST_INFO Info;
			Info.nID = 100;
			int nStarCounter = 0;
			for (int j = 2; j < 23; j++)
			{
				if (m_BL_UDEVisionList.GetItemText(i, j) != _T(""))
				{
					nStarCounter++;
					Info.byStarGroup[nStarCounter - 1] = j - 2;
				}
			}
			if (nStarCounter > 0)
			{
				Info.nParam2 = nStarCounter;    //�����Ե�Ⱥ�M���
				m_vbyRobotStarUDEVisionGroup.clear();
				for (int i = 0; i < nStarCounter; i++)
				{
					m_vbyRobotStarUDEVisionGroup.push_back(Info.byStarGroup[i]);
				}
				CString  szInfo;
				szInfo = GetTitle();//������Ϣ�Ĵ�������
				USES_CONVERSION;
				memcpy(Info.szSrcWnd ,W2A(szInfo) , strlen(W2A(szInfo)) + 1);
				COPYDATASTRUCT Cds;
				Cds.dwData = Info.nID;
				Cds.cbData = sizeof(TEST_INFO);
				Cds.lpData = (LPVOID)&Info;
				::SendMessage(hWnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)(&Cds));
			}
		}
	}
	return 0;
}


BOOL CUDEVisionListDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nInfoID = 0;
	nInfoID = pCopyDataStruct->dwData;

	TEST_INFO tagUDEVisionResult;

	memset(tagUDEVisionResult.szInfo , '\0' , TEST_INFO_ARRAY_LEN);
	memset(tagUDEVisionResult.szSrcWnd ,'\0' , TEST_INFO_ARRAY_LEN);
	memcpy(&tagUDEVisionResult, pCopyDataStruct->lpData, pCopyDataStruct->cbData);


	TRACE(_T("\n"));
	TRACE(tagUDEVisionResult.szSrcWnd);
	TRACE(_T("\n"));

	USES_CONVERSION;
	CString strInfo = A2W(tagUDEVisionResult.szSrcWnd);
	if (tagUDEVisionResult.nID == 8)
	{
		for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
		{
			if (m_BL_UDEVisionList.GetItemText(i, tagUDEVisionResult.nParam2 + 2) != _T(""))
			{
				switch (tagUDEVisionResult.nParam1)
				{
				case 0://NG
					m_BL_UDEVisionList.SetItemTextColor(i, tagUDEVisionResult.nParam2 + 2, RGB(255,0,0));
					break;
				case 1://PASS
					m_BL_UDEVisionList.SetItemTextColor(i, tagUDEVisionResult.nParam2 + 2, RGB(0,255,0));
					break;
				case 2://FINISH
					m_BL_UDEVisionList.SetItemTextColor(i, tagUDEVisionResult.nParam2 + 2, RGB(0,0,255));
					break;
				default:
					break;
				}
			}
		}
		BOOL bResDispose = FALSE;//�Y����̎��
		for (size_t i = 0; i < m_vbyRobotStarUDEVisionGroup.size(); i++)
		{
			if (tagUDEVisionResult.nParam2 == m_vbyRobotStarUDEVisionGroup[i])
			{
				bResDispose = TRUE;
				m_pUDEVisionListDlg->PostMessage(WM_UDEVISION_FINISH_ROBOT, tagUDEVisionResult.nParam2, tagUDEVisionResult.nParam1);
				if ((tagUDEVisionResult.nParam1 == 0) || (tagUDEVisionResult.nParam1 == 1))//�յ��yԇ�Y��
				{
					m_vbyRobotStarUDEVisionGroup.erase(m_vbyRobotStarUDEVisionGroup.begin() + i);
				}
				break;
			}
		}
		if (!bResDispose)
		{
			m_pUDEVisionListDlg->PostMessage(WM_UDEVISION_FINISH, tagUDEVisionResult.nParam2, tagUDEVisionResult.nParam1);
		}
	}
	return CTpLayerWnd::OnCopyData(pWnd, pCopyDataStruct);
}


afx_msg LRESULT CUDEVisionListDlg::OnEdUdevisionRes(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)
	{
		for (int i = 0; i < 21; i++)
		{
			if (m_BL_edUDEVisionRes[i].IsMsgSrc())
			{
				m_nUDEVisionNO = i;
				m_BL_edUDEVisionInfo.SetValueText(m_vstrUDEVisionInfo[i]);
				CMsgBox MsgBox(this);
				CString strInfoOld;
				CString strInfoNew;
				strInfoNew = m_BL_edUDEVisionRes[i].GetValueText();
				strInfoOld = m_BL_edUDEVisionRes[i].GetValueText();
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
					m_BL_edUDEVisionRes[i].SetValueText(strInfoNew);
				}
				else
				{
					CString strAddress;
					if (strInfoNew[0] == 'R')
					{
						if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
						{
							MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
							m_BL_edUDEVisionRes[i].SetValueText(strInfoOld);
						}
						strInfoNew.Delete(0, 1);
						int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
						if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
						{
							MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
							m_BL_edUDEVisionRes[i].SetValueText(strInfoOld);
						}
					}
					if (strInfoNew[0] == 'D')
					{
						if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
						{
							m_BL_edUDEVisionRes[i].SetValueText(strInfoOld);
							MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
						}
						strInfoNew.Delete(0, 1);
						int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
						if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
						{
							MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
							m_BL_edUDEVisionRes[i].SetValueText(strInfoOld);
						}
					}
				}
			}
		}
	}
	return 0;
}



void CUDEVisionListDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		if (!m_BL_UDEVisionList.GetReadOnly())
		{
			for (int i = 0; i < m_BL_UDEVisionList.GetRows(); i++)
			{
				for (int j = 2; j < 23; j++)
				{
					m_BL_UDEVisionList.SetItemTextColor(i, j, RGB(0,255,230));
				}
			}
		}
		SetTimer(0, 1, nullptr);
		break;
	case 1:
		KillTimer(1);
		if (GetAsyncKeyState(VK_LCONTROL) || GetAsyncKeyState(VK_RCONTROL)) 
		{
			for (int i = 0; i < 21; i++)
			{
				m_BL_edUDEVisionRes[i].SetCaption(m_vstrUDEVisionRes[i]);
			}
		}
		else
		{
			for (int i = 0; i < 21; i++)
			{
				m_BL_edUDEVisionRes[i].SetCaption(m_vstrUDEVisionRes[i]);
			}
		}
		SetTimer(1, 1, nullptr);
		break;
	default:
		break;
	}
	CTpLayerWnd::OnTimer(nIDEvent);
}


void CUDEVisionListDlg::EnterPressedBledudevisioninfo(LPCTSTR strValue)
{
	// TODO: �ڴ˴������Ϣ����������
	m_vstrUDEVisionInfo[m_nUDEVisionNO] = m_BL_edUDEVisionInfo.GetValueText();
}





void CUDEVisionListDlg::StatusChangedBlrdudevisionPlc(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_BL_rdUDEVision_Robot.SetSelect(!bNewStatus);
}


void CUDEVisionListDlg::StatusChangedBlrdudevisionRobot(BOOL bNewStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_BL_rdUDEVision_PLC.SetSelect(!bNewStatus);
}
