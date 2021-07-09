
// MFCdlgDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCdlg.h"
#include "MFCdlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCdlgDlg dialog



CMFCdlgDlg::CMFCdlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDLG_DIALOG, pParent)
	, m_strValue(_T(""))//The variable name that holds the date.
	, m_strTimer(_T(""))//The variable name that holds the time value.
	
	, m_Session(_T(""))
	, m_Motion(_T(""))
	, m_Operation(_T(""))
	, m_Subject(_T(""))
	, m_Name(_T(""))
	, m_Ok(_T(""))
	, m_Bool(FALSE)
{
	number = 0;
	session = 1;//If it is 1, Training is written, if it is 2, Maintenance is written.
	motion = 1;//If it is 1, it is written on, if it is 2, off.
	subject = 1;//If it is 1, it is written manned, if it is 2, unmanned.
	operation = 1;//If it is 1, SD Profile is written, if 2 is Direct Flight, if 3 is Maintenance.
	name = 1;
	ok = 1;//If 1 is OK, 2 is Warning, 3 is Failure.
	second = -1;
	minute = 0;
	hour = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCdlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_Date, m_strValue);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DTPicker);
	DDX_Text(pDX, IDC_STATIC_Time, m_strTimer);
	DDX_Text(pDX, IDC_STATIC_Session, m_Session);
	DDX_Text(pDX, IDC_STATIC_Motion, m_Motion);
	DDX_Text(pDX, IDC_STATIC_Operation, m_Operation);
	DDX_Text(pDX, IDC_STATIC_Subject, m_Subject);
	DDX_Text(pDX, IDC_STATIC_Name, m_Name);
	DDX_Text(pDX, IDC_STATIC_ok, m_Ok);
	DDX_Control(pDX, IDC_STATIC_ok, m_OkColor);
	DDX_Control(pDX, IDC_BTN_Clear, m_buttonColor);


	DDX_Control(pDX, IDC_STATIC_TimeCount, Edit_number2);
}


BEGIN_MESSAGE_MAP(CMFCdlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CMFCdlgDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BTN_Clear, &CMFCdlgDlg::OnBnClickedBtnClear)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCdlgDlg message handlers

