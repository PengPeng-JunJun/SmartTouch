#pragma once

/* ʹ�÷���:
	��ʹ��ʱ������������ָ��
*/


#ifndef ZERO					// 0
#define ZERO					0.0000001
#endif

#ifndef FORTHINT				// ������������
#define FORTHINT				0.5
#endif

class AFX_EXT_CLASS CPointEx
{
public:
	CPointEx(void);
	CPointEx(double dx, double dy);
	CPointEx(CPoint pt);
	~CPointEx(void);

	double x;
	double y;

	/*================================================================
	����: ת����CPoint���
	�������: ��
	����ֵ: CPoint���
	================================================================*/
	CPoint Convert2CPoint(void);

	/*================================================================
	����: ��ָ������ת
	�������:
		1. ptCenter: ��ת����
		2. dDegree: ��ת�Ƕ�
	����ֵ: ��ת������
	================================================================*/
	CPointEx Rotation(CPointEx ptCenter, double dDegree);

	AFX_INLINE void operator = (const CPoint & ptCPoint);
	AFX_INLINE void operator = (const CPointEx & ptCPoint);
	AFX_INLINE BOOL operator == (const CPointEx & ptCPoint);
	AFX_INLINE BOOL operator != (const CPointEx & ptCPoint);

	AFX_INLINE CPointEx operator + (const CPointEx & ptCPoint);
	AFX_INLINE CPointEx operator += (const CPointEx & ptCPoint);
	AFX_INLINE CPointEx operator - (const CPointEx & ptCPoint);
	AFX_INLINE CPointEx operator -= (const CPointEx & ptCPoint);
};
