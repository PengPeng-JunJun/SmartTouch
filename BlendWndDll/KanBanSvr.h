#pragma once

#include "MsgBox.h"

#define NET_KANBAN_DEFAULT_PORT	9999

// CKanBanSvr 对话框

class AFX_EXT_CLASS CKanBanSvr : public CTpLayerWnd
{
	DECLARE_SERIAL(CKanBanSvr)

public:
	CKanBanSvr(CWnd* pParent = NULL);   // 标准构造函数
	CKanBanSvr(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CKanBanSvr();

// 对话框数据
	enum { IDD = IDD_KANBANSVR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strIp;
	int m_nPort;
	CString m_strStartFix;
	CString m_strEndFix;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);

	void LoadDefaultIpPortFix(void);
	void SaveDefaultIpPortFix(void);
protected:
	CString m_strIpBkup;
	int m_nPortBkup;

	CString m_strStartFixBkup;
	CString m_strEndFixBkup;

	void _UpdateUi(void);
};
