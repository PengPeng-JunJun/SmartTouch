// ControllerAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDE_Outlook.h"
#include "ControllerAddDlg.h"
#include "afxdialogex.h"


// CControllerAddDlg �Ի���

IMPLEMENT_DYNAMIC(CControllerAddDlg, CTpLayerWnd)

CControllerAddDlg::CControllerAddDlg(CWnd* pParent /*=NULL*/)
	: CTpLayerWnd(CControllerAddDlg::IDD, pParent)
	, m_bIsFileChanged(FALSE)
{

}


CControllerAddDlg::CControllerAddDlg(UINT nIDTemplate, CWnd * pParent/* = nullptr*/)
	: CTpLayerWnd(nIDTemplate, pParent)
	, m_bIsFileChanged(FALSE)
{

}

CControllerAddDlg::~CControllerAddDlg()
{
}

void CControllerAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CTpLayerWnd::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BL_ControllerName, m_BL_ControllerName);
	DDX_Control(pDX, IDC_BL_ControllerCheckModeName, m_BL_ControllerCheckModeName);
	DDX_Control(pDX, IDC_BL_CtrlRegistersStart, m_BL_CtrlRegistersStart);
	DDX_Control(pDX, IDC_BL_CtrlRegistersEnd, m_BL_CtrlRegistersEnd);
	DDX_Control(pDX, IDC_BL_CtrlRegistersStart1, m_BL_CtrlRegistersStart1);
	DDX_Control(pDX, IDC_BL_CtrlRegistersEnd1, m_BL_CtrlRegistersEnd1);
	DDX_Control(pDX, IDC_BL_CtrlRegisters, m_BL_CtrlRegisters);
	DDX_Control(pDX, IDC_BL_CtrlRegisters1, m_BL_CtrlRegisters1);
	DDX_Control(pDX, IDC_BL_CtrlRegistersPos, m_BL_CtrlRegistersPos);
	DDX_Control(pDX, IDC_BL_CtrlRegistersPos1, m_BL_CtrlRegistersPos1);

	DDX_Control(pDX, IDC_BL_CtrlCoilStart, m_BL_CtrlCoilStart);
	DDX_Control(pDX, IDC_BL_CtrlCoilEnd, m_BL_CtrlCoilEnd);
	DDX_Control(pDX, IDC_BL_CtrlCoil, m_BL_CtrlCoil);
	DDX_Control(pDX, IDC_BL_CtrlCoilPos, m_BL_CtrlCoilPos);

}


BEGIN_MESSAGE_MAP(CControllerAddDlg, CTpLayerWnd)
END_MESSAGE_MAP()


// CControllerAddDlg ��Ϣ�������


BOOL CControllerAddDlg::OnInitDialog()
{
	CTpLayerWnd::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetTitle(WINDOWTITLE);
	m_BtBaseClose.ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CControllerAddDlg::_DefaultFocus(void)
{
	m_BtBaseOk.ShowWindow(FALSE);
	m_BtBaseCancel.ShowWindow(FALSE);
}
BEGIN_EVENTSINK_MAP(CControllerAddDlg, CTpLayerWnd)
	ON_EVENT(CControllerAddDlg, IDC_BL_AddOK, 1, CControllerAddDlg::LBtClickedBlAddok, VTS_I4)
	ON_EVENT(CControllerAddDlg, IDC_BL_AddCancel, 1, CControllerAddDlg::LBtClickedBlAddcancel, VTS_I4)
	ON_EVENT(CControllerAddDlg, IDC_BL_ControllerName, 3, CControllerAddDlg::SelectChangedBlControllername, VTS_BSTR VTS_BSTR VTS_I2)
	ON_EVENT(CControllerAddDlg, IDC_BL_ControllerName, 1, CControllerAddDlg::TextChangedBlControllername, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_ControllerCheckModeName, 3, CControllerAddDlg::SelectChangedBlControllercheckmodename, VTS_BSTR VTS_BSTR VTS_I2)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlCoilStart, 1, CControllerAddDlg::ValueChangedBlCtrlcoilstart, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlCoilEnd, 1, CControllerAddDlg::ValueChangedBlCtrlcoilend, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegistersStart, 1, CControllerAddDlg::ValueChangedBlCtrlregistersstart, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegistersEnd, 1, CControllerAddDlg::ValueChangedBlCtrlregistersend, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegisters, 1, CControllerAddDlg::StatusChangedBlCtrlregisters, VTS_BOOL)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegisters1, 1, CControllerAddDlg::StatusChangedBlCtrlregisters1, VTS_BOOL)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegistersStart1, 1, CControllerAddDlg::ValueChangedBlCtrlregistersstart1, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegistersEnd1, 1, CControllerAddDlg::ValueChangedBlCtrlregistersend1, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegistersPos, 1, CControllerAddDlg::ValueChangedBlCtrlregisterspos, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlRegistersPos1, 1, CControllerAddDlg::ValueChangedBlCtrlregisterspos1, VTS_BSTR)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlCoil, 1, CControllerAddDlg::StatusChangedBlCtrlcoil, VTS_BOOL)
	ON_EVENT(CControllerAddDlg, IDC_BL_CtrlCoilPos, 1, CControllerAddDlg::ValueChangedBlCtrlcoilpos, VTS_BSTR)
