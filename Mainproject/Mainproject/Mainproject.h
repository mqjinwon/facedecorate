
// Mainproject.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMainprojectApp:
// �� Ŭ������ ������ ���ؼ��� Mainproject.cpp�� �����Ͻʽÿ�.
//

class CMainprojectApp : public CWinApp
{
public:
	CMainprojectApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMainprojectApp theApp;

