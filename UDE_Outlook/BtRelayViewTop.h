#pragma once
#include <gdiplus.h>
#include "..\BlendFigureDll\FigureBase.h"

// CBtRelayViewTop 对话框
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendFigureDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendFigureDll.lib")
#endif

#include<vector>
#include <math.h>
// CViewTop 对话框
using namespace std;

class CBtRelayViewTop : public CFigureBase
{
	DECLARE_DYNAMIC(CBtRelayViewTop)

public:
	CBtRelayViewTop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBtRelayViewTop();

// 对话框数据
	enum { IDD = IDD_BTRELAYVIEWTOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
