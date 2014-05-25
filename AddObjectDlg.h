#pragma once
#include "afxwin.h"

// CAddObjectDlg ��ȭ �����Դϴ�.

class CAddObjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddObjectDlg)

public:
	CAddObjectDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CAddObjectDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ADD_OBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
