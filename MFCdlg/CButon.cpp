// CButon.cpp : implementation file
//

#include "pch.h"
#include "MFCdlg.h"
#include "CButon.h"
#include "afxdialogex.h"


// CButon dialog

IMPLEMENT_DYNAMIC(CButon, CDialogEx)

CButon::CButon(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDLG_DIALOG, pParent)
{

}

CButon::~CButon()
{
}

void CButon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CButon, CDialogEx)
END_MESSAGE_MAP()


// CButon message handlers
