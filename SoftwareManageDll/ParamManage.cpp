// ParamManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ParamManage.h"
#include "afxdialogex.h"

// CParamManage �Ի���

IMPLEMENT_DYNAMIC(CParamManage, CTpLayerWnd)

CParamManage::CParamManage(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CParamManage::IDD, pParent)
{

}

CParamManage::CParamManage(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CParamManage::~CParamManage()
{

}

void CParamManage::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ParamManageList, m_BL_ltParamManage);
}


BEGIN_MESSAGE_MAP(CParamManage, CTpLayerWnd)
END_MESSAGE_MAP()


// CParamManage ��Ϣ�������


BOOL CParamManage::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);

	SetTitle(_T("�����޸����I"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CParamManage::_ShowInfo()
{
	m_BL_ltParamManage.DeleteAll(FALSE);

	m_BL_ltParamManage.AppendColumn(_T("�M̖"),DT_CENTER,50,FALSE);
	m_BL_ltParamManage.AppendColumn(_T("�Ŀ̖"),DT_CENTER,70,FALSE);
	m_BL_ltParamManage.AppendColumn(_T("׃��ǰ"),DT_CENTER,420,FALSE);
	m_BL_ltParamManage.AppendColumn(_T("׃����"),DT_CENTER,420,FALSE);
	//m_BL_ltParamManage.AppendColumn(_T("�����T"),DT_CENTER,50,FALSE);

// 	for (size_t i = 0; i < m_dqQualityInfo.size(); i++)
// 	{
// 		for (size_t j = 0; j < m_dqQualityInfo[i].dqstrInfo.size(); j++)
// 		{
// 			m_BL_ltParamManage.AppendRow(TRUE);
// 			CString strTemp;
// 			strTemp.Format(_T("%d"), m_dqQualityInfo[i].nGroup);
// 			const int nRow = m_BL_ltParamManage.GetRows();
// 			m_BL_ltParamManage.SetItemText(m_BL_ltParamManage.GetRows() - 1, 1, strTemp);
// 			strTemp.Format(_T("%d"), m_dqQualityInfo[i].nProject);
// 			m_BL_ltParamManage.SetItemText(m_BL_ltParamManage.GetRows() - 1, 2, strTemp);
// 
// 			m_BL_ltParamManage.SetItemText(m_BL_ltParamManage.GetRows() - 1, 3, m_dqQualityInfo[i].strName);
// 			m_BL_ltParamManage.SetItemText(m_BL_ltParamManage.GetRows() - 1, 4, m_dqQualityInfo[i].dqstrInfo[j]);
// 		}
// 	}
}