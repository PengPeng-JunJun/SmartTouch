
// UDE_Outlook.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDE_OutlookApp:
// �йش����ʵ�֣������ UDE_Outlook.cpp
//

class CUDE_OutlookApp : public CWinApp
{
public:
	CUDE_OutlookApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUDE_OutlookApp theApp;