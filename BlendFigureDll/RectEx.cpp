#include "stdafx.h"
#include "RectEx.h"


CRectEx::CRectEx(void)
	: left(0)
	, right(0)
	, top(0)
	, bottom(0)
	, m_dAngle(0)
{
}


CRectEx::CRectEx(double dLeft, double dTop, double dRight, double dBottom)
{
	left	 = dLeft;
	top		 = dTop;
	right	 = dRight;
	bottom	 = dBottom;

	m_dAngle = 0.0;
	m_ptTopRight = CPointEx(right, top);
}


CRectEx::CRectEx(CPointEx ptTopLeft, CPointEx ptBottomRight)
{
	left	 = ptTopLeft.x;
	top		 = ptTopLeft.y;
	right	 = ptBottomRight.x;
	bottom	 = ptBottomRight.y;

	m_dAngle = 0.0;
	m_ptTopRight = CPointEx(right, top);
}

CRectEx::CRectEx(CPoint ptTopLeft, CPoint ptBottomRight)
{
	left	 = ptTopLeft.x;
	top		 = ptTopLeft.y;
	right	 = ptBottomRight.x;
	bottom	 = ptBottomRight.y;

	m_dAngle = 0.0;
	m_ptTopRight = CPointEx(right, top);
}


CRectEx::~CRectEx(void)
{
}


// ���Ͻ�
AFX_INLINE CPointEx &CRectEx::TopLeft(void)
{
	return *((CPointEx*)this);
}


// ���½�
AFX_INLINE CPointEx CRectEx::BottomLeft(void)
{
	return CPointEx(left, bottom);
}


// ���Ͻ�
AFX_INLINE CPointEx CRectEx::TopRight(void)
{
	return CPointEx(right, top);
}


// ���½�
AFX_INLINE CPointEx &CRectEx::BottomRight(void)
{
	return *((CPointEx*)this + 1);
}


// ��������
AFX_INLINE CPointEx CRectEx::CenterPoint(void)
{
	return CPointEx((left + right) / 2.0, (top + bottom) / 2.0);
}


AFX_INLINE double CRectEx::Width(void)
{
	return fabs(right - left);
}


// �������
AFX_INLINE LONG CRectEx::IntWidth(void)
{
	return (LONG)(Width() + FORTHINT);
}


// 1/2 ���
AFX_INLINE double CRectEx::HalfWidth(void)
{
	return Width() / 2.0;
}


// ���� 1/2 ���
AFX_INLINE LONG CRectEx::IntHalfWidth(void)
{
	return (LONG)(HalfWidth() + FORTHINT);
}


// �߶�
AFX_INLINE double CRectEx::Height(void)
{
	return fabs(bottom - top);
}


// �����߶�
AFX_INLINE LONG CRectEx::IntHeight(void)
{
	return (LONG)(Height() + FORTHINT);
}


// 1/2 �߶�
AFX_INLINE double CRectEx::HalfHeight(void)
{
	return Height() / 2.0;
}


// ���� 1/2 �߶�
AFX_INLINE LONG CRectEx::IntHalfHeight(void)
{
	return (LONG)(HalfHeight() + FORTHINT);
}


// �Խ��߳���
AFX_INLINE double CRectEx::CrossDistance(void)
{
	return sqrt(Width() * Width() + Height() * Height());
}


// �����Խ��߳���
AFX_INLINE LONG CRectEx::IntCrossDistance(void)
{
	return (LONG)sqrt(Width() * Width() + Height() * Height());
}


// ת����CRect
AFX_INLINE CRect CRectEx::Convert2Crect(void)
{
	CRect rcTemp;
	rcTemp.left = (LONG)(left + FORTHINT);
	rcTemp.top = (LONG)(top + FORTHINT);
	rcTemp.right = (LONG)(right + FORTHINT);
	rcTemp.bottom = (LONG)(bottom + FORTHINT);

	return rcTemp;
}


AFX_INLINE void CRectEx::SetRectEmpty()
{
	left	 = 0.0;
	top		 = 0.0;
	right	 = 0.0;
	bottom	 = 0.0;
}


// ��������
AFX_INLINE LONG CRectEx::IntLeft(void)
{
	return (LONG)(left + FORTHINT);
}


// ��������
AFX_INLINE LONG CRectEx::IntRight(void)
{
	return (LONG)(right + FORTHINT);
}


// ��������
AFX_INLINE LONG CRectEx::IntTop(void)
{
	return (LONG)(top + FORTHINT);
}


// ��������
AFX_INLINE LONG CRectEx::IntBottom(void)
{
	return (LONG)(bottom + FORTHINT);
}


// ��һ��
AFX_INLINE CRectEx CRectEx::NormalizeRect(void)
{
	if (left > right)
	{
		double dTemp = right;
		right = left;
		left = dTemp;
	}

	if (top > bottom)
	{
		double dTemp = bottom;
		bottom = top;
		top = dTemp;
	}

	return CRectEx(left, top, right, bottom);
}


// �����Ƿ�Ϊ��
AFX_INLINE BOOL CRectEx::IsRectEmpty(void)
{
	return 0.0 == Width() || 0.0 == Height();
}


// ��ת
AFX_INLINE void CRectEx::Rotation(CPointEx ptCenter, double dAngle)
{
}


// ���ز����� =
AFX_INLINE void CRectEx::operator = (const CRectEx & rcect)
{
	left	= rcect.left;
	top		= rcect.top;
	right	= rcect.right;
	bottom	= rcect.bottom;
}


// ���ز����� =
AFX_INLINE void CRectEx::operator = (const CRect & rcect)
{
	left	= (double)rcect.left;
	top		= (double)rcect.top;
	right	= (double)rcect.right;
	bottom	= (double)rcect.bottom;
}


// ���ز����� ==
AFX_INLINE BOOL CRectEx::operator == (const CRectEx & rcect)
{
	return left	== rcect.left &&
		top == rcect.top &&
		right == rcect.right &&
		bottom == rcect.bottom;
}


// ���ز����� !=
AFX_INLINE BOOL CRectEx::operator != (const CRectEx & rcect)
{
	return left	!= rcect.left ||
		top != rcect.top ||
		right != rcect.right ||
		bottom != rcect.bottom;
}
