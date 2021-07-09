#pragma once


// CButon dialog

class CButon : public CDialogEx
{
	DECLARE_DYNAMIC(CButon)

public:
	CButon(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CButon();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDLG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
