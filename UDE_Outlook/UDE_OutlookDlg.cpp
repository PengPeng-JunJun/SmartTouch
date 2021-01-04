
// UDE_OutlookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "UDE_OutlookDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUDE_OutlookDlg 对话框



CUDE_OutlookDlg::CUDE_OutlookDlg(CWnd* pParent /*=NULL*/)
	: CAppBase(CUDE_OutlookDlg::IDD, pParent)
	, m_nRunStyle(0)
	, m_nCollectCounter_Main(0)
	, m_nCollectCounter_Slave(-1)
	, m_strFilePath(_T(""))
	, m_nCommend(0)
    , m_nStationNO(0)
	, m_nStationAddress(0)
	, m_bIfExcel(FALSE)
	, m_bOpenFile(FALSE)
	, m_nHistoryPathCounter(0)
	, m_nInit(FALSE)
	, m_bAutoRun(FALSE)
	, m_bMin2Tray(FALSE)
	, m_bShowDlg(FALSE)
	, m_bItemFinish(TRUE)
	, m_bAutoFindFile(FALSE)
	, m_bIsBalloonTipShow(FALSE)
	, m_bReceive(FALSE)
	, m_bCommuncating(FALSE)
	, m_bInterruptRead(FALSE)
	, m_nCommunicationMode(3)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pControllerDlg.resize(247);
	m_nReceiveData.clear();
	m_strCollectStatus.clear();
	m_strCollectStatus.push_back(_T("軟體運行中"));
	m_strCollectStatus.push_back(_T("軟體運行中."));
	m_strCollectStatus.push_back(_T("軟體運行中. ."));
	m_strCollectStatus.push_back(_T("軟體運行中. . ."));
	m_strCollectStatus.push_back(_T("軟體運行中. . . ."));
	m_strCollectStatus.push_back(_T("軟體運行中. . . . ."));

	m_nvMsg.clear();
	m_nvWriteMsg.clear();
	m_bvConnecting.clear();
}

void CUDE_OutlookDlg::DoDataExchange(CDataExchange* pDX)
{
	CAppBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_MainMenu,m_BL_MainMenu);
	DDX_Control(pDX, IDC_BL_ReportMainList, m_BL_ReportMainList);
	DDX_Control(pDX, IDC_BL_Collect, m_BL_Collect);
	DDX_Control(pDX, IDC_BL_CollectStatus, m_BL_CollectStatus);
	DDX_Control(pDX, IDC_BL_ReportLimit, m_BL_ReportLimit);
	DDX_Control(pDX, IDC_BL_DateReport, m_BL_DateReport);
	DDX_Control(pDX, IDC_BL_MouthReport, m_BL_MouthReport);
}

BEGIN_MESSAGE_MAP(CUDE_OutlookDlg, CAppBase)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_WM_CLOSE()
ON_WM_CLOSE()
ON_REGISTERED_MESSAGE(gMsgSerialReceiveChar, &CUDE_OutlookDlg::OnGmsgserialreceivechar)
ON_WM_TIMER()
ON_MESSAGE(WM_REGISTER, &CUDE_OutlookDlg::OnGetRegisterMsg)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_MESSAGE(WM_SHOWTASK, OnShowTask)
ON_REGISTERED_MESSAGE(gMsgMinWindow, &CUDE_OutlookDlg::OnGmsgminwindow)
ON_MESSAGE(WM_DELETFILE, &CUDE_OutlookDlg::OnDeletFlie)
ON_MESSAGE(WM_COLLECTRUN, &CUDE_OutlookDlg::OnCollectRun)
ON_MESSAGE(WM_STOPCOLLECT, &CUDE_OutlookDlg::OnStopcollect)
ON_MESSAGE(WM_STARTCOLLECT, &CUDE_OutlookDlg::OnStartcollect)
ON_MESSAGE(WM_WRITE_DATA, &CUDE_OutlookDlg::OnWriteData)
END_MESSAGE_MAP()


// CUDE_OutlookDlg 消息处理程序

BOOL CUDE_OutlookDlg::OnInitDialog()
{
	CAppBase::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

// 
	//設置托盤圖標等信息，

	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	char cstr[128] = "UDE_SmartTouch"; 
	for(int i = 0;i<=128;++i)
	{
		m_nid.szTip[i] = cstr[i];
	}
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
	//
	// TODO: 在此添加额外的初始化代码

	double dTime = 100;
	double dCounter = 200;
	double dInfo = 300;
	
	SetTitle(_T("UDE SMART TOUCH"));

	LoadHistoryPath();//加載路徑

	InitMainWindow();

	CreateChildWindow();

	SearchConfigurationFile();//创建CRC校验文件文件夹

	SearchControllerFile();//创建设备文件的文件夹

	SearchReportFile();//创建报表文件夹

	SearchTemplateFile();//創建EXCEL模板文件夾

	m_BL_ReportMainList.ShowWindow(SW_HIDE);
	m_BL_Collect.ShowWindow(SW_HIDE);
	m_BL_CollectStatus.ShowWindow(SW_HIDE);


	m_Register->CheckRegisterList(CHECKREGISTERLIST);

	m_BtBaseOk.ShowWindow(FALSE);
	m_BtBaseCancel.ShowWindow(FALSE);

	m_nCollectCounter_Main = 0;
	m_nCollectCounter_Slave = -1;

	SetTimer(4, 0, NULL);//啟動間斷收集Timmer，每個1MS掃描一次消息向量

	
	m_BL_ReportMainList.SetReadOnly(m_swBaseLock.GetStatus());
	
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUDE_OutlookDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CAppBase::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUDE_OutlookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (!m_bShowDlg)
		{
			this->ShowWindow(SW_HIDE);   
		}
		  
		CAppBase::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUDE_OutlookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CUDE_OutlookDlg::PreInitDialog()
{
	// TODO: 在此添加专用代码和/或调用基类
	_RegisterActivex(TRUE);
	CAppBase::PreInitDialog();
}

BOOL CUDE_OutlookDlg::_RegisterActivex(BOOL bRegister)
{

#define AX_CTRL_SUM		12

	const CString strDllName[] =
	{
		_T("BL_CheckBox.ocx"),
		_T("BL_DropDown.ocx"),
		_T("BL_Edit.ocx"),
		_T("BL_Button.ocx"),
		_T("BL_IPAdd.ocx"),
		_T("BL_Line.ocx"),
		_T("BL_List.ocx"),
		_T("BL_Radio.ocx"),
		_T("BL_Switch.ocx"),	
		_T("BL_Menu.ocx"),
		_T("BL_Slider.ocx"),
		_T("BL_VScroll.ocx")
	};

	for (int nCunter = 0; nCunter < AX_CTRL_SUM; nCunter++)
	{
		const CString &strDll = strDllName[nCunter];

		HINSTANCE hLib = LoadLibrary(strDll);

		if (hLib < (HINSTANCE)HINSTANCE_ERROR)
		{
			CString strInfo = _T("載入") + strDll;
			strInfo += _T(" 失敗！\n情監測當前目錄是否存在該文件。");

// 			CMsgWnd MsgBox;
// 			MsgBox.ShowMsg(strInfo, nullptr, MB_OK | MB_ICONERROR);

			return FALSE;
		}

		// 获取注册函数DllRegisterServer地址
		FARPROC lpDllEntryPoint;
		lpDllEntryPoint = GetProcAddress(hLib, bRegister? "DllRegisterServer": "DllUnregisterServer");

		// 调用注册函数DllRegisterServer
		if(nullptr != lpDllEntryPoint)
		{ 
			if (FAILED((*lpDllEntryPoint)()))
			{
				CString strInfo = _T("調用") + strDll;

				if (bRegister)
				{
					strInfo += _T(" DllRegisterServer 失敗！\n請確認是否為管理員權限。");
				}
				else
				{
					strInfo += _T(" DllUnregisterServer 失敗！\n請確認是否為管理員權限。");
				}

// 				CMsgWnd MsgBox;
// 				MsgBox.ShowMsg(strInfo, nullptr, MB_OK | MB_ICONERROR);
				FreeLibrary(hLib);

				return FALSE;
			}
		}
		else
		{
			CString strInfo = _T("調用") + strDll;

			if (bRegister)
			{
				strInfo += _T(" DllRegisterServer 失敗！\n請確認是否為管理員權限。");
			}
			else
			{
				strInfo += _T(" DllUnregisterServer 失敗！\n請確認是否為管理員權限。");
			}

// 			CMsgWnd MsgBox;
// 			MsgBox.ShowMsg(strInfo, nullptr, MB_OK | MB_ICONERROR);
			FreeLibrary(hLib);

			return FALSE;
		}
	}

	return TRUE;
}

void CUDE_OutlookDlg::LockCtrls(int nLock)
{
	const BOOL bLocked = _GetLockState(nLock, PSD_LEVEL_TE);//是否为技术员权限

	m_BL_ReportMainList.SetReadOnly(bLocked);

	for (int i = 0; i < m_BL_ReportMainList.GetRows(); i++)
	{
		(*m_pControllerDlg[i])->m_bLocked = bLocked;
		(*m_pControllerDlg[i])->PostMessage(WM_LOCK_STATE, bLocked);
	}
}

LRESULT CUDE_OutlookDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
	return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单                    
// 			LPPOINT lpoint = new tagPOINT;
// 			::GetCursorPos(lpoint);                    // 得到鼠标位置
// 			CMenu menu;
// 			menu.CreatePopupMenu();                    // 声明一个弹出式菜单
// 			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));
// 			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
// 			HMENU hmenu = menu.Detach();
// 			menu.DestroyMenu();
// 			delete lpoint;
		break;

	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
		m_bShowDlg = TRUE;
		this->ShowWindow(SW_SHOW);         // 显示主窗口
		break;
	}
	return 0;

}

void CUDE_OutlookDlg::InitMainWindow()
{
	//=========   如下代码用于在最大化显示窗口，但不遮挡任务栏  ===========//
	// 		CRect rcClient;
	// 		SystemParametersInfo(SPI_GETWORKAREA, 0, &rcClient, 0);
	// 		MoveWindow(rcClient);

	AdjustMenuPos(&m_BL_MainMenu);

	CRect rcMenu;
	m_BL_MainMenu.GetWindowRect(rcMenu);
	ScreenToClient(&rcMenu);
	rcMenu.right += 80;
	m_BL_MainMenu.MoveWindow(rcMenu);

	CRect rcLock;
	m_swBaseLock.GetWindowRect(rcLock);
	rcLock.left -= 202;
	rcLock.right -= 160;
	ScreenToClient(&rcLock);
	m_swBaseLock.MoveWindow(rcLock);

	m_swBaseLock.SetStatus(TRUE);

	CRect rcMin;
	m_BtBaseMin.GetWindowRect(rcMin);
	rcMin.left -= 60;
	rcMin.right -= 60;
	ScreenToClient(&rcMin);
	m_BtBaseMin.MoveWindow(rcMin);

	SetMainMenu();
}

