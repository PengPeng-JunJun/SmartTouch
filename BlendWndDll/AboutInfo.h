#pragma once

#include "TpLayerWnd.h"

// CAboutInfo �Ի���

class AFX_EXT_CLASS CAboutInfo : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CAboutInfo)

public:
	CAboutInfo(CWnd* pParent = NULL);   // ��׼���캯��
	CAboutInfo(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAboutInfo();

// �Ի�������
	enum { IDD = IDD_ABOUTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:	
	virtual BOOL OnInitDialog();
};
