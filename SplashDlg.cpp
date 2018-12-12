/////////////////////////////////////////////////////////////////////////////
// SplashDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "SplashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg dialog
/////////////////////////////////////////////////////////////////////////////


CSplashDlg::CSplashDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplashDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CSplashDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void 
CSplashDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplashDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSplashDlg, CDialog)
	//{{AFX_MSG_MAP(CSplashDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplashDlg message handlers
/////////////////////////////////////////////////////////////////////////////

void
CSplashDlg::OnTimer(UINT nIDEvent) {
	OnOK();
	CDialog::OnTimer(nIDEvent);
}


BOOL
CSplashDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
  SetTimer(1, 3000, NULL);
  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
