#pragma once
#include "resource.h"
#include "GdiplusText.h"

static UINT gMsgSemiTransBlur = RegisterWindowMessage(_T("gMsgSemiTransBlur"));

#define CRECT2RECTF(rect)	RectF((REAL)rect.left, (REAL)rect.top, (REAL)rect.Width(), (REAL)rect.Height())

// CTopBlur 对话框

class CTopBlur : public CDialogEx
{
	DECLARE_DYNAMIC(CTopBlur)

public:
	CTopBlur(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTopBlur();

	// 对话框数据
	enum { IDD = IDD_TOPBLUR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bUseLayerWnd;
	CString m_strCaption;
	virtual BOOL OnInitDialog();
private:
	BLENDFUNCTION m_Blend;
	void __DrawBorder(Graphics * pGraph, Pen * pen, Brush * pBrush, RectF rect, REAL fOfst);
	void __DrawTarget(Graphics * pGraph, Pen * pen, Brush * pBrush, GraphicsPath * pPath);
public:
	afx_msg void OnPaint();
};
