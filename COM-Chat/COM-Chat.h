
// COM-Chat.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CApp:
// � ���������� ������� ������ ��. COM-Chat.cpp
//

class CApp : public CWinApp
{
public:
	CApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CApp theApp;