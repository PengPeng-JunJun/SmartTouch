#pragma once
#include "TpLayerWnd.h"


// CBtLayerWnd �Ի���

class AFX_EXT_CLASS CBtLayerWnd : public CDialogEx
{
	DECLARE_DYNAMIC(CBtLayerWnd)

public:
	CBtLayerWnd(CWnd* pParent = NULL);   // ��׼���캯��
	CBtLayerWnd(UINT nIDTemplate, CWnd* pParent = nullptr);
	virtual ~CBtLayerWnd();

	// �Ի�������
	enum { IDD = IDD_BTLAYERWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	CWnd *m_pTopWnd;
	virtual BOOL OnInitDialog();
protected:
	int m_nTrans;	
	COLORREF m_rgbBack;
private:
	BLENDFUNCTION m_Blend;
	void __DrawBorder(Graphics * pGraph, Pen * pen, Brush * pBrush, RectF rect, REAL fOfst);
	void __DrawTarget(Graphics * pGraph, Pen * pen, Brush * pBrush, GraphicsPath * pPath);
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
protected:
	afx_msg LRESULT OnGmsgtplayerwndclose(WPARAM wParam, LPARAM lParam);
};
