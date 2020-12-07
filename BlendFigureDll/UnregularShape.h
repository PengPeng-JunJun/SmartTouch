#pragma once

#include "resource.h"

#include <vector>
#include "PointEx.h"
#include "ResizeRect.h"
#include "BlendFigureDefine.h"

class AFX_EXT_CLASS CUnregularShape : public CResizeRect
{
public:
	CUnregularShape(void);
	~CUnregularShape(void);

	std::vector<CPointEx> m_vOutline;	// ��������

	virtual void SerializeEx(CArchive& ar);

	virtual void StartDrawing(CWnd * pOwner);						// ��ʼ���߿�
	virtual BOOL LButtonDown(UINT nFlags, CPoint point);			// ����������������
	virtual BOOL LButtonUp(UINT nFlags, CPoint point);				// �������������ͷ�
	virtual BOOL MouseMove(UINT nFlags, CPoint point);				// ����������ƶ�

	virtual void Draw(CDC * pDC);	// ��DC�л�����

	void SetEmpty(void);

	AFX_INLINE void Offset(CPoint ptOffset);

	AFX_INLINE void operator =  (const CUnregularShape & UnrShape);
	AFX_INLINE BOOL operator == (const CUnregularShape & UnrShape);
	AFX_INLINE BOOL operator != (const CUnregularShape & UnrShape);

protected:
	CRect m_rcBkup;
	std::vector<CPointEx> m_vBkup;			// ��������

	void _GetFrameRect(void);
	void _MoveTo(CPoint ptDst);				// �ƶ���Ŀ���
};

