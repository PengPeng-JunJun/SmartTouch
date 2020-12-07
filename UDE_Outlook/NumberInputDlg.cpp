// NumberInputDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "NumberInputDlg.h"
#include "afxdialogex.h"


// CNumberInputDlg 对话框

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


// CNumberInputDlg 消息处理程序


BOOL CNumberInputDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_BtBaseClose.ShowWindow(SW_HIDE);
	m_BL_edCurrentValue.SetValueText(m_strCurrentValue);
	m_BL_edPtByte.SetValueText(m_strPtByte);

	if (m_strPtByte == _T("0"))
	{
		m_BL_btNumberInput[10].SetEnabled(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


afx_msg LRESULT CNumberInputDlg::OnBtNumberInput(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 0)//單擊鼠標左鍵
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
	// TODO: 在此添加专用代码和/或调用基类
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
	// TODO: 在此处添加消息处理程序代码
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

	if (m_strPtByte != _T("0"))//有小數
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
	else//無小數
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
	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此处添加消息处理程序代码
	m_BL_edSendValue.SetValueText(_T(""));
}




