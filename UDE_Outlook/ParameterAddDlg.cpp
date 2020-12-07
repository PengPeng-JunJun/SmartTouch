// ParameterAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ParameterAddDlg.h"
#include "afxdialogex.h"


// CParameterAddDlg �Ի���

IMPLEMENT_DYNAMIC(CParameterAddDlg, CTpLayerWnd)

CParameterAddDlg::CParameterAddDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CParameterAddDlg::IDD, pParent)
	, m_nDataStar(0)
	, m_nDataEnd(0)
	, m_nDataInterval(0)
	, m_nDataBits(0)
{

}

CParameterAddDlg::CParameterAddDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_nDataStar(0)
	, m_nDataEnd(0)
	, m_nDataInterval(0)
	, m_nDataBits(0)
{
}

CParameterAddDlg::~CParameterAddDlg()
{
}

void CParameterAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_edDataStar, m_BL_edDataStar);
	DDX_Control(pDX, IDC_BL_edDataEnd, m_BL_edDataEnd);
	DDX_Control(pDX, IDC_BL_edDataInterval, m_BL_edDataInterval);
	DDX_Control(pDX, IDC_BL_dpDataBits, m_BL_dpDataBits);
}


BEGIN_MESSAGE_MAP(CParameterAddDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CParameterAddDlg ��Ϣ�������
BEGIN_EVENTSINK_MAP(CParameterAddDlg, CTpLayerWnd)
	ON_EVENT(CParameterAddDlg, IDC_BL_edDataStar, 1, CParameterAddDlg::ValueChangedBleddatastar, VTS_BSTR)
	ON_EVENT(CParameterAddDlg, IDC_BL_edDataEnd, 1, CParameterAddDlg::ValueChangedBleddataend, VTS_BSTR)
END_EVENTSINK_MAP()


void CParameterAddDlg::ValueChangedBleddatastar(LPCTSTR strNew)
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
		m_BL_edDataStar.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edDataStar.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edDataStar.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edDataStar.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edDataStar.SetValueText(strInfoOld);
			}
		}
	}
}


void CParameterAddDlg::ValueChangedBleddataend(LPCTSTR strNew)
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
		m_BL_edDataEnd.SetValueText(strInfoNew);
	}
	else
	{
		CString strAddress;
		if (strInfoNew[0] == 'R')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edDataEnd.SetValueText(strInfoOld);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd) - _ttoi(m_strRegistersStart);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� R �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edDataEnd.SetValueText(strInfoOld);
			}
		}
		if (strInfoNew[0] == 'D')
		{
			if ((strInfoNew[strInfoNew.GetLength() - 1] < '0') || (strInfoNew[strInfoNew.GetLength() - 1] > '9'))
			{
				m_BL_edDataEnd.SetValueText(strInfoOld);
				MsgBox.ShowMsg(_T("��������ֻ̖�ܞ锵��"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
			}
			strInfoNew.Delete(0, 1);
			int nSub = _ttoi(m_strRegistersEnd1) - _ttoi(m_strRegistersStart1);
			if ((_ttoi(strInfoNew) - _ttoi(m_strRegistersPos)) > nSub)
			{
				MsgBox.ShowMsg(_T("���񼯔����� D �����������O�ù���"), _T("�o���@ȡ"), MB_ICONSTOP | MB_OK);
				m_BL_edDataEnd.SetValueText(strInfoOld);
			}
		}
	}
}


void CParameterAddDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CMsgBox MsgBox(this);
	if (m_BL_edDataStar.GetValueText().GetLength() <= 1)
	{
		MsgBox.ShowMsg(_T("����������ʼݔ���e�`"), _T("�o�����"), MB_ICONSTOP | MB_OK);
		return;
	}
	if (m_BL_edDataEnd.GetValueText().GetLength() <= 1)
	{
		MsgBox.ShowMsg(_T("���������Y��ݔ���e�`"), _T("�o�����"), MB_ICONSTOP | MB_OK);
		return;
	}
	if (m_BL_edDataStar.GetValueText()[0] != m_BL_edDataEnd.GetValueText()[0])
	{
		MsgBox.ShowMsg(_T("����������Ͳ�һ��ݔ���e�`"), _T("�o�����"), MB_ICONSTOP | MB_OK);
		return;
	}
	if (m_BL_edDataInterval.GetValueText() == _T(""))
	{
		MsgBox.ShowMsg(_T("δݔ�딵���g��"), _T("�o�����"), MB_ICONSTOP | MB_OK);
		return;
	}

	CString strTemStar;
	CString strTemEnd;

	strTemStar = m_BL_edDataStar.GetValueText();
	strTemEnd = m_BL_edDataEnd.GetValueText();

	strTemStar.Delete(0, 1);
	strTemEnd.Delete(0, 1);

	if (_ttoi(strTemEnd) <= _ttoi(strTemStar))
	{
		MsgBox.ShowMsg(_T("��������ݔ���e�`���Y����ַ�������ʼ��ַ"), _T("�o�����"), MB_ICONSTOP | MB_OK);
		return;
	}
	if ((_ttoi(strTemEnd) - _ttoi(strTemStar)) < m_BL_edDataInterval.GetIntValue())
	{
		MsgBox.ShowMsg(_T("��������ݔ���e�`���Y����ַ�p��ʼ��ַ����춵���g��"), _T("�o�����"), MB_ICONSTOP | MB_OK);
		return;
	}

	m_nDataStar = _ttoi(strTemStar);
	m_nDataEnd = _ttoi(strTemEnd);
	m_nDataInterval = m_BL_edDataInterval.GetIntValue();
	m_nDataBits = m_BL_dpDataBits.GetIntValue();
	m_strDataStar = m_BL_edDataStar.GetValueText();
	m_strDataEnd = m_BL_edDataEnd.GetValueText();  

	CTpLayerWnd::OnOK();
}