END_EVENTSINK_MAP()


void CControllerAddDlg::LBtClickedBlAddok(long nFlags)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	if (AddFile() == 0)
	{

	}
	else
	{
		switch (AddFile())
		{
		case NOFILENAME:
			MsgBox.ShowMsg(_T("δݔ���O�����Q"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case NOCHECKNAME:
			MsgBox.ShowMsg(_T("δݔ��У򞅢��ģ��"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case NOCOILSTART:
			MsgBox.ShowMsg(_T("δݔ�뾀Ȧ��ʼ��ַ"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case NOCOILEND:
			MsgBox.ShowMsg(_T("δݔ�뾀Ȧ�Y����ַ"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case NOREGISTERSSTART:
			MsgBox.ShowMsg(_T("δݔ�뾏������ʼ��ַ"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case NOREGISTERSEND:
			MsgBox.ShowMsg(_T("δݔ�뾏�����Y����ַ"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case REGISTERDATAERROR:
			MsgBox.ShowMsg(_T("��������ַ�e�`����ʼ��ַ���ܴ�춽Y����ַ"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		case COILDATAERROR:
			MsgBox.ShowMsg(_T("��Ȧ��ַ�e�`����ʼ��ַ���ܴ�춽Y����ַ"), _T("ݔ���e�`"), MB_OK |MB_ICONSTOP);
			break;
		default:
			break;
		}
	}
}


void CControllerAddDlg::LBtClickedBlAddcancel(long nFlags)
{
	//m_pMsgCtrlAddDlg
	OnCancel();
	// TODO: �ڴ˴������Ϣ����������
}



int CControllerAddDlg::AddFile()
{
	if (m_BL_ControllerName.GetValueText() != _T(""))
	{
		if (m_BL_ControllerCheckModeName.GetValueText() != _T(""))
		{
			if (m_BL_CtrlCoilStart.GetValueText() != _T(""))
			{
				if (m_BL_CtrlCoilEnd.GetValueText() != _T(""))
				{
					if (m_BL_CtrlRegisters.GetStatus())//R������̎�ʹ�à�B
					{
						if (m_BL_CtrlRegistersStart.GetValueText() != _T(""))
						{
							if (m_BL_CtrlRegistersEnd.GetValueText() != _T(""))
							{
								if (_ttoi(m_BL_CtrlRegistersStart.GetValueText()) <= _ttoi(m_BL_CtrlRegistersEnd.GetValueText()))
								{
									if (m_BL_CtrlRegisters1.GetStatus())//D������̎�ʹ�à�B
									{
										if (m_BL_CtrlRegistersStart1.GetValueText() != _T(""))
										{
											if (m_BL_CtrlRegistersEnd1.GetValueText() != _T(""))
											{
												if (_ttoi(m_BL_CtrlRegistersStart1.GetValueText()) <= _ttoi(m_BL_CtrlRegistersEnd1.GetValueText()))
												{
													if (m_BL_CtrlRegisters.GetStatus())//M��ʹ�à�B
													{
														if (_ttoi(m_BL_CtrlCoilStart.GetValueText()) <= _ttoi(m_BL_CtrlCoilEnd.GetValueText()))
														{
															CMsgBox MsgBox(this);
															CString strConfigurationName;
															strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

															if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
															{
																if (m_bIsFileChanged)
																{
																	if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
																	{
																		SaveCtrlParam();
																		m_bIsFileChanged = FALSE;
																		return OK;
																	}
																	else
																	{
																		LoadCtrlParam();
																		return OK;
																	}
																}
																else
																{
																	return OK;
																}
															}
															else
															{
																if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
																{
																	SaveCtrlParam();
																	m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
																	return OK;
																}
																else
																{
																	return OK;
																}
															}
														}
														else
														{
															return COILDATAERROR;
														}
													}
													else
													{
														CMsgBox MsgBox(this);
														CString strConfigurationName;
														strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

														if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
														{
															if (m_bIsFileChanged)
															{
																if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
																{
																	SaveCtrlParam();
																	m_bIsFileChanged = FALSE;
																	return OK;
																}
																else
																{
																	LoadCtrlParam();
																	return OK;
																}
															}
															else
															{
																return OK;
															}
														}
														else
														{
															if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
															{
																SaveCtrlParam();
																m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
																return OK;
															}
															else
															{
																return OK;
															}
														}
													}
												}
												else
												{
													return REGISTERDATAERROR;
												}
											}
											else
											{
												return NOREGISTERSEND;
											}
										}
										else
										{
											return NOREGISTERSSTART;
										}
									}
									else//D������̎춷�ʹ�à�B
									{
										if (m_BL_CtrlRegisters.GetStatus())//M��ʹ�à�B
										{
											if (_ttoi(m_BL_CtrlCoilStart.GetValueText()) <= _ttoi(m_BL_CtrlCoilEnd.GetValueText()))
											{
												CMsgBox MsgBox(this);
												CString strConfigurationName;
												strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

												if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
												{
													if (m_bIsFileChanged)
													{
														if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
														{
															SaveCtrlParam();
															m_bIsFileChanged = FALSE;
															return OK;
														}
														else
														{
															LoadCtrlParam();
															return OK;
														}
													}
													else
													{
														return OK;
													}
												}
												else
												{
													if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
													{
														SaveCtrlParam();
														m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
														return OK;
													}
													else
													{
														return OK;
													}
												}
											}
											else
											{
												return COILDATAERROR;
											}
										}
										else
										{
											CMsgBox MsgBox(this);
											CString strConfigurationName;
											strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

											if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
											{
												if (m_bIsFileChanged)
												{
													if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
													{
														SaveCtrlParam();
														m_bIsFileChanged = FALSE;
														return OK;
													}
													else
													{
														LoadCtrlParam();
														return OK;
													}
												}
												else
												{
													return OK;
												}
											}
											else
											{
												if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
												{
													SaveCtrlParam();
													m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
													return OK;
												}
												else
												{
													return OK;
												}
											}
										}
									}
								}
								else
								{
									return REGISTERDATAERROR;
								}
							}
							else
							{
								return NOREGISTERSEND;
							}
						}
						else
						{
							return NOREGISTERSSTART;
						}
					}
					else//R������̎춷�ʹ�à�B
					{
						if (m_BL_CtrlRegisters1.GetStatus())//D������̎�ʹ�à�B
						{
							if (m_BL_CtrlRegistersStart1.GetValueText() != _T(""))
							{
								if (m_BL_CtrlRegistersEnd1.GetValueText() != _T(""))
								{
									if (_ttoi(m_BL_CtrlRegistersStart1.GetValueText()) <= _ttoi(m_BL_CtrlRegistersEnd1.GetValueText()))
									{
										if (m_BL_CtrlRegisters.GetStatus())//M��ʹ�à�B
										{
											if (m_BL_CtrlCoilStart.GetValueText() != _T(""))
											{
												if (m_BL_CtrlCoilEnd.GetValueText() != _T(""))
												{
													if (_ttoi(m_BL_CtrlCoilStart.GetValueText()) <= _ttoi(m_BL_CtrlCoilEnd.GetValueText()))
													{
														CMsgBox MsgBox(this);
														CString strConfigurationName;
														strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

														if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
														{
															if (m_bIsFileChanged)
															{
																if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
																{
																	SaveCtrlParam();
																	m_bIsFileChanged = FALSE;
																	return OK;
																}
																else
																{
																	LoadCtrlParam();
																	return OK;
																}
															}
															else
															{
																return OK;
															}
														}
														else
														{
															if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
															{
																SaveCtrlParam();
																m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
																return OK;
															}
															else
															{
																return OK;
															}
														}
													}
													else
													{
														return COILDATAERROR;
													}
												}
												return NOCOILEND;
											}
											else
											{
												return NOCOILSTART;
											}
										}
										else
										{
											CMsgBox MsgBox(this);
											CString strConfigurationName;
											strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

											if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
											{
												if (m_bIsFileChanged)
												{
													if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
													{
														SaveCtrlParam();
														m_bIsFileChanged = FALSE;
														return OK;
													}
													else
													{
														LoadCtrlParam();
														return OK;
													}
												}
												else
												{
													return OK;
												}
											}
											else
											{
												if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
												{
													SaveCtrlParam();
													m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
													return OK;
												}
												else
												{
													return OK;
												}
											}
										}
									}
									else
									{
										return REGISTERDATAERROR;
									}
								}
								else
								{
									return NOREGISTERSEND;
								}
							}
							else
							{
								return NOREGISTERSSTART;
							}
						}
						else//D������̎춷�ʹ�à�B
						{
							if (m_BL_CtrlRegisters.GetStatus())//M��ʹ�à�B
							{
								if (m_BL_CtrlCoilStart.GetValueText() != _T(""))
								{
									if (m_BL_CtrlCoilEnd.GetValueText() != _T(""))
									{
										if (_ttoi(m_BL_CtrlCoilStart.GetValueText()) <= _ttoi(m_BL_CtrlCoilEnd.GetValueText()))
										{
											CMsgBox MsgBox(this);
											CString strConfigurationName;
											strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

											if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
											{
												if (m_bIsFileChanged)
												{
													if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
													{
														SaveCtrlParam();
														m_bIsFileChanged = FALSE;
														return OK;
													}
													else
													{
														LoadCtrlParam();
														return OK;
													}
												}
												else
												{
													return OK;
												}
											}
											else
											{
												if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
												{
													SaveCtrlParam();
													m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
													return OK;
												}
												else
												{
													return OK;
												}
											}
										}
										else
										{
											return COILDATAERROR;
										}
									}
									return NOCOILEND;
								}
								else
								{
									return NOCOILSTART;
								}
							}
							else
							{

								CMsgBox MsgBox(this);
								CString strConfigurationName;
								strConfigurationName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

								if (GetFileAttributes(strConfigurationName) != -1) //����ļ�����
								{
									if (m_bIsFileChanged)
									{
										if (IDOK == MsgBox.ShowMsg(_T("�����ļ��Ѵ��ڣ��_�J�޸ģ�"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
										{
											SaveCtrlParam();
											m_bIsFileChanged = FALSE;
											return OK;
										}
										else
										{
											LoadCtrlParam();
											return OK;
										}
									}
									else
									{
										return OK;
									}
								}
								else
								{
									if (IDOK == MsgBox.ShowMsg(_T("�_�J�����µ������ļ���"), _T("�_�J�޸�"), MB_OKCANCEL | MB_ICONQUESTION))
									{
										SaveCtrlParam();
										m_BL_ControllerName.SetDropDownData(m_BL_ControllerName.GetDropDownData() + _T(";")+ m_BL_ControllerName.GetValueText());
										return OK;
									}
									else
									{
										return OK;
									}
								}
							}
						}
					}
				}
				else
				{
					return NOCOILEND;
				}
			}
			else
			{
				return NOCOILSTART;
			}
		}
		else
		{
			return NOCHECKNAME;
		}
	}
	else
	{
		return NOFILENAME;
	}

}


CString CControllerAddDlg:: GetExePath(void)  
{  
	CString strExePath;  
	GetModuleFileName(NULL, strExePath.GetBuffer(MAX_PATH), MAX_PATH);  
	strExePath.ReleaseBuffer();  
	strExePath = strExePath.Left(strExePath.ReverseFind(_T('\\')));  
	return strExePath;  
}  

void CControllerAddDlg:: SaveCtrlParam()
{
	CString strPath;
	strPath = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

	CString strCtrlName;
	CString strCtrlCheckModeName;
	
	CString strRegistersStart;
	CString strRegistersEnd;
	CString strRegistersStart1;
	CString strRegistersEnd1;
	CString strRegistersPos;
	CString strRegistersPos1;
	CString strRegisters;
	CString strRegisters1;

	CString strCoil;
	CString strCoilStart; 
	CString strCoilEnd;   
	CString strCoilPos;


	strCtrlName = m_BL_ControllerName.GetValueText();
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strCtrlName"), strCtrlName, strPath);

	strCtrlCheckModeName = m_BL_ControllerCheckModeName.GetValueText();
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strCtrlCheckModeName"), strCtrlCheckModeName, strPath);

	strRegistersStart.Format(_T("%s"),m_BL_CtrlRegistersStart.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegistersStart"), strRegistersStart, strPath);

	strRegistersEnd.Format(_T("%s"),m_BL_CtrlRegistersEnd.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegistersEnd"), strRegistersEnd, strPath);

	strRegistersStart1.Format(_T("%s"),m_BL_CtrlRegistersStart1.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegistersStart1"), strRegistersStart1, strPath);

	strRegistersEnd1.Format(_T("%s"),m_BL_CtrlRegistersEnd1.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegistersEnd1"), strRegistersEnd1, strPath);

	strRegisters.Format(_T("%d"),m_BL_CtrlRegisters.GetStatus());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegisters"), strRegisters, strPath);

	strRegisters1.Format(_T("%d"),m_BL_CtrlRegisters1.GetStatus());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegisters1"), strRegisters1, strPath);

	strRegistersPos.Format(_T("%s"),m_BL_CtrlRegistersPos.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegistersPos"), strRegistersPos, strPath);

	strRegistersPos1.Format(_T("%s"),m_BL_CtrlRegistersPos1.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strRegistersPos1"), strRegistersPos1, strPath);

	strCoilStart.Format(_T("%s"),m_BL_CtrlCoilStart.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strCoilStart"), strCoilStart, strPath);

	strCoilEnd.Format(_T("%s"),m_BL_CtrlCoilEnd.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strCoilEnd"), strCoilEnd, strPath);

	strCoil.Format(_T("%d"),m_BL_CtrlCoil.GetStatus());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strCoil"), strCoil, strPath);

	strCoilPos.Format(_T("%s"),m_BL_CtrlCoilPos.GetValueText());
	WritePrivateProfileString( m_BL_ControllerName.GetValueText(),  _T("strCoilPos"), strCoilPos, strPath);
}


void CControllerAddDlg::LoadCtrlParam()
{
	CString strFileName;

	strFileName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

	CString strCtrlName;
	CString strCtrlCheckModeName;
	CString strRegistersStart;
	CString strRegistersEnd;
	CString strRegistersStart1;
	CString strRegistersEnd1;
	CString strRegistersPos;
	CString strRegistersPos1;
	CString strRegisters;
	CString strRegisters1;

	CString strCoil;
	CString strCoilStart; 
	CString strCoilEnd;   
	CString strCoilPos;

	if (GetFileAttributes(strFileName) != -1) //����ļ�����
	{
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCtrlName"),_T(""),strCtrlName.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCtrlCheckModeName"),_T(""),strCtrlCheckModeName.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoilStart"),_T(""),strCoilStart.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoilEnd"),_T(""),strCoilEnd.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersStart"),_T(""),strRegistersStart.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersEnd"),_T(""),strRegistersEnd.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersStart1"),_T(""),strRegistersStart1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersEnd1"),_T(""),strRegistersEnd1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegisters"),_T(""),strRegisters.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegisters1"),_T(""),strRegisters1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersPos"),_T(""),strRegistersPos.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersPos1"),_T(""),strRegistersPos1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoil"),_T(""),strCoil.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
		GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoilPos"),_T(""),strCoilPos.GetBuffer(MAX_PATH),MAX_PATH,strFileName);


		m_BL_ControllerName.SetValueText(strCtrlName);
		m_BL_ControllerCheckModeName.SetValueText(strCtrlCheckModeName);
		m_BL_CtrlCoilStart.SetValueText(strCoilStart);
		m_BL_CtrlCoilEnd.SetValueText(strCoilEnd);
		m_BL_CtrlRegistersStart.SetValueText(strRegistersStart);
		m_BL_CtrlRegistersEnd.SetValueText(strRegistersEnd);
		m_BL_CtrlRegistersStart1.SetValueText(strRegistersStart1);
		m_BL_CtrlRegistersEnd1.SetValueText(strRegistersEnd1);
		m_BL_CtrlRegistersPos.SetValueText(strRegistersPos);
		m_BL_CtrlRegistersPos1.SetValueText(strRegistersPos1);
		m_BL_CtrlCoilPos.SetValueText(strCoilPos);

		m_BL_CtrlRegisters.SetStatus(_ttoi(strRegisters));
		m_BL_CtrlRegistersStart.SetEnabled(m_BL_CtrlRegisters.GetStatus());
		m_BL_CtrlRegistersEnd.SetEnabled(m_BL_CtrlRegisters.GetStatus());
		m_BL_CtrlRegistersPos.SetEnabled(m_BL_CtrlRegisters.GetStatus());

		m_BL_CtrlRegisters1.SetStatus(_ttoi(strRegisters1));
		m_BL_CtrlRegistersStart1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
		m_BL_CtrlRegistersEnd1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
		m_BL_CtrlRegistersPos1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());

		m_BL_CtrlCoil.SetStatus(_ttoi(strCoil));
		m_BL_CtrlCoilStart.SetEnabled(m_BL_CtrlCoil.GetStatus());
		m_BL_CtrlCoilEnd.SetEnabled(m_BL_CtrlCoil.GetStatus());
		m_BL_CtrlCoilPos.SetEnabled(m_BL_CtrlCoil.GetStatus());
	}
	else
	{
		m_BL_ControllerName.SetValueText(_T(""));
		m_BL_ControllerCheckModeName.SetValueText(_T(""));
		m_BL_CtrlCoilStart.SetValueText(_T(""));
		m_BL_CtrlCoilEnd.SetValueText(_T(""));
		m_BL_CtrlRegistersStart.SetValueText(_T(""));
		m_BL_CtrlRegistersEnd.SetValueText(_T(""));
		m_BL_CtrlRegistersStart1.SetValueText(_T(""));
		m_BL_CtrlRegistersEnd1.SetValueText(_T(""));
		m_BL_CtrlRegistersPos.SetValueText(_T(""));
		m_BL_CtrlRegistersPos1.SetValueText(_T(""));
		m_BL_CtrlCoilPos.SetValueText(_T(""));

		m_BL_CtrlRegisters.SetStatus(FALSE);
		m_BL_CtrlRegisters1.SetStatus(FALSE);
		m_BL_CtrlCoil.SetStatus(FALSE);

		m_BL_CtrlRegistersStart.SetEnabled(m_BL_CtrlRegisters.GetStatus());
		m_BL_CtrlRegistersEnd.SetEnabled(m_BL_CtrlRegisters.GetStatus());
		m_BL_CtrlRegistersPos.SetEnabled(m_BL_CtrlRegisters.GetStatus());

		m_BL_CtrlRegistersStart1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
		m_BL_CtrlRegistersEnd1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
		m_BL_CtrlRegistersPos1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());

		m_BL_CtrlCoilStart.SetEnabled(m_BL_CtrlCoil.GetStatus());
		m_BL_CtrlCoilEnd.SetEnabled(m_BL_CtrlCoil.GetStatus());
		m_BL_CtrlCoilPos.SetEnabled(m_BL_CtrlCoil.GetStatus());
	}
	m_bIsFileChanged = FALSE;
}

void CControllerAddDlg::SelectChangedBlControllername(LPCTSTR strOld, LPCTSTR strNew, short nPos)
{
	// TODO: �ڴ˴������Ϣ����������
	LoadCtrlParam();
}


void CControllerAddDlg::TextChangedBlControllername(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	CMsgBox MsgBox(this);
	CString strInput = strNew;
	if (strInput.GetLength() != 0)
	{
		if (strInput[strInput.GetLength() - 1] == '/')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '|')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '\\')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == ':')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '?')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '<')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '>')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '"')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		if (strInput[strInput.GetLength() - 1] == '*')
		{
			MsgBox.ShowMsg(_T("�O�����Q���ܺ���| : ? < > / * \\ \" �����ַ�"), _T("�e�`"), MB_OK | MB_ICONSTOP);
			strInput.Delete(strInput.GetLength() - 1, 1);
			m_BL_ControllerName.SetValueText(strInput);
			return;
		}
		m_bIsFileChanged = TRUE;
		CString strFileName;
		strFileName = GetExePath() + _T("\\Controller\\") + m_BL_ControllerName.GetValueText() + _T(".ini");

		CString strCtrlName;
		CString strCtrlCheckModeName;
		CString strCoil;
		CString strCoilStart; 
		CString strCoilEnd;   
		CString strCoilPos;
		CString strRegistersStart;
		CString strRegistersEnd;
		CString strRegistersStart1;
		CString strRegistersEnd1;
		CString strRegisters;
		CString strRegisters1;
		CString strRegistersPos;
		CString strRegistersPos1;

		if (GetFileAttributes(strFileName) != -1) //����ļ�����
		{
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCtrlName"),_T(""),strCtrlName.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCtrlCheckModeName"),_T(""),strCtrlCheckModeName.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoilStart"),_T(""),strCoilStart.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoilEnd"),_T(""),strCoilEnd.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersStart"),_T(""),strRegistersStart.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersEnd"),_T(""),strRegistersEnd.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersStart1"),_T(""),strRegistersStart1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersEnd1"),_T(""),strRegistersEnd1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegisters"),_T(""),strRegisters.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegisters1"),_T(""),strRegisters1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersPos"),_T(""),strRegistersPos.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strRegistersPos1"),_T(""),strRegistersPos1.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoil"),_T(""),strCoil.GetBuffer(MAX_PATH),MAX_PATH,strFileName);
			GetPrivateProfileString(m_BL_ControllerName.GetValueText(),_T("strCoilPos"),_T(""),strCoilPos.GetBuffer(MAX_PATH),MAX_PATH,strFileName);

			m_BL_ControllerName.SetValueText(strCtrlName);
			m_BL_ControllerCheckModeName.SetValueText(strCtrlCheckModeName);
			m_BL_CtrlCoilStart.SetValueText(strCoilStart);
			m_BL_CtrlCoilEnd.SetValueText(strCoilEnd);
			m_BL_CtrlRegistersStart.SetValueText(strRegistersStart);
			m_BL_CtrlRegistersEnd.SetValueText(strRegistersEnd);
			m_BL_CtrlRegistersStart1.SetValueText(strRegistersStart1);
			m_BL_CtrlRegistersEnd1.SetValueText(strRegistersEnd1);
			m_BL_CtrlRegistersPos.SetValueText(strRegistersPos);
			m_BL_CtrlRegistersPos1.SetValueText(strRegistersPos1);
			m_BL_CtrlCoilPos.SetValueText(strCoilPos);

			m_BL_CtrlRegisters.SetStatus(_ttoi(strRegisters));
			m_BL_CtrlRegistersStart.SetEnabled(m_BL_CtrlRegisters.GetStatus());
			m_BL_CtrlRegistersEnd.SetEnabled(m_BL_CtrlRegisters.GetStatus());
			m_BL_CtrlRegistersPos.SetEnabled(m_BL_CtrlRegisters.GetStatus());

			m_BL_CtrlRegisters1.SetStatus(_ttoi(strRegisters1));
			m_BL_CtrlRegistersStart1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
			m_BL_CtrlRegistersEnd1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
			m_BL_CtrlRegistersPos1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());

			m_BL_CtrlCoil.SetStatus(_ttoi(strCoil));
			m_BL_CtrlCoilStart.SetEnabled(m_BL_CtrlCoil.GetStatus());
			m_BL_CtrlCoilEnd.SetEnabled(m_BL_CtrlCoil.GetStatus());
			m_BL_CtrlCoilPos.SetEnabled(m_BL_CtrlCoil.GetStatus());
			m_bIsFileChanged = FALSE;
		}
		m_BL_ControllerName.SetInputPos(m_BL_ControllerName.GetValueText().GetLength() + 1);
	}
}


void CControllerAddDlg::SelectChangedBlControllercheckmodename(LPCTSTR strOld, LPCTSTR strNew, short nPos)
{
	m_bIsFileChanged = TRUE;
	// TODO: �ڴ˴������Ϣ����������
}


void CControllerAddDlg::ValueChangedBlCtrlcoilstart(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}


void CControllerAddDlg::ValueChangedBlCtrlcoilend(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}


void CControllerAddDlg::ValueChangedBlCtrlregistersstart(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}


void CControllerAddDlg::ValueChangedBlCtrlregistersend(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}

void CControllerAddDlg::ValueChangedBlCtrlregistersstart1(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}


void CControllerAddDlg::ValueChangedBlCtrlregistersend1(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	
	m_bIsFileChanged = TRUE;
}

void CControllerAddDlg::StatusChangedBlCtrlregisters(BOOL bStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
	m_BL_CtrlRegistersStart.SetEnabled(m_BL_CtrlRegisters.GetStatus());
	m_BL_CtrlRegistersEnd.SetEnabled(m_BL_CtrlRegisters.GetStatus());
	m_BL_CtrlRegistersPos.SetEnabled(m_BL_CtrlRegisters.GetStatus());
}


void CControllerAddDlg::StatusChangedBlCtrlregisters1(BOOL bStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
	m_BL_CtrlRegistersStart1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
	m_BL_CtrlRegistersEnd1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
	m_BL_CtrlRegistersPos1.SetEnabled(m_BL_CtrlRegisters1.GetStatus());
}



void CControllerAddDlg::ValueChangedBlCtrlregisterspos(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}


void CControllerAddDlg::ValueChangedBlCtrlregisterspos1(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}


void CControllerAddDlg::StatusChangedBlCtrlcoil(BOOL bStatus)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
	m_BL_CtrlCoilStart.SetEnabled(m_BL_CtrlCoil.GetStatus());
	m_BL_CtrlCoilEnd.SetEnabled(m_BL_CtrlCoil.GetStatus());
	m_BL_CtrlCoilPos.SetEnabled(m_BL_CtrlCoil.GetStatus());
}


void CControllerAddDlg::ValueChangedBlCtrlcoilpos(LPCTSTR strNew)
{
	// TODO: �ڴ˴������Ϣ����������
	m_bIsFileChanged = TRUE;
}
