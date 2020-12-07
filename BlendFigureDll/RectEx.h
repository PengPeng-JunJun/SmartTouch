#pragma once

/* ʹ�÷���:
	��ʹ��ʱ������������ָ��
*/

#include "PointEx.h"
#include <math.h>

class AFX_EXT_CLASS CRectEx
{
public:
	CRectEx(void);
	CRectEx(double dLeft, double dTop, double dRight, double dBottom);
	CRectEx(CPointEx ptTopLeft, CPointEx ptBottomRight);
	CRectEx(CPoint ptTopLeft, CPoint ptBottomRight);

	~CRectEx(void);

	double left;
	double top;
	double right;
	double bottom;

	double m_dAngle;
	CPointEx m_ptTopRight;
	CPointEx m_ptLeftBottom;

	AFX_INLINE CPointEx &TopLeft(void);		// ���Ͻ�
	AFX_INLINE CPointEx BottomLeft(void);	// ���½�
	AFX_INLINE CPointEx TopRight(void);		// ���Ͻ�
	AFX_INLINE CPointEx &BottomRight(void);	// ���½�

	AFX_INLINE CPointEx CenterPoint(void);	// ��������

	AFX_INLINE double	Width(void);			// ���
	AFX_INLINE LONG		IntWidth(void);			// �������
	AFX_INLINE double	HalfWidth(void);		// 1/2 ���
	AFX_INLINE LONG		IntHalfWidth(void);		// ���� 1/2 ���
	AFX_INLINE double	Height(void);			// �߶�
	AFX_INLINE LONG		IntHeight(void);		// �����߶�
	AFX_INLINE double	HalfHeight(void);		// 1/2 ���
	AFX_INLINE LONG		IntHalfHeight(void);	// ���� 1/2 �߶�
	AFX_INLINE double	CrossDistance(void);	// �Խ��߳���
	AFX_INLINE LONG		IntCrossDistance(void);	// �����Խ��߳���

	AFX_INLINE CRect	Convert2Crect(void);	// ת����Crect

	// ���Ƿ��ھ�����
	template <typename T>
	BOOL PtInRect(T pt)
	{
		return left <= pt.x && right >= pt.x && top <= pt.y && bottom >= pt.y;
	}

	// ƫ��
	template <typename T>
	void OffsetRect(T pt)
	{
		left	+= pt.x;
		right	+= pt.x;
		top		+= pt.y;
		bottom	+= pt.y;
	}

	// ƫ��
	template <typename T>
	void OffsetRect(T x, T y)
	{
		left	+= x;
		right	+= x;
		top		+= y;
		bottom	+= y;
	}

	AFX_INLINE void SetRectEmpty();

	AFX_INLINE LONG IntLeft(void);			// ��������
	AFX_INLINE LONG IntTop(void);			// ��������
	AFX_INLINE LONG IntRight(void);			// ��������
	AFX_INLINE LONG IntBottom(void);		// ��������
	AFX_INLINE CRectEx NormalizeRect(void);	// ��һ��
	AFX_INLINE BOOL IsRectEmpty(void);		// �����Ƿ�Ϊ��
	AFX_INLINE void Rotation(CPointEx ptCenter, double dAngle);	// ��ת

	// ���ز����� =
	AFX_INLINE void operator = (const CRectEx & rcect);
	AFX_INLINE void operator = (const CRect & rcect);

	AFX_INLINE BOOL operator == (const CRectEx & rcect);
	AFX_INLINE BOOL operator != (const CRectEx & rcect);
};

