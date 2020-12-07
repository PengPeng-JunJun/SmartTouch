#pragma once

#include "Resource.h"

// CSplashWnd 对话框

class AFX_EXT_CLASS CSplashWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSplashWnd();

// 对话框数据
	enum { IDD = IDD_SPLASHWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
