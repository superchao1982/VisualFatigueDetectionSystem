
// VisualFatigueDetectionSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VisualFatigueDetectionSystem.h"
#include "VisualFatigueDetectionSystemDlg.h"
#include "afxdialogex.h"
#include <string>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ȫ�ֱ�����
volatile bool isRunning;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CVisualFatigueDetectionSystemDlg �Ի���




CVisualFatigueDetectionSystemDlg::CVisualFatigueDetectionSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisualFatigueDetectionSystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_statusBar = _T("��ʾ��Ϣ");
}

void CVisualFatigueDetectionSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_STATUS, m_statusBar);
}

BEGIN_MESSAGE_MAP(CVisualFatigueDetectionSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENDEVICE, &CVisualFatigueDetectionSystemDlg::OnBnClickedBtnOpendevice)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CVisualFatigueDetectionSystemDlg::OnBnClickedBtnClose)
	ON_BN_CLICKED(IDC_BTN_FTSTART, &CVisualFatigueDetectionSystemDlg::OnBnClickedBtnFtstart)
	ON_BN_CLICKED(IDC_BTN_FTSTOP, &CVisualFatigueDetectionSystemDlg::OnBnClickedBtnFtstop)
	ON_MESSAGE(WM_UPDATEDATA, &CVisualFatigueDetectionSystemDlg::OnUpdatedata)
END_MESSAGE_MAP()


// CVisualFatigueDetectionSystemDlg ��Ϣ�������

BOOL CVisualFatigueDetectionSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_BTN_FTSTOP)->EnableWindow(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVisualFatigueDetectionSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVisualFatigueDetectionSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVisualFatigueDetectionSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*****************************************************
* ���̺߳��� 
******************************************************/
DWORD WINAPI ThreadFaceTracking (LPVOID pParam) 
{
	//
	CVisualFatigueDetectionSystemDlg* pDlg = (CVisualFatigueDetectionSystemDlg*)pParam;
	Mat resMat(480,640,CV_8UC3);
	string str;

	CFaceTracking ft;
	if(ft.KinectFTInitialize()<0){
		str=_T("δ�����豸���޷���ȡ�豸����");
		pDlg->SetStatusContent(str);
		pDlg->SendMessage(WM_UPDATEDATA,0,0);
		return 0;
	}
	int type = -1;
	while(isRunning)
	{
		ft.Track(resMat);
		//type = ft.GetFacialExpression();
		type = ft.GetFacialExpression(&resMat);
		// display the results: face model and face expression
		IplImage img = resMat;
		pDlg->DrawImgtoDC(&img,IDC_SHOWIMG);
		if(type == 0) str=_T("Neutral");
		else if(type > 0) str = _T("Expressive");
		else str=_T("No Track Result");
		pDlg->SetStatusContent(str);
		pDlg->SendMessage(WM_UPDATEDATA,0,0);
	}
	ft.KinectFTRelease();
	resMat = Mat::zeros(480,640,CV_8UC3);
	IplImage img = resMat;
	pDlg->DrawImgtoDC(&img,IDC_SHOWIMG);
	str=_T("��ʾ��Ϣ");
	pDlg->SetStatusContent(str);
	pDlg->SendMessage(WM_UPDATEDATA,0,0);
	return 1;
}
/***************************************************
* ��Ϣ��Ӧ����
****************************************************/
// ���豸
void CVisualFatigueDetectionSystemDlg::OnBnClickedBtnOpendevice()
{

}

// �˳�ϵͳ
void CVisualFatigueDetectionSystemDlg::OnBnClickedBtnClose()
{
	OnCancel();
}


// �������ٿ���
void CVisualFatigueDetectionSystemDlg::OnBnClickedBtnFtstart()
{
	GetDlgItem(IDC_BTN_FTSTART)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_FTSTOP)->EnableWindow(TRUE);
	// �����߳�
	DWORD threadID = 1;
	isRunning = true;
	m_hTreadFT = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFaceTracking,
		this,0,&threadID);
}


// �������ٹر�
void CVisualFatigueDetectionSystemDlg::OnBnClickedBtnFtstop()
{
	 GetDlgItem(IDC_BTN_FTSTART)->EnableWindow(TRUE);
	 GetDlgItem(IDC_BTN_FTSTOP)->EnableWindow(FALSE);
	 // �ر��߳�
	 isRunning = false; // �����߳̽������ź�
	 CloseHandle(m_hTreadFT); // �ͷž��
}

// ��������
afx_msg LRESULT CVisualFatigueDetectionSystemDlg::OnUpdatedata(WPARAM wParam, LPARAM lParam)
{
	UpdateData(FALSE);
	return 0;
}


/***************************************************
* ��Ա����
****************************************************/
void CVisualFatigueDetectionSystemDlg::DrawImgtoDC(IplImage * img, UINT ID)
{
	// get a dc
	CDC* pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cvImg;
	cvImg.CopyOf(img);
	cvImg.DrawToHDC(hDC,&rect);
	ReleaseDC(pDC);
}


void CVisualFatigueDetectionSystemDlg::SetStatusContent(string str)
{
	m_statusBar.Format("%s",str.c_str());
}
