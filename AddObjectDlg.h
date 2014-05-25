#pragma once
#include "afxwin.h"

// CAddObjectDlg 대화 상자입니다.

class CAddObjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddObjectDlg)

public:
	CAddObjectDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAddObjectDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADD_OBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_controlID;
	CString m_valueName;
	CComboBox m_controlColorCombo;
	CString m_valueCha;
	CString m_valueTemp1;
	CString m_valueTemp2;
	CString m_valueTemp3;
	CString m_valueDesc;
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	char* colorCode[3];
	double colorCodeInDouble[3];

	CComboBox m_controlSize;
	
	CString size;
	double sizeInDouble;
};
