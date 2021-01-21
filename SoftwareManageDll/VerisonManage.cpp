// VerisonManage.cpp : 实现文件
//

#include "stdafx.h"
#include "VerisonManage.h"
#include "afxdialogex.h"


// CVerisonManage 对话框

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


// CVerisonManage 消息处理程序
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

	UpdateInfoTemp.strUpdateDate = _T("V11.1.1    修改時間：2021年01月14日");
	UpdateInfoTemp.strUpdateInfo = _T("1.關於界面添加軟件升級信息;2.修改手臂消息BUG;3.自動鎖定時長可設置;4.窗口名稱可設置");
	deUpdateInfo.push_front(UpdateInfoTemp);

	UpdateInfoTemp.strUpdateDate = _T("V11.1.2    修改時間：2021年01月21日");
	UpdateInfoTemp.strUpdateInfo = _T("1.修改自動加載檔案BUG");
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

