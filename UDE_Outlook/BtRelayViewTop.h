#pragma once
#include <gdiplus.h>
#include "..\BlendFigureDll\FigureBase.h"

// CBtRelayViewTop �Ի���
#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendFigureDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendFigureDll.lib")
#endif

#include<vector>
#include <math.h>
// CViewTop �Ի���
using namespace std;

class CBtRelayViewTop : public CFigureBase
{
	DECLARE_DYNAMIC(CBtRelayViewTop)

public:
	CBtRelayViewTop(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBtRelayViewTop();

// �Ի�������
	enum { IDD = IDD_BTRELAYVIEWTOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
