// NumberInputDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "NumberInputDlg.h"
#include "afxdialogex.h"


// CNumberInputDlg �Ի���

IMPLEMENT_DYNAMIC(CNumberInputDlg, CTpLayerWnd)

CNumberInputDlg::CNumberInputDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CNumberInputDlg::IDD, pParent)
	, m_nSendValue(0)
{

}

CNumberInputDlg::CNumberInputDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nSendValue(0)
{

}

CNumberInputDlg::~CNumberInputDlg()
{
}

void CNumberInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);

	for (int i = 0; i < 11; i++)
	{
		DDX_Control(pDX, IDC_BL_btInput_0 + i, m_BL_btNumberInput[i]);
	}

	DDX_Control(pDX, IDC_BL_edSendValue, m_BL_edSendValue);
	DDX_Control(pDX, IDC_BL_edCurrentValue, m_BL_edCurrentValue);
	DDX_Control(pDX, IDC_BL_edPtByte, m_BL_edPtByte);
	
}


BEGIN_MESSAGE_MAP(CNumberInputDlg, CTpLayerWnd)
	ON_MESSAGE(WM_BT_NUMBER_INPUT, &CNumberInputDlg::OnBtNumberInput)
END_MESSAGE_MAP()


// CNumberInputDlg ��Ϣ�������


BOOL CNumberInputDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_BtBaseClose.ShowWindow(SW_HIDE);
	m_BL_edCurrentValue.SetValueText(m_strCurrentValue);
	m_BL_edPtByte.SetValueText(m_strPtByte);

	if (m_strPtByte == _T("0"))
	{
		m_BL_btNumberInput[10].SetEnabled(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


afx_msg LRESULT CNumberInputDlg::OnBtNumberInput(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)//�Γ�������I
	{
		for (int i = 0; i < 11; i++)
		{
			if(m_BL_btNumberInput[i].IsMsgSrc())
			{
				CString strTem;
				strTem = m_BL_edSendValue.GetValueText();
				strTem.Append(m_BL_btNumberInput[i].GetCaption());
				if (strTem.GetLength() == 1)
				{
					if (strTem[0] == '.')
					{
						m_BL_edSendValue.SetValueText(_T(""));
						return 0;
					}
				}
				m_BL_edSendValue.SetValueText(strTem);
				if (m_BL_btNumberInput[i].GetCaption() == _T("."))
				{
					m_BL_btNumberInput[i].SetEnabled(FALSE);
				}
			}
		}
	}
	return 0;
}

void CNumberInputDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CString strTem;
	strTem = m_BL_edSendValue.GetValueText();
	if (strTem.GetLength() > 0)
	{
		if (strTem[strTem.GetLength() - 1] == '.')
		{
			strTem.Delete(strTem.GetLength() - 1, 1);
		}
		m_nSendValue = (int)(_ttof(strTem) * pow(10, _ttoi(m_strPtByte)));
	}
	CTpLayerWnd::OnOK();
}

BEGIN_EVENTSINK_MAP(CNumberInputDlg, CTpLayerWnd)
	ON_EVENT(CNumberInputDlg, IDC_BL_edSendValue, 1, CNumberInputDlg::ValueChangedBledsendvalue, VTS_BSTR)
	ON_EVENT(CNumberInputDlg, IDC_BL_btDelet, 1, CNumberInputDlg::LBtClickedBlbtdelet, VTS_I4)
	ON_EVENT(CNumberInputDlg, IDC_BL_btInput_Clean, 1, CNumberInputDlg::LBtClickedBlbtinputClean, VTS_I4)
END_EVENTSINK_MAP()


void CNumberInputDlg::ValueChangedBledsendvalue(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strTem;
	strTem = strNew;
	if (strTem.GetLength() == 1)
	{
		if (strTem[0] == '.')
		{
			m_BL_edSendValue.SetValueText(_T(""));
			return;
		}
	}

	if (m_strPtByte != _T("0"))//��С��
	{
		if (strTem.GetLength() > 0)
		{
			if (m_ValueCalculate.FindCharInString(strTem, '.').size() < 1)
			{
				m_BL_btNumberInput[10].SetEnabled(TRUE);
				if  (((strTem[strTem.GetLength() - 1] > '9') || (strTem[strTem.GetLength() - 1] < '0')) && (strTem[strTem.GetLength() - 1] != '.'))
				{
					strTem.Delete(strTem.GetLength() - 1, 1);
					m_BL_edSendValue.SetValueText(strTem);
				}
			}
			else if(m_ValueCalculate.FindCharInString(strTem, '.').size() == 1)
			{
				m_BL_btNumberInput[10].SetEnabled(FALSE);
				if (((strTem[strTem.GetLength() - 1] > '9') || (strTem[strTem.GetLength() - 1] < '0')) && (strTem[strTem.GetLength() - 1] != '.'))
				{
					strTem.Delete(strTem.GetLength() - 1, 1);
					m_BL_edSendValue.SetValueText(strTem);
				}
			}
			else
			{
				m_BL_btNumberInput[10].SetEnabled(FALSE);
				if ((strTem[strTem.GetLength() - 1] > '9') || (strTem[strTem.GetLength() - 1] < '0'))
				{
					strTem.Delete(strTem.GetLength() - 1, 1);
					m_BL_edSendValue.SetValueText(strTem);
				}
			}
		}
		else
		{
			m_BL_btNumberInput[10].SetEnabled(TRUE);
		}
	}
	else//�oС��
	{
		if (strTem.GetLength() > 0)
		{
			if ((strTem[strTem.GetLength() - 1] > '9') || (strTem[strTem.GetLength() - 1] < '0'))
			{
				strTem.Delete(strTem.GetLength() - 1, 1);
				m_BL_edSendValue.SetValueText(strTem);
			}
		}
	}
}


void CNumberInputDlg::LBtClickedBlbtdelet(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CString strTem;
	strTem = m_BL_edSendValue.GetValueText();
	strTem.Delete(strTem.GetLength() - 1, 1);
	m_BL_edSendValue.SetValueText(strTem);
	if (m_strPtByte != _T("0"))
	{
		int nFindRes = strTem.Find('.');
		if (nFindRes >= 0)
		{
			m_BL_btNumberInput[10].SetEnabled(FALSE);
		}
		else
		{
			m_BL_btNumberInput[10].SetEnabled(TRUE);
		}
	}
}

void CNumberInputDlg::LBtClickedBlbtinputClean(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	m_BL_edSendValue.SetValueText(_T(""));
}




