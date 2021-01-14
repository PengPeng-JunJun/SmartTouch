#pragma once

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CProjectName 对话框

class CProjectName : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CProjectName)

public:
	CProjectName(CWnd* pParent = NULL);   // 标准构造函数
	CProjectName(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CProjectName();

	// 对话框数据
	enum { IDD = IDD_PROJECTNAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strProjectName;
public:
	CBL_Edit m_BL_ProjectName;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
