#pragma once


// CRemoveConfirmDlg ��ȭ �����Դϴ�.

class CRemoveConfirmDlg : public CDialog
{
	DECLARE_DYNAMIC(CRemoveConfirmDlg)

public:
	CRemoveConfirmDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRemoveConfirmDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_REMOVE_CONFIRM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
