#pragma once

#include "math.h"
#include <vector>

#define  Bin   2
#define  DEC   10
#define  HEX   16
#define  ASCII 17

#define	CRC4_ITU   0
#define	CRC5_EPC   1
#define	CRC5_ITU  2
#define	CRC5_USB   3
#define	CRC6_ITU   4
#define	CRC7_MMC   5
#define	CRC8       6
#define	CRC8_ITU  7
#define	CRC8_ROHC  8
#define	CRC8_MAXIM  9
#define	CRC16_IBM   10
#define	CRC16_MAXIM  11
#define	CRC16_USB   12
#define	CRC16_MODBUS   13
#define	CRC16_CCITT   14
#define	CRC16_CCITT_FALSE  15
#define	CRC16_X25     16
#define	CRC16_XMODEM  17
#define	CRC16_DNP     18
#define	CRC32         19
#define	CRC32_MPEG_2  20


#define	CRC4_ITU_STRING   _T("CRC4_ITU")
#define	CRC5_EPC_STRING   _T("CRC5_EPC")
#define	CRC5_ITU_STRING  _T("CRC5_ITU")
#define	CRC5_USB_STRING   _T("CRC5_USB")
#define	CRC6_ITU_STRING   _T("CRC6_ITU")
#define	CRC7_MMC_STRING   _T("CRC7_MMC")
#define	CRC8_STRING       _T("CRC8")
#define	CRC8_ITU_STRING   _T("CRC8_ITU")
#define	CRC8_ROHC_STRING  _T("CRC8_ROHC") 
#define	CRC8_MAXIM_STRING   _T("CRC8_MAXIM")
#define	CRC16_IBM_STRING   _T("CRC16_IBM")
#define	CRC16_MAXIM_STRING   _T("CRC16_MAXIM")
#define	CRC16_USB_STRING   _T("CRC16_USB")
#define	CRC16_MODBUS_STRING   _T("CRC16_MODBUS") 
#define	CRC16_CCITT_STRING   _T("CRC16_CCITT") 
#define	CRC16_CCITT_FALSE_STRING  _T("CRC16_CCITT_FALSE") 
#define	CRC16_X25_STRING     _T("CRC16_X25")
#define	CRC16_XMODEM_STRING  _T("CRC16_XMODEM") 
#define	CRC16_DNP_STRING     _T("CRC16_DNP")
#define	CRC32_STRING         _T("CRC32")
#define	CRC32_MPEG_2_STRING  _T("CRC32_MPEG_2") 

using namespace std;

class AFX_EXT_CLASS CValueCalculate
{
public:
	CValueCalculate(void);
	~CValueCalculate(void);

	//==============��ȡ�ļ��ĵ�ǰ·��============//
	CString GetExePath(void);


	//=============������Ҫת�������ֺ�ת���Ľ���=================//
	int ValueCalculate(int nValue, int nTransform);

	//=============������Ҫת����ֵ������ת������Ӧ�Ķ�����ֵ��������,������Ҫ��ȷ���Ƿ�ת����=============//
	vector<int> ValueVectorCalculat(long long nValue, int nTransform, BOOL bRef);

	//==============����������ת��Ϊ�ַ������������ڶ�����ʹ��==============//
	vector<CString> IntVector2StringVector(vector<int> nInt);

	//===============���ַ�ת��Ϊ��������Ҫ�ṩԴ�ַ�����Դ�ַ����ĸ�ʽ===========//
	int String2Int(CString strValue, int nTransform);

	//===============������ת��Ϊ�ַ�������Ҫ�ṩ��������������===========//
	CString Int2String(long long nValue, int nTransform, int nWidth);

	//===============���ַ���ת��Ϊһ��2���Ƶ��ַ������ṩԴ�ַ�����Դ�ַ����ĸ�ʽ,������Ҫ��ȷ���Ƿ�ת=======//
	CString String2String_2(CString strValue, int nTransform, BOOL bRef);

	vector<int> String2IntVector(CString strValue, int nTransform, BOOL bRef);

	//===============�и��ַ�������Ҫ�ṩԴ�ַ������и����ַ�,��������Ϊδɾ��===========//
	vector<CString> CutString_All(CString strInpur, char chTag);

	//===============�и��ַ�������Ҫ�ṩԴ�ַ������и����ַ�,��������δɾ������ַ���===========//
	vector<CString> CutString(CString strInpur, char chTag);

	//===============�и��ַ�������Ҫ�ṩԴ�ַ�����ƽ���и�������,��������===========//
	vector<CString> CutString(CString strInpur, int nCounter);

	//===============����CRCУ���룬��Ҫ�ṩԭʼ�ַ�����У��ģʽ eg��============//

	long long CRCCheck(CString strInput, int nDataType, CString strChecckMode, CString & strResult_HEX, CString & strResult_Bin);

	//===============����У������ǣ����������ļ��еĲ���===============//
	void LoadConfigurationParam(CString strChecckMode, CString & strInputString, int & nWidth, CString & strInitData, CString & strXOROut, BOOL & bRefIn, BOOL & bRefOut);

	//===================У������=====================//
	long long CheckCalculate(long long nMode, vector<int> nCheck);//У������
	//===================У��ģʽ�ȶ�==================//
	int CheckModeCMP(CString strMode);//У������

	vector<int> FindCharInString(CString strInfo, char chInfo);//���ַ����в����ַ��������ַ�����λ�ã��M������
};

