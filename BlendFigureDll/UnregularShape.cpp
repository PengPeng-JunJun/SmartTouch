#include "stdafx.h"
#include "UnregularShape.h"

#define APP_FONT	_T("������")

CUnregularShape::CUnregularShape(void)
{
}


CUnregularShape::~CUnregularShape(void)
{
}


void CUnregularShape::SerializeEx(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		const size_t nSize = m_vOutline.size();

		ar << nSize;

		for (size_t i = 0; i < nSize; i++)
		{
			ar << m_vOutline[i].x;
			ar << m_vOutline[i].y;

			ar << m_vBkup[i].x;
			ar << m_vBkup[i].y;
		}

		ar << m_rcBkup;
	}
	else
	{	// loading code
		size_t nSize = 0;

		ar >> nSize;
		m_vOutline.resize(nSize);
		m_vBkup.resize(nSize);

		for (size_t i = 0; i < nSize; i++)
		{
			ar >> m_vOutline[i].x;
			ar >> m_vOutline[i].y;

			ar >> m_vBkup[i].x;
			ar >> m_vBkup[i].y;
		}

		ar >> m_rcBkup;
	}
}


// ��ʼ���߿�
void CUnregularShape::StartDrawing(CWnd * pOwner)
{
	m_bDrawing		= TRUE;			// ��ǻ��߿����
	m_bLButtonDown	= FALSE;		// ������Ϊδ����
	m_bShow			= FALSE;		// ��ʾ

	m_pOwner		= pOwner;		// ��¼CWndָ��

	ASSERT(nullptr != m_pOwner);

	m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_START_DRAWING, (LPARAM)this);
	m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_DOT);	// ����ʮ���ι��
}


// ����������������
BOOL CUnregularShape::LButtonDown(UINT nFlags, CPoint point)
{
// 	if (nullptr != m_pOwner)
// 	{
// 		return FALSE;
// 	}

	// �������Ϊ����״̬�򷵻�FALSE

	if (m_bLock && !m_bDrawing)
	{
		return FALSE;
	}

	if (m_bDrawing)
	{
		m_bShow = TRUE;
	}
	else if (!m_bShow)
	{
		return FALSE;
	}

	m_ptCursor	= point;
	m_ptDown	= point;

	m_bResizing	= FALSE;
	m_bMoving	= FALSE;

	// ������ڻ��߿�
	if (m_bDrawing)		
	{
		m_vOutline.clear();
		m_vOutline.push_back(point);

		m_rcFrame.TopLeft()		= point;		// ��Ǳ߿�����
		m_rcFrame.BottomRight()	= point;

		for (int i = 0; i < RECT_ANCHOR_SUM; i++)
		{
			m_rcAnchor[i].SetRectEmpty();
		}
	}
	else
	{
		m_nCurAnchor = -1;

		for (int i = 0; i < RECT_ANCHOR_SUM; i++)
		{
			// ���λ���Ƿ���ê����
			if (m_rcAnchor[i].PtInRect(m_ptCursor))
			{
				m_bResizing = TRUE;
				m_nCurAnchor = i;

				goto LABEL_END;
			}
		}

		if (PtInRect(point))
		{
			m_bSelect = TRUE;
			m_bMoving = TRUE;
		}
		else
		{
			m_bSelect = FALSE;
		}
	}

LABEL_END:

	m_bLButtonDown = m_bDrawing || m_bResizing || m_bMoving;

	return m_bLButtonDown;
}


