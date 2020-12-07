#pragma once

#include "AppBase.h"

#define GET_TP_LAYER(p)		(*p)

static UINT gMsgTplayerWndClose = RegisterWindowMessage(_T("gMsgTplayerWndClose"));

// CTpLayerWnd 对话框

class AFX_EXT_CLASS CTpLayerWnd : public CAppBase
{
	DECLARE_DYNAMIC(CTpLayerWnd)

public:
	CTpLayerWnd(CWnd* pParent = NULL);   // 标准构造函数
	CTpLayerWnd(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CTpLayerWnd();

	// 对话框数据
	enum { IDD = IDD_TPLAYERWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual void DrawTitle(CDC * pDC, CRect rcDraw);

	INT_PTR CreateTopWnd(BOOL bModal, CWnd * pOwner);

	void MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE);
	void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
	BOOL SetWindowPos(const CWnd * pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
protected:
	BOOL m_bModal;
	CWnd *m_pBtLayer;

	virtual void _PreShowWnd(void);
	void _CloseWnd(void);
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