void CUDE_OutlookDlg::SetMainMenu()
{
	CString strHistoryPath = _T("");
	m_BL_MainMenu.AddPopByPosPosPos(0, 0, 0, 0, _T("文件"), _T("新建...@Ctrl+N;打開...@Ctrl+O;保存...@Ctrl+S;另存為...@Ctrl+Shift+S;最近開啟檔案...;退出...@Ctrl+Q"));
	
	if (m_strHistoryPath.size() == 0)
	{
		m_BL_MainMenu.AddPopByPosPosPos(1, 0, 4, 0,_T("最近開啟檔案"), _T("--(空)--"));
		m_BL_MainMenu.EnableItemByName(_T("最近開啟檔案"), _T("--(空)--"), FALSE);
	}
	else
	{
		for (UINT nCounter = 0; nCounter < m_strHistoryPath.size(); nCounter++)
		{
			strHistoryPath.Append(m_strHistoryPath[nCounter]);
			if (nCounter != m_strHistoryPath.size() - 1)
			{
				strHistoryPath.Append(_T(";"));
			}
			m_BL_MainMenu.EnableItemByPos(_T("最近開啟檔案"), nCounter, TRUE);
		}
		m_BL_MainMenu.AddPopByPosPosPos(1, 0, 4, 0,_T("最近開啟檔案"), strHistoryPath);
	}

	m_BL_MainMenu.AddPopByPosPosPos(0, 1, 0, 0, _T("設置"), _T("串口設置...;CRC循環冗餘校驗...;添加設備...;開機啟動...;最小化到托盤...;自動加載檔案..."));
	
	m_BL_MainMenu.AddPopByPosPosPos(0, 2, 0, 0, _T("幫助"), _T("關於 SmartTouch...;軟體註冊..."));

	if (!m_nInit)
	{
		m_BL_MainMenu.EnableItemByName(_T("文件"), _T("保存"), FALSE);
		m_BL_MainMenu.EnableItemByName(_T("文件"), _T("另存為"), FALSE);
		m_nInit = TRUE;
	}
	m_BL_MainMenu.CheckItemByPos(_T("設置"), 3, m_bAutoRun);
	m_BL_MainMenu.CheckItemByPos(_T("設置"), 4, m_bMin2Tray);
	m_BL_MainMenu.CheckItemByPos(_T("設置"), 5, m_bAutoFindFile);
}

void CUDE_OutlookDlg::CreateChildWindow()
{
	m_MsgInfoDlg.CreateBlendWnd(IDD_MSGINFODLG, this);
	m_MsgInfoDlg.CreateTopWnd(FALSE, FALSE);

	m_Port.CreateBlendWnd(this);
	m_Port.CreateTopWnd(FALSE, FALSE);
	m_Port.Init(0);

	m_CRC.CreateBlendWnd(this);
	m_CRC.CreateTopWnd(FALSE, FALSE);

	m_ControllerAddDlg.CreateBlendWnd(IDD_CONTROLLERADDDLG, this);
	m_ControllerAddDlg.CreateTopWnd(FALSE, FALSE);
	m_ControllerAddDlg->m_pMsgCtrlAddDlg = this;

	m_Register.CreateBlendWnd(IDD_REGISTERDLG, this);
	m_Register.CreateTopWnd(FALSE, FALSE);
	m_Register->m_pRegister = this;
	
	m_SoftwareInfoDlg.CreateBlendWnd(IDD_SOFTWAREINFODLG, this);
	m_SoftwareInfoDlg.CreateTopWnd(FALSE, FALSE);
}

CString CUDE_OutlookDlg:: GetExePath(void)  
{  
	CString strExePath;  
	GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);  
	strExePath.ReleaseBuffer();  
	strExePath = strExePath.Left(strExePath.ReverseFind(_T('\\')));  
	return strExePath;  
}  

void CUDE_OutlookDlg::SearchConfigurationFile()
{
	CMsgBox MsgBox(this);
	if (!m_CRC.SearchConfigurationFile())
	{
		MsgBox.ShowMsg(_T("未找到CRC配置文件!"),_T("查找失敗"), MB_YESNO | MB_ICONQUESTION);  
		m_BL_MainMenu.EnableItemByName(_T("設置"), _T("循環冗餘校驗"), FALSE);
	}
}


void CUDE_OutlookDlg::SearchControllerFile()
{
	CMsgBox MsgBox(this);
	//判断路径是否存在   
	if (!m_FindCtrlFile.SearchControllerFile())
	{
		MsgBox.ShowMsg(_T("未找到控制器配置文件!"),_T("查找失敗"), MB_YESNO | MB_ICONQUESTION);
		m_BL_MainMenu.EnableItemByName(_T("設置"), _T("添加設備"), FALSE);
	}
}


void CUDE_OutlookDlg::SearchReportFile()
{
// 	CMsgBox MsgBox(this);
// 	if (!m_FindCtrlFile.SearchReportFile())
// 	{
// 		MsgBox.ShowMsg(_T("未找到報表放置文件夾!"),_T("查找失敗"), MB_YESNO | MB_ICONQUESTION);
// 	}
}

void CUDE_OutlookDlg::SearchTemplateFile()//創建EXCEL模板文件夾
{
// 	CMsgBox MsgBox(this);
// 	if (!m_FindCtrlFile.SearchTemplateFile())
// 	{
// 		MsgBox.ShowMsg(_T("未找到EXCEL模板置文件夾!"),_T("查找失敗"), MB_YESNO | MB_ICONQUESTION);
// 	}
}


void CUDE_OutlookDlg::CheckFileCounter()
{
// 	vector<pair<CString,CString>> files;
// 	vector<CString> vstrFileName;
// 	CString strFilePath = GetExePath() + _T("\\Report\\");
// 	int nFileCounter = 0;
// 	m_FindCtrlFile.m_vstrFileName.clear();
// 	files = m_FindCtrlFile.FindFilesInDirecotryRecursion(_T("*.xlsx"),strFilePath, -1, nFileCounter, vstrFileName);
// 	vstrFileName.pop_back();
// 
// 	for (size_t i = 0; i < vstrFileName.size(); i++)
// 	{
// 		vstrFileName[i].Delete(vstrFileName[i].GetLength() - 4, 4);
// 	}
// 
// 	if (nFileCounter > _ttoi(m_BL_ReportLimit.GetValueText()))//如果文件夾數量超過上限
// 	{
// 		int nDelet = 0;
// 		while (nFileCounter > _ttoi(m_BL_ReportLimit.GetValueText()))
// 		{
// 			m_FindCtrlFile.RecycleFileOrFolder(vstrFileName[nDelet], FALSE);
// 			nFileCounter--;
// 			nDelet++;
// 		}
// 	}
}


void CUDE_OutlookDlg::Saveproject()
{
	CFileDialog dlgFile(FALSE,_T("*.RPT"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("RPT Files(*.RPT)|*.RPT|All File(*.*)|*.*||"),this);
	dlgFile.m_pOFN->lpstrTitle = _T("文件保存");
	if (m_strFilePath == _T(""))
	{
		if (IDOK == dlgFile.DoModal())
		{
			m_strFilePath = dlgFile.GetPathName();
		}
		else
		{
			return;
		}
	}
	CFile file;
	CFileException FileEX;
	if (!file.Open(m_strFilePath,CFile::modeWrite| CFile::modeCreate,&FileEX))
	{
		FileEX.ReportError();
		return;
	}	
	CArchive ar(&file,CArchive::store);

	m_Port.Serialize(ar);

 	Serialize(ar); 
 	
 	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
 	{
 		(*m_pControllerDlg[nCounter])->Serialize(ar);
  	}
	ar.Flush();
	ar.Close();
	file.Close();

	SetTimer(3, 1, NULL);

	CMsgBox MsgBox(this);

	MsgBox.ShowMsg(_T("檔案保存成功"), _T("Save"), MB_OK | MB_ICONINFORMATION);
}


void CUDE_OutlookDlg::Openproject()
{
	CFileDialog dlgFile(TRUE, _T("*.RPT"), nullptr, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY,
		_T("AOI Files(*.RPT)|*.RPT|All Files(*.*)|*.*||"), this);

	dlgFile.m_pOFN->lpstrTitle = _T("文件打開");

	if (IDOK == dlgFile.DoModal())
	{
		CString strPath = dlgFile.GetPathName();

		if (m_strFilePath == strPath)
		{
			return ;
		}
		else
		{
			if (m_bOpenFile)
			{
				Saveproject();
			}
			m_strFilePath = strPath;
		}
	}
	else
	{
		return ;
	}

	CFile file;
	CFileException FileEx;

	if (!file.Open(m_strFilePath, CFile::modeRead, &FileEx))
	{
		FileEx.ReportError();
		return ;
	}
	CArchive ar(&file, CArchive::load);

	m_Port.Serialize(ar);

	Serialize(ar);

	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
	{
		(*m_pControllerDlg[nCounter])->Serialize(ar);
	}

	ar.Flush();
	ar.Close();
	file.Close();

	m_bOpenFile = TRUE;

	SetTimer(3, 1, NULL);
}


void CUDE_OutlookDlg::OpenprojectWithFilePath(CString strPath)
{
	if (m_strFilePath == strPath)
	{
		return ;
	}
	else
	{
		if (m_bOpenFile)
		{
			Saveproject();
		}
		m_strFilePath = strPath;
	}

	CFile file;
	CFileException FileEx;

	if (!file.Open(m_strFilePath, CFile::modeRead, &FileEx))
	{
		FileEx.ReportError();
		return ;
	}
	CArchive ar(&file, CArchive::load);

	m_Port.Serialize(ar);

	Serialize(ar);

	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
	{
		(*m_pControllerDlg[nCounter])->Serialize(ar);
	}

	ar.Flush();
	ar.Close();
	file.Close();

	m_bOpenFile = TRUE;

	SetTimer(3, 1, NULL);
}


void CUDE_OutlookDlg::Saveasproject()
{
	CFileDialog dlgFile(FALSE,_T("*.RPT"),_T("無標題"),OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,_T("RPT Files(*.RPT)|*.RPT|All File(*.*)|*.*||"),this);
	dlgFile.m_pOFN->lpstrTitle = _T("文件另存為");
	if (IDOK == dlgFile.DoModal())
	{
		m_strFilePath = dlgFile.GetPathName();
	}
	else
	{
		return;
	}
	CFile file;
	CFileException FileEX;
	if (!file.Open(m_strFilePath,CFile::modeWrite| CFile::modeCreate,&FileEX))
	{
		FileEX.ReportError();
		return;
	}	
	CArchive ar(&file,CArchive::store);
	
	m_Port.Serialize(ar);

	Serialize(ar);

	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
	{
		(*m_pControllerDlg[nCounter])->Serialize(ar);
 	}
	ar.Flush();
	ar.Close();
	file.Close();
	// TODO: 在此添加命令处理程序代码


	SetTimer(3, 1, NULL);

	CMsgBox MsgBox(this);

	MsgBox.ShowMsg(_T("檔案保存成功"), _T("Save"), MB_OK | MB_ICONINFORMATION);
}

void CUDE_OutlookDlg::CreateNewReportList()
{
	m_BL_ReportMainList.ShowWindow(SW_SHOW);

	CleanCurrentReportList();//清空现有列表的全部内容

	m_BL_ReportMainList.AppendColumn(_T("序號"),DT_CENTER,70,FALSE);
	m_BL_ReportMainList.AppendColumn(_T("設備選型"),DT_CENTER,200,FALSE);
	m_BL_ReportMainList.AppendColumn(_T("設備名稱"),DT_CENTER,300,FALSE);
	m_BL_ReportMainList.AppendColumn(_T("站號"),DT_CENTER,80,FALSE);
	m_BL_ReportMainList.AppendColumn(_T("設備狀態"),DT_CENTER,110,FALSE);
	m_BL_ReportMainList.AppendColumn(_T("校驗方式"),DT_CENTER,100,FALSE);

	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetColumns(); nCounter++)//修改表头文字格式
	{
		m_BL_ReportMainList.SetHeaderFont(nCounter, _T("Tahoma"), 150);
	}

	m_BL_ReportMainList.SetColumnReadOnly(0, TRUE);
	m_BL_ReportMainList.SetColumnReadOnly(4, TRUE);

	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("保存"), TRUE);
	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("另存為"), TRUE);

	m_BL_Collect.ShowWindow(SW_HIDE);
	m_BL_CollectStatus.ShowWindow(SW_HIDE);
	m_BL_CollectStatus.SetCaption(_T("採集停止"));
	m_BL_CollectStatus.SetForeColor(RGB(155, 64, 64));
}

