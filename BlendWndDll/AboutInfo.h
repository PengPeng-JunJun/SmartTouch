#pragma once

#include "TpLayerWnd.h"

// CAboutInfo 对话框

class AFX_EXT_CLASS CAboutInfo : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CAboutInfo)

public:
	CAboutInfo(CWnd* pParent = NULL);   // 标准构造函数
	CAboutInfo(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAboutInfo();

// 对话框数据
	enum { IDD = IDD_ABOUTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();
};
