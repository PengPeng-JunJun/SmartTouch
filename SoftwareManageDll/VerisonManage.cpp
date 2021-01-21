// VerisonManage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VerisonManage.h"
#include "afxdialogex.h"


// CVerisonManage �Ի���

IMPLEMENT_DYNAMIC(CVerisonManage, CTpLayerWnd)

CVerisonManage::CVerisonManage(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CVerisonManage::IDD, pParent)
{

}

CVerisonManage::CVerisonManage(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
{

}

CVerisonManage::~CVerisonManage()
{
}

void CVerisonManage::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_btVersion, m_BL_btVersion);
	DDX_Control(pDX, IDC_BL_UpdateInfoList, m_BL_ltUpdateInfo);
}


BEGIN_MESSAGE_MAP(CVerisonManage, CTpLayerWnd)
END_MESSAGE_MAP()


// CVerisonManage ��Ϣ�������
void CVerisonManage::_DefaultFocus(void)
{
	//m_BtBaseOk.ShowWindow(SW_HIDE);
	m_BtBaseCancel.ShowWindow(SW_HIDE);
}

void CVerisonManage::_ShowInfo()
{
	m_BL_ltUpdateInfo.DeleteAll(FALSE);

	m_BL_ltUpdateInfo.AppendColumn(_T("No."),DT_LEFT,30,FALSE);

	struct UpdateInfo
	{
		CString strUpdateDate;
		CString strUpdateInfo;
	};

	deque<UpdateInfo> deUpdateInfo;

	UpdateInfo UpdateInfoTemp;

	UpdateInfoTemp.strUpdateDate = _T("V11.1.1    �޸ĕr�g��2021��01��14��");
	UpdateInfoTemp.strUpdateInfo = _T("1.�P춽������ܛ��������Ϣ;2.�޸��ֱ���ϢBUG;3.�Ԅ��i���r�L���O��;4.�������Q���O��");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V11.1.2    �޸ĕr�g��2021��01��21��");
	UpdateInfoTemp.strUpdateInfo = _T("1.�޸��ԄӼ��d�n��BUG");
	deUpdateInfo.push_front(UpdateInfoTemp);


	CValueCalculate ValueCalculate;
	for (size_t i = 0; i < deUpdateInfo.size(); i++)
	{
		m_BL_ltUpdateInfo.AppendRow(TRUE);
		m_BL_ltUpdateInfo.SetItemText(m_BL_ltUpdateInfo.GetRows() - 1, 0, deUpdateInfo[i].strUpdateDate);
		m_BL_ltUpdateInfo.SetItemTextColor(m_BL_ltUpdateInfo.GetRows() - 1, 0, RGB(255, 155, 32));

		vector<CString> vstrTemp = ValueCalculate.CutStringElse(deUpdateInfo[i].strUpdateInfo, ';');

		for (size_t j = 0; j < vstrTemp.size(); j++)
		{
			m_BL_ltUpdateInfo.AppendRow(TRUE);
			
			m_BL_ltUpdateInfo.SetItemText(m_BL_ltUpdateInfo.GetRows() - 1, 0, _T("   ") + vstrTemp[j]);
			m_BL_ltUpdateInfo.SetItemTextColor(m_BL_ltUpdateInfo.GetRows() - 1, 0, RGB(0, 255, 230));
		}
	}
	m_BL_ltUpdateInfo.SelectRow(0);
}

