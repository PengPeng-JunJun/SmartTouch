#pragma once

#include "Blender.h"
#include "MsgLayer.h"

class AFX_EXT_CLASS CMsgBox
{
public:
	CMsgBox(CWnd * pParent)
	{
		m_pParent = pParent;
	}

	~CMsgBox(void)
	{
	}

public:
	INT_PTR ShowMsg(const CString & strMsg, const CString & strWnd, UINT unStyle)
	{
		m_MsgBox.CreateBlendWnd(m_pParent);

		m_MsgBox->m_unStyle = unStyle;
		m_MsgBox->m_strMsg = strMsg;

		m_MsgBox.CreateTopWnd(strWnd, TRUE);

		return m_MsgBox->m_nRetVal;
	}

	INT_PTR ShowMsg(const CString & strMsg, const CString * pstrWnd, UINT unStyle)
	{
		return ShowMsg(strMsg, nullptr == pstrWnd? AfxGetAppName(): *pstrWnd, unStyle);
	}

	INT_PTR ShowMsg(const CString * pstrMsg, const CString & strWnd, UINT unStyle)
	{
		return ShowMsg(*pstrMsg, strWnd, unStyle);
	}

	INT_PTR ShowMsg(const CString * pstrMsg, const CString * pstrWnd, UINT unStyle)
	{
		return ShowMsg(*pstrMsg, nullptr == pstrWnd? AfxGetAppName(): *pstrWnd, unStyle);
	}

protected:
	CWnd *m_pParent;
	CBlender<CMsgLayer> m_MsgBox;
};

