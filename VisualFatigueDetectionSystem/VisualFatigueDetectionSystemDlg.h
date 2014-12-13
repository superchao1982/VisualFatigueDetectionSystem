
// VisualFatigueDetectionSystemDlg.h : ͷ�ļ�
//

#pragma once

#include "src\CvvImage.h"
#include "src\FaceTracking.h"

#define WM_UPDATEDATA (WM_USER+100)

// CVisualFatigueDetectionSystemDlg �Ի���
class CVisualFatigueDetectionSystemDlg : public CDialogEx
{
// ����
public:
	CVisualFatigueDetectionSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VISUALFATIGUEDETECTIONSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpendevice();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnFtstart();
	afx_msg void OnBnClickedBtnFtstop();
	afx_msg LRESULT OnUpdatedata(WPARAM wParam, LPARAM lParam);
private:
	// �����������ٺ������߳̾��
	HANDLE m_hTreadFT;
public:
	void DrawImgtoDC(IplImage * img, UINT ID);
	CString m_statusBar;
	void SetStatusContent(string str);
	
};
