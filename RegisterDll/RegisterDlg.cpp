// RegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"


// CRegisterDlg �Ի���

IMPLEMENT_DYNAMIC(CRegisterDlg, CTpLayerWnd)

CRegisterDlg::CRegisterDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CRegisterDlg::IDD, pParent)
{

}

CRegisterDlg::CRegisterDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_strRegisterID(_T(""))
{

}

CRegisterDlg::~CRegisterDlg()
{
}

void CRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_SoftwareID, m_BL_SoftwareID);
	DDX_Control(pDX, IDC_BL_RegisterID, m_BL_RegisterID);
	DDX_Control(pDX, IDC_BL_StartRegister, m_BL_StartRegister);
	DDX_Control(pDX, IDC_BL_StopRegister, m_BL_StopRegister);
}

void CRegisterDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}

BEGIN_MESSAGE_MAP(CRegisterDlg, CTpLayerWnd)
END_MESSAGE_MAP()

CString CRegisterDlg::GetSoftwareID()//�@ȡܛ��ID
{
	vector<CString> strMacAdd;
	m_HardwareInfo.GetMacAdd(&strMacAdd);

	if (strMacAdd.size() > 0)
	{
		int MACNum = Rand(1, strMacAdd.size());
		m_BL_SoftwareID.SetValueText(strMacAdd[MACNum - 1]);//�@ʾܛ��ID
		return strMacAdd[MACNum - 1];
	}
	else
	{
		CMsgBox Msgbox(this);
		Msgbox.ShowMsg(_T("δ�z�y���W��"), _T("�W����ԃʧ��"), MB_OK | MB_ICONSTOP);
		return NULL;
	}
}

void CRegisterDlg::GetRegisterID(CString strMacAdd)
{
	int nMACLength;
	nMACLength = strMacAdd.GetLength();
	char *pStrData = new char[nMACLength + 1];
	int nCounter = 0;
	for (;nCounter < nMACLength; nCounter++)
	{
		if(strMacAdd[nCounter] != '-')
		{
			if (strMacAdd[nCounter] >=48 && strMacAdd[nCounter] <= 57)
			{
				if (strMacAdd[nCounter] == '5' || strMacAdd[nCounter] == '6')
				{
					pStrData[nCounter] = strMacAdd[nCounter] + 11;
				}
				if (strMacAdd[nCounter] == '7' || strMacAdd[nCounter] == '8')
				{
					pStrData[nCounter] = strMacAdd[nCounter] - 18;
				}
				if (strMacAdd[nCounter] == '0' || strMacAdd[nCounter] == '9')
				{
					pStrData[nCounter] = strMacAdd[nCounter] - 14;
				}
				if (strMacAdd[nCounter] == '1' || strMacAdd[nCounter] == '3')
				{
					pStrData[nCounter] = strMacAdd[nCounter] + 10;
				}
				else
				{
					pStrData[nCounter] = strMacAdd[nCounter] + 3;
				}
			}
			else
			{

				if((strMacAdd[nCounter] >= 65) && (strMacAdd[nCounter] <= 79))
				{
					pStrData[nCounter] = strMacAdd[nCounter] - 18;
				}
				if((strMacAdd[nCounter] >= 80) && (strMacAdd[nCounter] <= 90))
				{
					pStrData[nCounter] = strMacAdd[nCounter] - 47;
				}
			}
		}
		else
		{
			pStrData[nCounter] = '-';
		}
	}
	pStrData[nCounter] = '\0';
	m_strRegisterID = pStrData;  //�����ע����
	
}
// CRegisterDlg ��Ϣ�������

void CRegisterDlg::Write2RegisterList()
{
	CRegKey key;
	BOOL bOpenReg = key.Open(HKEY_CURRENT_USER,_T("UDE_Report\\Register"));
	key.SetStringValue(_T("RegisterPassword"),m_strRegisterID);//��ע����Ϣд��ע���
	key.Close();
}

void CRegisterDlg::CheckRegisterList(int nCheckMode)
{
	HKEY hKey;
	long ret;
	LPTSTR RegPath = _T("UDE_Report\\Register");
	ret = RegOpenKeyEx(HKEY_CURRENT_USER,RegPath,0,KEY_READ,&hKey);
	if (ret != ERROR_SUCCESS)//����ע������Ƿ���ڸü�
	{
		CRegKey key;
		key.Create(HKEY_CURRENT_USER,_T("UDE_Report\\Register"));
		key.Close();
	}
	else
	{
		CRegKey key;
		TCHAR s[_MAX_PATH];
		CString strRegisterPassword;
		DWORD  Word = _MAX_PATH;
		BOOL bOpenReg = key.Open(HKEY_CURRENT_USER,_T("UDE_Report\\Register"));
		key.QueryStringValue(_T("RegisterPassword"),s,&Word);
		strRegisterPassword = s;
		switch (nCheckMode)
		{
		case CHECKREGISTERLIST:
			if (!CheckRegisterID(strRegisterPassword))
			{
				GetSoftwareID();
				m_pRegister->SendMessage(WM_REGISTER, REGISTERERROR);
				ShowWindow(SW_SHOW);
			}
			else
			{
				m_pRegister->SendMessage(WM_REGISTER, REGISTEROK);
			}
			break;
		default:
			break;
		}
		
	}
}

BOOL CRegisterDlg::CheckRegisterID(CString strRegisterID)
{
	vector<CString> strMacAdd;
	m_HardwareInfo.GetMacAdd(&strMacAdd);
	for (UINT nCounter = 0; nCounter < strMacAdd.size(); nCounter++)
	{
		GetRegisterID(strMacAdd[nCounter]);//�õ�һ��MAC
		if (strRegisterID == m_strRegisterID)//ע����Ա�
		{
			m_BL_SoftwareID.SetValueText(strMacAdd[nCounter]);
			m_BL_RegisterID.SetValueText(_T("ܛ�w���]��"));
			m_BL_RegisterID.SetReadOnly(TRUE);
			m_BL_StartRegister.ShowWindow(SW_HIDE);
			m_BL_StopRegister.SetCaption(_T("�˳�"));
			Write2RegisterList();
			return TRUE;
		}
	}
	m_BL_RegisterID.SetValueText(_T(""));
	return FALSE;
}


int CRegisterDlg::Rand(int nMin, int nMax)
{
	srand((unsigned)time(nullptr) + rand());
	const int nRand = rand() % (nMax - nMin + 1) + nMin;
	return nRand;
}


BEGIN_EVENTSINK_MAP(CRegisterDlg, CTpLayerWnd)
	ON_EVENT(CRegisterDlg, IDC_BL_StopRegister, 1, CRegisterDlg::LBtClickedBlStopRegister, VTS_I4)
	ON_EVENT(CRegisterDlg, IDC_BL_StartRegister, 1, CRegisterDlg::LBtClickedBlStartRegister, VTS_I4)
END_EVENTSINK_MAP()


void CRegisterDlg::LBtClickedBlStopRegister(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	OnCancel();
}


void CRegisterDlg::LBtClickedBlStartRegister(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox Msgbox(this);
	
	if (CheckRegisterID(m_BL_RegisterID.GetValueText()))
	{
		Msgbox.ShowMsg(_T("    �]�Գɹ�"), _T("�]�����"), MB_OK | MB_ICONINFORMATION);
		m_pRegister->SendMessage(WM_REGISTER, REGISTEROK);
	}
	else
	{
		Msgbox.ShowMsg(_T("    �]�Դa�e�`"), _T("�]��ʧ��"), MB_OK | MB_ICONSTOP);
	}
	
}

