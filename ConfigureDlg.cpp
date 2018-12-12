/////////////////////////////////////////////////////////////////////////////
// ConfigureDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CConfigureDlg, CPropertySheet)

CConfigureDlg::CConfigureDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage) {
}


CConfigureDlg::CConfigureDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage) {
}


CConfigureDlg::~CConfigureDlg() {
}


BEGIN_MESSAGE_MAP(CConfigureDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CConfigureDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CConfigureDlg message handlers
/////////////////////////////////////////////////////////////////////////////


