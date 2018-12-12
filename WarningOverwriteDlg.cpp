/////////////////////////////////////////////////////////////////////////////
// WarningOverwriteDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "WarningOverwriteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWarningOverwriteDlg dialog
/////////////////////////////////////////////////////////////////////////////


CWarningOverwriteDlg::CWarningOverwriteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarningOverwriteDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CWarningOverwriteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void
CWarningOverwriteDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarningOverwriteDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarningOverwriteDlg, CDialog)
	//{{AFX_MSG_MAP(CWarningOverwriteDlg)
	ON_BN_CLICKED(ID_MERGE, OnMerge)
	ON_BN_CLICKED(IDC_OVERWRITE, OnOverwrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarningOverwriteDlg message handlers
/////////////////////////////////////////////////////////////////////////////

void
CWarningOverwriteDlg::OnMerge() {
	EndDialog(ID_MERGE);
}


void
CWarningOverwriteDlg::OnOverwrite() {
	EndDialog(IDC_OVERWRITE);
	
}


void
CWarningOverwriteDlg::OnCancel() {
	CDialog::OnCancel();
}
