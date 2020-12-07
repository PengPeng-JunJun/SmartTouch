#pragma once

#include <vector>

#include "PointEx.h"
#include "ResizeRect.h"

class AFX_EXT_CLASS CPolygon : public CResizeRect
{
public:
	CPolygon(void);
	~CPolygon(void);

public:
	std::vector<CPointEx> m_vOutline;	// ��������

	virtual void SerializeEx(CArchive& ar);

	virtual void StartDrawing(CWnd * pOwner);						// ��ʼ���߿�
	virtual BOOL LButtonDown(UINT nFlags, CPoint point);			// ����������������
	virtual BOOL LButtonUp(UINT nFlags, CPoint point);				// �������������ͷ�
	virtual BOOL MouseMove(UINT nFlags, CPoint point);				// ����������ƶ�
	virtual BOOL RButtonUp(UINT nFlags, CPoint point);				// ����������Ҽ��ͷ�

	virtual void Draw(CDC * pDC);	// ��DC�л�����

	void SetEmpty(void);

	AFX_INLINE void Offset(CPoint ptOffset);

	AFX_INLINE void operator =  (const CPolygon & pl);
	AFX_INLINE BOOL operator == (const CPolygon & pl);
	AFX_INLINE BOOL operator != (const CPolygon & pl);

protected:
	BOOL m_bDragCorner;
	CRect m_rcBkup;
	std::vector<CPointEx> m_vBkup;		// ��������

	void _GetFrameRect(void);
	void _MoveTo(CPoint ptDst);			// �ƶ���Ŀ���
};

