#pragma once

#include "Resource.h"

// CSplashWnd �Ի���

class AFX_EXT_CLASS CSplashWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CSplashWnd)

public:
	CSplashWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSplashWnd();

// �Ի�������
	enum { IDD = IDD_SPLASHWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
