#pragma once


// CRemoveConfirmDlg 대화 상자입니다.

class CRemoveConfirmDlg : public CDialog
{
	DECLARE_DYNAMIC(CRemoveConfirmDlg)

public:
	CRemoveConfirmDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRemoveConfirmDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_REMOVE_CONFIRM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
