/////////////////////////////////////////////////////////////////////////////
// EasterDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "EasterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasterDlg dialog
/////////////////////////////////////////////////////////////////////////////


CEasterDlg::CEasterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEasterDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CEasterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void 
CEasterDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEasterDlg)
	DDX_Control(pDX, IDC_STARTSCTRL, m_starsCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEasterDlg, CDialog)
	//{{AFX_MSG_MAP(CEasterDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEasterDlg message handlers
/////////////////////////////////////////////////////////////////////////////

#define BANNER_LINES    21
char 
starBannerText[BANNER_LINES][50] = {
   "If this code works,",        //0
   "it was written by",          //1
   "",                           //2
   "© Gabriele Salvato",         //3
   "salvato@me.cnr.it",          //4
   "",                           //5
   "If not...",                  //6
   ".",                          //7
   ".",                          //8
   ".",                          //9
   "I don't know who wrote it.", //10
   ":-)",                        //11
   "Credits:",                   //12
   "Pablo van der Meer -",       //13
   " for this control",          //14
   "",                           //15
   "Paul DiLascia",              //16
   "for \"...if this code...\"", //17
   "",                           //18
   "Hit Esc to exit",            //19
   ".",                          //20
};


BOOL 
CEasterDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_starsCtrl.SetStarSpeed(30);
	m_starsCtrl.SetScrollSpeed(2);

   for (int i=0; i < BANNER_LINES; i++)
	   m_starsCtrl.AddTextLine(starBannerText[i]);
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
