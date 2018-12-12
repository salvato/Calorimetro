// LowLevelSettings.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "LowLevelSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLowLevelSettings

IMPLEMENT_DYNAMIC(CLowLevelSettings, CPropertySheet)

CLowLevelSettings::CLowLevelSettings(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CLowLevelSettings::CLowLevelSettings(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CLowLevelSettings::~CLowLevelSettings()
{
}


BEGIN_MESSAGE_MAP(CLowLevelSettings, CPropertySheet)
	//{{AFX_MSG_MAP(CLowLevelSettings)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLowLevelSettings message handlers
