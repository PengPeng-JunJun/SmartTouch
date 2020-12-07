#pragma once

#include "BlendFigureDefine.h"

enum
{
	RECT_TITLE_TOP = 0,
	RECT_TITLE_RIGH,
	RECT_TITLE_BOTTOM,
	RECT_TITLE_LEFT
};

class AFX_EXT_CLASS CResizeRect
{
public:
	CResizeRect(void);
	~CResizeRect(void);

public:
	CWnd *m_pOwner;					// �ͻ���ָ��

	int m_nIndex;					// ���
	CString m_strTitle;				// ����
	int m_nTitlePos;				// ������ʾλ��
	BOOL m_bDrawing;				// ���ڻ�ͼ����
	BOOL m_bLButtonDown;			// ���������±��
	BOOL m_bLock;					// �������ܱ༭
	BOOL m_bShow;					// ��ʾ����
	BOOL m_bSelect;					// ѡ����
	BOOL m_bResizing;				// ����Resize
	BOOL m_bMoving;					// �����ƶ�
	CRect m_rcFrame;				// �߿����

	virtual void Serialize(CArchive& ar, CWnd * pOwner);
	virtual void SerializeEx(CArchive& ar);

	virtual void StartDrawing(CWnd * pOwner);						// ��ʼ���߿�
	virtual BOOL LButtonDown(UINT nFlags, CPoint point);			// ����������������
	virtual BOOL LButtonUp(UINT nFlags, CPoint point);				// �������������ͷ�
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint point);			// ������˫�����	
	virtual BOOL MouseMove(UINT nFlags, CPoint point);				// ����������ƶ�
	
	virtual BOOL RButtonUp(UINT nFlags, CPoint point);				// ����������Ҽ��ͷ�
	virtual BOOL MouseWheel(UINT nFlags, short zDelta, CPoint pt);	// �����������ֹ���

	virtual void Draw(CDC * pDC);	// ��DC�л�����

	void ClearFlags(void);

	BOOL PtInAnchor(CPoint ptDst);
	BOOL PtInRect(CPoint ptDst);
	BOOL RectInRect(CRect rcDst);
	BOOL RectInRect(CResizeRect rcDst);

	CPoint & TopLeft(void);
	CPoint & BottomRight(void);
	CPoint CenterPoint(void);

	BOOL IsRectEmpty(void);
	void SetEmpty(void);
	BOOL IsChanged(void);
	void InverSelect(void);

	void SetFrameColor(COLORREF rgbFrame);
	COLORREF GetFrameColor(void);

	void SetAnchorPos(void);
	void SetAnchorColor(COLORREF rgbAnchor);
	COLORREF GetAnchorColor(void);

	void SetLineWidth(int nWidth);
	int GetLineWidth(void);

	void ShowTitle(BOOL bShow);
	void UpdateBkupFrame(void);
	CRect GetBkupFrame(void);

	const CRect * GetAnchors(void);

	AFX_INLINE void Offset(CPoint ptOffset);

	AFX_INLINE void operator =  (const CResizeRect & rect);
	AFX_INLINE BOOL operator == (const CResizeRect & rect);
	AFX_INLINE BOOL operator != (const CResizeRect & rect);

protected:
	CRect m_rcAnchor[RECT_ANCHOR_SUM];	// ê�����

	int m_nCurAnchor;					// ��ǰ�϶�ê��
	int m_nLineWidth;					// �߿��߿�
	COLORREF m_rgbFrame;				// �߿���ɫ
	COLORREF m_rgbAnchor;				// ê����ɫ
	CPoint m_ptCursor;					// ���λ��
	CPoint m_ptDown;					// ����ʱ�ĵ�
	BOOL m_bChanged;					// �����ı���
	BOOL m_bShowTitle;					// �Ƿ���ʾ����

	CRect m_rcFrameBkup;				// ���α���

	void _MoveTo(CPoint ptDst);			// �ƶ���Ŀ���
};

