// FileInProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "FileInProcessDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileInProcessDlg dialog


CFileInProcessDlg::CFileInProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileInProcessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileInProcessDlg)
	sFilename = _T("");
	//}}AFX_DATA_INIT
}


void CFileInProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileInProcessDlg)
	DDX_Text(pDX, IDC_FILENAME, sFilename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFileInProcessDlg, CDialog)
	//{{AFX_MSG_MAP(CFileInProcessDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileInProcessDlg message handlers
