
// VisualFatigueDetectionSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVisualFatigueDetectionSystemApp:
// �йش����ʵ�֣������ VisualFatigueDetectionSystem.cpp
//

class CVisualFatigueDetectionSystemApp : public CWinApp
{
public:
	CVisualFatigueDetectionSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVisualFatigueDetectionSystemApp theApp;