#pragma once
#include "afxwin.h"

#include "JoshuaGISColor.h"

// CPropertyForm 폼 뷰입니다.

class CPropertyForm : public CFormView
{
	DECLARE_DYNCREATE(CPropertyForm)

protected:
	CPropertyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CPropertyForm();

public:
	enum { IDD = IDD_PROPERTY_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_controlID;
	CEdit m_controlName;
	CString m_valueName;
	CEdit m_controlSize;
	CString m_valueSize;
	CEdit m_controlCha;
	CString m_valueCha;
	CEdit m_controlTemp1;
	CString m_valueTemp1;
	CEdit m_controlTemp2;
	CString m_valueTemp2;
	CEdit m_controlTemp3;
	CString m_valueTemp3;
	CEdit m_controlDesc;
	CString m_valueDesc;

	virtual void OnInitialUpdate();
	CEdit m_controlColor;
	void initialize(void);
};