// �������������ͷ�
BOOL CUnregularShape::LButtonUp(UINT nFlags, CPoint point)
{
// 	if (nullptr != m_pOwner)
// 	{
// 		return FALSE;
// 	}

	// �������Ϊ����״̬�򷵻�	

	if (!m_bShow || !m_bLButtonDown)
	{
		return FALSE;
	}

	// ��ǵ��λ�ú͵���λ���Ƿ���ͬ
	const BOOL bChange = m_ptDown != point;

	if (bChange)
	{
		// ������ڻ��߿�
		if (m_bDrawing)
		{
			m_bDrawing = FALSE;					// ȡ�����߿���, ��ʾ��ͼ���

			m_vOutline.push_back(m_vOutline[0]);
			
			_GetFrameRect();
			SetAnchorPos();

			m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_END_DRAWING, (LPARAM)this);
			m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_ARROW);

			goto LABEL_END;
		}
		else if (m_bResizing)
		{
			m_bResizing = FALSE;
			m_nCurAnchor = -1;

			m_rcFrame.NormalizeRect();

			m_rcBkup = m_rcFrame;
			m_vBkup = m_vOutline;

			SetAnchorPos();
		}
		else if (m_bMoving)
		{
			m_bMoving = FALSE;

			_MoveTo(point);		// �ƶ�����괦
		}

		m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_ARROW);		// ���ü�ͷ���
		m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_FILE_DIRTY, (LPARAM)this);		// ����޸ĵ���
	}
	else if (m_vOutline.size() < 1)
	{
		SetEmpty();
	}
	
LABEL_END:

	m_bLButtonDown	= FALSE;		// �ͷ����
	m_ptCursor		= point;		// ������λ��

	return bChange;
}


// ����������ƶ�
BOOL CUnregularShape::MouseMove(UINT nFlags, CPoint point)
{
// 	if (nullptr != m_pOwner)
// 	{
// 		return FALSE;
// 	}

	// �������Ϊ����״̬�򷵻�
	if ((!m_bShow || m_bLock) && !m_bDrawing)
	{
		return FALSE;
	}

	BOOL bHover = FALSE;

	// ������������
	if (m_bLButtonDown)
	{
		// ������ڻ��߿�
		if (m_bDrawing)
		{
			m_bChanged = TRUE;
			m_vOutline.push_back(point);
		}
		else if (m_bResizing)
		{
			m_bChanged = TRUE;

			for (int i = 0; i < RECT_ANCHOR_SUM; i++)
			{
				m_rcAnchor[i].SetRectEmpty();
			}

			m_rcAnchor[m_nCurAnchor].TopLeft()		= CPoint(point.x - ANCHOR_WID, point.y - ANCHOR_WID);
			m_rcAnchor[m_nCurAnchor].BottomRight()	= CPoint(point.x + ANCHOR_WID, point.y + ANCHOR_WID);

			switch (m_nCurAnchor)
			{
			case 0:
				m_rcFrame.TopLeft() = point;
				break;

			case 1:
				m_rcFrame.left = point.x;
				break;

			case 2:
				m_rcFrame.left = point.x;
				m_rcFrame.bottom = point.y;
				break;

			case 3:
				m_rcFrame.bottom = point.y;
				break;

			case 4:
				m_rcFrame.BottomRight() = point;
				break;

			case 5:
				m_rcFrame.right = point.x;
				break;

			case 6:
				m_rcFrame.right = point.x;
				m_rcFrame.top = point.y;
				break;

			case 7:
				m_rcFrame.top = point.y;
				break;

			default:
				break;
			}

			const CPointEx ptBase = m_rcFrame.TopLeft();

			const int nSize = m_vOutline.size();

			for (int i = 0; i < nSize; i++)
			{
				const CPointEx &ptSrc = m_vBkup[i];
				CPointEx &ptDst = m_vOutline[i];

				const double dScaleX = (ptSrc.x - m_rcBkup.left) / m_rcBkup.Width();
				ptDst.x = ptBase.x + m_rcFrame.Width() * dScaleX;

				const double dScaleY = (ptSrc.y - m_rcBkup.top) / m_rcBkup.Height();
				ptDst.y = ptBase.y + m_rcFrame.Height() * dScaleY;
			}
		}
		else
		{
			_MoveTo(point);	// �ƶ�����괦
		}
	}
	else
	{
		if (m_rcAnchor[0].PtInRect(point) || m_rcAnchor[4].PtInRect(point))
		{
			bHover = TRUE;
			m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_SIZE_NWSE);
		}
		else if (m_rcAnchor[1].PtInRect(point) || m_rcAnchor[5].PtInRect(point))
		{
			bHover = TRUE;
			m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_SIZE_WE);
		}
		else if (m_rcAnchor[2].PtInRect(point) || m_rcAnchor[6].PtInRect(point))
		{
			bHover = TRUE;
			m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_SIZE_NESW);
		}
		else if (m_rcAnchor[3].PtInRect(point) || m_rcAnchor[7].PtInRect(point))
		{
			bHover = TRUE;
			m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_SIZE_NS);
		}
		else
		{
			if (nullptr != m_pOwner)
			{
				m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_ARROW);
			}
		}
	}	

	m_ptCursor = point;	// ����������

	return m_bLButtonDown || bHover;
}


