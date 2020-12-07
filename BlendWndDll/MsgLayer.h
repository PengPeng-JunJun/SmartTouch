#pragma once

#include "TpLayerWnd.h"

// CMsgLayer �Ի���

class AFX_EXT_CLASS CMsgLayer : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CMsgLayer)

public:
	CMsgLayer(CWnd* pParent = NULL);   // ��׼���캯��
	CMsgLayer(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CMsgLayer();

// �Ի�������
	enum { IDD = IDD_MSGLAYER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	UINT m_unStyle;	
	int m_nRetVal;
	CString m_strMsg;

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawTitle(CDC * pDC, CRect rcDraw);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);	
protected:
	COLORREF m_rgbText;

	virtual void _DefaultFocus(void);
private:
	RectF m_rcText;
	vector<CString> m_vMsgs;
public:
	void LBtClickedBtMsgIgnore(long nFlags);
	void LBtClickedBtMsgOk(long nFlags);
	void LBtClickedBtMsgCancel(long nFlags);
};
