
// JoshuaGIS3.h : JoshuaGIS3 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CJoshuaGIS3App:
// �� Ŭ������ ������ ���ؼ��� JoshuaGIS3.cpp�� �����Ͻʽÿ�.
//

class CJoshuaGIS3App : public CWinApp
{
public:
	CJoshuaGIS3App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJoshuaGIS3App theApp;