BOOL CMFCdlgDlg::OnInitDialog()
{
	//----------------------------------------------------------------------------------------------------------------------------
	StartDebug();//It is written here to call the function we created below at the program start. The function was called.
	//-----------------------------------------------------------------------------------------------------------------------------
	CDialogEx::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{

			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_brushColor.CreateSolidBrush(RGB(0, 133, 68));//The CreateSolidBrush function creates a logical brush with a specified solid color. We can give this color as RGB.
	m_brushColor1.CreateSolidBrush(RGB(45, 55, 60));
	m_brushColor2.CreateSolidBrush(RGB(255, 165, 0));
	m_brushColor3.CreateSolidBrush(RGB(255, 0, 0));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCdlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();

	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCdlgDlg::OnPaint()
{
	
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCdlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCdlgDlg::StartDebug()//The code of the function to be executed from the start of the program. The function was called above
{
	SetTimer(TIMERCOUNT, 1000, NULL);

	// All of the values ​​written here are below the 67th code line in MFC dlg DLG.cpp.If the values ​​there are changed, the operation is performed according to the status of the value.

	if (session == 1)
		m_Session.Format(_T("Training"));//We check the state value that we have assigned as an int in the dlg.h section. If it is equal to 0, then Maintenance is written in the Static Text part, if not Training.
	else if (session == 2)
		m_Session.Format(_T("Maintenance"));

	if (motion == 1)//We control the motion value that we have assigned as int in the dlg.h section. If it is equal to 1, ON is written in Static Text, otherwise OF.
		m_Motion.Format(_T("Motion ON"));
	else if (motion == 2)
		m_Motion.Format(_T("Motion OFF"));

	if (operation == 1)//We perform the control of the operation value that we have assigned as int in the Dlg.h section. If it is equal to 1, SD Profile is written in Static Text, if it is equal to 0, Direct Flight is written, if it is equal to 3, Maintenance is written.
		m_Operation.Format(_T("SD Profile"));
	else if (operation == 2)
		m_Operation.Format(_T("Direct Flight"));
	else if (operation == 3)
		m_Operation.Format(_T("Maintenance"));

	if (subject == 1)//We perform the control of the subject value that we have assigned as int in the dlg.h section. If it is equal to 1, Manned is written to Static Text, and if it is equal to 2, Unmanned is written to Static Text.
		m_Subject.Format(_T("Manned"));
	else if (subject == 2)
		m_Subject.Format(_T("Unmanned"));

	if (name == 1)//In the dlg.h section, we check the name value that we have assigned as int. If it is equal to 1, 21 COR-Coriolis is written in Static Text.
		m_Name.Format(_T("21COR-Coriolis"));
	if (ok == 1)//We perform the control of the arrow value that we have assigned as int in the dlg.h section. If it is equal to 1, OK is written. If it is equal to 2, Warning is written. If it is equal to 3, Failure is written.
		m_Ok.Format(_T("OK"));
	else if(ok == 2)
		m_Ok.Format(_T("WARNİNG"));
	else if(ok == 3)
		m_Ok.Format(_T("FAİLURE"));

	SetBackgroundColor(RGB(255, 255, 255));//Written to make the background color white with RGB color codes.
	GetDlgItemText(IDC_DATETIMEPICKER1, m_strValue);//When the program starts, DateTimePicker inserts the date from the static text part we defined as m_strValue.

}



void CMFCdlgDlg::OnTimer(UINT_PTR nIDEvent)//Since a timer in the form of 00:00:00 was requested, the timer was created by writing code with if commands.
{
	if (nIDEvent == TIMERCOUNT)//It checks the equality of Timer Count to nIDEvent.
	{
		if (hour <= 9)
		{
			if (minute <= 9)
			{
				if (second <= 9)
				{
					second++;
					str.Format(_T("0%d:0%d:0%d"), hour, minute, second);
					
				Edit_number2.SetWindowText(str);

				}
				if (second >= 10)
				{

					str.Format(_T("0%d:0%d:%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);
					second++;

					if (second == 60 && minute < 9)
					{
						minute++;
						second = -1;
					}
					if (second == 61 && minute == 9)
					{
						second--;
						str.Format(_T("0%d:0%d:%d"), hour, minute, second);
						Edit_number2.SetWindowText(str);
						second = -1;
						minute++;
					}

				}
			}

			if (minute >= 10)
			{
				str.Format(_T("0%d:0%d:0%d"), hour, minute, second);
				Edit_number2.SetWindowText(str);
				if (second <= 9)
				{
					second++;
					str.Format(_T("0%d:%d:0%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);


				}
				if (second >= 10)
				{
					str.Format(_T("0%d:%d:%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);
					second++;
					if (second == 60)
					{
						minute++;
						second = -1;
					}

				}
				if (minute == 60)
				{
					hour++;
					minute = 0;
				}
			}
		}
		if (hour >= 10)
		{
			if (minute <= 9)
			{
				if (second <= 9)
				{
					second++;
					str.Format(_T("%d:0%d:0%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);

				}
				if (second >= 10)
				{

					str.Format(_T("%d:0%d:%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);
					second++;

					if (second == 60 && minute < 9)
					{
						minute++;
						second = -1;
					}
					if (second == 61 && minute == 9)
					{
						second--;
						str.Format(_T("%d:0%d:%d"), hour, minute, second);
						Edit_number2.SetWindowText(str);
						second = -1;
						minute++;
					}

				}
			}

			if (minute >= 10)
			{
				str.Format(_T("%d:0%d:0%d"), hour, minute, second);
				Edit_number2.SetWindowText(str);
				if (second <= 9)
				{
					second++;
					str.Format(_T("%d:%d:0%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);


				}
				if (second >= 10)
				{
					str.Format(_T("%d:%d:%d"), hour, minute, second);
					Edit_number2.SetWindowText(str);
					second++;
					if (second == 60)
					{
						minute++;
						second = -1;
					}

				}
				if (minute == 60)
				{
					hour++;
					minute = 0;
				}
			}
		}
	}
	CTime CurrentTime = CTime::GetCurrentTime(); //Returns an object that represents the current time inside the computer.
	//Ctime: It is the current hour value of your computer.
	int iHours = CurrentTime.GetHour();//Returns the time displayed by the object.
	int iMinutes = CurrentTime.GetMinute();//Returns the minute the object represents. Indicates the minute in local time from 0 to 59.
	int iSeconds = CurrentTime.GetSecond();//Returns the seconds represented by the object. Returns the second in local time in the range 0 to 59.
	CString strHours, strMinutes, strSeconds;

	if (iHours < 10) //%d means that an integer variable will be displayed on the screen.
		strHours.Format(_T("0%d"), iHours);//If the hour value of our clock is less than 10, "0%d" is done to bring a leading zero.
	else
		strHours.Format(_T("%d"), iHours);

	if (iMinutes < 10)
		strMinutes.Format(_T("0%d"), iMinutes);//If the minute value of our clock is less than 10, "0%d" operation is performed to bring a leading zero.
	else
		strMinutes.Format(_T("%d"), iMinutes);

	if (iSeconds < 10)
		strSeconds.Format(_T("0%d"), iSeconds);//If the second value of our clock is less than 10, "0%d" operation is performed to bring a leading zero.
	else
		strSeconds.Format(_T("%d"), iSeconds);

	m_strTimer.Format(_T("%s:%s:%s"), strHours, strMinutes, strSeconds);//%s is used because we want to write our timer value as a string. For sorting, it was written as hour/minute/second.

	UpdateData(FALSE);//UpdateData(FALSE): used to put values ​​in variables into associated controls.
	CDialogEx::OnTimer(nIDEvent);
}



void CMFCdlgDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	GetDlgItemText(IDC_DATETIMEPICKER1, m_strValue);//It allows us to pass the data in the DateTimePicker to the value static text value, which we call m_strValue.

	UpdateData(FALSE);

	*pResult = 0;
}

void CMFCdlgDlg::OnBnClickedBtnClear()
{
	if (m_Bool == TRUE)//It is written to make a BOOL statement in the background FALSE if TRUE and TRUE if FALSE each time the Clear Interlocks button is pressed. The initial value of the BOOL expression is false.
	{
		m_Bool = FALSE;
	}
	else
		m_Bool = TRUE;

	UpdateData(FALSE);

}


HBRUSH CMFCdlgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//In CMFCdlgDLG, VM_CTLCOLOR has been added from the messages section in the properties section, so that the background color and text color can be changed.
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ok) //It provided access to the ID of Static Text, which is IDC_STATIC_ok.
	{
		pDC->SetTextColor(RGB(140,183, 209));//We changed the text color part.
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SessionType)
	{
		pDC->SetTextColor(RGB(60, 80, 90));
		hbr = m_brushColor1;//145. The value m_bruscolor1 assigned in code line is assigned to hbr here.
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Session)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MotionType)
	{
		pDC->SetTextColor(RGB(60, 80, 90));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Motion)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_SubjectType)
	{
		pDC->SetTextColor(RGB(60, 80, 90));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Subject)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_OperationMode)
	{
		pDC->SetTextColor(RGB(60, 80, 90));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Operation)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_ProfilName)
	{
		pDC->SetTextColor(RGB(60, 80, 90));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Name)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_TrainingTime)
	{
		pDC->SetTextColor(RGB(60, 80, 90));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TimeCount)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Date)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_Time)
	{
		pDC->SetTextColor(RGB(140, 183, 209));
		hbr = m_brushColor1;
	}
	if (pWnd->GetDlgCtrlID() == IDC_BTN_Clear)
	{
		hbr = m_brushColor1;
	}

	if (ok == 1)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ok)//Using GetDlgCtrID, we reached the ID part of the Dialog. We said, "If the value reached is the value written, take action."
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			hbr = m_brushColor;//We have assigned the value in m_brushColor, which we defined at the top, here.
			m_Ok = "OK";
		}
	}
	if (ok == 2)
	{

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ok)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			hbr = m_brushColor2;
			m_Ok = "WARNİNG";
			
		}
	}
	if (ok == 3)
	{

		if (pWnd->GetDlgCtrlID() == IDC_STATIC_ok)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			hbr = m_brushColor3;
			m_Ok = "FAİLURE";
		}
	}
	return hbr;
}