// ��DC�л�����
void CUnregularShape::Draw(CDC * pDC)
{
	if (!m_bShow)
	{
		return;
	}

	CRect rcTemp = m_rcFrame;
	rcTemp.NormalizeRect();

	CPen penSelect;

	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(255 - GetRValue(m_rgbFrame), 255 - GetGValue(m_rgbFrame), 255 - GetBValue(m_rgbFrame));

	DWORD dwFigure[4];
	dwFigure[0] = m_nLineWidth;
	dwFigure[1] = m_nLineWidth << 1;
	dwFigure[2] = m_nLineWidth;
	dwFigure[3] = m_nLineWidth << 1;

	if (1 == m_nLineWidth)
	{
		penSelect.CreatePen(PS_DOT, m_nLineWidth, logBrush.lbColor);
	}
	else
	{
		penSelect.CreatePen(PS_USERSTYLE | PS_DOT | PS_GEOMETRIC | PS_ENDCAP_SQUARE,
			m_nLineWidth, &logBrush, 4, dwFigure);
	}

	CPen penFrame(PS_SOLID, m_nLineWidth, logBrush.lbColor);

	pDC->SelectObject(m_bSelect? penSelect: penFrame);
	pDC->SelectStockObject(NULL_BRUSH);

	pDC->SetBkMode(TRANSPARENT);
	pDC->Rectangle(rcTemp);

	CPen penOutline(PS_SOLID, m_nLineWidth, m_rgbFrame);
	pDC->SelectObject(penOutline);

	pDC->MoveTo(m_vOutline[0].Convert2CPoint());

	const size_t nSize = m_vOutline.size();

	for (size_t i = 0; i < nSize; i++)
	{
		pDC->LineTo(m_vOutline[i].Convert2CPoint());
	}

	if (!m_bLock)
	{
		CPen penAnchor(PS_SOLID, 1, m_rgbAnchor);
		pDC->SelectObject(penAnchor);

		for (int i = 0; i < RECT_ANCHOR_SUM; i++)
		{
			if (m_bSelect)
			{
				pDC->FillSolidRect(m_rcAnchor[i], m_rgbAnchor);
			}
			else
			{
				pDC->Rectangle(m_rcAnchor[i]);
			}
		}
	}

	if (m_bShowTitle && !m_strTitle.IsEmpty() && !m_bDrawing)
	{
		CFont Font;
		Font.CreatePointFont(100, APP_FONT, nullptr);
		pDC->SelectObject(&Font);

		const CSize szText = pDC->GetTextExtent(m_strTitle);

		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkColor(m_rgbFrame);

		CRect rcText(rcTemp.left, rcTemp.top - 24, rcTemp.left + szText.cx + 4, rcTemp.top - 24 + szText.cy + 4);
		pDC->FillSolidRect(rcText, m_rgbFrame);
		pDC->DrawText(m_strTitle, rcText, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	}
}


// ��վ���
void CUnregularShape::SetEmpty(void)
{
	m_bShow = FALSE;

	m_rcFrame.SetRectEmpty();
	m_vOutline.clear();
}

// �ƶ�
AFX_INLINE void CUnregularShape::Offset(CPoint ptOffset)
{
	m_rcFrame.OffsetRect(ptOffset);

	SetAnchorPos();

	const int nSize = m_vOutline.size();

	for (int i = 0; i < nSize; i++)
	{
		m_vOutline[i] += (ptOffset);
	}
}


AFX_INLINE void CUnregularShape::operator = (const CUnregularShape & rect)
{
	m_nIndex		= rect.m_nIndex;
	m_strTitle		= rect.m_strTitle;
	m_bDrawing		= rect.m_bDrawing;
	m_bLButtonDown	= rect.m_bLButtonDown;
	m_bLock			= rect.m_bLock;
	m_bShow			= rect.m_bLock;
	m_bSelect		= rect.m_bSelect;
	m_bResizing		= rect.m_bResizing;
	m_bMoving		= rect.m_bMoving;
	m_rcFrame		= rect.m_rcFrame;

	m_nLineWidth	= rect.m_nLineWidth;
	m_rgbFrame		= rect.m_rgbFrame;
	m_rgbAnchor		= rect.m_rgbAnchor;

	for (int i = 0; i < RECT_ANCHOR_SUM; i++)
	{
		m_rcAnchor[i] = rect.m_rcAnchor[i];
	}

	m_vOutline = rect.m_vOutline;
	m_vBkup = m_vOutline;
}


AFX_INLINE BOOL CUnregularShape::operator == (const CUnregularShape & rect)
{
	if (m_rcFrame != rect.m_rcFrame)
	{
		return FALSE;
	}

	for (int i = 0; i < RECT_ANCHOR_SUM; i++)
	{
		if (m_rcAnchor[i] != rect.m_rcAnchor[i])
		{
			return FALSE;
		}
	}

	if (m_vOutline.size() != rect.m_vOutline.size())
	{
		return FALSE;
	}

	const int nSize = m_vOutline.size();

	for (int i = 0; i < nSize; i++)
	{
		if (m_vOutline[i] != rect.m_vOutline[i])
		{
			return FALSE;
		}
	}

	return TRUE;
}


AFX_INLINE BOOL CUnregularShape::operator != (const CUnregularShape & rect)
{
	if (m_rcFrame != rect.m_rcFrame)
	{
		return TRUE;
	}

	for (int i = 0; i < RECT_ANCHOR_SUM; i++)
	{
		if (m_rcAnchor[i] != rect.m_rcAnchor[i])
		{
			return TRUE;
		}
	}

	if (m_vOutline.size() != rect.m_vOutline.size())
	{
		return TRUE;
	}

	const int nSize = m_vOutline.size();

	for (int i = 0; i < nSize; i++)
	{
		if (m_vOutline[i] != rect.m_vOutline[i])
		{
			return TRUE;
		}
	}

	return FALSE;
}


AFX_INLINE void CUnregularShape::_GetFrameRect(void)
{
	double dLeft	= MAXINT;
	double dRight	= -MAXINT;
	double dTop		= MAXINT;
	double dBottom	= -MAXINT;

	const int nSize = m_vOutline.size();

	for (int i = 0; i < nSize; i++)
	{
		const CPointEx &pt = m_vOutline[i];

		if (pt.x < dLeft)
		{
			dLeft = pt.x;
		}

		if (pt.x > dRight)
		{
			dRight = pt.x;
		}

		if (pt.y < dTop)
		{
			dTop = pt.y;
		}

		if (pt.y > dBottom)
		{
			dBottom = pt.y;
		}
	}

	m_rcFrame.left		= (int)dLeft;
	m_rcFrame.right		= (int)dRight + 1;
	m_rcFrame.top		= (int)dTop;
	m_rcFrame.bottom	= (int)dBottom + 1;

	m_rcBkup = m_rcFrame;
	m_vBkup = m_vOutline;
}


// �ƶ���Ŀ���
AFX_INLINE void CUnregularShape::_MoveTo(CPoint ptDst)
{
	m_pOwner->PostMessage(gMsgBlendFigure, FIGURE_MSG_SET_CURSOR, FIGURE_CURSOR_SIZE_ALL);

	CPoint ptOfst = ptDst - m_ptCursor;

	m_rcFrame.OffsetRect(ptOfst);
	SetAnchorPos();

	const int nSize = m_vOutline.size();

	for (int i = 0; i < nSize; i++)
	{
		m_vOutline[i] += (ptOfst);
	}

	SetAnchorPos();
}