void CUDE_OutlookDlg::CleanCurrentReportList()
{
	m_pControllerDlg.clear();
	m_BL_ReportMainList.DeleteAll(TRUE);	
}


void CUDE_OutlookDlg::SaveHistoryPath()
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 

	strPath.Replace(_T(".exe"), _T(".ini"));

	CString strItem = _T("History");
	CString strOutpt;

	CString strHiatoryName;

	CString strAutoRun;
	CString strMin2Tray;
	CString strAutoFindFile;
	/////保存路徑數量，最大為6

	m_nHistoryPathCounter = m_strHistoryPath.size();
	strOutpt.Format(_T("%d"), m_nHistoryPathCounter);
	WritePrivateProfileString(strItem, _T("strHistoryPathCounter"), strOutpt, strPath);

	for (UINT nCounter = 0; nCounter < m_strHistoryPath.size(); nCounter++)
	{
		strHiatoryName.Format(_T("strHistoryPathCounter%d"),nCounter);
		WritePrivateProfileString(strItem, strHiatoryName, m_strHistoryPath[nCounter], strPath);
	}
	
	if (m_BL_MainMenu.IsItemCheckedByPos(_T("設置"), 3))
	{
		strAutoRun = _T("1");
		m_bAutoRun = TRUE;
	}
	else
	{
		strAutoRun = _T("0");
		m_bAutoRun = FALSE;
	}
	WritePrivateProfileString(strItem, _T("strAutoRun"), strAutoRun, strPath);
	SetAutoRun(_ttoi(strAutoRun));

	if (m_BL_MainMenu.IsItemCheckedByPos(_T("設置"), 4))
	{
		strMin2Tray = _T("1");
		m_bMin2Tray = TRUE;
	}
	else
	{
		strMin2Tray = _T("0");
		m_bMin2Tray = FALSE;
	}
	WritePrivateProfileString(strItem, _T("strMin2Tray"), strMin2Tray, strPath);

	if (m_BL_MainMenu.IsItemCheckedByPos(_T("設置"), 5))
	{
		strAutoFindFile = _T("1");
		m_bAutoFindFile = TRUE;
	}
	else
	{
		strAutoFindFile = _T("0");
		m_bAutoFindFile = FALSE;
	}
	WritePrivateProfileString(strItem, _T("strAutoFindFile"), strAutoFindFile, strPath);
}

void CUDE_OutlookDlg::LoadHistoryPath()
{
	CString strPath;

	GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
	strPath.ReleaseBuffer(); 
	strPath.Replace(_T(".exe"), _T(".ini"));

	CString strItem = _T("History");

	CString strHiatoryName;
	CString strHistoryPathCounter;
	CString strHistoryPath;
	CString strAutoRun;
	CString strMin2Tray;
	CString strAutoFindFile;

	GetPrivateProfileString(strItem, _T("strHistoryPathCounter"), _T(""), strHistoryPathCounter.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);

	m_nHistoryPathCounter = _ttoi(strHistoryPathCounter);

	for (UINT nCounter = 0; nCounter < m_nHistoryPathCounter; nCounter++)
	{
		strHiatoryName.Format(_T("strHistoryPathCounter%d"),nCounter);
		GetPrivateProfileString(strItem, strHiatoryName, _T(""), strHistoryPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);
		m_strHistoryPath.push_back(strHistoryPath);
		
	}

	GetPrivateProfileString(strItem, _T("strAutoRun"), _T("0"), strAutoRun.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);
	m_bAutoRun = _ttoi(strAutoRun);

	GetPrivateProfileString(strItem, _T("strMin2Tray"), _T("0"), strMin2Tray.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);
	m_bMin2Tray = _ttoi(strMin2Tray);
	m_bShowDlg = !m_bMin2Tray;

	GetPrivateProfileString(strItem, _T("strAutoFindFile"), _T("0"), strAutoFindFile.GetBufferSetLength(MAX_PATH + 1), MAX_PATH, strPath);
	m_bAutoFindFile = _ttoi(strAutoFindFile);
}
 
void CUDE_OutlookDlg::UpdateMenu()
{
	if (m_strHistoryPath.size() == 0)
	{
		m_strHistoryPath.insert(m_strHistoryPath.begin(), m_strFilePath);
	}
	else
	{
		BOOL bSame = FALSE;
		UINT nCounter = 0;
		CString strHistoryPath;
		for (; nCounter < m_strHistoryPath.size(); nCounter++)
		{
			if (m_strFilePath == m_strHistoryPath[nCounter])//有相同路徑
			{
				bSame = TRUE;
				break;
			}
		}
		if (!bSame)//如果沒有相同路徑,則插入新路徑
		{
			if (m_strHistoryPath[0] != m_strFilePath)
			{
				m_strHistoryPath.insert(m_strHistoryPath.begin(), m_strFilePath);
				while (m_strHistoryPath.size() > MAXHISTORYPATH)
				{
					m_strHistoryPath.pop_back();
				} 
			}
		}
		else
		{
			strHistoryPath = m_strHistoryPath[nCounter];
			m_strHistoryPath.insert(m_strHistoryPath.begin(), m_strFilePath);
			m_strHistoryPath.erase(m_strHistoryPath.begin() + nCounter + 1);
		}

	}
	SaveHistoryPath();
	SetMainMenu();
}

void CUDE_OutlookDlg::SetAutoRun(BOOL bAutoRun)
{
	CRegKey key;
	BOOL bOpenReg = key.Open(HKEY_LOCAL_MACHINE,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if (bOpenReg == ERROR_SUCCESS)
	{
		if (bAutoRun)
		{
			CString strPath;
			GetModuleFileName(nullptr, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH); 
			strPath.ReleaseBuffer(); 
			key.SetValue(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Run") ,strPath,_T("UDE_Outlook"));
		}
		else
		{
			key.DeleteValue(_T("UDE_Outlook"));
		}
	}	
	else
	{
		MessageBox(_T("注册表打开失败！请检查是否为管理员权限"));
	}
	key.Close();
}

BEGIN_EVENTSINK_MAP(CUDE_OutlookDlg, CAppBase)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_MainMenu, 2, CUDE_OutlookDlg::ItemClickBlMainMenu, VTS_BSTR VTS_BSTR VTS_I2 VTS_BOOL VTS_I4)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_ReportMainList, 5, CUDE_OutlookDlg::LBtDbClickBlReportMainList, VTS_I4 VTS_I4 VTS_PI2 VTS_I2)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_ReportMainList, 2, CUDE_OutlookDlg::ItemChangedBlReportMainList, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_ReportMainList, 6, CUDE_OutlookDlg::ItemEditFinishBlReportmainlist, VTS_I4 VTS_I4 VTS_BSTR)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_ReportMainList, 1, CUDE_OutlookDlg::RowsChangedBlReportmainlist, VTS_I4 VTS_I4 VTS_BOOL)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_DateReport, 1, CUDE_OutlookDlg::StatusChangedBlDatereport, VTS_BOOL)
	ON_EVENT(CUDE_OutlookDlg, IDC_BL_MouthReport, 1, CUDE_OutlookDlg::StatusChangedBlMouthreport, VTS_BOOL)
END_EVENTSINK_MAP()


