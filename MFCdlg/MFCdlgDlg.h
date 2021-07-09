
// MFCdlgDlg.h : header file
//

#pragma once
#define TIMERCOUNT 100


// CMFCdlgDlg dialog
class CMFCdlgDlg : public CDialogEx
{
// Construction
public:
	CMFCdlgDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	int number;
	int session;
	int motion;
	int operation;
	int subject;
	int name;
	int ok;
	int m_strcount;
	int hour;
	int minute;
	int second;
	
	
	CString str;
public:
	
	void StartDebug();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_strValue;
	CDateTimeCtrl m_DTPicker;
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	CString m_strTimer;
	CString m_strCount;
	CString m_Session;
	CString m_Motion;
	CString m_Operation;
	CString m_Subject;
	CString m_Name;
	CString m_Ok;
	afx_msg void OnBnClickedBtnClear();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_OkColor;
	CBrush m_brushColor;
	CBrush m_brushColor1;
	CBrush m_brushColor2;
	CBrush m_brushColor3;
	CButton m_buttonColor;
	BOOL m_Bool;
private:
	CStatic Edit_number2;
};
