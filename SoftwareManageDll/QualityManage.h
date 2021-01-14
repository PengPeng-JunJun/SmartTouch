#pragma once
#include "resource.h"

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CQualityManage �Ի���
#include <deque>
#include <queue>
using namespace std;

struct QualityInfo
{
	int nGroup;
	int nProject;
	CString strName;
	deque<CString> dqstrInfo;
};

class AFX_EXT_CLASS CQualityManage : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CQualityManage)

public:
	CQualityManage(CWnd* pParent = NULL);   // ��׼���캯��
	CQualityManage(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CQualityManage();

// �Ի�������
	enum { IDD = IDD_QUALITYMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CBL_List m_BL_ltQualityManage;

	deque<QualityInfo> m_dqQualityInfo;

	void _ShowInfo();
};