void CUDE_OutlookDlg::ItemClickBlMainMenu(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags)
{
	CString strMenuName = strMenu;
	CString strItemName = strItem;
	CString strPath;
	if (strMenuName == _T("文件"))
	{
		switch (nItemPos)
		{
		case 0:   //新建一个报表系统表格
			m_strFilePath = _T("");
			CreateNewReportList();
			m_BL_Collect.ShowWindow(SW_HIDE);
			m_BL_CollectStatus.ShowWindow(SW_HIDE);
			m_bOpenFile = TRUE;
			break;
		case 1:
			Openproject();
			break;
		case 2:
			Saveproject();
			break;
		case 3:
			Saveasproject();
			break;
		case 4:
			break;
		case 5:
			OnCancel();
			break;
		default:
			break;
		}
	}
	if (strMenuName == _T("設置"))
	{
		switch (nItemPos)
		{
		case 0:
			m_Port.ShowParamWnd(SW_SHOW);
			break;
		case 1:
			m_CRC.ShowParamWnd(SW_SHOW);
			break;
		case 2:
			strPath = GetExePath() + _T("\\Configuration");
			m_ControllerAddDlg->m_BL_ControllerCheckModeName.SetDropDownData(m_CRC.LoadConfigurationFile(strPath, _T(".ini"), FALSE));
			strPath = GetExePath() + _T("\\Controller");
			m_ControllerAddDlg->m_BL_ControllerName.SetDropDownData(m_CRC.LoadConfigurationFile(strPath, _T(".ini"), FALSE));
			m_ControllerAddDlg->ShowWindow(SW_SHOW);

			if (m_ControllerAddDlg->m_BL_ControllerName.GetValueText() == _T(""))
			{
				m_ControllerAddDlg->m_BL_CtrlRegisters.SetStatus(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegisters1.SetStatus(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegistersStart.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegistersEnd.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegistersStart1.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegistersEnd1.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegistersPos.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlRegistersPos1.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlCoilStart.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlCoilEnd.SetEnabled(FALSE);
				m_ControllerAddDlg->m_BL_CtrlCoilPos.SetEnabled(FALSE);
			}
			else
			{
				m_ControllerAddDlg->LoadCtrlParam();
			}
			break;
		case 3:
			m_BL_MainMenu.CheckItemByPos(_T("設置"), 3, !bChecked);
			m_bAutoRun = !bChecked;
			break;

		case 4:
			m_BL_MainMenu.CheckItemByPos(_T("設置"), 4, !bChecked);
			m_bMin2Tray = !bChecked;
			break;

		case 5:
			m_BL_MainMenu.CheckItemByPos(_T("設置"), 5, !bChecked);
			m_bAutoFindFile = !bChecked;
			break;
		default:
			break;
		}
	}
	if (strMenuName == _T("幫助"))
	{
		switch (nItemPos)
		{
		case 0:
			m_SoftwareInfoDlg->ShowWindow(SW_SHOW);
			break;
		case 1:
			m_Register->CheckRegisterList(CHECKREGISTERLIST);
			m_Register->ShowWindow(SW_SHOW);
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	if (strMenuName == _T("最近開啟檔案"))
	{
		OpenprojectWithFilePath(strItemName);
	}
	
	// TODO: 在此处添加消息处理程序代码
}



void CUDE_OutlookDlg::LBtDbClickBlReportMainList(long nRow, long nCol, short* pnParam, short nFlags)
{
	// TODO: 在此处添加消息处理程序代码
	CMsgBox MsgBox(this);
	if (nCol == 0)
	{
		if (m_BL_ReportMainList.GetItemText(nRow, 1) == _T(""))
		{
			MsgBox.ShowMsg(_T("設備未選型"), _T("無法打開"), MB_OK | MB_ICONWARNING);
		}
		else
		{
			for (int nRowCounter = 0; nRowCounter < nRow; nRowCounter++)
			{
				if (m_BL_ReportMainList.GetItemText(nRowCounter, 2) == m_BL_ReportMainList.GetItemText(nRow, 2))
				{
					m_BL_ReportMainList.SelectRow(nRow);
					MsgBox.ShowMsg(_T("設備名稱重命名，請重新輸入"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
					return;
				}
			}

			if (m_BL_ReportMainList.GetItemText(nRow, 3) == _T(""))
			{
				m_BL_ReportMainList.SelectRow(nRow);
				MsgBox.ShowMsg(_T("未寫入站號，請輸入"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
				return;
			}

			if (m_BL_ReportMainList.GetItemText(nRow, 2) == _T(""))
			{
				m_BL_ReportMainList.SelectRow(nRow);
				MsgBox.ShowMsg(_T("未寫入設備名稱"), _T("無法打開"), MB_OK | MB_ICONWARNING);
				return;
			}
			(*m_pControllerDlg[nRow])->m_strControllerName = m_BL_ReportMainList.GetItemText(nRow, 1);
			(*m_pControllerDlg[nRow])->ShowWindow(SW_SHOW);
			(*m_pControllerDlg[nRow])->LoadFileData();
		}
		
	}
	if (nCol == 1)
	{
		* pnParam = 2;
		m_BL_ReportMainList.SetDropDownData(m_CRC.LoadConfigurationFile(GetExePath() + _T("\\Controller"), _T(".ini"), FALSE));
	}
	if (nCol == 4)
	{
		if (!m_BL_Collect.GetStatus())
		{
			m_bItemFinish = FALSE;
			* pnParam = 2;
			CString strStatus;
			strStatus = _T("設備運行;暫不運行");
			m_BL_ReportMainList.SetDropDownData(strStatus);
		}
	}
}


void CUDE_OutlookDlg::ItemEditFinishBlReportmainlist(long nRow, long nCol, LPCTSTR strNew)
{
	CMsgBox MsgBox(this);
	CString strItemInfo_New  =  strNew;

	if (nCol == 3)//修改的站号列
	{
		if (strItemInfo_New.GetLength() > 0)
		{
			if (!((strItemInfo_New[strItemInfo_New.GetLength() - 1] >= '0') && (strItemInfo_New[strItemInfo_New.GetLength() - 1] <= '9')))
			{
				m_MsgInfoDlg->SetTitle(_T("錯誤"));
				m_MsgInfoDlg->m_BL_btErrorInfo.SetCaption(_T("站號範圍1~247"));
				for (int i = 0; i < 3; i++)
				{
					m_MsgInfoDlg->m_BL_btErrorReason[i].ShowWindow(SW_HIDE);
				}
				m_MsgInfoDlg->ShowWindow(SW_SHOW);
				strItemInfo_New.Delete(strItemInfo_New.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, _T(""));
				return;
			}
		}

		for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
		{
			if ((strItemInfo_New != _T("")) && (nRow != nCounter))
			{
				if (m_BL_ReportMainList.GetItemText(nCounter, nCol) == strItemInfo_New)
				{
					m_MsgInfoDlg->SetTitle(_T("錯誤"));
					m_MsgInfoDlg->m_BL_btErrorInfo.SetCaption(_T("站號重複，請重新輸入"));
					for (int i = 0; i < 3; i++)
					{
						m_MsgInfoDlg->m_BL_btErrorReason[i].ShowWindow(SW_HIDE);
					}
					m_MsgInfoDlg->ShowWindow(SW_SHOW);
					m_BL_ReportMainList.SetItemText(nRow, nCol, _T(""));
					return;
				}
			}
		}
	}

	if (nCol == 2)
	{
		CString strInput = strNew;
		if (strInput.GetLength() != 0)
		{
			if (strInput[strInput.GetLength() - 1] == '/')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '|')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '\\')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == ':')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '?')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '<')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '>')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '"')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
			if (strInput[strInput.GetLength() - 1] == '*')
			{
				MsgBox.ShowMsg(_T("設備名稱不能含有| : ? < > / * \\ \" 特殊字符"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
		}
		for (int nRowCounter = 0; nRowCounter < nRow; nRowCounter++)
		{
			if ((m_BL_ReportMainList.GetItemText(nRowCounter, 2) == strInput) && (strInput.GetLength() != 0))
			{
				MsgBox.ShowMsg(_T("設備名稱重命名"), _T("錯誤"), MB_OK | MB_ICONSTOP);
				strInput.Delete(strInput.GetLength() - 1, 1);
				m_BL_ReportMainList.SetItemText(nRow, nCol, strInput);
				return;
			}
		}
		(*m_pControllerDlg[nRow])->SetTitle(m_BL_ReportMainList.GetItemText(nRow, 2));
		(*m_pControllerDlg[nRow])->m_SmartDotsListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("焊點檢測"));
		(*m_pControllerDlg[nRow])->m_SmartRobotListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("機械手臂"));
		(*m_pControllerDlg[nRow])->m_AngleTestListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("角度檢測"));
		(*m_pControllerDlg[nRow])->m_DiameterTestListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("直徑檢測"));
		(*m_pControllerDlg[nRow])->m_UDEOutlookListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("視覺檢測"));
		(*m_pControllerDlg[nRow])->m_UDEVisionListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("_UDEVision"));
		(*m_pControllerDlg[nRow])->m_SmartLEDListDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("LED檢測"));
		(*m_pControllerDlg[nRow])->m_DataCollectionDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("數據統計"));
		(*m_pControllerDlg[nRow])->m_NewSmartDotsDlg->SetTitle((*m_pControllerDlg[nRow])->GetTitle() + _T("新焊點檢測"));
	}
	if (nCol == 4)
	{
		m_bItemFinish = TRUE;
		if (m_BL_ReportMainList.GetItemText(nRow, nCol) == _T("設備運行"))
		{
			(*m_pControllerDlg[nRow])->UpdateMsgList();
			if ((*m_pControllerDlg[nRow])->m_MsgListDlg->m_BL_MsgList.GetRows() == 0)
			{
				m_BL_ReportMainList.SetItemText(nRow, nCol, _T("暫不運行"));
				m_BL_ReportMainList.SelectRow(nRow);
				MsgBox.ShowMsg(_T("設備中未設置待採集數據"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
				return;
			}
			for (int nCounter = 0;nCounter < (*m_pControllerDlg[nRow])->m_MsgListDlg->m_BL_MsgList.GetRows(); nCounter++)
			{
// 				if ((*m_pControllerDlg[nRow])->m_MsgListDlg->m_BL_MsgList.GetItemText(nCounter, 2) != _T(""))
// 				{
// 					if (_ttoi((*m_pControllerDlg[nRow])->m_MsgListDlg->m_BL_MsgList.GetItemText(nCounter, 2)) > 65535)
// 					{
// 						m_BL_ReportMainList.SetItemText(nRow, nCol, _T("暂不采集"));
// 						m_BL_ReportMainList.SelectRow(nRow);
// 						MsgBox.ShowMsg(_T("設備中數據地址未設置或設置超出範圍\n正確範圍是0~65535"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
// 						return;
// 					}
// 				}
// 				else
// 				{
// 					m_BL_ReportMainList.SetItemText(nRow, nCol, _T("暫不運行"));
// 					m_BL_ReportMainList.SelectRow(nRow);
// 					MsgBox.ShowMsg(_T("設備中數據地址未設置或設置超出範圍\n正確範圍是0~65535"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
// 					return;
// 				}
				if (m_BL_ReportMainList.GetItemText(nRow, 2) == _T(""))
				{
					m_BL_ReportMainList.SetItemText(nRow, nCol, _T("暫不運行"));
					m_BL_ReportMainList.SelectRow(nRow);
					MsgBox.ShowMsg(_T("該設備中未輸入設備名稱"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
					return;
				}
			}
			for (int nRowCounter = 0; nRowCounter < nRow; nRowCounter++)
			{
				if (m_BL_ReportMainList.GetItemText(nRowCounter, 2) == m_BL_ReportMainList.GetItemText(nRow, 2))
				{
					m_BL_ReportMainList.SetItemText(nRow, nCol, _T("暫不運行"));
					m_BL_ReportMainList.SelectRow(nRow);
					MsgBox.ShowMsg(_T("設備名稱重命名，請重新輸入"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
					return;
				}

			}
			
			if (m_BL_ReportMainList.GetItemText(nRow, 3) == _T(""))
			{
				m_BL_ReportMainList.SetItemText(nRow, nCol, _T("暫不運行"));
				m_BL_ReportMainList.SelectRow(nRow);
				MsgBox.ShowMsg(_T("未寫入站號，請輸入"), _T("設置提示"), MB_OK | MB_ICONINFORMATION);
				return;
			}
			m_BL_ReportMainList.SetItemReadOnly(nRow, 1, TRUE);
			m_BL_ReportMainList.SetItemReadOnly(nRow, 2, TRUE);
			m_BL_ReportMainList.SetItemReadOnly(nRow, 3, TRUE);
			//(*m_pControllerDlg[nRow])->m_BL_ReportCollectList.SetReadOnly(TRUE);
			m_BL_ReportMainList.SetItemTextColor(nRow, 4, RGB(0, 255, 255));
			(*m_pControllerDlg[nRow])->m_bCollecting = TRUE;
			#ifdef _DEBUG
			#else
			(*m_pControllerDlg[nRow])->m_BL_btAddCtrl.ShowWindow(SW_HIDE);
			(*m_pControllerDlg[nRow])->m_BL_btChangeCtrl.ShowWindow(SW_HIDE);
			#endif
		}
		else
		{
			m_BL_ReportMainList.SetItemTextColor(nRow, 4, RGB(255, 155, 32));
			m_BL_ReportMainList.SetItemReadOnly(nRow, 1, FALSE);
			m_BL_ReportMainList.SetItemReadOnly(nRow, 2, FALSE);
			m_BL_ReportMainList.SetItemReadOnly(nRow, 3, FALSE);
			//(*m_pControllerDlg[nRow])->m_BL_ReportCollectList.SetReadOnly(FALSE);
			(*m_pControllerDlg[nRow])->m_bCollecting = FALSE;
			#ifdef _DEBUG
			#else
			(*m_pControllerDlg[nRow])->m_BL_btAddCtrl.ShowWindow(SW_SHOW);
			(*m_pControllerDlg[nRow])->m_BL_btChangeCtrl.ShowWindow(SW_SHOW);
			#endif
		}
	}
	// TODO: 在此处添加消息处理程序代码
}


void CUDE_OutlookDlg::ItemChangedBlReportMainList(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew)
{
	CMsgBox MsgBox(this);
	// TODO: 在此处添加消息处理程序代码
	if (nCol == 1)
	{
		if (m_BL_ReportMainList.GetItemText(nRow, 1) != _T(""))
		{
			m_BL_ReportMainList.SetItemText(nRow, 5,  m_FindCtrlFile.LoadSignalData(m_BL_ReportMainList.GetItemText(nRow, 1)));
		}
	}
}


void CUDE_OutlookDlg::RowsChangedBlReportmainlist(long nOldRows, long nNewRows, BOOL bAppend)
{
	// TODO: 在此处添加消息处理程序代码
 	CString strStationNO;
 	if (nOldRows < nNewRows)//如果添加行
 	{
 		if (nOldRows < 247)
 		{
 			m_pControllerDlg.insert(m_pControllerDlg.begin() + m_BL_ReportMainList.GetCurRow(), new CBlender<CControllerDlg>);
 			(*m_pControllerDlg[m_BL_ReportMainList.GetCurRow()]).CreateBlendWnd(IDD_CONTROLLERDLG, this);
 			(*m_pControllerDlg[m_BL_ReportMainList.GetCurRow()]).CreateTopWnd(FALSE, FALSE);
			(*m_pControllerDlg[m_BL_ReportMainList.GetCurRow()])->m_pController = this;

			m_BL_ReportMainList.SetItemText(m_BL_ReportMainList.GetCurRow(), 4, _T("設備未運行"));

			m_BL_ReportMainList.SetItemTextColor(m_BL_ReportMainList.GetCurRow(), 4, RGB(255, 155, 32));

 			for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
 			{
 				(*m_pControllerDlg[nCounter])->m_nControllerDlgCounter = nCounter;
 				(*m_pControllerDlg[nCounter])->SetTitle(m_BL_ReportMainList.GetItemText(nCounter, 2));
				(*m_pControllerDlg[nCounter])->m_bLocked = m_swBaseLock.GetStatus();
				(*m_pControllerDlg[nCounter])->PostMessage(WM_LOCK_STATE, m_swBaseLock.GetStatus());
 			}
			vector<int> nvPart;
			nvPart.clear();
			m_nvMsg.push_back(nvPart);
			m_nvWriteMsg.push_back(nvPart);
			m_bvConnecting.push_back(FALSE);
 		}
 		else
 		{
 			m_MsgInfoDlg->SetTitle(_T("系統報警"));
 			m_MsgInfoDlg->m_BL_btErrorInfo.SetCaption(_T("系統最多容納247臺設備"));
			for (int i = 0; i < 3; i++)
			{
				m_MsgInfoDlg->m_BL_btErrorReason[i].ShowWindow(SW_HIDE);
			}
 			m_MsgInfoDlg->ShowWindow(SW_SHOW);
 		}
 	}
 	else//如果删除行
 	{
		if (m_BL_ReportMainList.GetRows() != 0)
		{
			vector<CBlender<CControllerDlg>*> pControllerDlg;
			pControllerDlg.clear();
			for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
			{
				pControllerDlg.push_back(m_pControllerDlg[_ttoi(m_BL_ReportMainList.GetItemText(nCounter, 3)) - 1]);
			}
			m_pControllerDlg.clear();
			m_pControllerDlg = pControllerDlg;
			for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
			{
				(*m_pControllerDlg[nCounter])->m_nControllerDlgCounter = nCounter;
				(*m_pControllerDlg[nCounter])->SetTitle(m_BL_ReportMainList.GetItemText(nCounter, 2));
			}
		}
		else
		{
			m_pControllerDlg.clear();
		}
 	}
	
}

void CUDE_OutlookDlg::StatusChangedBlDatereport(BOOL bNewStatus)
{
	// TODO: 在此处添加消息处理程序代码
	if (bNewStatus)
	{
		m_BL_DateReport.SetSelect(bNewStatus);
		m_BL_MouthReport.SetSelect(!bNewStatus);
	}
}


void CUDE_OutlookDlg::StatusChangedBlMouthreport(BOOL bNewStatus)
{
	// TODO: 在此处添加消息处理程序代码
	if (bNewStatus)
	{
		m_BL_MouthReport.SetSelect(bNewStatus);
		m_BL_DateReport.SetSelect(!bNewStatus);
	}
}


void CUDE_OutlookDlg:: StartCollect()
{
	CMsgBox MsgBox(this);

	for (int nRowCounter = 0; nRowCounter < m_BL_ReportMainList.GetRows(); nRowCounter++)
	{
		if (m_BL_ReportMainList.GetItemText(nRowCounter, 4) == _T("設備運行"))
		{
			if (m_BL_ReportMainList.GetItemText(nRowCounter, 1) == _T(""))
			{
				MsgBox.ShowMsg(_T("採集數據設備未選型"), _T("通訊提示"), MB_OK | MB_ICONINFORMATION);
				m_BL_Collect.SetStatus(FALSE);
				m_BL_ReportMainList.SelectRow(nRowCounter);
				return;
			}
			break;
		}
		if (nRowCounter == m_BL_ReportMainList.GetRows() - 1)
		{
			MsgBox.ShowMsg(_T("不存在待採集數據設備"), _T("通訊提示"), MB_OK | MB_ICONINFORMATION);
			m_BL_Collect.SetStatus(FALSE);
			return;
		}
	}

	for (int nRowCounter = 0; nRowCounter < m_BL_ReportMainList.GetRows(); nRowCounter++)
	{
		if (m_BL_ReportMainList.GetItemText(nRowCounter, 4) == _T("設備運行"))
		{
			if (m_BL_ReportMainList.GetItemText(nRowCounter, 1) == _T(""))
			{
				MsgBox.ShowMsg(_T("採集數據設備未選型"), _T("通訊提示"), MB_OK | MB_ICONINFORMATION);
				m_BL_Collect.SetStatus(FALSE);
				m_BL_ReportMainList.SelectRow(nRowCounter);
				return;
			}
		}
	}

	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
	{
		if (m_BL_ReportMainList.GetItemText(nCounter, 4) == _T("設備運行"))
		{
			(*m_pControllerDlg[nCounter])->PostMessage(WM_STARTCOLLECT);
		}
	}


	m_nCollectCounter_Main = 0;
	m_nCollectCounter_Slave = -1;

	SetTimer(4, 0, NULL);//啟動間斷收集Timmer，每個1MS掃描一次消息向量
	

	m_BL_CollectStatus.SetCaption(m_strCollectStatus[0]);
	m_BL_CollectStatus.SetForeColor(RGB(0, 255, 255));
	SetTimer(0, 500, NULL);

	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("新建"), FALSE);
	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("打開"), FALSE);
	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("最近開啟檔案"), FALSE);
// 	m_BL_ReportMainList.SetColumnReadOnly(1, TRUE);
// 	m_BL_ReportMainList.SetColumnReadOnly(3, TRUE);
	m_BL_ReportMainList.SetColumnReadOnly(4, TRUE);
	m_BL_ReportMainList.SetNoHotKey(TRUE);
	m_BL_ReportMainList.SetNoRtMenu(TRUE);
}


void CUDE_OutlookDlg::InterruptedSendMsg2Ctrl()
{
	m_bCommuncating = TRUE;

	if (m_nvWriteMsg[m_nCollectCounter_Main].size() > 0)//有待寫入數據
	{
		m_nCommunicationMode = WRITE_DATA;
	}
	else
	{
		m_nCommunicationMode = READ_DATA;
		m_nCollectCounter_Slave++;
		if (m_nvWriteMsg[m_nCollectCounter_Main].size() > 0)
		{
			m_nCollectCounter_Slave = -1;
			m_nvMsg[m_nCollectCounter_Main].erase(m_nvMsg[m_nCollectCounter_Main].begin());//刪除向量的第0個元素
			(*m_pControllerDlg[m_nCollectCounter_Main])->SendMessage(WM_COLLECTFINISH);//搜集完成，開始統計數據
			SetTimer(4, 0, NULL);
			return;
		}
		else
		{
			if (m_nCollectCounter_Slave == (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetRows())//如果超出了从表格的行数范围
			{
				m_bCommuncating = FALSE;
				m_nCollectCounter_Slave = -1;
				m_nvMsg[m_nCollectCounter_Main].erase(m_nvMsg[m_nCollectCounter_Main].begin());//刪除向量的第0個元素
				(*m_pControllerDlg[m_nCollectCounter_Main])->SendMessage(WM_COLLECTFINISH);//搜集完成，開始統計數據
				SetTimer(4, 0, NULL);
				return;
			}
			while ((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 6) == _T("0"))
			{
				m_nCollectCounter_Slave++;
				if (m_nCollectCounter_Slave == (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetRows())//如果超出了从表格的行数范围
				{
					m_bCommuncating = FALSE;
					m_nCollectCounter_Slave = -1;
					m_nvMsg[m_nCollectCounter_Main].erase(m_nvMsg[m_nCollectCounter_Main].begin());//刪除向量的第0個元素
					(*m_pControllerDlg[m_nCollectCounter_Main])->SendMessage(WM_COLLECTFINISH);//搜集完成，開始統計數據
					SetTimer(4, 0, NULL);
					return;
				}
				
			}
			if (m_nCollectCounter_Slave > 6)//基本信息採集完成
			{
				CString strInfo;
				CString strTemp;

				const BOOL bShowRelayAuto = (*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_swRelayAuto.IsWindowVisible();
				const BOOL bShowRelayUnAuto = (*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_swRelayUnAuto.IsWindowVisible();

				for (; ; m_nCollectCounter_Slave++)
				{
					if (m_nCollectCounter_Slave == (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetRows())//如果超出了从表格的行数范围
					{
						m_bCommuncating = FALSE;
						m_nCollectCounter_Slave = -1;
						m_nvMsg[m_nCollectCounter_Main].erase(m_nvMsg[m_nCollectCounter_Main].begin());//刪除向量的第0個元素
						(*m_pControllerDlg[m_nCollectCounter_Main])->SendMessage(WM_COLLECTFINISH);//搜集完成，開始統計數據
						SetTimer(4, 0, NULL);
						return;
					}
					 strInfo = (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 1);
					 strTemp = (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 8);
					 if (strInfo[0] == 'M')
					 {
						 if (bShowRelayAuto)
						 {
							 if (strTemp[0] == 'D')
							 {
								 const BOOL bDrop = (*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_dpRelay[0].GetEnabled();
								 if (!bDrop)
								 { 
									 continue;
								 }
								 else
								 {
									 break;
								 }
							 }
							 else
							 {
								 if ((*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_swRelayAuto.GetStatus())
								 {
									 if (strTemp[0] == 'A' || strTemp[0] == 'C')
									 {
										 break;
									 }
									 else
									 {
										 continue;
									 }
								 }
								 else
								 {
									 break;
								 }
							 }
						 }
						 else if(!bShowRelayAuto && bShowRelayUnAuto)
						 {
							 if (strTemp[0] == 'D')
							 {
								 const BOOL bDrop = (*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_dpRelay[0].GetEnabled();
								 if (!bDrop)
								 { 
									 continue;
								 }
								 else
								 {
									 break;
								 }
							 }
							 else
							 {
								 if (!(*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_swRelayUnAuto.GetStatus())
								 {
									 if (strTemp[0] == 'A' || strTemp[0] == 'C')
									 {
										 break;
									 }
									 else
									 {
										 continue;
									 }
								 }
								 else
								 {
									 break;
								 }
							 }
						 }
						 else if(!bShowRelayAuto && !bShowRelayUnAuto)
						 {
							break;
						 }
					 }
					 if (strInfo[0] == 'D' || strInfo[0] == 'R')
					 {
						 if (strTemp == _T("消息轉換") || (*m_pControllerDlg[m_nCollectCounter_Main])->m_ParameterListDlg->IsWindowVisible() || (*m_pControllerDlg[m_nCollectCounter_Main])->m_DataCollectionDlg->IsWindowVisible())
						 {
							 break;
						 }
						 else
						 {
							 continue;
						 }
					 }
				}
			}
		}
	}

	if (m_nCommunicationMode == READ_DATA)
	{
		m_nStationAddress = _ttoi((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 2));//地址
	}
	if (m_nCommunicationMode == WRITE_DATA)
	{
		m_nStationAddress = _ttoi((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 2));//地址
	}

	m_nStationNO = _ttoi(m_BL_ReportMainList.GetItemText(m_nCollectCounter_Main, 3));//站号

	CString strDataMode = _T("");
	if (m_nCommunicationMode == READ_DATA)
	{
		strDataMode = (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 1);
		if ((strDataMode[0] == 'R') || (strDataMode[0] == 'D'))
		{
			m_nCommend = 3;
		}
		if ((strDataMode[0] == 'M'))
		{
			m_nCommend = 1;
		}
	}
	if (m_nCommunicationMode == WRITE_DATA)
	{
		strDataMode = (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 1);//寄存器名
		if ((strDataMode[0] == 'R') || (strDataMode[0] == 'D'))
		{
			m_nCommend = 16;
		}
		if ((strDataMode[0] == 'M'))
		{
			m_nCommend = 15;
		}
	}

	vector<BYTE> bySend;
	bySend.clear();
	bySend.push_back(m_nStationNO);
	bySend.push_back(m_nCommend);
	bySend.push_back(m_nStationAddress >> 8);
	bySend.push_back(m_nStationAddress & 0xff);
	if (m_nCommunicationMode == READ_DATA)
	{
		bySend.push_back(0);
		if ((strDataMode[0] == 'R') || (strDataMode[0] == 'D'))
		{
			if (_ttoi((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 3)) == 16)
			{
				bySend.push_back(1);
			}
			else
			{
				bySend.push_back(2);
			}
		}
		if ((strDataMode[0] == 'M'))
		{
			bySend.push_back(1);
		}
	}
	
	if (m_nCommunicationMode == WRITE_DATA)
	{
		if ((strDataMode[0] == 'M'))
		{
			bySend.push_back(0);
			bySend.push_back(1);
			bySend.push_back(1);
			
			if ((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 10) == _T("0"))//重置值
			{
				bySend.push_back(0);
			}
			else
			{
				bySend.push_back(1);
			}
		}
		if ((strDataMode[0] == 'R') || (strDataMode[0] == 'D'))
		{
			int nSend = _ttoi((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 10));

			bySend.push_back(0);
			if (_ttoi((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 3)) == 16)
			{
				bySend.push_back(1);//写入数量
				bySend.push_back(2);//字節數
				bySend.push_back((nSend >> 8) & 0xFF);//數據
				bySend.push_back(nSend & 0xFF);//數據
			}
			else
			{
				bySend.push_back(2);//写入数量
				bySend.push_back(4);//字節數
				bySend.push_back((nSend >> 8) & 0xFF);//數據
				bySend.push_back((nSend) & 0xFF);//數據
				bySend.push_back((nSend >> 24) & 0xFF);//數據
				bySend.push_back((nSend >> 16) & 0xFF);//數據
			}

			//寫入數據的高八位和低八位
		}
	}
	
	CString strCRC;
	strCRC = GetCRCCheck(bySend, m_BL_ReportMainList.GetItemText(m_nCollectCounter_Main, 5));

	while (strCRC.GetLength() < 4)
	{
		strCRC.Insert(0, _T("0"));
	}
	CString strCRC_H = strCRC.Right(2);
	CString strCRC_L = strCRC.Left(2);

	bySend.push_back(m_CRC.String2Int(strCRC_H, HEX));
	bySend.push_back(m_CRC.String2Int(strCRC_L, HEX));

	m_bReceive = TRUE;
	m_Port.Write2Port(&bySend);
	SetTimer(1, 1500, NULL);//启动定时器，检测通讯超时
}



CString CUDE_OutlookDlg::GetCRCCheck(vector<BYTE> bySend, CString strChecckMode)
{
	CString strPart;

	CString strInput = _T("");
	int nDataType = 0;
	CString strResult_HEX;
	CString strResult_Bin;

	for (UINT nCounter = 0; nCounter < bySend.size(); nCounter++)
	{
		int n = bySend[nCounter];
		strPart.Format(_T("%x"), n);
		if (strPart.GetLength() == 1)
		{
			strPart.Insert(0, _T("0"));
		}
		strInput = strInput + strPart + _T(" ");
	}

	m_CRC.CRCCheck(strInput, HEX, strChecckMode, strResult_HEX, strResult_Bin);

	return strResult_HEX;
}


afx_msg LRESULT CUDE_OutlookDlg::OnGmsgserialreceivechar(WPARAM wParam, LPARAM lParam)
{
	CMsgBox MsgBox(this);
	static int nAllByteCounter = 0;
	static int nCurrentCounter = 0;
	if(m_Port.GetPortNum() == wParam)  
	{
		if (m_bReceive)
		{
			nCurrentCounter++;
			m_nReceiveData.push_back(BYTE(lParam));
			if (m_nReceiveData.size() == 2)
			{
				if (m_nCommend != m_nReceiveData[1])
				{
					//MsgBox.ShowMsg(_T("設備返回數據錯誤，通訊出現故障！"), _T("通訊錯誤"), MB_OK | MB_ICONWARNING);
				}

				if ((m_nCommunicationMode == WRITE_DATA))// && ((*m_pControllerDlg[m_nCollectCounter_Main])->m_strWriteMode == _T("M")))
				{
					nAllByteCounter = 8;
				}
			}

			if (m_nCommunicationMode == READ_DATA)
			{
				if (m_nReceiveData.size() == 3)
				{
					nAllByteCounter = m_nReceiveData[2] + 5;
				}
			}

			if ((nCurrentCounter == nAllByteCounter) && (nAllByteCounter != 0))
			{
				nAllByteCounter = 0;
				nCurrentCounter = 0;
				m_bReceive = FALSE;
				TranslateReveiveData();
				return 0;
			}
		}
	}
	return 0;
}


void CUDE_OutlookDlg:: TranslateReveiveData()
{
	KillTimer(1);
	KillTimer(5);
	(*m_pControllerDlg[m_nCollectCounter_Main])->KillTimer(5);
	m_bIsBalloonTipShow = FALSE;
	int nReceiveData = 0;
	long n = 0;
	CString strDataMode = _T("");
	
	m_bvConnecting[m_nCollectCounter_Main] = TRUE;//通訊在線

	if ((*m_pControllerDlg[m_nCollectCounter_Main])->m_BL_swConnect.GetStatus())
	{
		m_BL_ReportMainList.SetItemText(m_nCollectCounter_Main, 4, _T("設備運行中"));
		m_BL_ReportMainList.SetItemTextColor(m_nCollectCounter_Main, 4, RGB(0, 255, 255));
	}
	else
	{
		m_BL_ReportMainList.SetItemTextColor(m_nCollectCounter_Main, 4, RGB(255, 155, 32));
	}
	

	if (m_nCommunicationMode == READ_DATA)
	{
		strDataMode = (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 1);
		if ((strDataMode[0] == 'R') || (strDataMode[0] == 'D'))
		{
			if ((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nCollectCounter_Slave, 3) == _T("16"))
			{
				nReceiveData = (m_nReceiveData[3] << 8) + m_nReceiveData[4];
			}
			else
			{
				nReceiveData = (m_nReceiveData[5] << 24) + (m_nReceiveData[6] << 16) + (m_nReceiveData[3] << 8) + m_nReceiveData[4];
			}
		}
		if ((strDataMode[0] == 'M'))
		{
			nReceiveData = m_nReceiveData[3];
		}

		CString strReveiveData;
		strReveiveData.Format(_T("%d"), nReceiveData);
		(*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.SetItemText(m_nCollectCounter_Slave, 5, strReveiveData);
	}
	if (m_nCommunicationMode == WRITE_DATA)
	{
		//
		strDataMode = (*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 1);
		if ((strDataMode[0] == 'M'))
		{
			if((*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.GetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 10) == _T("3"))
			{
				(*m_pControllerDlg[m_nCollectCounter_Main])->m_MsgListDlg->m_BL_MsgList.SetItemText(m_nvWriteMsg[m_nCollectCounter_Main][0], 10, _T("0"));
			}
			else
			{
				m_nvWriteMsg[m_nCollectCounter_Main].erase(m_nvWriteMsg[m_nCollectCounter_Main].begin());
			}
		}
		if ((strDataMode[0] == 'D') || (strDataMode[0] == 'R'))
		{
			m_nvWriteMsg[m_nCollectCounter_Main].erase(m_nvWriteMsg[m_nCollectCounter_Main].begin());
		}
		if (m_nvWriteMsg[m_nCollectCounter_Main].size() < 1)
		{
			(*m_pControllerDlg[m_nCollectCounter_Main])->SendMessage(WM_WRITE_FINISH);
			m_nReceiveData.clear();
			SetTimer(4, 0, NULL);
			return;
		}
	}
	m_nReceiveData.clear();
	InterruptedSendMsg2Ctrl();
}


afx_msg LRESULT CUDE_OutlookDlg::OnGetRegisterMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == REGISTEROK)
	{
		for (int nCounter = 0; nCounter < 5; nCounter++)
		{
			m_BL_MainMenu.EnableItemByPos(_T("文件"), nCounter, TRUE);
		}

		for (int nCounter = 0; nCounter < 6; nCounter++)
		{
			m_BL_MainMenu.EnableItemByPos(_T("設置"), nCounter, TRUE);
		}

		if (m_bAutoFindFile)
		{
			if (m_strHistoryPath.size() != 0)
			{
				OpenprojectWithFilePath(m_strHistoryPath[0]);
				//m_BL_Collect.SetStatus(TRUE);
				//StartCollect();
				for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
				{
					if ((*m_pControllerDlg[nCounter])->m_bCollecting)
					{
						(*m_pControllerDlg[nCounter])->m_BL_swConnect.SetStatus(TRUE);
						(*m_pControllerDlg[nCounter])->StartConnect();
					}
				}
				m_BL_MainMenu.EnableItemByName(_T("文件"), _T("新建"), FALSE);
				m_BL_MainMenu.EnableItemByName(_T("文件"), _T("打開"), FALSE);
				m_BL_MainMenu.EnableItemByName(_T("文件"), _T("最近開啟檔案"), FALSE);
			}
		}
	}
	if (wParam == REGISTERERROR)
	{
		for (int nCounter = 0; nCounter < 5; nCounter++)
		{
			m_BL_MainMenu.EnableItemByPos(_T("文件"), nCounter, FALSE);
		}
		for (int nCounter = 0; nCounter < 6; nCounter++)
		{
			m_BL_MainMenu.EnableItemByPos(_T("設置"), nCounter, FALSE);
		}
	}
	return 0;
}


afx_msg LRESULT CUDE_OutlookDlg::OnGmsgminwindow(WPARAM wParam, LPARAM lParam)
{
	if (m_bMin2Tray)
	{
		m_bShowDlg = FALSE;
		Invalidate(FALSE);
	}
	else
	{
		this->ShowWindow(SW_MINIMIZE);
	}
	return 0;
}



afx_msg LRESULT CUDE_OutlookDlg::OnDeletFlie(WPARAM wParam, LPARAM lParam)
{
	CheckFileCounter();
	return 0;
}


afx_msg LRESULT CUDE_OutlookDlg::OnCollectRun(WPARAM wParam, LPARAM lParam)
{
	if ((*m_pControllerDlg[wParam])->m_BL_swConnect.GetStatus())
	{
		if (lParam == WRITE_DATA)
		{

		}
		else if(lParam == READ_DATA)
		{
			m_nvMsg[wParam].push_back(lParam);
		}
		else if(lParam == SAVE_DATA)
		{
			AfxBeginThread(_SaveProjectThread, this);//啟動採集數據線程
		}
	}
	return 0;
}


afx_msg LRESULT CUDE_OutlookDlg::OnWriteData(WPARAM wParam, LPARAM lParam)
{
	if ((*m_pControllerDlg[wParam])->m_BL_swConnect.GetStatus())
	{
		m_nvWriteMsg[wParam].push_back(lParam);//lParaam.....需要寫入數據的行號
	}
	return 0;
}


afx_msg LRESULT CUDE_OutlookDlg::OnStartcollect(WPARAM wParam, LPARAM lParam)
{
	m_BL_ReportMainList.SetItemReadOnly(wParam, 1, TRUE);
	m_BL_ReportMainList.SetItemReadOnly(wParam, 2, TRUE);
	m_BL_ReportMainList.SetItemReadOnly(wParam, 3, TRUE);
	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("新建"), FALSE);
	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("打開"), FALSE);
	m_BL_MainMenu.EnableItemByName(_T("文件"), _T("最近開啟檔案"), FALSE);
	m_BL_ReportMainList.SetItemText(wParam, 4, _T("設備運行中"));
	m_BL_ReportMainList.SetItemTextColor(wParam, 4, RGB(0, 255, 255));
	return 0;
}


afx_msg LRESULT CUDE_OutlookDlg::OnStopcollect(WPARAM wParam, LPARAM lParam)
{
	m_BL_ReportMainList.SetItemReadOnly(wParam, 1, FALSE);
	m_BL_ReportMainList.SetItemReadOnly(wParam, 2, FALSE);
	m_BL_ReportMainList.SetItemReadOnly(wParam, 3, FALSE);
	m_BL_ReportMainList.SetItemText(wParam, 4, _T("設備未運行"));
	m_BL_ReportMainList.SetItemTextColor(wParam, 4, RGB(255, 155, 32));
	return 0;
}


UINT CUDE_OutlookDlg::_SaveProjectThread(LPVOID pParam)
{
	CUDE_OutlookDlg *pApp = (CUDE_OutlookDlg *)pParam;
	UINT nRetVul = pApp->_SaveProjectThreadKernal();
	return nRetVul;
}


UINT CUDE_OutlookDlg::_SaveProjectThreadKernal(void)
{
	CFile file;
	CFileException FileEX;
	if (!file.Open(m_strFilePath,CFile::modeWrite| CFile::modeCreate,&FileEX))
	{
		FileEX.ReportError();
		return 0;
	}	
	CArchive ar(&file,CArchive::store);

	m_Port.Serialize(ar);

	Serialize(ar); 

	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
	{
		(*m_pControllerDlg[nCounter])->Serialize(ar);
	}
	return 0;
}


void CUDE_OutlookDlg::OnClose()
{
 	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMsgBox MsgBox(this);
	if (IDNO == MsgBox.ShowMsg(_T("确认退出软件"), _T("退出"), MB_YESNO | MB_ICONQUESTION))
	{
		return;
	}
#ifdef _DEBUG
	m_BL_Collect.SetStatus(FALSE);
	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)//停止采集数据
	{
		if (m_BL_ReportMainList.GetItemText(nCounter, 4) == _T("設備運行"))
		{
			(*m_pControllerDlg[nCounter])->SendMessage(WM_STOPCOLLECT);
		}
	}
	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
	{
		(*m_pControllerDlg[nCounter])->m_Excel.CloseExcelFile();
		(*m_pControllerDlg[nCounter])->m_Excel.ReleaseExcel();
	}
	m_Excel.CloseExcelFile();
	m_Excel.ReleaseExcel();
	if (m_bOpenFile)
	{
		if (m_strFilePath != _T(""))
		{
			Saveproject();
			UpdateMenu();
		}
		else
 		{
			if (IDYES == MsgBox.ShowMsg(_T("是否需要保存"), _T("保存檔案"), MB_YESNO | MB_ICONQUESTION))
			{
				Saveproject();
				UpdateMenu();
			}
		}
		
	}
	Shell_NotifyIcon(NIM_DELETE, &m_nid);             
	/*SetTimer(2, 1000, NULL);*/
	
#else

	m_BL_Collect.SetStatus(FALSE);
	for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)//停止采集数据
	{
		if (m_BL_ReportMainList.GetItemText(nCounter, 4) == _T("設備運行"))
		{
			(*m_pControllerDlg[nCounter])->SendMessage(WM_STOPCOLLECT);
		}
	}

	if (m_bOpenFile)
	{
		if (m_strFilePath != _T(""))
		{
			Saveproject();
			UpdateMenu();
		}
		else
		{
			if (IDYES == MsgBox.ShowMsg(_T("是否需要保存"), _T("保存檔案"), MB_YESNO | MB_ICONQUESTION))
			{
				Saveproject();
				UpdateMenu();
			}
		}

	}
	Shell_NotifyIcon(NIM_DELETE, &m_nid);        
	#endif
	CAppBase::OnClose();
}

void CUDE_OutlookDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
// 	m_Excel.CloseExcelFile();
// 	m_Excel.ReleaseExcel();

	CAppBase::OnCancel();
}

void CUDE_OutlookDlg::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_SoftwareInfoDlg->m_BL_btVersion.GetCaption();
		ar << m_BL_DateReport.GetSelect();
		ar << m_BL_MouthReport.GetSelect();
		ar << m_BL_ReportMainList.GetRows();
		for (int nCounter = 0; nCounter < m_BL_ReportMainList.GetRows(); nCounter++)
		{
			ar << m_BL_ReportMainList.GetItemText(nCounter, 1);
			ar << m_BL_ReportMainList.GetItemText(nCounter, 2);
			ar << m_BL_ReportMainList.GetItemText(nCounter, 3);
		}
	}
	else
	{	// loading code
		ar >> m_strSoftwareVersion;
		BOOL bAr = FALSE;
		ar >> bAr;
		m_BL_DateReport.SetSelect(bAr);
		ar >> bAr;
		m_BL_MouthReport.SetSelect(bAr);
		int nAr;
		CString strAr;
		ar >> nAr;
		CreateNewReportList();
		for (int nCounter = 0; nCounter < nAr; nCounter++)
		{
			m_BL_ReportMainList.AppendRow(TRUE);
			ar >> strAr;
			m_BL_ReportMainList.SetItemText(nCounter, 1, strAr);
			if (m_BL_ReportMainList.GetItemText(nCounter, 1) != _T(""))
			{
				(*m_pControllerDlg[nCounter])->m_strControllerName = m_BL_ReportMainList.GetItemText(nCounter, 1);
				m_BL_ReportMainList.SetItemText(nCounter, 5,  m_FindCtrlFile.LoadSignalData(m_BL_ReportMainList.GetItemText(nCounter, 1)));
			}
			
			ar >> strAr;
			m_BL_ReportMainList.SetItemText(nCounter, 2, strAr);
			(*m_pControllerDlg[nCounter])->SetTitle(m_BL_ReportMainList.GetItemText(nCounter, 2));
			ar >> strAr;
			m_BL_ReportMainList.SetItemText(nCounter, 3, strAr);
			(*m_pControllerDlg[nCounter])->m_strSoftwareVersion = m_strSoftwareVersion;
			(*m_pControllerDlg[nCounter])->m_bLocked = m_swBaseLock.GetStatus();
			(*m_pControllerDlg[nCounter])->PostMessage(WM_LOCK_STATE, m_swBaseLock.GetStatus());
		}
	}
}


void CUDE_OutlookDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT nCollectStatusCounter = 0;
	CMsgBox MsgBox(this);
	CString strErrorInfo;
	CString strCtrlNO;
	switch (nIDEvent)
	{
	case 0://顯示採集狀態循環變化
		KillTimer(0);
		m_BL_CollectStatus.SetForeColor(RGB(0,255,255));
		for (; nCollectStatusCounter < m_strCollectStatus.size(); nCollectStatusCounter++)
		{
			if (m_BL_CollectStatus.GetCaption() == m_strCollectStatus[nCollectStatusCounter])
			{
				if (nCollectStatusCounter == m_strCollectStatus.size() - 1)
				{
					m_BL_CollectStatus.SetCaption(m_strCollectStatus[0]);
					break;
				}
				else
				{
					m_BL_CollectStatus.SetCaption(m_strCollectStatus[nCollectStatusCounter + 1]);
					break;
				}
			}
		}
		SetTimer(0, 500, NULL);
		break;
	case 1:
		KillTimer(1);
		KillTimer(4);

		m_bReceive = FALSE;
		m_bCommuncating = FALSE;
		strCtrlNO.Format(_T("%d# 設備掉線"), m_nCollectCounter_Main + 1);
		m_BL_ReportMainList.SetItemText(m_nCollectCounter_Main, 4, _T("設備掉線"));
		m_BL_ReportMainList.SetItemTextColor(m_nCollectCounter_Main, 4, RGB(255, 155, 32));

		if (!m_bIsBalloonTipShow)
		{
			ShowBalloonTip(strCtrlNO, _T("提示"), 5000, 1);
			SetTimer(5, 5000, nullptr);
			m_bIsBalloonTipShow = TRUE;
		}

		m_BL_ReportMainList.SelectRow(m_nCollectCounter_Main);

		m_bvConnecting[m_nCollectCounter_Main] = FALSE;//該設備通訊失敗
		m_nCollectCounter_Slave = -1;
		m_nvMsg[m_nCollectCounter_Main].clear();


		(*m_pControllerDlg[m_nCollectCounter_Main])->PostMessage(WM_COLLECTLOSE); 

		m_nCollectCounter_Main++;
		if (m_nCollectCounter_Main >= (int)m_nvMsg.size())
		{
			m_nCollectCounter_Main = 0;
		}
		 
		SetTimer(4, 0, NULL);
		break;
	case 2:
		KillTimer(2);
		OnCancel();
		break;
	case 3:
		KillTimer(3);
		UpdateMenu();
		break;
	case 4:
		KillTimer(4);
		m_bCommuncating = FALSE;
		if ((m_nvMsg.size() > 0) || (m_nvWriteMsg.size() > 0))
		{
			if ((m_nvMsg[m_nCollectCounter_Main].size() <= 0) && (m_nvWriteMsg[m_nCollectCounter_Main].size() <= 0))
			{
				if (!m_bInterruptRead)
				{
					m_nCollectCounter_Main++;
				}
				else
				{
					m_bInterruptRead = FALSE;
				}
				
				if (m_nCollectCounter_Main >= (int)m_nvMsg.size())
				{
					m_nCollectCounter_Main = 0;
				}
				SetTimer(4, 0, NULL);
			}
			else
			{
				InterruptedSendMsg2Ctrl();
			}
		}
		else
		{
			SetTimer(4, 0, NULL);
		}
		break;
	case 5:
		KillTimer(5);
		m_bIsBalloonTipShow = FALSE;
		break;
	case 6:
		KillTimer(6);
		m_swBaseLock.SetStatus(TRUE);
		m_BL_ReportMainList.SetReadOnly(TRUE);
		for (int i = 0; i < m_BL_ReportMainList.GetRows(); i++)
		{
			(*m_pControllerDlg[i])->m_bLocked = TRUE;
			(*m_pControllerDlg[i])->PostMessage(WM_LOCK_STATE, TRUE);
		}
		break;
	default:
		break;
	}
	CAppBase::OnTimer(nIDEvent);
}


BOOL CUDE_OutlookDlg::ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle, UINT uTimeout, DWORD dwInfoFlags)
{
	m_nid.cbSize=sizeof(NOTIFYICONDATA);
	m_nid.uFlags = NIF_INFO;
	m_nid.uTimeout = uTimeout;
	m_nid.dwInfoFlags = dwInfoFlags;
	StrCpy(m_nid.szInfo,szMsg ? szMsg : _T(""));
	StrCpy(m_nid.szInfoTitle,szTitle ? szTitle : _T(""));
	return Shell_NotifyIcon(NIM_MODIFY, &m_nid);
}



void CUDE_OutlookDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((point.x >= 0) && (point.x <= 700) && (point.y>= 0) && (point.y <= 480))
	{ 
		if(MK_LBUTTON == nFlags)  
		{
			int Dx = point.x - m_startPoint.x;
			int Dy = point.y - m_startPoint.y;
			m_startRect.left += Dx;
			m_startRect.right += Dx;
			m_startRect.top +=Dy;
			m_startRect.bottom +=Dy;             //获取新的位置
			this->MoveWindow(&m_startRect);     //将窗口移到新的位置
		}

	}
	CAppBase::OnMouseMove(nFlags, point);
}


