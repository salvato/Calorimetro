/////////////////////////////////////////////////////////////////////////////
// CurrGenSettings.cpp : implementation file
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "CurrGenSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurrGenSettings property page
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CCurrGenSettings, CPropertyPage)

CCurrGenSettings::CCurrGenSettings()
  : CPropertyPage(CCurrGenSettings::IDD) {
	//{{AFX_DATA_INIT(CCurrGenSettings)
	iAddress = 8;
	//}}AFX_DATA_INIT
  iModelNumber = 0;
	
  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Current Generator";
  strStringItem = "Settings";
  strValue = pApp->GetProfileString(strSection, strStringItem);
  if(strValue != "") {
    char *buf = new char[strlen(strValue)+1];
    strcpy(buf, strValue);
    iAddress     = atoi(strtok(buf, ","));
    iModelNumber = atoi(strtok(0, "\0"));
    delete[] buf;
  }
  strValue.Format("%d,%d", iAddress, iModelNumber);
  pApp->WriteProfileString(strSection, strStringItem, strValue);
}


CCurrGenSettings::~CCurrGenSettings() {
}


void
CCurrGenSettings::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurrGenSettings)
	DDX_Control(pDX, IDC_ADDRESS, eAddress);
	DDX_Control(pDX, IDC_MODEL, cModelNumber);
	DDX_Text(pDX, IDC_ADDRESS, iAddress);
	DDV_MinMaxInt(pDX, iAddress, 1, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurrGenSettings, CPropertyPage)
	//{{AFX_MSG_MAP(CCurrGenSettings)
	ON_WM_CREATE()
	ON_EN_CHANGE(IDC_ADDRESS, OnChangeAddress)
	ON_CBN_SELCHANGE(IDC_MODEL, OnSelchangeModel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int
CCurrGenSettings::GetModelNumber() {
  return iModelNumber;
}


int
CCurrGenSettings::GetAddress() {
  return iAddress;
}


/////////////////////////////////////////////////////////////////////////////
// CCurrGenSettings message handlers
/////////////////////////////////////////////////////////////////////////////

int 
CCurrGenSettings::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}


BOOL 
CCurrGenSettings::OnInitDialog() {
	CPropertyPage::OnInitDialog();
	
  cModelNumber.SetCurSel(iModelNumber);
  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  bSettingChanged  = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void
CCurrGenSettings::OnChangeAddress() {
  CString sText;
  eAddress.GetWindowText(sText);
  if(atoi(sText) == iOldAddress) {
    bAddressModified = false;
  } else {
    bAddressModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


void
CCurrGenSettings::OnSelchangeModel() {
  if(cModelNumber.GetCurSel() == iOldModelNumber) {
    bModelModified = false;
  } else {
    bModelModified = true;
  }
  SetModified(bAddressModified || bModelModified);	
}


BOOL
CCurrGenSettings::OnApply() {
  if(!(bAddressModified || bModelModified)) return true;
	if(!UpdateData(true)) return false;

  iModelNumber = cModelNumber.GetCurSel();
  bSettingChanged = true;

  CWinApp* pApp = AfxGetApp();
  CString strSection;
  CString strValue;
  CString strStringItem;

  strSection = "Current Generator";
  strStringItem = "Settings";
  strValue.Format("%d,%d", iAddress, iModelNumber);
  pApp->WriteProfileString(strSection, strStringItem, strValue);

  bAddressModified = false;
  bModelModified   = false;
  iOldAddress      = iAddress;
  iOldModelNumber  = iModelNumber;
  SetModified(bAddressModified || bModelModified);	
	return CPropertyPage::OnApply();
}
