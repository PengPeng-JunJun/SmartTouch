#pragma once

#include "AES.h"
#include "MsgBox.h"

#define WM_PSD_LEVEL	WM_USER + 1
#define WM_PSD_ENTER	WM_USER + 2

// CPsdLayer 对话框

class AFX_EXT_CLASS CPsdMgr : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CPsdMgr)

public:
	CPsdMgr(CWnd* pParent = NULL);   // 标准构造函数
	CPsdMgr(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CPsdMgr();

// 对话框数据
	enum { IDD = IDD_PSDMGR};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bChangePsd;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
protected:
	int m_nLevel;
	CString m_strPsd;
	CString m_strDefault[PSD_LEVEL_SUM];

	BOOL _ReadCode(void);
protected:
	afx_msg LRESULT OnPsdLevel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPsdEnter(WPARAM wParam, LPARAM lParam);
};