void CUDE_OutlookDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_startPoint = point;
	this->GetWindowRect(m_startRect);//传递窗口矩形
	CAppBase::OnLButtonDown(nFlags, point);
}


void CUDE_OutlookDlg::DelayTimeRun()
{
	int in = 10;
again:

	LARGE_INTEGER cpuFreq;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
	double rumTime = 0.0;

	QueryPerformanceFrequency(&cpuFreq);
	QueryPerformanceCounter(&startTime);

	while (rumTime < 1)
	{
		QueryPerformanceCounter(&endTime);
		rumTime = (((double)endTime.QuadPart - (double)startTime.QuadPart) / (double)cpuFreq.QuadPart);
	}

	m_bCommuncating = FALSE;
	if ((m_nvMsg.size() > 0) || (m_nvWriteMsg.size() > 0))
	{
		if ((m_nvMsg[m_nCollectCounter_Main].size() <= 0) && (m_nvWriteMsg[m_nCollectCounter_Main].size() <= 0))
		{
			if (!m_bInterruptRead)
			{
				m_nCollectCounter_Main++;
			}
			else
			{
				m_bInterruptRead = FALSE;
			}

			if (m_nCollectCounter_Main >= (int)m_nvMsg.size())
			{
				m_nCollectCounter_Main = 0;
			}
			goto again;
		}
		else
		{
			InterruptedSendMsg2Ctrl();
		}
	}
	else
	{
		goto again;
	}
}

