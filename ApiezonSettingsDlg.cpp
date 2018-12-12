/////////////////////////////////////////////////////////////////////////////
// ApiezonSettingsDlg.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ApiezonSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CApiezonSettingsDlg property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CApiezonSettingsDlg, CPropertyPage)

CApiezonSettingsDlg::CApiezonSettingsDlg()
  : CPropertyPage(CApiezonSettingsDlg::IDD) {
	//{{AFX_DATA_INIT(CApiezonSettingsDlg)
	sFileCApiezon = _T("");
	//}}AFX_DATA_INIT

  bSettingChanged = false;

  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strStringItem = "File Cs Apiezon";
  strSection = "Settings";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    sFileCApiezon = strValue;
  } else {
    sFileCApiezon = "";
  }
  strValue = sFileCApiezon;
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CApiezonSettingsDlg::~CApiezonSettingsDlg() {

}


void
CApiezonSettingsDlg::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApiezonSettingsDlg)
	DDX_Text(pDX, IDC_FILE_APIEZON, sFileCApiezon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CApiezonSettingsDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CApiezonSettingsDlg)
	ON_BN_CLICKED(IDC_CHANGE, OnChangeFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApiezonSettingsDlg message handlers
/////////////////////////////////////////////////////////////////////////////


void
CApiezonSettingsDlg::OnChangeFile() {

	char szFilter[] = "File Cter Apiezon (*.cte)|*.cte|All Files (*.*)|*.*||";
  char szDefExt[] = "cte";
  CFileDialog FileDialog(TRUE, szDefExt, sFileCApiezon, OFN_HIDEREADONLY, szFilter);
  CString Prompt = "File Containing Apiezon Thermal Capacity";
  FileDialog.m_ofn.lpstrTitle = LPCTSTR(Prompt);

	if(FileDialog.DoModal() == IDOK) {
    sFileCApiezon = FileDialog.GetPathName();

    CWinApp* pApp = AfxGetApp();
    CString strSection;
    CString strValue;
    CString strStringItem;
    strSection = "Settings";
    strStringItem = "File Cs Apiezon";
    strValue      = sFileCApiezon;
    pApp->WriteProfileString(strSection, strStringItem, strValue);

    bSettingChanged = true;
  }
  UpdateData(false);
}
