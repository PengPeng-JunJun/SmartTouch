#pragma once

#include <IPHlpApi.h>
#include <iostream>
#include <windows.h>
#include <winioctl.h>
#include <vector>

#pragma comment(lib, "IPHlpApi.lib") //��Ҫ���Iphlpapi.lib��

using namespace std;

#define  MAX_IDE_DRIVES  4

typedef struct _tagDriveInfo
{  
	USHORT wGenConfig;				// WORD 0: ������Ϣ��
	USHORT wNumCyls;				// WORD 1: ������
	USHORT wReserved2;				// WORD 2: ����
	USHORT wNumHeads;				// WORD 3: ��ͷ��
	USHORT wReserved4;				// WORD 4: ����
	USHORT wReserved5;				// WORD 5: ����
	USHORT wNumSectorsPerTrack;		// WORD 6: ÿ�ŵ�������
	USHORT wVendorUnique[3];		// WORD 7-9: �����趨ֵ
	CHAR sSerialNumber[20];			// WORD 10-19:���к�
	USHORT wBufferType;				// WORD 20: ��������
	USHORT wBufferSize;				// WORD 21: �����С
	USHORT wECCSize;				// WORD 22: ECCУ���С
	CHAR sFirmwareRev[8];			// WORD 23-26: �̼��汾
	CHAR sModelNumber[40];			// WORD 27-46: �ڲ��ͺ�
	USHORT wMoreVendorUnique;		// WORD 47: �����趨ֵ
	USHORT wReserved48;				// WORD 48: ����

	struct
	{
		USHORT reserved1:8;
		USHORT DMA:1;				// 1 = ֧��DMA
		USHORT LBA:1;				// 1 = ֧��LBA
		USHORT DisIORDY:1;			// 1 = �ɲ�ʹ��IORDY
		USHORT IORDY:1;				// 1 = ֧��IORDY
		USHORT SoftReset:1;			// 1 = ��ҪATA������
		USHORT Overlap:1;			// 1 = ֧���ص�����
		USHORT Queue:1;				// 1 = ֧���������
		USHORT InlDMA:1;			// 1 = ֧�ֽ����ȡDMA
	}wCapabilities;					// WORD 49: һ������

	USHORT wReserved1;				// WORD 50: ����
	USHORT wPIOTiming;				// WORD 51: PIOʱ��
	USHORT wDMATiming;				// WORD 52: DMAʱ��
	struct
	{
		USHORT CHSNumber:1;			// 1 = WORD 54-58��Ч
		USHORT CycleNumber:1;		// 1 = WORD 64-70��Ч
		USHORT UnltraDMA:1;			// 1 = WORD 88��Ч
		USHORT reserved:13;
	}wFieldValidity;				// WORD 53: �����ֶ���Ч�Ա�־

	USHORT wNumCurCyls;				// WORD 54: CHS��Ѱַ��������
	USHORT wNumCurHeads;			// WORD 55: CHS��Ѱַ�Ĵ�ͷ��
	USHORT wNumCurSectorsPerTrack;	// WORD 56: CHS��Ѱַÿ�ŵ�������
	USHORT wCurSectorsLow;			// WORD 57: CHS��Ѱַ����������λ��
	USHORT wCurSectorsHigh;			// WORD 58: CHS��Ѱַ����������λ��
	struct{   
		USHORT CurNumber:8;			// ��ǰһ���Կɶ�д������
		USHORT Multi:1;				// 1 = ��ѡ���������д
		USHORT reserved1:7;
	}wMultSectorStuff;				// WORD 59: ��������д�趨

	ULONG dwTotalSectors;			// WORD 60-61: LBA��Ѱַ��������
	USHORT wSingleWordDMA;			// WORD 62: ���ֽ�DMA֧������

	struct{
		USHORT Mode0:1;				// 1 = ֧��ģʽ0 (4.17Mb/s)
		USHORT Mode1:1;				// 1 = ֧��ģʽ1 (13.3Mb/s)
		USHORT Mode2:1;				// 1 = ֧��ģʽ2 (16.7Mb/s)
		USHORT Reserved1:5;
		USHORT Mode0Sel:1;			// 1 = ��ѡ��ģʽ0
		USHORT Mode1Sel:1;			// 1 = ��ѡ��ģʽ1
		USHORT Mode2Sel:1;			// 1 = ��ѡ��ģʽ2
		USHORT Reserved2:5;
	}wMultiWordDMA;					// WORD 63: ���ֽ�DMA֧������

	struct
	{   
		USHORT AdvPOIModes:8;		// ֧�ָ߼�POIģʽ��
		USHORT reserved:8;
	}wPIOCapacity;					// WORD 64: �߼�PIO֧������

	USHORT wMinMultiWordDMACycle;	// WORD 65: ���ֽ�DMA�������ڵ���Сֵ

	USHORT wRecMultiWordDMACycle;	// WORD 66: ���ֽ�DMA�������ڵĽ���ֵ
	USHORT wMinPIONoFlowCycle;		// WORD 67: ��������ʱPIO�������ڵ���Сֵ
	USHORT wMinPOIFlowCycle;		// WORD 68: ��������ʱPIO�������ڵ���Сֵ
	USHORT wReserved69[11];			// WORD 69-79: ����

	struct   
	{   
		USHORT Reserved1:1;   
		USHORT ATA1:1;				// 1 = ֧��ATA-1
		USHORT ATA2:1;				// 1 = ֧��ATA-2
		USHORT ATA3:1;				// 1 = ֧��ATA-3
		USHORT ATA4:1;				// 1 = ֧��ATA/ATAPI-4
		USHORT ATA5:1;				// 1 = ֧��ATA/ATAPI-5
		USHORT ATA6:1;				// 1 = ֧��ATA/ATAPI-6
		USHORT ATA7:1;				// 1 = ֧��ATA/ATAPI-7
		USHORT ATA8:1;				// 1 = ֧��ATA/ATAPI-8
		USHORT ATA9:1;				// 1 = ֧��ATA/ATAPI-9
		USHORT ATA10:1;				// 1 = ֧��ATA/ATAPI-10
		USHORT ATA11:1;				// 1 = ֧��ATA/ATAPI-11
		USHORT ATA12:1;				// 1 = ֧��ATA/ATAPI-12
		USHORT ATA13:1;				// 1 = ֧��ATA/ATAPI-13
		USHORT ATA14:1;				// 1 = ֧��ATA/ATAPI-14
		USHORT Reserved2:1;   
	}wMajorVersion;				// WORD 80: ���汾

	USHORT wMinorVersion;			// WORD 81: ���汾
	USHORT wReserved82[6];			// WORD 82-87: ����

	struct   
	{   
		USHORT Mode0:1;				// 1 = ֧��ģʽ0 (16.7Mb/s)
		USHORT Mode1:1;				// 1 = ֧��ģʽ1 (25Mb/s)
		USHORT Mode2:1;				// 1 = ֧��ģʽ2 (33Mb/s)
		USHORT Mode3:1;				// 1 = ֧��ģʽ3 (44Mb/s)
		USHORT Mode4:1;				// 1 = ֧��ģʽ4 (66Mb/s)
		USHORT Mode5:1;				// 1 = ֧��ģʽ5 (100Mb/s)
		USHORT Mode6:1;				// 1 = ֧��ģʽ6 (133Mb/s)
		USHORT Mode7:1;				// 1 = ֧��ģʽ7 (166Mb/s)
		USHORT Mode0Sel:1;			// 1 = ��ѡ��ģʽ0
		USHORT Mode1Sel:1;			// 1 = ��ѡ��ģʽ1
		USHORT Mode2Sel:1;			// 1 = ��ѡ��ģʽ2
		USHORT Mode3Sel:1;			// 1 = ��ѡ��ģʽ3
		USHORT Mode4Sel:1;			// 1 = ��ѡ��ģʽ4
		USHORT Mode5Sel:1;			// 1 = ��ѡ��ģʽ5
		USHORT Mode6Sel:1;			// 1 = ��ѡ��ģʽ6
		USHORT Mode7Sel:1;			// 1 = ��ѡ��ģʽ7
		}wUltraDMA;					// WORD 88: Ultra DMA֧������
	USHORT wReserved89[167];		// WORD 89-255
}DRIVEINFO, *PDRIVEINFO;


typedef struct _tagHardDrive
{
	CString strModel;
	CString strSerial;
}HARDDRIVEINFO;


class AFX_EXT_CLASS CHardwareInfo
{
public:
	CHardwareInfo(void);
	~CHardwareInfo(void);

	HANDLE OpenDevice(CString strDevice);
	BOOL GetDriveInfo(int nDisk, PDRIVEINFO pInfo);
	void GetMacAdd(vector<CString> * pvMac);
	
protected:
	void _AdjustString(char *pszData, int nLenght);
};

