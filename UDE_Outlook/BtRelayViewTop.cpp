// BtRelayViewTop.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "BtRelayViewTop.h"
#include "afxdialogex.h"


// CBtRelayViewTop 对话框

IMPLEMENT_DYNAMIC(CBtRelayViewTop, CFigureBase)

CBtRelayViewTop::CBtRelayViewTop(CWnd* pParent /*=NULL*/)
	: CFigureBase(CBtRelayViewTop::IDD, pParent)
{

}

CBtRelayViewTop::~CBtRelayViewTop()
{
}

void CBtRelayViewTop::DoDataExchange(CDataExchange* pDX)
{
	CFigureBase::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBtRelayViewTop, CFigureBase)
END_MESSAGE_MAP()


// CBtRelayViewTop 消息处理程序