UINT CUDE_OutlookDlg::_DelayTimeRunThread(LPVOID pParam)
{
	CUDE_OutlookDlg *pApp = (CUDE_OutlookDlg *)pParam;
	UINT nRetVul = pApp->_DelayTimeRunThreadKernal();
	return nRetVul;
}


UINT CUDE_OutlookDlg::_DelayTimeRunThreadKernal(void)
{
again:

	LARGE_INTEGER cpuFreq;
	LARGE_INTEGER startTime;
	LARGE_INTEGER endTime;
    double rumTime = 0.0;

	QueryPerformanceFrequency(&cpuFreq);
	QueryPerformanceCounter(&startTime);

	while (rumTime < 0.00001)
	{
		QueryPerformanceCounter(&endTime);
		rumTime = (((double)(endTime.QuadPart - startTime.QuadPart)) / (double)cpuFreq.QuadPart);
	}

	m_bCommuncating = FALSE;
	if ((m_nvMsg.size() > 0) || (m_nvWriteMsg.size() > 0))
	{
		if ((m_nvMsg[m_nCollectCounter_Main].size() <= 0) && (m_nvWriteMsg[m_nCollectCounter_Main].size() <= 0))
		{
			if (!m_bInterruptRead)
			{
				m_nCollectCounter_Main++;
			}
			else
			{
				m_bInterruptRead = FALSE;
			}

			if (m_nCollectCounter_Main >= (int)m_nvMsg.size())
			{
				m_nCollectCounter_Main = 0;
			}
			goto again;
		}
		else
		{
			InterruptedSendMsg2Ctrl();
		}
	}
	else
	{
		goto again;
	}
	return 0;
}